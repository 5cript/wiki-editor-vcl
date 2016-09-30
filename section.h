//---------------------------------------------------------------------------
#pragma once

#include "padding_control.h"
#include "forward_declarations.h"
#include "utilities.h"
#include "layout.h"
#include "viewport.h"

#include <Vcl.ExtCtrls.hpp>

#include <vector>
#include <memory>
//---------------------------------------------------------------------------
class Section
{
public:
	using children_list_type = std::vector <std::unique_ptr <WikiElements::BasicElement>>;

public:
	Section(PageController* parent);

	/**
	 *  Get the bounding box of this section. Includes all elements.
	 */
	BoundingBox getBoundingBox() const;

	/**
	 * 	Returns the sum of all heights control elements' heights.
	 */
	long getAccumulativeHeight() const;

	/**
	 *  Get control that is the furthest down (Top + Height)
	 */
	long getMostBottom() const;

	/**
	 * 	Realigns all elements in this section
	 */
	void realign(long previousSectionEnd = 0);

	/**
	 *  Calls parent_->realign();
	 */
	void causePageRealign();

	/**
	 * 	Add an element to the section. It will be created in place and initialized.
	 */
	template <typename T>
	T* addElement()
	{
		auto* elem = new T(this);
		try
		{
			children_.push_back(std::unique_ptr <T> {elem});
		}
		catch (std::bad_alloc const& exc)
		{
            delete elem;
        }
		return elem;
	}

	template <typename T>
	void removeElement(T* element)
	{
		auto child = findChild(element);

		if (child != std::end(children_))
		{
			children_.erase(child);
			causePageRealign();
		}
	}

	/**
	 *  Returns the object which is before the given one in orthograpic (top, down) order.
	 *
	 *	@param reference reference element.
	 *	@return The predecessor element or nullptr if there is no such element.
	 */
	WikiElements::BasicElement* getPredecessor(WikiElements::BasicElement* reference);

	/**
	 *  Returns the object which is after the given one in orthograpic (top, down) order.
	 *
	 *	@param reference reference element.
	 *	@return The predecessor element or nullptr if there is no such element.
	 */
	WikiElements::BasicElement* getSuccessor(WikiElements::BasicElement* reference);

	/**
	 *	Determine where the drop will end up and create an indicator there.
	 */
	void moveDropIndicatorToMouse();

	/**
	 * 	Move element down a spot.
	 *	Will do nothing, if element is already in that spot.
	 */
	void moveDown(WikiElements::BasicElement* element);

	/**
	 * 	Move element up a spot
	 *	Will do nothing, if element is already in that spot.
	 */
	void moveUp(WikiElements::BasicElement* element);

	ViewportContainer* getViewport() const;
	Layout* getLayout();

public:
    void __fastcall onDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);

private:
	children_list_type::iterator findChild(WikiElements::BasicElement* element);

private:
	PageController* parent_;
	Layout layout_;
	children_list_type children_;
	WikiElements::DropTarget* dropTarget_;
};
//---------------------------------------------------------------------------
