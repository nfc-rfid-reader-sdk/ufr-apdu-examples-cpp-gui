/***************************************************************
 * Name:      apdu_guiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Aleksandar Krstic (aleksandar.krstic@d-logic.rs)
 * Created:   2018-04-03
 * Copyright: Aleksandar Krstic (www.d-logic.net)
 * License:
 **************************************************************/

#ifndef APDU_GUIMAIN_H
#define APDU_GUIMAIN_H

//(*Headers(apdu_guiFrame)
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class apdu_guiFrame: public wxFrame
{
    public:

        apdu_guiFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~apdu_guiFrame();

    private:

        //(*Handlers(apdu_guiFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton10Click(wxCommandEvent& event);
        void OnButton11Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnButton6Click(wxCommandEvent& event);
        void OnButton7Click(wxCommandEvent& event);
        void OnButton8Click(wxCommandEvent& event);
        void OnButton9Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(apdu_guiFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_PANEL1;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL6;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_PANEL2;
        static const long ID_STATICTEXT8;
        static const long ID_TEXTCTRL7;
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_PANEL3;
        static const long ID_NOTEBOOK1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON10;
        static const long ID_BUTTON11;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL5;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(apdu_guiFrame)
        wxStaticText* PortStatus;
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        wxButton* Button4;
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxStaticText* StaticText1;
        wxTextCtrl* DLL;
        wxPanel* Panel2;
        wxButton* Button8;
        wxStaticText* StaticText3;
        wxTextCtrl* ReadFileSystem;
        wxButton* Button5;
        wxTextCtrl* ReadNDEF;
        wxButton* Button9;
        wxTextCtrl* CardType_label;
        wxPanel* Panel3;
        wxStaticText* StaticText7;
        wxTextCtrl* ReadCC;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxNotebook* Notebook1;
        wxStaticText* StaticText6;
        wxButton* Button11;
        wxTextCtrl* UID_label;
        wxButton* Button7;
        wxTextCtrl* ReaderInfo;
        wxButton* Button6;
        wxButton* Button10;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // APDU_GUIMAIN_H
    