//---------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace TableStyling
{
	using Color = uint32_t;

	struct Font
	{
		Color color;
		int size;
		std::string family;
	};

	struct CellStyle
	{
		Color background;
		Font font;
	};

	class StyleGrid
	{
	private:
		std::vector <std::vector <CellStyle>> data_;
	};

	struct TableStyleContainer
	{

	};
}
//---------------------------------------------------------------------------
