//---------------------------------------------------------------------------

#pragma hdrstop

#include "drop_target.h"
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	DropTarget::DropTarget(Section* parentSection)
		: Element{parentSection}
	{
		auto* parent = parentSection->getLayout()->getControl();

		// Style
		control_->ParentBackground = false;
		control_->Color = clLime;
		control_->BorderStyle = bsNone;
		control_->BevelOuter = bvRaised;

		// Positioning and Size
		control_->Height = 10;
		//control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		//control_->Left = leftSectionPadding;
		//control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
	}
//---------------------------------------------------------------------------
	void DropTarget::styleChanged(WretchedCss::StyleSheet const& style)
	{
	}
//---------------------------------------------------------------------------
}
#pragma package(smart_init)
