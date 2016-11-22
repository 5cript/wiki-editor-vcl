//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <string>
#include <vcl.h>
//---------------------------------------------------------------------------
bool SaveResourceToFile(wchar_t const* resourceName, wchar_t const* fileName)
{
	HRSRC hrsrc = FindResource(HInstance, resourceName, RT_RCDATA);
	if (hrsrc == NULL)
		return false;
	DWORD size = SizeofResource(HInstance, hrsrc);
	HGLOBAL hglob = LoadResource(HInstance, hrsrc);
	LPVOID rdata = LockResource(hglob);
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	try
	{
		DWORD writ;
		WriteFile(hFile, rdata, size, &writ, NULL);
	}
	catch (...)
	{
	}
	CloseHandle(hFile);
	return true;
}
//---------------------------------------------------------------------------