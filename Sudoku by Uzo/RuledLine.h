#pragma once

//I am creating a custon widget control to create ruled lines 
//for beautification purposes

#include <wx/wx.h>
#include <wx/statline.h>
#include "wx/vscroll.h"




class RuledLine : public wxStaticLine
{
public:
	RuledLine( wxWindow *parent);
	~RuledLine();
private:

	//We would overide the normal drawing routine of the control
	void OnDraw(wxDC& dc); //Actual drawing code
	void OnPaint(wxPaintEvent& evt); //Called whenever the control needs to update its screen presence eg refresh and resized or now visible

};

