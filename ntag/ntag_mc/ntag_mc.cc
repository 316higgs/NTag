#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"
#include "TVirtualFitter.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TreeManager.h"


// These contain the common block variables 
#include <tqrealroot.h>
#include <loweroot.h>
#include <skheadC.h>
#include <skparmC.h>
#include <sktqC.h>
#include <skbadcC.h>
#include <geotnkC.h>
#include <geopmtC.h>
#include <skwaterlenC.h>
#include <DataDefinition.h>
#include <Reformatter.h>
#include <vcworkC.h>
#include <zbsC.h>
#include <zbsmc.h>
#include "vcworkC.h"
#include "vcvrtxC.h"
#include "neworkC.h"

#include "apmueC.h"

#include "effwallf.h"
#include "wallsk.h"
#include "typepdf.hh"

#include "skroot.h"

// 8jul2019
//#include "apflscndprtC.h"

// 1aug2019



#include <iostream>
#include <string>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "prm.h"
#include "ConnectionTable.h"

#define MAXSCNDPRT 500
#define watch( x ) std::cerr << (#x) << " = " << (x) << '\n'
#define dump( x ) std::cerr << (x) << '\n'
#define dbg( x ) std::cerr << "DBG = " << (x) << '\n'


using namespace std;

extern "C" void zbsinit_();
extern "C" void kzeclr_();

void createNTagTree( TTree *tree, FeatureVector &fv );

string ntag_fname_maker( string fname, string prefix ) {
    string ntag_fname = fname;
    int pos = ntag_fname.rfind( "/" );
    if ( pos == string::npos ) ntag_fname = prefix + ntag_fname; 
    else {
        ++pos;
        ntag_fname.insert( pos, prefix );
    }

    return ntag_fname;
}


bool is_inside_sk( const float *x ) {
    const float R = 1690.;
    const float H2 = 1810.;
    return ( x[0]*x[0]+x[1]*x[1] < R*R && abs( x[2] ) < H2 );
}

float euclidean_distance( float *x, float *y ) {    
    float dist = 0.;
    for ( int i = 0; i < 3; ++i ) dist += ( x[i] - y[i] ) * ( x[i] - y[i] );
    dist = sqrt( dist );

    return dist;
}



void apply_vtxshift_average( float *x ) {
    // Disclaimer before change position
    cout << "*** " << __func__ << " ***\n";
    cout << "Position before shift\n";
    printf( "%15.6f %15.6f %15.6f\n", x[0], x[1], x[2] );

    // Radius shift
    double rhosq, rho, phi;  // Polar coordinates
    phi = atan2( x[1], x[0] );  // azimuthal angle
    rhosq = x[0]*x[0] + x[1]*x[1];  // Compute squared radius
    rhosq += 1.78;  // Shift squared radius
    rho = sqrt( rhosq );  // Compute shifted radius
    x[0] = rho * cos( phi );
    x[1] = rho * sin( phi );

    // Z shift
    if ( x[2] > 0. ) {
        x[2] += 0.7;
    }
    else {
        x[2] += -0.27;
    }
    
    // Disclaimer after change position
    cout << "Position after shift\n";
    printf( "%15.6f %15.6f %15.6f\n\n", x[0], x[1], x[2] );
}



void apply_vtxshift_worstcase( float *x, float inout ) {
    // Disclaimer before change position
    cout << "*** " << __func__ << " ***\n";
    cout << "Position before shift\n";
    printf( "%15.6f %15.6f %15.6f\n", x[0], x[1], x[2] );

    // Radius shift
    double rho, phi;  // Polar coordinates
    phi = atan2( x[1], x[0] );  // azimuthal angle
    rho = sqrt( x[0]*x[0] + x[1]*x[1] );  // Compute radius
    rho += inout * 10.;  // Shift radius
    x[0] = rho * cos( phi );
    x[1] = rho * sin( phi );

    // Z shift
    if ( x[2] > 0. ) {
        x[2] += inout * 5.;
    }
    else {
        x[2] += -5. * inout;
    }
    
    // Disclaimer after change position
    cout << "Position after shift\n";
    printf( "%15.6f %15.6f %15.6f\n\n", x[0], x[1], x[2] );
}



typedef struct {
    // Particle info
    int index;
    int iprtscnd;
    float totalmom;
    int lmecscnd;
    int iprnttrk;
    int iorgprt;

    // Decision info
    int injective_cnt;
    int is_injective;
    int is_neutron;

    // Final info
    int neutrondegree;  // 1 = primary, 2 = secondary
} BufferGamma;



void fill_neutrondegree( int nscndprt, int *iprtscnd, int *lmecscnd, float pscnd[][3], int *iprnttrk, int *iorgprt, int *neutrondegree ) {
    BufferGamma buf[MAXSCNDPRT];
    int ng = 0;
    float totalmom = 0.;

    // Save 2.22 MeV gammas
    for ( int i = 0; i < nscndprt; ++i ) {
        totalmom = sqrt( pscnd[i][0]*pscnd[i][0] + pscnd[i][1]*pscnd[i][1] + pscnd[i][2]*pscnd[i][2] );
        if ( iprtscnd[i] == 22 && lmecscnd[i] == 18 && abs( totalmom - 2.22 ) < 0.1 ) {
            buf[ng].index    = i;
            buf[ng].iprtscnd = iprtscnd[i];
            buf[ng].totalmom = totalmom;
            buf[ng].lmecscnd = lmecscnd[i];
            buf[ng].iprnttrk = iprnttrk[i];
            buf[ng].iorgprt  = iorgprt[i];
            ++ng;
        }
    }


    // Put is_injective label
    for ( int i = 0; i < ng; ++i ) {
        buf[i].injective_cnt = 0;
        for ( int j = 0; j < ng; ++j ) {
            if ( buf[i].iprnttrk == buf[j].iprnttrk ) ++buf[i].injective_cnt;
        }

        buf[i].is_injective = buf[i].injective_cnt == 1 ? 1 : 0;
    }


    // Put is_neutron label
    for ( int i = 0; i < ng; ++i ) {
        buf[i].is_neutron = buf[i].iorgprt == 2112 ? 1 : 0;
    }

    // Put neutrondegree info
    for ( int i = 0; i < ng; ++i ) {
        if ( buf[i].is_injective == 1 && buf[i].is_neutron == 1 ) {
            buf[i].neutrondegree = 1;  // Primary neutron
        }
        else {
            buf[i].neutrondegree = 2;  // Secondary neutron
        }
    }

    // Return the neutrondegree (running on secondary particles, not only 2.22 MeV gammas) 
    ng = 0;
    for ( int i = 0; i < nscndprt; ++i ) {
        if ( buf[ng].index == i ) {
            neutrondegree[i] = buf[ng].neutrondegree;  // 2.2 MeV gammas
            ++ng;
        }
        else {
            neutrondegree[i] = -1;  // other particles
        } 

        //watch( neutrondegree[i] );  // DBG
    }

}




