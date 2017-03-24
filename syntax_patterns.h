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

private:
	std::regex pattern;
	TColor color;
	bool bold;
};

using SyntaxPatterns = std::vector <SyntaxPattern>;
//---------------------------------------------------------------------------
SyntaxPatterns getDefaultStyle();
//---------------------------------------------------------------------------
