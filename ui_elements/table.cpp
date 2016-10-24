//---------------------------------------------------------------------------

#pragma hdrstop

#include "table.h"

#include "style_applicator.h"

#include <algorithm>

#include <Vcl.Dialogs.hpp>
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
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
