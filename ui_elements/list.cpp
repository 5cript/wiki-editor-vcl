//---------------------------------------------------------------------------

#pragma hdrstop

#include "list.h"

#include "style_applicator.h"
#include "frames/list_options.h"
#include "frames/style_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace WikiElements
{
//###########################################################################
	void writeToUi(TRichEdit* edit, PrimalList* primal)
	{
		if (!primal) return;
	}
//---------------------------------------------------------------------------
	void writeToUi(TRichEdit* edit, ListTextLine* textLine)
	{
		if (!textLine) return;

        control_->Text += textLine->data;
    }
//---------------------------------------------------------------------------
	void decideWrite(TRichEdit* edit, ListElement* element)
	{
		if (element)
		{
			writeToUi(edit, dynamic_cast <PrimalList*> (element));
			writeToUi(edit, dynamic_cast <ListTextLine*> (element));
        }
    }
//###########################################################################
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
		data_.list
	}
//---------------------------------------------------------------------------
	void List::initializeOptionsFrame()
	{
    	optionsFrame_.reset(new TListOptionsFrame(nullptr));
		static_cast <TListOptionsFrame*> (&*optionsFrame_)->setOwner(this);
	}
//---------------------------------------------------------------------------
	void List::initializeStyleOptionsFrame()
	{
        styleOptionsFrame_.reset(new TStyleOptionsFrame(nullptr));
		static_cast <TStyleOptionsFrame*> (&*styleOptionsFrame_)->setOwner(this);
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
    	auto previousHeight = control_->Height;
		control_->Height = (control_->Lines->Count + 1) * (control_->Font->Size + 5);

		if (previousHeight != control_->Height)
		{
			parentSection_->causePageRealign();
		}

        parentSection_->makeDirty();
        //data_.data = UTF8String(control_->Text).c_str();
	}
//---------------------------------------------------------------------------
	void __fastcall List::onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
	{
		if (Key == vkReturn)
		{
        	auto selBackup = control_->SelStart;

			control_->SelStart = 0;
			control_->Perform(EM_SCROLLCARET, 0, 0);
			//control_->SelStart = control_->Text.Length();
			control_->SelStart = selBackup;
        }
    }
//###########################################################################
}
//---------------------------------------------------------------------------