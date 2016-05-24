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
# include <Siv3D/TextReader.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	class TextReader::CTextReader
	{
	private:

		std::shared_ptr<IReader> m_reader;

		FilePath m_fullPath;

		int32 m_bomSize = 0;

		TextEncoding m_textEncoding = TextEncoding::Default;

	public:

		CTextReader();

		~CTextReader();

		bool open(const std::shared_ptr<IReader>& reader, const FilePath& path_optional, const Optional<TextEncoding>& encoding);

		void close();

		bool isOpened() const;

		bool readAll(String& out);

		void readLine(String& str);

		wchar readChar();

		bool eof();

		const FilePath& path() const;

		TextEncoding encoding() const;
	};
}
