class  pdfExport {
//class to compile data for export and create a PDF file
//will use data created by notation and UI teams 
//allows export of multiple data types
//author: Nicole Regenauer
private:
	short output_format;  //format flag, used to specify the type of file for export
			      //ex: type 1 might represent PDF, type 2 might represent word, etc
	short output_type; //flag representing the “type” of output
 //ex, type 1 for a list of MIDI notes, type 2 for sheet music, type 3 for tablature, etc
	string output_name; //name for output file 
public: 
	pdfExport(short output_format=0, short output_type =0, short output_name) : {} 
	//create instance of class and set default output format

	void formatOutput () {
		//pull data from UI/notation output
		//create or utilize previously created data for graphical rendering
}
void createOutput() {
	//write previously created data to PDF file for display 
	//utilizing specifications of PDF format
}
}