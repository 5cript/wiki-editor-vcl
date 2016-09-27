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
	class Table : public Element <Table, TDrawGrid, WikiMarkup::Components::ExportableTable>
	{
	public:
		Table(ElementContainer* parent, Section* parentSection);

	protected: // wimu events
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser);

	private: // vcl events
		void __fastcall onDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);

	private:
    };

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
