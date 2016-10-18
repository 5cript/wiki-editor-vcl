//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#   include <SimpleJSON/parse/jsd_fusion_adapted_struct.hpp>
#endif

#include <System.Classes.hpp>

#include <string>
#include <map>
//---------------------------------------------------------------------------
namespace TranslationData
{
	struct Language : public JSON::Stringifiable <Language>
					, public JSON::Parsable <Language>
	{
		using map_type = std::map <std::string, std::string>;
		map_type mappings;

        Language() = default;
		Language(std::map <std::string, std::string> translations);
	};

	struct TranslationFile : public JSON::Stringifiable <TranslationFile>
                           , public JSON::Parsable <TranslationFile>
	{
		using map_type = std::map <std::string, Language>;
		map_type languages;
	};
}
//---------------------------------------------------------------------------
class Translator
{
public:
	static Translator& getInstance() {
		static Translator inst;
		return inst;
	}

	void loadLanguageFile(std::string const& file);
    void saveLanguageFile(std::string const& file);
	void setLanguage(std::string const& language);
	std::string translate(std::string const& keyString);

private:
	Translator();

private:
	std::string language_;
    TranslationData::TranslationFile translationFile_;
};
//---------------------------------------------------------------------------
String translate(String str);
//---------------------------------------------------------------------------
BOOST_FUSION_ADAPT_STRUCT
(
	TranslationData::Language,
	(TranslationData::Language::map_type, mappings)
)
//---------------------------------------------------------------------------
BOOST_FUSION_ADAPT_STRUCT
(
	TranslationData::TranslationFile,
	(TranslationData::TranslationFile::map_type, languages)
)
//---------------------------------------------------------------------------
#define TRANSLATE_SPECIFIC(WHAT, PROPERTY) \
	if (WHAT->PROPERTY.SubString(0, 1) == "$") \
		WHAT->PROPERTY = ::translate(WHAT->PROPERTY); \

#define TRANSLATE_OF_TYPE(PARENT, TYPE, PROPERTY) \
{ \
	auto* control = dynamic_cast <TYPE*> (PARENT->Components[i]); \
	if (!control) \
		continue; \
	\
	TRANSLATE_SPECIFIC(control, PROPERTY) \
}
//---------------------------------------------------------------------------
