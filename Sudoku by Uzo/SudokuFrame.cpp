#include "SudokuFrame.h"
#include "RuledLine.h"


SudokuFrame::SudokuFrame(wxWindow* parent) : wxFrame(parent, wxID_ANY, "Sudoku by Uzo", wxPoint(400, 300), wxSize(400, 400))
{
	m_TextCtrl = new wxTextCtrl*[nFieldWidth * nFieldHeight];
	

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);


	


//Using Vbox and Hbox Sizers to create the sudoku Board

	//wxBoxSizer* b_sizer2 = new wxBoxSizer(wxVERTICAL);
	//
	//for (int x = 0; x < 9; x++)
	//{
	//	wxBoxSizer* b_sizer = new wxBoxSizer(wxHORIZONTAL);
	//	for (int y = 0; y < 9; y++)
	//	{
	//		m_TextCtrl[y * nFieldWidth + x] = new wxTextCtrl(this, 10000 + (y * nFieldWidth + x), "", wxDefaultPosition, wxSize(35, 35), wxTE_CENTRE );
	//		m_TextCtrl[y * nFieldWidth + x]->SetMaxLength(1);
	//		m_TextCtrl[y * nFieldWidth + x]->SetWindowStyle(wxBORDER_NONE);
	//		m_TextCtrl[y * nFieldWidth + x]->SetFont(font);
	//		wxString tv= "";
	//		wxTextValidator txv(wxFILTER_INCLUDE_CHAR_LIST, &tv);
	//		wxArrayString inc(9, "123456789");
	//		txv.SetIncludes(inc);
	//		m_TextCtrl[y * nFieldWidth + x]->SetValidator(txv);

	//		b_sizer->Add(m_TextCtrl[y * nFieldWidth + x], 0, 0, 5);

	//		if ((y + 1) % 3 == 0)
	//		{
	//			wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 35), wxLI_VERTICAL);
	//			b_sizer->Add(staticLine, -1, 0, 1);
	//		}
	//		//else
	//			//b_sizer->Add(0, -1, 0, 5);

	//	}
	//	b_sizer2->Add(b_sizer,-1,wxEXPAND,20);


	//	if ((x + 1) % 3 == 0)
	//	{
	//		wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(35, -1), wxLI_HORIZONTAL);
	//		b_sizer2->Add(staticLine, -1, 0, 1); 

	//	}
	//	//else
	//		//b_sizer2->Add(0, -1, 0, 5);
	//}
	//wxButton* check = new wxButton(this, wxID_ANY, "Check");
	//wxButton* b_save = new wxButton(this, wxID_ANY, "Save");

	//wxBoxSizer* lower_sizer = new wxBoxSizer(wxHORIZONTAL);
	//
	//lower_sizer->Add(check, -1, wxLEFT,0 );
	//lower_sizer->AddSpacer(180);
	//lower_sizer->Add(b_save, -1, wxRIGHT, 0);

	//b_sizer2->Add(lower_sizer, -1, wxEXPAND, 30);




