//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------

#include "dll/dll/library.hpp"
#include "wretched-css/style_sheet.hpp"
#include "singleton.h"

#include <cctype>

/*
DLL_DECLARE_INTERFACE
(
	WretchedCssLibrary,
	(std::function <void(char*)>, free_buffer)
	(std::function <void(const char*, char**)>, css_to_json)
	(std::function <void(const char*, char**)>, json_to_css)
)
*/

//---------------------------------------------------------------------------
SINGLETON_GLOBALS(WretchedCssLibrary)
//---------------------------------------------------------------------------
class WretchedCssLibrary : public Singleton <WretchedCssLibrary>
{
public:
	SINGLETON_GET_INSTANCE(WretchedCssLibrary)

	std::string cssToJson(std::string const& css);
	std::string jsonToCss(std::string const& json);
	std::string selectorToJson(std::string const& selector);
	std::string getLastError();

private:
	WretchedCssLibrary();

private:
	LibraryLoader::Library library_;

private:
	std::function <void(char*)> free_buffer_;
	std::function <void(const char*, char**)> css_to_json_;
	std::function <void(const char*, char**)> json_to_css_;
	std::function <int32_t(const char*, char**)> selector_to_json_;
	std::function <void(char**)> get_last_error_;
};
//---------------------------------------------------------------------------
class StyleParser
{
public:
	StyleParser();

	WretchedCss::StyleSheet parseStyleSheet(std::string const& style) const;
	std::string parseSelector(std::string const& selector) const;
};
//---------------------------------------------------------------------------
