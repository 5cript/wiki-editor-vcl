//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "viewport.h"

#include <Vcl.ExtCtrls.hpp>

#include <memory>
//---------------------------------------------------------------------------
class Layout
{
public:
	Layout(ViewportContainer* parent);

	TGridPanel* getControl() const;
	ViewportContainer* getParent() const;
	void resize(int height);
	void realign();
	void swap(int lhs, int rhs);
	void moveControl(TControl* control, int position);
	void update();

private:
	ViewportContainer* parent_;
    std::unique_ptr <TGridPanel> gridPanel_;
};
//---------------------------------------------------------------------------
