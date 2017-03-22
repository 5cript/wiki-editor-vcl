//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BackupSettings.h"
#include "localization.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBackupSettingsDialog *BackupSettingsDialog;
//---------------------------------------------------------------------------
__fastcall TBackupSettingsDialog::TBackupSettingsDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TBackupSettingsDialog::TranslateWindow()
{
	TRANSLATE_SPECIFIC(this, Caption);

	// All Objects that have captions:
	for(int i = 0; i < ComponentCount; i++)
	{
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TButton, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TCategoryPanel, Caption);
	}
}
//---------------------------------------------------------------------------
bool TBackupSettingsDialog::Accepted() const
{
    return accept;
}
//---------------------------------------------------------------------------
void __fastcall TBackupSettingsDialog::FormCreate(TObject *Sender)
{
	TranslateWindow();
}
//---------------------------------------------------------------------------
void __fastcall TBackupSettingsDialog::MaxBackupsChange(TObject *Sender)
{
	auto text = ::translate("$OldestBackup");
	IntervalLabel->Caption = IntToStr(Interval->Position);
	text = StringReplace(text, "%m", IntToStr((Interval->Position * StrToInt(MaxBackups->Text)) / 60), TReplaceFlags{} << rfReplaceAll);
    OldestBackup->Caption = text;
}
//---------------------------------------------------------------------------
void __fastcall TBackupSettingsDialog::Button1Click(TObject *Sender)
{
	accept = true;
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TBackupSettingsDialog::Button2Click(TObject *Sender)
{
	accept = false;
	Close();
}
//---------------------------------------------------------------------------
void TBackupSettingsDialog::LoadOptions(BackupOptions const& options)
{
	Interval->Position = options.intervalSec;
	MaxBackups->Text = IntToStr(options.maxBackups);
	MaxBackupsChange(nullptr);
}
//---------------------------------------------------------------------------
BackupOptions TBackupSettingsDialog::GetOptions() const
{
	return {
		Interval->Position,
		StrToInt(MaxBackups->Text)
    };
}
//---------------------------------------------------------------------------
