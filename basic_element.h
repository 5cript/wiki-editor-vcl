//---------------------------------------------------------------------------
#pragma once

#include "utilities.h"
#include "forward_declarations.h"
#include "wretched-css/style_sheet.hpp"

#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <string>
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
        virtual BoundingBox getRenderedBox() const = 0;
		virtual std::string getDataTypeName() const = 0;
		virtual TFrame* getOptionsFrame() = 0;
		virtual TFrame* getStyleOptionsFrame() = 0;
		virtual void remove() = 0;
		virtual void setStyle(WretchedCss::StyleSheet const& style, bool delayRealign = false) = 0;
	};
}
//---------------------------------------------------------------------------
