//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "About.h"
//#include "component_export.hpp"

#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "NiceGrid"
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
	, controller_{PageContainer}
{
	controller_.addSection();
	//srand(time(0));
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
void __fastcall TMainEditor::Button1Click(TObject *Sender)
{
	controller_.test();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::About1Click(TObject *Sender)
{
	AboutForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormResize(TObject *Sender)
{
	EditorGrid->Width = Width - 24 - EditorGrid->Left;
	EditorGrid->Height = Height - 64 - EditorGrid->Top;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::PageContainerDragDrop(TObject *Sender, TObject *Source,
          int X, int Y)
{
	ShowMessage(__clang_version__);
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::PageContainerDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept)
{
	if (dynamic_cast <TImage*> (Source))
	{
		Accept = true;
		controller_.renderDropTarget(X, Y);
		Label1->Caption = IntToStr(Y);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormCreate(TObject *Sender)
{
	controller_.initializeViewport();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::ElementEndDrag(TObject *Sender, TObject *Target, int X, int Y)
{
	controller_.endDragDrop();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::ElementStartDrag(TObject *Sender, TDragObject *&DragObject)
{
    controller_.startDragDrop();
}
//---------------------------------------------------------------------------



