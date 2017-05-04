//---------------------------------------------------------------------------
#pragma once

#include "wretched-css/rule_set/rule/property/value/numerical.hpp"

#include <boost/optional.hpp>

#include <string>
//---------------------------------------------------------------------------
namespace WikiElements
{
	/**
	 *  Unspecified =
	 *      Within encompassing text block.
	 *		Text starts above image and everything after image is to the left,
	 *		as much as fits and then continues after the image.
     *		(Image is embedded within one line)
	 *
	 *	None =
	 *      Image is to the left and splits the text.
	 *
	 *  Center =
	 *		Image is in the center and splits the text.
	 *		(no text left or right of the image)
	 *
	 *  Left =
	 *      Image is left and text is right.
	 *
	 *	Right =
	 *		Image is right and text is left.
	 */
	enum class ImageAlignment
	{
		Unspecified,
		None,
		Center,
		Left,
		Right
	};

    // https://www.mediawiki.org/wiki/Help:Images#Format
	enum class ImageFormat
	{
		Unspecified,
		Border,
		Frameless,
		FramelessBorder,
		Frame,  // implicit right
		Thumb	// implicit right
	};

	enum class VerticalImageAlignment
	{
		Baseline,
		Sub,
		Super,
		Top,
		TextTop, // text-top
		Middle,
		Bottom,
        TextBottom // text-bottom
    };

	struct ImageAttributes
	{
		boost::optional <WretchedCss::ValueTypes::NumericValue> size;
		boost::optional <ImageAlignment> alignment;
		boost::optional <VerticalImageAlignment> verticalAlignment; // unrendered?
		boost::optional <std::string> page; // unrendered
		boost::optional <std::string> class_; // unrendered
		boost::optional <std::string> lang; // unrendered
		boost::optional <std::string> alt; // unrendered?
        boost::optional <std::string> link; // empty is valid
    };
}
//---------------------------------------------------------------------------
