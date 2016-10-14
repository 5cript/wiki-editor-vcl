//---------------------------------------------------------------------------
#pragma once

#include <memory>
#include <typeinfo>
#include <Vcl.ExtCtrls.hpp>

#include "section.h"
#include "padding_control.h"
#include "utilities.h"
#include "style_parser.h"
#include "viewport.h"
#include "layout.h"

#include "wretched-css/style_sheet.hpp"
//---------------------------------------------------------------------------
namespace WikiElements
{
	class BasicElement
	{
	public:
    	virtual ~BasicElement() = default;

		virtual BoundingBox getBoundingBox() const = 0;
		virtual void realignAfter(BasicElement* element) const = 0;
		virtual void realignAfter(int position) const = 0;
		virtual void moveDown(int pixels) = 0;
		virtual void moveUp(int pixels) = 0;
		virtual long getHeight() const = 0;
		virtual long getWidth() const = 0;
		virtual TControl* getBasicControl() = 0;
		virtual std::string getDataTypeName() const = 0;
	};

	template <typename Derivative, typename UnderlyingUiElement, typename DataElement>
	class Element : public BasicElement
	{
	public:
		using control_type = UnderlyingUiElement;
		using data_type = DataElement;
		using this_type = Derivative;

	public:
		Element(Section* parentSection)
			: parentSection_{parentSection}
			, control_{new UnderlyingUiElement(parentSection->getLayout()->getControl())}
			, data_{}
		{
			control_->Parent = parentSection->getLayout()->getControl();
			control_->AlignWithMargins = true;
			control_->Align = alTop;
			control_->OnDragOver = onDragOver;
		}

		void setStyle(std::string const& style)
		{
			StyleParser parser;
            styleChanged(parser.parseStyleSheet(style), parser);
		}

		void realignAfter(BasicElement* element) const override
		{
			control_->Top = element->getBoundingBox().bottom + sectionSplitPadding;
		}

		void realignAfter(int position) const override
		{
			control_->Top = position + sectionSplitPadding;
		}

		long getHeight() const
		{
			return control_->Height;
		}

		long getWidth() const
		{
			return control_->Width;
		}

		void remove()
		{
            parentSection_->removeElement(this);
		}

		BoundingBox getBoundingBox() const override
		{
			return {
				control_->Top,
				control_->Left,
				control_->Left + control_->Width,
				control_->Top + control_->Height
			};
		}

		virtual void moveDown(int pixels)
		{
			control_->Top += pixels;
		}

		virtual void moveUp(int pixels)
		{
			control_->Top -= pixels;
		}

		UnderlyingUiElement* getControl()
		{
            return &*control_;
		}

		TControl* getBasicControl() override
		{
            return getControl();
		}

		std::string getDataTypeName() const override
		{
            return {typeid(DataElement).name()};
        }

	protected:
		DataElement* getDataHandle()
		{
			return &data_;
		}

		virtual void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser) = 0;

		void __fastcall onDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
		{
			parentSection_->onDragOver(Sender, Source, X + control_->Left,Y + control_->Top, State, Accept);
        }

    protected:
		Section* parentSection_;
		std::unique_ptr <UnderlyingUiElement> control_;
		DataElement data_;
    };
};
//---------------------------------------------------------------------------
