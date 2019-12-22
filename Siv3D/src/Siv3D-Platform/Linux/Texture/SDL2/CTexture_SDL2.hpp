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

# pragma once
# include <thread>
# include <mutex>
# include <atomic>
# include <Texture/ITexture.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "Texture_SDL2.hpp"

namespace s3d
{
	class CTexture_SDL2 : public ISiv3DTexture
	{
	private:

		AssetHandleManager<TextureID, Texture_SDL2> m_textures{ U"Texture" };

		const std::thread::id m_id = std::this_thread::get_id();
		
		struct Request
		{
			const Image *pImage = nullptr;
			
			const Array<Image> *pMipmaps = nullptr;
			
			const TextureDesc* pDesc = nullptr;
			
			std::reference_wrapper<TextureID> idResult;
			
			std::reference_wrapper<std::atomic<bool>> waiting;
		};
		
		Array<Request> m_requests;
		
		std::mutex m_requestsMutex;
		
		bool isMainThread() const;
		
		TextureID pushRequest(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc);
		
	public:

		~CTexture_SDL2() override;

		void init();

		void updateAsync(size_t maxUpdate) override;

		TextureID createUnmipped(const Image& image, TextureDesc desc) override;

		TextureID create(const Image& image, const Array<Image>& mips, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const ColorF& color, TextureFormat format, TextureDesc desc) override;

		void release(TextureID handleID) override;

		Size getSize(TextureID handleID) override;

		TextureDesc getDesc(TextureID handleID) override;

		bool fill(TextureID handleID, const ColorF& color, bool wait) override;

		bool fillRegion(TextureID handleID, const ColorF& color, const Rect& rect) override;

		bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) override;

		bool fillRegion(TextureID handleID, const void* src, uint32 stride, const Rect& rect, bool wait) override;
		
		
		s3d::Image const& getImage(TextureID handleID){return m_textures[handleID]->getImage();}
	};
}
