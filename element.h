//---------------------------------------------------------------------------
#pragma once

#include <memory>
#include <typeinfo>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>

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
		virtual TFrame* getOptionsFrame() = 0;
		virtual TFrame* getStyleOptionsFrame() = 0;
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
			, optionsFrame_{}
			, style_{}
		{
			control_->Parent = parentSection->getLayout()->getControl();
			control_->AlignWithMargins = true;
			control_->Align = alTop;
			control_->OnDragOver = onDragOver;
            control_->OnClick = onClick;
		}

		void setStyle(std::string const& style)
		{
			StyleParser parser;
            style_ = style;
            styleChanged(parser.parseStyleSheet(style), parser);
		}

		bool redraw()
		{
			/*
			static bool entered = false;
			if (entered)
			{
				// function called recursively!!!
				return false;
			}
			entered = true;
			*/

			if (style_.empty())
            	return false;

			StyleParser parser;
			styleChanged(parser.parseStyleSheet(style_), parser);

			//entered = false;
			return true;
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

		TFrame* getOptionsFrame() override
		{
			if (!optionsFrame_)
				initializeOptionsFrame();
			if (!optionsFrame_)
				return nullptr;
			return &*optionsFrame_;
		}

		TFrame* getStyleOptionsFrame() override
		{
			if (!styleOptionsFrame_)
				initializeStyleOptionsFrame();
			if (!styleOptionsFrame_)
				return nullptr;
			return &*styleOptionsFrame_;
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

		void __fastcall onClick(TObject* Sender)
		{
			parentSection_->onElementClick(Sender, this);
        }

		virtual void initializeOptionsFrame()
		{
			// this function is only initialized, so an option frame is not
			// required by any control. It is eligible to have components without it.
		}

		virtual void initializeStyleOptionsFrame()
		{
			// this function is only initialized, so a style option frame is not
			// required by any control. It is eligible to have components without it.
		}

    protected:
		Section* parentSection_;
		std::unique_ptr <UnderlyingUiElement> control_;
		DataElement data_;
		std::unique_ptr <TFrame> optionsFrame_;
		std::unique_ptr <TFrame> styleOptionsFrame_;
        std::string style_;
    };
};
//---------------------------------------------------------------------------
