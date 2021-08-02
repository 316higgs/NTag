#include "runsummanager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>

#define dbg( x ) std::cout << "DBG " << x << '\n'
#define dump( x ) std::cout << x << '\n'
#define watch( x ) std::cout << (#x) << " = " << x << '\n'

using namespace std;

void read_runsum( string rsfilename ) {
    ifstream fin;
    fin.open( rsfilename.c_str() );
    if ( !fin.good() ) {
        cerr << "runsum not found, exiting program" << endl;
        exit( EXIT_FAILURE );
    }
    RSTuple inp;
    runsum = new RSTuple[15000];
    runsumsize = 0;
    while (fin >> inp.nrun >> inp.startdate >> inp.starttime >> inp.stopdate >> inp.stoptime >> inp.runhours >> inp.deadratio >> inp.ntrgevt >> inp.darkrate) {
        runsum[runsumsize] = inp;
        ++runsumsize;
    }
    fin.close();

    // DBG
    watch( runsumsize );
}


bool nruncomp( const RSTuple &t1, const RSTuple &t2  ) { return t1.nrun < t2.nrun; }

void runsum_gettuple( int nrun, RSTuple &tpl ) {
    RSTuple dum;
    dum.nrun = nrun;
    tpl = *lower_bound( runsum, runsum + runsumsize, dum, nruncomp );
}

void kill_runsum() {
    delete [] runsum;
}
