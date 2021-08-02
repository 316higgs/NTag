#ifndef _STEEPEST_DESCENT_H__
#define _STEEPEST_DESCENT_H__

class SteepestDescent {
public:
    int ndim;

    // External usage
    SteepestDescent();
    ~SteepestDescent();
    void init_dimension( int ndim_ );
    void init_func_constr( double (*f)(double*), bool (*is_id)(double*) );  // point to function and constraints
    void extremalize( const double *guessx, double step, int maxmin );  // maxmin = +1 maximalize   maxmin = -1 minimalize
    
    //--- RESULTS ---
    double *xmin;
    double funcmin;

    // Internal usage
    double *x0;  // Current guess
    double *x1;  // Next guess
    
    double (*func)( double *x );  // function to minimize
    bool (*is_indomain)( double *x );  // constraints on variables
   
    void compute_gradient();  // compute grad and normgrad
    double h, h2;
    double *grad, *normgrad;
    double *fwd, *bwd;
};

#endif  // _STEEPEST_DESCENT_H__
