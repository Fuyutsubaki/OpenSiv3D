//----------------------------------------------------------------------------------------
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//	
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
//----------------------------------------------------------------------------------------

# pragma once
# ifndef SIV3D_INCLUDED
	# define SIV3D_INCLUDED
# endif

# include "Siv3D/Platform.hpp"
# include "Siv3D/PlatformWindows.hpp"

//
// ユーティリティ
//
	// ライブラリのバージョン
	# include "Siv3D/Version.hpp"
	// 型
	# include "Siv3D/Types.hpp"
	// 前方宣言
	# include "Siv3D/Fwd.hpp"
	// ユーティリティ
	# include "Siv3D/Utility.hpp"
	// コピー禁止クラス
	# include "Siv3D/Uncopyable.hpp"
	// アロケータ
	# include "Siv3D/Allocator.hpp"
	// 動的配列
	# include "Siv3D/Array.hpp"
	// 範囲
	# include "Siv3D/Step.hpp"
	// 二次元配列
	# include "Siv3D/Grid.hpp"
	// Optional
	# include "Siv3D/Optional.hpp"
	// unspecified
	# include "Siv3D/Unspecified.hpp"
//
// 文字列と数値
//
	// 文字
	//# include "Siv3D/Char.hpp"
	// 文字列
	# include "Siv3D/String.hpp"
	// 文字列ビュー
	//# include "Siv3D/StringView.hpp"
	// 文字コード変換
	//# include "Siv3D/CharacterSet.hpp"
	// 基数
	# include "Siv3D/Radix.hpp"
	// 大文字小文字
	# include "Siv3D/LetterCase.hpp"	
	// 数値
	# include "Siv3D/Number.hpp"
	// 多倍長整数
	# include "Siv3D/BigInt.hpp"
	// 整数のフォーマット
	# include "Siv3D/FormatInt.hpp"
	// 浮動小数点数のフォーマット
	# include "Siv3D/FormatFloat.hpp"
	// ブール値のフォーマット
	# include "Siv3D/FormatBool.hpp"
	// データ -> 文字列 の変換
	# include "Siv3D/Format.hpp"
	// フォーマットリテラル
	# include "Siv3D/FormatLiteral.hpp"
	// 文字列 -> データ の変換
	//# include "Siv3D/Parse.hpp"
	// 正規表現
	//# include "Siv3D/Regex.hpp"
//
// 時刻と時間
//
	// 時間の単位
	//# include "Siv3D/Duration.hpp"
	// 日付
	//# include "Siv3D/Date.hpp"
	// 日付と時刻
	//# include "Siv3D/DateTime.hpp"
	// 時間
	# include "Siv3D/Time.hpp"
	// ストップウォッチ
	//# include "Siv3D/Stopwatch.hpp"
	// イベント付きストップウォッチ
	//# include "Siv3D/EventTimer.hpp"
	// スピードを変更可能なストップウォッチ
	//# include "Siv3D/VariableSpeedStopwatch.hpp"
	// 処理にかかった時間の測定
	//# include "Siv3D/ProfilerUtility.hpp"
//
// ファイル I/O と暗号化
//
