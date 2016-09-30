//---------------------------------------------------------------------------

#pragma hdrstop

#include "header.h"

#include "style_applicator.h"

#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace WikiElements
{
//---------------------------------------------------------------------------
	Header::Header(Section* parentSection)
		: Element{parentSection}
		, underline_{new TPanel(parentSection->getLayout()->getControl())}
		, deleteCounter_{0}
	{
        auto* parent = parentSection->getLayout()->getControl();
		//applyDefaultMargins(wrapper_->Margins);

		setText(data_.data);
		//underline_->Parent = parent;

		// Style
		control_->Color = clWhite;
		control_->BorderStyle = bsNone;

		underline_->Color = clGray;
		underline_->Hide();
		underline_->Width = 1000; // FIXME: get this dynamic.

		// Events
		control_->OnChange = this->onTextChange;
		control_->OnKeyUp = this->onKeyUp;

		// Positioning
		control_->Left = 0;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;

		// control_->Font->Name = "Courier";
		//control_->Left = leftSectionPadding;
		//control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		//control_->Height = 10;
		//control_->Top = parentSection->getMostBottom() + sectionSplitPadding;

		//underline_->Top = control_->Top + control_->Height + 3;
		//underline_->Height = 1;
		//underline_->Left = leftSectionPadding;
		//underline_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
	}
//---------------------------------------------------------------------------
	void __fastcall Header::onTextChange(TObject* Sender)
	{
		data_.data = UTF8String(control_->Text).c_str();
	}
//---------------------------------------------------------------------------
	void __fastcall Header::onKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
	{
		if (data_.data.empty() && (Key == vkBack || Key == vkDelete))
		{
			deleteCounter_++;
			//if (deleteCounter_ > 2)
			//	remove();
		}
		else if (!data_.data.empty())
		{
			deleteCounter_ = 0;
        }
    }
//---------------------------------------------------------------------------
	void Header::realignAfter(BasicElement* element) const
	{
		Element::realignAfter(element);
		underline_->Top = control_->Top + control_->Height + 3;
	}
//---------------------------------------------------------------------------
	void Header::realignAfter(int position) const
	{
		Element::realignAfter(position);
		underline_->Top = control_->Top + control_->Height + 3;
	}
//---------------------------------------------------------------------------
	void Header::setLevel(int level)
	{
        data_.level = level;
	}
//---------------------------------------------------------------------------
	int Header::getLevel() const
	{
		return data_.level;
	}
//---------------------------------------------------------------------------
	void Header::setText(std::string const& text)
	{
        control_->Text = text.c_str();
	}
//---------------------------------------------------------------------------
	std::string const& Header::getText() const
	{
		return std::string{UTF8String(control_->Text).c_str()};
    }
//---------------------------------------------------------------------------
	void Header::styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
	{
		auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".header"
				  << ".header h"_s + boost::lexical_cast <std::string> (data_.level)
		;

		readStyles(
			&*control_,
			style,
			hierarchy,
			{
				readFontStyles <control_type>,
				readBackgroundStyles <control_type>
			}
		);

		control_->Height = control_->Font->Size + 5;

		if (data_.level == 1 || data_.level == 2)
		{
			underline_->Show();
			underline_->Top = control_->Top + control_->Height + 3;
		}
		else
			underline_->Hide();
	}
//---------------------------------------------------------------------------
	BoundingBox Header::getBoundingBox() const
	{
		return {
			control_->Top,
			control_->Left,
			control_->Width + control_->Left,
			(data_.level > 2)?(control_->Height + control_->Top):(underline_->Height + underline_->Top)
		};
    }
//---------------------------------------------------------------------------
}