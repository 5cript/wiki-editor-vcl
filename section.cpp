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
bool Section::isWithin(int x, int y) const
{
	auto box = getBoundingBox();
	return
		(x > box.left) &&
		(y > box.top) &&
		(x < box.right) &&
		(y < box.bottom)
	;
}
//---------------------------------------------------------------------------
void __fastcall Section::onDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
	auto* control = dynamic_cast <TControl*> (Sender);
	parent_->renderDropTarget(control->Top + X, Y);
    Accept = true;
}
//---------------------------------------------------------------------------
BoundingBox Section::placeDropIndicator(int x, int y)
{
	if (children_.empty())
		return {0, 0, 0, 0};

	auto element = std::begin(children_);
	for (; element < std::end(children_); ++element)
		if (y < ((*element)->getBoundingBox().top + (*element)->getBoundingBox().height() / 2))
			break;

	if (element == std::end(children_))
		return {children_.back()->getBoundingBox().bottom, 0, 0, 0};
	else
        return {(*element)->getBoundingBox().top - 13, 0, 0, 0};
}
//---------------------------------------------------------------------------
void Section::makeSpaceForDrop()
{
	int counter = 1;
	for (auto element = std::begin(children_); element < std::end(children_); ++element)
	{
		(*element)->moveDown(counter * 15);
		++counter;
    }
}
//---------------------------------------------------------------------------
std::pair <WikiElements::BasicElement*, WikiElements::BasicElement*>
Section::getDropEnclosingElements(int x, int y)
{
	if (children_.empty())
		return {nullptr, nullptr};

	std::pair <WikiElements::BasicElement*,WikiElements::BasicElement*> result;
	int loopCount = 0;
	for (auto& element : children_)
	{
		if (y < (element->getBoundingBox().top + element->getBoundingBox().height() / 2))
			break;
		loopCount++;
	}
	return {
		(loopCount - 1) > 0 ? &*children_[loopCount - 1] : nullptr,
		(loopCount != children_.size()) ? &*children_[loopCount] : nullptr
	};
}
//---------------------------------------------------------------------------
void Section::realign(long previousSectionEnd)
{
	if (!children_.empty())
        children_.front()->realignAfter(previousSectionEnd + sectionSplitPadding);

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
