//---------------------------------------------------------------------------

#pragma hdrstop

#include "debug.h"

#include <Vcl.Dialogs.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdint>
//---------------------------------------------------------------------------
template <unsigned S>
struct IntFromSize
{
};
template <>
struct IntFromSize <1>
{
	using type = std::int8_t;
	using utype = std::uint8_t;
};
template <>
struct IntFromSize <2>
{
	using type = std::int16_t;
	using utype = std::uint16_t;
};
template <>
struct IntFromSize <4>
{
	using type = std::int32_t;
	using utype = std::uint32_t;
};
template <>
struct IntFromSize <8>
{
	using type = std::int64_t;
	using utype = std::uint64_t;

};
//---------------------------------------------------------------------------
void SetLog(TRichEdit* log)
{
    Log = log;
}
//---------------------------------------------------------------------------
void DebugOut(std::string const& str)
{
	std::cout << str;
	if (Log)
		Log->Lines->Add(str.c_str());
	else
		ShowMessage(str.c_str());
}
//---------------------------------------------------------------------------
void DebugOut(void* ptr)
{
	std::stringstream sstr;
	sstr << "0x" << std::hex << reinterpret_cast <IntFromSize <sizeof(ptr)>::type> (ptr);
	std::cout << sstr.str();
	if (Log)
		Log->Lines->Add(sstr.str().c_str());
	else
		ShowMessage(sstr.str().c_str());
}
//---------------------------------------------------------------------------
void DebugOut(int integer)
{
	std::cout << integer;
	if (Log)
		Log->Lines->Add(IntToStr(integer));
	else
		ShowMessage(IntToStr(integer));
}
//---------------------------------------------------------------------------
void DebugOut(std::exception const& exc)
{
	if (Log)
		Log->Lines->Add(std::string{exc.what()}.c_str());
	else
		ShowMessage(std::string{exc.what()}.c_str());
	std::cout << exc.what();
}
//---------------------------------------------------------------------------
void DebugOut(const char* cstr)
{
    DebugOut(std::string{cstr});
}
//---------------------------------------------------------------------------
void DebugOut(const wchar_t* wcstr)
{
    DebugOut(std::string{AnsiString(String(wcstr)).c_str()});
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
