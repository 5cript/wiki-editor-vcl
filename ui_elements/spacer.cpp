//---------------------------------------------------------------------------

#pragma hdrstop

#include "spacer.h"
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	Spacer::Spacer(ElementContainer* parent, Section* parentSection)
		: Element{parent, parentSection}
	{

	}
//---------------------------------------------------------------------------
	void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
	{

	}
//---------------------------------------------------------------------------
}
#pragma package(smart_init)
