//---------------------------------------------------------------------------

#pragma hdrstop

#include "style_parser.h"
#include "constants.h"

//###########################################################################
WretchedCssLibrary::WretchedCssLibrary()
	: library_{WikiEditorConstants::CssParserLibrary}
	, free_buffer_{library_.get <void(char*)>("free_buffer")}
	, css_to_json_{library_.get <void(const char*, char**)>("css_to_json")}
	, json_to_css_{library_.get <void(const char*, char**)>("json_to_css")}
	, selector_to_json_{library_.get <int32_t(const char*, char**)>("selector_to_json")}
{
/*
	library_.loadSymbols();
	auto& symbols = library_.getSymbols();
	for (auto const& i : symbols)
	{
		ShowMessage(i.first.c_str());
	}
*/
}
//---------------------------------------------------------------------------
std::string WretchedCssLibrary::cssToJson(std::string const& css)
{
	char* buffer;
	css_to_json_(css.c_str(), &buffer);
	std::string json = {buffer}; // noexcept, or bad_alloc
	free_buffer_(buffer);

	return json;
}
//---------------------------------------------------------------------------
std::string WretchedCssLibrary::jsonToCss(std::string const& json)
{
	char* buffer;
	json_to_css_(json.c_str(), &buffer);
	std::string css = {buffer}; // noexcept, or bad_alloc
	free_buffer_(buffer);

	return css;
}
//---------------------------------------------------------------------------
std::string WretchedCssLibrary::selectorToJson(std::string const& selector)
{
	char* buffer;
	selector_to_json_(selector.c_str(), &buffer);
    std::string selectorJson = {buffer};
	free_buffer_(buffer);

	return selectorJson;
}
//###########################################################################
StyleParser::StyleParser()
{
}
//---------------------------------------------------------------------------
WretchedCss::StyleSheet StyleParser::parseStyleSheet(std::string const& style) const
{
    auto json = WretchedCssLibrary::getInstance().cssToJson(style);

	WretchedCss::RuleSet rules;
	try
	{
		rules.fromJson(json);
	}
	catch (std::exception const& exc)
	{
		std::string error = exc.what();
		error += "\n";
		error += json;
        throw std::runtime_error(error.c_str());
    }
    return {rules};
}
//---------------------------------------------------------------------------
std::string StyleParser::parseSelector(std::string const& selector) const
{
	return WretchedCssLibrary::getInstance().selectorToJson(selector);
}
//###########################################################################
#pragma package(smart_init)
