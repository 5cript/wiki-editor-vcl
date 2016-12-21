//---------------------------------------------------------------------------
#pragma once

#include "../element.h"
#include "../section.h"

#include "wretched-css/style_sheet.hpp"

// Model / Data
#include "wiki-markup/components/exportable_components/exportable_table.hpp"

// View
#include <Vcl.Grids.hpp> // TDrawGrid

// STL
#include <memory>
#include <utility>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class Table : public Element <Table, TStringGrid, WikiMarkup::Components::ExportableTable>
	{
	public:
		Table(Section* parentSection);

		/**
		 *  Makes a style sheet out of all styles that are given by the overall
		 *	style sheet and the attributes of the table, the rows and the cell.
		 *
		 *  All given styles will then have to cascade for a proper cell style.
		 *	The cascade order is the same as the style order in the style sheet.
		 */
		WretchedCss::StyleSheet gatherStyles(std::size_t row, std::size_t column);

		/**
		 *  Sets the size of the table.
		 *
		 *	@param height The new height.
		 *	@param width The new width.
		 *	@param safeMode does not shrink the table, if it contains data that would be lost.
		 *
		 *  @return Will only return false, if shrinking fails due to safe mode.
		 */
		bool resize(std::size_t height, std::size_t width, bool safeMode = false);

	protected: // wimu events
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser) override;

	private: // vcl events
		void __fastcall onDrawCell(TObject *Sender, int ACol, int ARow, TRect const &Rect, TGridDrawState State);
		void __fastcall onSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
		void __fastcall onMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	protected:
		void initializeOptionsFrame() override;
		void initializeStyleOptionsFrame() override;

	private: // private methods
		/**
		 *	Will resize a wiki table row to the given width.
		 *	This function is internal and does not need to do safety checkings.
		 *	As placing the check here would make resizing partially an issue.
		 *
		 *	@param row A table row
		 *	@param width The width to resize the row to.
		 **/
		void resizeRow(WikiMarkup::Components::TableRow& row, std::size_t width);

		/**
		 * 	Returns the width of the table. (min, max)
		 *
		 *	@return A table is not guaranteed to be of homogenous width,
		 *  		therefore we cannot assume a definitive width here.
		 */
		std::pair <std::size_t, std::size_t> getTableWidth() const;

	private: // members
    };

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
