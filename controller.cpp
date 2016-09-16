//---------------------------------------------------------------------------

#pragma hdrstop

#include "controller.h"
#include "ui_elements/header.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

PageController::PageController(TScrollBox* viewport)
	: viewport_(viewport)
{

}
//---------------------------------------------------------------------------
void PageController::test()
{
	using namespace WikiElements;

	auto* head = new Header(viewport_);
	elements_.push_back(std::unique_ptr <Header>(head));
    head->setStyle("a{}");
}
//---------------------------------------------------------------------------
