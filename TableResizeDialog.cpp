//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TableResizeDialog.h"
#include "localization.h"
#include "debug.h"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResizeDialog *ResizeDialog;
//---------------------------------------------------------------------------
__fastcall TResizeDialog::TResizeDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TResizeDialog::translate()
{
    for(int i = 0; i < ComponentCount; i++)
	{
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TButton, Caption);
	}
}
//---------------------------------------------------------------------------
void TResizeDialog::show(WikiElements::Table* table)
{
	table_ = table;
	TableWidth->Value = table->getColumnCount();
	TableHeight->Value = table->getRowCount();
    ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TResizeDialog::Button1Click(TObject *Sender)
{
	bool safeResize = table_->resize(TableHeight->Value, TableWidth->Value, true);
	if (!safeResize)
	{
		auto res = MessageBox(
			nullptr,
			::translate("$TableResizeLossWarning").c_str(),
			::translate("$LossWarningCaption").c_str(),
			MB_YESNOCANCEL | MB_ICONWARNING
		);

		if (res == IDYES)
			table_->resize(TableHeight->Value, TableWidth->Value);
    }
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TResizeDialog::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
