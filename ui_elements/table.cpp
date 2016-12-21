//---------------------------------------------------------------------------

#pragma hdrstop

// Self
#include "table.h"

// Project
#include "style_applicator.h"
#include "frames/table_options.h"
#include "style_parser.h"

// VCL
#include <Vcl.Dialogs.hpp>

// STL
#include <algorithm>
#include <limits>
#include <tuple>
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	Table::Table(Section* parentSection)
		: Element{parentSection}
	{
    	auto* parent = parentSection->getLayout()->getControl();

		control_->Left = leftSectionPadding;
		// control_->Color = clWhite;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		// control_->Height = 10;
		control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		control_->OnDrawCell = this->onDrawCell;
		control_->OnSetEditText = this->onSetEditText;

		control_->Options <<= goFixedVertLine;
		control_->Options <<= goFixedHorzLine;
		control_->Options <<= goRowSizing;
		control_->Options <<= goColSizing;
		control_->Options <<= goEditing;
		control_->Options <<= goAlwaysShowEditor;

		control_->DrawingStyle = gdsClassic;
		control_->ColWidths[0] = 8;
		control_->RowHeights[0] = 8;
	}
//---------------------------------------------------------------------------
	WretchedCss::StyleSheet Table::gatherStyles(std::size_t column, std::size_t row)
	{
		if (data_.rows.size() <= row)
			throw std::invalid_argument("row parameter exceeds actual row count");

		if (data_.rows[row].cells.size() <= column)
			throw std::invalid_argument("column parameter exceeds actual row count");

		auto getOptional = [](std::map <std::string, std::string> const& map,
							  std::string const& key) -> boost::optional <std::string>
		{
			auto iter = map.find(key);
			if (iter != std::end(map))
				return {iter->second};
			else
				return boost::none;
        };

		auto cellStyle = getOptional(data_.rows[row].cells[column].attributes, "style");
		auto rowStyle = getOptional(data_.rows[row].attributes, "style");
		auto tableStyle = getOptional(data_.attributes, "style");

		auto tableClass = getOptional(data_.attributes, "class");

		using namespace WretchedCss;

		StyleParser extractor;
		auto sheet = extractor.parseStyleSheet(style_);
		StyleSheet filteredSheet;

		auto augmentStyle = [](std::string const& selector, std::string const& content)
		{
            return selector + " {\r\n" + content + "\r\n}";
		};

		auto& cssParser = WretchedCssLibrary::getInstance();

		if (tableClass) {
			auto tableClass2 = sheet.select(cssParser.selectorToJson(std::string(".") + tableClass.get()));
			if (tableClass2)
				filteredSheet.addStyle(tableClass2.get());
		}

		if (tableStyle)
			filteredSheet.addStyle(
				extractor.parseStyleSheet(
					augmentStyle(".tableStyle", tableStyle.get())
				).select(cssParser.selectorToJson(".tableStyle")).get()
			);

		if (rowStyle)
			filteredSheet.addStyle(
				extractor.parseStyleSheet(
					augmentStyle(".rowStyle", rowStyle.get())
				).select(cssParser.selectorToJson(".rowStyle")).get()
			);

		if (cellStyle)
			filteredSheet.addStyle(
				extractor.parseStyleSheet(
					augmentStyle(".cellStyle", cellStyle.get())
				).select(cssParser.selectorToJson(".cellStyle")).get()
			);

        ShowMessage(filteredSheet.toString().c_str());
	}
//---------------------------------------------------------------------------
	bool Table::resize(std::size_t height, std::size_t width, bool safeMode)
	{
		auto safetyCheck = [this, &height, &width](bool checkAttributes) -> bool
		{
			auto canRemoveCellSafely = [](WikiMarkup::Components::TableCell* cell, bool checkAttributes) {
				if (cell == nullptr)
					return true;

				if (!cell->data.empty())
					return false;

				if (checkAttributes && !cell->attributes.empty())
					return false;

				return true;
            };

			std::size_t minWidth;
			std::size_t maxWidth;
			std::size_t oldHeight = data_.rows.size();

			std::tie (minWidth, maxWidth) = getTableWidth();

			// from top to bottom
			if (maxWidth > width) // optimizing check
				for (std::size_t y = 0u; y != data_.rows.size(); ++y)
					for (std::size_t x = width; x != maxWidth; ++x)
						if (!canRemoveCellSafely(data_[x][y], checkAttributes))
							return false;

			if (oldHeight > height) // optimizing check
				for (std::size_t y = height; y != oldHeight; ++y)
					for (std::size_t x = 0u; x != width; ++x)
						if (!canRemoveCellSafely(data_[x][y], checkAttributes))
							return false;

			return true;
		};

		if (safeMode && !safetyCheck(true))
			return false;

		data_.rows.resize(height);
		for (auto& row : data_.rows)
			resizeRow(row, width);

		return true;
	}
//---------------------------------------------------------------------------
	void Table::resizeRow(WikiMarkup::Components::TableRow& row, std::size_t width)
	{
        row.cells.resize(width);
	}
//---------------------------------------------------------------------------
	std::pair <std::size_t, std::size_t> Table::getTableWidth() const
	{
		if (data_.rows.empty())
			return {0u, 0u};

		std::size_t widthMin = std::numeric_limits<std::size_t>::max();
		std::size_t widthMax = 0u;
		for (auto const& r : data_.rows)
		{
			widthMin = std::min(r.cells.size(), widthMin);
			widthMax = std::max(r.cells.size(), widthMax);
		}
		return {widthMin, widthMax};
    }
//---------------------------------------------------------------------------
	void Table::styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
	{
    	auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".table"
		;

		readStyles(
			&*control_,
			style,
			hierarchy,
			{
				//readFontStyles <control_type>,
				//readBackgroundStyles <control_type>
			}
		);
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onDrawCell(TObject *Sender, int ACol, int ARow, TRect const &Rect, TGridDrawState State)
	{
		//control_->Canvas->Brush->Color = clLime;
		//control_->Canvas->FillRect(Rect);
		//control_type::OnDrawCell(Sender, ACol, ARow, Rect, State);

		auto drawRectCpy = Rect;
		drawRectCpy.Left += 2;
		drawRectCpy.Top += 2;


		control_->Canvas->Brush->Color = clRed;
		control_->Canvas->FillRect(Rect);
		DrawText(
			control_->Canvas->Handle,
			control_->Cells[ACol][ARow].c_str(),
			-1,
			&drawRectCpy,
			DT_NOPREFIX | DT_WORDBREAK
		);
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value)
	{
		int lineCountMax = 0;
		for (int col = 1; col != control_->ColCount; ++col)
		{
			int lineCount = 1;
			for (int i = 1; i != control_->Cells[ARow][col].Length() + 1; ++i)
			{
				//auto c = Value[i];
				auto c = control_->Cells[ARow][col][i];
				if (c == '\n')
					lineCount++;
			}

			if (lineCount > lineCountMax)
				lineCountMax = lineCount;
		}


		control_->RowHeights[ARow] =
			std::max(1, lineCountMax) *
			control_->Canvas->TextHeight("ABCDEFGHIJKLMNOPQRSTUVWXYZ") +
			10
		;
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
	{

	}
//---------------------------------------------------------------------------
	void Table::initializeOptionsFrame()
	{
		optionsFrame_.reset(new TTableOptionsFrame(nullptr));
        static_cast <TTableOptionsFrame*> (&*optionsFrame_)->setOwner(this);
	}
//---------------------------------------------------------------------------
	void Table::initializeStyleOptionsFrame()
	{

    }
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
