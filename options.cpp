//---------------------------------------------------------------------------

#pragma hdrstop

#include "options.h"
#include "user_files.h"

#include "SimpleJSON/utility/beauty_stream.hpp"

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
//---------------------------------------------------------------------------
SettingsHolder loadSettings()
{
	auto path = fs::path{UserHome::getAppDataPath()} / "settings.json";
	std::ifstream reader(path.string(), std::ios_base::binary);
	if (!reader.good())
		throw std::runtime_error(std::string{"cannot open "} + path.string());

	SettingsHolder holder;
	auto tree = JSON::parse_json(reader);
	JSON::parse(holder, "settings", tree);
	return holder;
}
//---------------------------------------------------------------------------
void saveSettings(SettingsHolder const& settings)
{
	auto path = fs::path{UserHome::getAppDataPath()} / "settings.json";
	std::ofstream writer(path.string(), std::ios_base::binary);
	if (!writer.good())
		throw std::runtime_error(std::string{"cannot open "} + path.string());

	boost::iostreams::filtering_ostream out;
	out.push(JSON::BeautifiedStreamWrapper{});
    out.push(writer);

	out << "{";
	JSON::try_stringify(out, "settings", settings, JSON::ProduceNamedOutput);
	out << "}";
}
//---------------------------------------------------------------------------
void setupSettings()
{
	auto fileRoot = fs::path{UserHome::getAppDataPath()};
	if (!fs::exists(fileRoot))
		fs::create_directory(fileRoot);

	auto path = fileRoot / "settings.json";
    std::ifstream reader(path.string(), std::ios_base::binary);
	if (!reader.good())
	{
		reader.close();
		saveSettings({}); // create default settings
    }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
