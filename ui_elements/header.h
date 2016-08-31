//---------------------------------------------------------------------------
#pragma once

#include "element.h"

// Model / Data
#include "stub/exportable_header_stub.hpp"

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
		Header(TControl* parent);

	private:
		std::unique_ptr <TPanel> underline_;
	};
}
//---------------------------------------------------------------------------
