//---------------------------------------------------------------------------

#pragma hdrstop

// Self
#include "table.h"

// Project
#include "style_applicator.h"
#include "frames/table_options.h"
#include "style_parser.h"

#include "debug.h"

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

		// Border
		control_->BevelInner = bvNone;
		control_->BevelOuter = bvNone;
        control_->BorderStyle = bsNone;

		// Positioning and Size
		control_->Left = leftSectionPadding;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		// control_->Height = 10;

		// Style
		// control_->Color = clWhite;
		control_->DrawingStyle = gdsClassic;
		//control_->GridLineWidth = 0;

		// Events
		control_->OnDrawCell = this->onDrawCell;
		control_->OnSetEditText = this->onSetEditText;
		control_->OnExit = this->onExit;
		control_->OnMouseUp = this->onMouseUp;
		control_->OnSelectCell = this->onSelectCell;

		control_->Options = TGridOptions()
			<< goFixedVertLine
			// << goFixedHorzLine
			// << goRowSizing
			<< goColSizing
			<< goEditing
			<< goAlwaysShowEditor
		;

		resize(4, 4, false);

		control_->ColWidths[0] = 0;
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

		DebugOut(cellStyle);
		DebugOut(rowStyle);
		DebugOut(tableStyle);
		DebugOut(tableClass);
		DebugOut(data_.attributes);

		using namespace WretchedCss;

        StyleParser extractor;
		auto sheet = parsedStyle_;
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

		return filteredSheet;
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
	void Table::updateRowHeights()
	{
		for (int y = control_->FixedRows; y != control_->RowCount; ++y)
		{
			auto maxHeight = control_->DefaultRowHeight - 4;
			for (int x = control_->FixedCols; x != control_->ColCount; ++x)
			{
				TRect rect = Rect(0, 0, control_->ColWidths[x] - 4, 0);
				int textHeight = DrawText(
					control_->Canvas->Handle,
					control_->Cells[x][y].c_str(),
					-1,
					&rect,
					DT_WORDBREAK | DT_CALCRECT
				);
				if (textHeight > maxHeight)
					maxHeight = textHeight;
			}
			control_->RowHeights[y] = maxHeight + 10;
		}
		control_->Height = 15;
		for (int y = control_->FixedRows; y != control_->RowCount; ++y)
		{
			control_->Height += control_->RowHeights[y];
        }
	}
//---------------------------------------------------------------------------
	void Table::updateColumnWidths()
	{

	}
//---------------------------------------------------------------------------
	void Table::updateSizes()
	{
		updateRowHeights();
		updateColumnWidths();
        parentSection_->realign();
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
	void Table::styleChanged(WretchedCss::StyleSheet const& style)
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

		gatherStyles(0, 0);
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onDrawCell(TObject *Sender, int ACol, int ARow, TRect const &Rect, TGridDrawState State)
	{
		if (ACol == 0 || ARow == 0)
			return;

		auto cellRect = Rect;
		cellRect.Left -= 5;
		cellRect.Bottom += 1;

		control_->Canvas->Brush->Color = clGray;
		control_->Canvas->FillRect(cellRect);

		// Grid Lines
		control_->Canvas->Pen->Color = clBlack;

		// Grid Lines - Horizontal
		control_->Canvas->MoveTo(cellRect.Left, cellRect.Top);
		control_->Canvas->LineTo(cellRect.Right, cellRect.Top);

		// Grid Lines - Vertical
		control_->Canvas->MoveTo(cellRect.Left, cellRect.Top);
		control_->Canvas->LineTo(cellRect.Left, cellRect.Bottom);

		auto textRect = Rect;
		textRect.Top += 2;
		DrawText(
			control_->Canvas->Handle,
			control_->Cells[ACol][ARow].c_str(),
			-1,
			&textRect,
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

		updateRowHeights();


		/*
		control_->RowHeights[ARow] =
			std::max(1, lineCountMax) *
			control_->Canvas->TextHeight("ABCDEFGHIJKLMNOPQRSTUVWXYZ") +
			10
		;
		*/

        parentSection_->makeDirty();
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
	{
        updateRowHeights();
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onExit(TObject* Sender)
	{
		updateRowHeights();
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
	{
		updateRowHeights();
        CanSelect = true;
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
