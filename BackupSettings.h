//---------------------------------------------------------------------------

#ifndef BackupSettingsH
#define BackupSettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "options.h"
//---------------------------------------------------------------------------
class TBackupSettingsDialog : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TTrackBar *Interval;
	TLabel *Label1;
	TEdit *MaxBackups;
	TLabel *Label2;
	TLabel *OldestBackup;
	TLabel *IntervalLabel;
	TButton *Button1;
	TButton *Button2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MaxBackupsChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool accept;
public:		// Benutzer-Deklarationen
	void TranslateWindow();
	bool Accepted() const;
	void LoadOptions(BackupOptions const& options);
	BackupOptions GetOptions() const;
	__fastcall TBackupSettingsDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBackupSettingsDialog *BackupSettingsDialog;
//---------------------------------------------------------------------------
#endif