int main( int argc, char *argv[] ) {
    //------------------
    // Check arguments
    //------------------
    string ifname;
    string ofname;
    string vtxshift;

    // Parse arguments
    if ( argc != 3 && argc != 4 ) {
        cerr << " 2 (+1) arguments needed:" << endl;
        cerr << " ---> ifname [.root]" << endl;
        cerr << " ---> ofname [.root]" << endl;
        cerr << " ---> vtxshift (OPTIONAL)" << endl;

        exit( EXIT_FAILURE );
    }
    else if ( argc == 3 ) {
        ifname = argv[1];
        ofname = argv[2];
        vtxshift = "NOVTXSHIFT";
    }
    else if ( argc == 4 ) {
        ifname = argv[1];
        ofname = argv[2];
        vtxshift = argv[3];
    }
    else {
        cerr << " ---> ERROR in function " << __func__ << " parsing arguments" << endl;
        exit( EXIT_FAILURE );
    }
    
    // Watch arguments
    watch( ifname );
    watch( ofname );
    watch( vtxshift );

    // Check vertexshift
    if ( vtxshift != "VTXSHIFTOUT" && vtxshift != "VTXSHIFTIN" && vtxshift != "NOVTXSHIFT" ) {
        cerr << " ---> ERROR in function " << __func__ << ": unknown vtxshift value" << endl;
        exit( EXIT_FAILURE );
    }

    // fvfill init
    fvfill_init();

    // init tubes
    zbsinit_(); // wrapper around kzinit/kzlimit (set skgeometry = 4 and calls geoset)
    kzeclr_();

    /*
    ConnectionTable conntab;
    for ( int i = 1; i < MAXPM+1; ++i ) {
        //conntab.PrintTubePosition( i );
        conntab.GetTubePosition( i , geopmt_.xyzpm[i-1]  );
    }
    */

    // DBG
    /*
    for ( int i = 0; i < MAXPM; ++i ) {
        fprintf( stderr, "%10d %12.5f %12.5f %12.5f\n", i, geopmt_.xyzpm[i][0], geopmt_.xyzpm[i][1], geopmt_.xyzpm[i][2] );
    }
    */

    // Open input file
    TFile *ifile = new TFile( ifname.c_str() );
    TTree *itree = NULL;
    ifile->GetObject( "h1", itree );
    int nentry = itree->GetEntries();
    watch( nentry );


    // Open output files
    FeatureVector fv;
    TFile *ofile = new TFile( ofname.c_str(), "RECREATE" );
    TTree *otree = itree->CloneTree( 0 );

    TString sigoutfname = ntag_fname_maker( ofname, "nsig_" );
    watch( sigoutfname );
    TFile *fout_nsig = new TFile(sigoutfname, "RECREATE");
    TTree *nsigtree = new TTree ( "ntag", "ntag" );
    createNTagTree( nsigtree, fv );

    TString bkgoutfname = ntag_fname_maker( ofname, "nbkg_" );
    watch( bkgoutfname );
    TFile *fout_nbkg = new TFile(bkgoutfname, "RECREATE");
    TTree *nbkgtree = new TTree ( "ntag", "ntag" );
    createNTagTree( nbkgtree, fv );


    // Branch management
    int nrun;
    int nsub;
    int nev;
    float dt0vtx;
    float dt0;
    int validfit;
    int validhit;
    float tbgn, tend, tdur, tntagdur;
    int nscndprt;
    float pos[3];
    float posv[3];
	int npar;
	float pmomv[1000];
    float erec, wall, effwall, ovaq, angle;
    int prm_trufal_label[MAXSCNDPRT];
    int prm_posneg_label[MAXSCNDPRT];
    int prm_truall;
    int prm_truallin;
    int prm_truallout;
    int prm_posall;
    int prm_trupos;
    int prm_trupos_n1;
    int prm_trupos_n2;
    int prm_falpos;
    int prm_truneg;
    int prm_fvprocessed;
    int prm_fvunprocessed;
    int prm_initia_nqiskz513;
    int prm_initia_nqiskz495;
    int prm_dblcut_nwnd495;
    float prm_t0[MAXSCNDPRT];
    float prm_trgofst[MAXSCNDPRT];
    float prm_tds[MAXSCNDPRT];
    float prm_timetruall[MAXSCNDPRT];
    float prm_timetrupos[MAXSCNDPRT];
    float prm_timefalpos[MAXSCNDPRT];
    float prm_truenvx[MAXSCNDPRT][3];
    float vtxscnd[MAXSCNDPRT][3];
    float pscnd[MAXSCNDPRT][3];
    float trgofst;
    int           iprtscnd[MAXSCNDPRT];
    int           lmecscnd[MAXSCNDPRT];
    int           iprnttrk[MAXSCNDPRT];
    int           iorgprt[MAXSCNDPRT];
    float         tscnd[MAXSCNDPRT];

    // 7oct2020 - nnvar
    int N10nvx[MAXSCNDPRT];
    int N300S[MAXSCNDPRT];
    int NcS[MAXSCNDPRT];
    float llrca[MAXSCNDPRT];
    float beta1[MAXSCNDPRT];
    float beta2[MAXSCNDPRT];
    float beta3[MAXSCNDPRT];
    float beta4[MAXSCNDPRT];
    float beta5[MAXSCNDPRT];
    float accepave[MAXSCNDPRT];
    float taurms[MAXSCNDPRT];
    float mintaurms6[MAXSCNDPRT];
    float ndwall[MAXSCNDPRT];
    float ntowall[MAXSCNDPRT];




    // 25jun2020
    float prm_reconvx[MAXSCNDPRT][3];

    itree->SetBranchAddress( "nrun", &nrun );
    itree->SetBranchAddress( "nsub", &nsub );
    itree->SetBranchAddress( "nev", &nev );
    itree->SetBranchAddress( "dt0vtx", &dt0vtx );
    itree->SetBranchAddress( "dt0", &dt0 );
    itree->SetBranchAddress( "validfit", &validfit );
    itree->SetBranchAddress( "tbgn", &tbgn );
    itree->SetBranchAddress( "tend", &tend );
    itree->SetBranchAddress( "tdur", &tdur );
    itree->SetBranchAddress( "pos", pos );
    itree->SetBranchAddress( "posv", posv );
	itree->SetBranchAddress( "npar", &npar );
	itree->SetBranchAddress( "pmomv", pmomv );
    itree->SetBranchAddress( "nscndprt", &nscndprt );
    itree->SetBranchAddress( "iprtscnd", iprtscnd );
    itree->SetBranchAddress( "lmecscnd", lmecscnd );
    itree->SetBranchAddress( "iprnttrk", iprnttrk );
    itree->SetBranchAddress( "iorgprt", iorgprt );
    itree->SetBranchAddress( "vtxscnd", vtxscnd );
    itree->SetBranchAddress( "trgofst", &trgofst );
    itree->SetBranchAddress( "tscnd", tscnd );
    itree->SetBranchAddress( "pscnd", pscnd );
    itree->SetBranchAddress( "erec", &erec );
    itree->SetBranchAddress( "wall", &wall );
    itree->SetBranchAddress( "effwall", &effwall );
    itree->SetBranchAddress( "ovaq", &ovaq );
    itree->SetBranchAddress( "angle", &angle );
    itree->SetBranchAddress( "nqiskz", &sktqz_.nqiskz );
    itree->SetBranchAddress( "icabiz", sktqz_.icabiz );
    itree->SetBranchAddress( "tiskz", sktqz_.tiskz );
    itree->SetBranchAddress( "qiskz", sktqz_.qiskz );

	otree->Branch( "tntagdur", &tntagdur, "tntagdur/F" );
    otree->Branch( "validhit", &validhit, "validhit/I" );
    otree->Branch( "prm_truall", &prm_truall, "prm_truall/I" );
    otree->Branch( "prm_truallin", &prm_truallin, "prm_truallin/I" );
    otree->Branch( "prm_truallout", &prm_truallout, "prm_truallout/I" );
    otree->Branch( "prm_posall", &prm_posall, "prm_posall/I" );
    otree->Branch( "prm_trupos", &prm_trupos, "prm_trupos/I" );
    otree->Branch( "prm_trupos_n1", &prm_trupos_n1, "prm_trupos_n1/I" );
    otree->Branch( "prm_trupos_n2", &prm_trupos_n2, "prm_trupos_n2/I" );
    otree->Branch( "prm_falpos", &prm_falpos, "prm_falpos/I" );
    otree->Branch( "prm_truneg", &prm_truneg, "prm_truneg/I" );
    otree->Branch( "prm_fvprocessed", &prm_fvprocessed, "prm_fvprocessed/I" );
    otree->Branch( "prm_fvunprocessed", &prm_fvunprocessed, "prm_fvunprocessed/I" );
    otree->Branch( "prm_dblcut_nwnd495", &prm_dblcut_nwnd495, "prm_dblcut_nwnd495/I" );
    otree->Branch( "prm_posneg_label"  , prm_posneg_label  , "prm_posneg_label[prm_dblcut_nwnd495]/I" );
    otree->Branch( "prm_trufal_label"  , prm_trufal_label  , "prm_trufal_label[prm_dblcut_nwnd495]/I" );
    otree->Branch( "prm_initia_nqiskz513", &prm_initia_nqiskz513, "prm_initia_nqiskz513/I" );
    otree->Branch( "prm_initia_nqiskz495", &prm_initia_nqiskz495, "prm_initia_nqiskz495/I" );
    otree->Branch( "prm_t0", prm_t0, "prm_t0[prm_posall]/F" );
    otree->Branch( "prm_timetruall", prm_timetruall, "prm_timetruall[prm_truall]/F" );
    otree->Branch( "prm_truenvx", prm_truenvx, "prm_truenvx[prm_truall][3]/F" );

    // 25jun2020
    otree->Branch( "prm_reconvx", prm_reconvx, "prm_reconvx[prm_posall][3]/F" );
    otree->Branch( "prm_tds", prm_tds, "prm_tds[prm_posall]/F" );
    
    // 7oct2020 - nnvar
    otree->Branch( "N10nvx", N10nvx, "N10nvx[prm_posall]/I" );
    otree->Branch( "N300S", N300S, "N300S[prm_posall]/I" );
    otree->Branch( "NcS", NcS, "NcS[prm_posall]/I" );
    otree->Branch( "llrca", llrca, "llrca[prm_posall]/F" );
    otree->Branch( "beta1", beta1, "beta1[prm_posall]/F" );
    otree->Branch( "beta2", beta2, "beta2[prm_posall]/F" );
    otree->Branch( "beta3", beta3, "beta3[prm_posall]/F" );
    otree->Branch( "beta4", beta4, "beta4[prm_posall]/F" );
    otree->Branch( "beta5", beta5, "beta5[prm_posall]/F" );
    otree->Branch( "accepave", accepave, "accepave[prm_posall]/F" );
    otree->Branch( "taurms", taurms, "taurms[prm_posall]/F" );
    otree->Branch( "mintaurms6", mintaurms6, "mintaurms6[prm_posall]/F" );
    otree->Branch( "ndwall", ndwall, "ndwall[prm_posall]/F" );
    otree->Branch( "ntowall", ntowall, "ntowall[prm_posall]/F" );


// Begin of event loop
float secondary_pabs;
CableTimeHit CT[30*MAXPM];
int ctsize;
for ( int ientry = 0; ientry < nentry; ++ientry ) {
	// Get entry
	itree->GetEntry( ientry );
	fill_ct_nosbi( sktqz_, combad_, CT, ctsize );

	// t of event
	//tbgn = sktqz_.tiskz[0];
	tend = sktqz_.tiskz[sktqz_.nqiskz-1];
	tbgn = CT[0].tiskz;
	tend = CT[ctsize-1].tiskz;
	tdur = tend - tbgn;
	tntagdur = tend - 19000.;
	watch( tbgn );
	watch( tend );
	watch( tdur );
	watch( tntagdur );


    //======================================
    //
    // 12nov2019
    // NEUTRON TAGGING ALGORITHM
    //
    // 0. SET AMBE SPECIFICS / VTX SHIFT
    //
    // 1. CLEAR / SET COUNTERS
    //
    // 2. GET TRUE INFO
    //
    // 3. NTAG SCAN (see diagram below)
    //
    //
    //                              |--- SIG (0b111)
    //               |--- FVPROC ---|
    //               |              |--- BKG (0b110)
    // |--- VALID ---|
    // |             |
    // |             |--- FVUNPROC (0b100)
    // |
    // |
    // |
    // |--- INVALID (0b000)
    //
    //
    // 4. PRINT COUNTERS
    //
    // 5. CHECK COUNTERS
    //
    //=====================================
    
    //====================================
    //
    // 0. SET AMBE SPECIFICS / VTX SHIFT
    //
    //====================================
    //pos[0] = 35.3; pos[1] = -70.7; pos[2] = 0.;  // AmBe AMBE ambe Ambe central
    if ( vtxshift == "NOVTXSHIFT" ) {
        // It's normal, nothing special
        cout << endl;
    }
    else if ( vtxshift == "VTXSHIFTOUT" ) {
        // Apply the shift, this function modifies the pos vector to outer positions
        //apply_vtxshift_average( pos );
        apply_vtxshift_worstcase( pos, +1. );
    }
    else if ( vtxshift == "VTXSHIFTIN" ) {
        // Apply the shift, this function modifies the pos vector to inner positions
        apply_vtxshift_worstcase( pos, -1. );
    }
    else {
        cerr << " ---> ERROR in function " << __func__ << ": unknown vtxshift option" << endl;
        exit( EXIT_FAILURE );
    }

    //==========================
    //
    // 1. CLEAR / SET COUNTERS
    //
    //==========================

    // Clear counters
    prm_truall = 0;
    prm_truallin = 0;
    prm_truallout = 0;
    prm_posall = 0;
    prm_trupos = 0;
    prm_trupos_n1 = 0;
    prm_trupos_n2 = 0;
    prm_falpos = 0;
    prm_truneg = 0;

    prm_fvprocessed = 0;
    prm_fvunprocessed = 0;

    int write_tp = 0;
    int write_fp = 0;

    // Set counters
    prm_initia_nqiskz513 = ctsize;
    prm_initia_nqiskz495 = 0;
	for ( int i = 0; i < ctsize; ++i ) {
        if ( 19000. < CT[i].tiskz && CT[i].tiskz < 514000. ) {
            ++prm_initia_nqiskz495;
        }
    }
    prm_dblcut_nwnd495 = 0;



    //===================
    //
    // 2. GET TRUE INFO
    //
    //===================
    
    float secondary_pabs;
    int neutrondegree[MAXSCNDPRT];
    printf( "***********************************\n" );
    printf( "****** NEUTRON TAGGING BEGIN ******\n" );
    printf( "***********************************\n" );
    printf( "--- SECONDARY PARTICLES ---\n" );
    printf( "nscndprt = %d\n", nscndprt );
    printf( "    i      pdg-id  lmech    momentum        time\n" );
    //printf( "12345  0123456789  01234  0123456789  0123456789" );

    fill_neutrondegree( nscndprt, iprtscnd, lmecscnd, pscnd, iprnttrk, iorgprt, neutrondegree );
    for ( int isp = 0; isp < nscndprt; ++isp ) {
        secondary_pabs = pscnd[isp][0]*pscnd[isp][0] + pscnd[isp][1]*pscnd[isp][1] + pscnd[isp][2]*pscnd[isp][2];
        secondary_pabs = sqrt( secondary_pabs );
        printf( "%5d  %10d  %5d  %10.2f  %10.2f\n", isp, iprtscnd[isp], lmecscnd[isp], secondary_pabs, tscnd[isp] );

        if ( iprtscnd[isp] == 22 && lmecscnd[isp] == 18 && abs( secondary_pabs - 2.22 ) < 0.1 ) {
            prm_timetruall[prm_truall] = tscnd[isp];
            prm_truenvx[prm_truall][0] = vtxscnd[isp][0];
            prm_truenvx[prm_truall][1] = vtxscnd[isp][1];
            prm_truenvx[prm_truall][2] = vtxscnd[isp][2];

            ++prm_truall;  // It's a true neutron
            if ( is_inside_sk( vtxscnd[isp] ) ) ++prm_truallin;  // It's inside ID
            else ++prm_truallout;  // It's outside ID
        }
    }



    //===============
    //
    // 3. NTAG SCAN
    //
    //===============
    // DBG WARNING dbg warning! Time dependent upper bound correcting to gain drift in SK - IV
    //validhit = (int)( 20000 < sktqz_.nqiskz && sktqz_.nqiskz < 40000 );  // remove lo bnd. hi bnd as atmpd
    //validhit = (int)( 17000 < (float) prm_initia_nqiskz495 / tntagdur * 495000. && (float) prm_initia_nqiskz495 / tntagdur * 495000. < 37000 );
    std::cout << "prm_initia_nqiskz495: " << prm_initia_nqiskz495 << std::endl;
    validhit = (int)(17000 < prm_initia_nqiskz495 && prm_initia_nqiskz495 < 37000);
    //validhit = 1;  // Only for pure neutron gun check (Am/Be Secondary)

    //----------
    //
    // INVALID
    //
    //----------
    //validhit = 1;
    if ( validfit == 0 || validhit == 0 ) {
        cerr << "NTAG INVALID validfit = " << validfit << " validhit = " << validhit << '\n';
    }
    //--------
    //
    // VALID
    //
    //--------
    else {
        cerr << "NTAG VALID validfit = " << validfit << " validhit = " << validhit << '\n';
        // Data structures for neutron tagging
        printf( "--- PRIMARY CUTS ---\n" );
        //CableTimeHit CT[30*MAXPM];
        //int ctsize;
        WindowBounds wndbnd[1000];
        int wbsize;

        // Fill cable-time info about hits
        fprintf( stderr, "sktqz_.nqiskz = %d\n", sktqz_.nqiskz );  // Should be masked
        //fill_ct_nosbi( sktqz_, combad_, CT, ctsize );
        printf( "Initial      hits in [0, 513] usec = %d\n", prm_initia_nqiskz513 );

        // Search candidates
        searchCandidates( CT, ctsize, pos, wndbnd, wbsize ); // Normal
        prm_dblcut_nwnd495 = wbsize;
        printf( "Post-Doublet-Cut N10 windows in [18, 513] usec = %d\n", prm_dblcut_nwnd495 );

        //printf( "01234  0123456789  0123456789  0123456789  01234\n" );
        printf( "--- SIGNAL / BACKGROUND ---\n" );
        printf( "iwnd           t0     trgofst         tds  label\n" );
        for ( int iwnd = 0; iwnd < prm_dblcut_nwnd495; ++iwnd ) {
            prm_trufal_label[iwnd] = (int)candidate_is_signal( nscndprt, iprtscnd, lmecscnd, tscnd, trgofst, pscnd, wndbnd[iwnd], prm_t0[iwnd], prm_tds[iwnd] );
            //printf( "%5d  %10.2f  %10.2f  %10.2f  %5d\n", iwnd, prm_t0[iwnd], prm_trgofst[iwnd], prm_tds[iwnd], prm_trufal_label[iwnd] );  // 9oct2020 - TEST - DBG
            printf( "%5d  %10.2f  %10.2f  %10.2f  %5d\n", iwnd, prm_t0[iwnd], trgofst, prm_tds[iwnd], prm_trufal_label[iwnd] );  // 9oct2020 - TEST - DBG
        }
        
        // Compute Feature Vector
        for ( int iwnd = 0; iwnd < wbsize; ++iwnd ) {
            //--------------------
            //
            // VALID ---> FVPROC
            //
            //--------------------
            //if ( fill_feature_vector( CT, ctsize, wndbnd[iwnd], pos, fv ) == 0 ) {  // Normal
			if ( computeVariables ( CT, ctsize, wndbnd[iwnd], pos, fv ) == 0 ) {  // Normal
                cerr << "NTAG FVPROC" << '\n';
                ++prm_fvprocessed;
                prm_posneg_label[iwnd] = +1;  // positive
                //-----------------------------
                //
                // VALID ---> FVPROC ---> BKG
                //
                //-----------------------------
                if ( prm_trufal_label[iwnd] == -1 ) {
                    fv.nrun = nrun;
                    fv.nsub = nsub;
                    fv.nev = nev;
                    fv.dt0vtx = dt0vtx;
                    fv.dt0 = dt0;
                    fv.neutrondegree = -9999;
                    watch( fv.neutrondegree );
                    fv.dist_truentagvtx = -1.;
                    fv.truenvx[0] = fv.truenvx[1] = fv.truenvx[2] = -1e7;  // True neutron vtx
                    fv.truebvx[0] = posv[0];  // True neutrino vtx
                    fv.truebvx[1] = posv[1];  // True neutrino vtx
                    fv.truebvx[2] = posv[2];  // True neutrino vtx
                    fv.erec = erec;
                    fv.wall    = wall;
                    fv.effwall = effwall;
                    fv.ovaq    = ovaq;
                    fv.angle = angle;
                    prm_timefalpos[prm_falpos] = wndbnd[iwnd].bgn->tiskz;
                    fv.timefalpos = wndbnd[iwnd].bgn->tiskz;
                    fv.timetrupos = -9999.;
					fv.capture_time = wndbnd[iwnd].bgn->tiskz;
					fv.neutron_mom = pmomv[0];  // Only valid for Am/Be systematics

                    // 25jun2020
                    prm_reconvx[prm_posall][0] = fv.ntagvtx[0];
                    prm_reconvx[prm_posall][1] = fv.ntagvtx[1];
                    prm_reconvx[prm_posall][2] = fv.ntagvtx[2];

                    // 7oct2020 - nnvar
                    N10nvx[prm_posall] = fv.N10nvx;
                    N300S[prm_posall] = fv.N300S;
                    NcS[prm_posall] = fv.NcS;
                    llrca[prm_posall] = fv.llrca;
                    beta1[prm_posall] = fv.beta[0];
                    beta2[prm_posall] = fv.beta[1];
                    beta3[prm_posall] = fv.beta[2];
                    beta4[prm_posall] = fv.beta[3];
                    beta5[prm_posall] = fv.beta[4];
                    accepave[prm_posall] = fv.accepave;
                    taurms[prm_posall] = fv.taurms;
                    mintaurms6[prm_posall] = fv.mintaurms6;
                    ndwall[prm_posall] = fv.ndwall;
                    ntowall[prm_posall] = fv.ntowall;


                    cerr << "NTAG BKG" << '\n';
                    nbkgtree->Fill(); 

                    ++write_fp;
                    ++prm_falpos;
                    ++prm_posall;
                }
                //-----------------------------
                //
                // VALID ---> FVPROC ---> SIG
                //
                //-----------------------------
                if ( prm_trufal_label[iwnd] != -1 ) {
                    fv.nrun = nrun;
                    fv.nsub = nsub;
                    fv.nev = nev;
                    fv.dt0vtx = dt0vtx;
                    fv.dt0 = dt0;
                    fv.neutrondegree = neutrondegree[ prm_trufal_label[ iwnd ] ];
                    watch( fv.neutrondegree );
                    fv.dist_truentagvtx = euclidean_distance( fv.ntagvtx, vtxscnd[prm_trufal_label[iwnd]] ); 
                    fv.truenvx[0] = vtxscnd[prm_trufal_label[iwnd]][0];
                    fv.truenvx[1] = vtxscnd[prm_trufal_label[iwnd]][1];
                    fv.truenvx[2] = vtxscnd[prm_trufal_label[iwnd]][2];
                    fv.truebvx[0] = posv[0];  // True neutrino vtx
                    fv.truebvx[1] = posv[1];  // True neutrino vtx
                    fv.truebvx[2] = posv[2];  // True neutrino vtx
                    fv.erec = erec;
                    fv.wall    = wall;
                    fv.effwall = effwall;
                    fv.ovaq    = ovaq;
                    fv.angle = angle;
                    prm_timetrupos[prm_trupos] = wndbnd[iwnd].bgn->tiskz;
                    fv.timetrupos = wndbnd[iwnd].bgn->tiskz;
                    fv.timefalpos = -9999.;
					fv.capture_time = wndbnd[iwnd].bgn->tiskz;
					// DBG FOR NEUTRON MOM - BGN
					//cout << " --- DBG for Neutron momentum BGN ---" << endl;
					//watch( npar );
					//watch( pmomv[0] );
					//cout << " --- DBG for Neutron momentum END ---" << endl;
					// DBG FOR NEUTRON MOM - END
					fv.neutron_mom = pmomv[0];  // Only valid for Am/Be systematics

                    // 25jun2020
                    prm_reconvx[prm_posall][0] = fv.ntagvtx[0];
                    prm_reconvx[prm_posall][1] = fv.ntagvtx[1];
                    prm_reconvx[prm_posall][2] = fv.ntagvtx[2];

                    // 7oct2020 - nnvar
                    N10nvx[prm_posall] = fv.N10nvx;
                    N300S[prm_posall] = fv.N300S;
                    NcS[prm_posall] = fv.NcS;
                    llrca[prm_posall] = fv.llrca;
                    beta1[prm_posall] = fv.beta[0];
                    beta2[prm_posall] = fv.beta[1];
                    beta3[prm_posall] = fv.beta[2];
                    beta4[prm_posall] = fv.beta[3];
                    beta5[prm_posall] = fv.beta[4];
                    accepave[prm_posall] = fv.accepave;
                    taurms[prm_posall] = fv.taurms;
                    mintaurms6[prm_posall] = fv.mintaurms6;
                    ndwall[prm_posall] = fv.ndwall;
                    ntowall[prm_posall] = fv.ntowall;

                    cerr << "NTAG SIG" << '\n';
                    nsigtree->Fill();

                    ++write_tp;
                    ++prm_trupos;
                    ++prm_posall;
                    if ( neutrondegree[ prm_trufal_label[ iwnd ] ] == 1 ) ++prm_trupos_n1;
                    else if ( neutrondegree[ prm_trufal_label[ iwnd ] ] == 2 ) ++prm_trupos_n2;
                }
            }
            //----------------------
            //
            // VALID ---> FVUNPROC
            //
            //----------------------
            else {
                cerr << "NTAG FVUNPROC" << '\n';
                ++prm_fvunprocessed;
                prm_posneg_label[iwnd] = -1;  // Negative
            }
        }
        // Get runsum tuple (for dark rate)
        //runsum_gettuple( dummy_head.nrunsk, rstuple );


    }

    // Compute true negatives from incremented counters
    prm_truneg = prm_truall - prm_trupos;



    //====================
    //
    // 4. PRINT COUNTERS
    //
    //====================
    printf( "prm_truall    = %d\n", prm_truall );
    printf( "prm_truallin  = %d\n", prm_truallin );
    printf( "prm_truallout = %d\n", prm_truallout );
    printf( "prm_posall    = %d\n", prm_posall );
    printf( "prm_trupos    = %d\n", prm_trupos );
    printf( "prm_trupos_n1 = %d\n", prm_trupos_n1 );
    printf( "prm_trupos_n2 = %d\n", prm_trupos_n2 );
    printf( "prm_falpos    = %d\n", prm_falpos );
    printf( "prm_truneg    = %d\n", prm_truneg );
    printf( "prm_fvprocessed   = %d\n", prm_fvprocessed );
    printf( "prm_fvunprocessed = %d\n", prm_fvunprocessed );
    printf( "write_tp = %d\n", write_tp );
    printf( "write_fp = %d\n", write_fp );
    printf( "****** NEUTRON TAGGING END ******\n\n\n" );



    //====================
    //
    // 5. CHECK COUNTERS
    //
    //====================
    if ( prm_trupos + prm_falpos != prm_posall ) {
        cerr << " ---> ERROR in function " << __func__ << ", trupos + falpos != posall\n";
        exit( EXIT_FAILURE );
    }
    if ( prm_trupos + prm_truneg != prm_truall ) {
        cerr << " ---> ERROR in function " << __func__ << ", trupos + truneg != truall\n";
        exit( EXIT_FAILURE );
    }
    if ( write_tp != prm_trupos ) {
        cerr << " ---> ERROR in function " << __func__ << ", write_tp != trupos\n";
        exit( EXIT_FAILURE );
    }
    if ( write_fp != prm_falpos ) {
        cerr << " ---> ERROR in function " << __func__ << ", write_fp != falpos\n";
        exit( EXIT_FAILURE );
    }
    if ( prm_trupos_n1 + prm_trupos_n2 != prm_trupos ) {
        cerr << " ---> ERROR in function" << __func__ << ", prm_trupos_n1 + prm_trupos_n2 != prm_trupos\n";
        exit( EXIT_FAILURE );
    }

	// Fill tree
	sktqz_.nqiskz = 0;  // PREVENT WRITING TQ
	otree->Fill();
}  // END OF EVENT LOOP



    // Write and close
    ofile->cd();
    otree->Write();
    ofile->Close();

    fout_nsig->cd();
    nsigtree->Write();
    fout_nsig->Close();

    fout_nbkg->cd();
    nbkgtree->Write();
    fout_nbkg->Close();


    //otree->AutoSave();
    //ifile->Close();
    //delete ifile;
    //ofile->Close();
    //delete ofile;


    fvfill_end();
    
    return 0;
}








