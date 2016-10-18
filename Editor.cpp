//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "About.h"
#include "LayoutTest.h"
#include "localization.h"
#include "debug.h"
#include "constants.h"
//#include "component_export.hpp"

#include <functional>

#pragma package(smart_init)
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
	, controller_{Viewport}
{
	//srand(time(0));
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TMainEditor::LoadPage()
{
	ShowMessage("Test");
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::About1Click(TObject *Sender)
{
	AboutForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormResize(TObject *Sender)
{
	EditorGrid->Width = Width - 24 - EditorGrid->Left;
	EditorGrid->Height = Height - 64 - EditorGrid->Top;
	Viewport->Width =
		PageContainer->Width -
		!!(PageContainer->BevelOuter != bvNone) * PageContainer->BevelWidth * 2 -
		!!(Viewport->BevelOuter != bvNone) * Viewport->BevelWidth * 2 -
		18 /* scrollbar height */;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormCreate(TObject *Sender)
{
    // Controller
	controller_.initializeViewport();
	controller_.addSection();

	// Logging
	SetLog(Log);

	// Cursor
	Screen->Cursors[WikiEditorConstants::crosshairCursor] = LoadCursor(HInstance, L"Crosshair");

	// Translation
	Translator::getInstance().loadLanguageFile("locale.json");
	TranslateWindow();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::ElementEndDrag(TObject *Sender, TObject *Target, int X, int Y)
{
	auto dropTarget = controller_.endDragDrop();
	controller_.addHeader(dropTarget);
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::ElementStartDrag(TObject *Sender, TDragObject *&DragObject)
{
    controller_.startDragDrop();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::ViewportDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
	if (dynamic_cast <TImage*> (Source))
	{
		Accept = true;
		auto* section = controller_.getSectionUnder(X, Y);
		//controller_.renderDropTarget(X, Y);
		//Label1->Caption = IntToStr(Y) + " " + BoolToStr(section != nullptr, true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::AddTestElements1Click(TObject *Sender)
{
	controller_.test();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::estFormShowModal1Click(TObject *Sender)
{
	TestForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::controlleraddSection1Click(TObject *Sender)
{
	controller_.addSection();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::StartComponentSelectClick(TObject *Sender)
{
	if (!controller_.isInSelectionMode())
	{
		Screen->Cursor = static_cast <TCursor> (WikiEditorConstants::crosshairCursor);
		controller_.startSelectionMode([this](WikiElements::BasicElement* element){
			if (element == nullptr)
			{
			}
			Screen->Cursor = crDefault;
		});
	}
	else
	{
		controller_.stopSelectionMode();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::initLocals1Click(TObject *Sender)
{
	//
	Translator::getInstance().saveLanguageFile("locale.json");
}
//---------------------------------------------------------------------------
void TMainEditor::TranslateWindow()
{
	auto translate = [this](String str) -> String {
		auto& translator = Translator::getInstance();
		str = StringReplace(str, "&", "", TReplaceFlags{} << rfReplaceAll << rfIgnoreCase);
		return UTF8ToString(translator.translate(AnsiString(str).c_str()).c_str());
	};

	// Menu
	std::function <void(TMenuItem*)> translateMenuItem;
	translateMenuItem = [this, &translateMenuItem, &translate](TMenuItem* item){
		for (int i = 0; i < item->Count; ++i)
		{
			item->operator[](i)->Caption = translate(item->operator[](i)->Caption);
			translateMenuItem(item->operator[](i));
        }
	};
	translateMenuItem(Menu->Items);

	// All Objects that have captions:
	for(int i = 0; i < ComponentCount; i++)
	{
		auto* control = dynamic_cast <TBitBtn*> (Components[i]);
		if (!control)
			continue;

		if (control->Caption.SubString(0, 1) == "$")
		{
			control->Caption = translate(control->Caption);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainEditor::AppEventsMessage(tagMSG &Msg, bool &Handled)
{
	switch (Msg.message)
	{
		case (WM_KEYUP):
		{
			if (Msg.wParam == vkEscape && controller_.isInSelectionMode())
			{
				controller_.stopSelectionMode();
			}
		}
    }
}
//---------------------------------------------------------------------------

