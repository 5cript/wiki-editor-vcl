//---------------------------------------------------------------------------
#pragma once

#include <Vcl.Graphics.hpp>

#include <boost/optional.hpp>

#include <cstdint>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace TableStyling
{
	enum class FontWeight : int
	{
		Normal,
		Bold
	};

	struct Style
	{
		TColor background = clWhite;
		TColor highlightBackground = clGray;
		TColor fontColor = clBlack;
		TColor highlightFontColor = clBlack;
		FontWeight fontWeight = FontWeight::Normal;
		FontWeight highlightFontWeight = FontWeight::Bold;
		int fontSize = 9;
		int highlightFontSize = 9;
	};
}
//---------------------------------------------------------------------------
