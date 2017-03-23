//---------------------------------------------------------------------------

#ifndef horizontal_line_optionsH
#define horizontal_line_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class THorizontalLineOptionsFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TButton *Button1;
	TLabel *Label1;
	void __fastcall Button1Click(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::HorizontalLine* owner_;
	TFrame** selfReference_;
public:		// Benutzer-Deklarationen
	void translate();
	void populate();
	void setOwner(WikiElements::BasicElement* owner);
	void setSelfReference(TFrame** selfReference);
	__fastcall THorizontalLineOptionsFrame(TComponent* Owner);
	__fastcall ~THorizontalLineOptionsFrame();
};
//---------------------------------------------------------------------------
extern PACKAGE THorizontalLineOptionsFrame *HorizontalLineOptionsFrame;
//---------------------------------------------------------------------------
#endif
