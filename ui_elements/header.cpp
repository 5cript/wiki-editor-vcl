//---------------------------------------------------------------------------

#pragma hdrstop

#include "header.h"

#include "wretched-css/rule_set/rule/property/value/keyword.hpp"
#include "wretched-css/rule_set/rule/property/value/numerical.hpp"
#include "wretched-css/rule_set/rule/property/value/dimensionless.hpp"
#include "wretched-css/rule_set/rule/property/value/string.hpp"
#include "wretched-css/rule_set/rule/property/value/url.hpp"
#include "wretched-css/rule_set/rule/property/value/point.hpp"
#include "wretched-css/rule_set/rule/property/value/color.hpp"

#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace WikiElements
{
//---------------------------------------------------------------------------
	Header::Header(ElementContainer* parent, Section* parentSection)
		: Element{parent}
		, underline_{new TPanel(parent)}
		, parentSection_{parentSection}
	{
		setText(data_.data);

		// control_->Font->Name = "Courier";
		control_->Left = leftSectionPadding;
		control_->Color = clWhite;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		control_->Height = 10;
		control_->Top = parentSection->getMostBottom() + sectionSplitPadding;
		control_->BorderStyle = bsNone;
		control_->OnChange = this->onTextChange;

		underline_->Height = 1;
		underline_->Left = leftSectionPadding;
		underline_->Color = clGray;
		underline_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		underline_->Parent = parent;
		underline_->Hide();
	}
//---------------------------------------------------------------------------
	void __fastcall Header::onTextChange(TObject* Sender)
	{
		data_.data = UTF8String(control_->Text).c_str();
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
		return UTF8String(control_->Text).c_str();
    }
//---------------------------------------------------------------------------
	void Header::styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser)
	{
		std::string soughtSelector = ".header";
		if (data_.level > 1)
			soughtSelector += " h" + boost::lexical_cast <std::string> (data_.level);
		auto maybeStyle = style.select(parser.parseSelector(soughtSelector));
		if (maybeStyle)
		{
			auto rule = maybeStyle.get().getCombined();

			auto* property = rule["font-size"];
			if (property != nullptr && !property->values.empty())
			{
            	// 1em default
				unsigned int fontSize = /* style.getPxPerEm() */ 2;

				auto* value = static_cast <WretchedCss::ValueTypes::NumericValue*> (property->values[0].get());
				if (value->unit == WretchedCss::ValueTypes::Unit::em)
					fontSize = style.getPxPerEm() * value->value;
				else if (value->unit == WretchedCss::ValueTypes::Unit::px)
					fontSize = value->value;

				control_->Font->Size = fontSize;
				control_->Height = fontSize + 5;
			}

			if ((property = rule["font-weight"]) != nullptr && !property->values.empty())
			{
				auto* value = static_cast <WretchedCss::ValueTypes::StringValue*> (property->values[0].get());
				if (value->value == "bold")
					control_->Font->Style = control_->Font->Style << fsBold;
			}
		}

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