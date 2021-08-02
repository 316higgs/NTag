#include "SteepestDescent.h"
#include <cmath>

using namespace std;

SteepestDescent::SteepestDescent() {}
SteepestDescent::~SteepestDescent() {}

void SteepestDescent::init_dimension( int ndim_ ) {
    ndim = ndim_;

    x0 = new double[ndim];
    x1 = new double[ndim];
    xmin = new double[ndim];

    grad = new double[ndim];
    normgrad = new double[ndim];

    fwd = new double[ndim];
    bwd = new double[ndim];
}

void SteepestDescent::init_func_constr( double (*f)(double*), bool (*is_id)(double*) ) {
    func = f;
    is_indomain = is_id;
}

// maxmin = 1 ---> Maximalize
// maxmin = -1 ---> Minimalize
bool less_than( const double &a, const double &b ) { return a < b; }
bool more_than( const double &a, const double &b ) { return a > b; }

void SteepestDescent::extremalize( const double *guessx, double step, int maxmin ) {
    // Decide stop condition and step, for correct direction
    bool (*stop)( const double&, const double& );
    if       ( maxmin == 1 ) { stop = less_than; step = +step; }  // maximize
    else if ( maxmin == -1 ) { stop = more_than; step = -step; }  // minimize

    // Decide h and h/2 for gradient
    h = abs( step ) / sqrt( ndim );
    h2 = h / 2.;

    // Put initial guess
    for ( int i = 0; i < ndim; ++i ) x0[i] = guessx[i];

    while ( is_indomain( x0 ) ) {  // out-of-bound stops search and gives x0 as minimum
        compute_gradient();  // at x0, computes grad and normgrad (normalized)
        for ( int i = 0; i < ndim; ++i ) x1[i] = x0[i] + step*normgrad[i];  // compute next guess
        if ( stop( func( x1 ), func( x0 ) ) ) break;  // arrived, x0 is minimum
        for ( int i = 0; i < ndim; ++i ) x0[i] = x1[i];
    }

    for ( int i = 0; i < ndim; ++i ) xmin[i] = x0[i];
    funcmin = func( xmin ); 
}

// compute grad and normgrad at x0
void SteepestDescent::compute_gradient() {
    
    for ( int i = 0; i < ndim; ++i ) {
        for ( int j = 0; j < ndim; ++j ) {
            fwd[j] = ( j==i ? x0[j]+h2 : x0[j] );
            bwd[j] = ( j==i ? x0[j]-h2 : x0[j] );
        }
        grad[i] = ( func( fwd ) - func( bwd ) ) / h;
    }

    double norm = 0.;
    for ( int i = 0; i < ndim; ++i ) norm += grad[i]*grad[i];
    norm = sqrt( norm );

    for ( int i = 0; i < ndim; ++i ) normgrad[i] = grad[i] / norm;
}





