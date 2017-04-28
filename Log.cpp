//---------------------------------------------------------------------------

#include <vcl.h>
#include <Vcl.Dialogs.hpp>
#pragma hdrstop

#include "Log.h"
#include "debug.h"
#include "localization.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLogWindow *LogWindow;
//---------------------------------------------------------------------------
__fastcall TLogWindow::TLogWindow(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLogWindow::FormResize(TObject *Sender)
{
	Log->Width = Width;
	Log->Height = Height;
}
//---------------------------------------------------------------------------
void __fastcall TLogWindow::SaveLog1Click(TObject *Sender)
{
    // ...
}
//---------------------------------------------------------------------------
void __fastcall TLogWindow::ClearLog1Click(TObject *Sender)
{
    Log->Clear();
}
//---------------------------------------------------------------------------
void TLogWindow::translate()
{
	if (translated_)
		return;
	translated_ = true;

	std::function <void(TMenuItem*)> translateMenuItem;
	translateMenuItem = [this, &translateMenuItem](TMenuItem* item){
		for (int i = 0; i < item->Count; ++i)
		{
			item->operator[](i)->Caption = ::translate(item->operator[](i)->Caption);
			translateMenuItem(item->operator[](i));
        }
	};
	translateMenuItem(LogWindowMenu->Items);
}
//---------------------------------------------------------------------------
void __fastcall TLogWindow::FormCreate(TObject *Sender)
{
    SetLog(Log);
}
//---------------------------------------------------------------------------
