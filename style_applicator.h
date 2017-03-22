//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "wretched-css/style_sheet.hpp"
#include "literals.h"

#include "wretched-css/rule_set/rule/property/value/keyword.hpp"
#include "wretched-css/rule_set/rule/property/value/numerical.hpp"
#include "wretched-css/rule_set/rule/property/value/dimensionless.hpp"
#include "wretched-css/rule_set/rule/property/value/string.hpp"
#include "wretched-css/rule_set/rule/property/value/url.hpp"
#include "wretched-css/rule_set/rule/property/value/point.hpp"
#include "wretched-css/rule_set/rule/property/value/color.hpp"

#include "debug.h"

#include <Vcl.Graphics.hpp>

#include <vector>
#include <string>
#include <functional>
//---------------------------------------------------------------------------
class StyleHierarchy
{
public:
	StyleHierarchy() = default;
	~StyleHierarchy();

	template <typename StringT>
	friend StyleHierarchy& operator<<(StyleHierarchy& thi, StringT&& selector)
	{
		//thi.selectors_.push_back(std::forward <StringT&&> (selector));
		thi.selectors_.push_back(selector);
		return thi;
	}

	std::string getTop();
	void pop();
    std::string popTop();
private:
	std::vector <std::string> selectors_;
};
//---------------------------------------------------------------------------
boost::optional <unsigned int> extractSize(
	WretchedCss::StyleSheet const& style,
	WretchedCss::Property const* property
);
//---------------------------------------------------------------------------
boost::optional <std::string> extractString(
	WretchedCss::StyleSheet const& style,
	WretchedCss::Property const* property
);
//---------------------------------------------------------------------------
boost::optional <WretchedCss::ValueTypes::Color> extractColor(
	WretchedCss::StyleSheet const& style,
	WretchedCss::Property const* property
);
//---------------------------------------------------------------------------
WretchedCss::Style constructCascade(
	WretchedCss::StyleSheet const& sheet,
	StyleHierarchy hierarchy
);
//---------------------------------------------------------------------------
template <typename T>
void readStyles(T* control,
				WretchedCss::StyleSheet const& sheet,
				StyleHierarchy const& hierarchy,
				std::vector <std::function <void (T*,
												  WretchedCss::StyleSheet const&,
												  StyleHierarchy const&)>> const& functions
)
{
	for (auto const& f : functions)
	{
        f(control, sheet, hierarchy);
    }
}
//---------------------------------------------------------------------------
template <typename T>
void readFontStyles(T* control, WretchedCss::StyleSheet const& sheet, StyleHierarchy const& hierarchy)
{
	// build style cascade from style hierarchy.
	auto rule = constructCascade(sheet, hierarchy).getCombined();

	auto fontFamily = extractString(sheet, rule["font-family"]);
	if (fontFamily)
	{
		DebugOut(fontFamily.get());
	}

	auto fontSize = extractSize(sheet, rule["font-size"]);
	if (fontSize)
		control->Font->Size = fontSize.get();

	control->Font->Style = TFontStyles{};
	auto fontWeight = extractString(sheet, rule["font-weight"]);
	if (fontWeight)
	{
		if (fontWeight.get() == "bold")
			control->Font->Style = control->Font->Style << fsBold;
	}

	auto fontStyle = extractString(sheet, rule["font-style"]);
	if (fontStyle)
	{
		if (fontWeight.get() == "italic")
			control->Font->Style = control->Font->Style << fsItalic;
	}

	auto fontColor = extractColor(sheet, rule["color"]);
	if (fontColor)
		control->Font->Color = TColor(fontColor.get().toInt());
}
//---------------------------------------------------------------------------
template <typename T>
void readBackgroundStyles(T* control, WretchedCss::StyleSheet const& sheet, StyleHierarchy const& hierarchy)
{
	auto rule = constructCascade(sheet, hierarchy).getCombined();

	auto backgroundColor = extractColor(sheet, rule["background-color"]);
	if (backgroundColor)
		control->Color = TColor(backgroundColor.get().toInt());
}
//---------------------------------------------------------------------------
template <typename T>
void readSizes(T* control, WretchedCss::StyleSheet const& sheet, StyleHierarchy const& hierarchy)
{
	auto rule = constructCascade(sheet, hierarchy).getCombined();

	auto height = extractSize(sheet, rule["height"]);
	if (height)
		control->Height = height.get();

	auto width = extractSize(sheet, rule["width"]);
	if (width)
		control->Width = width.get();
}
//---------------------------------------------------------------------------
