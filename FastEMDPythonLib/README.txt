Wrapper by Gavin Smith (gavin.smith@nottingham.ac.uk)

For the original readme for the code being wrapped see: README_orig.txt

WARNING: Functionality is limited. 1D histograms assumed. Ground distance is fixed to the abs( diff in vector indices ).

Wrapper: python_fast_emd.cpp

How to compile: Place python_fast_emd.cpp in the same folder as the files from: 
http://www.seas.upenn.edu/~ofirpele/FastEMD/code/
Tested version from website: FastEMD-3.zip  (17.5.2012)

Compile by (Ubuntu 12.10):
g++ python_fast_emd.cpp -o fastemd.so -shared -fPIC -I/usr/include/python2.7 -lboost_python -lpython2.7

Use: 
place resulting fastemd.so in python directory. A simple test.py is:

#########################
import fastemd

if __name__ == '__main__':
    emd = fastemd.EMDFast(3)
    
    a = [0,2,0]
    b = [1,0,0]
    
    print emd.dist(a,b,10)
##########################