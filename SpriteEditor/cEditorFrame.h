#include "wx/wx.h"

#include "cCanvas.h" 
using namespace std;




class olcSprite
{
public:
	olcSprite()
	{

	}

	olcSprite(int w, int h)
	{
		Create(w, h);
	}

	olcSprite(wstring sFile)
	{
		if (!Load(sFile))
			Create(8, 8);
	}

	int nWidth = 0;
	int nHeight = 0;

private:
	wchar_t* m_Glyphs = nullptr;
	short* m_Colours = nullptr;

	void Create(int w, int h)
	{
		nWidth = w;
		nHeight = h;
		m_Glyphs = new wchar_t[w * h];
		m_Colours = new short[w * h];
		for (int i = 0; i < w * h; i++)
		{
			m_Glyphs[i] = L' ';
			m_Colours[i] = 0;
		}
	}

public:
	void SetGlyph(int x, int y, wchar_t c)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return;
		else
			m_Glyphs[y * nWidth + x] = c;
	}

	void SetColour(int x, int y, short c)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return;
		else
			m_Colours[y * nWidth + x] = c;
	}

	wchar_t GetGlyph(int x, int y)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return L' ';
		else
			return m_Glyphs[y * nWidth + x];
	}

	short GetColour(int x, int y)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return 0;
		else
			return m_Colours[y * nWidth + x];
	}

	wchar_t SampleGlyph(float x, float y)
	{
		int sx = (int)(x * (float)nWidth);
		int sy = (int)(y * (float)nHeight - 1.0f);
		if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
			return L' ';
		else
			return m_Glyphs[sy * nWidth + sx];
	}

	short SampleColour(float x, float y)
	{
		int sx = (int)(x * (float)nWidth);
		int sy = (int)(y * (float)nHeight - 1.0f);
		if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
			return 0;
		else
			return m_Colours[sy * nWidth + sx];
	}

	bool Save(wstring sFile)
	{
		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"wb");
		if (f == nullptr)
			return false;

		fwrite(&nWidth, sizeof(int), 1, f);
		fwrite(&nHeight, sizeof(int), 1, f);
		fwrite(m_Colours, sizeof(short), nWidth * nHeight, f);
		fwrite(m_Glyphs, sizeof(wchar_t), nWidth * nHeight, f);

		fclose(f);

		return true;
	}

	bool Load(wstring sFile)
	{
		delete[] m_Glyphs;
		delete[] m_Colours;
		nWidth = 0;
		nHeight = 0;

		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"rb");
		if (f == nullptr)
			return false;

		fread(&nWidth, sizeof(int), 1, f);
		fread(&nHeight, sizeof(int), 1, f);

		Create(nWidth, nHeight);

		fread(m_Colours, sizeof(short), nWidth * nHeight, f);
		fread(m_Glyphs, sizeof(wchar_t), nWidth * nHeight, f);

		fclose(f);
		return true;
	}

};





class cEditorFrame : public wxMDIChildFrame //inherits from child frame
{
public:
	cEditorFrame(wxMDIParentFrame* parent, wxString sName); //Overloaded it so that it is linked to its parent window
	~cEditorFrame();

	void SetColour(int c);
	bool Save(wxString sFileName);
	bool Open(wxString sFileName);
	bool New(int r, int c);

private:
	cCanvas* m_Canvas = nullptr; //add canvas to Editor frame
	wxStatusBar* m_StatusBar = nullptr; //Status bar
	wxSlider* m_ZoomSlider = nullptr;  //Zoom Slider

	olcSprite sprBase;
	unsigned char *m_pSprite = nullptr;

	void OnZoomChange(wxCommandEvent& evt); //Responds to Slider changes

	wxDECLARE_EVENT_TABLE();
};

