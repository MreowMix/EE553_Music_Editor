//simpleLedgerRender.cc
//Author: Nicole Regenauer
//this file is a "jump-off" point for the PDF export class
//it creates a single page filled with "ledger lines"
//as the project continues, we will need to modify this code
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <setjmp.h>
#include "hpdf.h"
#include <iostream>
using namespace std;
/*#include <iostream>
using namespace std;*/

jmp_buf env; //built in error handling class

#ifdef HPDF_DLL
void __stdcall
#else
void
#endif
//this error handling function was written by the creators of libharu
//uses some old stye c syntax
//works with the error codes they defined in their library
//All credit for the function goes to them
error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data){
  printf ("Error: error_no=%04X, detail_no=%u\n",
          (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
  longjmp(env,1);
}

//drawing a formatted set of 6 lines
//going to want to do this over and over again to create "staff lines"
void draw_staff_grouping(HPDF_Page page, float x, float y, float width, float spacing, float lw){
  HPDF_Page_SetLineWidth(page,lw);
  HPDF_Page_MoveTo(page,x,y);
  for(int i=0;i<5;i++){
    HPDF_Page_LineTo(page,x+width,y - (i*spacing));
    HPDF_Page_Stroke(page);
    HPDF_Page_MoveTo(page,x,y - (i+1)*spacing);
  }
  HPDF_Page_Stroke(page);
}

int main(){
  HPDF_Doc staff;
  //later, might make this a changable parameter
  HPDF_Font font;
  HPDF_Page page1; //at least need one page by default
  char* filename = "StaffDemo";
  //string as pointer to chars  -> using old c stuff
  //to append appropriate file ending to this
  strcat(filename,".pdf");
  HPDF_REAL height;
  HPDF_REAL width;

  staff = HPDF_New(error_handler,NULL);
  if(!staff){
    printf("Error: unable to create a PDF successfully\n");
  }
  if(setjmp(env)){
    HPDF_Free(staff);
    return 1;
  }

  font = HPDF_GetFont(staff,"Helvetica",NULL);

  page1 = HPDF_AddPage(staff);
  height = HPDF_Page_GetHeight(page1);
  cout << "Height is: " << height << endl;
  width = HPDF_Page_GetWidth(page1);
  cout << "Width is: " << width << endl;
  while(height>20){
    draw_staff_grouping(page1, 20, height-20, width-40,6, 1.0);
      height-=60;
  }

  HPDF_SaveToFile (staff, filename);

  HPDF_Free (staff);

  return 1;
}
