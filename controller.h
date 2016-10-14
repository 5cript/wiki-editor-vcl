//---------------------------------------------------------------------------

#pragma once

#include "section.h"
#include "element.h"
#include "viewport.h"

#include <vector>
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

	void addSection();

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
	 *  Returns the section directly under the cursor.
	 */
	Section* getSectionUnderCursor();

	WikiElements::BasicElement* addHeader(Section* section, int pos = -1);
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

	void setStyle(std::string const& style);
	void setStyle(boost::filesystem::path const& styleFile);
	std::string getStyleString() const;

	ViewportContainer* getViewport() const;

private: // vcl events
	void __fastcall DropIndicatorDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);

private:
	ViewportContainer* viewport_;
	std::vector <Section> sections_;
	std::string style_;
};
//---------------------------------------------------------------------------
