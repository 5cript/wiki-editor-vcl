//---------------------------------------------------------------------------

#pragma once

#include "ui_elements/element.h"

#include <vector>
//---------------------------------------------------------------------------
class PageController
{
public:
	PageController(TPanel* viewport);

	void test();

private:
	TPanel* viewport_;
	std::vector <std::unique_ptr <WikiElements::BasicElement>> elements_;
};
//---------------------------------------------------------------------------
