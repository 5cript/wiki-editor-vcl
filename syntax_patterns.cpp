//---------------------------------------------------------------------------

#pragma hdrstop

#include "syntax_patterns.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define rgb(R, G, B) static_cast <TColor> (static_cast <unsigned long> (R + (G << 8) + (B << 16)))
//---------------------------------------------------------------------------
SyntaxPattern::SyntaxPattern(std::string const& pattern, TColor color, bool bold)
	: pattern_{pattern}
	, color_{color}
	, bold_{bold}
	, lineBreakMatcher_{false}
{
    std::string str = pattern.substr(pattern.length() - 3, 2);
	if (!pattern.empty() && pattern.substr(pattern.length() - 3, 2) == "\n")
		lineBreakMatcher_ = true;
}
//---------------------------------------------------------------------------
bool SyntaxPattern::matchesBreak() const
{
	return lineBreakMatcher_;
}
//---------------------------------------------------------------------------
SyntaxPatterns getDefaultStyle()
{
	return {
		SyntaxPattern{R"(((={2,6})( *.+ *)\2)\r?\n)", rgb(255, 189, 25), false},
		SyntaxPattern{R"(----\r?\n)", rgb(25, 235, 255), true},
		SyntaxPattern{R"(<!--(?!WIKI_EDITOR_END_SECTION)(?!-->).*-->)", rgb(45, 180, 0), true},
		SyntaxPattern{R"(<!--WIKI_EDITOR_END_SECTION-->)", rgb(188, 188, 188), true}
	};
}
//---------------------------------------------------------------------------
#undef rgb
