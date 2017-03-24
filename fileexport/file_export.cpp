#include "pdf_file.h" //Place holder for pdfExport header file

class fileExport : public pdfExport {
//class to compile data for export other than PDFs
//will inherit from pdfExport
//author: Jack Liang
private:
public:
    fileExport(short output_format, short output_type, short output_name)
        : {}
    void formatOutput(short output_format){
        //pulls data from UI/notation input
        //formats data for output according to output_format parameter
    }
    void createOutput(short output_type) {
        //wrtie file according to output_type parameter
    }
};
