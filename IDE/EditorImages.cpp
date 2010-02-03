#if defined(GDE)
#ifdef DEBUG
#define _MEMORY_TRACKER
#include "debugMem.h" //suivi m�moire
#endif

#include "EditorImages.h"
#ifdef __WXMSW__
#include <wx/msw/winundef.h>
#endif

//(*InternalHeaders(EditorImages)
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include <wx/toolbar.h>
#include <wx/config.h>
#include <wx/aui/aui.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/textdlg.h>
#include <wx/help.h>
#include <wx/dcbuffer.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/gallery.h>
#include <wx/ribbon/toolbar.h>

#include "Game_Develop_EditorMain.h"
#include "GDL/Game.h"
#include "GDL/StdAlgo.h"
#include "MemTrace.h"
#include "GDL/ChoixDossier.h"
#include "CppUnitLite/TestHarness.h"
#include "GDL/PropImage.h"
#include "GDL/BitmapGUIManager.h"

#ifdef __WXGTK__
#include <gtk/gtk.h>
#endif

extern MemTrace MemTracer;

//(*IdInit(EditorImages)
const long EditorImages::ID_PANEL2 = wxNewId();
const long EditorImages::ID_TREECTRL1 = wxNewId();
const long EditorImages::ID_PANEL3 = wxNewId();
const long EditorImages::ID_PANEL1 = wxNewId();
const long EditorImages::idMenuModProp = wxNewId();
const long EditorImages::idMenuMod = wxNewId();
const long EditorImages::idMenuModFile = wxNewId();
const long EditorImages::idMenuAjouter = wxNewId();
const long EditorImages::idMenuDel = wxNewId();
const long EditorImages::idMenuAddDossier = wxNewId();
const long EditorImages::idMenuRemoveDossier = wxNewId();
const long EditorImages::idMoveUp = wxNewId();
const long EditorImages::idMoveDown = wxNewId();
//*)
const long EditorImages::ID_BITMAPBUTTON1 = wxNewId();
const long EditorImages::ID_BITMAPBUTTON5 = wxNewId();
const long EditorImages::ID_BITMAPBUTTON4 = wxNewId();
const long EditorImages::ID_BITMAPBUTTON2 = wxNewId();
const long EditorImages::ID_BITMAPBUTTON3 = wxNewId();
const long EditorImages::ID_BITMAPBUTTON6 = wxNewId();
const long EditorImages::idRibbonAdd = wxNewId();
const long EditorImages::idRibbonModProp= wxNewId();
const long EditorImages::idRibbonMod= wxNewId();
const long EditorImages::idRibbonModFile= wxNewId();
const long EditorImages::idRibbonDel= wxNewId();
const long EditorImages::idRibbonAddDossier= wxNewId();
const long EditorImages::idRibbonRemoveDossier= wxNewId();
const long EditorImages::idRibbonUp= wxNewId();
const long EditorImages::idRibbonDown= wxNewId();
const long EditorImages::idRibbonDirectories= wxNewId();
const long EditorImages::idRibbonPaintProgram= wxNewId();
const long EditorImages::idRibbonSearch= wxNewId();
const long EditorImages::idRibbonHelp= wxNewId();
const long EditorImages::idRibbonRefresh = wxNewId();

BEGIN_EVENT_TABLE( EditorImages, wxPanel )
    //(*EventTable(EditorImages)
    //*)
END_EVENT_TABLE()


