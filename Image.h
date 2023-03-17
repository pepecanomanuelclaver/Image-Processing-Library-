#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageIOBase.h"
#include "algorithm"

namespace librarypepe {
	static constexpr int N_DIM{ 5 };

	class Image
	{
	public:
		// Internally used data types 
		typedef short T;
		typedef std::array<int, N_DIM> dimension;              // typedef std::array<int, N_DIM> dimension;  
		Image() : _dimensions({ 0,0,0,0,0 }), _data{ 0 } {};

		// STL container and iterator typedefs 
		typedef T         value_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T& reference;
		typedef const T& const_reference;

		int num_voxels(dimension d) const {        
			return d[0] * d[1] * d[2] * d[3] * d[4];
		} 

		// Constructors,  and destructor 
		Image(dimension d): _data(new T[num_voxels(d)]), _dimensions{d} { 
			for (int i = 0; i < num_voxels(d); ++i)
				_data[i] = 0;
		};  

		Image(const Image& arg)													           //Copy constructor 			
			:_dimensions{ arg._dimensions }, _data{ new T[arg.num_voxels(_dimensions)] }   // allocate elements, then initialize them by copying
		{
			copy(arg.begin(), arg.end(), _data); 
		};

		Image& operator=(const Image& a)												   //Copy assignment 
		{
			T* p = new T[a.num_voxels(_dimensions)];								       // allocate new space
			copy(a.begin(), a.end(), p);												   // copy elements
			delete[] _data;																   // deallocate old space
			_data = p;																	   // now we can reset elem
			_dimensions = a._dimensions;
			return *this;																   // return a self-reference 
		}

		Image(Image&& arg) noexcept : _dimensions{ arg._dimensions }, _data{ arg._data } { //Move constructor 
			arg._dimensions = { 0,0,0,0,0 };
			arg._data = nullptr;
		};

		Image& operator=(Image&& a) noexcept											   // Move assignment
		{
			delete[] _data;							                                       // deallocate old space
			_data = a._data;														       // copy a’s elem and sz
			_dimensions = a._dimensions;
			a._data = nullptr;															   // make a the empty vector
			a._dimensions = { 0,0,0,0,0 };
			return *this;																   // return a self-reference 
		}

		virtual ~Image() {																   // Destructor 
			delete[] _data;
			_data = nullptr;
		};

		iterator begin() { return _data; }; 
		iterator end() { 
		return _data + num_voxels(_dimensions); };											// Points to the last voxel plus one more. 
		const_iterator begin() const { return _data; };
		const_iterator end() const {
			return (_data + num_voxels(_dimensions));
		};

		// Size and resize 
		dimension size() const { return _dimensions; };										// The dimension object 
		unsigned int dim(unsigned int d) const { return _dimensions[d]; };					// Get the size of a dimension 
		unsigned int nr_dims() const { sizeof(_dimensions)/sizeof(_dimensions[0]); };		// Size of return the number of bytes  
		void resize(const dimension& d) {													// Resize this image 
			delete[] _data;
			_dimensions = d;
			_data = new T[num_voxels(_dimensions)];
																							// create an image with the new size 
		};        

		// Pixel value lookup, should support out-of-image coordinates by clamping to 0..dim 
		value_type operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) const {// Provide a const operator() for lookup of pixel values
			value_type value = _data[x,y,z,c,t ];

		// Define the cases in which a point out of the image is chosen. For that, it will be assigned the correspondant border value. 
			if (x > (dim(0)-1)) {
				x = (dim(0)-1);
			}
			if (x < 0) {
				x = 0;
			}
			if (y > (dim(1)-1)) {
				y = (dim(1)-1);
			}
			if (y < 0) {
				y = 0;
			}
			if (z > (dim(2)-1)) {
				z = (dim(2)-1);
			}
			if (z < 0) {
				z = 0;
			}
			if (c > (dim(3) - 1)) {
				c = (dim(3) - 1);
			}
			if (c < 0) {
				c = 0;
			}
			if (t > (dim(4) - 1)) {
				t = (dim(4) - 1);
			}
			if (t < 0) {
				t = 0;
			}

			return _data[(t* dim(3)* dim(0)* dim(1)* dim(2)) + (c * dim(0) * dim(1) * dim(2)) + (z * dim(0) * dim(1)) + (y * dim(0)) + x];
		}; 
		reference operator()(int x = 0, int y = 0, int z = 0, int c = 0, int t = 0) {		 // Non-const operator() that allows changing of the pixel values.
			return _data[t* dim(3)* dim(0)* dim(1)* dim(2) + (c * dim(0) * dim(1) * dim(2)) + (z * dim(0) * dim(1)) + (y * dim(0)) + x];
		};		  

	private:
		dimension _dimensions;
		T* _data;
	};


}