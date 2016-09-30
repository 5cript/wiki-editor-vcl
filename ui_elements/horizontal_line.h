//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "../element.h"
#include "../section.h"

// Model / Data
#include "wiki-markup/components/exportable_components/exportable_horizontal_line.hpp"

// View
#include <Vcl.ComCtrls.hpp> // TRichEdit

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class HorizontalLine : public Element <HorizontalLine, TPanel, WikiMarkup::Components::ExportableHorizontalLine>
	{
	public:
		HorizontalLine(Section* parentSection);

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser);

	private:
		//void __fastcall onTextChange(TObject* Sender);
		//void __fastcall onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    };

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
