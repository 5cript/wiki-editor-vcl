//---------------------------------------------------------------------------

#ifndef list_optionsH
#define list_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TListOptionsFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TLabel *Label1;
	TButton *RemoveList;
	void __fastcall RemoveListClick(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::List* owner_;
	TFrame** selfReference_;
public:		// Benutzer-Deklarationen
	void populate();
	void translate();
	void setOwner(WikiElements::BasicElement* owner);
	void setSelfReference(TFrame** selfReference);
	__fastcall TListOptionsFrame(TComponent* Owner);
	__fastcall ~TListOptionsFrame();
};
//---------------------------------------------------------------------------
extern PACKAGE TListOptionsFrame *ListOptionsFrame;
//---------------------------------------------------------------------------
#endif
