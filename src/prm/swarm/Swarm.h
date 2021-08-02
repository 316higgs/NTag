#ifndef _SWARM_H__
#define _SWARM_H__

#include "../steepdesc_min/SteepestDescent.h"


typedef struct {
    float x[3];
    float f;
} PointFunc3D;

class Swarm {
public:
    Swarm( bool (*domfcn_)( float *x ), void (*sampler_)( float *x ) );
    ~Swarm();

    void init_objfcn( float (*objfcn_)( float *x ) );
    void cast( int noptimization, float step, int maxmin );

    float (*objfcn) ( float *x );
    bool  (*domfcn) ( float *x );
    void  (*sampler)( float *x );
    
    int nopt;
    PointFunc3D opt[1000];
    SteepestDescent sd;

    void get_bestvtx( float *bestvtx );
    void get_closesttorefvtx( float *ref, float *closest );
    void sort_f();
    void compute_stddevopt();
    void compute_maxminrangeopt();
    void compute_bestgradnorm( float step );
    void compute_gradient( PointFunc3D &x0, float step, float *grad, float *normgrad, float &norm );
    void print_stat( const char *fmt );

    PointFunc3D meanopt;
    PointFunc3D stddevopt;
    PointFunc3D maxopt;
    PointFunc3D minopt;
    PointFunc3D rangeopt;
    float bestgradnorm;
};

#endif  // _SWARM_H__
