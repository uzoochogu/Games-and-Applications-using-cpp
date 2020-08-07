#include "cMain.h"



wxBEGIN_EVENT_TABLE(cMain,wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
wxEND_EVENT_TABLE()

cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Uzo's Sprite Editor", wxPoint(100, 100), wxSize(817, 600))
{
	//Add a menu bar
	m_MenuBar = new wxMenuBar(); // Create the menubar
	this->SetMenuBar(m_MenuBar); //Set the frame's Menu bar to this menu bar
	
	//Add Menu for file operations
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	//Add File Menu to Menu Bar
	m_MenuBar->Append(menuFile, "File");

	//Add a toolbar for palette
	//Frame is responsible for creating toolbar
	m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY); //Toolbar is horizontally placed
	
	//Create Colour Palette as an array of colours
	wxColour palette[16];
	palette[0] = wxColour(0, 0, 0);
	palette[1] = wxColour(0, 0, 128);
	palette[2] = wxColour(0, 128, 0);
	palette[3] = wxColour(0, 128, 128);
	palette[4] = wxColour(128, 0, 0);
	palette[5] = wxColour(128, 0, 128);
	palette[6] = wxColour(128, 128, 0);
	palette[7] = wxColour(192, 192, 192);
	palette[8] = wxColour(128, 128, 128);
	palette[9] = wxColour(0, 0, 255);
	palette[10] = wxColour(0, 255, 0);
	palette[11] = wxColour(0, 255, 255);
	palette[12] = wxColour(255, 0, 0);
	palette[13] = wxColour(255, 0, 255);
	palette[14] = wxColour(255, 255, 0);
	palette[15] = wxColour(255, 255, 255);

	for (int i = 0; i < 16; i++)
	{
		wxButton* b = new wxButton(m_ToolBar, 10100 + i, "", wxDefaultPosition, wxSize(44, 24), 0);
		b->SetBackgroundColour(palette[i]); //Colour button according to palette
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this); //Bind Dynamically
		m_ToolBar->AddControl(b); //Add button to toolbar


	}

	wxButton* b = new wxButton(m_ToolBar, 10100 + 16, "ALPHA", wxDefaultPosition, wxSize(44, 24), 0);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this); //Bind Dynamically

	m_ToolBar->AddControl(b);

	m_ToolBar->Realize(); //Instructs wxWidgets to create Toolbar




}

cMain::~cMain()
{

}

bool cMain::OnOpen(wxString Filename)
{
	cEditorFrame* f = new cEditorFrame(this, Filename);

	f->Open(Filename);

	f->Show();

	return false;
}



void cMain::OnMenuNew(wxCommandEvent& evt)
{
	cEditorFrame* f = new cEditorFrame(this, "Test"); //Associate it with the Parent Frame ie Main
	f->New(24, 24); //Create a New Sprite with resolution 16*16 pixels
	f->Show();
	evt.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent& evt)
{
	//               Parent, Title, default path, default file, "Text description|*extention allowed"ie.spr, Use Open Dialog and the file must exist
	wxFileDialog dlg(this, "Open olcSprite File", "", "", ".spr Files(*.spr)|*.spr", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK) //Show modal displays the dialog and doesn't allow input anywhere else until ok is clicked
	{
		cEditorFrame* f = new cEditorFrame(this, dlg.GetPath()); //OPen a new dialog window and name it according to File path
		f->Open(dlg.GetPath());  //Call Open function of child window
		f->Show();  //Show it
	}

	evt.Skip();
}

void cMain::OnMenuSave(wxCommandEvent& evt)
{
	if (GetActiveChild() != nullptr) //There must be an active child
	{
		wxFileDialog dlg(this, "Save olcSprite File", "", "", ".spr Files(*.spr)|*.spr", wxFD_SAVE | wxFD_OVERWRITE_PROMPT); //PROMPT IF YOU ARE OVERWRITING A FILE
		if (dlg.ShowModal() == wxID_OK)
		{
			((cEditorFrame*)GetActiveChild())->Save(dlg.GetPath()); //Save active frame to current  path
		}


	}
}

void cMain::OnMenuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void cMain::OnSelectColour(wxCommandEvent& evt)
{
	int colour = evt.GetId() - 10100;  //calculate value of colour from event Id
	if (GetActiveChild() != nullptr)  //Make sure that the at least one active child is available
	{
		((cEditorFrame*)GetActiveChild())->SetColour(colour); //Set the colour of the active child frame 
	}
}

