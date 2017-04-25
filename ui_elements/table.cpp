//---------------------------------------------------------------------------

#pragma hdrstop

// Self
#include "table.h"

// Project
#include "style_applicator.h"
#include "frames/table_options.h"
#include "style_parser.h"
#include "controller.h"

#include "debug.h"

// VCL
#include <Vcl.Dialogs.hpp>

// STL
#include <algorithm>
#include <limits>
#include <tuple>

#define RPP_COLOR(INDEX) INDEX, WretchedCss::ValueTypes::Color, std::decay <decltype(tup)>::type
#define RPP_STRING(INDEX) INDEX, WretchedCss::ValueTypes::StringValue, std::decay <decltype(tup)>::type
#define RPP_SIZE(INDEX) INDEX, WretchedCss::ValueTypes::NumericValue, std::decay <decltype(tup)>::type
//---------------------------------------------------------------------------
namespace WikiElements
{
//---------------------------------------------------------------------------
	Table::Table(Section* parentSection)
		: Element{parentSection}
		, styleGrid_{}
		, borderColor_{clBlack}
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
		//control_->SelectedColor = clRed;
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
            // << goDrawFocusSelected
		;

		resize(4, 4, false);

		control_->ColWidths[0] = 0;
		control_->RowHeights[0] = 8;
	}
//---------------------------------------------------------------------------
	void Table::writeModelToUserInterface()
	{
		if (data_.rows.empty())
		{
			resize(0, 0, false);
			return;
		}

		resize(data_.rows.size(), data_.rows[0].cells.size(), false);

		std::size_t rowc = 0u;
		for (auto const& row : data_.rows)
		{
			std::size_t colc = 0u;
			for (auto const& cell : row.cells)
			{
				setViewCellText(rowc, colc, cell.data, false);
				++colc;
			}
			++rowc;
		}
	}
//---------------------------------------------------------------------------
	void Table::setViewCellText(std::size_t row, std::size_t column, std::string const& text, bool updateModel)
	{
		if (updateModel)
		{
			if (data_.rows.size() <= row)
				throw std::invalid_argument("model table is smaler than given row index");
			if (data_.rows[row].cells.size() <= column)
				throw std::invalid_argument("model table is smaler than given column index");

			data_.rows[row].cells[column].data = text;
		}

		if (control_->RowCount - 1 <= row)
			throw std::invalid_argument("view table is smaler than given row index");
		if (control_->ColCount - 1 <= column)
			throw std::invalid_argument("view table is smaler than given row index");

		control_->Cells[column + 1][row + 1] = text.c_str();
	}
