//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "header_options.h"
#include "localization.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THeaderOptionsFrame *HeaderOptionsFrame;
//---------------------------------------------------------------------------
__fastcall THeaderOptionsFrame::THeaderOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
    , translated_{false}
{
}
//---------------------------------------------------------------------------
void __fastcall THeaderOptionsFrame::Label1Click(TObject *Sender)
{
    ShowMessage("Hello");
}
//---------------------------------------------------------------------------
void THeaderOptionsFrame::translate()
{
	if (translated_)
		return;

	for (int i = 0; i < ComponentCount; i++)
	{
		TRANSLATE_OF_TYPE(this, TLabel, Caption)
	}

	std::unique_ptr <TStringList> tempList {new TStringList()};
	tempList->AddStrings(HeaderLayer->Items);
	for (int j = 0; j != tempList->Count; ++j)
	{
    	auto temp = tempList->Strings[j];
		TRANSLATE_SPECIFIC(tempList, Strings[j])
	}
	HeaderLayer->Items->Assign(&*tempList);
	HeaderLayer->ItemIndex = 0;

	translated_ = true;
}
//---------------------------------------------------------------------------

