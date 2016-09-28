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
	class Spacer : public Element <Spacer, TPanel, int>
	{
	public:
		Spacer(ElementContainer* parent, Section* parentSection);

	protected:
		void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser);
    };

}
//---------------------------------------------------------------------------
