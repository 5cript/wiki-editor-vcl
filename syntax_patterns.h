//---------------------------------------------------------------------------
#pragma once

#include <Vcl.Graphics.hpp>

#include <string>
#include <vector>
#include <regex>
//---------------------------------------------------------------------------
class SyntaxHighlighter;
class SyntaxPattern
{
	friend SyntaxHighlighter;

public:
	SyntaxPattern(std::string const& pattern, TColor color, bool bold);

	bool matchesBreak() const;

private:
	std::regex pattern_;
	TColor color_;
	bool bold_;
	bool lineBreakMatcher_;
};

using SyntaxPatterns = std::vector <SyntaxPattern>;
//---------------------------------------------------------------------------
SyntaxPatterns getDefaultStyle();
//---------------------------------------------------------------------------
