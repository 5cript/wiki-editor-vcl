//---------------------------------------------------------------------------

#pragma hdrstop

#include "elements.h"
#include "debug.h"
//---------------------------------------------------------------------------
bool isSubComponent(WikiMarkup::Components::IExportableComponent* component)
{
	using namespace WikiMarkup::Components;

	return tryIdentify <ExportableCommentText> (component) != nullptr ||
		   tryIdentify <ExportableLink> (component) != nullptr;
}
//---------------------------------------------------------------------------
boost::optional <std::string> tryGetCommentText(WikiMarkup::Components::IExportableComponent* component)
{
	using namespace WikiMarkup::Components;

	auto* opt = dynamic_cast <ExportableCommentText*> (component);
	if (opt != nullptr)
		return opt->data;
	return boost::none;
}
//---------------------------------------------------------------------------
WikiMarkup::Components::IExportableComponent* extractData(WikiElements::BasicElement* element)
{
	using namespace WikiElements;

#	define EXTRACT(T) \
	{ \
		auto* optData = tryExtract <T> (element); \
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
void elementFactory(Section* section, WikiMarkup::Components::IExportableComponent* component)
{
	bool ignoreStyle = false;

#	define IDENTIFY(T, RES) \
	{ \
		auto* optData = tryIdentify <T> (component); \
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

	throw std::runtime_error((std::string{"element not supported by UI ("} + component->toJson() + ")").c_str());
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
