//---------------------------------------------------------------------------
#pragma once

#include "../../element.h"

//---------------------------------------------------------------------------
struct __declspec(uuid("{5898CCAF-1EE4-4EB4-A785-48920E5E97A5}")) IOptionsFrame
{
	virtual void translate() = 0;
	virtual void setOwner(WikiElements::BasicElement* element) = 0;
};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/*
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
	static bool translate(T* frame)
	{
		auto* framed = dynamic_cast <Head*> (frame);
		if (framed)
			framed->translate();
		return framed;
	}
};

template <typename T>
void frameTranslate(T* frame)
{
	InterfaceCaller <
		THeaderOptionsFrame
	>::translate(frame);
}
*/
//---------------------------------------------------------------------------
