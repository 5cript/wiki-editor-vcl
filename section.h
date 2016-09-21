//---------------------------------------------------------------------------
#pragma once

#include "padding_control.h"
#include "forward_declarations.h"
#include "element.h"
//---------------------------------------------------------------------------
class Section
{
public:
	Section(PageController* parent);

	BoundingBox getBoundingBox() const;
	long getMostBottom() const;

	template <typename T>
	T* addElement()
	{
		auto* elem = new T(getViewport(), this);
		try
		{
			children_.push_back(std::unique_ptr <T> {elem});
		}
		catch (std::bad_alloc const& exc)
		{
            delete elem;
        }
		return elem;
	}

	TScrollBox* getViewport() const;

private:
	PageController* parent_;
	std::vector <std::unique_ptr <WikiElements::BasicElement>> children_;
};
//---------------------------------------------------------------------------
