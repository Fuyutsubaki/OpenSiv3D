//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/TextureFormat.hpp>
# include <Siv3D/System.hpp>
# include "CTexture_SDL2.hpp"

namespace s3d
{
	namespace detail
	{
		Array<Byte> GenerateInitialColorBuffer(const Size& size, const ColorF& color, const TextureFormat format)
		{
			const size_t num_pixels = size.x * size.y;
			
			if (format == TextureFormat::R8G8B8A8_Unorm)
			{
				Array<Byte> bytes(num_pixels * sizeof(uint32));
				
				const uint32 value = Color(color).asUint32();
				
				uint32* pDst = static_cast<uint32*>(static_cast<void*>(bytes.data()));
				
				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
				
				return bytes;
			}
			
			return Array<Byte>();
		}
	}
	
	CTexture_SDL2::~CTexture_SDL2()
	{
		LOG_TRACE(U"CTexture_SDL2::~CTexture_SDL2()");

		m_textures.destroy();
	}

	void CTexture_SDL2::init()
	{
		LOG_TRACE(U"CTexture_SDL2::init()");

		auto nullTexture = std::make_unique<Texture_SDL2>(Texture_SDL2::Null{});

		if (!nullTexture->isInitialized())
		{
			throw EngineError(U"Null Texture initialization failed");
		}

		m_textures.setNullData(std::move(nullTexture));

		LOG_INFO(U"ℹ️ CTexture_SDL2 initialized");
	}

	void CTexture_SDL2::updateAsync(const size_t maxUpdate)
	{
		std::lock_guard<std::mutex> lock(m_requestsMutex);
		
		const size_t toProcess = std::min<size_t>(maxUpdate, m_requests.size());
		
		for (size_t i = 0; i < toProcess; ++i)
		{
			auto& request = m_requests[i];
			
			if (*request.pMipmaps)
			{
				request.idResult.get() = create(*request.pImage, *request.pMipmaps, *request.pDesc);
			}
			else
			{
				request.idResult.get() = createUnmipped(*request.pImage, *request.pDesc);
			}
			
			request.waiting.get() = false;
		}
		
		m_requests.erase(m_requests.begin(), m_requests.begin() + toProcess);
	}

	TextureID CTexture_SDL2::createUnmipped(const Image& image, const TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}
		
		if (!isMainThread())
		{
			return pushRequest(image, Array<Image>(), desc);
		}
		
		auto texture = std::make_unique<Texture_SDL2>(image, desc);
		
		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}
		
		return m_textures.add(std::move(texture), U"(size:{0}x{1})"_fmt(image.width(), image.height()));
	}

	TextureID CTexture_SDL2::create(const Image& image, const Array<Image>& mips, const TextureDesc desc)
	{
		assert(false);/*
		if (!image)
		{
			return TextureID::NullAsset();
		}
		
		if (!isMainThread())
		{
			return pushRequest(image, mips, desc);
		}
		
		auto texture = std::make_unique<Texture_SDL2>(image, mips, desc);
		
		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}
		
		return m_textures.add(std::move(texture), U"(size:{0}x{1})"_fmt(image.width(), image.height()));
		 */
	}

	TextureID CTexture_SDL2::createDynamic(const Size& size, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc desc)
	{
		auto texture = std::make_unique<Texture_SDL2>(size, pData, stride, format, desc);
		
		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}
		
		return m_textures.add(std::move(texture), U"(Dynamic, size:{0}x{1})"_fmt(size.x, size.y));
	}

	TextureID CTexture_SDL2::createDynamic(const Size& size, const ColorF& color, const TextureFormat format, const TextureDesc desc)
	{
		const Array<Byte> initialData = detail::GenerateInitialColorBuffer(size, color, format);
		
		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	void CTexture_SDL2::release(const TextureID handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_SDL2::getSize(const TextureID handleID)
	{
		return m_textures[handleID]->getSize();
	}

	TextureDesc CTexture_SDL2::getDesc(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc();
	}

	bool CTexture_SDL2::fill(const TextureID handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(color, wait);
	}

	bool CTexture_SDL2::fillRegion(TextureID handleID, const ColorF& color, const Rect& rect)
	{
		return m_textures[handleID]->fillRegion(color, rect);
	}

	bool CTexture_SDL2::fill(const TextureID handleID, const void* const src, const uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(src, stride, wait);
	}

	bool CTexture_SDL2::fillRegion(TextureID handleID, const void* src, uint32 stride, const Rect& rect, const bool wait)
	{
		return m_textures[handleID]->fillRegion(src, stride, rect, wait);
	}
	
	bool CTexture_SDL2::isMainThread() const
	{
		return std::this_thread::get_id() == m_id;
	}
	
	TextureID CTexture_SDL2::pushRequest(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		std::atomic<bool> waiting = true;
		
		TextureID result = TextureID::NullAsset();
		
		{
			std::lock_guard<std::mutex> lock(m_requestsMutex);
			
			m_requests.push_back(Request{ &image, &mipmaps, &desc, std::ref(result), std::ref(waiting) });
		}
		
		while (waiting)
		{
			System::Sleep(3);
		}
		
		return result;
	}
}
