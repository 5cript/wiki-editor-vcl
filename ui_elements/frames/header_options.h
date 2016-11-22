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
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall HeaderLayerChange(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::Header* owner_;
public:		// Benutzer-Deklarationen
	void translate();
	void setOwner(WikiElements::BasicElement* owner);
	__fastcall THeaderOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderOptionsFrame *HeaderOptionsFrame;
//---------------------------------------------------------------------------
#endif
