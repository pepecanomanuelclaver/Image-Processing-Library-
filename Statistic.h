#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageFilter.h"
#include <numeric>


namespace librarypepe {
    class StaticFilter :public ImageFilter {
        typedef short T;
    public:

        StaticFilter() : Minimum_(0), Maximum_(0), Media(0) {}

        // Get and set functions for the threshold value 
        short getMin() const { return Minimum_; }
        short getMax() const { return Maximum_; }
        short getMedia() const { return Media; }

    protected:
        // Override the execute function 
        virtual void execute(const Image& i) override
        {
            // Bring the threshold parameter within scope, so it can be given to 
            // the lambda initializer 
            Minimum_ = *min_element(i.begin(), i.end());
            Maximum_ = *max_element(i.begin(), i.end());
            Media = accumulate(i.begin(), i.end(), 0) / i.num_voxels(i.size());

        }
    private:
        T Minimum_;
        T Maximum_;
        T Media;

    };
}