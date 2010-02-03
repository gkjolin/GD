#include "EditPropScene.h"

#ifdef DEBUG
#include "nommgr.h"
#endif

//(*InternalHeaders(EditPropScene)





#include <wx/colour.h>
#include <wx/colordlg.h>
#include <wx/cmndata.h>
#include <wx/help.h>
#include <wx/config.h>

#ifdef DEBUG

#endif

#include "GDL/Scene.h"

//(*IdInit(EditPropScene)















BEGIN_EVENT_TABLE(EditPropScene,wxDialog)
	//(*EventTable(EditPropScene)
	//*)
END_EVENT_TABLE()

EditPropScene::EditPropScene(wxWindow* parent, Scene * pScene)
{
	//(*Initialize(EditPropScene)


















































































	scene = pScene;
	CaptionEdit->SetValue(scene->title);
	NomSceneTxt->SetLabel(scene->name);

	Panel1->SetBackgroundColour(wxColour(scene->backgroundColorR, scene->backgroundColorG, scene->backgroundColorB));

    if ( scene->standardSortMethod )
        TriBox->SetSelection(0);
    else
        TriBox->SetSelection(1);


    //On v�rifie si on est pas en mode simple.
    wxConfigBase * pConfig = wxConfigBase::Get();

    bool result = false;
    pConfig->Read("/ModeSimple", &result);

    if ( result )
        TriBox->Enable(false);

}

EditPropScene::~EditPropScene()
{
	//(*Destroy(EditPropScene)
	//*)
}


void EditPropScene::OnOkBtClick(wxCommandEvent& event)
{
    scene->title = static_cast<string> (CaptionEdit->GetValue());

    wxColourData cData;
    cData.SetColour(Panel1->GetBackgroundColour());
    scene->backgroundColorR = cData.GetColour().Red();
    scene->backgroundColorG = cData.GetColour().Green();
    scene->backgroundColorB = cData.GetColour().Blue();

    if ( TriBox->GetSelection() == 0 )
        scene->standardSortMethod = true;
    else
        scene->standardSortMethod = false;

    EndModal(1);
}

void EditPropScene::OnAnnulerBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

void EditPropScene::OnColorBtClick(wxCommandEvent& event)
{
    wxColourData cData;
    cData.SetColour(Panel1->GetBackgroundColour());
    wxColourDialog Dialog(this, &cData);
    if ( Dialog.ShowModal() == wxID_OK)
    {
        cData = Dialog.GetColourData();
        Panel1->SetBackgroundColour(cData.GetColour());
        Panel1->Refresh();
    }
}

void EditPropScene::OnAideBtClick(wxCommandEvent& event)
{
    wxHelpController * help = new wxHelpController;
    help->Initialize( "aide.chm" );
    help->DisplaySection(8);
}