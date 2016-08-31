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
	TPanel *Line;
	TMenuItem *Help1;
	TMenuItem *About1;
	TScrollBox *PageContainer;
	TRichEdit *TestHeader;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall TestHeaderEnter(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
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
