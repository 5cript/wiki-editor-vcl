//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StylePicker.h"
#include "style_parser.h"
#include "localization.h"
#include "style_applicator.h"

#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrameStylePicker *FrameStylePicker;
//---------------------------------------------------------------------------
__fastcall TFrameStylePicker::TFrameStylePicker(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFrameStylePicker::translate()
{
    for (int i = 0; i != ControlCount; ++i)
	{
		TRANSLATE_OF_TYPE_I(i, this, TLabel, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TCheckBox, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TButton, Caption);
		TRANSLATE_OF_TYPE_I(i, this, TPanel, Caption);
	}

	translateStringList(Alignment->Items);
}
//---------------------------------------------------------------------------
void __fastcall TFrameStylePicker::FontColorExampleClick(TObject *Sender)
{
	// change color.
	if (ColorDialog->Execute())
	{
		ExampleFrame->Font->Color = ColorDialog->Color;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrameStylePicker::ChangeBackgroundColorClick(TObject *Sender)
{
	if (ColorDialog->Execute())
	{
		ExampleFrame->Color = ColorDialog->Color;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrameStylePicker::BoldStateClick(TObject *Sender)
{
	if (BoldState->Checked)
		ExampleFrame->Font->Style = ExampleFrame->Font->Style << fsBold;
	else
		ExampleFrame->Font->Style = ExampleFrame->Font->Style >> fsBold;
}
//---------------------------------------------------------------------------

void __fastcall TFrameStylePicker::ItalicStateClick(TObject *Sender)
{
	if (ItalicState->Checked)
		ExampleFrame->Font->Style = ExampleFrame->Font->Style << fsItalic;
	else
		ExampleFrame->Font->Style = ExampleFrame->Font->Style >> fsItalic;
}
//---------------------------------------------------------------------------
boost::optional <std::string> TFrameStylePicker::show(std::string const& styleString,
													  StyleContainment::Style baseStyle)
{
	translate();

	using namespace WretchedCss;
	auto augmentStyle = [](std::string const& selector, std::string const& content)
	{
		return selector + " {\r\n" + content + "\r\n}";
	};

	auto& cssParser = WretchedCssLibrary::getInstance();
	StyleSheet styleSheet;
	StyleParser extractor;

	styleSheet.addStyle(
		extractor.parseStyleSheet(
			augmentStyle(".style", styleString)
		).select(cssParser.selectorToJson(".style")).get()
	);

    auto hierarchy = StyleHierarchy{};
	hierarchy << ".style";

	ExampleFrame->Color = baseStyle.background;
	ExampleFrame->Font->Color = baseStyle.fontColor;
	ExampleFrame->Font->Size = baseStyle.fontSize;
	if (baseStyle.fontWeight == StyleContainment::FontWeight::Bold)
		ExampleFrame->Font->Style = ExampleFrame->Font->Style << fsBold;
	if (baseStyle.fontStyle == StyleContainment::FontStyle::Italic)
		ExampleFrame->Font->Style = ExampleFrame->Font->Style << fsItalic;

	switch (baseStyle.alignment)
	{
		case(StyleContainment::TextAlign::Left):
			ExampleFrame->Alignment = taLeftJustify;
			break;
		case(StyleContainment::TextAlign::Right):
			ExampleFrame->Alignment = taRightJustify;
			break;
		case(StyleContainment::TextAlign::Center):
			ExampleFrame->Alignment = taCenter;
			break;
	}

	std::unique_ptr <TPanel> tempPanel {new TPanel (this)};
	readStyles(
		tempPanel.get(),
		styleSheet,
		hierarchy,
		{
			readFontStyles <TPanel>,
			readBackgroundStyles <TPanel>,
			readTextAlignment <TPanel>
		}
	);

	// DIRTY TRICK START
	if (tempPanel->Color == baseStyle.background)
		baseStyle.background = static_cast <TColor>(~baseStyle.background);
	if (tempPanel->Font->Color == baseStyle.fontColor)
		baseStyle.fontColor = static_cast <TColor>(~baseStyle.fontColor);
	if (tempPanel->Font->Size == baseStyle.fontSize)
		baseStyle.fontSize = ~tempPanel->Font->Size;

	switch (tempPanel->Alignment)
	{
		case (taLeftJustify):
			if (baseStyle.alignment == StyleContainment::TextAlign::Left)
				baseStyle.alignment = StyleContainment::TextAlign::Invalid;
			break;
		case (taCenter):
			if (baseStyle.alignment == StyleContainment::TextAlign::Center)
				baseStyle.alignment = StyleContainment::TextAlign::Invalid;
			break;
		case (taRightJustify):
			if (baseStyle.alignment == StyleContainment::TextAlign::Right)
				baseStyle.alignment = StyleContainment::TextAlign::Invalid;
			break;
	}
	if (tempPanel->Font->Style.Contains(fsItalic) && StyleContainment::FontStyle::Italic == baseStyle.fontStyle)
		baseStyle.fontStyle = StyleContainment::FontStyle::Normal;
	if (tempPanel->Font->Style.Contains(fsBold) && StyleContainment::FontWeight::Bold == baseStyle.fontWeight)
		baseStyle.fontWeight = StyleContainment::FontWeight::Normal;
	// DIRTY TRICK STOP

	switch (ExampleFrame->Alignment)
	{
		case (taLeftJustify):
			Alignment->ItemIndex = 0;
			break;
		case (taCenter):
			Alignment->ItemIndex = 1;
			break;
		case (taRightJustify):
			Alignment->ItemIndex = 2;
			break;
	}

	ItalicState->Checked = ExampleFrame->Font->Style.Contains(fsItalic);
	BoldState->Checked = ExampleFrame->Font->Style.Contains(fsBold);

    FontSize->Value = ExampleFrame->Font->Size;

	ShowModal();

	if (abort_)
		return boost::none;
	std::string result;

	// background
	auto bgColor = WretchedCss::ValueTypes::Color{
		static_cast <uint8_t> (ExampleFrame->Color & 0x0000FF),
		static_cast <uint8_t> ((ExampleFrame->Color & 0x00FF00) >> 8u),
		static_cast <uint8_t> ((ExampleFrame->Color & 0xFF0000) >> 16u),
		0.
	};
	if (ExampleFrame->Color != baseStyle.background)
		result += "background-color: " + bgColor.toString() + "; ";

	// font color
	auto fgColor = WretchedCss::ValueTypes::Color{
		static_cast <uint8_t> (ExampleFrame->Font->Color & 0x0000FF),
		static_cast <uint8_t> ((ExampleFrame->Font->Color & 0x00FF00) >> 8u),
		static_cast <uint8_t> ((ExampleFrame->Font->Color & 0xFF0000) >> 16u),
		0.
	};
	if (ExampleFrame->Font->Color != baseStyle.fontColor)
		result += "color: " + fgColor.toString() + "; ";

	// font size
	if (ExampleFrame->Font->Size != baseStyle.fontSize)
		result += std::string{"font-size: "} + std::to_string(ExampleFrame->Font->Size) + "px; ";

	// bold
	if (ExampleFrame->Font->Style.Contains(fsBold) != (StyleContainment::FontWeight::Bold == baseStyle.fontWeight) &&
		ExampleFrame->Font->Style.Contains(fsBold))
		result += std::string{"font-weight: bold; "};

	// italic
	if (ExampleFrame->Font->Style.Contains(fsItalic) != (StyleContainment::FontStyle::Italic == baseStyle.fontStyle) &&
		ExampleFrame->Font->Style.Contains(fsItalic))
		result += "font-style: italic; ";

	// alignment
	switch (Alignment->ItemIndex)
	{
		case(0): // Left
		{
			if (baseStyle.alignment != StyleContainment::TextAlign::Left)
				result += "text-align:left; ";
			break;
		}
		case(1): // Center
		{
			if (baseStyle.alignment != StyleContainment::TextAlign::Center)
				result += "text-align:center; ";
			break;
		}
		case(2): // Right
		{
			if (baseStyle.alignment != StyleContainment::TextAlign::Right)
				result += "text-align:right; ";
			break;
		}
    }

	if (!result.empty())
		result.pop_back();

	return result;
}
//---------------------------------------------------------------------------
void __fastcall TFrameStylePicker::Button2Click(TObject *Sender)
{
	abort_ = false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrameStylePicker::Button1Click(TObject *Sender)
{
	abort_ = true;
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TFrameStylePicker::FontSizeChange(TObject *Sender)
{
	ExampleFrame->Font->Size = FontSize->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFrameStylePicker::FormCreate(TObject *Sender)
{
	FontSize->Value = ExampleFrame->Font->Size;
}
//---------------------------------------------------------------------------

void __fastcall TFrameStylePicker::AlignmentChange(TObject *Sender)
{
	 switch (Alignment->ItemIndex)
	{
		case(0): // Left
		{
			ExampleFrame->Alignment = taLeftJustify;
			break;
		}
		case(1): // Center
		{
			ExampleFrame->Alignment = taCenter;
			break;
		}
		case(2): // Right
		{
			ExampleFrame->Alignment = taRightJustify;
			break;
		}
	}
}
//---------------------------------------------------------------------------

