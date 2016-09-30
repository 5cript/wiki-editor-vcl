//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
constexpr static const unsigned int leftSectionPadding = 8;
constexpr static const unsigned int generalTopPadding = 0;
constexpr static const unsigned int generalBottomPadding = 5;
constexpr static const unsigned int rightSectionPadding = 10;
constexpr static const unsigned int sectionSplitPadding = 5;
constexpr static const unsigned int dropBarMove = 10;
//---------------------------------------------------------------------------
template <typename MarginType>
void applyDefaultMargins(MarginType* margin)
{
	constexpr static const unsigned int left = 4;
	constexpr static const unsigned int top = sectionSplitPadding;
	constexpr static const unsigned int right = 4;
	constexpr static const unsigned int bottom = 0;
	margin->SetBounds(left, top, right, bottom);
}
//---------------------------------------------------------------------------