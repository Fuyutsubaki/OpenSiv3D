# pragma once
# include <Siv3D/Image.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureFormat.hpp>
#include<SDL2/SDL.h>

namespace s3d
{
	class Texture_SDL2
	{
	private:
		
        s3d::Image m_img;
				
		TextureDesc m_textureDesc = TextureDesc::Unmipped;
		
		bool m_isDynamic = false;
		
		bool m_initialized = false;
		
	public:
		
		struct Null {};
		
		Texture_SDL2() = default;
		
		Texture_SDL2(Null)
            :Texture_SDL2(Image (16, 16, Palette::Yellow),TextureDesc::Unmipped)
        {}
		
		Texture_SDL2(const Image& image, TextureDesc desc)
            :m_img(image),
            m_textureDesc(desc),
            m_isDynamic(false),
            m_initialized(true)
        {}
		
		//Texture_SDL2(const Image& image, const Array<Image>& mipmaps, TextureDesc desc);
		
		Texture_SDL2(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc)
        {
            assert(false);
        }
		
		~Texture_SDL2(){}
		
		bool isInitialized() const noexcept
		{
			return m_initialized;
		}
		
		s3d::Image const& getImage() const
		{
			return m_img;
		}
		
		Size getSize() const
		{
			return m_img.size();
		}
		
		TextureDesc getDesc() const
		{
			return m_textureDesc;
		}
		
		bool fill(const ColorF& color, bool wait){assert(false);}
		
		bool fillRegion(const ColorF& color, const Rect& rect){assert(false);}
		
		bool fill(const void* src, uint32 stride, bool wait){assert(false);}
		
		bool fillRegion(const void* src, uint32 stride, const Rect& rect, bool wait){assert(false);}
	};
}
