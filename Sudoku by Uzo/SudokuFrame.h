#pragma once
#include <wx/wx.h>
#include <wx/statline.h>


class SudokuFrame : public wxFrame
{
public:
	SudokuFrame(wxWindow* parent);
	~SudokuFrame();

	int nFieldWidth = 11;
	int	nFieldHeight = 11;
	wxTextCtrl** m_TextCtrl;


private:
	void OnCheckButtonClicked(wxCommandEvent& evt);
	void OnSaveButtonClicked(wxCommandEvent& evt);
	

};

