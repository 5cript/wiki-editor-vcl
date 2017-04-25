//---------------------------------------------------------------------------

#ifndef LayoutTestH
#define LayoutTestH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TTestForm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TGridPanel *GridPanel1;
	TRichEdit *RichEdit1;
	TRichEdit *RichEdit2;
	TGridPanel *GridPanel2;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TGridPanel *GridPanel3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TEdit *Edit7;
	TRichEdit *RichEdit3;
	TStringGrid *StringGrid1;
	void __fastcall StringGrid1ColumnMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall StringGrid1RowMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);







private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TTestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTestForm *TestForm;
//---------------------------------------------------------------------------
#endif
