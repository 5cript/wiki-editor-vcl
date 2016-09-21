//---------------------------------------------------------------------------

#pragma hdrstop

#include "controller.h"
#include "ui_elements/header.h"

#include <Vcl.Dialogs.hpp>

#include <fstream>
#include <cstdlib>
//---------------------------------------------------------------------------
#pragma package(smart_init)

PageController::PageController(TScrollBox* viewport)
	: viewport_(viewport)
	, sections_{}
	, style_{}
{
}
//---------------------------------------------------------------------------
void PageController::addSection()
{
	sections_.emplace_back(this);
}
//---------------------------------------------------------------------------
void PageController::test()
{
	using namespace WikiElements;

	auto* head = sections_.back().addElement <Header>();
	head->setLevel(rand() % 6 + 1);
	head->setText("Test");

	setStyle(boost::filesystem::path("D:/Development_IWS/wiki-project/wiki-vcl-css/header/header.css"));

	try
	{
		head->setStyle(style_);
	}
	catch (std::exception const& exc)
	{
        ShowMessage((std::string{"Error during css parsing process: "} + exc.what()).c_str());
    }
}
//---------------------------------------------------------------------------
TScrollBox* PageController::getViewport() const
{
	return viewport_;
}
//---------------------------------------------------------------------------
void PageController::setStyle(std::string const& style)
{
	style_ = style;
}
//---------------------------------------------------------------------------
void PageController::setStyle(boost::filesystem::path const& styleFile)
{
	std::ifstream reader(styleFile.string(), std::ios_base::binary);
	style_.clear();
	char buffer[4096];
	do {
		reader.read(buffer, 4096);
		style_ += std::string{buffer}.substr(0, reader.gcount());
    } while (reader.gcount() == 4096);
}
//---------------------------------------------------------------------------
std::string PageController::getStyleString() const
{
	return style_;
}
//---------------------------------------------------------------------------
