#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageIOBase.h"


namespace librarypepe {
    Image MhdImageIO::read() {
        vector<string> data;
        ifstream ifs{ filename };                       // Read the filename of interest of MHD. 

        string ElementDataFile;                         // Creates all the strings of the data of interest. 
        string NDims;
        string DimSize;
        string ElementType;
        int count_DimSize = 0;

        // Iterates through the text until reaches the data of interest. 
        for (string x; getline(ifs, x);) {              
            for (string x; getline(ifs, x);) { 
                if (x.find("NDims") != string::npos) { 
                    size_t position = x.find_last_of(" = ");
                    NDims = x.substr(position + 1);
                }
                if (x.find("DimSize") != string::npos) { 
                    size_t position = x.find_last_of("=");
                    DimSize = x.substr(position + 2);   // Gets the information from the values after the =.
                    count_DimSize++;
                }
                if (x.find("ElementType") != string::npos) { 
                    size_t position = x.find_last_of(" = ");
                    ElementType = x.substr(position + 1);
                }
                if (x.find("ElementDataFile") != string::npos) { 
                    size_t position = x.find_last_of(" = ");
                    ElementDataFile = x.substr(position + 1);
                }
            }
        }

        int space(0);

        istringstream is(DimSize);
        int p;
        int number_voxels = 1;
        vector<int> positions;
        int count = 0;
        array<int, N_DIM> dim = { 1,1,1,1,1 };

        while (is >> p) {
            dim[count++] = int(p);
            number_voxels = number_voxels * p;                                        // Gets the number of voxels in the image. 
        }

        if (stoi(NDims)!= count) error("\nFiles dimensions do not match.");           // In case the dimensions of the input does not correspond.
        if (ElementType != "MET_SHORT")error("\nThe Element Type is not MET_SHORT!"); // In case the element type is not an error. 

        Image image(dim);
        ifstream ips{ ElementDataFile,ios_base::binary };
                    // In case the data cannot be openned. 

        int count_image = 0;
        for (Image::iterator p = image.begin(); p != image.end(); ++p) {              // Iterates through all the voxels of the image.
            ips.read(as_bytes(*p), sizeof(Image::value_type));
            count_image = count_image++; 
        }

        if (!ips) error("\nThe file dimensions do not match.");                       // In case the file is shorter. 
        int ch = 0;
        ips.read(as_bytes(ch), sizeof(Image::value_type));                            // Reads next character and check if it is the last one. 
        if (!ips.eof()) error("\nThe file dimensions do not match.");                 // In case the file is longer. 

        if (number_voxels != count_image)error("\nThe dimensions do not match.");     // In case the dimensions do not match. 

        return image;

        ips.close();
    }

    void MhdImageIO::write(Image& image) { // The filename will be defined in the main function. 

        size_t position = filename.find_last_of(".\\");
        string filename_in = filename.substr(0, position);
        string filename_out = filename_in + "_out";

                                        // Write the MHD file 
        string mhd = filename_out + ".mhd";
        ofstream ofs{ mhd }; 
        string dim;
        ofs << "ObjectType = Image";
        ofs << "\nNDims = 3";
        ofs << "\nDimSize = ";

        int count = 0;                  // Introduce the Dimensions
        for (int x : image.size()) {        
            count = count++;
            if (count <= 3){
                dim += to_string(x);
                dim += " "; 
                ofs << x;
                ofs << " ";
            }
        }

        ofs << "\nElementType = MET_SHORT";
        ofs << "\nElementDataFile = ";

        string raw;                      // Write RAW file.
        raw = filename_out+ ".raw";      // Add the .raw extension. 
        ofs << raw;
        ofs.close();

        ofstream ofsraw{raw, ios_base::binary }; 
        for (Image::iterator p = image.begin(); p != image.end(); ++p) {           // Iterates and writes the raw file. 
            ofsraw.write(as_bytes(*p), sizeof(Image::value_type));
        }
        ofsraw.close();
    }
}