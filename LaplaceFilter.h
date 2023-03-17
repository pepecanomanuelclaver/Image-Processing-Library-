#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageFilter.h"
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageFilter.h"

// The Laplacian is a 2-D isotropic measure of the 2nd spatial derivative of an image. 
// The Laplacian of an image highlights regions of rapid intensity change and is therefore
// often used for edge detection (see zero crossing edge detectors). The Laplacian is often
// applied to an image that has first been smoothed with something approximating a Gaussian
// smoothing filter in order to reduce its sensitivity to noise, and hence the two variants 
// will be described together here. The operator normally takes a single graylevel image as 
// input and produces another graylevel image as output.

namespace librarypepe {

    class LaplaceFilter : public ImageFilter
    {
        typedef short T;

    public:

        LaplaceFilter() {} // Constructor for the filter.

    protected:
        // Override the execute function 
        virtual void execute(const Image& i) override
        {
            _output.resize(i.size());
            // Iterate through all the dimensions. 
            for ( int c{ 0 }; c < i.dim(4); ++c) {
                for ( int t{ 0 }; t < i.dim(3); ++t) {
                    for ( int z{ 0 }; z < i.dim(2); ++z) {
                        for ( int y{ 0 }; y < i.dim(1); ++y) {
                            for ( int x{ 0 }; x < i.dim(0); ++x) {

                                int sum = 0;
                                int count = 0;

                                // Kernell convolution 
                                for ( int x_r{x-1}; x_r <= (1+x); x_r++) {
                                    for ( int y_r{y-1}; y_r <= (1+y); y_r++) {
                                        count++;
                                        if (count==5) {                                // The central position.
                                            sum += (i(x_r, y_r, z, c, t) * 8); 
                                        }
                                        else {
                                            sum += (i(x_r, y_r, z, c, t) * -1);        // The external positions. 
                                        }
                                    }
                                }

                                // Here the mask ends 
                                int average = sum/9;                                   // The sum of the 9 pixels is averaged. 
                                _output(x, y, z, c, t) = average;                      // Assign the value to the corresponding output. 
                            }
                        }
                    }
                }
            }


        }
    };

}