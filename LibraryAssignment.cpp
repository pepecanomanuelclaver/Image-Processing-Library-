/*
José Luis Cano-Manuel Claver
Student number: 7272626
Simple Calculator: Delivered on november 11th for PMI @ Universiteit Utrecht
*/

#include "C:\Users\pepec\Desktop\PMI\Assingment 4\std_lib_facilities.h"
#include"ImageIOBase.h"
#include"ImageIOFactory.h"
#include"ThersholdFilter.h"
#include"Statistic.h"
#include"MaskFilter.h"
#include"ConvolutionFilter.h"
#include"LaplaceFilter.h"
#include"SumImages.h"
#pragma warning(default:4996)
using namespace librarypepe;

int main() {
    try {
        cout << "\nWelcome to the Image Processing Library!";
        cout << "\nYour favourite library :)";
        cout << "\nDeveloped by Pepe Cano-Manuel Claver for the course PMI";
        cout << "\n";
        cout << "\nHere, you have to select first the input of choice. ";
        cout << "\nThen, you can filter that image with different filters.";
        cout << "\nAnswer please in lower case. ";
        cout << "\nThe filter options are:";
        cout << "\n";
        cout << "\nlaplacian: The Laplacian is a 2-D isotropic measure of the 2nd spatial derivative of an image. ";
        cout << "\nstatistic: This filter shows the maximum, the minimum, and the media value of the introduced image.";
        cout << "\nconvolution: The convolution filter does the media from all the surrouding pixels within the indicated radius. ";
        cout << "\nthreshold: Set to zero the values bellow the selected ones.";
        cout << "\n";
        cout << "\nif you want to exit, just introduce other than the options provided, or a different to yes or no. ";
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\n______________________________________________________________________________________";

        cout << "\nPlease enter a PIP or MHD filename: " << endl;
        string filename;
        cin >> filename;

        unique_ptr <ImageIOBase> io = ImageIOFactory::getIO(filename);
        auto image = io->read();

        cout << "\nWhich filter do you want to apply?: ";
        string Answer;
        cin >> Answer;


        if (Answer == "static")
        {
            StaticFilter f;
            f.setInput(image);
            f.update();
            short max = f.getMax();
            short min = f.getMin();
            short media = f.getMedia();
            cout << "\nThe statistics are: " << "\nThe maximum is: " << max << "\nThe minimum is: " << min << "\nThe media value is: " << media << "\n";
        }
        else if (Answer == "threshold") {
            ThresholdImageFilter g;
            g.setInput(image);
            g.setThreshold(400);                        // Introduce the threshold value. 
            g.update();
            auto mask = g.getOutput();
            cout << "\nThe mask has been generated, do you want to apply it to the original image?";
            string answer2;
            cin >> answer2;
            if (answer2 == "yes")
            {
                MaskFilter m;
                m.setInput(image);
                m.setInputMask(mask);
                m.update();
                auto final = m.getOutput();
                unique_ptr <ImageIOBase> ip = ImageIOFactory::getIO(filename);
                ip->write(final);
            }
            else if (answer2 == "no") {
                cout << "\nThe mask is saved as an output.";
                unique_ptr <ImageIOBase> ip = ImageIOFactory::getIO(filename);
                ip->write(mask);
            }
            else {
                cout << "\nThe program is finished :) See you soon!";
            }
        }
        else if (Answer == "convolution") {
            cout << "\nIt may take a bit...";
            ConvolutionFilter c;
            c.setInput(image);
            c.setRadio(2);                      // Introduce the radius that you prefer. 
            c.update();
            auto convoluted_image = io->read();
            convoluted_image = c.getOutput();
            unique_ptr <ImageIOBase> ip = ImageIOFactory::getIO(filename);
            ip->write(convoluted_image);
        }
        else if (Answer == "laplacian") {
            LaplaceFilter bonus;
            bonus.setInput(image);
            bonus.update();
            auto bonus_out = bonus.getOutput();

            string answer3;
            cout << "\nDo you want to add the mask to the image? ";
            cin >> answer3;

            if (answer3 == "yes")
            {
                SumImages bonus_join;
                bonus_join.setInput(image);
                bonus_join.setInputImage2(bonus_out);
                bonus_join.update();
                auto bonus_join_out = bonus_join.getOutput();
                unique_ptr <ImageIOBase> ip = ImageIOFactory::getIO(filename);
                ip->write(bonus_join_out);
            }
            else if (answer3 == "no") {
                unique_ptr <ImageIOBase> ip = ImageIOFactory::getIO(filename);
                ip->write(bonus_out);
                cout << "\nThe laplacian mask is saved. ";
            }
            else {
                cout << "\nThe program is finished :) See you soon!";
            }
        }
        else {
            cout << "\nThe program is finished :) See you soon!";
        }
    }
    
    catch (exception& e) {
        cerr << "Exception: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cerr << "exception\n";
        return 2;
    }
}