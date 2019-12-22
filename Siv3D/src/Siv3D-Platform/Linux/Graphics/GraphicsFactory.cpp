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

//# include <Graphics/GL/CGraphics_GL.hpp>
# include <Graphics/SDL2/CGraphics_SDL2.hpp>

namespace s3d
{
	ISiv3DGraphics* ISiv3DGraphics::Create()
	{
		return new CGraphics_SDL2;
	}
}
