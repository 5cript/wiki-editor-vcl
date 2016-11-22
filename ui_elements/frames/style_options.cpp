//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "style_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStyleOptionsFrame *StyleOptionsFrame;
//---------------------------------------------------------------------------
__fastcall TStyleOptionsFrame::TStyleOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void TStyleOptionsFrame::translate()
{
	if (translated_)
		return;

	translated_ = true;
}
//---------------------------------------------------------------------------
void TStyleOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
    owner_ = owner;
}
//---------------------------------------------------------------------------
