//---------------------------------------------------------------------------

#ifndef EditorH
#define EditorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Ribbon.hpp>
#include <Vcl.RibbonLunaStyleActnCtrls.hpp>
//---------------------------------------------------------------------------
#include "controller.h"
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TMainEditor : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TMainMenu *Menu;
	TMenuItem *File1;
	TMenuItem *OpenArticle1;
	TMenuItem *SaveArticle1;
	TMenuItem *N1;
	TMenuItem *Exit1;
	TMenuItem *Autosave1;
	TMenuItem *SaveArticleAs1;
	TButton *Button1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TScrollBox *PageContainer;
	TEdit *Edit1;
	TRichEdit *RichEdit1;
	TPanel *Panel1;
	TDrawGrid *DrawGrid1;
	TStringGrid *StringGrid1;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall TestHeaderEnter(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall DrawGrid1GetEditMask(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
	void __fastcall DrawGrid1GetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
	void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);


private:	// Benutzer-Deklarationen
	void LoadPage();

	PageController controller_;
public:		// Benutzer-Deklarationen
	__fastcall TMainEditor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainEditor *MainEditor;
//---------------------------------------------------------------------------
#endif
