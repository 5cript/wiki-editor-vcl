//---------------------------------------------------------------------------
#pragma once

#include "controller.h"
#include "mini_timer.h"

#include <string>
#include <vector>
//---------------------------------------------------------------------------
class PersistenceControl
{
public:
	PersistenceControl(
		PageController* controller,
		std::string const& fileName = "",
		bool addExtension = true,
		int maxBackups = 100
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
	void backup();

	/**
	 * 	Set the maximum of backups.
	 */
	void setMaxBackups(int maxBackups);

	/**
	 * 	Opens a GUI to select a backup file to load.
	 */
	void loadSelectedBackup();

	/**
	 *	Sets the auto backup interval.
	 *
	 *  @param interval The backup interval in seconds.
	 */
	void setAutoBackupInterval(int interval);

	/**
	 * 	Starts the automatic backup.
	 */
	void startAutoBackup();

	/**
	 * 	Stop Automatic Backup.
	 */
	void stopAutoBackup();

	/**
	 * 	Returns the parent directory of the lastly saved file.
	 */
	std::string getParentDirectory() const;

private:
	std::vector <std::string> enlistBackups(std::string const& backupRoot);

    // This function is called by the timer.
	bool automaticBackup();

private:
	PageController* controller_;
    Timer backupTimer_;
	std::string fileName_;
	std::string nameStem_;
	int maxBackups_;
	int intervalS_;
};
//---------------------------------------------------------------------------