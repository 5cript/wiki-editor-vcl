//---------------------------------------------------------------------------

#pragma hdrstop

#include "controller.h"
#include "ui_elements/header.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

PageController::PageController(TPanel* viewport)
	: viewport_(viewport)
{

}
//---------------------------------------------------------------------------
void PageController::test()
{
	using namespace WikiElements;

	elements_.push_back(std::unique_ptr <Header>(new Header(viewport_)));
}
//---------------------------------------------------------------------------
