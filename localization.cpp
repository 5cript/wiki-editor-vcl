//---------------------------------------------------------------------------

#pragma hdrstop

#include "localization.h"

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#	include "SimpleJSON/utility/beauty_stream.hpp"
#endif

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <stdexcept>
#include <fstream>

SINGLETON_GLOBALS_DECLARATION(Translator)
//###########################################################################
TranslationData::Language::Language(std::map <std::string, std::string> translations)
	: mappings{std::move(translations)}
{
}
//###########################################################################
Translator::Translator()
	: language_{"de_DE"}
	, translationFile_{}
{
}
//---------------------------------------------------------------------------
Translator::~Translator()
{
}
//---------------------------------------------------------------------------
void Translator::loadLanguageFile(std::string const& file)
{
	std::ifstream reader(file, std::ios_base::binary);
	if (!reader.good())
		throw std::invalid_argument("file not found");

	auto tree = JSON::parse_json(reader);
	JSON::parse(translationFile_, "locales", tree);
}
//---------------------------------------------------------------------------
void Translator::saveLanguageFile(std::string const& file)
{
	/*
	translationFile_.languages["de_DE"] = TranslationData::Language{{
		{"$File", "Datei"}
	}};
	*/

	namespace io = boost::iostreams;

	io::filtering_ostream writer;
	writer.push(JSON::BeautifiedStreamWrapper{});
	writer.push(io::file_sink(file.c_str()));

	// std::ofstream writer(file, std::ios_base::binary);
	writer << "{";
	JSON::try_stringify(writer, "locales", translationFile_, JSON::ProduceNamedOutput);
	writer << "}";
}
//---------------------------------------------------------------------------
std::string Translator::translate(std::string const& keyString)
{
	auto language = translationFile_.languages.find(language_);
	if (language == std::end(translationFile_.languages))
		throw std::invalid_argument((std::string("language \"") + language_ + "\" was not found").c_str());

	auto translation = language->second.mappings.find(keyString);
	if (translation == std::end(language->second.mappings))
		return keyString;
		// throw std::invalid_argument((std::string("key \"") + keyString + "\" was not found").c_str());

	return translation->second;
}
//---------------------------------------------------------------------------
void Translator::setLanguage(std::string const& language)
{
	language_ = language;
}
//###########################################################################
String translate(String str)
{
	auto& translator = Translator::getInstance();
	str = StringReplace(str, "&", "", TReplaceFlags{} << rfReplaceAll << rfIgnoreCase);
	return UTF8ToString(translator.translate(AnsiString(str).c_str()).c_str());
}
//###########################################################################
#pragma package(smart_init)
