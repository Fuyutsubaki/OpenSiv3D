# pragma once
# include <memory>
# include <Siv3D/Color.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Scene.hpp>
# include <Graphics/IGraphics.hpp>
# include <Window/IWindow.hpp>
# include <Siv3DEngine.hpp>
# include <SDL2/SDL.h>
# include <Renderer2D/SDL2/CRenderer2D_SDL2.hpp>

namespace s3d
{
	class CGraphics_SDL2 : public ISiv3DGraphics
	{
	private:
		SDL_Window * m_window;
		SDL_Renderer * m_renderer;

		ColorF m_clearColor = Palette::DefaultBackground;
		ColorF m_letterboxColor = Palette::DefaultLetterbox;
	public:

		CGraphics_SDL2(){}

		~CGraphics_SDL2() override{}

		void init() override{
			assert(SDL_Init(SDL_INIT_VIDEO) == 0);
			m_window = static_cast<SDL_Window*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());
			CRenderer2D_SDL2 * renderer2D = dynamic_cast<CRenderer2D_SDL2*>(Siv3DEngine::Get<ISiv3DRenderer2D>());
			renderer2D->init();
			m_renderer = renderer2D->getRenderer();
		}

		bool present() override{
			SDL_RenderPresent(m_renderer);
			return true;
		}

		void clear() override{
			auto c = m_clearColor.toColor();
			SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
			SDL_RenderClear(m_renderer);
		}

		void flush() override{
			assert(false);
		}
		
		void setSceneTextureFilter(TextureFilter textureFilter) override{
			assert(false);
		}
		
		TextureFilter getSceneTextureFilter() const override{
			assert(false);
			return {};
		}

		void setBackgroundColor(const ColorF& color) override{
			m_clearColor = color;
		}

		void setLetterboxColor(const ColorF& color) override{
			m_letterboxColor = color;
		}

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) override{
			assert(false);
		}

		Optional<double> getTargetFrameRateHz() const override{
			assert(false);
			return 0;
		}

		double getDPIScaling() const override{
			assert(false);
			return 0;
		}

		double getDisplayRefreshRateHz() const override{
			assert(false);
			return 0;
		}

		void skipClearScreen() override{
			assert(false);
		}

		const Size& getBackBufferSize() const override{
			assert(false);
		}

		const Size& getSceneSize() const override{
			assert(false);
		}

		void setSceneSize(const Size& sceneSize) override{
			assert(false);
		}

		void resizeBuffers(const Size& backBufferSize, const Size& sceneSize) override{
			assert(false);
		}

		Optional<Rect> getFullscreenRect() override{
			assert(false);
			return {};
		}

		void requestScreenCapture() override{
			assert(false);
		}

		const Image& getScreenCapture() const override{
			assert(false);
		}
	};
}
