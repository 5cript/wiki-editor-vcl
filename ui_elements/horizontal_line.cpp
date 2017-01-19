//---------------------------------------------------------------------------

#pragma hdrstop

#include "horizontal_line.h"

#include "style_applicator.h"

#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
namespace WikiElements
{
	HorizontalLine::HorizontalLine(Section* parentSection)
		: Element{parentSection}
	{
    	auto* parent = parentSection->getLayout()->getControl();

		// Style
		control_->ParentBackground = false;
		control_->Color = clGray;
		control_->BorderStyle = bsNone;
		control_->BevelOuter = bvNone;

		// Positioning and Size
		//control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		//control_->Left = leftSectionPadding;
		control_->Height = 1;
		//control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
	}
//---------------------------------------------------------------------------
	void HorizontalLine::styleChanged(WretchedCss::StyleSheet const& style)
	{
		auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".hline"
		;

		readStyles(
			&*control_,
			style,
			hierarchy,
			{
				readBackgroundStyles <control_type>,
                readSizes <control_type>
			}
		);
	}
//---------------------------------------------------------------------------
}
#pragma package(smart_init)
