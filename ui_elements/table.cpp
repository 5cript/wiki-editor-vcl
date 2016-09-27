//---------------------------------------------------------------------------

#pragma hdrstop

#include "table.h"

#include "style_applicator.h"
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	Table::Table(ElementContainer* parent, Section* parentSection)
		: Element{parent, parentSection}
	{

    }
//---------------------------------------------------------------------------
	void Table::styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
	{
    	auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".text"
		;

		readStyles(
			&*control_,
			style,
			hierarchy,
			{
				//readFontStyles <control_type>,
				//readBackgroundStyles <control_type>
			}
		);
    }
//---------------------------------------------------------------------------
	void __fastcall Table::onDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
	{

    }
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
