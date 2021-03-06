//---------------------------------------------------------------------------
#pragma once

#include "../element.h"
#include "../section.h"

// Model / Data
#include "wiki-markup/components/exportable_components/exportable_text.hpp"

// View
#include <Vcl.ComCtrls.hpp> // TRichEdit

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class Text : public Element <Text, TRichEdit, WikiMarkup::Components::ExportableText>
	{
	public:
		Text(Section* parentSection);
		void writeModelToUserInterface() override;

	protected:
		void initializeOptionsFrame() override;
		void initializeStyleOptionsFrame() override;

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign) override;

	private:
		void __fastcall onTextChange(TObject* Sender);
		void __fastcall onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

	private:
		unsigned int deleteCounter_;
    };

}
//---------------------------------------------------------------------------
