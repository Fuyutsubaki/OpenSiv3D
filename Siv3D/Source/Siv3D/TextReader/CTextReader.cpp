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

# include <Siv3D/FileSystem.hpp>
# include "CTextReader.hpp"

namespace s3d
{
	namespace detail
	{
		static int32 CheckBOMSize(const IReader& reader, const TextEncoding encoding)
		{
			switch (encoding)
			{
			case TextEncoding::ANSI:
				{
					return 0;
				}
			case TextEncoding::UTF8:
				{
					uint8 bom[3] = {};
					reader.lookahead(bom);
					return (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) ? 3 : 0;
				}
			case TextEncoding::UTF16LE:
			case TextEncoding::UTF16BE:
				{
					uint8 bom[2] = {};
					reader.lookahead(bom);
					return (bom[0] == 0xFF && bom[1] == 0xFE) || (bom[0] == 0xFE && bom[1] == 0xFF) ? 2 : 0;
				}
			}

			return 0;
		}
	}

	TextReader::CTextReader::CTextReader()
	{

	}

	TextReader::CTextReader::~CTextReader()
	{
		close();
	}

	bool TextReader::CTextReader::open(const std::shared_ptr<IReader>& reader, const FilePath& path_optional, const Optional<TextEncoding>& encoding)
	{
		if (isOpened())
		{
			close();
		}

		if (!reader->isOpened())
		{
			return false;
		}

		if (encoding)
		{
			m_textEncoding = encoding.value();

			m_bomSize = detail::CheckBOMSize(*reader, m_textEncoding);
		}
		else
		{
			m_textEncoding = CharacterSet::GetEncoding(*reader, m_bomSize);
		}

		m_reader = reader;

		if (m_bomSize)
		{
			m_reader->skip(m_bomSize);
		}

		m_fullPath = path_optional;

		return true;
	}

	void TextReader::CTextReader::close()
	{
		if (!isOpened())
		{
			return;
		}

		m_bomSize = 0;

		m_textEncoding = TextEncoding::Default;

		m_reader.reset();

		m_fullPath.clear();
	}

	bool TextReader::CTextReader::isOpened() const
	{
		return static_cast<bool>(m_reader);
	}

	//bool TextReader::CTextReader::readAll(String& out);

	//void TextReader::CTextReader::readLine(String& str);

	//wchar TextReader::CTextReader::readChar()
	//{
	//	if (!isOpened() || eof())
	//	{
	//		return true;
	//	}

	//	if (m_textEncoding == TextEncoding::UTF16LE)
	//	{
	//		char16_t ch;

	//		m_reader->read(ch);

	//		return ch;
	//	}
	//	else if (m_textEncoding == TextEncoding::UTF16BE)
	//	{
	//		char16_t ch;

	//		m_reader->read(ch);

	//		ch = ((ch << 8) & 0xff00) | ((ch >> 8) & 0xFF);
	//	}
	//	else if (m_textEncoding == TextEncoding::ANSI)
	//	{
	//		m_fileText.get(ch);
	//	}
	//	else // UTF-8
	//	{
	//		char str[6] = {};

	//		m_reader->read(str, 1);

	//		const unsigned char b0 = str[0];

	//		unsigned readByte = 0;

	//		if (b0 < 0x80)	// 1B
	//		{
	//			readByte = 1;
	//		}
	//		else if (b0 < 0xC0)
	//		{
	//			return L'\0';
	//		}
	//		else if (b0 < 0xE0) // 2B
	//		{
	//			readByte = 2;
	//		}
	//		else if (b0 < 0xF0)	// 3B
	//		{
	//			readByte = 3;
	//		}
	//		else if (b0 < 0xF8)	// 4B
	//		{
	//			readByte = 4;
	//		}
	//		else if (b0 < 0xFC)	// 5B
	//		{
	//			readByte = 5;
	//		}
	//		else // 6B
	//		{
	//			readByte = 6;
	//		}

	//		if (readByte>1)
	//		{
	//			m_reader->read(str + 1, readByte - 1);
	//		}

	//		if (readByte >= 4)
	//		{
	//			ch = L'?';
	//		}
	//		else
	//		{
	//			ch = UTF8ToUTF16(str, readByte);
	//		}
	//	}

	//	return ch;
	//}

	//bool TextReader::CTextReader::eof();


	const FilePath& TextReader::CTextReader::path() const
	{
		return m_fullPath;
	}

	TextEncoding TextReader::CTextReader::encoding() const
	{
		return m_textEncoding;
	}
}
