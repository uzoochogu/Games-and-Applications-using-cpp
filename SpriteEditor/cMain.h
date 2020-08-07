#include <wx/wx.h>



#include "cEditorFrame.h"


class cMain : public wxMDIParentFrame //Multi Docking Interface  frame is used
{
public:
	cMain();
	~cMain();
	bool OnOpen(wxString Filename);
private:
	wxToolBar* m_ToolBar = nullptr;
	wxMenuBar* m_MenuBar = nullptr;

	

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);
	
	
	void OnSelectColour(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};

