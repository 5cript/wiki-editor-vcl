//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsDialog *SettingsDialog;
//---------------------------------------------------------------------------
__fastcall TSettingsDialog::TSettingsDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
