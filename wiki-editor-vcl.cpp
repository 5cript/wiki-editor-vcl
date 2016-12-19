//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("ui_elements\frames\header_options.cpp", HeaderOptionsFrame); /* TFrame: File Type */
USEFORM("ui_elements\frames\text_options.cpp", TextOptionsFrame); /* TFrame: File Type */
USEFORM("ui_elements\frames\style_options.cpp", StyleOptionsFrame); /* TFrame: File Type */
USEFORM("About.cpp", AboutForm);
USEFORM("Editor.cpp", MainEditor);
USEFORM("LayoutTest.cpp", TestForm);
USEFORM("ui_elements\frames\table_options.cpp", TableOptionsFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainEditor), &MainEditor);
		Application->CreateForm(__classid(TAboutForm), &AboutForm);
		Application->CreateForm(__classid(TTestForm), &TestForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
