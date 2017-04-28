//---------------------------------------------------------------------------

#ifndef StylePickerH
#define StylePickerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>

#include "ui_elements/styling/style_container.h"

#include <string>
#include <boost/optional.hpp>
//---------------------------------------------------------------------------
class TFrameStylePicker : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TColorDialog *ColorDialog;
	TLabel *Label1;
	TButton *ChangeFontColor;
	TSpinEdit *FontSize;
	TLabel *Label2;
	TPanel *ExampleFrame;
	TLabel *Label3;
	TButton *ChangeBackgroundColor;
	TCheckBox *BoldState;
	TCheckBox *ItalicState;
	TButton *Button1;
	TButton *Button2;
	TComboBox *Alignment;
	void __fastcall FontColorExampleClick(TObject *Sender);
	void __fastcall ChangeBackgroundColorClick(TObject *Sender);
	void __fastcall BoldStateClick(TObject *Sender);
	void __fastcall ItalicStateClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FontSizeChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall AlignmentChange(TObject *Sender);
private:	// Benutzer-Deklarationen
	bool abort_;
public:		// Benutzer-Deklarationen
	void translate();
	/**
	 *  Will parse param style and initialize the dialog state with it.
	 *  @return Returns the changed style, or boost::none if aborted.
	 */
	boost::optional <std::string> show(std::string const& styleString, StyleContainment::Style baseStyle);
	__fastcall TFrameStylePicker(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrameStylePicker *FrameStylePicker;
//---------------------------------------------------------------------------
#endif
