_______________ LIBRARY ASSINGMENT : JOSE LUIS (PEPE) CANO-MANUEL CLAVER with STUDENT NUMBER: 7272626 _______________

The library provided can be used to processed medical images, either .pip or .mhd format files, using certain filters. 
The file is composed to 13 headers, composed of mainly the main (LibraryAssignment.cpp), the ones used to do the 
object-oriented programming algorithm (Image.h, ImageFilter.h, ImageIOBase.h, ImageIOFactory.h), and the headers des-
cribing the filters used (LaplaceFilter.h, ThresholdFilter.h, Statistic.h, ConvolutionFilter.h) and two functions that 
fusion images, either by multiplication (SumImages.h) or by convolution one image over the other (MaskFilter.h). 

The filter used are the following:

- Laplacian:
The Laplacian is a 2-D isotropic measure of the 2nd spatial derivative of an image. 
the Laplacian of an image highlights regions of rapid intensity change and is therefore
often used for edge detection (see zero crossing edge detectors). The Laplacian is often
applied to an image that has first been smoothed with something approximating a Gaussian
smoothing filter in order to reduce its sensitivity to noise, and hence the two variants 
will be described together here. The operator normally takes a single graylevel image as 
input and produces another graylevel image as output.
This filter outputs the mask, to join it with the original image you would have to call
the SumImage.h.

- Statistic:
This filter shows the maximum, the minimum, and the media value of the introduced image. 

- Convolution:
The convolution filter does the media from all the surrouding pixels within the indica-
ted radius. 

- Threshold:
Set to zero the values bellow the selected ones. The filter outputs the mask. The 
MaskFilter.h needs to be called to join the mask with the desired input image. 

Through the code some improvement has been assesed: all is set to be a unique pointer to prevent 
memory leaks in the program, the main function is set to be user-friendly, the image is stored in
a object-oriented programmed image object, the functions of each assignment is divided into 
separate headers etc. 
