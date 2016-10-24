//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../text.h"

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
void TTextOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
	owner_ = dynamic_cast <WikiElements::Text*> (owner);
	if (!owner_)
		throw std::invalid_argument("passed owner is not of header element type");
}
//---------------------------------------------------------------------------
