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
#include "ui_elements/image.h"

#include <boost/optional.hpp>
#include <string>
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
	return dynamic_cast <T*> (component);
}
//---------------------------------------------------------------------------
boost::optional <std::string> tryGetCommentText(WikiMarkup::Components::IExportableComponent* component);
//---------------------------------------------------------------------------
/**
 *	Comments and links count as sub elements, that do not own a personal component.
 **/
bool isSubComponent(WikiMarkup::Components::IExportableComponent* component);
//---------------------------------------------------------------------------
WikiMarkup::Components::IExportableComponent* extractData(WikiElements::BasicElement* element);
//---------------------------------------------------------------------------
void elementFactory(Section* section, WikiMarkup::Components::IExportableComponent* component);
//---------------------------------------------------------------------------

