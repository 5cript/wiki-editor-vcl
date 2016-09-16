//---------------------------------------------------------------------------
#pragma once

#include "element.h"

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
	class Header : public Element <Header, TRichEdit, WikiMarkup::Components::ExportableHeader>
	{
	public:
		Header(ElementContainer* parent);

	protected:
        void styleChanged(WretchedCss::StyleSheet const& style);

	private:
		std::unique_ptr <TPanel> underline_;
	};
}
//---------------------------------------------------------------------------
