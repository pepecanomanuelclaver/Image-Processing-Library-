#pragma once
#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"Image.h"

namespace librarypepe {    
	class ImageIOBase {	
	public:
		ImageIOBase(const ImageIOBase&) = delete;			    // prevent copying
		ImageIOBase& operator=(const ImageIOBase&) = delete;
		virtual~ImageIOBase() {};
		virtual Image read() = 0;
		virtual void write(Image& img) = 0; 

	protected:
		ImageIOBase() {};
		ImageIOBase(const string& f) :filename(f) {};
		const string filename;
	};

	class PipImageIO : public ImageIOBase {
	public:
		PipImageIO(const string& f) :ImageIOBase(f) {};
		virtual Image read() override;						    // Read function overriden.
		virtual void write(Image& img) override;			    // Write function overriden.
	};

	class MhdImageIO : public ImageIOBase {
	public:
		MhdImageIO(const string& f) :ImageIOBase(f) {};
		virtual Image read() override;							// Read function overriden
		virtual void write(Image& img) override;				// Write function overriden.
	};
}






