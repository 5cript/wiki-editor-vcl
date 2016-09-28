//---------------------------------------------------------------------------

#pragma once

#include "section.h"
#include "element.h"

#include <vector>
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
class PageController
{
public:
	PageController(TScrollBox* viewport);

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
	 *	Renders a bar where the element will be inserted to.
	 */
	void renderDropTarget(int x, int y);

	/**
	 *  Starts drag and drop mechanism
	 */
	void startDragDrop();

	/**
	 *  Hides the drop target bar.
	 */
	void endDragDrop();

	void setStyle(std::string const& style);
	void setStyle(boost::filesystem::path const& styleFile);
	std::string getStyleString() const;

	TScrollBox* getViewport() const;

private: // vcl events
	void __fastcall DropIndicatorDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);

private:
	Section* getSectionUnder(int x, int y);


private:
	TScrollBox* viewport_;
	std::unique_ptr <TPanel> dropTarget_;
	std::vector <Section> sections_;
	std::string style_;
};
//---------------------------------------------------------------------------
