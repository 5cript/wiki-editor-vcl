//---------------------------------------------------------------------------

#pragma hdrstop

#include "controller.h"
#include "ui_elements/header.h"
#include "ui_elements/text.h"
#include "ui_elements/horizontal_line.h"
#include "ui_elements/table.h"
#include "ui_elements/drop_target.h"

#include <Vcl.Dialogs.hpp>

#include <fstream>
#include <cstdlib>
//---------------------------------------------------------------------------
#pragma package(smart_init)

PageController::PageController(ViewportContainer* viewport)
	: viewport_(viewport)
	//, dropTarget_{new TPanel{viewport_}}
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

	try
	{
		//setStyle(boost::filesystem::path("D:/Development_IWS/wiki-project/wiki-vcl-css/compiled.css"));
		setStyle(boost::filesystem::path("../../../wiki-vcl-css/compiled.css"));

		auto* head = sections_.back().addElement <Header>();
		//head->setLevel(rand() % 6 + 1);
		head->setLevel(1);
		head->setText("Test");
		head->setStyle(style_);

		auto* text = sections_.back().addElement <Text>();
		text->setStyle(style_);

		auto* hline = sections_.back().addElement <HorizontalLine>();
		hline->setStyle(style_);


		auto* text2 = sections_.back().addElement <Text>();
		text2->setStyle(style_);

		auto* table = sections_.back().addElement <Table>();
		table->setStyle(style_);

		// finally
		realign();
	}
	catch (std::exception const& exc)
	{
        ShowMessage((std::string{"Error during css parsing process: "} + exc.what()).c_str());
    }
}
//---------------------------------------------------------------------------
void PageController::initializeViewport()
{
	/*
	dropTarget_->Height = 10;
	dropTarget_->BorderStyle = bsSingle;
	dropTarget_->ParentBackground = false;
	dropTarget_->BevelOuter = bvNone;
	dropTarget_->Color = TColor(0x00EEEE);
	dropTarget_->Visible = false;
	dropTarget_->Parent = viewport_;
	dropTarget_->Left = leftSectionPadding;
	dropTarget_->Top = 0;
	dropTarget_->Width = viewport_->Width - leftSectionPadding;
	dropTarget_->OnDragOver = DropIndicatorDragOver;
	*/
}
//---------------------------------------------------------------------------
void PageController::startDragDrop()
{
	for (auto& section : sections_)
	{
		section.realign();
    }
}
//---------------------------------------------------------------------------
void __fastcall PageController::DropIndicatorDragOver(
	TObject *Sender,
	TObject *Source,
	int X,
	int Y,
	TDragState State,
	bool &Accept
)
{
	Accept = true;
}
//---------------------------------------------------------------------------
void PageController::renderDropTarget(int x, int y)
{
	/*
	dropTarget_->Visible = true;
	auto* section = getSectionUnder(x, y);
	if (sections_.empty() || !section)
	{
		dropTarget_->Top = y;
		dropTarget_->Color = TColor(0x00EEEE);
	}
	else
	{
		auto box = section->placeDropIndicator(x, y);
		dropTarget_->Top = box.top;
		dropTarget_->Color = TColor(0x00EE00);
	}
	*/
}
//---------------------------------------------------------------------------
void PageController::endDragDrop()
{
	//dropTarget_->Visible = false;
	realign();
}
//---------------------------------------------------------------------------
Section* PageController::getSectionUnder(int x, int y)
{
	/*
	for (auto& i : sections_)
	{
		if (i.isWithin(x, y))
			return &i;
	}
	*/
	return nullptr;
}
//---------------------------------------------------------------------------
void PageController::realign()
{
	int totalHeight = 0;

	if (!sections_.empty())
	{
		sections_.front().realign(generalTopPadding);
		totalHeight += sections_.front().getAccumulativeHeight();
	}

	for (auto i = std::begin(sections_) + 1; i < std::end(sections_); ++i)
	{
		i->realign((i-1)->getBoundingBox().bottom);
		totalHeight += i->getAccumulativeHeight();
	}

	viewport_->Height = totalHeight + 10;
	viewport_->Realign();
}
//---------------------------------------------------------------------------
ViewportContainer* PageController::getViewport() const
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
	if (!reader.good())
		throw std::invalid_argument("style file not found");

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
