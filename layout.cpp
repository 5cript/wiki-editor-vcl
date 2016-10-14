//---------------------------------------------------------------------------

#pragma hdrstop

#include "layout.h"
#include "debug.h"

#include <stdexcept>
//---------------------------------------------------------------------------
Layout::Layout(ViewportContainer* parent)
	: parent_{parent}
	, gridPanel_{nullptr}
{
    // Add Grid Item to Viewport and set style to automatic:
	auto item = parent->RowCollection->Add();
	item->SizeStyle = ssAuto;

    // Set GridPanel and set parent
	gridPanel_.reset(new TGridPanel(parent));
	gridPanel_->Parent = parent_;

	// Clear all unwanted columns
	gridPanel_->RowCollection->Clear();
	while (gridPanel_->ColumnCollection->Count > 1)
		gridPanel_->ColumnCollection->Delete(0);

	// Position
	//gridPanel_->Top = 0;
	gridPanel_->Align = alTop;
	resize(0);

	// Style
	gridPanel_->BorderStyle = bsSingle;
	gridPanel_->BorderWidth = 1;
	gridPanel_->BevelOuter = bvNone;
	//gridPanel_->ParentBackground = false;
	//gridPanel_->Color = TColor(((rand() % 255) << 16) + ((rand() % 255) << 8) + ((rand() % 255)));

	// SetLayoutStyle:
	int i = 0;
	for (; i != parent->RowCollection->Count; ++i)
		if (parent->ControlCollection->ControlItems[0][i]->Control == &*gridPanel_)
			break;
	if (i == parent->ControlCollection->Count)
		throw std::runtime_error("layout was not created inside viewport");

	//parent->RowCollection->Items[i]->SizeStyle = ssAbsolute;
	//parent->RowCollection->Items[i]->Value = gridPanel_->Height + 4;
}
//---------------------------------------------------------------------------
void Layout::resize(int height)
{
	realign();
	gridPanel_->Constraints->MinHeight = height;
	gridPanel_->Height = height;
}
//---------------------------------------------------------------------------
void Layout::swap(int lhs, int rhs)
{
	auto lhsControl = gridPanel_->ControlCollection->ControlItems[0][lhs]->Control;
	gridPanel_->ControlCollection->ControlItems[0][lhs]->Control =
		gridPanel_->ControlCollection->ControlItems[0][rhs]->Control;
	gridPanel_->ControlCollection->ControlItems[0][rhs]->Control = lhsControl;
}
//---------------------------------------------------------------------------
void Layout::moveControl(TControl* control, int position)
{
	bool found = false;
	int from = 0;
	for (; from != gridPanel_->ControlCount; ++from)
		if (gridPanel_->ControlCollection->ControlItems[0][from]->Control == control)
		{
			found = true;
			break;
		}

	if (!found)
		throw std::invalid_argument("control not in grid");

	//swap(from, position);

	if (position == from)
		return;

	// swap upwards
	if (from > position)
		for (int i = from; i > position; --i)
		{
			swap(i - 1, i);
		}
	// swap downwards
	else
		for (int i = from; i < position; ++i)
		{
			swap(i, i + 1);
		}
}
//---------------------------------------------------------------------------
void Layout::update()
{
    gridPanel_->UpdateControlsColumn(0);
}
//---------------------------------------------------------------------------
void Layout::realign()
{
	gridPanel_->Realign();
	//gridPanel_->Invalidate();
}
//---------------------------------------------------------------------------
TGridPanel* Layout::getControl() const
{
	return &*gridPanel_;
}
//---------------------------------------------------------------------------
ViewportContainer* Layout::getParent() const
{
    return parent_;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
