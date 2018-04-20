/***************************************************************
 * Name:      apdu_guiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Aleksandar Krstic (aleksandar.krstic@d-logic.rs)
 * Created:   2018-04-03
 * Copyright: Aleksandar Krstic (www.d-logic.net)
 * License:
 **************************************************************/

#include "apdu_guiApp.h"

//(*AppHeaders
#include "apdu_guiMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(apdu_guiApp);

bool apdu_guiApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	apdu_guiFrame* Frame = new apdu_guiFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
