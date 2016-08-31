//---------------------------------------------------------------------------

#pragma hdrstop

#include "header.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace WikiElements
{
//---------------------------------------------------------------------------
	Header::Header(TControl* parent)
		: Element{parent}
		, underline_{new TPanel(parent)}
	{
		control_->Left = 1;
		control_->Color = clWhite;
		control_->Width = 100;
		control_->Height = 100;
		control_->Top = 1;
		control_->BorderStyle = bsNone;


	}
//---------------------------------------------------------------------------
}