////////////////////////////////////////////////////////////
/// Constructeur
///
/// A utiliser par d�faut
////////////////////////////////////////////////////////////
EditorImages::EditorImages( wxWindow* parent, Game & game_, MainEditorCommand & mainEditorCommand_, bool useRibbon_ ) :
game(game_),
mainEditorCommand(mainEditorCommand_),
useRibbon(useRibbon_),
dossierId(-1),
toolbar(NULL)
{

    MemTracer.AddObj( "Editeur des images", ( long )this );
    //(*Initialize(EditorImages)
    wxFlexGridSizer* FlexGridSizer4;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenuItem* MenuItem3;
    wxMenuItem* editMenuItem;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(0);
    Core = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(1);
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    toolbarPanel = new wxPanel(Core, ID_PANEL2, wxDefaultPosition, wxSize(-1,25), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    toolbarPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    if ( useRibbon ) toolbarPanel->SetSize(-1, 0);
    FlexGridSizer1->Add(toolbarPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer4->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BanqueImageList = new wxTreeCtrl(Core, ID_TREECTRL1, wxDefaultPosition, wxSize(200,170), wxTR_EDIT_LABELS|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    BanqueImageList->SetToolTip(_("Clic droit sur une image pour acc�der aux options"));
    FlexGridSizer4->Add(BanqueImageList, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    apercuPanel = new wxPanel(Core, ID_PANEL3, wxDefaultPosition, wxSize(200,120), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer4->Add(apercuPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Core->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Core);
    FlexGridSizer4->SetSizeHints(Core);
    FlexGridSizer2->Add(Core, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(FlexGridSizer2);
    editMenuItem = new wxMenuItem((&ContextMenu), idMenuModProp, _("Modifier les propri�t�s de l\'image"), wxEmptyString, wxITEM_NORMAL);
    editMenuItem->SetBitmap(wxBitmap(wxImage(_T("res/editpropicon.png"))));
    ContextMenu.Append(editMenuItem);
    #ifdef __WXMSW__
    ContextMenu.Remove(editMenuItem);
     wxFont boldFont(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
     editMenuItem->SetFont(boldFont);
     ContextMenu.Append(editMenuItem);
    #endif
    MenuItem3 = new wxMenuItem((&ContextMenu), idMenuMod, _("Modifier le nom de l\'image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem3->SetBitmap(wxBitmap(wxImage(_T("res/editnom.png"))));
    ContextMenu.Append(MenuItem3);
    MenuItem4 = new wxMenuItem((&ContextMenu), idMenuModFile, _("Modifier le fichier de l\'image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem4->SetBitmap(wxBitmap(wxImage(_T("res/openicon.png"))));
    ContextMenu.Append(MenuItem4);
    ContextMenu.AppendSeparator();
    MenuItem1 = new wxMenuItem((&ContextMenu), idMenuAjouter, _("Ajouter une image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem1->SetBitmap(wxBitmap(wxImage(_T("res/addicon.png"))));
    ContextMenu.Append(MenuItem1);
    MenuItem2 = new wxMenuItem((&ContextMenu), idMenuDel, _("Supprimer l\'image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem2->SetBitmap(wxBitmap(wxImage(_T("res/deleteicon.png"))));
    ContextMenu.Append(MenuItem2);
    ContextMenu.AppendSeparator();
    MenuItem5 = new wxMenuItem((&ContextMenu), idMenuAddDossier, _("Ajouter une image d�j� existante au dossier"), wxEmptyString, wxITEM_NORMAL);
    MenuItem5->SetBitmap(wxBitmap(wxImage(_T("res/addicon.png"))));
    ContextMenu.Append(MenuItem5);
    MenuItem6 = new wxMenuItem((&ContextMenu), idMenuRemoveDossier, _("Supprimer l\'image du dossier"), wxEmptyString, wxITEM_NORMAL);
    MenuItem6->SetBitmap(wxBitmap(wxImage(_T("res/remove.png"))));
    ContextMenu.Append(MenuItem6);
    ContextMenu.AppendSeparator();
    MenuItem7 = new wxMenuItem((&ContextMenu), idMoveUp, _("D�placer vers le haut\tCtrl-P"), _("D�placer l\'image vers le haut dans la liste"), wxITEM_NORMAL);
    MenuItem7->SetBitmap(wxBitmap(wxImage(_T("res/up.png"))));
    ContextMenu.Append(MenuItem7);
    MenuItem8 = new wxMenuItem((&ContextMenu), idMoveDown, _("D�placer vers le bas"), _("D�placer l\'image vers le bas dans la liste"), wxITEM_NORMAL);
    MenuItem8->SetBitmap(wxBitmap(wxImage(_T("res/down.png"))));
    ContextMenu.Append(MenuItem8);
    FlexGridSizer2->Fit(this);
    FlexGridSizer2->SetSizeHints(this);

    toolbarPanel->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EditorImages::OntoolbarPanelResize,0,this);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_BEGIN_DRAG,(wxObjectEventFunction)&EditorImages::OnBanqueImageListBeginDrag);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT,(wxObjectEventFunction)&EditorImages::OnBanqueImageListBeginLabelEdit);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_END_LABEL_EDIT,(wxObjectEventFunction)&EditorImages::OnBanqueImageListEndLabelEdit);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_ITEM_ACTIVATED,(wxObjectEventFunction)&EditorImages::OnBanqueImageListItemActivated1);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&EditorImages::OnBanqueImageListSelectionChanged);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&EditorImages::OnBanqueImageListSelectionChanged);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_ITEM_MENU,(wxObjectEventFunction)&EditorImages::OnBanqueImageListItemMenu);
    apercuPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EditorImages::OnapercuPanelPaint,0,this);
    apercuPanel->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorImages::OnSetFocus,0,this);
    Core->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorImages::OnSetFocus,0,this);
    Connect(idMenuModProp,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnModPropSelected);
    Connect(idMenuMod,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnModNameImageBtClick);
    Connect(idMenuModFile,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnModFileImage);
    Connect(idMenuAjouter,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnAddImageBtClick);
    Connect(idMenuDel,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnDelImageBtClick);
    Connect(idMenuAddDossier,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnMenuItem5Selected);
    Connect(idMenuRemoveDossier,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnMenuItem6Selected);
    Connect(idMoveUp,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnMoveUpSelected);
    Connect(idMoveDown,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorImages::OnMoveDownSelected);
    Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorImages::OnSetFocus);
    //*)

    m_NomItem = "";

    BanqueImageList->AddRoot( _( "Toutes les images" ) );
    MenuItem5->Enable(false);
    MenuItem6->Enable(false);

    //EditorImages can be used without ribbon
    if ( !useRibbon )
        CreateToolbar();
    else
    {
        //The Images Editor is unique in the main editor, that's why we can connect events here.
        mainEditorCommand.GetMainEditor()->Connect(idRibbonAdd, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnAddImageBtClick, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonDel, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnDelImageBtClick, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonModProp, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnModPropSelected, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonMod, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnModNameImageBtClick, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonModFile, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnModFileImage, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonAddDossier, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnMenuItem5Selected, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonRemoveDossier, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnMenuItem6Selected, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonUp, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnMoveUpSelected, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonDown, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnMoveDownSelected, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonDirectories, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::DossierBt, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonPaintProgram, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnOpenPaintProgramClick, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonSearch, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnChercherBtClick, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonHelp, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::OnAideBtClick, NULL, this);
        mainEditorCommand.GetMainEditor()->Connect(idRibbonRefresh, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EditorImages::Refresh, NULL, this);
    }


    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&EditorImages::OnRefreshBtClick);
    Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&EditorImages::OnOpenPaintProgramClick);
    Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&EditorImages::OnMoreOptions);
    Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&EditorImages::DossierBt);
    Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&EditorImages::OnChercherBtClick);
    Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&EditorImages::OnAideBtClick);
}

