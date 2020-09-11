#include "cMainDialog.h"
#include "RuledLine.h"

//cMain::cMain() : wxFrame(nullptr, wxID_ANY,"wxWidgets App using Visual Studio")
//{
//}
//
//cMain::~cMain()
//{
//}




cMainDialog::cMainDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	//Box Sizer to contain the buttons, we will make it vertical
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);


	//Containing the Intro
	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Welcome to Sudoku by Uzo"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	m_staticText1->SetFont(wxFont(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("High Tower Text")));
	bSizer1->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	bSizer1->Add(0, 0, 1, wxEXPAND, 5); //Space in Sizer

	m_button1 = new wxButton(this, 10200, wxT("New Game"), wxPoint(-1, -1), wxSize(120, 40), 0);
	bSizer1->Add(m_button1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5); // Aligned in the sizer
	m_button1->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMainDialog::onButtonClicked, this); //Dynamically bind to the event handler
	
	m_button2 = new wxButton(this, 10201, wxT("Continue"), wxDefaultPosition, wxSize(120, 40), 0);
	bSizer1->Add(m_button2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	m_button2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMainDialog::onButtonClicked, this);

	bSizer1->Add(0, 0, 1, wxEXPAND, 5); //Space in Sizer





	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);
}

cMainDialog::~cMainDialog()
{
}

void cMainDialog::onButtonClicked(wxCommandEvent &evt)
{
	if (evt.GetId()== 10200)
	{
		s_frame = new SudokuFrame(this);
		this->Hide();

		//To prevent resizing of the window
		s_frame->SetMaxSize(s_frame->GetSize());
		s_frame->SetMinSize(s_frame->GetSize());
		

		s_frame->Show();
		
		
		
		

	}
	else if (evt.GetId() == 10201)
	{
		wxMessageBox("Continue previous game", "Continue button was clicked");
		Close();
	}

	
}
