#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageIOBase.h"

namespace librarypepe {
    Image PipImageIO::read() {
        vector<short> v;

        ifstream ifs{ filename,ios_base::binary };
        if (!ifs) error("can't open input file ", filename);

        array<int, N_DIM> dim;

        char datatype{ 0 };
        ifs.read(as_bytes(datatype), sizeof(char));                     // This read reads the first position. 
        if (datatype != 2) error("\nThe data type has to be short!");   // corrupt_01 

        int x, y, z, c, t;
        ifs.read(as_bytes(x), sizeof(int));                             // The dimensions are read, 
        ifs.read(as_bytes(y), sizeof(int));                             // each time the ifs.read functions goes through the next position. 
        ifs.read(as_bytes(z), sizeof(int));
        ifs.read(as_bytes(c), sizeof(int));
        ifs.read(as_bytes(t), sizeof(int));

        if (x < 1 || y < 1 || z < 1 || c < 1 || t < 1) error("\nThe dimensions have to be equal or greater than 1!");  // In case the dimensions introduced are negative. 

        dim[0] = x;                                                     // Assign the dimensions to the correspondant.
        dim[1] = y;
        dim[2] = z;
        dim[3] = c;
        dim[4] = t;

        int volume = x * y * z;                                         // Calculates the number of pixels in volume.  

        Image image(dim);
        int count{ 0 };

        for (Image::iterator p = image.begin(); p != image.end(); ++p) {
            ifs.read(as_bytes(*p), sizeof(Image::value_type));
            count = count++;                                            // Counts the number of iterations
        }

        if (volume != count) error("\nThe header dimensions do not match with the image provided.");   // In case the number of iterations do not match with the number of pixels. 
        if (!ifs) error("\nThe dimensions do not match.");              // In case the file is shorter than the dimensions. 

        int ch=0;
        ifs.read(as_bytes(ch), sizeof(Image::value_type));              // Reads next character. 
        if (!ifs.eof()) error("\nThe file dimensions do not match.");   // In case the file is longer than the dimensions. 

        ifs.close();

        return image;
    }

    void PipImageIO::write(Image& image) {
        // Take the filename of the input and creates the filename of the output.
        size_t position = filename.find_last_of(".\\");
        string filename_in = filename.substr(0, position);
        string filename_out = filename_in + "_out" + ".pip";            // Define the name of the output. 

        cout << "\nThe filename is: " << filename_out;

        ofstream ofs{ filename_out, ios_base::binary }; 
        if (!ofs) error("can't open input file ", filename);

        char initial{ 2 };                                              // Write the first as char. 
        ofs.write(as_bytes(initial), sizeof(char));

        for (int x : image.size())                                      // Write the next ones as int. 
            ofs.write(as_bytes(x), sizeof(int)); //estaba como int

        for (Image::iterator p = image.begin(); p != image.end(); ++p) {
            ofs.write(as_bytes(*p), sizeof(Image::value_type));         // Write the image in bytes. 
        }

        ofs.close();
    }
}