EditorImages::~EditorImages()
{
    //(*Destroy(EditorImages)
    //*)
    MemTracer.DelObj(( long )this );
}

/**
 * Static method for creating the ribbon's page used by Images Editors
 */
void EditorImages::CreateRibbonPage(wxRibbonPage * page)
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    bool hideLabels = false;
    pConfig->Read( _T( "/Skin/HideLabels" ), &hideLabels );

    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Liste d'images"), wxBitmap("res/list24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idRibbonAdd, !hideLabels ? _("Ajouter une image") : "", wxBitmap("res/add24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonDel, !hideLabels ? _("Supprimer") : "", wxBitmap("res/delete24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonUp, !hideLabels ? _("D�placer vers le haut") : "", wxBitmap("res/up24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonDown, !hideLabels ? _("D�placer vers le bas") : "", wxBitmap("res/down24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonSearch, !hideLabels ? _("Rechercher") : "", wxBitmap("res/search24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonRefresh, !hideLabels ? _("Rafraichir") : "", wxBitmap("res/refreshicon24.png", wxBITMAP_TYPE_ANY));
    }

    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Image s�lectionn�e"), wxBitmap("res/edit24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idRibbonMod, !hideLabels ? _("Nom") : "", wxBitmap("res/editname24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonModFile, !hideLabels ? _("Modifier le fichier") : "", wxBitmap("res/openicon24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonModProp, !hideLabels ? _("Propri�t�s") : "", wxBitmap("res/editprop24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonPaintProgram, !hideLabels ? _("Editer") : "", wxBitmap("res/paint24.png", wxBITMAP_TYPE_ANY));
    }

    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Dossiers"), wxBitmap("res/dossier24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idRibbonDirectories, !hideLabels ? _("Choisir") : "", wxBitmap("res/dossier24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonAddDossier, !hideLabels ? _("Ajouter au dossier") : "", wxBitmap("res/add24.png", wxBITMAP_TYPE_ANY));
        ribbonBar->AddButton(idRibbonRemoveDossier, !hideLabels ? _("Enlever") : "", wxBitmap("res/remove24.png", wxBITMAP_TYPE_ANY));
    }

    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Aide"), wxBitmap("res/helpicon24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idRibbonHelp, !hideLabels ? _("Aide") : "", wxBitmap("res/helpicon24.png", wxBITMAP_TYPE_ANY));
    }

}

