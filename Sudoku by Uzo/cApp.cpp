#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{

	//m_frame1 = new cMain();
	//m_frame1->Show();

	m_dialog = new cMainDialog(nullptr, wxID_ANY, "Sudoku by Uzo",wxPoint(100,100));
	m_dialog->Show();
	return true;
}

