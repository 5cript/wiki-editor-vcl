//---------------------------------------------------------------------------

#pragma hdrstop

#include "markup_converter.h"
#include "constants.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

SINGLETON_GLOBALS_DECLARATION(MarkupLibrary)
//---------------------------------------------------------------------------
MarkupLibrary::MarkupLibrary()
	: library_{WikiEditorConstants::MarkupLibrary}
	, free_buffer_{library_.get<void(char*)>("free_buffer")}
	, markup_to_json_{library_.get<void(const char*, char**)>("markup_to_json")}
	, json_to_markup_{library_.get<void(const char*, char**)>("json_to_markup")}
{

}
//---------------------------------------------------------------------------
std::string MarkupLibrary::markupToJson(std::string const& markup)
{
	char* buffer;
	markup_to_json_(markup.c_str(), &buffer);
	std::string json = std::string{buffer}; // noexcept, or bad_alloc
	free_buffer_(buffer);

	return json;
}
//---------------------------------------------------------------------------
std::string MarkupLibrary::jsonToMarkup(std::string const& json)
{
 	char* buffer;
	json_to_markup_(json.c_str(), &buffer);
	std::string markup = std::string{buffer}; // noexcept, or bad_alloc
	free_buffer_(buffer);

	return markup;
}
//---------------------------------------------------------------------------
