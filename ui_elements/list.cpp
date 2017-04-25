//---------------------------------------------------------------------------

#pragma hdrstop

#include "list.h"

#include "style_applicator.h"
#include "frames/text_options.h"
#include "frames/style_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	List::List(Section* parentSection)
		: Element{parentSection}
	{
		auto* parent = parentSection->getLayout()->getControl();

		control_->Left = leftSectionPadding;
		control_->Color = clWhite;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		control_->Height = (control_->Lines->Count + 1) * (control_->Font->Size + 5);
		control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		control_->BorderStyle = bsNone;
		control_->OnChange = this->onTextChange;
		control_->OnKeyUp = this->onKeyUp;
		control_->ScrollBars = ssNone;
        control_->WantTabs = true;
	}
//---------------------------------------------------------------------------
	void List::writeModelToUserInterface()
	{

	}
//---------------------------------------------------------------------------
	void List::initializeOptionsFrame()
	{

	}
//---------------------------------------------------------------------------
	void List::initializeStyleOptionsFrame()
	{

	}
//---------------------------------------------------------------------------
	void List::styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign)
	{
        parsedStyle_ = style;

		auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".list"
		;

		readStyles(
			&*control_,
			style,
			hierarchy,
			{
				readFontStyles <control_type>,
				readBackgroundStyles <control_type>
			}
		);

		control_->Height = (control_->Lines->Count + 1) * (control_->Font->Size + 5);

		if (!delayRealign)
			parentSection_->causePageRealign();
	}
//---------------------------------------------------------------------------
	void __fastcall List::onTextChange(TObject* Sender)
	{

	}
//---------------------------------------------------------------------------
	void __fastcall List::onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
	{

    }
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------