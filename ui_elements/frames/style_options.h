//---------------------------------------------------------------------------

#ifndef style_optionsH
#define style_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TStyleOptionsFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *FontSettings;
	TSpinEdit *SpinEdit1;
	TLabel *Label1;
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::BasicElement* owner_;
public:		// Benutzer-Deklarationen
	void translate();
	void setOwner(WikiElements::BasicElement* owner);
	__fastcall TStyleOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStyleOptionsFrame *StyleOptionsFrame;
//---------------------------------------------------------------------------
#endif
