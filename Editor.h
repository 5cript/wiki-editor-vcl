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
#include "VirtualTrees.hpp"
#include "NiceGrid.hpp"
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.jpeg.hpp>
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
	TButton *Button1;
	TGridPanel *EditorGrid;
	TScrollBox *PageContainer;
	TPanel *PropertyView;
	TCategoryPanelGroup *CategoryPanelGroup1;
	TCategoryPanel *CategoryPanel1;
	TImage *Penguins;
	TLabel *Label1;
	TButton *Button2;
	TButton *Button3;
	TGridPanel *Viewport;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ElementEndDrag(TObject *Sender, TObject *Target, int X, int Y);
	void __fastcall ElementStartDrag(TObject *Sender, TDragObject *&DragObject);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall ViewportDragOver(TObject *Sender, TObject *Source, int X, int Y,
          TDragState State, bool &Accept);


private:	// Benutzer-Deklarationen
	void LoadPage();

	PageController controller_;
public:		// Benutzer-Deklarationen
	__fastcall TMainEditor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainEditor *MainEditor;
//---------------------------------------------------------------------------
#endif
