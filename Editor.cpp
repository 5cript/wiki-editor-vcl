//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"

/*
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.h"
#   include "SimpleJSON/parse/jsd_convenience.h"
#   include "SimpleJSON/stringify/jss.h"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#endif
*/
//---------------------------------------------------------------------------
/*
struct ConfigContent : public JSON::Stringifiable <ConfigContent>
                     , public JSON::Parsable <ConfigContent>
{
    int id;
    std::string libPath;
    std::vector <std::string> someContainer;
};

BOOST_FUSION_ADAPT_STRUCT
(
    ConfigContent,
    (int, id)
    (std::string, libPath)
    (std::vector <std::string>, someContainer)
)

ConfigContent parse(std::istream& json)
{
    ConfigContent cc;
    auto tree = JSON::parse_json(json);
    JSON::parse(cc, "config_content", tree);
    return cc;
}

std::ostream& stringify(std::ostream& stream, ConfigContent const& cc)
{
    stream << "{";
    JSON::try_stringify(stream, "config_content", cc, JSON::ProduceNamedOutput);
    stream << "}";
    return stream;
}
*/

#pragma package(smart_init)
#pragma resource "*.dfm"
TMainEditor *MainEditor;
//---------------------------------------------------------------------------
__fastcall TMainEditor::TMainEditor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainEditor::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TMainEditor::LoadPage()
{
	ShowMessage("Test");
}
//---------------------------------------------------------------------------

void __fastcall TMainEditor::Button1Click(TObject *Sender)
{
/*
	ConfigContent cc;
	cc.id = 2;
	cc.libPath = "./somewhere";
	cc.someContainer = {"Hello", "World"};

	std::stringstream sstr;
	stringify(sstr, cc);
	auto unnecessarilyComplexCopy = parse(sstr);

	ShowMessage(String(sstr.str().c_str()));
*/
}
//---------------------------------------------------------------------------

