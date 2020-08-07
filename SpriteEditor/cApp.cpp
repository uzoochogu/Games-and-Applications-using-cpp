#include "cApp.h"
#include "SpriteEditor.xpm"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}



bool cApp::OnInit()
{
   cMain* m_frame1 = new cMain();

   //For Application icon
   //wxIcon icon("Sprite Editor.ico", wxBITMAP_TYPE_ICO);
 /*  if (argv[1] != 0)
   {
       m_frame1->OnOpen(argv[1]);
   }*/
   m_frame1->SetIcon(SpriteEditor_xpm);

    m_frame1->Show();


    return true;
}

