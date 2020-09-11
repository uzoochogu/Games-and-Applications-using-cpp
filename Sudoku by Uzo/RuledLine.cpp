#include "RuledLine.h"

//Needed for Device Context Manipulation
#include "wx/dcclient.h"  
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

RuledLine::RuledLine(wxWindow* parent) : wxStaticLine(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT); //Tell wxWdgets not to draw it that we would paint by ourselves
	Connect(wxEVT_PAINT, wxPaintEventHandler(RuledLine::OnPaint)); //Connect paint event to event handler

	
}

RuledLine::~RuledLine()
{
}


void RuledLine::OnDraw(wxDC& dc)
{
	dc.Clear();

	

	wxSize size = GetSize();
	int width = size.GetWidth();
	

	wxBrush brush = dc.GetBrush(); //describes what the inside of a shape looks like
	wxPen pen = dc.GetPen();   //describes what the outline or boundary looks like
	
							   
							   
	//Set Pen properties
	pen.SetStyle(wxPENSTYLE_LONG_DASH); //Long solid line
	pen.SetColour(wxColour(200, 200, 200)); //Grey

	dc.SetPen(pen);   //Commit pen to device context 

	dc.DrawLine(wxPoint(50, 50), wxPoint(100, 100));
	//dc.DrawLine(s.GetCol() + 40,s.GetRow() + 40 , s.GetCol()+80, s.GetRow() + 80);
	//dc.DrawRectangle(50, 50, 100, 100);
	//dc.DrawText("Test", this->GetPosition());


}

void RuledLine::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this); //We are  Painting a Device Context, this is the established way to dray custom control It is a memory surface you draw on
	this->PrepareDC(dc);  //Get the device context ready for rendering
	this->OnDraw(dc);  // Calls the draw event handler
	//no evt.Skip because we have handled everything 	
}
