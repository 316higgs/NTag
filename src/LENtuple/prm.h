//============
//
// LIBRARIES
//
//============
#ifndef PRM_H_
#define PRM_H_

#include <vector>
#include <string>
#include <sstream>
#include "/disk02/usr6/fiacob/ncqeana/tools/lentuple/T2KLowE.h"
#include "FeatureVector.h"

// SKLIBS
#include <tqrealroot.h>
#include <loweroot.h>
#include <skheadC.h>
#include <skparmC.h>
#include <sktqC.h>
#include <skbadcC.h>
#include <geotnkC.h>
#include <geopmtC.h>
#include "ConnectionTable.h"
#include <skwaterlenC.h>
#include <DataDefinition.h>
#include <Reformatter.h>
// ROOTLIBS
#include <TROOT.h>
#include <TVirtualFitter.h>
#include <TChain.h>
#include <TLine.h>
#include <TLatex.h>
#include <TMinuit.h>
#include <TMath.h>
#include "TStyle.h"
#include <TCanvas.h>
#include <TFile.h>
#include <TApplication.h>
#include <TNtuple.h>
#include <TH1.h>
#include <THStack.h>
#include <TH2F.h>
#include <TFrame.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TBranch.h>
#include <TLegend.h>
#include <TF1.h>
#include <TF2.h>
#include <TSystem.h>
//#include <tqrealroot.h>
////#include <loweroot.h>
#include <TRandom.h>
#include <TVector3.h>
#include <TRandom1.h>
#include <TMultiLayerPerceptron.h>
#include <TMLPAnalyzer.h>
#include <TGaxis.h>
#include <TGraphErrors.h>
#include <TTimeStamp.h>
#include <TCut.h>
#include <TPaveText.h>
#include <TArrow.h>
#include <TObject.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>

extern "C" void trginfo_(float*);



//=========================
//
// PRIMARY SELECTION CUTS
//
//=========================

typedef struct {
    int   icabiz;
    float tiskz;
    float tau;

    char  sb;
    int   flag_bonsvtx;
} CableTimeHit;

typedef struct {
    CableTimeHit *bgn;  // First
    CableTimeHit *end;  // Past-the-end
} WindowBounds;

bool compare_cable( const CableTimeHit &x, const CableTimeHit &y );
bool compare_time( const CableTimeHit &x, const CableTimeHit &y );

void fill_ct( const sktqz_common &insktqz, char *sbvec, CableTimeHit *ct, int &ctsize );
void fill_ct_nosbi( const sktqz_common &insktqz, const combad_common &incombad, CableTimeHit *ct, int &ctsize );
//void merge_sheaft_ambe( const sktqz_common &shesktqz, const combad_common &shecombad, const int sheit0sk, sktqz_common &aftsktqz, const combad_common &aftcombad, const int aftit0sk );
void fill_ct_she_nosbi( const sktqz_common &insktqz, const combad_common &incombad, CableTimeHit *ct, int &ctsize );
void fill_ct_sheaft_nosbi( const sktqz_common &insktqz, const combad_common &incombad, float last_she, int sheit0sk, int aftit0sk, CableTimeHit *ct, int &ctsize );
void fill_ct_rndmwidetrg_nosbi( const sktqz_common &insktqz, const combad_common &incombad, CableTimeHit *ct, int &ctsize );





/*
 * RBN = Repetitive Burst Noise
 * Considering one PMT, if two consecutive hits
 * have time difference < RBN_TIME_WIDTH
 * then are considered RBN, and are cut
*/
void cut_RBN( CableTimeHit *ct, int &ctsize );
void fill_sort_tau( CableTimeHit *ct, int ctsize, float *vtx );
void find_n10   ( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize );
void cut_n200   ( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize );
void cut_doublet( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize );

void searchCandidates( CableTimeHit *ct, int ctsize, float *pvx, WindowBounds *wb, int &wbsize, int *n200vec ); //CPM 190121 added n200 

