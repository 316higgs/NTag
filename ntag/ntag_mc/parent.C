#define dbg( x ) std::cout << "DBG " << (x) << '\n'
#define dump( x ) std::cout << (x) << '\n'
#define watch( x ) std::cout << (#x) << " = " << (x) << '\n'

#define MAXPART 500

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
    BufferGamma buf[MAXPART];
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
    }

}



int parent() {
    // Input
    string ifname = "seclentp_numubar.ncgamma_flux13a_neut533.099.root";
    TFile *ifile = new TFile( ifname.c_str() );
    if ( ifile->IsZombie() ) {
        cout << " ---> ERROR in function " << __func__ << ", file " << ifname << " not found" << '\n';
        exit( EXIT_FAILURE );
    }

    TTree *itree = NULL;
    ifile->GetObject( "h1", itree );
    if ( itree == NULL ) {
        cout << " ---> ERROR in function " << __func__ << ", tree h1 not found" << '\n';
        exit( EXIT_FAILURE );
    }

    int nentry = itree->GetEntries();
    watch( nentry );

    // Primary particles
    float radiusv;
    float posv[3];
    int npar;
    int ipv[MAXPART];
    float pmomv[MAXPART];
    float dirv[MAXPART][3];
    float parentdirinit[3];

    itree->SetBranchAddress( "posv", posv );
    itree->SetBranchAddress( "npar", &npar );
    itree->SetBranchAddress( "ipv", ipv );
    itree->SetBranchAddress( "pmomv", pmomv );
    itree->SetBranchAddress( "dirv", dirv );

    // NPAR2 particles
    int npar2;
    int ipv2[MAXPART];

    itree->SetBranchAddress( "npar2", &npar2 );
    itree->SetBranchAddress( "ipv2", ipv2 );
 
    // Secondary particles
    float totalmom, parentmominit, parentmom, radiusprnt, radiusscnd;
    int neutrondegree[MAXPART];
    int nscndprt;
    float vtxscnd[MAXPART][3];
    int iprtscnd[MAXPART];
    int lmecscnd[MAXPART];
    float pscnd[MAXPART][3];
    float vtxprnt[MAXPART][3];
    int iprntidx[MAXPART];
    float pprntinit[MAXPART][3];
    float pprnt[MAXPART][3];
    int iprnttrk[MAXPART];
    int iprntprt[MAXPART];
    int iorgprt[MAXPART];

    itree->SetBranchAddress( "nscndprt", &nscndprt );
    itree->SetBranchAddress( "vtxscnd", vtxscnd );
    itree->SetBranchAddress( "iprtscnd", iprtscnd );
    itree->SetBranchAddress( "lmecscnd", lmecscnd );
    itree->SetBranchAddress( "pscnd", pscnd );
    itree->SetBranchAddress( "vtxprnt", vtxprnt );
    itree->SetBranchAddress( "iprntidx", iprntidx );
    itree->SetBranchAddress( "pprnt", pprnt );
    itree->SetBranchAddress( "pprntinit", pprntinit );
    itree->SetBranchAddress( "iprnttrk", iprnttrk );
    itree->SetBranchAddress( "iprntprt", iprntprt );
    itree->SetBranchAddress( "iorgprt", iorgprt );

    for ( int i = 0; i < nentry; ++i ) {
        cout << '\n' << '\n';
        cout << "*** ENTRY " << i << " ***" << '\n';
        itree->GetEntry( i );

        watch( npar );
        for ( int k = 0; k < npar; ++k ) {
            //cout << "PRM  " << k << "  " << pmomv[k] << "  " << dirv[k][0] << "  " << dirv[k][1] << "  " << dirv[k][2] << '\n';
            radiusv = sqrt( posv[0]*posv[0] + posv[1]*posv[1] + posv[2]*posv[2] );
            printf( "PRM  %8d  %8d  %8f  %8f\n", k+1, ipv[k], pmomv[k], radiusv );
        }

        watch( npar2 );
        for ( int l = 0; l < npar2; ++l ) {
            printf( "NPAR2  %8d  %8d\n", l+1, ipv2[l] );
        }
 
        watch( nscndprt );
        fill_neutrondegree( nscndprt, iprtscnd, lmecscnd, pscnd, iprnttrk, iorgprt, neutrondegree );
        //cout << "POSV = " << posv[0] << "  " << posv[1] << "  " << posv[2] << '\n';
        for ( int j = 0; j < nscndprt; ++j ) {
            totalmom = sqrt( pscnd[j][0]*pscnd[j][0] + pscnd[j][1]*pscnd[j][1] + pscnd[j][2]*pscnd[j][2] );
            parentmom = sqrt( pprnt[j][0]*pprnt[j][0] + pprnt[j][1]*pprnt[j][1] + pprnt[j][2]*pprnt[j][2] );
            parentmominit = sqrt( pprntinit[j][0]*pprntinit[j][0] + pprntinit[j][1]*pprntinit[j][1] + pprntinit[j][2]*pprntinit[j][2] );
            parentdirinit[0] = pprntinit[j][0] / parentmominit;
            parentdirinit[1] = pprntinit[j][1] / parentmominit;
            parentdirinit[2] = pprntinit[j][2] / parentmominit;
            radiusprnt = sqrt( vtxprnt[j][0]*vtxprnt[j][0] + vtxprnt[j][1]*vtxprnt[j][1] + vtxprnt[j][2]*vtxprnt[j][2] );
            radiusscnd = sqrt( vtxscnd[j][0]*vtxscnd[j][0] + vtxscnd[j][1]*vtxscnd[j][1] + vtxscnd[j][2]*vtxscnd[j][2] );

            //cout << "SEC  " << j << "  " << iprtscnd[j] << "  " << totalmom << "  " << iprntprt[j] << "  " << iprntidx[j] << "  " << parentmominit << "  " << parentmom << "  " << parentdirinit[0] << "  " << parentdirinit[1] << "  " << parentdirinit[2] << '\n';
            printf( "SEC  %8d  %8d  %8d  %8d  %8d  %8d\n", j, iprtscnd[j], iprnttrk[j], iprntprt[j], iorgprt[j], neutrondegree[j] );
        }

   }

    return 0;
}



