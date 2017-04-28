//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "../table.h"
#include "localization.h"
#include "../../TableResizeDialog.h"
#include "StylePicker.h"

#include "table_options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTableOptionsFrame *TableOptionsFrame;
//---------------------------------------------------------------------------
__fastcall TTableOptionsFrame::TTableOptionsFrame(TComponent* Owner)
	: TFrame{Owner}
	, owner_{nullptr}
	, cell_{nullptr}
	, selfReference_{nullptr}
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

	std::function <void(TMenuItem*)> translateMenuItem;
	translateMenuItem = [this, &translateMenuItem](TMenuItem* item){
		for (int i = 0; i < item->Count; ++i)
		{
			item->operator[](i)->Caption = ::translate(item->operator[](i)->Caption);
			translateMenuItem(item->operator[](i));
        }
	};
	translateMenuItem(ChangeStyleMenu->Items);

	for (int i = 0; i != ControlCount; ++i)
	{
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TCheckBox, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TButton, Caption);
	}

	TRANSLATE_SPECIFIC(AttributeLbl, Caption);
	TRANSLATE_SPECIFIC(RowAttrLabel, Caption);
	TRANSLATE_SPECIFIC(CellAttrLabel, Caption);
	TRANSLATE_SPECIFIC(Button1, Caption);
	TRANSLATE_SPECIFIC(Button2, Caption);
	TRANSLATE_SPECIFIC(HeaderCellChecker, Caption);

	translateStringList(TableAttributes->TitleCaptions);
    translateStringList(CellAttributes->TitleCaptions);
    translateStringList(RowAttributes->TitleCaptions);
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
void TTableOptionsFrame::setCell(WikiMarkup::Components::TableCell* cell)
{
	cell_ = cell;
	if (cell_)
	{
		HeaderCellChecker->Checked = cell_->isHeaderCell;

		CellAttributes->Strings->Clear();
		for (auto const& i : cell_->attributes)
		{
			CellAttributes->InsertRow(i.first.c_str(), i.second.c_str(), true);
		}
	}
}
//---------------------------------------------------------------------------
void TTableOptionsFrame::setRow(WikiMarkup::Components::TableRow* row)
{
	row_ = row;
	if (row_)
	{
		RowAttributes->Strings->Clear();
		for (auto const& i : row_->attributes)
		{
			RowAttributes->InsertRow(i.first.c_str(), i.second.c_str(), true);
		}
    }
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

		owner_->getDataHandle()->attributes[key] = value;
		owner_->populateStyleGrid();
	}
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::CellAttributesValidate(TObject *Sender, int ACol,
		  int ARow, const UnicodeString KeyName, const UnicodeString KeyValue)
{
	if (!cell_)
		return;

	for (int i = 1; i != CellAttributes->RowCount; ++i)
	{
		std::string key = AnsiString(CellAttributes->Keys[i]).c_str();
		std::string value = AnsiString(CellAttributes->Values[key.c_str()]).c_str();

		if (key.empty())
			continue;

		if (value.empty())
		{
			auto& attr = cell_->attributes;
			auto iter = attr.find(key);
			if (iter != std::end(attr))
				attr.erase(iter);
			continue;
		}

		cell_->attributes[key] = value;
		owner_->populateStyleGrid();
	}
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::HeaderCellCheckerClick(TObject *Sender)
{
	if (cell_)
	{
		cell_->isHeaderCell = HeaderCellChecker->Checked;
    }
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::Button1Click(TObject *Sender)
{
    ResizeDialog->show(owner_);
}
//---------------------------------------------------------------------------
void TTableOptionsFrame::setStyleContainer(StyleContainment::Style const& style)
{
    parsedStyle_ = style;
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::Change1Click(TObject *Sender)
{
	// ...
	auto res = FrameStylePicker->show(UTF8String(clickedEditor_->Values["style"]).c_str(), parsedStyle_);
	if (res)
	{
		clickedEditor_->Values["style"] = res.get().c_str();
        clickedEditor_->OnValidate(Sender, 0, 0, "", "");
    }
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::ChangeClass1Click(TObject *Sender)
{
	// ...
	ShowMessage("class");
}
//---------------------------------------------------------------------------

void __fastcall TTableOptionsFrame::FrameResize(TObject *Sender)
{
	constexpr int scrollBoxRightPadding = 20;

	ScrollBox->Height = Height - ScrollBox->Top;
	ScrollBox->Width = Width;

	TableAttributes->Width = ScrollBox->Width - TableAttributes->Left - scrollBoxRightPadding;
	RowAttributes->Width = ScrollBox->Width - RowAttributes->Left - scrollBoxRightPadding;
	CellAttributes->Width = ScrollBox->Width - CellAttributes->Left - scrollBoxRightPadding;
	Button1->Width = ScrollBox->Width - Button1->Left - scrollBoxRightPadding;
	Button2->Width = ScrollBox->Width - Button2->Left - scrollBoxRightPadding;
}
//---------------------------------------------------------------------------

void __fastcall TTableOptionsFrame::Button2Click(TObject *Sender)
{
	auto res = MessageBox(
		nullptr,
		::translate("$ReallyWantRemove").c_str(),
		::translate("$LossWarningCaption").c_str(),
		MB_YESNO | MB_ICONWARNING
	);
	if (res == IDYES)
		owner_->remove();
}
//---------------------------------------------------------------------------

void __fastcall TTableOptionsFrame::RowAttributesValidate(TObject *Sender, int ACol,
          int ARow, const UnicodeString KeyName, const UnicodeString KeyValue)
{
	if (!cell_)
		return;

	for (int i = 1; i != RowAttributes->RowCount; ++i)
	{
		std::string key = AnsiString(RowAttributes->Keys[i]).c_str();
		std::string value = AnsiString(RowAttributes->Values[key.c_str()]).c_str();

		if (key.empty())
			continue;

		if (value.empty())
		{
			auto& attr = row_->attributes;
			auto iter = attr.find(key);
			if (iter != std::end(attr))
				attr.erase(iter);
			continue;
		}

		row_->attributes[key] = value;
		owner_->populateStyleGrid();
	}
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::RowAttributesMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	clickedEditor_ = static_cast <TValueListEditor*> (RowAttributes);
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::CellAttributesMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	clickedEditor_ = static_cast <TValueListEditor*> (CellAttributes);
}
//---------------------------------------------------------------------------
void __fastcall TTableOptionsFrame::TableAttributesMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	clickedEditor_ = static_cast <TValueListEditor*> (TableAttributes);
}
//---------------------------------------------------------------------------

