#pragma once

#include "wx/wx.h"
#include "SudokuFrame.h"

//class cMain : public wxFrame
//{
//public:
//	cMain();
//	~cMain();
//};
//

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

class cMainDialog : public wxDialog
{
private:

protected:
	wxStaticText* m_staticText1;
	wxButton* m_button1;
	wxButton* m_button2;

	SudokuFrame* s_frame = nullptr;



public:

	cMainDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(422, 385), long style = wxDEFAULT_DIALOG_STYLE | wxDIALOG_NO_PARENT);
	~cMainDialog();

	void onButtonClicked(wxCommandEvent &evt);

	


};

