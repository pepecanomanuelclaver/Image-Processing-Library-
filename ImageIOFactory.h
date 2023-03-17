#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageIOBase.h"
#include"PIP_functions.h"
#include"MHD_function.h"

namespace librarypepe {
	class ImageIOFactory {
	public:
		static unique_ptr<ImageIOBase> getIO(const string& filename);
	};

    unique_ptr<ImageIOBase> ImageIOFactory::getIO(const string& filename) { // ImageIOBase* definition in imageIOfactory
                                                                            
        size_t position = filename.find_last_of(".\\");
        string filetype = filename.substr(position + 1);

        // Points to the corresponding type of image. 
        if (filetype == "mhd") {
            return make_unique<MhdImageIO>(filename);                      // Pointer to the read and write MHD
        }
        else if (filetype == "pip") {
            return make_unique<PipImageIO>(filename);                      // Pointer to the read and write PIP
        }
        else if (filetype == "raw") error("\n.Raw files are not admitted, use either .mhd or .pip file please.\n");
        else error("\nThe file format introduced is not correct.");        // In case a wrong file format is introduced. 
    }
}

