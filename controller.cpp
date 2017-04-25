//---------------------------------------------------------------------------

#pragma hdrstop

#include "controller.h"
#include "style_parser.h"
#include "debug.h"
#include "page.h"
#include "user_files.h"

#include "star-tape/star_tape.hpp"

#include <Vcl.Dialogs.hpp>

#include <boost/scope_exit.hpp>

#include <string>
#include <fstream>
#include <cstdlib>
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace fs = boost::filesystem;
//---------------------------------------------------------------------------
PageController::PageController(ViewportContainer* viewport)
	: viewport_(viewport)
	//, dropTarget_{new TPanel{viewport_}}
	, sections_{}
	, style_{}
	, selectionCallback_{}
	, autoSelect_{false}
	, sectionGuard_{}
	, dirty_{false}
{
	viewport_->OnClick = onViewportClick;
}
//---------------------------------------------------------------------------
void PageController::addSection()
{
	std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
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

		//load("save.wes");

        std::ifstream reader {"testfile.txt", std::ios_base::binary};
		if (!reader.good())
			throw std::runtime_error((std::string{"file not found: "} + "testfile.txt").c_str());

		reader.seekg(0, std::ios::end);
		size_t size = reader.tellg();
		std::string buffer(size, ' ');
		reader.seekg(0);
		reader.read(&buffer[0], size);

		loadFromMarkup(buffer);

		save("out.wes");

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
	std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
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

	{
		std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
		for (auto& section : sections_)
		{
			auto pos = section.endDragDrop();

			if (&section == result.first)
				result.second = pos;
		}
	}
	realign();

	return result;
}
//---------------------------------------------------------------------------
Section* PageController::getSectionUnderCursor()
{
	auto clientPoint = viewport_->ScreenToClient(Mouse->CursorPos);
	std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
	for (auto& section : sections_)
	{
		if (section.isWithin(clientPoint.X, clientPoint.Y))
			return &section;
	}
	if (!sections_.empty())
	{
		if (clientPoint.Y < sections_.front().getBoundingBox().top)
			return &*std::begin(sections_);
		if (clientPoint.Y > sections_.back().getBoundingBox().top)
			return &*(std::begin(sections_) + (sections_.size() - 1));
    }
	return nullptr;
}
//---------------------------------------------------------------------------
Section* PageController::getSectionUnder(int x, int y)
{
    std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
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
void PageController::realign()
{
	if (disableRealigns_)
		return;

	DebugOut("Controller Realign");

    std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
	int totalHeight = 0;

	// first section size fix
	for (auto& i : sections_)
		i.realign();

	if (!sections_.empty())
		sections_.front().realign(generalTopPadding);

	// correct section tops
	for (auto i = std::begin(sections_) + 1; i < std::end(sections_); ++i)
		i->realign((i-1)->getBoundingBox().bottom);

	// resize the viewport
	{
		for (auto i = std::begin(sections_); i < std::end(sections_); ++i)
			totalHeight += i->getAccumulativeHeight();

		viewport_->Height = totalHeight + 10;
		viewport_->Realign();
	}
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
	StyleParser parser;
	parsedStyle_ = parser.parseStyleSheet(style_);
}
//---------------------------------------------------------------------------
void PageController::setStyle()
{
	fs::path fileRoot {UserHome::getAppDataPath()};
	auto style = fileRoot / "default_style.css";
	if (fs::exists(style) && fs::is_regular_file(style))
        setStyle(style);
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
    setStyle(style_);
}
//---------------------------------------------------------------------------
std::string PageController::getStyleString() const
{
	return style_;
}
//---------------------------------------------------------------------------
WretchedCss::StyleSheet PageController::getStyle() const
{
	return parsedStyle_;
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
void PageController::setAutoSelectEnabled(bool autoSelect)
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
	WikiPage page;
	{
		std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
		for (auto const& i : sections_)
			page.addComponents(i.saveComponents());
	}

    // NOTE: FROM HERE ON, THERE MUST NOT BE ANY MEMBER ACCESS.
	auto markup = page.toMarkup();
	auto json = page.toJson();

    using namespace StarTape;

	auto bundle = createOutputFileArchive <CompressionType::None> (fileName);
	(TapeWaterfall{}
		<< TapeOperations::AddString("page.mu", markup)
		<< TapeOperations::AddString("page.json", json)
	).apply(&archive(bundle));
	clearDirtyFlag();
}
//---------------------------------------------------------------------------
void PageController::load(std::string const& fileName)
{
	using namespace StarTape;

	disableRealigns_ = true;

	BOOST_SCOPE_EXIT(&disableRealigns_) {
        disableRealigns_ = false;
    } BOOST_SCOPE_EXIT_END

	WikiPage page;
	auto bundle = openInputFile <CompressionType::None> (fileName);
	auto decompressed = loadArchive <InputTapeArchive> (archive(bundle));
	auto index = archive(decompressed).makeIndex();
	auto markupFile = index.find("page.mu");
	if (markupFile == std::end(index))
		throw std::runtime_error("markup file not found");
	loadFromMarkup(index.readFile(markupFile));
}
//---------------------------------------------------------------------------
void PageController::loadFromMarkup(std::string const& markup)
{
	WikiPage page;
	page.fromMarkup(markup);

	auto components = page.getComponents();

    sections_.clear();

    std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
	for (auto component = std::begin(components), end = std::end(components); component != end;)
	{
		addSection();
		component = sections_.back().loadComponents(component, end);
	}
	clearDirtyFlag();

	disableRealigns_ = false;
	realign();
}
//---------------------------------------------------------------------------
std::string PageController::toMarkup() const
{
	WikiPage page;
	{
		std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
		for (auto const& i : sections_)
			page.addComponents(i.saveComponents());
	}

    return page.toMarkup();
}
//---------------------------------------------------------------------------
void PageController::reset()
{
	std::lock_guard <std::recursive_mutex> guard {sectionGuard_};
	sections_.clear();
	addSection();
	realign();
}
//---------------------------------------------------------------------------
bool PageController::empty() const
{
	for (auto const& section : sections_)
		if (!section.empty())
			return false;

	return true;
}
//---------------------------------------------------------------------------
void PageController::makeDirty()
{
	dirty_.store(true);
}
//---------------------------------------------------------------------------
bool PageController::isDirty() const
{
    return dirty_.load();
}
//---------------------------------------------------------------------------
void PageController::clearDirtyFlag() const
{
	dirty_.store(false);
}
//---------------------------------------------------------------------------
