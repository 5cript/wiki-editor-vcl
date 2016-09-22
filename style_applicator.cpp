//---------------------------------------------------------------------------

#pragma hdrstop

#include "style_applicator.h"
#include "style_parser.h"

#include <algorithm>
#include <iterator>
//###########################################################################
std::string StyleHierarchy::getTop()
{
	return (!selectors_.empty()) ? selectors_.back() : "";
}
//---------------------------------------------------------------------------
void StyleHierarchy::pop()
{
	selectors_.pop_back();
	/*
	decltype(selectors_) temp;
	std::copy(selectors_.begin(), selectors_.end() - 1, std::back_inserter(temp));
	selectors_ = temp;
	*/
}
//---------------------------------------------------------------------------
std::string StyleHierarchy::popTop()
{
	auto temp = getTop();
	if (temp != "")
		pop();
	return temp;
}
//---------------------------------------------------------------------------
StyleHierarchy::~StyleHierarchy()
{
}
//###########################################################################
boost::optional <unsigned int> extractSize(
	WretchedCss::StyleSheet const& style,
	WretchedCss::Property const* property
)
{
    if (property != nullptr && !property->values.empty())
	{
		// 1em default
		unsigned int size = /* style.getPxPerEm() */ 2;

		auto* value = static_cast <WretchedCss::ValueTypes::NumericValue*> (property->values[0].get());
		if (value->unit == WretchedCss::ValueTypes::Unit::em)
			size = style.getPxPerEm() * value->value;
		else if (value->unit == WretchedCss::ValueTypes::Unit::px)
			size = value->value;


		return {size};
	}
	return boost::none;
}
//---------------------------------------------------------------------------
boost::optional <WretchedCss::ValueTypes::Color> extractColor(
	WretchedCss::StyleSheet const& style,
	WretchedCss::Property const* property
)
{
	if (property != nullptr && !property->values.empty())
	{
		auto* value = static_cast <WretchedCss::ValueTypes::Color*> (property->values[0].get());
		return {*value};
	}
	return boost::none;
}
//---------------------------------------------------------------------------
boost::optional <std::string> extractString(
	WretchedCss::StyleSheet const& style,
	WretchedCss::Property const* property
)
{
	if (property != nullptr && !property->values.empty())
	{
		auto* value = static_cast <WretchedCss::ValueTypes::StringValue*> (property->values[0].get());
		return {value->value};
	}
	return boost::none;
}
//---------------------------------------------------------------------------
WretchedCss::Style constructCascade(
	WretchedCss::StyleSheet const& sheet,
	StyleHierarchy hierarchy
)
{
	StyleParser parser;
    WretchedCss::Style style;

	do {
		auto currentSelector = hierarchy.popTop();
		if (currentSelector == "")
			break;
		auto maybeStyle = sheet.select(parser.parseSelector(currentSelector));
		if (maybeStyle)
		{
			style = maybeStyle.get();
			break;
		}
	} while (true);

	for (std::string selector; !(selector = hierarchy.popTop()).empty();)
	{
		auto maybeStyle = sheet.select(parser.parseSelector(selector));
		if (maybeStyle)
		{
			auto curStyle = maybeStyle.get();
			style = {style.derive(&curStyle).getCombined()};
		}
	}
	return style;
}
//###########################################################################
#pragma package(smart_init)
