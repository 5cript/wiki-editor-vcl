//---------------------------------------------------------------------------
#pragma once

#include "padding_control.h"
#include "forward_declarations.h"
#include "utilities.h"
#include "layout.h"
#include "viewport.h"

#include "wiki-markup/components/exportable_components/exportable_component.hpp"
#include "SimpleUtil/value_ptr/value_ptr.hpp"
#include <Vcl.ExtCtrls.hpp>

#include <vector>
#include <memory>
//---------------------------------------------------------------------------
class Section
{
public:
	using children_list_type = std::vector <std::unique_ptr <WikiElements::BasicElement>>;
	using child_type = WikiElements::BasicElement;
	using child_pointer_type = child_type*;

	using component_container = std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>>;
	using component_iterator = component_container::iterator;

public:
	Section(PageController* parent);

	/**
	 *  Move constructor.
	 */
	Section(Section&& other);

	/**
	 *	Sections cannot be assigned.
	 */
	Section& operator=(Section const&) = delete;

	/**
	 * 	Sections can be moved.
	 */
	Section& operator=(Section&&) = default;

	/**
	 * 	Sections cannot be copied.
	 */
	Section(Section const&) = delete;

	/**
	 *  Get the bounding box of this section. Includes all elements.
	 */
	BoundingBox getBoundingBox() const;

	/**
	 *  Returns whether the coordinate is within this section relative to the viewport.
	 */
	bool isWithin(int x, int y) const;

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
	T* addElement(int position = -1, bool ignoreStyle = false)
	{
		auto* elem = new T(this);
		try
		{
			if (position < 0)
				children_.push_back(std::unique_ptr <T> {elem});
			else
				children_.insert(children_.begin() + position, std::unique_ptr <T> {elem});

			if (!ignoreStyle)
				adoptStyle(elem);
			synchronizeLayout();
		}
		catch (std::bad_alloc const& exc)
		{
			delete elem;
            throw exc; // bad_alloc is evil shit.
		}
		return elem;
	}

	template <typename T>
	T* addElement(bool ignoreStyle)
	{
        return addElement <T>(-1, ignoreStyle);
    }

	/**
	 *  Removes the given element from the section. It will be deleted and this will
	 *  invalidate the element!! Do not use the element after calling this.
	 */
	template <typename T>
	void removeElement(T* element)
	{
		auto child = findChild(element);

		if (child != std::end(children_))
		{
			children_.erase(child);
            layout_.update();
			causePageRealign();
		}
	}

	/**
	 *  Starts drag and drop mechanism
	 */
	void startDragDrop();

	/**
	 *  Hides the drop target bar.
	 *
	 *	@return Returns the index where the indicator was.
	 */
	int endDragDrop();

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
	 *	Will do nothing, if element is already in the lowest spot.
	 *
	 *	@return Element that previously was, where 'element' is now.
	 *          Will return nullptr, if 'element' is not part of this section.
	 *			Will return 'element', if 'element' was already the last element.
	 */
	WikiElements::BasicElement* moveDown(WikiElements::BasicElement* element);

	/**
	 * 	Move element up a spot
	 *	Will do nothing, if element is already in the highest spot.
	 *
	 *	@return Element that previously was, where 'element' is now.
	 *          Will return nullptr, if 'element' is not part of this section.
	 *			Will return 'element', if 'element' was already the first element.
	 */
	WikiElements::BasicElement* moveUp(WikiElements::BasicElement* element);

	/**
	 * 	Returns a pointer to the viewport control object.
	 */
	ViewportContainer* getViewport() const;

	/**
	 *	Returns a pointer to the layout object that is responsible for ordering
	 *	and displaying the elements in a correct fashion.
	 */
	Layout* getLayout();

	/**
	 *	Returns the element that is under the given coordinates, or nullptr if
	 *	there is none there. The coordinates shall be relative to the viewport.
	 */
	WikiElements::BasicElement* getElementUnder(int x, int y);

	/**
	 * 	Returns a pointer to the controller for this section.
	 */
	PageController* getController();

	/**
	 * 	Called by elements.
	 */
	void __fastcall onElementClick(TObject* Sender, WikiElements::BasicElement* element);

	/**
	 * 	Load components into section from exportables.
	 **/
	component_iterator loadComponents(component_iterator components, component_iterator const& end);

	/**
	 *  Save components into exportable format. (Appends END_SECTION comment)
	 **/
	void saveComponents(std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>>& components) const;

	/**
	 *  Save components into exportable format. (Appends END_SECTION comment)
	 **/
	std::vector <sutil::value_ptr <WikiMarkup::Components::IExportableComponent>> saveComponents() const;

	/**
	 * 	Returns wether the section is empty or not.
	 */
    bool empty() const;

public:
	void __fastcall onDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);

private:
	children_list_type::iterator findChild(WikiElements::BasicElement* element);
	void synchronizeLayout();
    void adoptStyle(WikiElements::BasicElement* element);

private:
	PageController* parent_;
	Layout layout_;
	children_list_type children_;
	WikiElements::DropTarget* dropTarget_;
};
//---------------------------------------------------------------------------