//---------------------------------------------------------------------------
	void Table::populateStyleGrid()
	{
		for (std::size_t row = 0u; row != data_.rows.size(); ++row)
			for (std::size_t col = 0u; col != data_.rows[row].cells.size(); ++col)
				gatherStyles(col, row);
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

		// body
		{
			auto optBody = parsedStyle_.select(cssParser.selectorToJson("body"));
			if (optBody)
			{
				filteredSheet.addStyle(optBody.get());
			}
		}

		if (tableClass)
		{
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

		TColor brushColor = clWhite;
		TColor fontColor = clBlack;


		auto readCellStyle = [&](){
			auto hierarchy = StyleHierarchy{};
			hierarchy
				<< "body"
				<< ".table"
				<< ".tableStyle"
				<< ".rowStyle"
				<< ".cellStyle"
			;

			//ShowMessage(styleGrid_[ARow - 1][ACol - 1].toString().c_str());

			std::tuple <TColor, TColor, TColor, TColor, std::string, std::string, int, int> tup;

			ShowMessage(filteredSheet.toString().c_str());

			readStyles(
				&tup,
                filteredSheet,
				hierarchy,
				{
					readColorProperty <RPP_COLOR(0)> ("background-color"),
					readColorProperty <RPP_COLOR(1)> ("header-background"),
					readColorProperty <RPP_COLOR(2)> ("font-color"),
					readColorProperty <RPP_COLOR(3)> ("header-font-color"),
					readStringProperty <RPP_STRING(4)> ("font-weight"),
					readStringProperty <RPP_STRING(5)> ("header-font-weight"),
					readSizeProperty <RPP_SIZE(6)> ("font-size"),
					readSizeProperty <RPP_SIZE(7)> ("header-font-size")
				}
			);

			auto& style = styleGrid_[row][column];

			style = {};
			style.background = std::get <0> (tup);
			style.highlightBackground = std::get <1> (tup);
			style.fontColor = std::get <2> (tup);
			style.highlightFontColor = std::get <3> (tup);
			if (std::get <4> (tup) == "bold")
				style.fontWeight = TableStyling::FontWeight::Bold;
			if (std::get <5> (tup) == "bold")
				style.highlightFontWeight = TableStyling::FontWeight::Bold;
			style.fontSize = std::get <6> (tup);
			style.highlightFontSize = std::get <7> (tup);

		};
		readCellStyle();

		// styleGrid_[row][column] = filteredSheet;

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

		//auto oldHeight = data_.rows.size();
		//auto oldWidth = data_

		if (safeMode && !safetyCheck(true))
			return false;

		// resize model
		data_.rows.resize(height);
		for (auto& row : data_.rows)
			resizeRow(row, width);

		// resize view
		control_->RowCount = data_.rows.size() + 1;
		control_->ColCount = data_.rows[0].cells.size() + 1;

        // resize style grid
		styleGrid_.resize(height);
		for (auto& row : styleGrid_)
			row.resize(width);

		updateRowHeights();
		updateColumnWidths();

        populateStyleGrid();

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
		for (int y = 1; y != control_->RowCount; ++y)
		{
			int a = control_->RowHeights[y];
			control_->Height += control_->RowHeights[y];
		}
		int h = control_->Height;
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
		parentSection_->causePageRealign();
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
	void Table::styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign)
	{
    	auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".table"
		;

        std::tuple <TColor> tup;

		readStyles(
			&tup,
			style,
			hierarchy,
			{
				readColorProperty <RPP_COLOR(0)> ("border-color")
			}
		);

		std::tie (borderColor_) = tup;

		readStyles(
			&*control_,
			style,
			hierarchy,
			{
				readFontStyles <control_type>
			}
		);

		if (!delayRealign)
			parentSection_->causePageRealign();
	}
//---------------------------------------------------------------------------
	void __fastcall Table::onDrawCell(TObject *Sender, int ACol, int ARow, TRect const &Rect, TGridDrawState State)
	{
		if (ACol == 0 || ARow == 0)
			return;

		auto cellRect = Rect;
		cellRect.Left -= 5;
		cellRect.Bottom += 1;

		auto* cell_ = &data_.rows[ARow - 1].cells[ACol - 1];

		auto& style = styleGrid_[ARow - 1][ACol - 1];

		control_->Canvas->Font->Style = TFontStyles();
		if (cell_->isHeaderCell)
		{
			control_->Canvas->Brush->Color = style.highlightBackground;
			control_->Canvas->Font->Color = style.highlightFontColor;
			control_->Canvas->Font->Size = style.highlightFontSize;
			if (style.highlightFontWeight == TableStyling::FontWeight::Bold)
				control_->Canvas->Font->Style = TFontStyles() << fsBold;
		}
		else
		{
			control_->Canvas->Brush->Color = style.background;
			control_->Canvas->Font->Color = style.fontColor;
			control_->Canvas->Font->Size = style.fontSize;
			if (style.fontWeight == TableStyling::FontWeight::Bold)
				control_->Canvas->Font->Style = TFontStyles() << fsBold;
		}

		//control_->Canvas->Brush->Color = brushColor;
		control_->Canvas->FillRect(cellRect);

		// Grid Lines
		control_->Canvas->Pen->Color = borderColor_;

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

		updateSizes();


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

		// Update Options Frame:
		static_cast <TTableOptionsFrame*> (getOptionsFrame())->setCell(&data_.rows[ARow - 1].cells[ACol - 1]);
    }
//---------------------------------------------------------------------------
	void Table::initializeOptionsFrame()
	{
		optionsFrame_.reset(new TTableOptionsFrame(nullptr));
        static_cast <TTableOptionsFrame*> (getOptionsFrame())->setOwner(this);
	}
//---------------------------------------------------------------------------
	void Table::initializeStyleOptionsFrame()
	{

    }
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#undef RPP_COLOR
#pragma package(smart_init)
