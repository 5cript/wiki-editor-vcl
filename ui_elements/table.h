//---------------------------------------------------------------------------
#pragma once

#include "../element.h"
#include "../section.h"

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
		Table(ElementContainer* parent, Section* parentSection);

	protected: // wimu events
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser);

	private: // vcl events
		void __fastcall onDrawCell(TObject *Sender, int ACol, int ARow, TRect const &Rect, TGridDrawState State);
		void __fastcall onSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
		void __fastcall onMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	private: // private methods


	private: // members
    };

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
