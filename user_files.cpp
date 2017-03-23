//---------------------------------------------------------------------------

#pragma hdrstop

#include "user_files.h"
#include "constants.h"

#include <System.Classes.hpp>

#include <initguid.h>
#include <shlobj.h>
#include <knownfolders.h>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

namespace fs = boost::filesystem;
//---------------------------------------------------------------------------
boost::optional <std::string> getFolderPath(REFKNOWNFOLDERID rfid)
{
	PWSTR path = nullptr;
	HRESULT hr = SHGetKnownFolderPath(
		rfid, // do not use local, because net synchronized folders are a bliss
		KF_FLAG_NO_ALIAS,
		nullptr,
		&path
	);
    std::string p{UTF8String(path).c_str()};
	CoTaskMemFree(path);

	if (hr == S_OK)
		return p;
	else
		return boost::none;
}
//---------------------------------------------------------------------------
std::string UserHome::getAppDataPath()
{
	static std::string p = {};
	if (!p.empty())
		return p;

	auto path = getFolderPath(FOLDERID_RoamingAppData);
	if (!path)
		throw std::runtime_error("Could not get %appdata% (roaming)");

	p = (fs::path(path.get()) / WikiEditorConstants::programName).string();

    return p;
}
//---------------------------------------------------------------------------
std::string UserHome::getHomePath()
{
	static std::string p = {};
	if (!p.empty())
		return p;

	auto path = getFolderPath(FOLDERID_Documents);
	if (!path)
		throw std::runtime_error("Could not get %USERPROFILE%\\Documents");
	else
		p = path.get();

	return p;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
