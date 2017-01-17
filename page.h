//---------------------------------------------------------------------------
#pragma once

#include "section.h"

#include "wiki-markup/exportable_page.hpp"

#include <vector>
//---------------------------------------------------------------------------
class WikiPage : public WikiMarkup::ExportablePage
{
public:
	void fromMarkup(std::string const& markup);
	std::string toMarkup();
};
//---------------------------------------------------------------------------

