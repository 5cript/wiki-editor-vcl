//---------------------------------------------------------------------------
#pragma once

#include "controller.h"

#include <string>
#include <vector>
//---------------------------------------------------------------------------
class PersistenceControl
{
public:
	PersistenceControl(
		PageController* controller,
		std::string const& fileName = "",
		bool addExtension = true
	);

	~PersistenceControl() = default;
	PersistenceControl& operator=(PersistenceControl const&) = delete;
	PersistenceControl& operator=(PersistenceControl&&) = delete;

	PersistenceControl(PersistenceControl const&) = delete;
	PersistenceControl(PersistenceControl&&) = delete;

	/**
	 *	Sets up folders required for backup files.
	 */
	static void setupBackupStructure();

	/**
	 *  Set the file to interact with.
	 */
	void setFile(std::string const& fileName, bool addExtension = true);

	/**
	 * 	Saves the controller state into the file.
	 */
	void save();

	/**
	 *  Loads the file content into the controller.
	 */
	void load();

	/**
	 * 	Creates a backup with the name of the file.
	 *	Backups rotate up to a limit.
	 */
	void backup(int maxBackups);

	/**
	 * 	Opens a GUI to select a backup file to load.
	 */
	void loadSelectedBackup();

private:
	std::vector <std::string> enlistBackups(std::string const& backupRoot);

private:
	PageController* controller_;
	std::string fileName_;
	std::string nameStem_;
};
//---------------------------------------------------------------------------