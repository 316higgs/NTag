#include <iostream>
#include "SteepestDescent.h"
#include <cmath>

using namespace std;

float parabola( float *x ) { return x[0]*x[0] + x[1]*x[1]; }
bool interval( float *x ) { return sqrt(x[0]*x[0]+x[1]*x[1]) < 5.0; }


int main() {
    cerr << "Start minimization" << endl;
    SteepestDescent sd;

    const int ndim = 2;
    sd.init_dimension( ndim );  // 1-dimensional
    sd.init_func_constr( parabola, interval );

    float guessx[ndim] = { -1.0, -1.0 };
    float step = 0.01;
    int maxmin = +1;  // minimalize
    sd.extremalize( guessx, step, maxmin );

    for ( int i = 0; i < ndim; ++i ) cerr << sd.xmin[i] << " ";
    cerr << sd.funcmin << endl;
    return 0;
}
