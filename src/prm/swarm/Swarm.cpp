#include "Swarm.h"
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>

#define watch( x ) std::cerr << (#x) << " = " << x << '\n'
#define dbg( x ) std::cerr << "DBG " << x << '\n'
#define dump( x ) std::cerr << x << '\n'

Swarm::Swarm( bool (*domfcn_)( float *x ), void (*sampler_)( float *x ) ) {
    domfcn = domfcn_;
    sampler = sampler_;
    sd.init_dimension( 3 );
}

Swarm::~Swarm() {}

void Swarm::init_objfcn( float (*objfcn_)( float *x ) ) {
    objfcn = objfcn_;
    sd.init_func_constr( objfcn, domfcn );
}

void Swarm::cast( int noptimization, float step, int maxmin ) {
    nopt = noptimization;
    
    for ( int i = 0; i < nopt; ++i ) {
        sampler( opt[i].x );
        sd.extremalize( opt[i].x, step, maxmin );
        for ( int j = 0; j < 3; ++j ) opt[i].x[j] = sd.xmin[j];
        opt[i].f = sd.funcmin;
        //printf( "%d %f %f %f %f\n", i, opt[i].x[0], opt[i].x[1], opt[i].x[2], opt[i].f );
    }
}



void Swarm::compute_stddevopt() {
    // Compute mean
    meanopt.x[0] = meanopt.x[1] = meanopt.x[2] = meanopt.f = 0.;
    for ( int i = 0; i < nopt; ++i ) {
        for ( int j = 0; j < 3; ++j ) meanopt.x[j] += opt[i].x[j] / (float) nopt;
        meanopt.f += opt[i].f / (float) nopt;
    }

    // Compute stddev
    stddevopt.x[0] = stddevopt.x[1] = stddevopt.x[2] = stddevopt.f = 0.;
    for ( int i = 0; i < nopt; ++i ) {
        for ( int j = 0; j < 3; ++j ) stddevopt.x[j] += 1./((float)(nopt-1))*( opt[i].x[j]-meanopt.x[j] )*( opt[i].x[j]-meanopt.x[j] );
        stddevopt.f += 1./((float)(nopt-1))*( opt[i].f-meanopt.f )*( opt[i].f-meanopt.f );
    }
    for ( int j = 0; j < 3; ++j ) {
        stddevopt.x[j] = sqrt( stddevopt.x[j] );
    }
    stddevopt.f = sqrt( stddevopt.f );
}

bool compare_x0( const PointFunc3D &p1, const PointFunc3D &p2 ) { return p1.x[0] < p2.x[0]; }
bool compare_x1( const PointFunc3D &p1, const PointFunc3D &p2 ) { return p1.x[1] < p2.x[1]; }
bool compare_x2( const PointFunc3D &p1, const PointFunc3D &p2 ) { return p1.x[2] < p2.x[2]; }
bool compare_f ( const PointFunc3D &p1, const PointFunc3D &p2 ) { return p1.f    < p2.f; }

void Swarm::compute_maxminrangeopt() {
    minopt.x[0] = std::min_element( opt, opt+nopt, compare_x0 )->x[0];
    minopt.x[1] = std::min_element( opt, opt+nopt, compare_x1 )->x[1];
    minopt.x[2] = std::min_element( opt, opt+nopt, compare_x2 )->x[2];
    minopt.f    = std::min_element( opt, opt+nopt, compare_f )->f;

    maxopt.x[0] = std::max_element( opt, opt+nopt, compare_x0 )->x[0];
    maxopt.x[1] = std::max_element( opt, opt+nopt, compare_x1 )->x[1];
    maxopt.x[2] = std::max_element( opt, opt+nopt, compare_x2 )->x[2];
    maxopt.f    = std::max_element( opt, opt+nopt, compare_f )->f;

    for ( int j = 0; j < 3; ++j ) rangeopt.x[j] = maxopt.x[j] - minopt.x[j];
    rangeopt.f = maxopt.f - minopt.f;
}








