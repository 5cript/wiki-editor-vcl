//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "component_export.hpp"

#pragma package(smart_init)
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TMainEditor::LoadPage()
{
	ShowMessage("Test");
}
//---------------------------------------------------------------------------


