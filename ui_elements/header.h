//---------------------------------------------------------------------------
#pragma once

#include "element.h"
#include "section.h"

// Model / Data
// #include "stub/exportable_header_stub.hpp"
#include "wiki-markup/components/exportable_components/exportable_header.hpp"

// View
#include <Vcl.ComCtrls.hpp> // TRichEdit

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class Header : public Element <Header, TEdit, WikiMarkup::Components::ExportableHeader>
	{
	public:
		Header(ElementContainer* parent, Section* parentSection);

		void setLevel(int level);
		int getLevel() const;

		void setText(std::string const& text);
		std::string const& getText() const;

        BoundingBox getBoundingBox() const override;

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser);

	private:
		void __fastcall onTextChange(TObject* Sender);

	private:
		std::unique_ptr <TPanel> underline_;
		Section* parentSection_;
	};
}
//---------------------------------------------------------------------------