////////////////////////////////////////////////////////////
/// Cr�ation de la toolbar
////////////////////////////////////////////////////////////
void EditorImages::CreateToolbar()
{
    //Barre d'outils
    toolbar = new wxToolBar( toolbarPanel, -1, wxDefaultPosition, wxDefaultSize,
                                    wxTB_FLAT /*| wxTB_NODIVIDER*/ );

    toolbar->SetToolBitmapSize( wxSize( 16, 16 ) );
    toolbar->AddTool( ID_BITMAPBUTTON1, wxT( "Rafraichir" ), wxBitmap( wxImage( "res/refreshicon.png" ) ), _("Rafraichir la liste d'images") );
    toolbar->AddSeparator();
    toolbar->AddTool( idMenuAjouter, wxT( "Ajouter une image" ), wxBitmap( wxImage( "res/addicon.png" ) ), _("Ajouter une image") );
    toolbar->AddTool( idMenuDel, wxT( "Supprimer l'image selectionn�e" ), wxBitmap( wxImage( "res/deleteicon.png" ) ), _("Supprimer l'image selectionn�e") );
    toolbar->AddTool( idMenuModProp, wxT( "Modifier les propri�t�s de l'image" ), wxBitmap( wxImage( "res/editpropicon.png" ) ), _("Modifier les propri�t�s de l'image") );
    toolbar->AddTool( ID_BITMAPBUTTON6, wxT( "Plus d'options d'�dition ( clic droit sur la liste )" ), wxBitmap( wxImage( "res/moreicon.png" ) ), _("Plus d'options d'�dition ( clic droit sur la liste )") );
    toolbar->AddSeparator();
    toolbar->AddTool( ID_BITMAPBUTTON5, wxT( "Ouvrir l'image avec un �diteur" ), wxBitmap( wxImage( "res/paint.png" ) ), _("Ouvrir l'image avec un �diteur") );
    toolbar->AddTool( ID_BITMAPBUTTON4, wxT( "Naviguer dans les dossiers" ), wxBitmap( wxImage( "res/dossier.png" ) ), _("Naviguer dans les dossiers") );
    toolbar->AddTool( ID_BITMAPBUTTON2, wxT( "Rechercher une image" ), wxBitmap( wxImage( "res/searchicon.png" ) ), _("Rechercher une image") );
    toolbar->AddSeparator();
    toolbar->AddTool( ID_BITMAPBUTTON3, wxT( "Aide de l'�diteur de la banque d'images" ), wxBitmap( wxImage( "res/helpicon.png" ) ), _("Aide de l'�diteur de la banque d'images") );
    toolbar->Realize();

    wxConfigBase * pConfig = wxConfigBase::Get();

    bool result = false;
    pConfig->Read("/ModeSimple", &result);

    if ( result )
    {
        toolbar->EnableTool(ID_BITMAPBUTTON1, false);
        toolbar->EnableTool(ID_BITMAPBUTTON6, false);
        toolbar->EnableTool(ID_BITMAPBUTTON4, false);
        toolbar->EnableTool(ID_BITMAPBUTTON2, false);
    }

    //Obligatoire avec wxGTK, sinon la toolbar ne s'affiche pas
#ifdef __WXGTK__
    wxSize tbSize = toolbar->GetSize();
    gtk_widget_set_usize( toolbar->m_widget, tbSize.GetWidth(), tbSize.GetHeight() );
#endif
}

////////////////////////////////////////////////////////////
/// Redimensionement de la toolbar
////////////////////////////////////////////////////////////
void EditorImages::OntoolbarPanelResize(wxSizeEvent& event)
{
    if ( !useRibbon )
    {
        toolbar->SetSize(toolbarPanel->GetSize().x, -1);
        toolbarPanel->SetSize(toolbarPanel->GetSize().GetWidth(), toolbar->GetSize().GetHeight());
    }
}

////////////////////////////////////////////////////////////
/// Ajouter une nouvelle image vierge
////////////////////////////////////////////////////////////
void EditorImages::OnAddImageBtClick( wxCommandEvent& event )
{
    //Les vector contenant les nouvelles images
    vector <string> newFile;
    vector <string> newName;

    //Le treeCtrl
    wxTreeItemId rootId = BanqueImageList->GetRootItem();

    //Boite de dialogue d'ajout d'une image
    wxFileDialog FileDialog( this, "Choisissez une ou plusieurs images � ajouter", "", "", "Images support�es|*.bmp;*.gif;*.jpg;*.png;*.tga;*.dds|Tous les fichiers|*.*", wxFD_MULTIPLE );

    //Si c'est ok
    if ( FileDialog.ShowModal() == wxID_OK )
    {
        wxLogStatus( _( "Ajout des images" ) );

        wxArrayString Fichiers;
        wxArrayString Noms;
        FileDialog.GetFilenames( Noms );
        FileDialog.GetPaths( Fichiers );
        string imageNonAjoutees;

        for ( unsigned int i = 0; i < Fichiers.GetCount();i++ )
        {
            wxString Status = _( "Ajout de l'image " );
            wxLogStatus( Status + Noms[i] );

            //V�rifier que l'image n'est pas d�j� dans la liste
            if ( ChercherNomImage(game.images, static_cast<string>(Noms[i])) == -1 )
            {
                //On ajoute l'image
                Image image;

                image.fichier = ( string ) Fichiers[i];
                image.nom = ( string ) Noms[i];

                game.images.push_back(image);
                Dossier::Add( &game.dossierImages, (string)Noms[i], dossierId );

                BanqueImageList->AppendItem( rootId, Noms[i] );
            }
            else
                imageNonAjoutees += "\n"+Noms[i];

        }

        if ( imageNonAjoutees != "" )
        {
            wxLogMessage(wxString(_("Des images portant le m�me nom sont d�j� dans la liste, et n'ont pas �t� ajout�es :")+imageNonAjoutees));
        }

        //Fin du processus, n�cessit�e de mettre � jour les sc�nes.
        mainEditorCommand.NeedRefreshAllImages();
        mainEditorCommand.NeedRefreshAllScenes();
        wxLogStatus( _( "L'image a �t� correctement ajout�e � la banque d'image" ) );
    }

}

