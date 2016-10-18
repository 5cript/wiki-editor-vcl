//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "header_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THeaderOptionsFrame *HeaderOptionsFrame;
//---------------------------------------------------------------------------
__fastcall THeaderOptionsFrame::THeaderOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THeaderOptionsFrame::Label1Click(TObject *Sender)
{
    ShowMessage("Hello");
}
//---------------------------------------------------------------------------
