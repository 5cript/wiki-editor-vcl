//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "header_options.h"
#include "localization.h"
#include "../header.h"

#include <stdexcept>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THeaderOptionsFrame *HeaderOptionsFrame;
//---------------------------------------------------------------------------
__fastcall THeaderOptionsFrame::THeaderOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
	, translated_{false}
    , owner_{nullptr}
{
}
//---------------------------------------------------------------------------
void THeaderOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
	owner_ = dynamic_cast <WikiElements::Header*> (owner);
	if (!owner_)
		throw std::invalid_argument("passed owner is not of header element type");
}
//---------------------------------------------------------------------------
void __fastcall THeaderOptionsFrame::Label1Click(TObject *Sender)
{
    ShowMessage("Hello");
}
//---------------------------------------------------------------------------
void THeaderOptionsFrame::populate()
{
    HeaderLayer->ItemIndex = owner_->getLevel() - 2;
}
//---------------------------------------------------------------------------
void THeaderOptionsFrame::translate()
{
	if (translated_)
		return;

    // All Objects that have captions:
	for(int i = 0; i < ComponentCount; i++)
	{
		TRANSLATE_OF_TYPE_I(i, this, TButton, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
	}

    translateStringList(HeaderLayer->Items);

	translated_ = true;
}
//---------------------------------------------------------------------------
void __fastcall THeaderOptionsFrame::HeaderLayerChange(TObject *Sender)
{
	// no owner was assigned.
	if (owner_ == nullptr)
		return;
	else
    	owner_->setLevel(HeaderLayer->ItemIndex + 2);
}
//---------------------------------------------------------------------------
void __fastcall THeaderOptionsFrame::Button1Click(TObject *Sender)
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

