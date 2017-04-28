//---------------------------------------------------------------------------
#pragma once

#include <Vcl.Graphics.hpp>

#include <boost/optional.hpp>

#include <cstdint>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace StyleContainment
{
	enum class FontWeight : int
	{
		Normal,
		Bold
	};

	enum class TextAlign
	{
    	Invalid,
		Left,
		Center,
		Right
	};

	enum class FontStyle
	{
		Normal,
		Italic
    };

	struct Style
	{
		TColor background = clWhite;
		TColor highlightBackground = clGray;
		TColor fontColor = clBlack;
		TColor highlightFontColor = clBlack;
		FontWeight fontWeight = FontWeight::Normal;
		FontWeight highlightFontWeight = FontWeight::Bold;
		FontStyle fontStyle = FontStyle::Normal;
        FontStyle highlightFontStyle = FontStyle::Normal;
		int fontSize = 9;
		int highlightFontSize = 9;
        TextAlign alignment = TextAlign::Left;
	};
}
//---------------------------------------------------------------------------
