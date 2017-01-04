//---------------------------------------------------------------------------
#pragma once

#include "section.h"

#ifndef Q_MOC_RUN
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#endif

#include <vector>
//---------------------------------------------------------------------------
struct WikiPage : public JSON::Stringifiable <WikiPage>
				, public JSON::Parsable <WikiPage>
{
	std::vector <Section> const& sections;

	WikiPage(std::vector <Section> const& sections);

	std::string toJson();
	void fromJson();
	std::string toMarkup();
    void fromMarkup();
};
//---------------------------------------------------------------------------

BOOST_FUSION_ADAPT_STRUCT
(
	WikiPage,
    (std::vector <Section>, sections)
)
