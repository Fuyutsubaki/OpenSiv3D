﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// 1 バイトを表現する型
	/// </summary>
	enum class Byte : unsigned char { };
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Byte
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	namespace detail
	{
		constexpr wchar ToHexU4(const uint8 value_0_15)
		{
			constexpr wchar s[16] = {
				L'0', L'1', L'2', L'3', L'4', L'5',L'6', L'7', L'8',L'9', L'a', L'b', L'c', L'd', L'e', L'f'
			};

			return s[value_0_15];
		}
	}

	inline void Formatter(FormatData& formatData, const Byte& value)
	{
		formatData.string.append({ detail::ToHexU4(static_cast<uint8>(value) >> 4), detail::ToHexU4(static_cast<uint8>(value) & 0xF) });
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Byte& value)
	{
		const wchar s[2] = { detail::ToHexU4(static_cast<uint8>(value) >> 4), detail::ToHexU4(static_cast<uint8>(value) & 0xF) };

		return os << s;
	}
}
//
//////////////////////////////////////////////////////////////////////////////