////////////////////////////////////////////////////////////
/// Supprimer une image de la liste
////////////////////////////////////////////////////////////
void EditorImages::OnDelImageBtClick( wxCommandEvent& event )
{
    wxTreeItemId Item = m_itemSelected;
    wxTreeItemId ItemNul = NULL;
    if ( Item != ItemNul && BanqueImageList->GetRootItem() != Item )
    {
        int i = ChercherNomImage( game.images, ( string ) BanqueImageList->GetItemText( Item ) );
        if ( i != -1 )
        {
            //On enl�ve l'image
            game.images.erase( game.images.begin() + i );
            Dossier::RemoveImage(&game.dossierImages, ( string ) BanqueImageList->GetItemText( Item ));
        }

        mainEditorCommand.NeedRefreshAllImages();
        BanqueImageList->Delete( Item );

        return;

    }
    else
    {
        wxLogStatus( _( "Aucune image s�lectionn�e" ) );
    }
}

////////////////////////////////////////////////////////////
/// Modification d'une image d�j� existante
////////////////////////////////////////////////////////////
void EditorImages::OnModNameImageBtClick( wxCommandEvent& event )
{
    wxTreeItemId Item = m_itemSelected;
    wxTreeItemId ItemNul = NULL;
    if ( Item != ItemNul && BanqueImageList->GetChildrenCount( m_itemSelected ) == 0 )
    {
        BanqueImageList->EditLabel( m_itemSelected );
    }
    else
    {
        wxLogStatus( _( "Aucune image s�lectionn�e" ) );
    }
}

////////////////////////////////////////////////////////////
/// Affichage du menu
////////////////////////////////////////////////////////////
void EditorImages::OnBanqueImageListItemMenu( wxTreeEvent& event )
{
    //Editor have focus
    wxFocusEvent unusedEvent;
    OnSetFocus(unusedEvent);

    PopupMenu( &ContextMenu );
}

////////////////////////////////////////////////////////////
/// Affichage du menu ( plus d'options )
////////////////////////////////////////////////////////////
void EditorImages::OnMoreOptions( wxCommandEvent& event )
{
    PopupMenu( &ContextMenu );
}

////////////////////////////////////////////////////////////
/// Clic sur le bouton de rafraichissement
////////////////////////////////////////////////////////////
void EditorImages::OnRefreshBtClick( wxCommandEvent& event )
{
    Refresh();
}

////////////////////////////////////////////////////////////
/// Selection d'une image
////////////////////////////////////////////////////////////
void EditorImages::OnBanqueImageListSelectionChanged( wxTreeEvent& event )
{
    //Editor have focus
    wxFocusEvent unusedEvent;
    OnSetFocus(unusedEvent);

    string nom = ( string ) BanqueImageList->GetItemText( event.GetItem() );
    //Changement de l'item s�lectionn�
    m_itemSelected = event.GetItem();

    if ( BanqueImageList->GetChildrenCount( m_itemSelected ) == 0)
    {
        //Zone d'aper�u de l'image
        int i = ChercherNomImage( game.images, nom );
        if ( i != -1 )
        {
            fileImageSelected = game.images.at( i ).fichier;
            apercuPanel->Refresh();
            apercuPanel->Update();
        }
    }

}

////////////////////////////////////////////////////////////
/// Edition du nom d'une image : 2-> Passage du nom original au nouveau
////////////////////////////////////////////////////////////
void EditorImages::OnBanqueImageListEndLabelEdit( wxTreeEvent& event )
{
    if ( !event.IsEditCancelled() )
    {
        //Si le nom n'existe pas
        if ( ChercherNomImage( game.images, ( string ) event.GetLabel() ) != -1 )
        {
            wxLogWarning( _( "Impossible de renommer l'image : une autre image porte d�j� ce nom." ) );
            Refresh();
            return;
        }
        else
        {
            int i = ChercherNomImage( game.images, m_NomItem );
            if ( i != -1 )
            {
                game.images.at( i ).nom = event.GetLabel();
                Dossier::ReplaceNomImage(&game.dossierImages, m_NomItem, static_cast<string> (event.GetLabel()));

                mainEditorCommand.NeedRefreshAllImages();
                BanqueImageList->SetItemText( event.GetItem(), event.GetLabel() );

                return;
            }
        }
    }
}

////////////////////////////////////////////////////////////
/// Edition du nom d'une image : 1-> Nom original
////////////////////////////////////////////////////////////
void EditorImages::OnBanqueImageListBeginLabelEdit( wxTreeEvent& event )
{
    if ( BanqueImageList->GetItemText( event.GetItem() ) != _( "Toutes les images" ) )
    {
        m_NomItem = BanqueImageList->GetItemText( event.GetItem() );
    }
    else
    {
        //On ne touche pas au dossier "Toutes les images"
        BanqueImageList->EndEditLabel( event.GetItem(), true );
    }
}

