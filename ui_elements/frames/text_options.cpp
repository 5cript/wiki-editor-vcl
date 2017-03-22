//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../text.h"

#include "localization.h"
#include "text_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTextOptionsFrame *TextOptionsFrame;
//---------------------------------------------------------------------------
__fastcall TTextOptionsFrame::TTextOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void TTextOptionsFrame::translate()
{
	if (translated_)
		return;

    // All Objects that have captions:
	for(int i = 0; i < ComponentCount; i++)
	{
		TRANSLATE_OF_TYPE_I(i, this, TButton, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
	}

	translated_ = true;
}
//---------------------------------------------------------------------------
void TTextOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
	owner_ = dynamic_cast <WikiElements::Text*> (owner);
	if (!owner_)
		throw std::invalid_argument("passed owner is not of text element type");
}
//---------------------------------------------------------------------------
void __fastcall TTextOptionsFrame::Button1Click(TObject *Sender)
{
	auto res = MessageBox(
		nullptr,
		::translate("$ReallyWantRemove").c_str(),
		::translate("$LossWarningCaption").c_str(),
		MB_YESNO | MB_ICONWARNING
	);
	if (res == IDYES)
		owner_->remove();
}
//---------------------------------------------------------------------------

