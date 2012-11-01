Python Wrapper for the Fast EMD code from http://www.seas.upenn.edu/~ofirpele/FastEMD/code/

For the original readme for the code being wrapped see: README_orig.txt

WARNING: Functionality is limited. 1D histograms assumed. Ground distance is fixed to the abs( diff in vector indices ).

Wrapper: python_fast_emd.cpp

How to compile: 
1. [Optional] Attempt to update the code being wrapped by placing python_fast_emd.cpp in the same folder as the files from: 
http://www.seas.upenn.edu/~ofirpele/FastEMD/code/
Do not need to do this if you are happy with the version included in this GIT: FastEMD-3.zip  (17.5.2012)

Compile by (Ubuntu 12.10):
g++ python_fast_emd.cpp -o fastemd.so -shared -fPIC -I/usr/include/python2.7 -lboost_python -lpython2.7

Use: 

To prevent the cost matrix be constructed each time it is constructed once within the C++ at object creation.
Future calls reuse the same cost matrix within the C++ code.

place resulting fastemd.so in python directory. A simple test.py is:

#########################
import fastemd

if __name__ == '__main__':
    emd = fastemd.EMDFast(3)
    
    a = [0,2,0]
    b = [1,0,0]
    
    extra_mass_penalty = -1 # Default, see emd_hat.hpp
    
    print emd.dist(a,b,extra_mass_penalty)
##########################

A more complex one to hide the object construction and use a python function as an atomic function, assuming the length of the passed vectors will
always be the same:

###########################

import fastemd

def fast_emd_dist( p, q ):

    # Using function attributes rather than making a class
    if not hasattr(fast_emd_dist, 'emd_obj'):
        fast_emd_dist.emd_obj = fastemd.EMDFast( len(p) )

    extra_mass_penalty = -1 # Default, see emd_hat.hpp
    
    return fast_emd_dist.emd_obj.dist(p,q,extra_mass_penalty)
    
if __name__ == '__main__':
    
    a = [0,2,0]
    b = [1,0,0]
    
    print fast_emd_dist( a, b )

###########################
