//---------------------------------------------------------------------------

#pragma hdrstop

#include "section.h"
#include "controller.h"
#include "element.h"
#include "debug.h"

#include "ui_elements/drop_target.h"

#include <algorithm>
#include <limits>
#include <functional>
//---------------------------------------------------------------------------
Section::Section(PageController* parent)
	: parent_{parent}
	, layout_{parent_->getViewport()}
	, children_{}
	, dropTarget_{nullptr}
{
	layout_.getControl()->OnDragOver = onDragOver;
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
bool Section::isWithin(int x, int y) const
{
	auto box = getBoundingBox();
	return
		(x >= box.left) &&
		(x <= box.right) &&
		(y >= box.top) &&
		(y <= box.bottom)
	;
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
	if (!dropTarget_)
		return;

	auto mouseY = Mouse->CursorPos.Y;

	std::function <child_pointer_type(child_pointer_type)> moveOperation;
	std::function <bool(int, int)> comparisonOperator;
	std::function <child_pointer_type(child_pointer_type)> xCessor;

	auto getYPosition = [](child_pointer_type control) {
		return control->getBasicControl()->ClientToScreen(Point(0,0)).Y;
	};

	if (dropTarget_->getControl()->ClientToScreen(Point(0,0)).Y < mouseY)
	{
		moveOperation = [this](child_pointer_type ptr) {
			return moveDown(ptr);
		};

		comparisonOperator = [](int lhs, int rhs) {
			return lhs > rhs;
		};

		xCessor = [this](child_pointer_type ptr) {
			return getPredecessor(ptr);
		};
	}
	else
	{
		moveOperation = [this](child_pointer_type ptr) {
			return moveUp(ptr);
		};

		comparisonOperator = [](int lhs, int rhs) {
			return lhs < rhs;
		};

		xCessor = [this](child_pointer_type ptr) {
			return getSuccessor(ptr);
		};
	}

	child_pointer_type prevChild = nullptr;
	child_pointer_type corresChild = nullptr;
	bool found = false;
	for (auto& child : children_)
	{
		auto childRef = child->getBasicControl()->ClientToScreen(Point(0,0)).Y +
						   child->getBasicControl()->Height;
		if (comparisonOperator(childRef, mouseY))
		{
			corresChild = &*child;
			if (corresChild == dropTarget_)
				return;
			found = true;
			break;
		}
	}
	if (!found)
	{
		auto str = dropTarget_->getDataTypeName();
		while (moveOperation(dropTarget_) != dropTarget_)
		{ }
	}

	corresChild = xCessor(corresChild);
	if (corresChild == dropTarget_)
		return;

	if (corresChild != nullptr)
	{
		child_pointer_type prev = nullptr;
		do {
			prev = moveOperation(dropTarget_);
			//if (prev == dropTarget_)
			//	break;
		} while (!comparisonOperator(getYPosition(dropTarget_), getYPosition(corresChild)));
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
WikiElements::BasicElement* Section::moveDown(WikiElements::BasicElement* element)
{
	auto iter = findChild(element);
	if (iter != std::end(children_) && iter != std::begin(children_) + (children_.size() - 1))
	{
		layout_.swap(iter - std::begin(children_), iter - std::begin(children_) + 1);
		std::iter_swap(iter, iter + 1);
		return &**(iter);
	}
	else if (iter == std::end(children_))
		return nullptr;
	else
		return element;
}
//---------------------------------------------------------------------------
WikiElements::BasicElement* Section::moveUp(WikiElements::BasicElement* element)
{
	auto iter = findChild(element);
	if (iter != std::begin(children_) && iter != std::end(children_))
	{
		layout_.swap(iter - std::begin(children_), iter - std::begin(children_) - 1);
		std::iter_swap(iter, iter - 1);
		return &**(iter);
	}
	else if (iter == std::end(children_))
		return nullptr;
	else
		return element;
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
void Section::startDragDrop()
{
	dropTarget_ = addElement <WikiElements::DropTarget>();
	realign();
}
//---------------------------------------------------------------------------
int Section::endDragDrop()
{
	int pos = findChild(dropTarget_) - std::begin(children_);
	removeElement(dropTarget_);
	dropTarget_ = nullptr;
	return pos;
}
//---------------------------------------------------------------------------
void Section::synchronizeLayout()
{
	auto csize = children_.size();
	for (std::size_t i = 0; i != csize; ++i)
	{
        layout_.moveControl(children_[i]->getBasicControl(), i);
    }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
