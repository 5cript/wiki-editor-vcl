//---------------------------------------------------------------------------

#pragma hdrstop

#include "user_files.h"
#include "constants.h"

#include <initguid.h>
#include <shlobj.h>
#include <knownfolders.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
//---------------------------------------------------------------------------
std::string UserHome::getAppDataPath()
{
	static std::string p = {};
	if (!p.empty())
		return p;

	PWSTR path = nullptr;
	HRESULT hr = SHGetKnownFolderPath(
		FOLDERID_RoamingAppData, // do not use local, because net synchronized folders are a bliss
		KF_FLAG_NO_ALIAS,
		nullptr,
        &path
	);
	p = (fs::path(path) / WikiEditorConstants::programName).string();
	CoTaskMemFree(path);

	if (hr == S_OK)
		return p;
	else
		throw std::runtime_error("Could not get %appdata% (roaming)");
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