////////////////////////////////////////////////////////////
/// Recr�er le TreeCtrl
////////////////////////////////////////////////////////////
void EditorImages::Refresh()
{
    BanqueImageList->DeleteAllItems();

    //On v�rifie bien la validit� de dossierId, car on a tr�s bien pu changer
    //de jeu entre son choix et le rafraichissement
    if ( dossierNom != "" && dossierId >= 0 && static_cast<unsigned>(dossierId) < game.dossierImages.size())
    {
        BanqueImageList->AddRoot( dossierNom );
        if ( !game.dossierImages.at(dossierId).contenu.empty() )
        {
            for ( unsigned int i = 0;i < game.dossierImages.at(dossierId).contenu.size();i++ )
            {
                wxString nom = game.dossierImages.at(dossierId).contenu.at( i );

                //Ajout � la liste
                BanqueImageList->AppendItem( BanqueImageList->GetRootItem(), nom );
            }
        }

        return;
    }

    BanqueImageList->AddRoot( _( "Toutes les images" ) );

    if ( !game.images.empty() )
    {
        for ( unsigned int i = 0;i < game.images.size();i++ )
        {
            wxString nom = game.images.at( i ).nom;

            //Ajout � la liste
            BanqueImageList->AppendItem( BanqueImageList->GetRootItem(), nom );

        }
    }
    BanqueImageList->Expand( BanqueImageList->GetRootItem() );
}

////////////////////////////////////////////////////////////
/// Modifier le fichier d'une image
////////////////////////////////////////////////////////////
void EditorImages::OnModFileImage( wxCommandEvent& event )
{
    int i = ChercherNomImage( game.images, ( string ) BanqueImageList->GetItemText( m_itemSelected ) );
    if ( i == -1 )
    {
        wxLogStatus( _( "L'image � modifier n'a pas �t� trouv�e." ) );
        return;
    }

    //Boite de dialogue d'ajout d'une image
    wxFileDialog FileDialog( this, _( "Choisissez le fichier de l'image" ), "", "", "Images support�es|*.bmp;*.gif;*.jpg;*.png;*.tga;*.dds|Tous les fichiers|*.*", wxFD_OPEN );
    if ( FileDialog.ShowModal() == wxID_OK )
    {
        wxLogStatus( _( "Changement du fichier de l'image..." ) );

        string Fichier;
        Fichier = ( string ) FileDialog.GetPath();

        game.images.at( i ).fichier = Fichier;
        //Ne concerne pas les dossiers

        mainEditorCommand.NeedRefreshAllImages();
        wxLogStatus( _( "Changement du fichier de l'image effectu�" ) );
    }

}

void EditorImages::OnChercherBtClick( wxCommandEvent& event )
{
    string name = static_cast<string>( wxGetTextFromUser( _( "Entrez le nom de l'image � rechercher" ), _( "Chercher une image" ) ) );
    if ( name == "" ) return;

    int i = ChercherNomImage( game.images, name );
    if ( i != -1 )
    {
        //On en a trouv� un, on le s�lectionne.
        void * rien;
        wxTreeItemId item = BanqueImageList->GetFirstChild( BanqueImageList->GetRootItem(), rien );
        while ( BanqueImageList->GetItemText( item ) != name )
        {
            item = BanqueImageList->GetNextSibling( item );
        }

        BanqueImageList->SelectItem( item );

        return;
    }
    else { wxLogMessage( "Aucune image de ce nom trouv�e !" ); }
}

void EditorImages::OnAideBtClick( wxCommandEvent& event )
{
    wxHelpController * help = new wxHelpController;
    help->Initialize( "aide.chm" );
    help->DisplaySection(9);
}

void EditorImages::DossierBt( wxCommandEvent& event )
{
    ChoixDossier Dialog( this, &game.dossierImages );
    int returnValue = Dialog.ShowModal();
    if ( returnValue == 1 )
    {
        dossierNom = Dialog.dossierNom;
        dossierId = -1;

        for ( unsigned int i = 0;i < game.dossierImages.size() ;i++ )
        {
            if ( game.dossierImages.at( i ).nom == dossierNom )
            {
                dossierId = i;
            }
        }

        if ( dossierId == -1 )
        {
            wxLogWarning( _( "N'a pas pu localiser le dossier" ) );
        }
        MenuItem5->Enable(true);
        MenuItem6->Enable(true);

        Refresh();
        return;
    }
    else if ( returnValue == 2 )
    {
        dossierNom = "";
        dossierId = -1;

        MenuItem5->Enable(false);
        MenuItem6->Enable(false);

        Refresh();
        return;
    }
}


////////////////////////////////////////////////////////////
/// Ajouter une image d�j� existante au dossier
////////////////////////////////////////////////////////////
void EditorImages::OnMenuItem5Selected(wxCommandEvent& event)
{
    string name = static_cast<string>( wxGetTextFromUser( _( "Entrez le nom de l'image � ajouter" ), _( "Ajouter une image au dossier" ) ) );
    if ( name == "" ) return;

    bool trouve = false;
    for (unsigned int i = 0;i<game.images.size();i++)
    {
    	if ( name == game.images.at(i).nom )
            trouve = true;
    }

    if ( !trouve )
    {
        wxLogWarning(_("L'image n'existe pas."));
        return;
    }

    Dossier::Add(&game.dossierImages, name, dossierId);
    BanqueImageList->AppendItem(BanqueImageList->GetRootItem(), name);
}

