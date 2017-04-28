//---------------------------------------------------------------------------

#ifndef table_optionsH
#define table_optionsH
//---------------------------------------------------------------------------
#include "../element_fwd.h"
#include "wiki-markup/components/exportable_components/exportable_table.hpp"
#include "wretched-css/style_sheet.hpp"
#include "../styling/style_container.h"

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
	TLabel *Label2;
	TPopupMenu *ChangeStyleMenu;
	TMenuItem *Change1;
	TMenuItem *ChangeClass1;
	TScrollBox *ScrollBox;
	TLabel *RowAttrLabel;
	TValueListEditor *RowAttributes;
	TLabel *CellAttrLabel;
	TValueListEditor *CellAttributes;
	TValueListEditor *TableAttributes;
	TLabel *AttributeLbl;
	TButton *Button1;
	TCheckBox *HeaderCellChecker;
	TButton *Button2;
	void __fastcall TableAttributesValidate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
          const UnicodeString KeyValue);
	void __fastcall CellAttributesValidate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
          const UnicodeString KeyValue);
	void __fastcall HeaderCellCheckerClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Change1Click(TObject *Sender);
	void __fastcall ChangeClass1Click(TObject *Sender);
	void __fastcall FrameResize(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall RowAttributesValidate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
          const UnicodeString KeyValue);
	void __fastcall RowAttributesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall CellAttributesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall TableAttributesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// Benutzer-Deklarationen
	bool translated_;
	WikiElements::Table* owner_;
	WikiMarkup::Components::TableCell* cell_;
	WikiMarkup::Components::TableRow* row_;
	WretchedCss::StyleSheet style_;
	StyleContainment::Style parsedStyle_;
	TFrame** selfReference_;
    TValueListEditor* clickedEditor_;
public:		// Benutzer-Deklarationen
	void translate();
	void populate();
	void setOwner(WikiElements::BasicElement* owner);
	void setSelfReference(TFrame** selfReference);
	void setCell(WikiMarkup::Components::TableCell* cell);
	void setRow(WikiMarkup::Components::TableRow* row);
	void setStyleContainer(StyleContainment::Style const& style);

	__fastcall TTableOptionsFrame(TComponent* Owner);
	__fastcall ~TTableOptionsFrame();
};
//---------------------------------------------------------------------------
extern PACKAGE TTableOptionsFrame *TableOptionsFrame;
//---------------------------------------------------------------------------
#endif
