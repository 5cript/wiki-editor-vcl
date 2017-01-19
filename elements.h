//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "section.h"
#include "wiki-markup/components/exportable_components/exportable_component.hpp"
#include "wiki-markup/components/exportable_components/exportable_components.hpp"

#include "ui_elements/header.h"
#include "ui_elements/horizontal_line.h"
#include "ui_elements/spacer.h"
#include "ui_elements/table.h"
#include "ui_elements/text.h"
//---------------------------------------------------------------------------
template <typename T>
typename T::data_type* tryExtract(WikiElements::BasicElement* element)
{
	auto* p = dynamic_cast <T*> (element);
	if (p == nullptr)
		return nullptr;
	else
		return p->getDataHandle();
}
//---------------------------------------------------------------------------
template <typename T>
T* tryIdentify(WikiMarkup::Components::IExportableComponent* component)
{
	auto* p = dynamic_cast <T*> (component);
	if (p == nullptr)
		return nullptr;
	else
		return p;
}
//---------------------------------------------------------------------------
WikiMarkup::Components::IExportableComponent* extractData(WikiElements::BasicElement* element)
{
	using namespace WikiElements;

#	define EXTRACT(T) \
	{ \
		auto optData = tryExtract <T> (element); \
		if (optData != nullptr) \
			return optData->clone(); \
	}

	EXTRACT(Text)
	EXTRACT(Header)
	EXTRACT(Table)
	EXTRACT(HorizontalLine)

#	undef EXTRACT

	return nullptr;
}
//---------------------------------------------------------------------------
void elementFactory(Section* section, WikiMarkup::Components::IExportableComponent* element)
{
	bool ignoreStyle = false;

#	define IDENTIFY(T, RES) \
	{ \
		auto optData = tryIdentify <T> (element); \
		if (optData != nullptr) \
		{ \
			section->addElement <RES>(ignoreStyle)->setData(*optData); \
            return; \
		} \
	}

	using namespace WikiMarkup::Components;
	using namespace WikiElements;

	IDENTIFY(ExportableText, Text)
	IDENTIFY(ExportableHeader, Header)
	IDENTIFY(ExportableTable, Table)
	IDENTIFY(ExportableHorizontalLine, HorizontalLine);

#	undef IDENTIFY

	throw std::runtime_error((std::string{"element not supported by UI ("} + element->toJson() + ")").c_str());
}
//---------------------------------------------------------------------------
