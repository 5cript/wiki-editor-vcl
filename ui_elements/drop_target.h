//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "../element.h"
#include "../section.h"

// Model / Data
// #include "wiki-markup/components/exportable_components/exportable_horizontal_line.hpp"

// View
#include <Vcl.ComCtrls.hpp>

// STL
#include <memory>
//---------------------------------------------------------------------------
namespace WikiElements
{
	class DropTarget : public Element <DropTarget, TPanel, int>
	{
	public:
		DropTarget(Section* parentSection);

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser) override;
    };
}
//---------------------------------------------------------------------------
