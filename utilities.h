//---------------------------------------------------------------------------
#pragma once

struct BoundingBox
{
	long top;
	long left;
	long right;
	long bottom;

	BoundingBox(long top = 0, long left = 0, long right = 0, long bottom = 0)
		: top{top}
		, left{left}
		, right{right}
		, bottom{bottom}
	{
    }
};
//---------------------------------------------------------------------------
