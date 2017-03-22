//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TSettingsDialog : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TSettingsDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsDialog *SettingsDialog;
//---------------------------------------------------------------------------
#endif
