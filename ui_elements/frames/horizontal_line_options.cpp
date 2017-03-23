//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "horizontal_line_options.h"
#include "localization.h"
#include "common_dialogs.h"
#include "../horizontal_line.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THorizontalLineOptionsFrame *HorizontalLineOptionsFrame;
//---------------------------------------------------------------------------
__fastcall THorizontalLineOptionsFrame::THorizontalLineOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall THorizontalLineOptionsFrame::~THorizontalLineOptionsFrame()
{
	*selfReference_ = nullptr;
}
//---------------------------------------------------------------------------
void __fastcall THorizontalLineOptionsFrame::Button1Click(TObject *Sender)
{
	if (ElementDeletionWarning() == AbortContinueCase::Continue)
		owner_->remove();
}
//---------------------------------------------------------------------------
void THorizontalLineOptionsFrame::translate()
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
void THorizontalLineOptionsFrame::populate()
{

}
//---------------------------------------------------------------------------
void THorizontalLineOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
	owner_ = dynamic_cast <WikiElements::HorizontalLine*> (owner);
	if (!owner_)
		throw std::invalid_argument("passed owner is not of horizontal line element type");
}
//---------------------------------------------------------------------------
void THorizontalLineOptionsFrame::setSelfReference(TFrame** selfReference)
{
	selfReference_ = selfReference;
}
//---------------------------------------------------------------------------
