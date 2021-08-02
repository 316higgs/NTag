#include "prm.h"
#include <iostream>

using namespace std;

#define dump( x ) std::cerr << (x) << '\n'
#define watch( x ) std::cerr << (#x) << " = " << (x) << '\n'
#define dbg( x ) std::cerr << "DBG " << x << '\n'

extern "C" void zbsinit_();
extern "C" void skopenf_( int&, int&, const char*, int&, long );
extern "C" void skoptn_( const char*, long );
extern "C" void skcread_( int&, int& );
extern "C" void skgetv_();
extern "C" void kzeclr_();
extern "C" void skclosef_(int&);

int main() {
    // Open ZBS file
    int ilun = 10;
    int ipt = 1, ierr;
    string opt = "31,30,29,27,26,25";
    zbsinit_();
    skoptn_( (char*)opt.c_str(), opt.length() );
    skopenf_( ilun, ipt, "Z", ierr, 1 );
    
    // Loop through events
    int nevt = 0;
    int limnevt = -1;
    watch( limnevt );
    CableTimeHit CT[30*MAXPM];
    WindowBounds wndbnd[50];
    FeatureVector featvec[50];
    int wbsize;
    int n10;  // DBG
    int ctsize;
    float vtx[3];
    while ( nevt < limnevt || limnevt == -1 ) {
        // Read event / Exit
        skcread_( ilun, ierr );
        if ( ierr == 2 ) break;

        // Fill Cable Time Hits for primary cuts and selection
        fill_ct( sktqz_, CT, sktqz_.nqiskz, ctsize );
        
        // Check first event
        if ( nevt == 0 ) {
            watch( sktqz_.nqiskz );
            watch( ctsize );
            //for ( int i = 0; i < ctsize; ++i ) {
            //    printf( "%d  %f    %d  %f\n", sktqz_.icabiz[i], sktqz_.tiskz[i], CT[i].icabiz, CT[i].tiskz );
            //}

            // Mochizuki-san cut
            cut_RBN( CT, ctsize );
            watch( ctsize );

            // Read bonsai vertex
            vtx[0] = 0.;
            vtx[1] = 0.;
            vtx[2] = 0.;
            fill_sort_tau( CT, ctsize, vtx );

            // Find all n10 windows
            find_n10( CT, ctsize, wndbnd, wbsize );
            watch( wbsize );

            // DBG
            for ( int iwnd = 0; iwnd < wbsize; ++iwnd ) {
                n10 = (int)(wndbnd[iwnd].end-wndbnd[iwnd].bgn);
                watch( n10 );
                for ( int j = 0; j < n10; ++j )
                    printf( "%d  %d  %f\n", j, (wndbnd[iwnd].bgn+j)->icabiz, (wndbnd[iwnd].bgn+j)->tau );
            }

            // n200 cut
            cut_n200( CT, ctsize, wndbnd, wbsize );
            cout << "AFTER n200 cut" << endl;
            watch( wbsize );
            for ( int iwnd = 0; iwnd < wbsize; ++iwnd ) {
                n10 = (int)(wndbnd[iwnd].end-wndbnd[iwnd].bgn);
                watch( n10 );
                for ( int j = 0; j < n10; ++j )
                    printf( "%d  %d  %f\n", j, (wndbnd[iwnd].bgn+j)->icabiz, (wndbnd[iwnd].bgn+j)->tau );
            }

            // Doublet cut
            cut_doublet( CT, ctsize, wndbnd, wbsize );
            cout << "AFTER DOUBLET CUT" << endl;
            watch( wbsize );
            for ( int iwnd = 0; iwnd < wbsize; ++iwnd ) {
                n10 = (int)(wndbnd[iwnd].end-wndbnd[iwnd].bgn);
                watch( n10 );
                for ( int j = 0; j < n10; ++j )
                    printf( "%d  %d  %f\n", j, (wndbnd[iwnd].bgn+j)->icabiz, (wndbnd[iwnd].bgn+j)->tau );
            }
            
            // Compute Feature Vector
            for ( int iwnd = 0; iwnd < wbsize; ++iwnd ) {
                fill_feature_vector( wndbnd[iwnd], vtx, featvec[iwnd] );
            }
        }

        // Increment nevt
        ++nevt;
    }
    watch( nevt );

    // Close ZBS file
    skclosef_( ilun );

    return 0;
}