////////////////////////////////////////////////////////////
/// Supprimer l'image du dossier seulement
////////////////////////////////////////////////////////////
void EditorImages::OnMenuItem6Selected(wxCommandEvent& event)
{
    wxTreeItemId Item = m_itemSelected;
    wxTreeItemId ItemNul = NULL;
    if ( Item != ItemNul && BanqueImageList->GetChildrenCount( m_itemSelected ) == 0 )
    {
        Dossier::RemoveImage(&game.dossierImages, ( string ) BanqueImageList->GetItemText( Item ), dossierId);

        BanqueImageList->Delete( Item );

        return;

    }
    else
    {
        wxLogStatus( _( "Aucune image s�lectionn�e" ) );
    }
}

TEST(Dialogues, EditorImages)
{
}

////////////////////////////////////////////////////////////
/// Modifier les propri�t�s de l'image
////////////////////////////////////////////////////////////
void EditorImages::OnModPropSelected(wxCommandEvent& event)
{
    int i = ChercherNomImage( game.images, static_cast< string > ( BanqueImageList->GetItemText( m_itemSelected ) ));
    if ( i == -1 )
    {
        wxLogStatus( _( "L'image � modifier n'a pas �t� trouv�e." ) );
        return;
    }

    PropImage dialog(this, game.images.at(i));
    if ( dialog.ShowModal() == 1 )
        mainEditorCommand.NeedRefreshAllImages();
}
void EditorImages::OnBanqueImageListItemActivated1(wxTreeEvent& event)
{
    wxFocusEvent unusedEvent;
    OnSetFocus(unusedEvent);

    wxCommandEvent eventUseless;
    OnModPropSelected( eventUseless );
}

////////////////////////////////////////////////////////////
/// Ouvrir le programme d'�dition d'image.
////////////////////////////////////////////////////////////
void EditorImages::OnOpenPaintProgramClick(wxCommandEvent& event)
{

    wxConfigBase *pConfig = wxConfigBase::Get();
    wxString result;
    pConfig->Read( _T( "/EditeursExternes/Image" ), &result );

    if ( result == "" )
    {
        wxFileDialog dialog(this, _("Choisissez le programme d'�dition d'images ( fichier exe )"), "", "", "Programmes (*.exe)|*.exe");
        dialog.ShowModal();

        pConfig->Write( _T( "/EditeursExternes/Image" ), dialog.GetPath() );
        pConfig->Read( _T( "/EditeursExternes/Image" ), &result );
    }

    if ( result != "" )
    {
        int i = ChercherNomImage( game.images, static_cast< string > ( BanqueImageList->GetItemText( m_itemSelected ) ));
        if ( i == -1 )
        {
            wxExecute(result);
            return;
        }

        wxExecute(result+" \""+game.images.at(i).fichier+"\"");
    }
}

////////////////////////////////////////////////////////////
/// Affichage de l'apercu de l'image
////////////////////////////////////////////////////////////
void EditorImages::OnapercuPanelPaint(wxPaintEvent& event)
{
    wxPaintDC dc( apercuPanel ); //Cr�ation obligatoire du wxBufferedPaintDC

    wxSize size = apercuPanel->GetSize();

    BitmapGUIManager * bitmapGUIManager = BitmapGUIManager::getInstance();

    //Fond en damier
    dc.SetBrush(bitmapGUIManager->transparentBg);
    dc.DrawRectangle(0,0, size.GetWidth(), size.GetHeight());

    if ( fileImageSelected == "" )
        return;

    wxBitmap bmp( fileImageSelected, wxBITMAP_TYPE_ANY);
    if ( bmp.GetWidth() > 120 || bmp.GetHeight() > 120 )
    {
        //R�duction � l'�chelle
        int max = bmp.GetWidth() > bmp.GetHeight() ? bmp.GetWidth() : bmp.GetHeight();
        float factor = 120.f/max;

        wxImage image = bmp.ConvertToImage();
        bmp = wxBitmap(image.Scale(bmp.GetWidth()*factor, bmp.GetHeight()*factor));
    }

    //Affichage au centre de l'image
    dc.DrawBitmap(bmp,
                  (size.GetWidth() - bmp.GetWidth()) / 2,
                  (size.GetHeight() - bmp.GetHeight()) / 2,
                  true /* use mask */);
}

