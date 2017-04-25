//---------------------------------------------------------------------------

#ifndef table_optionsH
#define table_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"
#include "wiki-markup/components/exportable_components/exportable_table.hpp"
#include "wretched-css/style_sheet.hpp"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TTableOptionsFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
	TValueListEditor *TableAttributes;
	TLabel *AttributeLbl;
	TCheckBox *HeaderCellChecker;
	TLabel *Label2;
	TLabel *Label1;
	TValueListEditor *CellAttributes;
	TLabel *Label3;
	TValueListEditor *RowAttributes;
	TButton *Button1;
	TPopupMenu *ChangeStyleMenu;
	TMenuItem *Change1;
	TMenuItem *ChangeClass1;
	void __fastcall TableAttributesValidate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
          const UnicodeString KeyValue);
	void __fastcall CellAttributesValidate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
          const UnicodeString KeyValue);
	void __fastcall HeaderCellCheckerClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Change1Click(TObject *Sender);
	void __fastcall ChangeClass1Click(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::Table* owner_;
	WikiMarkup::Components::TableCell* cell_;
	WretchedCss::StyleSheet style_;
	TFrame** selfReference_;
public:		// Benutzer-Deklarationen
	void translate();
	void populate();
	void setOwner(WikiElements::BasicElement* owner);
	void setSelfReference(TFrame** selfReference);
	void setCell(WikiMarkup::Components::TableCell* cell);

	__fastcall TTableOptionsFrame(TComponent* Owner);
	__fastcall ~TTableOptionsFrame();
};
//---------------------------------------------------------------------------
extern PACKAGE TTableOptionsFrame *TableOptionsFrame;
//---------------------------------------------------------------------------
#endif
