//---------------------------------------------------------------------------

#pragma hdrstop

#include "section.h"
#include "controller.h"

#include <algorithm>
#include <limits>
//---------------------------------------------------------------------------
Section::Section(PageController* parent)
	: parent_{parent}
	, children_{}
{

}
//---------------------------------------------------------------------------
TScrollBox* Section::getViewport() const
{
	return parent_->getViewport();
}
//---------------------------------------------------------------------------
BoundingBox Section::getBoundingBox() const
{
	auto overallBox = BoundingBox{
		std::numeric_limits <decltype(BoundingBox::top)>::max(),
		std::numeric_limits <decltype(BoundingBox::left)>::max(),
		0,
		0
	};
	for (auto const& i : children_)
	{
		auto childBox = i->getBoundingBox();
		overallBox.top = std::min(childBox.top, overallBox.top);
		overallBox.left = std::min(childBox.left, overallBox.left);
		overallBox.right = std::max(childBox.right, overallBox.right);
		overallBox.bottom = std::max(childBox.bottom, overallBox.bottom);
	}

	return overallBox;
}
//---------------------------------------------------------------------------
long Section::getMostBottom() const
{
    return getBoundingBox().bottom + generalBottomPadding;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