////////////////////////////////////////////////////////////
/// D�placement vers le haut de la liste
////////////////////////////////////////////////////////////
void EditorImages::OnMoveUpSelected(wxCommandEvent& event)
{
    string name = static_cast< string > ( BanqueImageList->GetItemText( m_itemSelected ));

    if ( dossierId == -1 )
    {
        int i = ChercherNomImage( game.images, name );
        if ( i == -1 )
        {
            wxLogStatus( _( "L'image � d�placer n'a pas �t� trouv�e." ) );
            return;
        }
        else if ( static_cast<unsigned>(i-1) >= 0 )
        {
            //On d�place l'image
            Image image = game.images[i];
            game.images.erase(game.images.begin() + i );
            game.images.insert(game.images.begin()+i-1, image);

            Refresh();
            mainEditorCommand.NeedRefreshAllImages();

            //On la reselectionne
            wxTreeItemId item = BanqueImageList->GetLastChild(BanqueImageList->GetRootItem());
            while ( item.IsOk() )
            {
                if ( BanqueImageList->GetItemText( item ) == name )
                {
                    BanqueImageList->SelectItem(item);
                    return;
                }
                item = BanqueImageList->GetPrevSibling(item);
            }

        }
    }
    //Un dossier
    else if ( dossierId >= 0 && static_cast<unsigned>(dossierId) < game.dossierImages.size())
    {
        int imageId = -1;
        for (unsigned int i =0;i<game.dossierImages[dossierId].contenu.size();++i)
        {
        	if ( game.dossierImages[dossierId].contenu[i] == name )
                imageId = i;
        }
        if ( imageId == -1 )
        {
            wxLogStatus( _( "L'image � d�placer n'a pas �t� trouv�e." ) );
            return;
        }
        else if ( imageId-1 >= 0)
        {
            //On d�place l'image
            string image = game.dossierImages[dossierId].contenu[imageId];
            game.dossierImages[dossierId].contenu.erase( game.dossierImages[dossierId].contenu.begin()+imageId );
            game.dossierImages[dossierId].contenu.insert( game.dossierImages[dossierId].contenu.begin()+imageId-1, image);

            Refresh();
            mainEditorCommand.NeedRefreshAllImages();

            //On la reselectionne
            wxTreeItemId item = BanqueImageList->GetLastChild(BanqueImageList->GetRootItem());
            while ( item.IsOk() )
            {
                if ( BanqueImageList->GetItemText( item ) == name )
                {
                    BanqueImageList->SelectItem(item);
                    return;
                }
                item = BanqueImageList->GetPrevSibling(item);
            }

        }
    }
}

void EditorImages::OnMoveDownSelected(wxCommandEvent& event)
{
    string name = static_cast< string > ( BanqueImageList->GetItemText( m_itemSelected ));

    //Toutes les images
    if ( dossierId == -1 )
    {
        int i = ChercherNomImage( game.images, name );
        if ( i == -1 )
        {
            wxLogStatus( _( "L'image � d�placer n'a pas �t� trouv�e." ) );
            return;
        }
        else if ( static_cast<unsigned>(i+1) < game.images.size() )
        {
            //On d�place l'image
            Image image = game.images[i];
            game.images.erase(game.images.begin() + i );
            game.images.insert(game.images.begin()+i+1, image);

            Refresh();
            mainEditorCommand.NeedRefreshAllImages();

            //On la reselectionne
            wxTreeItemId item = BanqueImageList->GetLastChild(BanqueImageList->GetRootItem());
            while ( item.IsOk() )
            {
                if ( BanqueImageList->GetItemText( item ) == name )
                {
                    BanqueImageList->SelectItem(item);
                    return;
                }
                item = BanqueImageList->GetPrevSibling(item);
            }

        }
    }
    //Un dossier
    else if ( dossierId >= 0 && static_cast<unsigned>(dossierId) < game.dossierImages.size())
    {
        int imageId = -1;
        for (unsigned int i =0;i<game.dossierImages[dossierId].contenu.size();++i)
        {
        	if ( game.dossierImages[dossierId].contenu[i] == name )
                imageId = i;
        }
        if ( imageId == -1 )
        {
            wxLogStatus( _( "L'image � d�placer n'a pas �t� trouv�e." ) );
            return;
        }
        else if ( static_cast<unsigned>(imageId+1) < game.dossierImages[dossierId].contenu.size())
        {
            //On d�place l'image
            string image = game.dossierImages[dossierId].contenu[imageId];
            game.dossierImages[dossierId].contenu.erase( game.dossierImages[dossierId].contenu.begin()+imageId );
            game.dossierImages[dossierId].contenu.insert( game.dossierImages[dossierId].contenu.begin()+imageId+1, image);

            Refresh();
            mainEditorCommand.NeedRefreshAllImages();

            //On la reselectionne
            wxTreeItemId item = BanqueImageList->GetLastChild(BanqueImageList->GetRootItem());
            while ( item.IsOk() )
            {
                if ( BanqueImageList->GetItemText( item ) == name )
                {
                    BanqueImageList->SelectItem(item);
                    return;
                }
                item = BanqueImageList->GetPrevSibling(item);
            }

        }
    }
}

/**
 * Begin dragging image ( can be dropped in a Objects Editor so as to create easily an object )
 */
void EditorImages::OnBanqueImageListBeginDrag(wxTreeEvent& event)
{
    if ( event.GetItem().IsOk() && event.GetItem() != BanqueImageList->GetRootItem() )
    {
        wxTextDataObject name(BanqueImageList->GetItemText(event.GetItem()));
        wxDropSource dragSource( this );
        dragSource.SetData( name );
        dragSource.DoDragDrop( true );
    }
}

/**
 * Show appropriate ribbon page when get focus.
 */
void EditorImages::OnSetFocus(wxFocusEvent& event)
{
    if ( useRibbon )
        mainEditorCommand.GetRibbon()->SetActivePage(1);
}
#endif