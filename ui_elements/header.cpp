//---------------------------------------------------------------------------

#pragma hdrstop

#include "header.h"

#include "frames/header_options.h"
#include "style_applicator.h"

#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace WikiElements
{
	constexpr auto UnderlinePadding = 0;
//---------------------------------------------------------------------------
	Header::Header(Section* parentSection)
		: Element{parentSection}
		, textbox_{new TEdit(control_.get())}
		, underline_{new TPanel(control_.get())}
		, deleteCounter_{0}
	{
        auto* parent = parentSection->getLayout()->getControl();
		//applyDefaultMargins(wrapper_->Margins);

		// Init Model
		setText("ABC");
		setLevel(2);

		// Parenting
		underline_->Parent = control_.get();
		textbox_->Parent = control_.get();

		// Style
		//control_->ParentBackground = false;
		//control_->Color = clLime;
		control_->BorderStyle = bsNone;
		control_->BevelOuter = bvNone;
		textbox_->Color = clWhite;
		textbox_->BorderStyle = bsNone;

		underline_->ParentBackground = false;
		underline_->Color = clGray;
		underline_->BorderStyle = bsNone;
		underline_->BevelOuter = bvNone;
		//underline_->Hide();

		// Events
		textbox_->OnChange = onTextChange;
		textbox_->OnKeyUp = onKeyUp;
		textbox_->OnClick = onClick;
		underline_->OnClick = onClick;
        control_->OnResize = onResize;

		// Positioning
		textbox_->Left = 0;
		textbox_->Width = parent->Width - leftSectionPadding - rightSectionPadding;
		control_->Left = 0;
		control_->Width = parent->Width - leftSectionPadding - rightSectionPadding;

		underline_->Top = textbox_->Top + textbox_->Height + UnderlinePadding;
		underline_->Width = textbox_->Width; // FIXME: get this dynamic.
		underline_->Height = 1;
	}
//---------------------------------------------------------------------------
	void __fastcall Header::onResize(TObject* Sender)
	{
		underline_->Width = control_->Width;
		textbox_->Width = control_->Width - rightSectionPadding - leftSectionPadding;
    }
//---------------------------------------------------------------------------
	void __fastcall Header::onTextChange(TObject* Sender)
	{
		data_.data = UTF8String(textbox_->Text).c_str();
		parentSection_->makeDirty();
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
		underline_->Top = control_->Top + control_->Height + UnderlinePadding;
	}
//---------------------------------------------------------------------------
	void Header::realignAfter(int position) const
	{
		Element::realignAfter(position);
		underline_->Top = control_->Top + control_->Height + UnderlinePadding;
	}
//---------------------------------------------------------------------------
	void Header::setLevel(int level)
	{
		data_.level = level;
		redraw();
	}
//---------------------------------------------------------------------------
	int Header::getLevel() const
	{
		return data_.level;
	}
//---------------------------------------------------------------------------
	void Header::setText(std::string const& text)
	{
		data_.data = text;
        writeModelToUserInterface();
	}
//---------------------------------------------------------------------------
	std::string const& Header::getText() const
	{
		return data_.data;
    }
//---------------------------------------------------------------------------
	void Header::styleChanged(WretchedCss::StyleSheet const& style, bool delayRealign)
	{
		auto hierarchy = StyleHierarchy{};
		hierarchy << "body"
				  << ".header"
				  << ".header h"_s + boost::lexical_cast <std::string> (data_.level)
		;

		readStyles(
			&*textbox_,
			style,
			hierarchy,
			{
				readFontStyles <TEdit>,
				readBackgroundStyles <TEdit>
			}
		);

		textbox_->Height = getRenderedFontHeight(textbox_->Font) + 2;
		control_->Height = getRenderedFontHeight(textbox_->Font) + 2;
		auto REMOVE_ME = control_->Font->Size;

		if (data_.level == 2 || data_.level == 3)
		{
			underline_->Top = textbox_->Top + textbox_->Height + UnderlinePadding;
			control_->Height += underline_->Height + underline_->Height + UnderlinePadding;
			underline_->Show();
		}
		else
			underline_->Hide();

		if (!delayRealign)
			parentSection_->causePageRealign();
	}
//---------------------------------------------------------------------------
	BoundingBox Header::getBoundingBox() const
	{
		return {
			control_->Top,
			control_->Left,
			control_->Width + control_->Left,
			(data_.level > 3)?(control_->Height + control_->Top):(underline_->Height + underline_->Top)
		};
	}
//---------------------------------------------------------------------------
	BoundingBox Header::getRenderedBox() const
	{
		auto textBoxXY = control_->ClientToScreen(Point(0,0));
		auto lineXY = underline_->ClientToScreen(Point(0,0));
		return {
			textBoxXY.X,
			textBoxXY.Y,
			lineXY.X + underline_->Width,
			lineXY.Y + underline_->Height
		};
	}
//---------------------------------------------------------------------------
	void Header::initializeOptionsFrame()
	{
		optionsFrame_.reset(new THeaderOptionsFrame(nullptr));
        static_cast <THeaderOptionsFrame*> (&*optionsFrame_)->setOwner(this);
	}
//---------------------------------------------------------------------------
	void Header::writeModelToUserInterface()
	{
        textbox_->Text = data_.data.c_str();
    }
//---------------------------------------------------------------------------
}