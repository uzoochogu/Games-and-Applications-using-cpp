#include "App.h"
#include "UzoIcon.xpm"





wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
    
}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
    //Create the Frame
    cMain* m_frame1 = new cMain();
    
    //Creating the Icon for the Window
   // wxImage image2("UzoIcon.bmp", wxBITMAP_TYPE_BMP);
   // wxBitmap bitmap2(image2);
   // wxIcon icon2;
   // icon2.CopyFromBitmap(bitmap2);
    
    m_frame1->SetIcon(UzoIcon_xpm);

    //if you want to use icon
   // wxIcon icon("small.ico", wxBITMAP_TYPE_ICO);
   // m_frame1->SetIcon(icon);


    //Show Frame
    m_frame1->Show();

    return true;
}
