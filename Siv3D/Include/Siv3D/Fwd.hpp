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
# include "Types.hpp"

namespace s3d
{
	//////////////////////////////////////////////////////
	//
	//	Uncopyable.hpp
	//
	class Uncopyable;

	//////////////////////////////////////////////////////
	//
	//	Allocator.hpp
	//
	template <class Type, size_t Alignment> class AlignedAllocator;
	template <class Type> struct DefaultAllocator;

	//////////////////////////////////////////////////////
	//
	//	Array.hpp
	//
	template <class Type, class Allocator> class Array;

	//////////////////////////////////////////////////////
	//
	//	Optional.hpp
	//
	struct nullopt_t;
	template <class Type> class Optional;

	//////////////////////////////////////////////////////
	//
	//	String.hpp
	//
	class String;

	//////////////////////////////////////////////////////
	//
	//	Radix.hpp
	//
	class Radix;

	//////////////////////////////////////////////////////
	//
	//	LetterCase.hpp
	//
	enum class LetterCase;

	//////////////////////////////////////////////////////
	//
	//	Format.hpp
	//
	struct FormatData;
}
