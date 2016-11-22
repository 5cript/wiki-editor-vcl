//---------------------------------------------------------------------------
#pragma once

#include "../../element.h"

#include "header_options.h"
#include "text_options.h"
#include "style_options.h"

#include <cassert>

#include <boost/preprocessor/seq/for_each.hpp>
//---------------------------------------------------------------------------
struct __declspec(uuid("{5898CCAF-1EE4-4EB4-A785-48920E5E97A5}")) IOptionsFrame
{
	virtual void translate() = 0;
	virtual void setOwner(WikiElements::BasicElement* element) = 0;
};
//---------------------------------------------------------------------------
#define OPTION_FRAMES THeaderOptionsFrame, TTextOptionsFrame, TStyleOptionsFrame
#define INTERFACE_FUNCTIONS (translate)(setOwner)
//---------------------------------------------------------------------------
#define IOPTIONS_FRAME_CALLER_BEGIN(NAME) \
template <typename Head, typename... Tail> \
struct InterfaceCaller_ ## NAME \
{ \
	template <typename T, typename... List> \
	static bool NAME(T* frame, List... params) \
	{ \
		auto* framed = dynamic_cast <Head*> (frame); \
		if (framed) \
			framed->NAME(params...); \
		else \
			return InterfaceCaller_ ## NAME <Tail...>::NAME(frame, params...); \
		return true; \
	} \
};

#define IOPTIONS_FRAME_CALLER_END(NAME) \
template <typename Head> \
struct InterfaceCaller_ ## NAME <Head> \
{ \
	template <typename T, typename... List> \
	static bool NAME(T* frame, List... params) \
	{ \
		auto* framed = dynamic_cast <Head*> (frame); \
		if (framed) \
			framed->NAME(params...); \
		return framed; \
	} \
};

#define IOPTIONS_FRAME_CALL_DELEGATE(NAME) \
template <typename T, typename... List> \
void frame_ ## NAME(T* frame, List... params) \
{ \
	InterfaceCaller_ ## NAME < \
		OPTION_FRAMES \
	>::NAME(frame, params...); \
}

#define IOPTIONS_FRAME_CALL(NAME, ...) \
frame_ ## NAME(__VA_ARGS__)

#define IOPTIONS_FRAME_CALLER(r, ctx, NAME) \
	IOPTIONS_FRAME_CALLER_BEGIN(NAME) \
	IOPTIONS_FRAME_CALLER_END(NAME) \
	IOPTIONS_FRAME_CALL_DELEGATE(NAME)
//---------------------------------------------------------------------------
#define SETUP_OPTIONS_FRAME_INTERFACE(SEQUENCE) \
    BOOST_PP_SEQ_FOR_EACH(IOPTIONS_FRAME_CALLER, _, SEQUENCE)
//---------------------------------------------------------------------------
SETUP_OPTIONS_FRAME_INTERFACE(INTERFACE_FUNCTIONS)
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
		IOPTIONS_FRAME_CALL(translate, frame_);
		return *this;
	}

	OptionsFrameAdapter& setOwner(WikiElements::BasicElement* element)
	{
		IOPTIONS_FRAME_CALL(setOwner, frame_, element);
		return *this;
	}

private:
	TFrame* frame_;
};
//---------------------------------------------------------------------------
