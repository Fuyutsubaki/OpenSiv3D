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
# include <sstream>
# include "Fwd.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "FormatInt.hpp"
# include "FormatFloat.hpp"

namespace s3d
{
	/// <summary>
	/// Format の内部で使用するデータ
	/// </summary>
	struct FormatData
	{
		String string;

		struct DecimalPlace
		{
			explicit constexpr DecimalPlace(int32 v = 5) : value(v) {}
			int32 value;
		} decimalPlace;
	};

	/// <summary>
	/// 浮動小数点数を変換する際の小数点以下の最大桁数を指定するマニピュレータを返します。
	/// </summary>
	/// <param name="width">
	/// 小数点以下の最大桁数
	/// </param>
	/// <remarks>
	/// この関数が返すマニピュレータを Format の引数にすると、
	/// 該当 Format() 内のそれ以降の浮動小数点数の変換に適用されます。
	/// </remarks>
	/// <returns>
	/// Format に渡すマニピュレータ
	/// </returns>
	inline constexpr FormatData::DecimalPlace DecimalPlace(int32 width)
	{
		return FormatData::DecimalPlace(width);
	}

	namespace literals
	{
		inline namespace formatting_literals
		{
			inline constexpr FormatData::DecimalPlace operator ""_dp(unsigned long long width)
			{
				return DecimalPlace(static_cast<int32>(width));
			}
		}
	}

	namespace detail
	{
		/// <summary>
		/// Format の内部で使用するクラス
		/// </summary>
		template <class...>
		struct format_validation : std::true_type {};

		/// <summary>
		/// Format の内部で使用するクラス
		/// </summary>
		template <class T, class... TT>
		struct format_validation<T, TT...>
			: std::integral_constant<bool, !std::is_same<std::decay_t<T>, char*>::value && format_validation<TT...>::value> {};

		/// <summary>
		/// Format の内部で使用する関数
		/// </summary>
		inline void Format(const FormatData&)
		{
			return;
		}

		/// <summary>
		/// Format の内部で使用する関数
		/// </summary>
		template <class Type, class... Args>
		inline void Format(FormatData& formatData, const Type& value, const Args&... args)
		{
			Formatter(formatData, value);
			Format(formatData, args...);
		}
	}

	/// <summary>
	/// 一連の引数を文字列に変換します。
	/// </summary>
	/// <param name="args">
	/// 変換する値
	/// </param>
	/// <returns>
	/// 引数を文字列に変換して連結した文字列
	/// </returns>
	template <class... Args>
	inline String Format(const Args&... args)
	{
		static_assert(detail::format_validation<Args...>::value, "type \"char*\" cannot be used in Format()");
		FormatData formatData;
		detail::Format(formatData, args...);
		return std::move(formatData.string);
	}

	/// <summary>
	/// 引数を文字列に変換します。
	/// </summary>
	/// <param name="ch">
	/// 変換する値
	/// </param>
	/// <returns>
	/// 引数を文字列に変換した文字列
	/// </returns>
	inline String Format(wchar ch)
	{
		return String(1, ch);
	}

	/// <summary>
	/// 引数を文字列に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 引数を文字列に変換した文字列
	/// </returns>
	inline String Format(const wchar* const str)
	{
		return String(str);
	}

	/// <summary>
	/// 引数を文字列に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 引数を文字列に変換した文字列
	/// </returns>
	inline String Format(const String& str)
	{
		return str;
	}

	/// <summary>
	/// 引数を文字列に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 引数を文字列に変換した文字列
	/// </returns>
	inline String Format(String&& str)
	{
		return std::move(str);
	}

	inline void Formatter(FormatData& formatData, int32 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, uint32 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, int64 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, uint64 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, double value)
	{
		wchar buf[384];
		const size_t len = detail::FormatFloat(buf, value, formatData.decimalPlace.value, false);
		formatData.string.append(buf, len);
	}

	//void Formatter(FormatData& formatData, const void* value);

	void Formatter(FormatData& formatData, const char* const str) = delete;

