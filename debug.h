//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>

#include "literals.h"

#include <boost/optional.hpp>

#include <string>
#include <exception>
#include <typeinfo>
#include <unordered_map>
#include <map>
//---------------------------------------------------------------------------
extern TRichEdit* Log;
//---------------------------------------------------------------------------
void SetLog(TRichEdit* log);

void DebugOut(std::string const& str);
void DebugOut(void* ptr);
void DebugOut(int integer);
void DebugOut(std::exception const& exc);
void DebugOut(const char* cstr);
void DebugOut(const wchar_t* wcstr);
void DebugOut(std::unordered_map <std::string, std::string> const& associative);
void DebugOut(std::map <std::string, std::string> const& associative);

template <typename T>
void DebugOut(boost::optional <T> const& optOut)
{
	if (optOut)
		DebugOut(optOut.get());
	else
		DebugOut("optional not set."_s + typeid(T).name());
}
//---------------------------------------------------------------------------