//Using GridSizer to Create Sudoku Board

	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight,0,0);
	//wxBoxSizer* b_sizer = new wxBoxSizer(wxHORIZONTAL);
	//wxBoxSizer* b_sizer2 = new wxBoxSizer(wxVERTICAL);

	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nFieldHeight; y++)
		{
			//m_TextCtrl[y * nFieldWidth + x] = new wxTextCtrl(this, 10000 + (y * nFieldWidth + x), "", wxDefaultPosition, wxSize(35, 35), wxTE_CENTRE);
			//m_TextCtrl[y * nFieldWidth + x]->SetMaxLength(1);
			//m_TextCtrl[y * nFieldWidth + x]->SetWindowStyle(wxBORDER_NONE);
			//m_TextCtrl[y * nFieldWidth + x]->SetFont(font);

			////Make Sure input is between 1-9
			//wxString tv = "";
			//wxTextValidator txv(wxFILTER_INCLUDE_CHAR_LIST, &tv);
			//wxArrayString inc(9, "123456789");
			//txv.SetIncludes(inc);
			//m_TextCtrl[y * nFieldWidth + x]->SetValidator(txv);



			if ((x + 1) % 4 == 0)
			{
				wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
				//wxStaticLine* staticLine2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
				

				//if ((y % 4) == 0)
				//{
				//	wxBoxSizer* b_sizer = new wxBoxSizer(wxVERTICAL);
				//	b_sizer->Add(staticLine, 1, 0, 0);
				//	b_sizer->Add(staticLine2, 1, 0, 0);
				//	grid->Add(b_sizer, 1, 0, 0);

				//}
				//else
				grid->Add(staticLine, 1, wxALIGN_RIGHT, 0);
			}
			else if ((y + 1)% 4 == 0)
			{
				wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
				grid->Add(staticLine, 1, wxALIGN_TOP, 0);
			}
			else
			{
				m_TextCtrl[y * nFieldWidth + x] = new wxTextCtrl(this, 10000 + (y * nFieldWidth + x), "", wxDefaultPosition, wxSize(35, 35), wxTE_CENTRE);
				m_TextCtrl[y * nFieldWidth + x]->SetMaxLength(1);
				m_TextCtrl[y * nFieldWidth + x]->SetWindowStyle(wxBORDER_NONE);
				m_TextCtrl[y * nFieldWidth + x]->SetFont(font);

				//Make Sure input is between 1-9
				wxString tv = "";
				wxTextValidator txv(wxFILTER_INCLUDE_CHAR_LIST, &tv);
				wxArrayString inc(9, "123456789");
				txv.SetIncludes(inc);
				m_TextCtrl[y * nFieldWidth + x]->SetValidator(txv);
				
				grid->Add(m_TextCtrl[y * nFieldWidth + x], 8, 0, 0);
			}


			//if ((y + 1) % 3 == 0) 
			//{
			//	//*m_TextCtrl[y * nFieldWidth + x] << m_TextCtrl[y * nFieldWidth + x]->GetAlignment();
			//	
			//	wxBoxSizer* b_sizer = new wxBoxSizer(wxHORIZONTAL);


			//	b_sizer->Add(m_TextCtrl[y * nFieldWidth + x], 0, wxCENTRE, 0);
			//	wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
			//	b_sizer->AddSpacer(10);
			//	b_sizer->Add(staticLine, -1, wxCENTRE, 5);
			//	m_TextCtrl[y * nFieldWidth + x]->SetValue("1");
			//	

			//	

			//	if ((x + 1) % 3 == 0)
			//	{
			//		wxBoxSizer* b_sizer3 = new wxBoxSizer(wxVERTICAL);
			//		b_sizer3->Add(b_sizer, -1, wxCENTRE, 0);
			//		wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
			//		b_sizer3->Add(staticLine, -1, wxCENTRE, 0);
			//		grid->Add(b_sizer3, -1, wxCENTRE, 0);
			//		m_TextCtrl[y * nFieldWidth + x]->SetValue("2");
			//	}
			//	else
			//	{
			//		grid->Add(b_sizer, -1, wxCENTRE, 5);
			//	}
					

			//}
			//else if ((x + 1) % 3 == 0)
			//{

			//	//*m_TextCtrl[y * nFieldWidth + x] << m_TextCtrl[y * nFieldWidth + x]->GetAlignment();


			//	wxBoxSizer* b_sizer2 = new wxBoxSizer(wxVERTICAL);


			//	b_sizer2->Add(m_TextCtrl[y * nFieldWidth + x], 0, 0, 0);
			//	wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
			//	b_sizer2->AddSpacer(10);
			//	b_sizer2->Add(staticLine, -1, wxCENTRE, 0);
			//	
			//	grid->Add(b_sizer2, -1, wxCENTRE, 5);
			//	m_TextCtrl[y * nFieldWidth + x]->SetValue("3");
			//}
			//else
			//{
			//	grid->Add(m_TextCtrl[y * nFieldWidth + x], 1, wxCENTRE , 5);	
			//	m_TextCtrl[y * nFieldWidth + x]->SetValue("4");
			//	
			//}


		}

		

		
	
	
	}

	wxButton* check = new wxButton(this, wxID_ANY, "Check");
	wxButton* b_save = new wxButton(this, wxID_ANY, "Save");

	wxBoxSizer* lower_sizer = new wxBoxSizer(wxHORIZONTAL);
	
	lower_sizer->Add(check, -1, wxLEFT,0 );
	lower_sizer->AddSpacer(180);
	lower_sizer->Add(b_save, -1, wxRIGHT, 0);

	wxBoxSizer* final_sizer = new wxBoxSizer(wxVERTICAL);
	final_sizer->AddSpacer(20);
	final_sizer->Add(grid, 0, wxEXPAND | wxCENTRE, 30);

	final_sizer->AddSpacer(20);
	wxStaticLine* staticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	final_sizer->Add(staticLine, 1, wxEXPAND, 0);



	final_sizer->AddSpacer(20);
	final_sizer->Add(lower_sizer, 0, wxEXPAND | wxCENTRE, 30);

	final_sizer->SetSizeHints(this);  //b_sizer2
	this->SetSizer(final_sizer);  //b_sizer2
	this->Layout();

}

SudokuFrame::~SudokuFrame()
{
	
}

void SudokuFrame::OnCheckButtonClicked(wxCommandEvent& evt)
{
}

void SudokuFrame::OnSaveButtonClicked(wxCommandEvent& evt)
{
}

