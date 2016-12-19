//---------------------------------------------------------------------------
#pragma once

#include "../../element.h"

#include "header_options.h"
#include "text_options.h"
#include "style_options.h"
#include "table_options.h"

#include <utility>
#include <type_traits>
#include <cassert>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

//############################################################################
// START OF USER DECLARATIONS!
//############################################################################
struct __declspec(uuid("{5898CCAF-1EE4-4EB4-A785-48920E5E97A5}")) IOptionsFrame
{
	virtual void translate() = 0;
	virtual void setOwner(WikiElements::BasicElement* element) = 0;
	virtual void populate() = 0;
};
//---------------------------------------------------------------------------
#define FI_OPTION_FRAMES THeaderOptionsFrame, TTextOptionsFrame, TStyleOptionsFrame, \
					  TTableOptionsFrame

#define FI_INTERFACE_FUNCTIONS (translate)(setOwner)(populate)

#define interfaceFunctionType_translate void()
#define interfaceFunctionType_setOwner void(WikiElements::BasicElement*)
#define interfaceFunctionType_populate void()

//############################################################################
// END OF USER DECLARATIONS!
//############################################################################
//---------------------------------------------------------------------------
template <typename>
struct ExtractMethodReturnType
{

};

template <typename R, typename... List>
struct ExtractMethodReturnType <R(IOptionsFrame::*)(List...)>
{
	using type = R;
};

template <typename T>
struct ConvertFunctionType {};

template <typename CT, typename Ret, typename... Args>
struct ConvertFunctionType <Ret(CT::*)(Args...)>
{
	using type = Ret(Args...);
};

template <typename Ret, typename... Args>
struct ConvertFunctionType <Ret(Args...)>
{
    using type = Ret(Args...);
};

template <typename Ret, typename... Args>
struct ConvertFunctionType <Ret(*)(Args...)>
{
    using type = Ret(Args...);
};

struct __attribute__((packed)) yes { int _; };
struct __attribute__((packed)) no { int _1; int _2; };
//---------------------------------------------------------------------------
#define FI_CAN_CALL_STUMP(NAME) \
template <typename, typename T> \
struct hasMethod_ ## NAME \
{ \
}; \
\
template <typename ClassT, typename Ret, typename... Args> \
struct hasMethod_ ## NAME <ClassT, Ret(Args...)> \
{ \
private: \
    template <typename U, Ret (U::*)(Args...)> struct SFINAE {}; \
    template <typename U> static yes test(SFINAE <U, &U::NAME>*); \
    template <typename U> static no test(...); \
\
public: \
    static constexpr bool value = sizeof(test<ClassT>(nullptr)) == sizeof(yes); \
}

#define FI_CALL_IF_CALLABLE_IMPL(FNAME) \
template <bool Enable> \
struct FI_CALL_IF_CALLABLE_ ## FNAME \
{ \
	static void exec(...) {} \
}; \
\
template <> \
struct FI_CALL_IF_CALLABLE_ ## FNAME <false> \
{ \
	static void exec(...) {} \
}; \
\
template <> \
struct FI_CALL_IF_CALLABLE_ ## FNAME <true> \
{ \
	template <typename LhsT, typename... List> \
	static void exec(LhsT* lhs, List&&... params) \
	{ \
		lhs->FNAME(std::forward <List&&> (params)...); \
	} \
}

#define FI_CAN_CALL(CLASS, NAME, TYPE) \
	hasMethod_ ## NAME <CLASS, interfaceFunctionType_ ## NAME>::value
	//hasMethod_ ## NAME <CLASS, ConvertFunctionType<TYPE>::type>::value

#define FI_CAN_CALL_STUMP_DELEGATE(r, ctx, NAME) \
	FI_CAN_CALL_STUMP(NAME); \
	FI_CALL_IF_CALLABLE_IMPL(NAME);

#define FI_SETUP_CALL_CHECKS(SEQUENCE) \
	BOOST_PP_SEQ_FOR_EACH(FI_CAN_CALL_STUMP_DELEGATE, _, SEQUENCE)

#define FI_CALL_IF_CALLABLE(LHS_T, NAME, ...) \
	{ \
		FI_CALL_IF_CALLABLE_ ## NAME <FI_CAN_CALL(LHS_T, NAME, ftype)>::exec(__VA_ARGS__); \
	}
// FI_CAN_CALL(LHS_T, NAME, decltype(IOptionsFrame::NAME))

FI_SETUP_CALL_CHECKS(FI_INTERFACE_FUNCTIONS)
//---------------------------------------------------------------------------

#define FI_IOPTIONS_FRAME_CALLER_BEGIN(NAME) \
template <typename Head, typename... Tail> \
struct InterfaceCaller_ ## NAME \
{ \
	template <typename T, typename... List> \
	static bool NAME(T* frame, List&&... params) \
	{ \
		auto* framed = dynamic_cast <Head*> (frame); \
		if (framed) \
			FI_CALL_IF_CALLABLE(Head, NAME, framed, std::forward <List&&> (params)...) \
		else \
			return InterfaceCaller_ ## NAME <Tail...>::NAME(frame, params...); \
		return true; \
	} \
};

#define FI_IOPTIONS_FRAME_CALLER_END(NAME) \
template <typename Head> \
struct InterfaceCaller_ ## NAME <Head> \
{ \
	template <typename T, typename... List> \
	static bool NAME(T* frame, List&&... params) \
	{ \
		auto* framed = dynamic_cast <Head*> (frame); \
		if (framed) \
			FI_CALL_IF_CALLABLE(Head, NAME, framed, std::forward <List&&> (params)...) \
		return framed; \
	} \
};

#define FI_IOPTIONS_FRAME_CALL_DELEGATE(NAME) \
template <typename T, typename... List> \
void frame_ ## NAME(T* frame, List... params) \
{ \
	InterfaceCaller_ ## NAME < \
		FI_OPTION_FRAMES \
	>::NAME(frame, params...); \
}

#define FI_IOPTIONS_FRAME_CALL(NAME, ...) \
frame_ ## NAME(__VA_ARGS__)

#define FI_IOPTIONS_FRAME_CALLER(r, ctx, NAME) \
	FI_IOPTIONS_FRAME_CALLER_BEGIN(NAME) \
	FI_IOPTIONS_FRAME_CALLER_END(NAME) \
	FI_IOPTIONS_FRAME_CALL_DELEGATE(NAME)
//---------------------------------------------------------------------------
#define FI_SETUP_OPTIONS_FRAME_INTERFACE(SEQUENCE) \
	BOOST_PP_SEQ_FOR_EACH(FI_IOPTIONS_FRAME_CALLER, _, SEQUENCE)
//---------------------------------------------------------------------------
FI_SETUP_OPTIONS_FRAME_INTERFACE(FI_INTERFACE_FUNCTIONS)
//---------------------------------------------------------------------------
class OptionsFrameAdapter
{
public:
	OptionsFrameAdapter(TFrame* frame)
		: frame_(frame)
	{
	}

	OptionsFrameAdapter& translate()
	{
		FI_IOPTIONS_FRAME_CALL(translate, frame_);
		return *this;
	}

	OptionsFrameAdapter& setOwner(WikiElements::BasicElement* element)
	{
		FI_IOPTIONS_FRAME_CALL(setOwner, frame_, element);
		return *this;
	}

	OptionsFrameAdapter& populate()
	{
		FI_IOPTIONS_FRAME_CALL(populate, frame_);
		return *this;
    }

private:
	TFrame* frame_;
};
//---------------------------------------------------------------------------
