//---------------------------------------------------------------------------

#pragma hdrstop

#include "utilities.h"

#include <memory>
//---------------------------------------------------------------------------
int getRenderedFontHeight(TFont* font)
{
	static std::map <int, int> memoization;

	auto iter = memoization.find(font->Size);
	if (iter != std::end (memoization))
		return iter->second;

	std::unique_ptr <TBitmap> bm (new TBitmap);
	bm->Canvas->Font->Assign(font);
	auto lineHeight = bm->Canvas->TextHeight("W|x");

	if (memoization.size() < 1000)
		memoization[font->Size] = lineHeight;

	return lineHeight;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
