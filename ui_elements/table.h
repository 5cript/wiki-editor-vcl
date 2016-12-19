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
		 */
		void resize(std::size_t height, std::size_t width);

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


	private: // members
    };

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
