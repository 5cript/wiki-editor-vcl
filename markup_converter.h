//---------------------------------------------------------------------------
#pragma once

#include "dll/dll/library.hpp"
//---------------------------------------------------------------------------
class MarkupLibrary
{
public:
	static MarkupLibrary& getInstance() {
		static MarkupLibrary inst;
		return inst;
	}

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
