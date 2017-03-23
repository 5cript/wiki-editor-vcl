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
		void initializeOptionsFrame() override;
		void initializeStyleOptionsFrame() override;

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style) override;

	private: // VCL Events
    };

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
