#include "SteepestDescent.h"
#include <cmath>
#include <cstdio>

using namespace std;

SteepestDescent::SteepestDescent() {}
SteepestDescent::~SteepestDescent() {}

void SteepestDescent::init_dimension( int ndim_ ) {
    ndim = ndim_;

    x0 = new float[ndim];
    x1 = new float[ndim];
    xmin = new float[ndim];

    grad = new float[ndim];
    normgrad = new float[ndim];

    fwd = new float[ndim];
    bwd = new float[ndim];
}

void SteepestDescent::init_func_constr( float (*f)(float*), bool (*is_id)(float*) ) {
    func = f;
    is_indomain = is_id;
}

// maxmin = 1 ---> Maximalize
// maxmin = -1 ---> Minimalize
bool less_than( const float &a, const float &b ) { return a < b; }
bool more_than( const float &a, const float &b ) { return a > b; }

void SteepestDescent::extremalize_lim( const float *guessx, float step, int maxmin, int limnstep ) {
    nstep = 0;
    // Decide stop condition and step, for correct direction
    bool (*stop)( const float&, const float& );
    if       ( maxmin == 1 ) { stop = less_than; step = +step; }  // maximize
    else if ( maxmin == -1 ) { stop = more_than; step = -step; }  // minimize

    // Decide h and h/2 for gradient
    h = abs( step ) / sqrt( (float)ndim );
    h2 = h / 2.;

    // Put initial guess
    for ( int i = 0; i < ndim; ++i ) x0[i] = guessx[i];

    while ( is_indomain( x0 ) && nstep < limnstep ) {  // out-of-bound stops search and gives x0 as minimum
        ++nstep;
        compute_gradient();  // at x0, computes grad and normgrad (normalized)
        for ( int i = 0; i < ndim; ++i ) x1[i] = x0[i] + step*normgrad[i];  // compute next guess
        if ( stop( func( x1 ), func( x0 ) ) ) break;  // arrived, x0 is minimum
        for ( int i = 0; i < ndim; ++i ) x0[i] = x1[i];
    }

    for ( int i = 0; i < ndim; ++i ) xmin[i] = x0[i];
    funcmin = func( xmin );

    //printf( "extremalized %d\n", nstep );
}


void SteepestDescent::extremalize( const float *guessx, float step, int maxmin ) {
    nstep = 0;
    // Decide stop condition and step, for correct direction
    bool (*stop)( const float&, const float& );
    if       ( maxmin == 1 ) { stop = less_than; step = +step; }  // maximize
    else if ( maxmin == -1 ) { stop = more_than; step = -step; }  // minimize

    // Decide h and h/2 for gradient
    h = abs( step ) / sqrt( (float)ndim );
    h2 = h / 2.;

    // Put initial guess
    for ( int i = 0; i < ndim; ++i ) x0[i] = guessx[i];

    while ( is_indomain( x0 ) ) {  // out-of-bound stops search and gives x0 as minimum
        ++nstep;
        compute_gradient();  // at x0, computes grad and normgrad (normalized)
        for ( int i = 0; i < ndim; ++i ) x1[i] = x0[i] + step*normgrad[i];  // compute next guess
        if ( stop( func( x1 ), func( x0 ) ) ) break;  // arrived, x0 is minimum
        for ( int i = 0; i < ndim; ++i ) x0[i] = x1[i];
    }

    for ( int i = 0; i < ndim; ++i ) xmin[i] = x0[i];
    funcmin = func( xmin );

    //printf( "extremalized %d\n", nstep );
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

    norm = 0.;
    for ( int i = 0; i < ndim; ++i ) norm += grad[i]*grad[i];
    norm = sqrt( norm );

    for ( int i = 0; i < ndim; ++i ) normgrad[i] = grad[i] / norm;
}




void SteepestDescent::compute_bestgradnorm( float step ) {
    // Get minimum
    for ( int i = 0; i < ndim; ++i ) x0[i] = xmin[i];

    // Compute gradient
    h = abs( step ) / sqrt( (float)ndim );
    h2 = h / 2.;
    compute_gradient();

    // Go uphill one step
    for ( int i = 0; i < ndim; ++i ) x1[i] = x0[i] + step*normgrad[i];

    // Compute gradient again
    compute_gradient();

    // Read norm from outside!!!
}
