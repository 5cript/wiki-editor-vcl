//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "About.h"
#include "LayoutTest.h"
//#include "component_export.hpp"

#pragma package(smart_init)
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
	, controller_{Viewport}
{
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
	Viewport->Width =
		PageContainer->Width -
		!!(PageContainer->BevelOuter != bvNone) * PageContainer->BevelWidth * 2 -
		!!(Viewport->BevelOuter != bvNone) * Viewport->BevelWidth * 2 -
		18 /* scrollbar height */;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormCreate(TObject *Sender)
{
	controller_.initializeViewport();
	controller_.addSection();
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
void __fastcall TMainEditor::Button2Click(TObject *Sender)
{
	TestForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::Button3Click(TObject *Sender)
{
	controller_.addSection();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::ViewportDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
	if (dynamic_cast <TImage*> (Source))
	{
		Accept = true;
		auto* section = controller_.getSectionUnder(X, Y);
		//controller_.renderDropTarget(X, Y);
		Label1->Caption = IntToStr(Y) + " " + BoolToStr(section != nullptr, true);
	}
}
//---------------------------------------------------------------------------

