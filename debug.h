//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>

#include <string>
#include <exception>
#include <typeinfo>
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
//---------------------------------------------------------------------------
