//---------------------------------------------------------------------------
#pragma once

#include "header_options.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <typename Head, typename... Tail>
struct InterfaceCaller
{
	template <typename T>
	static void translate(T* frame)
	{
		auto* framed = dynamic_cast <Head*> (frame);
		if (framed)
			framed->translate();
		else
			InterfaceCaller<Tail...>::translate(frame);
	}
};

template <typename Head>
struct InterfaceCaller <Head>
{
	template <typename T>
	static void translate(T* frame)
	{
		auto* framed = dynamic_cast <Head*> (frame);
		if (framed)
			framed->translate();
	}
};

template <typename T>
void frameTranslate(T* frame)
{
	InterfaceCaller <
		THeaderOptionsFrame
	>::translate(frame);
}
//---------------------------------------------------------------------------
