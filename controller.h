//---------------------------------------------------------------------------

#pragma once

#include "section.h"
#include "element.h"
#include "viewport.h"

// UI Elements
#include "ui_elements/header.h"
#include "ui_elements/text.h"
#include "ui_elements/horizontal_line.h"
#include "ui_elements/table.h"
#include "ui_elements/drop_target.h"

#include "wretched-css/style_sheet.hpp"

#include <vector>
#include <functional>
#include <mutex>
#include <atomic>

#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
class PageController
{
public:
	PageController(ViewportContainer* viewport);

	/**
	 *	The controller can be created before the viewport.
	 *	Therefore we have to initialize the viewport delayed.
	 */
	void initializeViewport();

	/**
	 *	Adds a section to the page
	 */
	void addSection();

	/**
	 *  Function for testing purposes only. Do not use. Will be removed later.
	 */
	void test();

	/**
	 * 	Realigns all sections in order, which realign their elements.
	 */
	void realign();

	/**
	 *	Returns the section under the coordinates, relative to the viewport.
	 */
	Section* getSectionUnder(int x, int y);

	/**
	 *	Returns the element that is under the cursor, or nullptr if
	 *	there is none there.
	 *
	 *	@return Element under cursor or nullptr.
	 */
	WikiElements::BasicElement* getElementUnderCursor();

	/**
	 *  Returns the section directly under the cursor.
	 */
	Section* getSectionUnderCursor();

	/**
	 * 	Add an element to a specific section at the specified position.
	 */
	template <typename ElementT>
	WikiElements::BasicElement* addElement(std::pair <Section*, int> const& parameters)
	{
		auto* section = parameters.first;
		int pos = parameters.second;

		if (section == nullptr)
			return nullptr;

		auto* elem = section->addElement <ElementT> (pos);
		makeDirty();
		if (!parsedStyle_.empty())
			elem->setStyle(parsedStyle_);
		realign();
		return elem;
    }

	/**
	 *  Starts drag and drop mechanism
	 */
	void startDragDrop();

	/**
	 *  Hides the drop target bar.
	 *
	 *  @return Returns a pair of a section pointer and the position the
	 *			drop indicator was at. For insertion of new items.
	 */
	std::pair <Section*, int> endDragDrop();

	/**
	 *  Sets the css style from a string. (utf-8 buffer)
	 */
	void setStyle(std::string const& style);

	/**
	 *  Sets the css style from the appdata path. (utf-8 buffer)
	 */
	void setStyle();

	/**
	 *	Sets the css style from a string.
	 */
	void setStyle(boost::filesystem::path const& styleFile);

	/**
	 *  Returns the current css style as a string.
	 */
	std::string getStyleString() const;

	/**
	 * 	Returns the current css style as a WCSS Style Sheet.
	 **/
	WretchedCss::StyleSheet getStyle() const;

	/**
	 * 	Returns a pointer to the viewport control object.
	 */
	ViewportContainer* getViewport() const;

	/**
	 *  Start mode for selecting elements.
	 */
	void startSelectionMode(std::function <void(WikiElements::BasicElement*)> const& cb);

	/**
	 *  Leave mode for selecting elements.
	 */
	void stopSelectionMode(WikiElements::BasicElement* element = nullptr);

	/**
	 *  Is selection mode active?
	 */
	bool isInSelectionMode() const;

	/**
	 *  Checks whether the page is in auto selection mode.
	 *  Elements will be automatically selected on click when in auto select mode.
	 */
	bool isAutoSelectEnabled() const;

	/**
	 *  Set the selection mode.
	 */
	void setAutoSelectEnabled(bool autoSelect);

	/**
	 * 	Saves the page as a .tar.bz2
	 */
	void save(std::string const& fileName) const;

	/**
	 *	Loads a page from a .tar.bz2
	 **/
	void load(std::string const& fileName);

	/**
	 *	Loads a page from a markup string.
	 **/
	void loadFromMarkup(std::string const& markup);

	/**
	 *  Empties everything and adds a blank section.
	 */
	void reset();

	/**
	 *	Checks if there are any elements in any section.
	 */
	bool empty() const;

    /**
	 *  There were changes within any section! A save is recommended.
	 *	(A call to save resets the dirty flag)
	 */
	void makeDirty();

	/**
	 *  Returns whether the state has changed since last save.
	 */
	bool isDirty() const;

private: // private methods
	void clearDirtyFlag() const;

private: // vcl events
	void __fastcall dropIndicatorDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
	void __fastcall onViewportClick(TObject* Sender);

private:
	ViewportContainer* viewport_;
	std::vector <Section> sections_;
	std::string style_;
    WretchedCss::StyleSheet parsedStyle_;
	std::function <void(WikiElements::BasicElement*)> selectionCallback_;
	bool autoSelect_;
	mutable std::recursive_mutex sectionGuard_;
	mutable std::atomic_bool dirty_;
};
//---------------------------------------------------------------------------
