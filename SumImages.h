#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageFilter.h"
#include<numeric>

// This function joints one image with another one by summing then. 

namespace librarypepe {
    class SumImages : public ImageFilter
    {
        typedef short T;

    public:

         SumImages() {} ;     // Constructor.

        const Image& getInputImage2() const {                              
            return const_cast<const Image&>(*image2_);
        }

        void setInputImage2(const Image& i) {                            // Set inputs of the mask. 
            image2_ = const_cast<Image*>(&i); 

        }

        virtual void update() override {                                // Execute the input and the mask 
            execute(getInput(), getInputImage2());
        }

    protected:
        // Override the execute function 
        virtual void execute(const Image& i) override {};
        virtual void execute(const Image& i, const Image& m)  
        {
            _output.resize(i.size());

            for (unsigned int t{ 0 }; t < i.dim(4); ++t) {                                  // Loops over all dimensions 
                for (unsigned int c{ 0 }; c < i.dim(3); ++c) {
                    for (unsigned int z{ 0 }; z < i.dim(2); ++z) {
                        for (unsigned int y{ 0 }; y < i.dim(1); ++y) {
                            for (unsigned int x{ 0 }; x < i.dim(0); ++x) {
                                _output(x, y, z, c, t) = i(x, y, z, c, t)+m(x, y, z, c, t); // Adds one mask to another 
                            }

                        }
                    }
                }
            }
        }

    private:
        Image* image2_;  // Pointer to the second image.
    };
}