//---------------------------------------------------------------------------

#pragma hdrstop

#include "common_dialogs.h"

#include "localization.h"
#include "constants.h"

#include <Vcl.Dialogs.hpp>

#include <memory>
#include <stdexcept>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
SaveWarningResult PromptSaveWarning()
{
	auto res = MessageBox(
		nullptr,
		translate("$WantSave?").c_str(),
		translate("$LossWarningCaption").c_str(),
		MB_YESNOCANCEL | MB_ICONWARNING
	);
	if (res == IDCANCEL || res == IDABORT)
		return SaveWarningResult::Cancel;
	if (res == IDYES)
		return SaveWarningResult::Save;
	if (res == IDNO)
		return SaveWarningResult::Discard;
	throw std::runtime_error(std::string{"SaveWarning returned with unexpected response"}
		+ __FILE__ + ":" + std::to_string(__LINE__)
	);
}
//---------------------------------------------------------------------------
SaveResult SaveAsDialog(PersistenceControl& persistence)
{
	std::unique_ptr <TSaveDialog> dialog {new TSaveDialog(nullptr)};
	dialog->Title = translate("$SaveAsDialogTitle");
	dialog->InitialDir = persistence.getParentDirectory().c_str();
	dialog->Filter = (
		translate("$WikiArticleFilter") + "|*." + WikiEditorConstants::saveFileExtension + "|" +
		translate("$AllFilesFilter") + "|*.*"
	).c_str();
	dialog->DefaultExt = WikiEditorConstants::saveFileExtension;
	dialog->FilterIndex = 1;

	if (dialog->Execute())
	{
		persistence.stopAutoBackup();
		persistence.setFile(UTF8String{dialog->FileName}.c_str(), false);
		persistence.save();
		persistence.startAutoBackup();
		return SaveResult::Saved;
	}
	else
		return SaveResult::Cancel;
}
//---------------------------------------------------------------------------
AbortContinueCase WarnAndSave(PersistenceControl& persistence)
{
	auto res = PromptSaveWarning();
	if (res == SaveWarningResult::Cancel)
		return AbortContinueCase::Abort;
	if (res == SaveWarningResult::Discard)
		return AbortContinueCase::Continue;
	if (res == SaveWarningResult::Save)
	{
		auto res2 = SaveAsDialog(persistence);
		if (res2 == SaveResult::Cancel)
			return AbortContinueCase::Abort;
		if (res2 == SaveResult::Saved)
			return AbortContinueCase::Continue;
	}
	throw std::runtime_error(std::string{"Unreachable code execution error"}
		+ __FILE__ + ":" + std::to_string(__LINE__)
	);
}
//---------------------------------------------------------------------------
void OpenArticle(PersistenceControl& persistence)
{
	std::unique_ptr <TOpenDialog> dialog {new TOpenDialog(nullptr)};
	dialog->Title = translate("$OpenDialogTitle");
	dialog->InitialDir = persistence.getParentDirectory().c_str();
    dialog->Filter = (
		translate("$WikiArticleFilter") + "|*." + WikiEditorConstants::saveFileExtension + "|" +
		translate("$AllFilesFilter") + "|*.*"
	).c_str();
	dialog->FilterIndex = 1;

	if (dialog->Execute())
	{
		persistence.stopAutoBackup();
		persistence.setFile(UTF8String{dialog->FileName}.c_str(), false);
        persistence.load();
		persistence.startAutoBackup();
	}
}
//---------------------------------------------------------------------------
void DisplayException(std::exception const& exc, std::string const& metaInfo,
					  std::string const& replacementMessage)
{
	String msg;
	if (replacementMessage.empty())
		msg = translate("$ExceptionOccurred") + "\r\n" + exc.what() + "\r\n" + metaInfo.c_str();
	else
		msg = translate(replacementMessage.c_str()) + "\r\n" + exc.what() + "\r\n" + metaInfo.c_str();
	ShowMessage(msg);
}
//---------------------------------------------------------------------------
AbortContinueCase ElementDeletionWarning()
{
    auto res = MessageBox(
		nullptr,
		::translate("$ReallyWantRemove").c_str(),
		::translate("$LossWarningCaption").c_str(),
		MB_YESNO | MB_ICONWARNING
	);
	if (res == IDYES)
		return AbortContinueCase::Continue;
	return AbortContinueCase::Abort;
}
//---------------------------------------------------------------------------
