#ifndef RUNSUM_H__
#define RUNSUM_H__

#include <string>
#include <vector>

typedef struct {
    int nrun;
    std::string startdate;
    std::string starttime;
    std::string stopdate;
    std::string stoptime;
    float runhours;
    float deadratio;
    int ntrgevt;
    float darkrate;
} RSTuple;

RSTuple *runsum;
int runsumsize;

void read_runsum( std::string rsfilename ); 
void runsum_gettuple( int nrun, RSTuple &tpl ); 
void kill_runsum();

#endif  // RUNSUM_H__
