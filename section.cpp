//---------------------------------------------------------------------------

#pragma hdrstop

#include "section.h"
#include "controller.h"
#include "element.h"
#include "debug.h"
#include "markup_converter.h"
#include "elements.h"
#include "constants.h"

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
Section::Section(Section&& other)
	: parent_{std::move(other.parent_)}
	, layout_{std::move(other.layout_)}
	, children_{std::move(other.children_)}
	, dropTarget_{std::move(other.dropTarget_)}
{
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
		auto childRef = child->getRenderedBox().bottom;
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
	//return std::max(totalHeight, 200L);
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
WikiElements::BasicElement* Section::getElementUnder(int x, int y)
{
	for (auto& child : children_)
	{
		auto box = child->getBoundingBox();
		if ((x >= box.left) &&
			(x <= box.right) &&
			(y >= box.top) &&
			(y <= box.bottom))
		{
            return &*child;
        }
	}
	return nullptr;
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
void Section::adoptStyle(WikiElements::BasicElement* element)
{
    element->setStyle(parent_->getStyle());
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
PageController* Section::getController()
{
    return parent_;
}
//---------------------------------------------------------------------------
void __fastcall Section::onElementClick(TObject* Sender, WikiElements::BasicElement* element)
{
	if (parent_->isInSelectionMode() || parent_->isAutoSelectEnabled())
	{
		parent_->stopSelectionMode(element);
	}
}
//---------------------------------------------------------------------------
Section::component_iterator Section::loadComponents(component_iterator component, component_iterator const& end)
{
	for (;component != end; ++component)
	{
		auto maybeComment = tryGetCommentText(component->get());
		if (maybeComment && maybeComment.get() == WikiEditorConstants::endSectionMarker)
			return ++component;

		if (isSubComponent(component->get()))
		{
			// add sub component to prior element.
			// TODO
        }
		else
        	elementFactory(this, component->get());
	}
	//not a requirement
	//if (components == end)
	//	throw std::runtime_error("section is not ended by end section marker");
	return end;
}
//---------------------------------------------------------------------------
void Section::saveComponents(std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>>& components) const
{
	for (auto const& i : children_)
	{
		auto* comp = extractData(i.get());
		if (comp != nullptr)
			components.emplace_back(comp);
		else
			throw std::runtime_error(std::string("impossible!? data == nullptr") + __FILE__ + ":" + std::to_string(__LINE__));
	}
	// Add END SECTION Comment
	auto* comment = new WikiMarkup::Components::ExportableCommentText;
	comment->data = WikiEditorConstants::endSectionMarker;
	components.emplace_back(comment);
}
//---------------------------------------------------------------------------
std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>> Section::saveComponents() const
{
	std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>> comps;
	saveComponents(comps);
	return comps;
}
//---------------------------------------------------------------------------
bool Section::empty() const
{
	return children_.empty();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
