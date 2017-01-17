//---------------------------------------------------------------------------

#pragma hdrstop

#include "page.h"
#include "markup_converter.h"

#include <Vcl.Dialogs.hpp>

#include <fstream>

#ifndef Q_MOC_RUN
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#	include "SimpleJSON/utility/object.hpp"
#	include "SimpleJSON/utility/array.hpp"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void WikiPage::fromMarkup(std::string const& markup)
{
    fromJson(MarkupLibrary::getInstance().markupToJson(markup));
}
//---------------------------------------------------------------------------
std::string WikiPage::toMarkup()
{
    return MarkupLibrary::getInstance().jsonToMarkup(toJson());
}
//---------------------------------------------------------------------------
