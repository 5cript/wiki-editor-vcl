//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "About.h"
#include "LayoutTest.h"
#include "BackupSettings.h"

#include "localization.h"
#include "debug.h"
#include "constants.h"
#include "frame_interface.h"
#include "query_delphi_interface.hpp"
#include "resources.h"
#include "common_dialogs.h"

#include <functional>

#pragma package(smart_init)
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
	, controller_{Viewport}
	, persistence_{&controller_}
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
	/*
	EditorGrid->Width = Width - 24 - EditorGrid->Left;
	EditorGrid->Height = Height - 64 - EditorGrid->Top;
	*/
	Viewport->Width =
		PageContainer->Width -
		!!(PageContainer->BevelOuter != bvNone) * PageContainer->BevelWidth * 2 -
		!!(Viewport->BevelOuter != bvNone) * Viewport->BevelWidth * 2 -
		18 /* scrollbar height */;

    PropertyTabs->Top = StartComponentSelect->Top + StartComponentSelect->Height + 8;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormCreate(TObject *Sender)
{
	try
	{
		// Settings
		setupSettings();
		settings_ = loadSettings();

		// Fix Ui Alignment
		PageContainerResize(this);
		PropertyControlPaneResize(this);

		// Controller
		controller_.setStyle();
		controller_.initializeViewport();

		// Persistence
		PersistenceControl::setupBackupStructure();
		persistence_.setFile("unsaved");
		persistence_.setAutoBackupInterval(settings_.backupOptions.intervalSec);
		persistence_.setMaxBackups(settings_.backupOptions.maxBackups);

		// Auto-Select
		controller_.setAutoSelectEnabled(true);
		controller_.startSelectionMode([this](WikiElements::BasicElement* element){
			SelectCallback(element);
		});

		// Logging
		SetLog(Log);

		// Cursor
		Screen->Cursors[WikiEditorConstants::crosshairCursor] = LoadCursor(HInstance, L"Crosshair");

		// Translation
		//if (!FileExists(L"locale.json"))
		SaveResourceToFile(L"locale", L"locale.json");

		Translator::getInstance().loadLanguageFile("locale.json");
		TranslateWindow();

		// Fresh Article
        NewArticle1Click(nullptr);
	}
	catch (std::exception const& exc)
	{
		DisplayException(exc, EXCEPTION_META);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::HeaderEndDrag(TObject *Sender, TObject *Target, int X, int Y)
{
	try
	{
		auto dropTarget = controller_.endDragDrop();
		controller_.addElement <WikiElements::Header> (dropTarget);
	}
    catch (std::exception const& exc)
	{
		DisplayException(exc, EXCEPTION_META);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::GenericStartDrag(TObject *Sender, TDragObject *&DragObject)
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
void __fastcall TMainEditor::SelectCallback(WikiElements::BasicElement* element, bool autoSelect)
{
	if (element != nullptr)
	{
		if (lastFrame_)
		{
			lastFrame_->Hide();
			lastFrame_->Parent = nullptr;
		}
		auto* frame = element->getOptionsFrame();
		if (frame)
		{
			try
			{
				OptionsFrameAdapter{frame}.translate().populate().setSelfReference(&lastFrame_);
				frame->Parent = ElementSpecificOptions;
				frame->Show();
			}
			catch (std::exception const& exc)
			{
				DisplayException(exc, EXCEPTION_META);
			}
		}
		lastFrame_ = frame;
	}
	if (!autoSelect)
		Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::StartComponentSelectClick(TObject *Sender)
{
	if (!controller_.isInSelectionMode())
	{
		try
		{
			Screen->Cursor = static_cast <TCursor> (WikiEditorConstants::crosshairCursor);
			controller_.startSelectionMode([this](WikiElements::BasicElement* element){
				SelectCallback(element);
			});
		}
		catch (std::exception const& exc)
		{
			DisplayException(exc, EXCEPTION_META);
		}
	}
	else
	{
		controller_.stopSelectionMode();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::initLocals1Click(TObject *Sender)
{
	Translator::getInstance().saveLanguageFile("locale.json");
}
//---------------------------------------------------------------------------
void TMainEditor::TranslateWindow()
{
	// Menu
	std::function <void(TMenuItem*)> translateMenuItem;
	translateMenuItem = [this, &translateMenuItem](TMenuItem* item){
		for (int i = 0; i < item->Count; ++i)
		{
			item->operator[](i)->Caption = translate(item->operator[](i)->Caption);
			translateMenuItem(item->operator[](i));
        }
	};
	translateMenuItem(Menu->Items);

	for (int i = 0; i != PropertyTabs->Tabs->Count; ++i)
	{
		PropertyTabs->Tabs->Strings[i] = ::translate(PropertyTabs->Tabs->Strings[i]);
    }

	// All Objects that have captions:
	for(int i = 0; i < ComponentCount; i++)
	{
		TRANSLATE_OF_TYPE_I(i, this, TBitBtn, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TCategoryPanel, Caption);
	}

	TRANSLATE_SPECIFIC(CategoryPanel1, Caption);
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::AppEventsMessage(tagMSG &Msg, bool &Handled)
{
	switch (Msg.message)
	{
		case (WM_KEYUP):
			if (Msg.wParam == vkEscape && controller_.isInSelectionMode())
				controller_.stopSelectionMode();
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::PropertyControlPaneResize(TObject *Sender)
{
	PropertyTabs->Width = PropertyControlPane->Width - PropertyTabs->Left * 2;
	Log->Width = PropertyControlPane->Width - Log->Left * 2;
	StartComponentSelect->Width = PropertyControlPane->Width - StartComponentSelect->Left * 2;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::PageContainerResize(TObject *Sender)
{
	Viewport->Width = PageContainer->Width - 4;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::PropertyTabsChanging(TObject *Sender, bool &AllowChange)

{
	if (PropertyTabs->TabIndex == 1)
	{
		ElementSpecificOptions->Show();
		StyleOptions->Hide();
	}
	else
	{
		ElementSpecificOptions->Hide();
		StyleOptions->Show();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::SaveArticle1Click(TObject *Sender)
{
	//...
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::FormClose(TObject *Sender, TCloseAction &Action)
{
	persistence_.stopAutoBackup();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::AllSettings2Click(TObject *Sender)
{
	// ...
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::WikiElementCategoryGroupMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (Button == mbMiddle && Shift.Contains(ssCtrl))
		Debug1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::CaptionSettings1Click(TObject *Sender)
{
	try
	{
		BackupSettingsDialog->LoadOptions(settings_.backupOptions);
		BackupSettingsDialog->ShowModal();
		if (BackupSettingsDialog->Accepted())
		{
			settings_.backupOptions = BackupSettingsDialog->GetOptions();
			saveSettings(settings_);
			persistence_.stopAutoBackup();
			persistence_.setAutoBackupInterval(settings_.backupOptions.intervalSec);
			persistence_.setMaxBackups(settings_.backupOptions.maxBackups);
			persistence_.startAutoBackup();
		}
	}
	catch (std::exception const& exc)
	{
        DisplayException(exc, EXCEPTION_META);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::TextEndDrag(TObject *Sender, TObject *Target, int X,
		  int Y)
{
	try
	{
		auto dropTarget = controller_.endDragDrop();
		controller_.addElement <WikiElements::Text> (dropTarget);
	}
	catch (std::exception const& exc)
	{
		DisplayException(exc, EXCEPTION_META);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::NewArticle1Click(TObject *Sender)
{
	auto reset = [this](){
		persistence_.stopAutoBackup();
		controller_.reset();
		persistence_.startAutoBackup();
	};

	if (controller_.isDirty())
	{
		auto cont = WarnAndSave(persistence_);

		if (cont == AbortContinueCase::Continue)
			reset();
	}
	else
		reset();
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::SaveArticleAs1Click(TObject *Sender)
{
    SaveAsDialog(persistence_);
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::OpenArticle1Click(TObject *Sender)
{
	if (controller_.isDirty())
	{
		auto cont = WarnAndSave(persistence_);

		if (cont == AbortContinueCase::Continue)
			OpenArticle(persistence_);
	}
	else
		OpenArticle(persistence_);
}
//---------------------------------------------------------------------------


void __fastcall TMainEditor::Image2EndDrag(TObject *Sender, TObject *Target, int X,
          int Y)
{
	try
	{
		auto dropTarget = controller_.endDragDrop();
		controller_.addElement <WikiElements::HorizontalLine> (dropTarget);
	}
	catch (std::exception const& exc)
	{
		DisplayException(exc, EXCEPTION_META);
	}
}
//---------------------------------------------------------------------------

