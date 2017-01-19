//---------------------------------------------------------------------------
#pragma once

#include "dll/dll/library.hpp"
#include "singleton.h"
//---------------------------------------------------------------------------
SINGLETON_GLOBALS(MarkupLibrary)
class MarkupLibrary : public Singleton <MarkupLibrary>
{
public:
	SINGLETON_GET_INSTANCE(MarkupLibrary)

	std::string markupToJson(std::string const& markup);
    std::string jsonToMarkup(std::string const& json);

private:
	MarkupLibrary();

private:
	LibraryLoader::Library library_;

private:
	std::function <void(char*)> free_buffer_;
	std::function <void(const char*, char**)> markup_to_json_;
	std::function <void(const char*, char**)> json_to_markup_;
};
