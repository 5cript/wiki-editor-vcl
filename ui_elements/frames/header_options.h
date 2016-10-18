//---------------------------------------------------------------------------

#ifndef header_optionsH
#define header_optionsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class THeaderOptionsFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TLabel *Label1;
	void __fastcall Label1Click(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall THeaderOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderOptionsFrame *HeaderOptionsFrame;
//---------------------------------------------------------------------------
#endif
