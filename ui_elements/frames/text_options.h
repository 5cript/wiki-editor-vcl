//---------------------------------------------------------------------------

#ifndef text_optionsH
#define text_optionsH
//---------------------------------------------------------------------------
#include "frame_interface.h"
#include "../element_fwd.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TTextOptionsFrame : public TFrame
						, public IOptionsFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TLabel *Label1;
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::Text* owner_;
public:		// Benutzer-Deklarationen
	void translate();
	void setOwner(WikiElements::BasicElement* owner);
	__fastcall TTextOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTextOptionsFrame *TextOptionsFrame;
//---------------------------------------------------------------------------
#endif