void Swarm::print_stat( const char *fmt ) {
    printf( "MEANOPT\n" );
    for ( int i = 0; i < 3; ++i ) { printf( fmt, meanopt.x[i] ); printf( " " ); }
    printf( fmt, meanopt.f );
    printf( "\n" );

    printf( "STDDEVOPT\n" );
    for ( int i = 0; i < 3; ++i ) { printf( fmt, stddevopt.x[i] ); printf( " " ); }
    printf( fmt, stddevopt.f );
    printf( "\n" );

    printf( "MINOPT\n" );
    for ( int i = 0; i < 3; ++i ) { printf( fmt, minopt.x[i] ); printf( " " ); }
    printf( fmt, minopt.f );
    printf( "\n" );

    printf( "MAXOPT\n" );
    for ( int i = 0; i < 3; ++i ) { printf( fmt, maxopt.x[i] ); printf( " " ); }
    printf( fmt, maxopt.f );
    printf( "\n" );

    printf( "RANGEOPT\n" );
    for ( int i = 0; i < 3; ++i ) { printf( fmt, rangeopt.x[i] ); printf( " " ); }
    printf( fmt, rangeopt.f );
    printf( "\n" );
}

void Swarm::get_bestvtx( float *bestvtx ) {
    PointFunc3D b = *std::min_element( opt, opt+nopt, compare_f );
    for ( int i = 0; i < 3; ++i ) bestvtx[i] = b.x[i];
}

void Swarm::get_closesttorefvtx( float *ref, float *closest ) {
    PointFunc3D cl;
    float cldist;

    float refdist = 0.;
    for ( int i = 0; i < 3; ++i ) refdist += ( ref[i] - opt[0].x[i] ) * ( ref[i] - opt[0].x[i] );
    cl = opt[0];
    cldist = refdist;

    for ( int i = 1; i < nopt; ++i ) {
        refdist = 0.;
        for ( int j = 0; j < 3; ++j ) refdist += ( ref[j] - opt[i].x[j] ) * ( ref[j] - opt[i].x[j] );
        if ( refdist < cldist ) cl = opt[i];
    }

    for ( int j = 0; j < 3; ++j ) closest[j] = cl.x[j];
}


void Swarm::compute_bestgradnorm( float step ) {
    // Take best minimizer
    PointFunc3D best = *std::min_element( opt, opt+nopt, compare_f );
    //printf( "Best %f %f %f %f\n", best.x[0], best.x[1], best.x[2], best.f ); // DBG
    
    // Go uphill one step
    float grad[3], normgrad[3], norm;
    compute_gradient( best, step, grad, normgrad, norm );
    //printf( "grad %f %f %f\n", grad[0], grad[1], grad[2] );
    //printf( "normgrad %f %f %f\n", normgrad[0], normgrad[1], normgrad[2] );
    //printf( "normmmm %f\n", norm );
    for ( int i = 0; i < 3; ++i ) best.x[i] += step*normgrad[i];
    //printf( "Uphill %f %f %f\n", best.x[0], best.x[1], best.x[2] );
    
    // Compute gradient again
    compute_gradient( best, step, grad, normgrad, norm );
    //printf( "norm %f\n", norm );
    bestgradnorm = norm;
}



void Swarm::compute_gradient( PointFunc3D &x0, float step, float *grad, float *normgrad, float &norm ) {
    float h = step / sqrt( 3. );
    float h2 = h / 2.;
    float fwd[3], bwd[3];
    //std::cerr << "step h h2 = " << step << " " << h << " " << h2 << std::endl;

    for ( int i = 0; i < 3; ++i ) {
        for ( int j = 0; j < 3; ++j ) {
            fwd[j] = ( j==i ? x0.x[j]+h2 : x0.x[j] );
            bwd[j] = ( j==i ? x0.x[j]-h2 : x0.x[j] );
        }
        grad[i] = ( objfcn( fwd ) - objfcn( bwd ) ) / h;
    }

    //printf( "fwd %f %f %f\n", fwd[0], fwd[1], fwd[2] );
    //printf( "bwd %f %f %f\n", bwd[0], bwd[1], bwd[2] );
    //printf( "fb %f %f\n", objfcn( fwd ), objfcn( bwd ) );

    norm = 0.;
    for ( int i = 0; i < 3; ++i ) norm += grad[i]*grad[i];
    norm = sqrt( norm );
    for ( int i = 0; i < 3; ++i ) normgrad[i] = grad[i] / norm;
}






