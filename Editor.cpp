//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "About.h"
//#include "component_export.hpp"

#pragma package(smart_init)
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
	, controller_{PageContainer}
{
	controller_.addSection();
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
void __fastcall TMainEditor::TestHeaderEnter(TObject *Sender)
{
    // Enter
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::Button1Click(TObject *Sender)
{
	/*TestEdit->OnClick = [](TObject* Sender) {
		ShowMessage("Bam");
	};
	*/
	controller_.test();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::About1Click(TObject *Sender)
{
	AboutForm->ShowModal();
}
//---------------------------------------------------------------------------


