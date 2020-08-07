#include "cEditorFrame.h"

wxBEGIN_EVENT_TABLE(cEditorFrame, wxMDIChildFrame)
EVT_SLIDER(20001, cEditorFrame::OnZoomChange)
wxEND_EVENT_TABLE()

cEditorFrame::cEditorFrame(wxMDIParentFrame* parent, wxString sName): wxMDIChildFrame(parent, wxID_ANY, sName)// we also call the constructor of the class it inherits from, String is used for title bar
{
	m_Canvas = new cCanvas(this); //Associates canvas with its parent 

	//Frame handles creation of Status bar
	m_StatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY); //it has 2 regions
	m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 8, 1, 32); //Default value is 8 range from 1 to 32 in section 2
}

cEditorFrame::~cEditorFrame()
{
}

void cEditorFrame::SetColour(int c)
{	
	m_Canvas->SetColour(c);
}

bool cEditorFrame::Save(wxString sFileName)
{ 
	for (int i = 0; i < sprBase.nWidth; i++)
		for (int j = 0; j < sprBase.nHeight; j++)
		{
			short colour = m_pSprite[j * sprBase.nWidth + i];

			if (colour == 16)
			{
				sprBase.SetColour(i, j, 0);
				sprBase.SetGlyph(i, j, L' ');
			}
			else
			{
				sprBase.SetColour(i, j, colour);
				sprBase.SetGlyph(i, j, 0x2588);
			}
		}

	return sprBase.Save(sFileName.wc_str()); //Allow Sprite class to save it and return 
}

bool cEditorFrame::Open(wxString sFileName)
{
	if (!sprBase.Load(sFileName.wc_str())) //Using olcSprite class 
		return false;
	else //we convert it to a desktop readable form using some olcSprite func
	{
		delete[] m_pSprite;
		m_pSprite = new unsigned char[sprBase.nWidth * sprBase.nHeight]{ 0 }; //Holds converted data
		//Check what the content of the file and does the conversion
		for(int i = 0; i < sprBase.nWidth; i++)
			for (int j = 0; j < sprBase.nHeight; j++)
			{
				wchar_t glyph = sprBase.GetGlyph(i, j);
				short colour = sprBase.GetColour(i, j);

				if (glyph == L' ')
				{
					m_pSprite[j * sprBase.nWidth + i] = 16;
				}
				else
				{
					m_pSprite[j * sprBase.nWidth + i] = colour & 0x000F;
				}
			}
		m_Canvas->SetSpriteData(sprBase.nHeight, sprBase.nWidth, m_pSprite); //Sets the populated data to the canvas
		return true;
	}
}

bool cEditorFrame::New(int r, int c)
{
	delete[] m_pSprite;  //Deletes any existing sprite in case
	m_pSprite = new unsigned char[r * c]{ 0 }; //Enough for width and height of char --Each pixel data is stored in char since it  is from 0-15
	m_Canvas->SetSpriteData(r, c, m_pSprite);  //Links data stored in canvas rectangle to sprite
	sprBase = olcSprite(c, r); //Create a sprite of those dimensions

	return false;
}

void cEditorFrame::OnZoomChange(wxCommandEvent& evt)
{
	m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1); //Update text in Statusbar to Zoomlevel in section 1
	m_Canvas->SetPixelSize(m_ZoomSlider->GetValue());  //Set Pixel Size
	evt.Skip();
}
