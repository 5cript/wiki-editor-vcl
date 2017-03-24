//---------------------------------------------------------------------------

#pragma hdrstop

#include "syntax_highlight.h"

#include <boost/algorithm/string/replace.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
SyntaxHighlighter::SyntaxHighlighter(TRichEdit* edit, std::vector <SyntaxPattern> patterns)
	: edit_{edit}
	, patterns_{std::move(patterns)}
	, defaultPattern_{".", clWhite, false}
{
}
//---------------------------------------------------------------------------
void SyntaxHighlighter::apply()
{
	// Remember RichEdit state
	auto mask = edit_->Perform(EM_GETEVENTMASK, 0, 0);
	edit_->Perform(EM_SETEVENTMASK, 0, ENM_NONE);
	DWORD start = 0;
	edit_->Perform(EM_GETSEL, (LPARAM)&start, 0);
	edit_->Perform(WM_SETREDRAW, false, 0);

	// Get rich edit text
	std::string text = UTF8String(edit_->Text).c_str();

	// Get all line starts for later correction.
	std::vector <std::size_t> lineStarts;
	int counter = 0;
	for (auto const& i : text)
	{
		if (i == '\n')
            lineStarts.push_back(counter);
		counter++;
    }

	// apply syntax highlighting patterns.
	std::vector <std::pair <std::size_t, std::size_t>> replacements;
	for (auto const& pattern : patterns_)
	{
		auto reps = applySingle(pattern, text, lineStarts);
		for (auto const& i : reps)
			replacements.push_back(i);
	}

	// merge overlapping highlights:
	for (auto const& replacement : replacements)
	{
		for (auto const& replacementSearch : replacements)
		{
            if (replacement.
        }
    }

	// Reset RichEdit.
	edit_->Perform(EM_SETSEL, start, start);
	edit_->Perform(EM_SETEVENTMASK, 0, mask);
	edit_->Perform(WM_SETREDRAW, true, 0);
	InvalidateRect(edit_->Handle, 0, true);
}
//---------------------------------------------------------------------------
void SyntaxHighlighter::select(std::size_t begin, std::size_t len)
{
	edit_->Perform(EM_SETSEL, begin, begin + len);
}
//---------------------------------------------------------------------------
void SyntaxHighlighter::stylize(SyntaxPattern const& pattern)
{
	::CHARFORMAT format{0};
	format.cbSize = sizeof(format);
	format.dwMask = CFM_COLOR;
	if (pattern.bold)
	{
		format.dwMask |= CFM_BOLD;
		format.dwEffects |= CFE_BOLD;
	}
	format.crTextColor = pattern.color;
	edit_->Perform(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&format);
}
//---------------------------------------------------------------------------
std::vector <std::pair <std::size_t, std::size_t>> SyntaxHighlighter::applySingle(
	SyntaxPattern const& pattern,
	std::string text,
	std::vector <std::size_t> const& lineStarts
)
{
	auto fixPosition = [&lineStarts](std::size_t pos)
	{
		int counter = 0;
		for (auto const& i : lineStarts)
			if (pos > i)
				counter++;
		return pos - counter;
	};

	auto highlight = [this, &pattern](std::size_t pos, std::size_t len)
	{
		select(pos, len);
		stylize(pattern);
		select(pos + len, 0);
		stylize(defaultPattern_);
		return std::pair <std::size_t, std::size_t>{pos, len}
	};

	std::vector <std::pair <std::size_t, std::size_t>> replacements;

	auto accumulativeCut = 0;
	std::smatch match;
	while (std::regex_search(text, match, pattern.pattern))
	{
		auto cut = text.length() - match.suffix().str().length();
		text = match.suffix().str();
		replacements.push_back(highlight(fixPosition(match.position() + accumulativeCut), match.length()));
		accumulativeCut += cut;
	}
	return replacements;
}
//---------------------------------------------------------------------------
