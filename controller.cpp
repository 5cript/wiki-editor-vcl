//---------------------------------------------------------------------------

#pragma hdrstop

#include "controller.h"
#include "ui_elements/header.h"
#include "ui_elements/text.h"
#include "ui_elements/horizontal_line.h"
#include "ui_elements/table.h"
#include "ui_elements/drop_target.h"
#include "debug.h"
#include "page.h"

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
	, selectionCallback_{}
	, autoSelect_{false}
{
	viewport_->OnClick = onViewportClick;
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
		head->setStyle(style_);
		head->setLevel(2);
		head->setText("Test");

		auto* text = sections_.back().addElement <Text>();
		text->setStyle(style_);

		auto* hline = sections_.back().addElement <HorizontalLine>();
		hline->setStyle(style_);


		auto* text2 = sections_.back().addElement <Text>();
		text2->setStyle(style_);

		auto* table = sections_.back().addElement <Table>();
		table->setStyle(style_);
		table->getDataHandle()->attributes["class"] = "wikitable";

		table->resize(1,1);

		table->gatherStyles(0, 0);

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
		section.startDragDrop();
		section.realign();
    }
}
//---------------------------------------------------------------------------
void __fastcall PageController::dropIndicatorDragOver(
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
std::pair <Section*, int> PageController::endDragDrop()
{
	std::pair <Section*, int> result = {
		getSectionUnderCursor(),
		-1
	};

	for (auto& section : sections_)
	{
		auto pos = section.endDragDrop();

		if (&section == result.first)
			result.second = pos;
	}
	realign();

	return result;
}
//---------------------------------------------------------------------------
Section* PageController::getSectionUnderCursor()
{
	auto clientPoint = viewport_->ScreenToClient(Mouse->CursorPos);
	for (auto& section : sections_)
	{
		if (section.isWithin(clientPoint.X, clientPoint.Y))
			return &section;
	}
	return nullptr;
}
//---------------------------------------------------------------------------
Section* PageController::getSectionUnder(int x, int y)
{
	for (auto& i : sections_)
	{
		auto fixed = viewport_->ScreenToClient(TPoint{x, y});
		if (i.isWithin(fixed.X, fixed.Y))
			return &i;
	}
	return nullptr;
}
//---------------------------------------------------------------------------
WikiElements::BasicElement* PageController::getElementUnderCursor()
{
	auto clientPoint = viewport_->ScreenToClient(Mouse->CursorPos);
	auto* section = getSectionUnderCursor();
	if (section == nullptr)
		return nullptr;

	return section->getElementUnder(clientPoint.X, clientPoint.Y);
}
//---------------------------------------------------------------------------
WikiElements::BasicElement* PageController::addHeader(Section* section, int pos)
{
	if (section == nullptr)
		return nullptr;

	auto* head = section->addElement <WikiElements::Header>(pos);
	if (!style_.empty())
		head->setStyle(style_);
	realign();
	return head;
}
//---------------------------------------------------------------------------
WikiElements::BasicElement* PageController::addHeader(std::pair <Section*, int> const& parameters)
{
	return addHeader(parameters.first, parameters.second);
}
//---------------------------------------------------------------------------
void PageController::realign()
{
	int totalHeight = 0;

	for (auto& i : sections_)
    	i.realign();

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
void PageController::startSelectionMode(std::function <void(WikiElements::BasicElement*)> const& cb)
{
	selectionCallback_ = cb;
}
//---------------------------------------------------------------------------
void PageController::stopSelectionMode(WikiElements::BasicElement* element)
{
	if (selectionCallback_)
	{
		selectionCallback_(element);
		if (!autoSelect_)
			selectionCallback_ = {};
	}
}
//---------------------------------------------------------------------------
void __fastcall PageController::onViewportClick(TObject* Sender)
{
	if (isInSelectionMode())
	{
		// selectionCallback_(nullptr);
		stopSelectionMode(nullptr);
    }
}
//---------------------------------------------------------------------------
bool PageController::isInSelectionMode() const
{
	return selectionCallback_;
}
//---------------------------------------------------------------------------
bool PageController::setAutoSelectEnabled(bool autoSelect)
{
	autoSelect_ = autoSelect;
}
//---------------------------------------------------------------------------
bool PageController::isAutoSelectEnabled() const
{
	return autoSelect_;
}
//---------------------------------------------------------------------------
void PageController::save(std::string const& fileName) const
{
	WikiPage page {sections_};

}
//---------------------------------------------------------------------------
