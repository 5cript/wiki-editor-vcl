//---------------------------------------------------------------------------

#ifndef LogH
#define LogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TLogWindow : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TRichEdit *Log;
	TMainMenu *LogWindowMenu;
	TMenuItem *File1;
	TMenuItem *SaveLog1;
	TMenuItem *ClearLog1;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall SaveLog1Click(TObject *Sender);
	void __fastcall ClearLog1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool translated_;
public:		// Benutzer-Deklarationen
	void translate();
	__fastcall TLogWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLogWindow *LogWindow;
//---------------------------------------------------------------------------
#endif
