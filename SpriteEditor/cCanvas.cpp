#include "cCanvas.h"

//Needed for Device Context Manipulation
#include "wx/dcclient.h"  
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(cCanvas, wxHVScrolledWindow)
EVT_PAINT(cCanvas::OnPaint) //Call paint func no need for unique identifier
EVT_LEFT_DOWN(cCanvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()

cCanvas::cCanvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY) //Call constructor of base class linking canvas class to child window
{
	SetRowColumnCount(40, 40);
	SetBackgroundStyle(wxBG_STYLE_PAINT); //Tell wxWdgets not to draw it that we would paint by ourselves

	//Define Colour Palette as an array of colours	
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

}


cCanvas::~cCanvas()
{
}

void cCanvas::SetPixelSize(int n)
{
	m_nPixelSize = n;
	//Force Window to recalculate scrollbar and call the OnGet funcs
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();
	Refresh(); //Force to redraw
}

void cCanvas::SetSpriteData(int rows, int columns, unsigned char* pSprite)
{
	m_pSprite = pSprite;  //locally cache pointer to sprite
	this->SetRowColumnCount(rows, columns);  //Sets rows and column count of the canvas depending on width and height of sprite
}

void cCanvas::SetColour(int c)
{
	m_nColour = c;
}

wxCoord cCanvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(m_nPixelSize);
}

wxCoord cCanvas::OnGetColumnWidth(size_t col) const
{
	return wxCoord(m_nPixelSize);
}

void cCanvas::OnDraw(wxDC& dc)
{
	dc.Clear();

	wxBrush brush = dc.GetBrush(); //describes what the inside of a shape looks like
	wxPen pen = dc.GetPen();   //describes what the outline or boundary looks like
	
	//Only draw what you can see --a good rule
	//Gets visible extent
	wxPosition s = GetVisibleBegin();
	wxPosition e = GetVisibleEnd();

	//Set Pen properties
	pen.SetStyle(wxPENSTYLE_LONG_DASH); //Long dash line
	pen.SetColour(wxColour(200, 200, 200)); //Grey
	
	dc.SetPen(pen);  //Commit pen to device context

	if (m_nPixelSize <= 4) dc.SetPen(*wxTRANSPARENT_PEN); //then switch it off

	for(int y= s.GetRow(); y < e.GetRow(); y++)
		for (int x = s.GetCol(); x < e.GetCol(); x++)
		{
			int colour = m_pSprite[y * this->GetColumnCount() + x];  //Extracts colour from the array from 2d to 1d

			if (colour < 16) //then it is one of the colours
			{
				brush.SetColour(palette[colour]); //according to the colour palette
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else  //Then it is transparent
			{
				brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
				brush.SetColour(wxColour(0, 0, 0)); //No colour...we will represent with hatch
				
			}

			dc.SetBrush(brush); //Commit brush to device context
			dc.DrawRectangle(x*m_nPixelSize, y*m_nPixelSize, m_nPixelSize, m_nPixelSize); //Changes with current pixel size
		}

	


}

void cCanvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this); //We are  Painting a Device Context, this is the established way to dray custom control It is a memory surface you draw on
	this->PrepareDC(dc);  //Get the device context ready for rendering
	this->OnDraw(dc);  // Calls the draw event handler
	//no evt.Skip because we have handled everything 
}

void cCanvas::OnMouseLeftDown(wxMouseEvent& evt)
{
	wxPosition s = GetVisibleBegin();
	m_pSprite[(evt.GetY() / m_nPixelSize + s.GetRow()) * this->GetColumnCount() + (evt.GetX() / m_nPixelSize + s.GetCol())] = m_nColour; //Gets mouse y coordinate, integer divide by pixel size variable to break it down to individual cells and offsets that value from the topmost visible row, Then we multiply result by Width from the column count and add a similarly offset x value ie y*width + x . Then the colour is asigned
	this->Refresh(false); //Redraw only this not everything that's why we sent false parameter 
	evt.Skip();
}
