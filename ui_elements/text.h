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
		Text(ElementContainer* parent, Section* parentSection);

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser);

	private:
		void __fastcall onTextChange(TObject* Sender);
		void __fastcall onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

	private:
		unsigned int deleteCounter_;
    };

}
//---------------------------------------------------------------------------
