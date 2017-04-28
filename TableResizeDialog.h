//---------------------------------------------------------------------------

#ifndef TableResizeDialogH
#define TableResizeDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Samples.Spin.hpp>

#include "ui_elements/table.h"
//---------------------------------------------------------------------------
class TResizeDialog : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TLabel *Label1;
	TLabel *Label2;
	TSpinEdit *TableWidth;
	TSpinEdit *TableHeight;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// Benutzer-Deklarationen
	WikiElements::Table* table_;
public:		// Benutzer-Deklarationen
	void translate();
	void show(WikiElements::Table* table);
	__fastcall TResizeDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResizeDialog *ResizeDialog;
//---------------------------------------------------------------------------
#endif
