#include "ModeSimple.h"

#ifdef DEBUG
#include "nommgr.h"
#endif

//(*InternalHeaders(ModeSimple)






#include <wx/config.h>
#include <wx/log.h>
#include <iostream>

#ifdef DEBUG

#endif

//(*IdInit(ModeSimple)











BEGIN_EVENT_TABLE(ModeSimple,wxDialog)
	//(*EventTable(ModeSimple)
	//*)
END_EVENT_TABLE()

ModeSimple::ModeSimple(wxWindow* parent)
{
	//(*Initialize(ModeSimple)















































    wxConfigBase * pConfig = wxConfigBase::Get();

    bool result = false;
    pConfig->Read("/ModeSimple", &result);

    if ( result == true )
        ModeSimpleCheck->SetValue(true);
}

ModeSimple::~ModeSimple()
{
	//(*Destroy(ModeSimple)
	//*)
}


void ModeSimple::OnAnnulerBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

void ModeSimple::OnOkBtClick(wxCommandEvent& event)
{
    wxConfigBase * pConfig = wxConfigBase::Get();

    if (ModeSimpleCheck->GetValue())
        pConfig->Write("/ModeSimple", true);
    else
        pConfig->Write("/ModeSimple", false);

    wxLogMessage(_("Vous devez red�marrer Game Develop afin de prendre en compte l'action ou d�sactivation du mode simple."));

    EndModal(1);
}