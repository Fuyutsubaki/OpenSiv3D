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
# include <Renderer2D/IRenderer2D.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Renderer2D/Vertex2DBuilder.hpp>
# include <Window/IWindow.hpp>
# include <Siv3DEngine.hpp>
# include <Graphics/IGraphics.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <SDL2/SDL.h>
# include <Texture/SDL2/CTexture_SDL2.hpp>

namespace s3d
{	
	class CRenderer2D_SDL2 : public ISiv3DRenderer2D
	{
	private:
		SDL_Renderer * m_renderer;

	public:

		CRenderer2D_SDL2(){}

		~CRenderer2D_SDL2() override{}

		void init(){
			SDL_Window *w = static_cast<SDL_Window*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());
			m_renderer = SDL_CreateRenderer(w,-1, 0);
		}
		SDL_Renderer* getRenderer()const{
			return m_renderer;
		}

		void flush() override{}

		std::pair<float, FloatRect> getLetterboxingTransform() const override{
			const Float2 sceneSize = Siv3DEngine::Get<ISiv3DGraphics>()->getSceneSize();
			const Float2 backBufferSize = Siv3DEngine::Get<ISiv3DGraphics>()->getBackBufferSize();
			
			const float sx = backBufferSize.x / sceneSize.x;
			const float sy = backBufferSize.y / sceneSize.y;
			const float s = std::min(sx, sy);
			
			if (sx <= sy)
			{
				const float offsetY = (backBufferSize.y - sceneSize.y * s) * 0.5f;
				return{ s, FloatRect(0.0f, offsetY,
									static_cast<float>(backBufferSize.x),
									static_cast<float>(backBufferSize.y - offsetY * 2.0f)) };
			}
			else
			{
				const float offsetX = (backBufferSize.x - sceneSize.x * s) * 0.5f;
				return{ s, FloatRect(offsetX, 0.0f,
									static_cast<float>(backBufferSize.x - offsetX * 2.0f),
									static_cast<float>(backBufferSize.y)) };
			}
		}

		void drawFullscreen(bool) override {} // do nothing for OpenGL

		void setColorMul(const Float4& color) override{}

		ColorF getColorMul() const override{assert(false);}

		void setColorAdd(const Float4& color) override{}

		ColorF getColorAdd() const override{assert(false);}

		void setBlendState(const BlendState& state) override{}

		BlendState getBlendState() const override{assert(false);}

		void setRasterizerState(const RasterizerState& state) override{}

		RasterizerState getRasterizerState() const override{assert(false);}

		void setPSSamplerState(uint32 slot, const SamplerState& state) override{}

		SamplerState getPSSamplerState(uint32 slot) const override{assert(false);}

		void setLocalTransform(const Mat3x2& matrix) override{}

		const Mat3x2& getLocalTransform() const override{assert(false);}

		void setCameraTransform(const Mat3x2& matrix) override{}

		const Mat3x2& getCameraTransform() const override{assert(false);}

		void setScissorRect(const Rect& rect) override{}

		float getMaxScaling() const override{return 1.0;} // setLocalTransform とか

		Rect getScissorRect() const override{{assert(false);}}

		void setViewport(const Optional<Rect>& viewport) override{}

		Optional<Rect> getViewport() const override{assert(false);}

		void setSDFParameters(const Float4& parameters) override{}

		Float4 getSDFParameters() const override{}

		void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override{}

		void addTriangle(const Float2(&pts)[3], const Float4& color) override{}

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override{}

		void addRect(const FloatRect& rect, const Float4& color) override{
			SDL_SetRenderDrawColor(m_renderer, color.x*255, color.y*255, color.z*255, color.w*255);
			SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);
			SDL_Rect r ={(int)rect.left, (int)rect.top, (int)(rect.right-rect.left), (int)(rect.bottom-rect.top)};
			SDL_RenderFillRect(m_renderer,&r);
		}

		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override{
			std::cout<<"addRect()"<<std::endl;
		}

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override{}

		void addCircle(const Float2& center, float r, const Float4& color) override{}

		void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) override{}

		void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) override{}

		void addCircleArc(const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& color) override{}

		void addEllipse(const Float2& center, float a, float b, const Float4& color) override{}

		void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) override{}

		void addQuad(const FloatQuad& quad, const Float4& color) override{}

		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override{}

		void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) override{
			addRect(rect,color); // todo: ちゃんと実装すべき
		}

		void addLineString(const LineStyle& style, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) override{}

		void addShape2D(const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color) override{}

		void addShape2DTransformed(const Array<Float2>& vertices, const Array<uint16>& indices, float s, float c, const Float2& offset, const Float4& color) override{}

		void addShape2DFrame(const Float2* pts, uint16 size, float thickness, const Float4& color) override{}

		void addSprite(const Sprite& sprite, uint16 startIndex, uint16 indexCount) override{}

		void addSprite(const Texture& texture, const Sprite& sprite, uint16 startIndex, uint16 indexCount) override{}

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) override{
			SDL_Rect dst ={(int)rect.left, (int)rect.top, (int)(rect.right-rect.left), (int)(rect.bottom-rect.top)};
			// 速度や表現について様々な懸念がある
			CTexture_SDL2* const pTexture = dynamic_cast<CTexture_SDL2* const>(Siv3DEngine::Get<ISiv3DTexture>()); 
			auto &img = pTexture->getImage(texture.id());
			SDL_Rect src ={(int)(uv.left*img.width()), (int)(uv.top*img.height()), (int)((uv.right-uv.left)*img.width()), (int)((uv.bottom-uv.top)*img.height())};
			auto surf = SDL_CreateRGBSurfaceFrom((void*)img.data(),img.width(),img.height(),32,img.width()*4,0x000000FF,0x0000FF00,0x00FF0000,0xFF000000);
			auto sdl_texture = SDL_CreateTextureFromSurface(m_renderer,surf);
			SDL_SetTextureColorMod(sdl_texture,(uint8_t)(color.x*255),(uint8_t)(color.y*255),(uint8_t)(color.z*255));
			SDL_SetTextureAlphaMod(sdl_texture,(uint8_t)(color.w*255));
			SDL_RenderCopy(m_renderer,sdl_texture,&src,&dst);

			SDL_FreeSurface(surf);
			SDL_DestroyTexture(sdl_texture);
		}

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]) override{}

		void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) override{}

		void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) override{}
	
		void addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
			ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
			ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc) override{}

		const Texture& getBoxShadowTexture() const override{assert(false);}
	};
}
