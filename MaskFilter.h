#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageFilter.h"
#include<numeric>

// This functions multiplies every pixel of an image by the corresponding pixel of a mask. 

namespace librarypepe {
    class MaskFilter : public ImageFilter
    {
        typedef short T;

    public:

        // Constructor that initializes the threshold at 0 
        MaskFilter() : mask_(0) {}; 

        // Get and set functions for the threshold value 
        const Image& getInputMask() const {
            return const_cast<const Image&>(*mask_);
        }

        void setInputMask(const Image& i) {
            mask_ = const_cast<Image*>(&i); // the _input is not constant. 

        }

        virtual void update() override {
            execute(getInput(), getInputMask());
        }

    protected:
        // Override the execute function 
        virtual void execute(const Image& i) override {};
        virtual void execute(const Image& i, const Image& m)  
        {
            _output.resize(i.size());

            for (unsigned int t{ 0 }; t < i.dim(4); ++t) {                                 // Go through all the dimensions 
                for (unsigned int c{ 0 }; c < i.dim(3); ++c) {
                    for (unsigned int z{ 0 }; z < i.dim(2); ++z) {
                        for (unsigned int y{ 0 }; y < i.dim(1); ++y) {
                            for (unsigned int x{ 0 }; x < i.dim(0); ++x) {
                                _output(x, y, z, c, t) = i(x, y, z, c, t) * m(x, y, z, c, t);   // Multiply both the image and the mask.
                            }

                        }
                    }
                }
            }
        }

    private:
        Image* mask_; // The mask image. 
    };
}