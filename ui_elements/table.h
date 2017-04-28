//---------------------------------------------------------------------------
#pragma once

#include "../element.h"
#include "../section.h"

#include "styling/style_container.h"

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
		 *  Calls gatherStyle for each cell.
		 *  Very costly.
		 */
		void populateStyleGrid();

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

		/**
		 *  get table row count.
		 */
		std::size_t getRowCount() const;

		/**
		 * 	get table column count.
		 */
		std::size_t getColumnCount() const;

		/**
		 * 	Write table model to user interface.
		 */
		void writeModelToUserInterface() override;

	protected: // wimu events
		void styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign) override;

	private: // vcl events
		void __fastcall onDrawCell(TObject *Sender, int ACol, int ARow, TRect const &Rect, TGridDrawState State);
		void __fastcall onSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
		void __fastcall onMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall onExit(TObject* Sender);
		void __fastcall onSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);

	protected:
		void initializeOptionsFrame() override;
		void initializeStyleOptionsFrame() override;

	private: // private methods
		/**
		 *  Makes a style sheet out of all styles that are given by the overall
		 *	style sheet and the attributes of the table, the rows and the cell.
		 *
		 *  All given styles will then have to cascade for a proper cell style.
		 *	The cascade order is the same as the style order in the style sheet.
		 */
		WretchedCss::StyleSheet gatherStyles(std::size_t row, std::size_t column);

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

		/**
		 *  Set text in a cell in the view.
		 *
		 *	@param if updateModel is set to true, the model gets updated with `test`.
		 */
		void setViewCellText(std::size_t row, std::size_t column, std::string const& text, bool updateModel = false);

		/**
		 *  Update the table row heights.
		 *	This should be done after text, table size or style changes.
		 */
		void updateRowHeights();

		/**
		 *  Update the table column widths.
		 *	This should be done after text, table size or style changes.
		 */
		void updateColumnWidths();

		/**
		 *  Updates both height and width and realigns the table withing the section.
		 *	This should be done after text, table size or style changes.
		 */
		void updateSizes();

		/**
		 *
		 */
		void TransformCellStyle(TColor* background, TColor* textColor);

	private: // members
		std::vector <std::vector <StyleContainment::Style> > styleGrid_; // row major
		TColor borderColor_;
	};

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