	inline void Formatter(FormatData& formatData, std::nullptr_t)
	{
		formatData.string.append(L"null", 4);
	}

	inline void Formatter(FormatData& formatData, bool value)
	{
		if (value)
		{
			formatData.string.append(L"true", 4);
		}
		else
		{
			formatData.string.append(L"false", 5);
		}
	}

	inline void Formatter(FormatData& formatData, char value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, int8 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, uint8 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, int16 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, uint16 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, long value)
	{
		Formatter(formatData, static_cast<int64>(value));
	}

	inline void Formatter(FormatData& formatData, unsigned long value)
	{
		Formatter(formatData, static_cast<uint64>(value));
	}

	inline void Formatter(FormatData& formatData, wchar value)
	{
		formatData.string.push_back(value);
	}

	inline void Formatter(FormatData& formatData, float value)
	{
		Formatter(formatData, static_cast<double>(value));
	}

	inline void Formatter(FormatData& formatData, const FormatData::DecimalPlace decimalPlace)
	{
		formatData.decimalPlace = decimalPlace;
	}

	inline void Formatter(FormatData& formatData, const wchar* const str)
	{
		formatData.string.append(str);
	}

	inline void Formatter(FormatData& formatData, const String& str)
	{
		formatData.string.append(str);
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const Optional<Type>& opt)
	{
		if (opt)
		{
			formatData.string.append(L"Optional ", 9);

			Formatter(formatData, opt.value());
		}
		else
		{
			formatData.string.append(L"none", 4);
		}
	}

	inline void Formatter(FormatData& formatData, nullopt_t)
	{
		formatData.string.append(L"none", 4);
	}

	template <class Iterator>
	inline void Formatter(FormatData& formatData, Iterator begin, Iterator end)
	{
		formatData.string.push_back(L'{');

		bool isFirst = true;

		while (begin != end)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.push_back(L',');
			}

			Formatter(formatData, *begin);

			++begin;
		}

		formatData.string.push_back(L'}');
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const Type(&values)[N])
	{
		Formatter(formatData, std::begin(values), std::end(values));
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const std::array<Type, N>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type, class Allocator = std::allocator<Type>>
	inline void Formatter(FormatData& formatData, const std::vector<Type, Allocator>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline void Formatter(FormatData& formatData, const Array<Type, Allocator>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const std::initializer_list<Type>& ilist)
	{
		Formatter(formatData, ilist.begin(), ilist.end());
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const Type& value)
	{
		std::wostringstream wos;

		wos << value;

		formatData.string.append(wos.str());
	}

	/*
	void Formatter(FormatData& formatData, const Color& value);
	void Formatter(FormatData& formatData, const ColorF& value);
	void Formatter(FormatData& formatData, const HSV& value);
	void Formatter(FormatData& formatData, const Point& value);
	void Formatter(FormatData& formatData, const Float2& value);
	void Formatter(FormatData& formatData, const Vec2& value);
	void Formatter(FormatData& formatData, const Float3& value);
	void Formatter(FormatData& formatData, const Vec3& value);
	void Formatter(FormatData& formatData, const Float4& value);
	void Formatter(FormatData& formatData, const Vec4& value);
	void Formatter(FormatData& formatData, const __m128& value);
	void Formatter(FormatData& formatData, const Circular& value);
	void Formatter(FormatData& formatData, const LineInt& value);
	void Formatter(FormatData& formatData, const Line& value);
	void Formatter(FormatData& formatData, const Rect& value);
	void Formatter(FormatData& formatData, const RectF& value);
	void Formatter(FormatData& formatData, const Circle& value);
	void Formatter(FormatData& formatData, const Ellipse& value);
	void Formatter(FormatData& formatData, const Triangle& value);
	void Formatter(FormatData& formatData, const Quad& value);
	void Formatter(FormatData& formatData, const RoundRect& value);
	void Formatter(FormatData& formatData, const Mat3x2& value);
	void Formatter(FormatData& formatData, const Quaternion& value);
	void Formatter(FormatData& formatData, const Mat4x4& value);
	void Formatter(FormatData& formatData, const Ray& value);
	*/
}
