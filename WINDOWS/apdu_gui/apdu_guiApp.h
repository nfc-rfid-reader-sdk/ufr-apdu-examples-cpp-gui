/***************************************************************
 * Name:      apdu_guiApp.h
 * Purpose:   Defines Application Class
 * Author:    Aleksandar Krstic (aleksandar.krstic@d-logic.rs)
 * Created:   2018-04-03
 * Copyright: Aleksandar Krstic (www.d-logic.net)
 * License:
 **************************************************************/

#ifndef APDU_GUIAPP_H
#define APDU_GUIAPP_H

#include <wx/app.h>

class apdu_guiApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // APDU_GUIAPP_H
