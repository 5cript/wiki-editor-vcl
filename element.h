//---------------------------------------------------------------------------
#pragma once

#include "section.h"
#include "padding_control.h"
#include "viewport.h"
#include "layout.h"
#include "basic_element.h"

#include "wretched-css/style_sheet.hpp"

#include <Vcl.Dialogs.hpp>

#include <memory>
#include <typeinfo>
//---------------------------------------------------------------------------
namespace WikiElements
{
	template <typename Derivative, typename UnderlyingUiElement, typename DataElement>
	class Element : public BasicElement
	{
	public:
		using control_type = UnderlyingUiElement;
		using data_type = DataElement;
		using this_type = Derivative;
        using element_type = Element <this_type, control_type, data_type>;

	public:
		Element(Section* parentSection)
			: parentSection_{parentSection}
			, control_{new UnderlyingUiElement(parentSection->getLayout()->getControl())}
			, data_{}
			, optionsFrame_{}
			, parsedStyle_{}
		{
			control_->Parent = parentSection->getLayout()->getControl();
			control_->AlignWithMargins = true;
			control_->Align = alTop;
			control_->OnDragOver = onDragOver;
            control_->OnClick = onClick;
		}

		~Element()
		{
        }

		void setStyle(WretchedCss::StyleSheet const& style)
		{
			parsedStyle_ = style;
            styleChanged(parsedStyle_);
        }

		virtual bool redraw()
		{
			static bool entered = false;

			struct EnterReset
			{
				bool& entered_;
				EnterReset(bool& entered)
					: entered_ {entered}
				{
					if (entered)
						throw std::logic_error("redraw called recursively");
					entered_ = true;
				}
				~EnterReset()
				{
					entered_ = false;
				}
			};
			auto recursionDetector = EnterReset{entered};


			static_cast <this_type*> (this)->writeModelToUserInterface();

			if (!parsedStyle_.empty())
			{
				styleChanged(parsedStyle_);
				return false;
			}
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

		DataElement* getDataHandle()
		{
			return &data_;
		}

		virtual void setData(DataElement const& data)
		{
			data_ = data;
			redraw();
		}

		BoundingBox getRenderedBox() const
		{
			auto xy = control_->ClientToScreen(Point(0,0));
			return {
				xy.X,
				xy.Y,
				xy.X + control_->Width,
                xy.Y + control_->Height
            };
        }

		virtual void writeModelToUserInterface()
		{
			// An element does not necessarly have a model.
			// Therfore not overriding this is a viable option.
        }

	protected:

		virtual void styleChanged(WretchedCss::StyleSheet const& style) = 0;

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
			// this function body is only given, so an option frame is not
			// required by any control. It is eligible to have components without it.
		}

		virtual void initializeStyleOptionsFrame()
		{
			// this function body is only given, so a style option frame is not
			// required by any control. It is eligible to have components without it.
		}

    protected:
		Section* parentSection_;
		std::unique_ptr <UnderlyingUiElement> control_;
		DataElement data_;
		std::unique_ptr <TFrame> optionsFrame_;
		std::unique_ptr <TFrame> styleOptionsFrame_;
		WretchedCss::StyleSheet parsedStyle_;
    };
};
//---------------------------------------------------------------------------
