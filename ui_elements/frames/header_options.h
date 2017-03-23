//---------------------------------------------------------------------------

#ifndef header_optionsH
#define header_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class THeaderOptionsFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TComboBox *HeaderLayer;
	TLabel *Label1;
	TButton *Button1;
	TLabel *Label2;
	void __fastcall HeaderLayerChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::Header* owner_;
	TFrame** selfReference_;
public:		// Benutzer-Deklarationen
	void populate();
	void translate();
	void setOwner(WikiElements::BasicElement* owner);
	void setSelfReference(TFrame** selfReference);
	__fastcall THeaderOptionsFrame(TComponent* Owner);
	__fastcall ~THeaderOptionsFrame();
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderOptionsFrame *HeaderOptionsFrame;
//---------------------------------------------------------------------------
#endif
