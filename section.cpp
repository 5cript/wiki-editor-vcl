//---------------------------------------------------------------------------

#pragma hdrstop

#include "section.h"
#include "controller.h"
#include "element.h"

#include "ui_elements/drop_target.h"

#include <algorithm>
#include <limits>
//---------------------------------------------------------------------------
Section::Section(PageController* parent)
	: parent_{parent}
	, layout_{parent_->getViewport()}
	, children_{}
	, dropTarget_{nullptr}
{
	layout_.getControl()->OnDragOver = onDragOver;

	dropTarget_ = addElement <WikiElements::DropTarget>();
}
//---------------------------------------------------------------------------
ViewportContainer* Section::getViewport() const
{
	return parent_->getViewport();
}
//---------------------------------------------------------------------------
BoundingBox Section::getBoundingBox() const
{
	if (children_.empty())
		return {0, 0, 0, 0};

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
void __fastcall Section::onDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
	auto* control = dynamic_cast <TControl*> (Sender);
	//parent_->renderDropTarget(control->Top + X, Y);
	moveDropIndicatorToMouse();
    Accept = true;
}
//---------------------------------------------------------------------------
void Section::moveDropIndicatorToMouse()
{
	auto y = Mouse->CursorPos.Y;
	auto top = dropTarget_->getControl()->ClientToScreen(Point(0,0)).Y;
	if (top < y)
		while (top < y - 20)
		{
			moveDown(dropTarget_);
			if (top == dropTarget_->getControl()->ClientToScreen(Point(0,0)).Y)
				break;
			top = dropTarget_->getControl()->ClientToScreen(Point(0,0)).Y;
		}
	else
		while (y < top - 20)
		{
			moveUp(dropTarget_);
			if (top == dropTarget_->getControl()->ClientToScreen(Point(0,0)).Y)
				break;
			top = dropTarget_->getControl()->ClientToScreen(Point(0,0)).Y;
		}
}
//---------------------------------------------------------------------------
long Section::getAccumulativeHeight() const
{
	long totalHeight = 10;

	for (auto const& i : children_)
		totalHeight += i->getHeight();

	totalHeight += (
		layout_.getControl()->Margins->Bottom +
		layout_.getControl()->Margins->Top
	) * children_.size();

	return totalHeight;
}
//---------------------------------------------------------------------------
void Section::realign(long previousSectionEnd)
{
	parent_->getViewport()->Realign();
    auto h = getAccumulativeHeight();
	layout_.resize(getAccumulativeHeight());
	/*
	if (!children_.empty())
		children_.front()->realignAfter(previousSectionEnd + sectionSplitPadding);

	for (auto i = children_.begin(); i + 1 < children_.end(); ++i)
	{
		auto next = i + 1;
		(*next)->realignAfter(i->get());
	}
	*/
}
//---------------------------------------------------------------------------
void Section::moveDown(WikiElements::BasicElement* element)
{
	auto iter = findChild(element);
	if (iter != std::end(children_) && iter != std::begin(children_) + (children_.size() - 1))
	{
		std::iter_swap(iter, iter + 1);
		layout_.swap(iter - std::begin(children_), iter - std::begin(children_) + 1);
	}
}
//---------------------------------------------------------------------------
void Section::moveUp(WikiElements::BasicElement* element)
{
	auto iter = findChild(element);
	if (iter != std::begin(children_) && iter != std::end(children_))
	{
		std::iter_swap(iter, iter - 1);
		layout_.swap(iter - std::begin(children_), iter - std::begin(children_) - 1);
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
Layout* Section::getLayout()
{
    return &layout_;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
