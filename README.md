CS213BF14-edge-detection
========================

The C program edge_filter.c offers helper functions for image I/O.

Please fill in your edge detection code (line 109 - 114), but feel free
to change any other part of the program as well. On the VM, you should be able to build this program using the ARM cross-compiler, and execute it on VarEMU. 

The 5 input images are located under input/. These images are downloaded from http://www.eecs.qmul.ac.uk/~phao/CIP/Images/ .

The MATLAB script used to calcualte the quality metric can be found at script/computeFilterAccuract.m. Usage:
  <[neg, pos, zer]  = computeFilterAccuracy('path/to/original/image', '/path/to/filtered/image')>
where neg is the false negative rate, pos is the false positive rate, and zer is the rate of correctly detected edges.
