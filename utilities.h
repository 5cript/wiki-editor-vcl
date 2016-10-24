//---------------------------------------------------------------------------
#pragma once

// Include all necessary css stuff
#include "wretched-css/style_sheet.hpp"

#include <boost/optional.hpp>

#include <string>

#include <Vcl.Graphics.hpp>

struct BoundingBox
{
	long top;
	long left;
	long right;
	long bottom;

	BoundingBox(long top = 0, long left = 0, long right = 0, long bottom = 0)
		: top{top}
		, left{left}
		, right{right}
		, bottom{bottom}
	{
	}

	long height() const { return bottom - top; }
	long width() const { return right - left; }
};
//---------------------------------------------------------------------------
int getRenderedFontHeight(TFont* font);
//---------------------------------------------------------------------------
