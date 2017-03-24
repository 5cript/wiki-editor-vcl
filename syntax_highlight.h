//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "syntax_patterns.h"

#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class SyntaxHighlighter
{
public:
	SyntaxHighlighter(TRichEdit* edit, std::vector <SyntaxPattern> patterns);

	void apply();

private:
	void select(std::size_t begin, std::size_t len);
	void stylize(SyntaxPattern const& pattern);
	std::vector <std::pair <std::size_t, std::size_t>> applySingle(
		SyntaxPattern const& pattern,
		std::string text,
		std::vector <std::size_t> const& lineStarts
	);

private:
	TRichEdit* edit_;
	std::vector <SyntaxPattern> patterns_;
	SyntaxPattern defaultPattern_;
};
//---------------------------------------------------------------------------
