//---------------------------------------------------------------------------

#pragma once

#include "section.h"
#include "element.h"
#include "viewport.h"

#include <vector>
#include <functional>

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
	 * 	Add a header to a specific section at the specified position.
	 */
	WikiElements::BasicElement* addHeader(Section* section, int pos = -1);

	/**
	 * 	Add a header to a specific section at the specified position (using a pair).
	 */
	WikiElements::BasicElement* addHeader(std::pair <Section*, int> const& parameters);

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
	 *	Sets the css style from a string.
	 */
	void setStyle(boost::filesystem::path const& styleFile);

	/**
	 *  Returns the current css style as a string.
	 */
	std::string getStyleString() const;

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

private: // vcl events
	void __fastcall dropIndicatorDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
	void __fastcall onViewportClick(TObject* Sender);

private:
	ViewportContainer* viewport_;
	std::vector <Section> sections_;
	std::string style_;
	std::function <void(WikiElements::BasicElement*)> selectionCallback_;
	bool autoSelect_;
};
//---------------------------------------------------------------------------
