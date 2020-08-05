#include <wx/wx.h>

class cMain : public wxFrame
{
public:
    cMain();
    ~cMain();

public:
    int nFieldWidth = 10;
    int nFieldHeight = 10;
    wxButton** btn; // a pointer to a pointer to wxButton or an array of pointers to wxButtons
    int* nField = nullptr;
    bool bFirstClick = true;



    void OnButtonClicked(wxCommandEvent &evt);

  
    
  

    // I Dynamically Linked the button so no need for this 
    //wxDECLARE_EVENT_TABLE();

};
