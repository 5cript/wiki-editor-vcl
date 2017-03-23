//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../table.h"
#include "localization.h"

#include "table_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTableOptionsFrame *TableOptionsFrame;
//---------------------------------------------------------------------------
__fastcall TTableOptionsFrame::TTableOptionsFrame(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TTableOptionsFrame::~TTableOptionsFrame()
{
	if (selfReference_)
		*selfReference_ = nullptr;
}
//---------------------------------------------------------------------------
void TTableOptionsFrame::populate()
{
	auto* handle = owner_->getDataHandle();

	TableAttributes->Strings->Clear();
	for (auto const& i : handle->attributes)
	{
		TableAttributes->InsertRow(i.first.c_str(), i.second.c_str(), true);
    }
}
//---------------------------------------------------------------------------
void TTableOptionsFrame::translate()
{
	if (translated_)
		return;
	translated_ = true;

	for (int i = 0; i != ControlCount; ++i)
	{
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TCheckBox, Caption);
	}

    translateStringList(TableAttributes->TitleCaptions);
}
//---------------------------------------------------------------------------
void TTableOptionsFrame::setOwner(WikiElements::BasicElement* owner)
{
 	owner_ = dynamic_cast <WikiElements::Table*> (owner);
	if (!owner_)
		throw std::invalid_argument("passed owner is not of table element type");
}
//---------------------------------------------------------------------------
void TTableOptionsFrame::setSelfReference(TFrame** selfReference)
{
	selfReference_ = selfReference;
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::TableAttributesValidate(TObject *Sender, int ACol,
          int ARow, const UnicodeString KeyName, const UnicodeString KeyValue)
{
	for (int i = 1; i != TableAttributes->RowCount; ++i)
	{
		std::string key = AnsiString(TableAttributes->Keys[i]).c_str();
		std::string value = AnsiString(TableAttributes->Values[key.c_str()]).c_str();

		if (key.empty())
			continue;

		if (value.empty())
		{
			auto& attr = owner_->getDataHandle()->attributes;
			auto iter = attr.find(key);
			if (iter != std::end(attr))
				attr.erase(iter);
        }
		else
			owner_->getDataHandle()->attributes[key] = value;
    }
}
//---------------------------------------------------------------------------

