//---------------------------------------------------------------------------
#pragma once

#include <memory>
#include <Vcl.ExtCtrls.hpp>

#include "../section.h"
#include "../padding_control.h"
#include "../utilities.h"
#include "../style_parser.h"

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
	};

	using ElementContainer = TScrollBox;

	template <typename Derivative, typename UnderlyingUiElement, typename DataElement>
	class Element : public BasicElement
	{
	public:
		using control_type = UnderlyingUiElement;
		using data_type = DataElement;
		using this_type = Derivative;

	public:
		Element(ElementContainer* parent, Section* parentSection)
			: parentSection_{parentSection}
			, control_{new UnderlyingUiElement(parent)}
			, data_{}
		{
			control_->Parent = parent;
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

	protected:
		DataElement* getDataHandle()
		{
			return &data_;
		}

		virtual void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser) = 0;

    protected:
		Section* parentSection_;
		std::unique_ptr <UnderlyingUiElement> control_;
		DataElement data_;
    };
};
//---------------------------------------------------------------------------
