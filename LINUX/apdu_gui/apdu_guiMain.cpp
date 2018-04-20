/***************************************************************
 * Name:      apdu_guiMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Aleksandar Krstic (aleksandar.krstic@d-logic.rs)
 * Created:   2018-04-03
 * Copyright: Aleksandar Krstic (www.d-logic.net)
 * License:
 **************************************************************/

#include "apdu_guiMain.h"
#include <wx/msgdlg.h>
#include "lib/include/uFCoder.h"
#include "ini.h"
#include "uFR.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#if __WIN32 || __WIN64
#include <conio.h>
#include <windows.h>
#elif linux || __linux__ || __APPLE__
#define __USE_MISC 1
#include <unistd.h>
#include <termios.h>
#undef __USE_MISC
#include "conio_gnu.h"
#else
#error "Unknown build platform."
#endif
#define RAW_RES_MAX_LEN 266
typedef const char *chr_ptr;
//(*InternalHeaders(apdu_guiFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

void dec_to_hex(uint32_t dec, char HEXA[1000]);

size_t response_len;
uint8_t response[RAW_RES_MAX_LEN];
char *resp = NULL;
uint8_t sw[2];
uint32_t le;
uint16_t *sw16_ptr = (uint16_t *)&sw;
wxString NDEF_TAG_APP_SELECT = "";
wxString READ_CC_SELECT = "";
wxString READ_NDEF = "";
uint32_t sw_int[2];
char sw_string1[4];
char sw_string2[4];
uint8_t file_id[2];
uint8_t lpucSak = 0;
uint8_t lpucUidSize = 0;
uint8_t aucUid[10];
uint32_t aucUid_integer[10];
char aucUid_string[255] = "";
uint8_t dl_card_type = 0;
wxString Status = ("");
UFR_STATUS status;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(apdu_guiFrame)
const long apdu_guiFrame::ID_BUTTON1 = wxNewId();
const long apdu_guiFrame::ID_BUTTON2 = wxNewId();
const long apdu_guiFrame::ID_BUTTON3 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT1 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT5 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL4 = wxNewId();
const long apdu_guiFrame::ID_BUTTON4 = wxNewId();
const long apdu_guiFrame::ID_BUTTON5 = wxNewId();
const long apdu_guiFrame::ID_PANEL1 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT7 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL6 = wxNewId();
const long apdu_guiFrame::ID_BUTTON6 = wxNewId();
const long apdu_guiFrame::ID_BUTTON7 = wxNewId();
const long apdu_guiFrame::ID_PANEL2 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT8 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL7 = wxNewId();
const long apdu_guiFrame::ID_BUTTON8 = wxNewId();
const long apdu_guiFrame::ID_BUTTON9 = wxNewId();
const long apdu_guiFrame::ID_PANEL3 = wxNewId();
const long apdu_guiFrame::ID_NOTEBOOK1 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT2 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL1 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT3 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL2 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT4 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL3 = wxNewId();
const long apdu_guiFrame::ID_BUTTON10 = wxNewId();
const long apdu_guiFrame::ID_BUTTON11 = wxNewId();
const long apdu_guiFrame::ID_STATICTEXT6 = wxNewId();
const long apdu_guiFrame::ID_TEXTCTRL5 = wxNewId();
const long apdu_guiFrame::idMenuQuit = wxNewId();
const long apdu_guiFrame::idMenuAbout = wxNewId();
const long apdu_guiFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(apdu_guiFrame,wxFrame)
    //(*EventTable(apdu_guiFrame)
    //*)
END_EVENT_TABLE()

