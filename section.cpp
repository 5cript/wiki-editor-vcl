//---------------------------------------------------------------------------

#pragma hdrstop

#include "section.h"
#include "controller.h"
#include "element.h"

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
void Section::realign()
{
	for (auto i = children_.begin(); i + 1 < children_.end(); ++i)
	{
		auto next = i + 1;
        (*next)->realignAfter(i->get());
    }
}
//---------------------------------------------------------------------------
WikiElements::BasicElement* Section::getPredecessor(WikiElements::BasicElement* reference)
{
	auto child = findChild(reference);
	if (child == std::end(children_) || child == std::begin(children_))
		return nullptr;
	else
		return &*(*(child - 1));
}
//---------------------------------------------------------------------------
WikiElements::BasicElement* Section::getSuccessor(WikiElements::BasicElement* reference)
{
	auto child = findChild(reference);
	if (child == std::end(children_) || (child + 1) == std::end(children_))
		return nullptr;
	else
		return &*(*(child + 1));
}
//---------------------------------------------------------------------------
Section::children_list_type::iterator Section::findChild(WikiElements::BasicElement* element)
{
	children_list_type::iterator child = std::begin(children_);
    for (; child != std::end(children_); ++child)
		if (&*(*child) == element)
			break;

	return child;
}
//---------------------------------------------------------------------------
void Section::causePageRealign()
{
    parent_->realign();
}
//---------------------------------------------------------------------------
long Section::getMostBottom() const
{
    return getBoundingBox().bottom + generalBottomPadding;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
