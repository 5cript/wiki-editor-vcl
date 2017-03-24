//---------------------------------------------------------------------------

#pragma hdrstop

#include "syntax_patterns.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define rgb(R, G, B) static_cast <TColor> (static_cast <unsigned long> (R + (G << 8) + (B << 16)))
//---------------------------------------------------------------------------
SyntaxPattern::SyntaxPattern(std::string const& pattern, TColor color, bool bold)
	: pattern{pattern}
	, color{color}
	, bold{bold}
{
}
//---------------------------------------------------------------------------
SyntaxPatterns getDefaultStyle()
{
	return {
		SyntaxPattern{R"(((={2,6})( *[^=\s]+ *)\2))", rgb(255, 189, 25), false},
		SyntaxPattern{R"(----\r?\n)", rgb(25, 235, 255), true},
		SyntaxPattern{R"(<!--[\w\s]*-->)", rgb(45, 180, 0), true},
		SyntaxPattern{R"(<!--WIKI_EDITOR_END_SECTION-->)", rgb(188, 188, 188), true}
	};
}
//---------------------------------------------------------------------------
#undef rgb