apdu_guiFrame::apdu_guiFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(apdu_guiFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxGridSizer* GridSizer4;
    wxGridSizer* GridSizer3;
    wxGridSizer* GridSizer2;
    wxGridSizer* GridSizer6;
    wxBoxSizer* BoxSizer2;
    wxGridSizer* GridSizer5;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1200,693));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    GridSizer1 = new wxGridSizer(4, 2, -70, -250);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Commands"));
    Button1 = new wxButton(this, ID_BUTTON1, _("Reader Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticBoxSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(this, ID_BUTTON2, _("Reader Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticBoxSizer1->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(this, ID_BUTTON3, _("Reader Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    StaticBoxSizer1->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PortStatus = new wxStaticText(this, ID_STATICTEXT1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticBoxSizer1->Add(PortStatus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(720,490), 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    GridSizer2 = new wxGridSizer(3, 1, -400, 0);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Read System File on M24SRxx tags : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    GridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    ReadFileSystem = new wxTextCtrl(Panel1, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(700,390), wxTE_MULTILINE|wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    GridSizer2->Add(ReadFileSystem, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Button4 = new wxButton(Panel1, ID_BUTTON4, _("READ"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer2->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button5 = new wxButton(Panel1, ID_BUTTON5, _("CLEAR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer2->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(BoxSizer2, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel1->SetSizer(GridSizer2);
    GridSizer2->Fit(Panel1);
    GridSizer2->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    GridSizer5 = new wxGridSizer(3, 1, -400, 0);
    StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT7, _("Read CC on NFC Type 4 Tags :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    GridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    ReadCC = new wxTextCtrl(Panel2, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(700,390), wxTE_MULTILINE|wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    GridSizer5->Add(ReadCC, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Button6 = new wxButton(Panel2, ID_BUTTON6, _("READ"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer1->Add(Button6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button7 = new wxButton(Panel2, ID_BUTTON7, _("CLEAR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer1->Add(Button7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer5->Add(BoxSizer1, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel2->SetSizer(GridSizer5);
    GridSizer5->Fit(Panel2);
    GridSizer5->SetSizeHints(Panel2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    GridSizer6 = new wxGridSizer(3, 1, -400, 0);
    StaticText7 = new wxStaticText(Panel3, ID_STATICTEXT8, _("Read NDEF message on NFC Type 4 Tags : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    GridSizer6->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    ReadNDEF = new wxTextCtrl(Panel3, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(700,390), wxTE_MULTILINE|wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    GridSizer6->Add(ReadNDEF, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Button8 = new wxButton(Panel3, ID_BUTTON8, _("READ"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer3->Add(Button8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button9 = new wxButton(Panel3, ID_BUTTON9, _("CLEAR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer3->Add(Button9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer6->Add(BoxSizer3, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel3->SetSizer(GridSizer6);
    GridSizer6->Fit(Panel3);
    GridSizer6->SetSizeHints(Panel3);
    Notebook1->AddPage(Panel1, _("Read System File"), false);
    Notebook1->AddPage(Panel2, _("Read CC"), false);
    Notebook1->AddPage(Panel3, _("Read NDEF message "), false);
    GridSizer1->Add(Notebook1, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    GridSizer3 = new wxGridSizer(4, 2, 0, -35);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("DLL version : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DLL = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(161,21), wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridSizer3->Add(DLL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("UID : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    GridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    UID_label = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridSizer3->Add(UID_label, 1, wxALL|wxEXPAND, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Card type : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    GridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CardType_label = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    GridSizer3->Add(CardType_label, 1, wxALL|wxEXPAND, 5);
    Button10 = new wxButton(this, ID_BUTTON10, _("Check"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    GridSizer3->Add(Button10, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Button11 = new wxButton(this, ID_BUTTON11, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    GridSizer3->Add(Button11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    GridSizer1->Add(-1,-1,1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    GridSizer4 = new wxGridSizer(2, 1, -290, 0);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Reader Info : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    GridSizer4->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    ReaderInfo = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(400,300), wxTE_MULTILINE|wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    GridSizer4->Add(ReaderInfo, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    GridSizer1->Add(GridSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(GridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(GridSizer1);
    Layout();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton3Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton4Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton5Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton6Click);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton7Click);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton8Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton9Click);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton10Click);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&apdu_guiFrame::OnButton11Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&apdu_guiFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&apdu_guiFrame::OnAbout);
    //*)
}

apdu_guiFrame::~apdu_guiFrame()
{
    //(*Destroy(apdu_guiFrame)
    //*)
}

void apdu_guiFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void apdu_guiFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}





void apdu_guiFrame::OnButton1Click(wxCommandEvent& event)
{

    UFR_STATUS status;
    UFR_STATUS status2;
    wxString manufacturer = "";
    manufacturer <<  "Manufacturer:\n\n" << "Digital Logic RnD" << "\n======================================\n";

    status = ReaderOpen();

    ReaderInfo -> SetValue(GetReaderDescription()+manufacturer);

    if(status == UFR_OK){

        ReaderUISignal(1,1);

        PortStatus -> SetLabel("Port opened");

        DLL->SetValue(GetDllVersionStr());

    }else {


        PortStatus -> SetLabel("Port not opened");

    }

    status = GetCardIdEx(&lpucSak, aucUid, &lpucUidSize);

    Status = UFR_Status2String(status);

    switch(status){

    case UFR_OK:

    for (int j = 0; j < lpucUidSize; j++)
    {

        aucUid_integer[j] = aucUid[j];
    }

    for (int i = 0; i < lpucUidSize; i++)
    {

        dec_to_hex(aucUid_integer[i], aucUid_string);
    }

    UID_label->SetValue(aucUid_string);

    strcpy(aucUid_string, "");

    CardType_label->SetValue(GetDlTypeName(dl_card_type));

    break;

    default:

    UID_label->SetValue(Status);

    }

    status2 = GetDlogicCardType(&dl_card_type);

    Status = UFR_Status2String(status2);

    switch(status){

    case UFR_OK:

    CardType_label->SetValue(GetDlTypeName(dl_card_type));

    break;

    default:

    CardType_label->SetValue(Status);

    }


}

void apdu_guiFrame::OnButton2Click(wxCommandEvent& event)
{

    UFR_STATUS status;

    status = ReaderReset();

        if(status == UFR_OK){

        ReaderUISignal(1,1);

        PortStatus -> SetLabel("Reader reset");

        DLL->SetValue(GetDllVersionStr());

    }else {


        PortStatus -> SetLabel("Reader not reset");

    }

}

void apdu_guiFrame::OnButton3Click(wxCommandEvent& event)
{

    UFR_STATUS status;

    status = ReaderClose();

        if(status == UFR_OK){

        PortStatus -> SetLabel("Reader closed");

    }else {


        PortStatus -> SetLabel("Reader not closed");

    }


}

void dec_to_hex(uint32_t dec, char HEXA[1000])
{

    char hex[1000] = "";
    char hex1[1000] = "";

    switch (dec / 16)
    {
    case 0:
        strcpy(hex, "0");
    break;
    case 1:
        strcpy(hex, "1");
    break;
    case 2:
        strcpy(hex, "2");
    break;
    case 3:
        strcpy(hex, "3");
    break;
    case 4:
        strcpy(hex, "4");
    break;
    case 5:
        strcpy(hex, "5");
    break;
    case 6:
        strcpy(hex, "6");
    break;
    case 7:
        strcpy(hex, "7");
    break;
    case 8:
        strcpy(hex, "8");
    break;
    case 9:
        strcpy(hex, "9");
    break;
    case 10:
        strcpy(hex, "A");
    break;
    case 11:
        strcpy(hex, "B");
    break;
    case 12:
        strcpy(hex, "C");
    break;
    case 13:
        strcpy(hex, "D");
    break;
    case 14:
        strcpy(hex, "E");
    break;
    case 15:
        strcpy(hex, "F");
    break;
    }

    switch (dec % 16)
    {
    case 0:
        strcpy(hex1, "0");
    break;
    case 1:
        strcpy(hex1, "1");
    break;
    case 2:
        strcpy(hex1, "2");
    break;
    case 3:
        strcpy(hex1, "3");
    break;
    case 4:
        strcpy(hex1, "4");
    break;
    case 5:
        strcpy(hex1, "5");
    break;
    case 6:
        strcpy(hex1, "6");
    break;
    case 7:
        strcpy(hex1, "7");
    break;
    case 8:
        strcpy(hex1, "8");
    break;
    case 9:
        strcpy(hex1, "9");
    break;
    case 10:
        strcpy(hex1, "A");
    break;
    case 11:
        strcpy(hex1, "B");
    break;
    case 12:
        strcpy(hex1, "C");
    break;
    case 13:
        strcpy(hex1, "D");
    break;
    case 14:
        strcpy(hex1, "E");
    break;
    case 15:
        strcpy(hex1, "F");
    break;
    }

    strcat(HEXA, hex);
    strcat(HEXA, hex1);
}

void apdu_guiFrame::OnButton10Click(wxCommandEvent& event)
{
    UFR_STATUS status2;

    DLL -> SetValue(GetDllVersionStr());

    status = GetCardIdEx(&lpucSak, aucUid, &lpucUidSize);

    Status = UFR_Status2String(status);

    for (int j = 0; j < lpucUidSize; j++)
    {

        aucUid_integer[j] = aucUid[j];
    }

    for (int i = 0; i < lpucUidSize; i++)
    {

        dec_to_hex(aucUid_integer[i], aucUid_string);
    }

    if (status == UFR_OK)
    {

        UID_label->SetValue(aucUid_string);
        strcpy(aucUid_string, "");

    }
    else if (status != UFR_OK)
    {

        UID_label->SetValue(Status);
    }

    status2 = GetDlogicCardType(&dl_card_type);

    Status = UFR_Status2String(status2);

    switch(status){

    case UFR_OK:

    CardType_label->SetValue(GetDlTypeName(dl_card_type));

    break;

    default:

    CardType_label->SetValue(Status);


    }

}

size_t hex2bin(uint8_t *dst, const char *src)
{
    size_t dst_len = 0;
    char s_tmp[3];

    s_tmp[2] = '\0';

    while (*src)
    {
        while (((char)*src < '0' || (char)*src > '9') && ((char)*src < 'a' || (char)*src > 'f') && ((char)*src < 'A' || (char)*src > 'F'))
            src++; // skip delimiters, white spaces, etc.

        s_tmp[0] = (char)*src++;

        // Must be pair of the hex digits:
        if (!(*src))
            break;

        // And again, must be pair of the hex digits:
        if (((char)*src < '0' || (char)*src > '9') && ((char)*src < 'a' || (char)*src > 'f') && ((char)*src < 'A' || (char)*src > 'F'))
            break;

        s_tmp[1] = (char)*src++;

        *dst++ = strtoul(s_tmp, NULL, 16);
        dst_len++;
    }

    return dst_len;
}

void apdu_guiFrame::OnButton11Click(wxCommandEvent& event)
{

    DLL -> SetValue("");
    UID_label -> SetValue("");
    CardType_label -> SetValue("");
    strcpy(aucUid_string, "");
}

void apdu_guiFrame::OnButton4Click(wxCommandEvent& event)
{

status = SetISO14443_4_Mode();

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        ReadFileSystem->SetValue("Error while switching into ISO 14443-4 mode, uFR status is: " + Status);

        return;
    }

    NDEF_TAG_APP_SELECT << "=====================================================================\n";
    NDEF_TAG_APP_SELECT << "1. Issuing NDEF Tag Application Select command: [C] 00 A4 04 00 07 D2 76 00 00 85 01 01 00";
    NDEF_TAG_APP_SELECT << "\n-------------------------------------------------------------------------------------------------------------------\n";

    response_len = RAW_RES_MAX_LEN;

    status = ApduCommand("00 A4 04 00 07 D2760000850101 00", &resp, sw);

    Status = UFR_Status2String(status);

    ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);

    if (status != UFR_OK)
    {

        NDEF_TAG_APP_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            NDEF_TAG_APP_SELECT << "\nCould not continue execution due to an APDU error"
                                << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
        }

        response_len = strlen(resp);


        NDEF_TAG_APP_SELECT << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        NDEF_TAG_APP_SELECT << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
    }

    ///---------------------------------------------------------------------------------------------------------------------------------------------------------------
    NDEF_TAG_APP_SELECT << "\n=====================================================================\n";
    NDEF_TAG_APP_SELECT << "2. Issuing System File Select command: [C] 00 A4 00 0C 02 E1 01\n";
    NDEF_TAG_APP_SELECT << "-------------------------------------------------------------------------------------------------------------------\n";

    status = ApduCommand("00 A4 00 0C 02 E101", &resp, sw);

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        NDEF_TAG_APP_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            NDEF_TAG_APP_SELECT << "\nCould not continue execution due to an APDU error"
                                << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
        }

        response_len = strlen(resp);

        NDEF_TAG_APP_SELECT << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        NDEF_TAG_APP_SELECT << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
    }

    NDEF_TAG_APP_SELECT << "\n=====================================================================\n";
    NDEF_TAG_APP_SELECT << "3. Issuing ReadBinary command (first two bytes contains file size): [C] 00 B0 00 00 02\n";
    NDEF_TAG_APP_SELECT << "-------------------------------------------------------------------------------------------------------------------\n";

    status = ApduCommand("00 B0 00 00 02", &resp, sw);

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        NDEF_TAG_APP_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            NDEF_TAG_APP_SELECT << "\nCould not continue execution due to an APDU error"
                                << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
        }

        response_len = strlen(resp);

        NDEF_TAG_APP_SELECT << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        NDEF_TAG_APP_SELECT << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
    }

    le = strtol(resp, NULL, 16);

    char le_string[10];

    sprintf(le_string, "%02X", le);

    NDEF_TAG_APP_SELECT << "\n=====================================================================\n";
    NDEF_TAG_APP_SELECT << "4. Issuing ReadBinary command (entire file size = " << (int)le << " decimal): "
                        << "[C] 00 B0 00 00 " << le_string;
    NDEF_TAG_APP_SELECT << "\n-------------------------------------------------------------------------------------------------------------------\n";

    status = APDUTransceive(0x00, 0xB0, 0x00, 0x00, NULL, 0, response, &le, 1, sw);

    if (status != UFR_OK)
    {

        NDEF_TAG_APP_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT + Status);
    }
    else
    {

        if (response_len)
        {

            NDEF_TAG_APP_SELECT << "\nAPDU command executed: response data length = " << (int)le;

            uint32_t response_integer[RAW_RES_MAX_LEN];

            for (uint32_t i = 0; i < le; i++)
            {

                response_integer[i] = response[i];
            }

            char RESPONSE[RAW_RES_MAX_LEN] = "";

            for (uint32_t j = 0; j < le; j++)
            {

                dec_to_hex(response_integer[j], RESPONSE);
            }

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%02X", sw_int[0]);
            sprintf(sw_string2, "%02X", sw_int[1]);

            NDEF_TAG_APP_SELECT << "\n[R] : " << RESPONSE << "\n [SW] : " << sw_string1 << " " << sw_string2;

            ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
        }

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            NDEF_TAG_APP_SELECT << "\nCould not continue execution due to an APDU error"
                                << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadFileSystem->SetValue(NDEF_TAG_APP_SELECT);
        }
    }

    s_block_deselect(100);


}


void apdu_guiFrame::OnButton5Click(wxCommandEvent& event)
{

    ReadFileSystem -> SetValue("");
    NDEF_TAG_APP_SELECT = "";
}

void apdu_guiFrame::OnButton6Click(wxCommandEvent& event)
{

        status = SetISO14443_4_Mode();

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        ReadCC->SetValue("Error while switching into ISO 14443-4 mode, uFR status is: " + Status);

        return;
    }

    READ_CC_SELECT << "=====================================================================\n";
    READ_CC_SELECT << "1. Issuing NDEF Tag Application Select command: [C] 00 A4 04 00 07 D2 76 00 00 85 01 01 00";
    READ_CC_SELECT << "\n-------------------------------------------------------------------------------------------------------------------\n";

    response_len = RAW_RES_MAX_LEN;

    status = ApduCommand("00 A4 04 00 07 D2760000850101 00", &resp, sw);

    Status = UFR_Status2String(status);

    ReadCC->SetValue(READ_CC_SELECT);

    if (status != UFR_OK)
    {

        READ_CC_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadCC->SetValue(READ_CC_SELECT + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_CC_SELECT << "\nCould not continue execution due to an APDU error"
                           << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadCC->SetValue(READ_CC_SELECT);
        }

        response_len = strlen(resp);


        READ_CC_SELECT << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_CC_SELECT << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadCC->SetValue(READ_CC_SELECT);
    }

    READ_CC_SELECT << "\n=====================================================================\n";
    READ_CC_SELECT << "2. Issuing CC Select command: [C] 00 A4 00 0C 02 E1 03\n";
    READ_CC_SELECT << "-------------------------------------------------------------------------------------------------------------------\n";

    status = ApduCommand("00 A4 00 0C 02 E103", &resp, sw);

    Status = UFR_Status2String(status);

    ReadCC->SetValue(READ_CC_SELECT);

    if (status != UFR_OK)
    {

        READ_CC_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadCC->SetValue(READ_CC_SELECT + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_CC_SELECT << "\nCould not continue execution due to an APDU error"
                           << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadCC->SetValue(READ_CC_SELECT);
        }

        response_len = strlen(resp);

        READ_CC_SELECT << "APDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_CC_SELECT << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadCC->SetValue(READ_CC_SELECT);
    }

    READ_CC_SELECT << "\n=====================================================================\n";
    READ_CC_SELECT << "3. Issuing ReadBinary command (first two bytes contains file size): [C] 00 B0 00 00 02\n";
    READ_CC_SELECT << "-------------------------------------------------------------------------------------------------------------------\n";

    status = ApduCommand("00 B0 00 00 02", &resp, sw);

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        READ_CC_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadCC->SetValue(READ_CC_SELECT + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_CC_SELECT << "\nCould not continue execution due to an APDU error"
                           << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadCC->SetValue(READ_CC_SELECT);
        }

        response_len = strlen(resp);

        READ_CC_SELECT << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_CC_SELECT << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadCC->SetValue(READ_CC_SELECT);
    }

    le = strtol(resp, NULL, 16);

    char le_string[10];

    sprintf(le_string, "%02X", le);

    READ_CC_SELECT << "\n=====================================================================\n";
    READ_CC_SELECT << "4. Issuing ReadBinary command (entire file size = " << (int)le << " decimal): "
                   << "[C] 00 B0 00 00 " << le_string;
    READ_CC_SELECT << "\n-------------------------------------------------------------------------------------------------------------------\n";

    status = APDUTransceive(0x00, 0xB0, 0x00, 0x00, NULL, 0, response, &le, 1, sw);

    if (status != UFR_OK)
    {

        READ_CC_SELECT = "Error while executing APDU command, uFR status is: ";

        ReadCC->SetValue(READ_CC_SELECT + Status);
    }
    else
    {

        if (response_len)
        {

            READ_CC_SELECT << "\nAPDU command executed: response data length = " << (int)le;

            uint32_t response_integer[RAW_RES_MAX_LEN];

            for (uint32_t i = 0; i < le; i++)
            {

                response_integer[i] = response[i];
            }

            char RESPONSE[RAW_RES_MAX_LEN] = "";

            for (uint32_t j = 0; j < le; j++)
            {

                dec_to_hex(response_integer[j], RESPONSE);
            }

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%02X", sw_int[0]);
            sprintf(sw_string2, "%02X", sw_int[1]);

            READ_CC_SELECT << "\n[R] : " << RESPONSE << "\n [SW] : " << sw_string1 << " " << sw_string2;

            ReadCC->SetValue(READ_CC_SELECT);
        }

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_CC_SELECT << "\nCould not continue execution due to an APDU error"
                           << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadCC->SetValue(READ_CC_SELECT);
        }
    }

    s_block_deselect(100);

}

void apdu_guiFrame::OnButton7Click(wxCommandEvent& event)
{

    ReadCC -> SetValue("");
    READ_CC_SELECT = "";

}

void apdu_guiFrame::OnButton8Click(wxCommandEvent& event)
{

     status = SetISO14443_4_Mode();

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        ReadNDEF->SetValue("Error while switching into ISO 14443-4 mode, uFR status is: " + Status);

        return;
    }

    READ_NDEF << "=====================================================================\n";
    READ_NDEF << "1. Issuing NDEF Tag Application Select command: [C] 00 A4 04 00 07 D2 76 00 00 85 01 01 00";
    READ_NDEF << "\n-------------------------------------------------------------------------------------------------------------------\n";

    response_len = RAW_RES_MAX_LEN;

    status = ApduCommand("00 A4 04 00 07 D2760000850101 00", &resp, sw);

    Status = UFR_Status2String(status);

    ReadNDEF->SetValue(READ_NDEF);

    if (status != UFR_OK)
    {

        READ_NDEF = "Error while executing APDU command, uFR status is: ";

        ReadNDEF->SetValue(READ_NDEF + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_NDEF << "\nCould not continue execution due to an APDU error"
                      << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }

        response_len = strlen(resp);


        READ_NDEF << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_NDEF << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadNDEF->SetValue(READ_NDEF);
    }

    READ_NDEF << "\n=====================================================================\n";
    READ_NDEF << "2. Issuing CC Select command: [C] 00 A4 00 0C 02 E1 03\n";
    READ_NDEF << "-------------------------------------------------------------------------------------------------------------------\n";

    status = ApduCommand("00 A4 00 0C 02 E103", &resp, sw);

    Status = UFR_Status2String(status);

    ReadNDEF->SetValue(READ_NDEF);

    if (status != UFR_OK)
    {

        READ_NDEF = "Error while executing APDU command, uFR status is: ";

        ReadNDEF->SetValue(READ_NDEF + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_NDEF << "\nCould not continue execution due to an APDU error"
                      << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }

        response_len = strlen(resp);

        READ_NDEF << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_NDEF << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadNDEF->SetValue(READ_NDEF);
    }

    READ_NDEF << "\n=====================================================================\n";
    READ_NDEF << "3. Issuing ReadBinary command (first two bytes contains file size): [C] 00 B0 00 00 02\n";
    READ_NDEF << "-------------------------------------------------------------------------------------------------------------------\n";

    status = ApduCommand("00 B0 00 00 02", &resp, sw);

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        READ_NDEF = "Error while executing APDU command, uFR status is: ";

        ReadNDEF->SetValue(READ_NDEF + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_NDEF << "\nCould not continue execution due to an APDU error"
                      << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }

        response_len = strlen(resp);

        READ_NDEF << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_NDEF << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadNDEF->SetValue(READ_NDEF);
    }

    le = strtol(resp, NULL, 16);

    char le_string[10];

    sprintf(le_string, "%02X", le);

    READ_NDEF << "\n=====================================================================\n";
    READ_NDEF << "4. Issuing ReadBinary command (entire file size = " << (int)le << " decimal): "
              << "[C] 00 B0 00 00 " << le_string;
    READ_NDEF << "\n-------------------------------------------------------------------------------------------------------------------\n";

    status = APDUTransceive(0x00, 0xB0, 0x00, 0x00, NULL, 0, response, &le, 1, sw);

    if (status != UFR_OK)
    {

        READ_NDEF = "Error while executing APDU command, uFR status is: ";

        ReadNDEF->SetValue(READ_NDEF + Status);
    }
    else
    {

        if (response_len)
        {

            READ_NDEF << "\nAPDU command executed: response data length = " << (int)le;

            uint32_t response_integer[RAW_RES_MAX_LEN];

            for (uint32_t i = 0; i < le; i++)
            {

                response_integer[i] = response[i];
            }

            char RESPONSE[RAW_RES_MAX_LEN] = "";

            for (uint32_t j = 0; j < le; j++)
            {

                dec_to_hex(response_integer[j], RESPONSE);
            }

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%02X", sw_int[0]);
            sprintf(sw_string2, "%02X", sw_int[1]);

            READ_NDEF << "\n[R] : " << RESPONSE << "\n [SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_NDEF << "\nCould not continue execution due to an APDU error"
                      << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }
    }

    uint32_t file_id_integer[2];

    char file_id_string1[4] = "";
    char file_id_string2[4] = "";

    READ_NDEF << "\n=====================================================================\n";
    READ_NDEF << "5. Parse CC for NDEF FileID (offset = 0x09): \n";
    READ_NDEF << "-------------------------------------------------------------------------------------------------------------------\n";

    memcpy(file_id, &response[9], 2);

    file_id_integer[0] = file_id[0];
    file_id_integer[1] = file_id[1];

    sprintf(file_id_string1, "%02X", file_id_integer[0]);
    sprintf(file_id_string2, "%02X", file_id_integer[1]);

    READ_NDEF << file_id_string1 << " " << file_id_string2;

    ReadNDEF->SetValue(READ_NDEF);

    READ_NDEF << "\n=====================================================================\n";
    READ_NDEF << "6. Issuing NDEF File Select command:  [C] 00 A4 00 0C 02 " << file_id_string1 << " " << file_id_string2;
    READ_NDEF << "\n-------------------------------------------------------------------------------------------------------------------\n";

    status = APDUTransceive(0x00, 0xA4, 0x00, 0x0C, file_id, 2, response, &le, 0, sw);

    if (status != UFR_OK)
    {

        READ_NDEF = "Error while executing APDU command, uFR status is: ";

        ReadNDEF->SetValue(READ_NDEF + Status);
    }
    else
    {

        READ_NDEF << "\nAPDU command executed: response data length = " << (int)le;
        READ_NDEF << "\n[R] : ";

        if (response_len)
        {

            uint32_t response_le_integer[RAW_RES_MAX_LEN];
            char RESPONSE_LE[RAW_RES_MAX_LEN] = "";

            for (uint32_t i = 0; i < le; i++)
            {

                response_le_integer[i] = response[i];
            }

            for (uint32_t j = 0; j < le; j++)
            {

                dec_to_hex(response_le_integer[j], RESPONSE_LE);
            }

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%02X", sw_int[0]);
            sprintf(sw_string2, "%02X", sw_int[1]);

            READ_NDEF << RESPONSE_LE << "\n [SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_NDEF << "\nCould not continue execution due to an APDU error"
                      << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }
    }

    READ_NDEF << "\n=====================================================================\n";
    READ_NDEF << "7. Issuing \"ReadBinary\" command (first two bytes contains file size): [C] 00 B0 00 00 02 \n";
    READ_NDEF << "-------------------------------------------------------------------------------------------------------------------\n";

    response_len = RAW_RES_MAX_LEN;

    status = ApduCommand("00 B0 00 00 02", &resp, sw);

    Status = UFR_Status2String(status);

    if (status != UFR_OK)
    {

        READ_NDEF = "Error while executing APDU command, uFR status is: ";

        ReadNDEF->SetValue(READ_NDEF + Status);
    }
    else
    {

        if (*sw16_ptr != 0x90)
        {

            sw_int[0] = sw[0];
            sw_int[1] = sw[1];

            sprintf(sw_string1, "%X", sw_int[0]);
            sprintf(sw_string2, "%X", sw_int[1]);

            READ_NDEF << "\nCould not continue execution due to an APDU error"
                      << "\n[SW] : " << sw_string1 << " " << sw_string2;

            ReadNDEF->SetValue(READ_NDEF);
        }

        response_len = strlen(resp);

        READ_NDEF << "\nAPDU command executed: response data length = " << response_len;

        sw_int[0] = sw[0];
        sw_int[1] = sw[1];

        sprintf(sw_string1, "%02X", sw_int[0]);
        sprintf(sw_string2, "%02X", sw_int[1]);

        READ_NDEF << "\n[R] : " << resp << "\n [SW] : " << sw_string1 << " " << sw_string2;

        ReadNDEF->SetValue(READ_NDEF);
    }

    s_block_deselect(100);
}

void apdu_guiFrame::OnButton9Click(wxCommandEvent& event)
{
    READ_NDEF = "";
    ReadNDEF -> SetValue("");

}
