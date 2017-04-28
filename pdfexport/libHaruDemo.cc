//pdfTest.cc
//author: Nicole Regenauer
//this document draws heavily upon the "libharu" library for PDF creation
//all credit for this library goes to its authors
//this library can be found at the link below
//https://github.com/libharu/libharu

#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include "hpdf_types.h"
using namespace std;

//freature added to library to help with error handling
//more detail provided on libharu page
jmp_buf env;
//this is pulled straight from the help files for libharu
//i will look it over later
#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no, HPDF_STATUS   detail_no, void *user_data){
    cout << "ERROR: error_no=%04X, detail_no=%u\n" << (HPDF_UINT)error_no << " " << (HPDF_UINT)detail_no;
    longjmp(env, 1);
}

const char *text_list[] = {
    "In the actual code",
    "We will pass in whatever notes were displayed",
    "in the actual program",
    "then space them out appropriately",
    "add them on to a staff",
    "draw bar lines where we need them",
    "go to a new line where we need to",
    "and ensure that at the start of each new line",
    "we have a time signature and key signature",
    NULL
};

int main (int argc, char **argv)
{
    //libharu was written for use with c technically
    //it doesn't like it if you use strings
    //instead, have to treat strings as pointers to arrays of characters
    const char* page_title = "553 2017 Demo for PDF Export Module";
    //creating variables for all paramaters used in this file
    //first variable: stores value of entire pdf file
    //HPDF_Doc is a type defined in hpdf.h
    HPDF_Doc  pdf;
    char* fname="my_demo_file";
    //this variable is just the page that we are going to be "drawing" on
    HPDF_Page page;
    //this is a "font" variable -> lets us choose what font to write in
    //I suspect we are going to need to do some research and find a "note" font to download
    //ledger lines are easy enough to create, but notes, clefs, etc will be very hard to draw
    HPDF_Font def_font;
    //this is basically a numeric type defined in the harupdf library
    //this variable corresponds to the desired text width-> we use it
    //to make sure no text falls off the edges of the page
    HPDF_REAL text_width;
    //using a method built into these classes to create local copy of the page height
    HPDF_REAL height;
    //using a method built into these classes to create local copy of the page width
    HPDF_REAL width;
    HPDF_UINT i;

    //this is creating the name for the output PDF
    //appending the name that I created to the .pdf extension
    //VERY VERY IMPORTANT
    //strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    //creating a new PDF file
    //paramaters to that function include error handling functions
    //and desired memory freeing function
    //saying NULL just lets the library deal with memory management
    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        cout << "error: unable to create a pdf at this time\n";
        return 1;
    }

    if (setjmp(env)) {
      //if we just got back from the error handler function-> aka an error occured
      //free any memory that we unsuccessfully tried to allocate
      //aka don't create a corrupt PDF file
        HPDF_Free (pdf);
        return 1;
    }
    //add a new page to the PDF object that we created
    page = HPDF_AddPage (pdf);
    //return local copies of the height and width of the page that we just created
    //WORTH NOTING: it is possible to set the height and width paramaters for the page
    //I chose not to do it here, but they can be passed in as creation arguments
    //when the page is created
    height = HPDF_Page_GetHeight (page);
    width = HPDF_Page_GetWidth (page);

    //we are going to draw a "box" border around the page
    //defining the page boundaries and demonstrating the functionality of the library
    //later, probably going to want to draw closely spaced groups of lines instead
    //these can serve as the staff
    HPDF_Page_SetLineWidth (page, 1);
    //define size of the rectangle we are about to draw
    HPDF_Page_Rectangle (page, 50, 50, width - 120, height - 120);
    //actually render the rectangle in the PDF
    HPDF_Page_Stroke (page);

    //retrive the font info from the library to use in the PDF
    //lots of fonts are defined-> pretty cool
    def_font = HPDF_GetFont (pdf, "Helvetica", NULL);
    //set the font type and size that we will be using to write when we start
    HPDF_Page_SetFontAndSize (page, def_font, 32);

    //make sure that our text doesn't fall off the edge of the page
    //return the width of the text based on what we want to print out
    text_width = HPDF_Page_TextWidth (page, page_title);
    //render the text to the PDF, again making sure it doesn't go past the upper
    //height or width
    HPDF_Page_BeginText (page);
    HPDF_Page_TextOut (page, (width - text_width) / 2, height - 50, page_title);
    HPDF_Page_EndText (page);

    //creating a new subtext box-> going to add more text here!
    //using a smaller font
    //and starting on the LHS inside our border rather than in the center
    HPDF_Page_BeginText (page);
    HPDF_Page_SetFontAndSize (page, def_font, 16);
    HPDF_Page_TextOut (page, 60, height - 90, "I am trying to write a block of text");
    HPDF_Page_EndText (page);

    //creating another new text box
    HPDF_Page_BeginText (page);
    //moving it to somewhere that we haven't started to write yet
    HPDF_Page_MoveTextPos (page, 60, height - 105);

    i = 0;
    while (text_list[i]) {
        //defining a new font size just for some variety
        HPDF_Page_SetFontAndSize (page, def_font, 9);
        HPDF_Page_ShowText (page, "This is a new line");
        HPDF_Page_MoveTextPos (page, 0, -18);

        //reading through a variable array of text sizes
        //this will most likely be super helpful when we are passing in MIDI files
        //of varying sizes
        HPDF_Page_SetFontAndSize (page, def_font, 20);
        HPDF_Page_ShowText (page, text_list[i]);
        HPDF_Page_MoveTextPos (page, 0, -20);

        i++;
    }
    //have to call this function to finish the "page" definition
    //and make sure we adhere to the PDF file format
    HPDF_Page_EndText (page);

    //this makes a new file with the name that we want
    HPDF_SaveToFile (pdf, fname);

    //this function lets the library handle all our memory management
    HPDF_Free (pdf);

    return 0;
}
