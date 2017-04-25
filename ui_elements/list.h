//---------------------------------------------------------------------------
#pragma once

#include "../element.h"
#include "../section.h"

#include "wretched-css/style_sheet.hpp"

// Model / Data
#include "wiki-markup/components/exportable_components/exportable_list.hpp"

// View
#include <Vcl.ComCtrls.hpp> // TRichEdit

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class List : public Element <List, TRichEdit, WikiMarkup::Components::ExportableList>
	{
	public:
		List(Section* parentSection);
		void writeModelToUserInterface() override;

	protected:
		void initializeOptionsFrame() override;
		void initializeStyleOptionsFrame() override;

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign) override;

	private:
		void __fastcall onTextChange(TObject* Sender);
		void __fastcall onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	};
}
//---------------------------------------------------------------------------
