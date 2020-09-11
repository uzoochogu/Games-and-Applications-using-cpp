#pragma once

#include "wx/wx.h" 
#include "cMainDialog.h"

class cApp : public wxApp 
{
public:
	cApp();
	~cApp();
private:
	//cMain* m_frame1= nullptr;
	cMainDialog* m_dialog = nullptr;

public:
	virtual bool OnInit();
};

