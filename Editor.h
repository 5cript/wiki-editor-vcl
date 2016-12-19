//---------------------------------------------------------------------------

#ifndef EditorH
#define EditorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Ribbon.hpp>
#include <Vcl.RibbonLunaStyleActnCtrls.hpp>
//---------------------------------------------------------------------------
#include "controller.h"
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TMainEditor : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TMainMenu *Menu;
	TMenuItem *File1;
	TMenuItem *OpenArticle1;
	TMenuItem *SaveArticle1;
	TMenuItem *N1;
	TMenuItem *Exit1;
	TMenuItem *Autosave1;
	TMenuItem *SaveArticleAs1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TCategoryPanelGroup *WikiElementCategoryGroup;
	TCategoryPanel *CategoryPanel1;
	TMenuItem *Debug1;
	TMenuItem *AddTestElements1;
	TMenuItem *estFormShowModal1;
	TMenuItem *controlleraddSection1;
	TMenuItem *loadCursor1;
	TMenuItem *initLocals1;
	TApplicationEvents *AppEvents;
	TPanel *Panel1;
	TScrollBox *PageContainer;
	TGridPanel *Viewport;
	TPanel *PropertyControlPane;
	TRichEdit *Log;
	TBitBtn *StartComponentSelect;
	TTabControl *PropertyTabs;
	TSplitter *Splitter1;
	TImage *Penguins;
	TPanel *ElementSpecificOptions;
	TPanel *StyleOptions;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ElementEndDrag(TObject *Sender, TObject *Target, int X, int Y);
	void __fastcall ElementStartDrag(TObject *Sender, TDragObject *&DragObject);
	void __fastcall ViewportDragOver(TObject *Sender, TObject *Source, int X, int Y,
          TDragState State, bool &Accept);
	void __fastcall AddTestElements1Click(TObject *Sender);
	void __fastcall estFormShowModal1Click(TObject *Sender);
	void __fastcall controlleraddSection1Click(TObject *Sender);
	void __fastcall StartComponentSelectClick(TObject *Sender);
	void __fastcall initLocals1Click(TObject *Sender);
	void __fastcall AppEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall PropertyControlPaneResize(TObject *Sender);
	void __fastcall PageContainerResize(TObject *Sender);
	void __fastcall PropertyTabsChanging(TObject *Sender, bool &AllowChange);


private:	// Benutzer-Deklarationen
	void LoadPage();
	void TranslateWindow();
	void __fastcall SelectCallback(WikiElements::BasicElement* element, bool autoSelect = false);

	PageController controller_;
    TFrame* lastFrame_;
public:		// Benutzer-Deklarationen
	__fastcall TMainEditor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainEditor *MainEditor;
//---------------------------------------------------------------------------
#endif
