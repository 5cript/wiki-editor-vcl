//---------------------------------------------------------------------------
#pragma once

#include <memory>
#include <Vcl.ExtCtrls.hpp>

#include "utilities.h"

#include "style_parser.h"
#include "wretched-css/style_sheet.hpp"
//---------------------------------------------------------------------------
namespace WikiElements
{
	class BasicElement
	{
	public:
    	virtual ~BasicElement() = default;

		virtual BoundingBox getBoundingBox() const = 0;
	};

	using ElementContainer = TScrollBox;

	template <typename Derivative, typename UnderlyingUiElement, typename DataElement>
	class Element : public BasicElement
	{
	public:
		Element(ElementContainer* parent)
			: control_{new UnderlyingUiElement(parent)}
			, data_{}
		{
			control_->Parent = parent;
		}

		void setStyle(std::string const& style)
		{
			StyleParser parser;
            styleChanged(parser.parseStyleSheet(style), parser);
		}

	protected:
		DataElement* getDataHandle()
		{
			return &data_;
		}

		virtual void styleChanged(WretchedCss::StyleSheet const& style, StyleParser const& parser) = 0;

    protected:
		std::unique_ptr <UnderlyingUiElement> control_;
		DataElement data_;
    };
};
//---------------------------------------------------------------------------
