#include "Main.h"
#include "mines2.xpm"

/*
//For older compilers
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
*/


using namespace std;


//Not necessary.. I did dynamic linking
//wxBEGIN_EVENT_TABLE(cMain, wxFrame)
//wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(NULL, wxID_ANY, "MINESWEEPER by Uzo", wxPoint(100, 100),wxSize(800,600))
{

    btn = new wxButton*[nFieldWidth * nFieldHeight]; //A dynamically allocated 1d array of pointers to wxButtons
    wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0); // A grid of with rows and clolumns specified

    nField = new int[nFieldWidth * nFieldHeight]; // Array representing the mine field in 1D space

    wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false); // Font Variable for specifying font

    //Creation and Customization of wxButtons
    for (int x = 0; x < nFieldWidth; x++)
    {
        for(int y =0 ; y < nFieldHeight; y++)
        {
            // int i = y*nFieldWidth + x;
            //ostringstream ss;
            //ss << i;
            //string str = ss.str();

            //Create the actual buttons pointed to by each element i.e. initialize the pointers
            btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));  // (inner loop y * width + outer loop x) to convert from 2d coordinates to 1d you can avoid this by using 2d array
            btn[y * nFieldWidth + x]->SetFont(font);  //set Font to the font object

            btn[y * nFieldWidth + x]->SetOwnBackgroundColour(wxColour(23, 160, 204)); //Set Colour using rgb values

            grid->Add(btn[y*nFieldWidth + x], 1 , wxEXPAND | wxALL);


            btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this ); // Dynamic binding to event handler
            nField[y*nFieldWidth + x] = 0; // 0 will be used to represent no mine in the button. All buttons are set to no mines

            //  btn[x][y] = new wxButton(this, 10000 + (y*nFieldWidth + x ));
            //grid->Add(btn[x][y], 1, wxEXPAND | wxALL);

        }
    }
    this->SetSizer(grid); // Tells Frame (Parent window) to use this sizer as it's sizer
    grid->Layout(); // Restructure itself depending on the information it has now
}

cMain::~cMain()
{
    //Delete dynamically allocated space to avoid memory leaks
    delete[]btn;
    delete[]nField;
}
//Visualization of arrangement
/*
0 10 20 30 40 50 60 70 80 90
1 11 12 13 14 15 16 17 18 19
2 21 22 23 24 25 26 27 28 29
3 31 32 33 34 35 36 37 38 39
4 41 42 43 44 45 46 47 48 49
5 51 52 53 54 55 56 57 58 59
6 61 62 63 64 65 66 67 68 69
7 71 72 73 74 75 76 77 78 79
8 81 82 83 84 85 86 87 88 89
9 91 92 93 94 95 96 97 98 99
*/
void cMain::OnButtonClicked(wxCommandEvent &evt)
{
    //Get coordinate of button in the button field array by converting from 1d to 2d
    int x = (evt.GetId() - 10000) % nFieldWidth; // Remainder is equal to x from the formula (y*width + x) also The Unit value is taken as x
    int y = (evt.GetId() - 10000) / nFieldWidth; // Truncated Dividend is y or Tens Value is y

    //We want the Mines to be created after the first click so that every player has a chance
    if (bFirstClick)
    {
        //There will be thirty mines....I may change this to a selectable difficulty menu
        int mines = 30;

        //This loops until the mine are all created randomly
        while (mines)
        {
            //A random X and Y coordinate is generated
            int rx = rand() % nFieldWidth;
            int ry = rand() % nFieldHeight;

            //Check that there is no mine there and it is not the current button
            if(nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
            {
                nField[ry * nFieldWidth + rx] = -1; //Mines will be indicated by -1
                mines--;
            }

        }
        bFirstClick = false; //it is no longer the first click
    }

    //Disable Button, preventing it from being pressed again
    btn[y * nFieldWidth + x]->Enable(false);
    btn[y * nFieldWidth + x]->SetOwnBackgroundColour( wxColour("AQUAMARINE"));

   // Check if player hit mine
    if(nField[y * nFieldWidth + x] == -1)
    {
        //Create an Image from file 
        //wxImage image("mines2.bmp", wxBITMAP_TYPE_BMP);        
        wxBitmap bitmap(mines2_xpm); //Create bitmap from Image

        //If you want to use Icon
        //wxIcon icon("small.ico", wxBITMAP_TYPE_ICO);
        //bitmap.CopyFromIcon(icon);
        
        //Change Colour and Bitmap Icon
        btn[y * nFieldWidth + x]->SetOwnBackgroundColour(wxColour(169, 204, 138));
        btn[y * nFieldWidth + x]->SetBitmap(bitmap);


        //Check all the buttons for mines and colour them 
        for(int x = 0; x < nFieldWidth; x++)
        {
            for(int y =0; y< nFieldHeight; y++)
            {

                if(nField[y * nFieldWidth + x] == -1)
                {
                    btn[y * nFieldWidth + x]->SetOwnBackgroundColour(wxColour(169,204,138));
                    btn[y * nFieldWidth + x]->SetBitmap(bitmap); //Set their icon too
                }

            }
        }

        wxMessageBox("BOOOOOOM !! - Game Over :( ");

        //Reset the game
        bFirstClick = true;
        for(int x = 0; x < nFieldWidth; x++)
        {
            for(int y =0; y< nFieldHeight; y++)
            {
                nField[y * nFieldWidth + x] = 0;
                btn[y * nFieldWidth + x]->SetLabel("");
                btn[y * nFieldWidth + x]->Enable(true);
                btn[y * nFieldWidth + x]->SetOwnBackgroundColour(wxColour(23, 160, 204));
                bitmap.UnRef(); //Removes bitmap from button
                btn[y * nFieldWidth + x]->SetBitmap(bitmap); //Shows the removed image
            }
        }
    }
    else
    {
        //Count Neighbouring mines
        int mine_count = 0;
        for(int i = -1; i < 2 ; i++)   //iterates through 9 buttons around the clicked button inclusive
            for(int j = -1; j < 2 ; j++)
            {
                //Corrects for corners and edge buttons since buttons are between 0 and (nFieldWidth * nFieldHeight) - 1
                if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
                {
                    if(nField[(y + j) * nFieldWidth + (x + i)] == -1)
                        mine_count++;
                }
            }
      
        // Update button label to show mine count if > 0
        if(mine_count > 0)
        {
/*          //Old code for compilers not supporting int to string conversion
            ostringstream mc;
            mc << mine_count;
            string str = mc.str();
            btn[y * nFieldWidth + x]->SetLabel(str);
*/
            btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
        }

        //Still trying to Implement an automatic clicker for mine free areas
        /*if(mine_count == 0)
        {
            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight && (i != 0 & j != 0))
                    {
                        btn[(y + j) * nFieldWidth + (x + i)]->Enable(false);
                        btn[(y + j) * nFieldWidth + (x + i)]->SetOwnBackgroundColour(wxColour("AQUAMARINE"));
                        if(nField[(y + j) * nFieldWidth + (x + i)] == 0)
                        {
                            btn[(y+j)* nFieldWidth + (x + i)]->Enable(false);
                            btn[(y+j)* nFieldWidth + (x + i)]->SetOwnBackgroundColour( wxColour("AQUAMARINE"));
                            evt.SetId(10000 + ((y + j) * nFieldWidth + (x + i)));
                            OnButtonClicked(evt);
                        }
                    }
                }
            }

        }*/


    }



    evt.Skip();
}


