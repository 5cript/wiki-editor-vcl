//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LayoutTest.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvEditor"
#pragma link "JvEditorCommon"
#pragma link "JvExControls"
#pragma link "JvExStdCtrls"
#pragma link "JvRichEdit"
#pragma resource "*.dfm"
TTestForm *TestForm;
//---------------------------------------------------------------------------
__fastcall TTestForm::TTestForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::StringGrid1ColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex)
{
	ShowMessage("Move");
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::StringGrid1RowMoved(TObject *Sender, int FromIndex, int ToIndex)

{
	ShowMessage("Move2");
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	ShowMessage("Select");
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::JvRichEdit1DragDrop(TObject *Sender, TObject *Source, int X,
		  int Y)
{
	ShowMessage("Drop");
}
//---------------------------------------------------------------------------

