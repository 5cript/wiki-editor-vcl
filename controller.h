//---------------------------------------------------------------------------

#pragma once

#include "section.h"
#include "element.h"

#include <vector>
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
class PageController
{
public:
	PageController(TScrollBox* viewport);

	void addSection();

	void test();

	void setStyle(std::string const& style);
	void setStyle(boost::filesystem::path const& styleFile);
	std::string getStyleString() const;

    TScrollBox* getViewport() const;

private:
	TScrollBox* viewport_;
	std::vector <Section> sections_;
	std::string style_;
};
//---------------------------------------------------------------------------
