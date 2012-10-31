#include <boost/python.hpp>
#include <vector>
#include "emd_hat.hpp"

// Compile by:
// g++ python_fast_emd.cpp -o fastemd.so -shared -fPIC -I/usr/include/python2.7 -lboost_python -lpython2.7

using namespace boost::python;

struct EMDFast
{
    EMDFast( int histogram_length ) 
    {
		
		for( int i = 0; i < histogram_length; i++ )
		{
			std::vector<double> tmp;
			for( int j = 0; j < histogram_length; j++ )
			{
				tmp.push_back( abs(i-j) );
			}
			cost_matrix.push_back( tmp );
		}
	}
	
    double dist(boost::python::list& p_py, boost::python::list& q_py, int extra_mass_penalty) 
    { 
		
		bool print_cost_matrix = false;
		
		if( print_cost_matrix )
		{
			printf("\n");
			for( unsigned i = 0; i < cost_matrix.size(); ++i )
			{
				printf("\n");
				for( unsigned j = 0; j < cost_matrix.size(); ++j )
				{
						printf("%f ", cost_matrix[i][j]);
				}
			}
			printf("\n");
		}
		
		std::vector<double> p_c;
		std::vector<double> q_c;
		for (int i = 0; i < len(p_py); ++i)
		{
			p_c.push_back(boost::python::extract<double>(p_py[i]));
			q_c.push_back(boost::python::extract<double>(q_py[i]));
		}
		
		
		
		return emd_hat_gd_metric<double,NO_FLOW>()(p_c,q_c,cost_matrix,extra_mass_penalty);
    }
    std::vector< std::vector<double> > cost_matrix;
};


BOOST_PYTHON_MODULE(fastemd)
{
	
    class_<EMDFast>("EMDFast", init<int>())
        .def("dist", &EMDFast::dist)
    ;
}