void surround_n10bonsvtx( CableTimeHit *ct_bonsvtx, int ctbsize, WindowBounds n10bvx, CableTimeHit *surround, int &surroundsize );


//===================================
//
// PRIMARY SELECTION FEATURE VECTOR
//
//===================================
struct Hit {
    float t;
    float tau;
    float stau;  // Shifted tau: tau[i] - tau[0]
    float tdelta;  // Tau delta[i] = tau[i+1] - tau[i]
    int cable;
    float co[6];  // PMT position x, y, z, rho, zenith, azimuth with respect to SK center
    float vco[6];  // PMT position x, y, z, rho, zenith, azimuth with respect to vertex center
    float nvco[6];  // Normalized PMT position x, y, z, rho, zenith, azimuth with respect to vertex center
    float spheremean_dist;
    char sb;
};



struct Window {
    // Initialization functions
    void init( CableTimeHit *first, CableTimeHit *last, float *vtx );
	void init_variant( vector<Int_t> &fCab, vector<Float_t> &fTim, vector<Float_t> &fTau, int _nhit, float *_vtx );
    void init_spheremean();
    void init_distancevector();
    void init_distancematrix();

    // Basic quantities
    float tauwidth;
    int nhit;
    float vtx[6];
    Hit hit[100];
    
    // Derived quantities
    float spheremean[6];
    bool spheremeanflag;
    float dmtx[100][100];
    int amtx[100][100];
};

/*
typedef struct {
    int nhit;
    float d0, d1, d2, d3, d4, d5;  // distances from spheremean
    float dmean, drms, ddiff;
    float vtx0, vtx1, vtx2, vtxval;
    float truevtxdist;
    float sd_bestgradnorm;
    float spheremeannorm;
    float taurms_stat0, taurms_stat1, taurms_stat2, taurms_stat3;  // mean, rms, skewness, kurtosis
    float taurms_stat4, taurms_stat5, taurms_stat6, taurms_stat7;  // 1st quartile, median, 3rd quartile, inter-quartile range
    float taurms_stat8, taurms_stat9, taurms_stat10, taurms_stat11;  // minx, miny, minz, val
} FeatureVector;
*/

struct Fitter {
    //void init_vtx( const Window &w, float *vtx );
    void sample_taurms( const Window &w, const float radius, const float semiheight, int nsample, float *stat );  // both in cm
    //int nhit;
    //float guesst[100];
    //float guessvtx[3];

    float compute_taurms( const Window &w, float *vtx );

    // Concentric cube fitter
    struct FuncPoint { float vtx[3]; float val; float seltaurms; float seldensity; };
    void concentric_cube_fitter( const Window &w, const float *inivtx, const float iniside, int ncycle, float cyclefactor );
    void refreshwnd_concentric_cube_fitter( CableTimeHit *ctbvx, int ctsize, WindowBounds wndbnd, const float *inivtx, const float iniside, int ncycle, float cyclefactor );

    FuncPoint minimum;
    int flag;
};

void fvfill_init();
void fvfill_end();
int fill_feature_vector( CableTimeHit *ct_bonsvtx, int ctsize, WindowBounds wb, float *bonsvtx, FeatureVector &fv );
Int_t computeVariables( CableTimeHit *ct_bonsvtx, int ctsize, WindowBounds wb, float *bonsvtx, FeatureVector &fv );

 
/*
 * Return label for supervised learning
 * return true  = SIGNAL
 * return false = BACKGROUND
*/
//int candidate_is_signal( T2KLowE &t2kle, WindowBounds wb, float &t0, float &trgofst, float &tds );
int candidate_is_signal( int nscndprt, int iprtscnd[], int lmecscnd[], float tscnd[], float trgofst, float pscnd[][3], WindowBounds wb, float &t0, float &tds );
int candidate_trigger_info( float trgofst, WindowBounds wb, float &t0, float &tds ); 










#endif  // PRM_H_
