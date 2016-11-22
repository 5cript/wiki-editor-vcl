//---------------------------------------------------------------------------

#pragma hdrstop

#include "text.h"

#include "style_applicator.h"
#include "frames/text_options.h"
#include "frames/style_options.h"
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	Text::Text(Section* parentSection)
		: Element{parentSection}
		, deleteCounter_{0}
	{
    	auto* parent = parentSection->getLayout()->getControl();

		// setText(data_.data);

		// control_->Font->Name = "Courier";
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
	void Text::styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
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
				readFontStyles <control_type>,
				readBackgroundStyles <control_type>
			}
		);

		control_->Height = (control_->Lines->Count + 1) * (control_->Font->Size + 5);
		parentSection_->causePageRealign();
	}
//---------------------------------------------------------------------------
	void __fastcall Text::onTextChange(TObject* Sender)
	{
		auto previousHeight = control_->Height;
		control_->Height = (control_->Lines->Count + 1) * (control_->Font->Size + 5);

		if (previousHeight != control_->Height)
		{
			parentSection_->causePageRealign();
		}

        data_.data = UTF8String(control_->Text).c_str();
	}
//---------------------------------------------------------------------------
	void __fastcall Text::onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
	{
		if (data_.data.empty() && (Key == vkBack || Key == vkDelete))
		{
			deleteCounter_++;
			//if (deleteCounter_ > 2)
			//	remove();
		}
		else if (!data_.data.empty())
		{
			deleteCounter_ = 0;
		}
		if (Key == vkReturn)
		{
			control_->SelStart = 0;
			control_->Perform(EM_SCROLLCARET, 0, 0);
			control_->SelStart = control_->Text.Length();
        }
	}
//---------------------------------------------------------------------------
	void Text::initializeOptionsFrame()
	{
		optionsFrame_.reset(new TTextOptionsFrame(nullptr));
		static_cast <TTextOptionsFrame*> (&*optionsFrame_)->setOwner(this);
	}
//---------------------------------------------------------------------------
	void Text::initializeStyleOptionsFrame()
	{
		styleOptionsFrame_.reset(new TStyleOptionsFrame(nullptr));
		static_cast <TStyleOptionsFrame*> (&*styleOptionsFrame_)->setOwner(this);
    }
//---------------------------------------------------------------------------
}
#pragma package(smart_init)
