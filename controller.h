//---------------------------------------------------------------------------

#pragma once

#include "ui_elements/element.h"

#include <vector>
//---------------------------------------------------------------------------
class PageController
{
public:
	PageController(TScrollBox* viewport);

	void test();

private:
	TScrollBox* viewport_;
	std::vector <std::unique_ptr <WikiElements::BasicElement>> elements_;
};
//---------------------------------------------------------------------------