void createNTagTree( TTree *tree, FeatureVector &fv ) {
    // Run + sub + event
    tree->Branch( "nrun", &fv.nrun, "nrun/I" );
    tree->Branch( "nsub", &fv.nsub, "nsub/I" );
    tree->Branch( "nev", &fv.nev, "nev/I" );
    tree->Branch( "dt0vtx", &fv.dt0vtx, "dt0vtx/F" );
    tree->Branch( "dt0", &fv.dt0, "dt0/F" );
    // Classifier input
    tree->Branch( "N10nvx"           , &fv.N10nvx,            "N10nvx/I" );
    tree->Branch( "N300S"           , &fv.N300S,            "N300S/I" );
    tree->Branch( "NcS"           , &fv.NcS,            "NcS/I" );
    tree->Branch( "llrca"           , &fv.llrca,             "llrca/F" );
    tree->Branch( "nllrca"          , &fv.nllrca,            "nllrca/F" );
    //tree->Branch( "cangmean"             , &fv.cangmean,              "cangmean/F" );
    //tree->Branch( "cangstddev"             , &fv.cangstddev,              "cangstddev/F" );
    //tree->Branch( "cangskew"             , &fv.cangskew,              "cangskew/F" );
    //tree->Branch( "cangkurt"             , &fv.cangkurt,              "cangkurt/F" );
    //tree->Branch( "cangcntnan"             , &fv.cangcntnan,              "cangcntnan/I" );
    tree->Branch( "beta1"             , &fv.beta[0],              "beta1/F" );
    tree->Branch( "beta2"             , &fv.beta[1],              "beta2/F" );
    tree->Branch( "beta3"             , &fv.beta[2],              "beta3/F" );
    tree->Branch( "beta4"             , &fv.beta[3],              "beta4/F" );
    tree->Branch( "beta5"             , &fv.beta[4],              "beta5/F" );
    tree->Branch( "accepave"             , &fv.accepave,              "accepave/F" );
    tree->Branch( "taurms"             , &fv.taurms,              "taurms/F" );
    tree->Branch( "mintaurms6"             , &fv.mintaurms6,              "mintaurms6/F" );
    tree->Branch( "ndwall"             , &fv.ndwall,              "ndwall/F" );
    tree->Branch( "ntowall"             , &fv.ntowall,              "ntowall/F" );
    tree->Branch( "d0"             , &fv.d[0],              "d0/F" );
    tree->Branch( "d1"             , &fv.d[1],              "d1/F" );
    tree->Branch( "d2"             , &fv.d[2],              "d2/F" );
    tree->Branch( "d3"             , &fv.d[3],              "d3/F" );
    tree->Branch( "d4"             , &fv.d[4],              "d4/F" );
    tree->Branch( "d5"             , &fv.d[5],              "d5/F" );
    tree->Branch( "d6"             , &fv.d[6],              "d6/F" );
    tree->Branch( "dmean"          , &fv.dmean,           "dmean/F" );
    tree->Branch( "drms"           , &fv.drms,            "drms/F" );
    tree->Branch( "ddiff"          , &fv.ddiff,           "ddiff/F" );
    tree->Branch( "spheremeannorm" , &fv.spheremeannorm,  "spheremeannorm/F" );
    tree->Branch( "stau0"             , &fv.stau[0],              "stau0/F" );
    tree->Branch( "stau1"             , &fv.stau[1],              "stau1/F" );
    tree->Branch( "stau2"             , &fv.stau[2],              "stau2/F" );
    tree->Branch( "stau3"             , &fv.stau[3],              "stau3/F" );
    tree->Branch( "stau4"             , &fv.stau[4],              "stau4/F" );
    tree->Branch( "stau5"             , &fv.stau[5],              "stau5/F" );
    tree->Branch( "stau6"             , &fv.stau[6],              "stau6/F" );
    tree->Branch( "staugeom0"             , &fv.staugeom[0],              "staugeom0/F" );
    tree->Branch( "staugeom1"             , &fv.staugeom[1],              "staugeom1/F" );
    tree->Branch( "staugeom2"             , &fv.staugeom[2],              "staugeom2/F" );
    tree->Branch( "staugeom3"             , &fv.staugeom[3],              "staugeom3/F" );
    tree->Branch( "staugeom4"             , &fv.staugeom[4],              "staugeom4/F" );
    tree->Branch( "staugeom5"             , &fv.staugeom[5],              "staugeom5/F" );
    tree->Branch( "staugeom6"             , &fv.staugeom[6],              "staugeom6/F" );
    tree->Branch( "taurms_stat0"   , &fv.taurms_stat[0],      "taurms_stat0/F" );
    tree->Branch( "taurms_stat1"   , &fv.taurms_stat[1],      "taurms_stat1/F" );
    tree->Branch( "taurms_stat2"   , &fv.taurms_stat[2],      "taurms_stat2/F" );
    tree->Branch( "taurms_stat3"   , &fv.taurms_stat[3],      "taurms_stat3/F" );
    tree->Branch( "taurms_stat4"   , &fv.taurms_stat[4],      "taurms_stat4/F" );
    tree->Branch( "taurms_stat5"   , &fv.taurms_stat[5],      "taurms_stat5/F" );
    tree->Branch( "taurms_stat6"   , &fv.taurms_stat[6],      "taurms_stat6/F" );
    tree->Branch( "taurms_stat7"   , &fv.taurms_stat[7],      "taurms_stat7/F" );
    tree->Branch( "taurms_stat8"   , &fv.taurms_stat[8],      "taurms_stat8/F" );
    tree->Branch( "taurms_stat9"   , &fv.taurms_stat[9],      "taurms_stat9/F" );
    tree->Branch( "taurms_stat10"   , &fv.taurms_stat[10],      "taurms_stat10/F" );
    tree->Branch( "taurms_stat11"   , &fv.taurms_stat[11],      "taurms_stat11/F" );

    // Spectator variables
    tree->Branch( "neutrondegree"  , &fv.neutrondegree,    "neutrondegree/I" );
    tree->Branch( "ntagvtx"        , fv.ntagvtx,          "ntagvtx[3]/F" );
    tree->Branch( "ntagvtx_val"    , &fv.ntagvtx_val,      "ntagvtx_val/F" );
    tree->Branch( "ntagvtx_flag"   , &fv.ntagvtx_flag,     "natgvtx_flag/I" );
    tree->Branch( "bonsvtx"        , fv.bonsvtx,          "bonsvtx[3]/F" );
    tree->Branch( "bonsvtx_val"    , &fv.bonsvtx_val,      "bonsvtx_val/F" );
    tree->Branch( "dist_bonsntagvtx"    , &fv.dist_bonsntagvtx,     "dist_bonsntagvtx/F" );
    tree->Branch( "diff_bonsntagvtx_val", &fv.diff_bonsntagvtx_val, "diff_bonsntagvtx_val/F" );
    tree->Branch( "dist_truentagvtx"    , &fv.dist_truentagvtx,     "dist_truentagvtx/F" );
    tree->Branch( "truenvx",         fv.truenvx,            "truenvx[3]/F" );
    tree->Branch( "truebvx",         fv.truebvx,            "truebvx[3]/F" );
    tree->Branch( "erec", &fv.erec, "erec/F" );
    tree->Branch( "wall",    &fv.wall,    "wall/F" );
    tree->Branch( "effwall", &fv.effwall, "effwall/F" );
    tree->Branch( "ovaq",    &fv.ovaq,    "ovaq/F" );
    tree->Branch( "angle", &fv.angle, "angle/F" );
    tree->Branch( "timetrupos", &fv.timetrupos, "timetrupos/F" );
    tree->Branch( "timefalpos", &fv.timefalpos, "timefalpos/F" );
	tree->Branch( "capture_time", &fv.capture_time, "capture_time/F" );
	tree->Branch( "neutron_mom", &fv.neutron_mom, "neutron_mom/F" );
    //tree->Branch( "nsig_bonsvtx", &fv.nsig_bonsvtx, "nsig_bonsvtx/I" );
    //tree->Branch( "nbkg_bonsvtx", &fv.nbkg_bonsvtx, "nbkg_bonsvtx/I" );
    //tree->Branch( "nsig_ntagvtx", &fv.nsig_ntagvtx, "nsig_ntagvtx/I" );
    //tree->Branch( "nbkg_ntagvtx", &fv.nbkg_ntagvtx, "nbkg_ntagvtx/I" );
    //tree->Branch( "sbvec_bonsvtx", fv.sbvec_bonsvtx, "sbvec_bonsvtx[N10nvx]/B" );
    //tree->Branch( "sbvec_ntagvtx", fv.sbvec_ntagvtx, "sbvec_ntagvtx[N10nvx]/B" );
    //tree->Branch( "dummy_nrunsk", &dummy_head.nrunsk, "dummy_nrunsk/I" );
    //tree->Branch( "dummy_nsubsk", &dummy_head.nsubsk, "dummy_nsubsk/I" );
    //tree->Branch( "dummy_nevsk", &dummy_head.nevsk, "dummy_nevsk/I" );
    //tree->Branch( "dummy_ndaysk", dummy_head.ndaysk, "dummy_ndaysk[3]/I" );
    //tree->Branch( "dummy_ntimsk", dummy_head.ntimsk, "dummy_ntimsk[4]/I" );
    //tree->Branch( "darkrate"    , &rstuple.darkrate        , "darkrate/F" );
}


