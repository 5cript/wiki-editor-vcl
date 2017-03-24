//---------------------------------------------------------------------------
#pragma once

#include "persistence_control.h"

#include <string>
#include <stdexcept>
//---------------------------------------------------------------------------
#define EXCEPTION_META std::string{"("} + __FILE__ + ":" + std::to_string(__LINE__) + ")"
//---------------------------------------------------------------------------
enum class SaveWarningResult
{
	Discard,
	Cancel,
	Save
};

enum class SaveResult
{
	Cancel,
	Saved
};

enum class AbortContinueCase
{
	Abort,
	Continue
};
//---------------------------------------------------------------------------
/**
 *  Open MessageBox to ask if the user wants to save current progress.
 */
SaveWarningResult PromptSaveWarning();

/**
 *  Opens Save Dialog and saves file if not cancelled.
 */
SaveResult SaveAsDialog(PersistenceControl& persistence);

/**
 *  PromptSaveWarning() and Save if needed.
 *	Will return if the data loss action may proceed or not.
 */
AbortContinueCase WarnAndSave(PersistenceControl& persistence);

/**
 *	Open Article if not cancelled.
 */
void OpenArticle(PersistenceControl& persistence);

/**
 *  Show a MessageBox with the exception message and line + file.
 */
void DisplayException(std::exception const& exc, std::string const& metaInfo,
					  std::string const& replacementMessage = "");

AbortContinueCase ElementDeletionWarning();
//---------------------------------------------------------------------------
