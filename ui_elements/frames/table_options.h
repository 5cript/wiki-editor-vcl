//---------------------------------------------------------------------------

#ifndef table_optionsH
#define table_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
//---------------------------------------------------------------------------
class TTableOptionsFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TValueListEditor *TableAttributes;
	TLabel *AttributeLbl;
	TCheckBox *HeaderCellChecker;
	void __fastcall TableAttributesValidate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
          const UnicodeString KeyValue);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::Table* owner_;
public:		// Benutzer-Deklarationen
	void translate();
	void populate();
	void setOwner(WikiElements::BasicElement* owner);

	__fastcall TTableOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTableOptionsFrame *TableOptionsFrame;
//---------------------------------------------------------------------------
#endif
