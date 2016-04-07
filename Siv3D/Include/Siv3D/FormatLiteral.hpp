//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "String.hpp"
# include "../cppformat/format.h"

namespace s3d
{
	namespace detail
	{
		struct FormatHelper
		{
			const wchar* str;

			template <class... Args>
			String operator ()(Args&& ...args) const
			{
				return fmt::format(str, std::forward<Args>(args)...);
			}

			template <class... Args>
			String args(Args&& ...args) const
			{
				return operator ()(std::forward<Args>(args)...);
			}
		};
	}

	inline detail::FormatHelper Fmt(const String& s)
	{
		return detail::FormatHelper{ s.c_str() };
	}

	inline detail::FormatHelper Fmt(const wchar* s)
	{
		return detail::FormatHelper{ s };
	}

	namespace literals
	{
		inline namespace formatting_literals
		{
			inline detail::FormatHelper operator ""_fmt(const wchar* s, size_t)
			{
				return detail::FormatHelper{ s };
			}
		}
	}
}
