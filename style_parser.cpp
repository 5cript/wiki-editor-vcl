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
{

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
//###########################################################################
StyleParser::StyleParser()
{
}
//---------------------------------------------------------------------------
WretchedCss::StyleSheet StyleParser::parseStyleSheet(std::string const& style)
{
    auto json = WretchedCssLibrary::getInstance().cssToJson(style);

	WretchedCss::RuleSet rules;
	rules.fromJson(json);
    return {rules};
}
//###########################################################################
#pragma package(smart_init)
