#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageFilter.h"

// The convolution filter does the media from all the surrouding pixels within the indicated radius. 

namespace librarypepe {
    class ConvolutionFilter : public ImageFilter
    {
        typedef short T;

    public:

        // Constructor 
        ConvolutionFilter() : _r(0) {}

        // Get and set functions for the radius
        T getRadio() const { return _r; }
        void setRadio(T radio) { _r = radio; }

    protected:
        // Override the execute function 
        virtual void execute(const Image& i) override
        {
            _output.resize(i.size());
        // The radius will 
           T num_pixels_mask = _r * _r * _r; 

           for (unsigned int c{ 0 }; c < i.dim(4); ++c) {
               for (unsigned int t{ 0 }; t < i.dim(3); ++t) {
                   for (unsigned int z{ 0 }; z < i.dim(2); ++z) {
                       for (unsigned int y{ 0 }; y < i.dim(1); ++y) {
                           for (unsigned int x{ 0 }; x < i.dim(0); ++x) { // Iterates through all the dimensions 

                               int sum = 0;
                               for (unsigned int x_r{x -_r }; x_r <= _r + x; x_r++) { // Iterates through the convoluted pixels positions. 
                                   for (unsigned int y_r{ y-_r }; y_r <= _r + y; y_r++) {
                                       for (unsigned int z_r{z -_r }; z_r <= _r + z; z_r++) {
                                           sum += i(x_r, y_r, z_r, c, t);
                                       }
                                   }
                               }

                               // Here the mask ends 
                               T average = sum / num_pixels_mask;
                               _output(x, y, z, c, t) = average;

                           }
                       }
                   }
               }
            }
        }

    private:

        T _r;         // The radious 

    };
}
