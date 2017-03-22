//---------------------------------------------------------------------------

#pragma hdrstop

#include "persistence_control.h"
#include "constants.h"
#include "user_files.h"
#include "debug.h"

#include <boost/filesystem.hpp>

#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>

namespace fs = boost::filesystem;
//---------------------------------------------------------------------------
PersistenceControl::PersistenceControl(
	PageController* controller,
	std::string const& fileName,
	bool addExtension,
	int maxBackups
)
	: controller_{controller}
	, backupTimer_{[this](){return automaticBackup();}}
	, fileName_{} // intentional
	, nameStem_{}
	, maxBackups_{maxBackups}
{
	setFile(fileName, addExtension);
}
//---------------------------------------------------------------------------
bool PersistenceControl::automaticBackup()
{
	try
	{
		backup();
		return true;
	}
	catch(...)
	{
        return false;
    }
}
//---------------------------------------------------------------------------
void PersistenceControl::setupBackupStructure()
{
	fs::path fileRoot {UserHome::getAppDataPath()};
	if (!fs::exists(fileRoot))
		fs::create_directory(fileRoot);
	if (!fs::exists(fileRoot / "backups"))
		fs::create_directory(fileRoot / "backups");
}
//---------------------------------------------------------------------------
void PersistenceControl::setFile(std::string const& fileName, bool addExtension)
{
	fileName_ = fileName;
	if (addExtension && !fileName.empty())
		fileName_ = fileName_ + "." + WikiEditorConstants::saveFileExtension;
	nameStem_ = fs::path{fileName}.stem().string();
}
//---------------------------------------------------------------------------
void PersistenceControl::save()
{
	if (!fileName_.empty())
		controller_->save(fileName_);
}
//---------------------------------------------------------------------------
void PersistenceControl::load()
{
	if (!fileName_.empty())
		controller_->load(fileName_);
}
//---------------------------------------------------------------------------
void PersistenceControl::loadSelectedBackup()
{

}
//---------------------------------------------------------------------------
std::vector <std::string> PersistenceControl::enlistBackups(std::string const& backupRoot)
{
	std::vector <std::pair <fs::path, std::time_t> > result;
	for (fs::directory_iterator iter{backupRoot}, end; iter != end; ++iter)
	{
		if (fs::is_regular_file(iter->status()))
		{
			auto name = iter->path().stem().string();
			auto pos = name.find_last_of(' ');
			auto stamp = name.substr(pos, name.length() - pos);
			std::tm t;
			std::get_time(&t, WikiEditorConstants::timeStampMask);
			result.push_back(std::pair <fs::path, std::time_t>{iter->path(), std::mktime(&t)});
		}
	}

	// sort:
	std::sort(std::begin(result), std::end(result),
		[](std::pair <fs::path, std::time_t> const& lhs, std::pair <fs::path, std::time_t> const& rhs)
		{
			return lhs < rhs;
		}
	);
	std::vector <std::string> unpacked;
	for (auto const& i : result)
		unpacked.push_back(i.first.string());

	return unpacked;
}
//---------------------------------------------------------------------------
void PersistenceControl::backup()
{
	if (maxBackups_ == 0)
		return;

	fs::path backupRoot = fs::path{UserHome::getAppDataPath()} / "backups";
	auto backups = enlistBackups(backupRoot.string());
	if (backups.size() > maxBackups_ - 1)
	{
		for (auto i = std::begin(backups), end = std::begin(backups) + (backups.size() - maxBackups_ + 1); i < end; ++i)
		{
			std::remove(i->c_str());
            //DebugOut(*i);
        }
    }

	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	auto now = *std::localtime(&time);
	std::stringstream sstr;
	sstr << nameStem_
		 << ' '
		 << std::put_time(&now, WikiEditorConstants::timeStampMask)
		 << '.'
		 << WikiEditorConstants::saveFileExtension
	;
	auto backupFile = backupRoot / sstr.str();

	controller_->save(backupFile.string());
}
//---------------------------------------------------------------------------
void PersistenceControl::setMaxBackups(int maxBackups)
{
	if (maxBackups < 0)
		throw std::invalid_argument("maximum backup count must at least be 0");
	maxBackups_ = maxBackups;
}
//---------------------------------------------------------------------------
void PersistenceControl::startAutoBackup(int interval)
{
	backupTimer_.start(std::chrono::seconds{interval}, false);
}
//---------------------------------------------------------------------------
void PersistenceControl::stopAutoBackup()
{
    backupTimer_.stop();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
