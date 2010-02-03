#ifndef MAJ_H
#define MAJ_H

//(*Headers(MAJ)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class MAJ: public wxDialog
{
	public:

		MAJ(wxWindow* parent);
		virtual ~MAJ();

		//(*Declarations(MAJ)
		wxButton* LienBt;
		wxStaticText* versionMAJTxt;
		wxStaticText* StaticText2;
		wxButton* FermerBt;
		wxTextCtrl* infoEdit;
		wxButton* VerifMAJBt;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticLine* StaticLine2;
		wxStaticLine* StaticLine1;
		wxStaticText* StaticText4;
		wxStaticText* versionTxt;
		wxStaticBitmap* StaticBitmap3;
		//*)

	protected:

		//(*Identifiers(MAJ)
		static const long ID_STATICBITMAP3;
		static const long ID_STATICTEXT1;
		static const long ID_PANEL1;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT6;
		static const long ID_BUTTON3;
		static const long ID_STATICLINE2;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(MAJ)
		void OnVerifMAJBtClick(wxCommandEvent& event);
		void OnLienBtClick(wxCommandEvent& event);
		void OnFermerBtClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif