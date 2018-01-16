//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "header_options.h"
#include "localization.h"
#include "common_dialogs.h"
#include "../list.h"

#include "list_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TListOptionsFrame *ListOptionsFrame;
//---------------------------------------------------------------------------
__fastcall TListOptionsFrame::TListOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
	, translated_{false}
	, owner_{nullptr}
{
}
//---------------------------------------------------------------------------
__fastcall TListOptionsFrame::~TListOptionsFrame()
{
	if (selfReference_)
		*selfReference_ = nullptr;
}
//---------------------------------------------------------------------------
void TListOptionsFrame::populate()
{
    //HeaderLayer->ItemIndex = owner_->getLevel() - 2;
}
//---------------------------------------------------------------------------
void TListOptionsFrame::translate()
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
void TListOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
	owner_ = dynamic_cast <WikiElements::List*> (owner);
	if (!owner_)
		throw std::invalid_argument("passed owner is not of header element type");
}
//---------------------------------------------------------------------------
void TListOptionsFrame::setSelfReference(TFrame** selfReference)
{
	selfReference_ = selfReference;
}
//---------------------------------------------------------------------------
void __fastcall TListOptionsFrame::RemoveListClick(TObject *Sender)
{
	if (ElementDeletionWarning() == AbortContinueCase::Continue)
		owner_->remove();
}
//---------------------------------------------------------------------------
