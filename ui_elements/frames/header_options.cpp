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


	TRANSLATE_OF_TYPE(this, TLabel, Caption);

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

