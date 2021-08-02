#ifndef _STEEPEST_DESCENT_H__
#define _STEEPEST_DESCENT_H__

class SteepestDescent {
public:
    int ndim;

    // External usage
    SteepestDescent();
    ~SteepestDescent();
    void init_dimension( int ndim_ );
    void init_func_constr( float (*f)(float*), bool (*is_id)(float*) );  // point to function and constraints
    void extremalize( const float *guessx, float step, int maxmin );
    void extremalize_lim( const float *guessx, float step, int maxmin, int limnstep );  // maxmin = +1 maximalize   maxmin = -1 minimalize
    void compute_bestgradnorm( float step ); 
    //--- RESULTS ---
    float *xmin;
    float funcmin;

    // Internal usage
    float *x0;  // Current guess
    float *x1;  // Next guess
    
    float (*func)( float *x );  // function to minimize
    bool (*is_indomain)( float *x );  // constraints on variables
   
    void compute_gradient();  // compute grad and normgrad
    float h, h2;
    float *grad, *normgrad;
    float norm;
    float *fwd, *bwd;

    int nstep;
};

#endif  // _STEEPEST_DESCENT_H__
