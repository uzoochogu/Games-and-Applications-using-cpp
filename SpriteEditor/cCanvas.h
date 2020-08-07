#pragma once
//We are creating a custom widget control to handle sprite editing 
//it inherits fron wxHVScrolledWindow
#include "wx/wx.h"
#include "wx/vscroll.h"

class cCanvas : public wxHVScrolledWindow
{
public:
	cCanvas(wxWindow *parent); //So that we can link it with parent
	~cCanvas();

private:
	int m_nPixelSize = 8;

public:
	void SetPixelSize(int n);
	void SetSpriteData(int rows, int columns, unsigned char* pSprite);  //takes size of sprite and pointer to array representing colours
	void SetColour(int c); //To set colour

private:
	unsigned char* m_pSprite = nullptr; //store a private pointer to the pointer we pass in
	wxColour palette[16];  //Create colour palette as an array of colours
	int m_nColour = 16; //To store colour

private:
	//wxHVScrolledWindow needs an implementation of these two functions
	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t col) const;


	//We would overide the normal drawing routine of the control
	void OnDraw(wxDC& dc); //Actual drawing code
	void OnPaint(wxPaintEvent& evt); //Called whenever the control needs to update its screen presence eg refresh and resized or now visible

	void OnMouseLeftDown(wxMouseEvent& evt);

	wxDECLARE_EVENT_TABLE(); //We are going to process events here
};

