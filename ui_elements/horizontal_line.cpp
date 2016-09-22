//---------------------------------------------------------------------------

#pragma hdrstop

#include "horizontal_line.h"

#include "style_applicator.h"

#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
namespace WikiElements
{
	HorizontalLine::HorizontalLine(ElementContainer* parent, Section* parentSection)
		: Element{parent, parentSection}
	{
		control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		control_->Height = 1;
		control_->Left = leftSectionPadding;
		control_->ParentBackground = false;
		control_->Color = clGray;
        control_->Font->Color = clRed;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		control_->Parent = parent;
		control_->BorderStyle = bsNone;
		control_->BevelOuter = bvNone;
		control_->Repaint();
	}
//---------------------------------------------------------------------------
	void HorizontalLine::styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
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
