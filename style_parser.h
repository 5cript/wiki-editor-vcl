//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "dll/dll/library.hpp"
#include "wretched-css/style_sheet.hpp"

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
class WretchedCssLibrary
{
public:
	static WretchedCssLibrary& getInstance() {
		static WretchedCssLibrary inst;
		return inst;
	}

	std::string cssToJson(std::string const& css);
	std::string jsonToCss(std::string const& json);

private:
	WretchedCssLibrary();

	std::function <void(char*)> free_buffer_;
	std::function <void(const char*, char**)> css_to_json_;
	std::function <void(const char*, char**)> json_to_css_;

private:
	LibraryLoader::Library library_;
};
//---------------------------------------------------------------------------
class StyleParser
{
public:
	StyleParser();

	WretchedCss::StyleSheet parseStyleSheet(std::string const& style);
};
//---------------------------------------------------------------------------
