



#include <cmath>
#include <geotnkC.h> 
#include <set>
#include "prm.h"
#include <string>
#include "TMath.h"
#include "/disk02/usr6/fiacob/ntag/swarm/Swarm.h"

#define watch( x ) std::cerr << (#x) << " = " << x << '\n'
#define dump( x ) std::cerr << x << '\n'
#define dbg( x ) std::cerr << "DBG " << x << '\n'

using namespace std;

// For old sbi_lentuple decomment
//extern "C" void trginfo_(float*);

const float TANKR = 1690.;
const float TANKZ = 1810.;

bool compare_cable( const CableTimeHit &x, const CableTimeHit &y ) {
    return x.icabiz < y.icabiz;
}



bool compare_time( const CableTimeHit &x, const CableTimeHit &y ) {
    return x.tiskz < y.tiskz;
}



bool compare_tau( const CableTimeHit &x, const CableTimeHit &y ) {
    return x.tau < y.tau;
}



bool is_negative_cable( const CableTimeHit &x ) {
    return x.icabiz < 0;
}



void fill_ct( const sktqz_common &insktqz, char *sbvec, CableTimeHit *ct, int &ctsize ) {
     for ( int i = 0; i < insktqz.nqiskz; ++i ) {
        ct[i].icabiz = insktqz.icabiz[i];
        ct[i].tiskz  = insktqz.tiskz[i];
        ct[i].sb     = sbvec[i];
        ct[i].flag_bonsvtx = 0;
    }
    ctsize = insktqz.nqiskz;
}



const int NMIS = 17;
const int MISCH[] = {
	7667,
	7686,
	8937,
	8980,
	9283,
	9312,
	9339,
	9362,
	9415,
	9434,
	9817,
	10685,
	10728,
	11031,
	11060,
	11087,
	11110
};

bool checkMiss( const int cab ) {
	for ( int i = 0; i < NMIS; ++i ) {
		if ( MISCH[i] == cab ) return true;
	}

	return false;
}



void merge_sheaft_ambe( const sktqz_common &shesktqz, const combad_common &shecombad, const int sheit0sk, sktqz_common &aftsktqz, const combad_common &aftcombad, const int aftit0sk ) {
	// Buffer container
	sktqz_common tmpsktqz;
	//int    nqiskz;
	//int    ihtiflz[30*MAXPM];
	//int    icabiz[30*MAXPM];
	//int    itiskz[30*MAXPM];
	//int    iqiskz[30*MAXPM];
	//float  tiskz[30*MAXPM];
	//float  qiskz[30*MAXPM];

	// SHE hits
	int cnt = 0;
	for ( int i = 0; i < shesktqz.nqiskz; ++i ) {
		// Only good hits
		if ( shesktqz.ihtiflz[i] & 0x02 && shesktqz.icabiz[i] <= MAXPM && !shecombad.ibad[shesktqz.icabiz[i]-1]	&& !checkMiss( shesktqz.icabiz[i] ) ) {
			tmpsktqz.ihtiflz[cnt] = shesktqz.ihtiflz[i];
			tmpsktqz.icabiz[cnt]  = shesktqz.icabiz[i];
			tmpsktqz.itiskz[cnt]  = shesktqz.itiskz[i];
			tmpsktqz.iqiskz[cnt]  = shesktqz.iqiskz[i];
			tmpsktqz.tiskz[cnt]   = shesktqz.tiskz[i];
			tmpsktqz.qiskz[cnt]   = shesktqz.qiskz[i];
			++cnt;
		}
    }

	// Save last SHE hits
	float last_she = tmpsktqz.tiskz[cnt-1];

	// Time between the offset of the triggers SHE and AFT
	float timediff = ( (float)aftit0sk - (float)sheit0sk ) / 1.92;

	// AFT hits
	for ( int i = 0; i < aftsktqz.nqiskz; ++i ) {
		// Only good hits
		if ( aftsktqz.ihtiflz[i] & 0x02 && aftsktqz.icabiz[i] <= MAXPM && !aftcombad.ibad[aftsktqz.icabiz[i]-1] && !checkMiss( aftsktqz.icabiz[i] ) && aftsktqz.tiskz[i] + timediff > last_she ) {
			tmpsktqz.ihtiflz[cnt] = aftsktqz.ihtiflz[i];
			tmpsktqz.icabiz[cnt]  = aftsktqz.icabiz[i];
			tmpsktqz.itiskz[cnt]  = aftsktqz.itiskz[i];
			tmpsktqz.iqiskz[cnt]  = aftsktqz.iqiskz[i];
			tmpsktqz.tiskz[cnt]   = aftsktqz.tiskz[i];
			tmpsktqz.qiskz[cnt]   = aftsktqz.qiskz[i];
			++cnt;
		}
    }
	// Complete buffer container with number of selected hits
	tmpsktqz.nqiskz = cnt;

	// Load buffer into aftsktqz (to be used outside this function)
	aftsktqz = tmpsktqz;
}



void fill_ct_she_nosbi( const sktqz_common &insktqz, const combad_common &incombad, CableTimeHit *ct, int &ctsize ) {
	// SHE hits
	ctsize = 0;
	for ( int i = 0; i < insktqz.nqiskz; ++i ) {
		//fprintf( stderr, "SHE %10X %10d %10d ", insktqz.ihtiflz[i], insktqz.icabiz[i], incombad.ibad[insktqz.icabiz[i]-1] );  // DBG
		// Only good hits
		if ( insktqz.ihtiflz[i] & 0x02 && insktqz.icabiz[i] <= MAXPM && !incombad.ibad[insktqz.icabiz[i]-1]	&& !checkMiss( insktqz.icabiz[i] ) ) {
	        ct[ctsize].icabiz = insktqz.icabiz[i];
			ct[ctsize].tiskz  = insktqz.tiskz[i];
			ct[ctsize].sb     = 'b';
			ct[ctsize].flag_bonsvtx = 0;

			//fprintf( stderr, "GOOD %10d %10d %15.2f", ctsize, ct[ctsize].icabiz, ct[ctsize].tiskz );  // DBG

			++ctsize;
		}
		//fprintf( stderr, "\n" );  // DBG
    }

	// DBG BGN
	fprintf( stderr, "*** fill_ct_she_nosbi BGN ***\n" );
	fprintf( stderr, "   Initial      Final       Diff\n" );
	fprintf( stderr, "%10d %10d %10d\n", insktqz.nqiskz, ctsize, insktqz.nqiskz - ctsize );
	fprintf( stderr, "*** fill_ct_she_nosbi END ***\n" );
	// DBG END

}



void fill_ct_sheaft_nosbi( const sktqz_common &insktqz, const combad_common &incombad, float last_she, int sheit0sk, int aftit0sk, CableTimeHit *ct, int &ctsize ) {
	// DBG
	int from_she = ctsize;

	// Time between the offset of the triggers SHE and AFT
	float timediff = ( (float)aftit0sk - (float)sheit0sk ) / 1.92;
	float flt_sheit0sk = (float) sheit0sk / 1.92;
	float flt_aftit0sk = (float) aftit0sk / 1.92;
	watch( flt_sheit0sk );
	watch( flt_aftit0sk );
	watch( timediff );

	// AFT hits
	for ( int i = 0; i < insktqz.nqiskz; ++i ) {
		//fprintf( stderr, "AFT %10X %10d %10d ", insktqz.ihtiflz[i], insktqz.icabiz[i], incombad.ibad[insktqz.icabiz[i]-1] );  // DBG

		// Only good hits
		if ( insktqz.ihtiflz[i] & 0x02 && insktqz.icabiz[i] <= MAXPM && !incombad.ibad[insktqz.icabiz[i]-1] && !checkMiss( insktqz.icabiz[i] ) && insktqz.tiskz[i] + timediff > last_she ) {
	        ct[ctsize].icabiz = insktqz.icabiz[i];
			ct[ctsize].tiskz  = insktqz.tiskz[i] + timediff;
			ct[ctsize].sb     = 'b';
			ct[ctsize].flag_bonsvtx = 0;

			//fprintf( stderr, "GOOD %10d %10d %15.2f", ctsize, ct[ctsize].icabiz, ct[ctsize].tiskz );  // DBG

			++ctsize;
		}
		//fprintf( stderr, "\n" );  // DBG
    }

	// DBG BGN
	fprintf( stderr, "*** fill_ct_sheaft_nosbi BGN ***\n" );
	fprintf( stderr, "  From SHE   Initial AFT  Final TOT   Diff\n" );
	fprintf( stderr, "%10d %10d %10d %10d\n", from_she, insktqz.nqiskz, ctsize, insktqz.nqiskz - ctsize );
	fprintf( stderr, "*** fill_ct_sheaft_nosbi END ***\n" );
	// DBG END
}



void fill_ct_rndmwidetrg_nosbi( const sktqz_common &insktqz, const combad_common &incombad, CableTimeHit *ct, int &ctsize ) {
	// RNDM_WIDE_TRG hits
	ctsize = 0;
	for ( int i = 0; i < insktqz.nqiskz; ++i ) {
		//fprintf( stderr, "RNDM_WIDE_TRG %10X %10d %10d ", insktqz.ihtiflz[i], insktqz.icabiz[i], incombad.ibad[insktqz.icabiz[i]-1] );  // DBG
		// Only good hits
		if ( insktqz.ihtiflz[i] & 0x02 && insktqz.icabiz[i] <= MAXPM && !incombad.ibad[insktqz.icabiz[i]-1]	&& !checkMiss( insktqz.icabiz[i] ) ) {
	        ct[ctsize].icabiz = insktqz.icabiz[i];
			ct[ctsize].tiskz  = insktqz.tiskz[i];
			ct[ctsize].sb     = 'b';
			ct[ctsize].flag_bonsvtx = 0;

			//fprintf( stderr, "GOOD %10d %10d %15.2f", ctsize, ct[ctsize].icabiz, ct[ctsize].tiskz );  // DBG

			++ctsize;
		}
		//fprintf( stderr, "\n" );  // DBG
    }

	// DBG BGN
	fprintf( stderr, "*** fill_ct_rndmwidetrg_nosbi BGN ***\n" );
	fprintf( stderr, "   Initial      Final       Diff\n" );
	fprintf( stderr, "%10d %10d %10d\n", insktqz.nqiskz, ctsize, insktqz.nqiskz - ctsize );
	fprintf( stderr, "*** fill_ct_rndmwidetrg_nosbi END ***\n" );
	// DBG END
}



void fill_ct_nosbi( const sktqz_common &insktqz, const combad_common &incombad, CableTimeHit *ct, int &ctsize ) {
	ctsize = 0;
	
	for ( int i = 0; i < insktqz.nqiskz; ++i ) {
		//fprintf( stderr, "AFT %10X %10d %10d ", insktqz.ihtiflz[i], insktqz.icabiz[i], incombad.ibad[insktqz.icabiz[i]-1] );  // DBG
		// In below if the condition "insktqz.ihtiflz[i] & 0x02" is missing
		// because insktqz.ihtiflz[i] == 0 for any MC event
		if ( insktqz.icabiz[i] <= MAXPM && !incombad.ibad[insktqz.icabiz[i]-1]	&& !checkMiss( insktqz.icabiz[i] ) ) {
			ct[ctsize].icabiz = insktqz.icabiz[i];
			ct[ctsize].tiskz  = insktqz.tiskz[i];
			ct[ctsize].sb     = 'b';
			ct[ctsize].flag_bonsvtx = 0;

			//fprintf( stderr, "GOOD %10d %10d %15.2f", ctsize, ct[ctsize].icabiz, ct[ctsize].tiskz );  // DBG
			++ctsize;
		}
		//fprintf( stderr, "\n" );  // DBG
    }

	// DBG BGN
	fprintf( stderr, "*** fill_ct_nosbi BGN ***\n" );
	fprintf( stderr, "   Initial      Final       Diff\n" );
	fprintf( stderr, "%10d %10d %10d\n", insktqz.nqiskz, ctsize, insktqz.nqiskz - ctsize );
	fprintf( stderr, "*** fill_ct_nosbi END ***\n" );
	// DBG END
}



/*
 * RBN = Repetitive Burst Noise
 * Considering one PMT, if two consecutive hits
 * have time difference < RBN_TIME_WIDTH
 * then are considered RBN, and are cut
 *
 * Above behaviour checked step-by-step at 7th July 2019
*/
const float RBN_TIME_WIDTH = 3000.;
void cut_RBN( CableTimeHit *ct, int &ctsize ) {
    // Sort PMT hits in increasing order of cable number
    sort( ct, ct + ctsize, compare_cable );

    // DBG
    //for ( int i = 0; i < ctsize; ++i ) {
    //    printf( "%d  %f\n", ct[i].icabiz, ct[i].tiskz );
    //}

    // Loop through each PMTs' hits and mark RBN hits
    // RBN hits marked with negative icabiz
    CableTimeHit *bound[2];
    bound[0] = bound[1] = ct;
    do {
        // Find next PMT range
        bound[0] = bound[1];
        bound[1] = upper_bound( bound[1], ct+ctsize, *bound[1], compare_cable );
        // DBG
        //printf( "%d   %d\n", int(bound[0]-ct), int(bound[1]-ct) );

        // Sort PMT range in time
        sort( bound[0], bound[1], compare_time );

        // DBG
        //CableTimeHit *it;
        //it = bound[0];
        //while ( it != bound[1] ) {
        //    printf( "%d %f\n", it->icabiz, it->tiskz );
        //    ++it;
        //}

        // Mark RBN
        // Loop in PMT range
        while ( bound[0] < bound[1]-1 ) {
            // If RBN mark icabiz as negative
            if ( (bound[0]+1)->tiskz - bound[0]->tiskz < RBN_TIME_WIDTH ) {
                (bound[0]+1)->icabiz = (bound[0]+1)->icabiz < 0 ? (bound[0]+1)->icabiz : -(bound[0]+1)->icabiz;
                bound[0]->icabiz = bound[0]->icabiz < 0 ? bound[0]->icabiz : -bound[0]->icabiz;
            }
            ++bound[0];
        }
    }
    while ( bound[1] != ct + ctsize );

    // DBG
    //for ( int i = 0; i < ctsize; ++i ) {
    //    printf( "%d  %f\n", ct[i].icabiz, ct[i].tiskz );
    //}

    // Remove element from range
    CableTimeHit *ctbgn = ct;
    CableTimeHit *ctend = ct + ctsize;
    ctend = remove_if( ctbgn, ctend, is_negative_cable );
    ctsize = (int)(ctend - ctbgn);

    // DBG
    //for ( int i = 0; i < ctsize; ++i ) {
    //    printf( "%d  %d  %f\n", i, ct[i].icabiz, ct[i].tiskz );
    //}
    
    // Re-sort in increasing time
    sort( ct, ct+ctsize, compare_time );

    // DBG
    //for ( int i = 0; i < ctsize; ++i ) printf( "%d  %d  %f\n", i, ct[i].icabiz, ct[i].tiskz );
}



// Akutsu-san style cut RBN (auxiliary function)
enum E_CBN_FLG{ eBFCHK=0, eKILLED, eSURVIVED };

void checkRBNHits(const vector<Float_t>& rawt, vector<UInt_t>& cbnflag)
{
	const float T_REDUC_WIDTH = 3000.;
	vector<Float_t> tim;
	vector<Int_t>	idx;
	vector<Int_t>	flg;
	
	Int_t n=(Int_t)rawt.size();

	tim.reserve( n );
	idx.reserve( n );
	for(Int_t i=0; i<n; i++){ tim.push_back( rawt[i] );	}

	// In increasing order
    TMath::Sort(n, &tim[0], &idx[0], kFALSE); 	for(Int_t i=0; i<n-1; i++)
	{
		if( tim[ idx[i+1] ] - tim[ idx[i] ]>T_REDUC_WIDTH )
		{
			if( cbnflag[ idx[i] ]!=eKILLED ){ cbnflag[ idx[i] ]=eSURVIVED; }
			cbnflag[ idx[i+1] ]	=eSURVIVED;
		}
		else
		{
			cbnflag[ idx[i] ]	=eKILLED;
			cbnflag[ idx[i+1] ]	=eKILLED;
		}
	}
}



// Akutsu-san style RBN cut
void doRBNReduction( CableTimeHit *ct, int &ctsize )
{
	int fNhits = ctsize;

	vector<Float_t> rawt;
	vector<Int_t>	cab;
	vector<Int_t>	idx;
	vector<Float_t> fTimRaw;
	vector<Int_t> fCabRaw;

	rawt.reserve( fNhits );
	cab.reserve( fNhits );
	idx.reserve( fNhits );
	fTimRaw.reserve( fNhits );
	fCabRaw.reserve( fNhits );


    for (Int_t i=0; i<fNhits; i++) 
	{
		rawt.push_back( ct[i].tiskz );
		cab.push_back( ct[i].icabiz );
    }

	// Sort PMT hits in increasing order of cable number
    TMath::Sort(fNhits, &cab[0], &idx[0], kFALSE);
	fTimRaw.clear();
	fCabRaw.clear();
    for (Int_t i=0; i<fNhits; i++)
	{
		fTimRaw.push_back( rawt[ idx[i] ] );
		fCabRaw.push_back( cab[ idx[i] ] );
	}


	// - Check time differences between hits for each PMT
	// - If time difference is less than ** T_REDUC_WIDTH **,
	//   then hits used for computing the difference are rearded
	//   as == Repetitive Burst Noise ==.
	rawt.clear();
	rawt.shrink_to_fit();

	Int_t	tmp		=-1,
			nhits	=-1;
	vector<UInt_t>	cbnr;

	vector<UInt_t>		fRBNFlag;
	fRBNFlag.reserve( fNhits );		
	for(Int_t i=0; i<fNhits; i++)
	{
		// First PMT having smallest cable number
		if( i==0 )
		{ 
			tmp=fCabRaw[i];			
			nhits=0;
		}	

		// Reached next cable
		if( fCabRaw[i]!=tmp )
		{
			if( nhits>1 )
			{
				checkRBNHits(rawt, cbnr);
				for(Int_t j=0; j<nhits; j++)
				{
					fRBNFlag.push_back( cbnr[j] );
				}
			}
			else{ fRBNFlag.push_back( eSURVIVED ); }

			tmp		=fCabRaw[i];
			nhits	=0;
			rawt.clear();	rawt.shrink_to_fit();
			cbnr.clear();	cbnr.shrink_to_fit();
		}	
		rawt.push_back( fTimRaw[i] );
		cbnr.push_back( eBFCHK );
		nhits+=1;	
	}

	// For the last PMT
	if( nhits>1 )
	{
		checkRBNHits(rawt, cbnr);
		for(Int_t j=0; j<nhits; j++){ fRBNFlag.push_back( cbnr[j] ); }
	}
	else{ fRBNFlag.push_back( eSURVIVED ); }


	if( fNhits!=(Int_t)fRBNFlag.size() )
	{
		cout<<" [ERROR] HitsManager::doRBNRedution "  <<endl;
		cout<<"   - fRBNFlag.size() != fNhits " 	  <<endl;
		cout<<" -> EXIT "							  <<endl;
		exit( -1 );
	}

	// Refill non-RBR hits only
	rawt.clear();	rawt.shrink_to_fit();
	cab.clear();	cab.shrink_to_fit();
	idx.clear();	idx.shrink_to_fit();
	nhits=0;
	
	for(Int_t i=0; i<fNhits; i++)
	{
		if( fRBNFlag[i]==eSURVIVED )
		{
			rawt.push_back( fTimRaw[i] );
			cab.push_back( fCabRaw[i] );
			nhits+=1;
		}
	}

	cout<<" [INFO] HitsManager::doRBNReduction " <<endl;
	cout<<"   - Before # hits :" << fNhits 		 <<
		  "; After # hits :"	 << nhits  		 <<endl;


	// Sort survived hits in increasing order of raw hit time
	idx.reserve( nhits );
    TMath::Sort(nhits, &rawt[0], &idx[0], kFALSE);
	fTimRaw.clear();
	fCabRaw.clear();
	for(Int_t i=0; i<nhits; i++)
	{
		fTimRaw.push_back( rawt[ idx[i] ] );
		fCabRaw.push_back( cab[ idx[i] ] );
	}

	fNhits=-1;
	fNhits=nhits;	
	fRBNFlag.clear();
	fRBNFlag.shrink_to_fit();
	
	// fiacob, go back to ct and ctsize
	ctsize = fNhits;
	for ( int i = 0; i < ctsize; ++i ) {
		ct[i].icabiz = fCabRaw[i];
		ct[i].tiskz = fTimRaw[i];
		//float tau;  // Tau sort done later
		ct[i].sb = 'b';  // fill_ct_nosbi convention
		ct[i].flag_bonsvtx = 0;  // fill_ct_nosbi convention
	}
}








// Verified behaviour at 7th July 2019
const float CWATER = 299792458. * 1e-7 / 1.33;
void fill_sort_tau( CableTimeHit *ct, int ctsize, float *vtx ) {
    int cable;
    float tof;
    for ( int i = 0; i < ctsize; ++i ) {
        tof = 0.;
        cable = ct[i].icabiz;
        for ( int j = 0; j < 3; ++j ) 
            tof += ( vtx[j] - geopmt_.xyzpm[cable-1][j] )*( vtx[j] - geopmt_.xyzpm[cable-1][j] );
        tof = sqrt( tof ) / CWATER;

        ct[i].tau = ct[i].tiskz - tof;
    }

    // DBG
    //for ( int i = 0; i < ctsize; ++i )
    //    printf( "%d  %d  %f  %f\n", i, ct[i].icabiz, ct[i].tiskz, ct[i].tau );

    // Sort tau in increasing order
    sort( ct, ct + ctsize, compare_tau );

    // DBG
    //for ( int i = 0; i < ctsize; ++i )
    //    printf( "%d  %d  %f  %f\n", i, ct[i].icabiz, ct[i].tiskz, ct[i].tau );
}




CableTimeHit* find_n10_end( CableTimeHit *first, CableTimeHit *last ) {
    CableTimeHit *it = first;
    while ( it != last && it->tau - first->tau < 10. ) ++it;

    return it;
}


/*
 * Find all n10 window bounds
 * Checked behaviour at 8th July 2019
*/ 
const int N10_LO_CUT = 7;
const int N10_HI_CUT = 50;
const CableTimeHit TAU_BGN_NTAG = {
    0,
    0,
    18000.//20000.  //18000.
};



void find_n10( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize ) {
    // Reset number of windows
    wbsize = 0;

    // Loop through event
    CableTimeHit *eventbgn = ct;
    CableTimeHit *eventend = ct + ctsize;
    CableTimeHit *eventbgn_ntag = upper_bound( eventbgn, eventend, TAU_BGN_NTAG, compare_tau ); 
    CableTimeHit *bound[2] = { eventbgn_ntag, eventbgn_ntag };
    int n10;
    do {
        // Find 10 nsec window [bound0, bound1[
        bound[1] = find_n10_end( bound[0], eventend );

        // Save if necessary
        n10 = (int)(bound[1] - bound[0]);
        if ( N10_LO_CUT <= n10 && n10 <= N10_HI_CUT ) {
            wndbnd[wbsize].bgn = bound[0];
            wndbnd[wbsize].end = bound[1];
            ++wbsize;
        }

        // DBG
        //printf( "n10 = %d\n", n10 );
        //for ( int i = 0; i < n10; ++i ) {
        //    printf( "%d  %d  %f\n", i, (bound[0]+i)->icabiz, (bound[0]+i)->tau );
        //}

        // Consider next hit
        ++bound[0];
    }
    while ( bound[1] != eventend );
}



WindowBounds find_n200bound( CableTimeHit *center, CableTimeHit *first, CableTimeHit *last ) { 
    WindowBounds n200bound;
    CableTimeHit *it;
    
    // Open 100 nsec to the right of t0
    it = center;
    while ( it != last && it->tau - center->tau < 100. ) ++it;
    n200bound.end = it;

    // Open 100 nsec to the left of t0
    it = center;
    while ( it != first-1 && center->tau - it->tau < 100. ) --it;
    ++it;
    n200bound.bgn = it;

    return n200bound;
}


bool is_bgnend_same( const WindowBounds &x ) {
    return x.bgn == x.end;
}


/*
 * Cut the n10 windows, whose surrounding n200 window exceeds 200 hits
 * Checked behaviour on 8th July 2019
*/
const int N200_CUT = 200;
void cut_n200( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize ) {
    CableTimeHit *eventbgn = ct;
    CableTimeHit *eventend = ct + ctsize;
    CableTimeHit *eventbgn_ntag = upper_bound( eventbgn, eventend, TAU_BGN_NTAG, compare_tau );
    WindowBounds n200bound;
    int n200;

    // Loop on considered windows
    for ( int iwnd = 0; iwnd < wbsize; ++iwnd ) {
        // Find n200 window
        n200bound = find_n200bound( wndbnd[iwnd].bgn, eventbgn_ntag, eventend );

        // Compute n200
        n200 = (int)(n200bound.end - n200bound.bgn);

        // Mark n10 windows as bad if necessary (BAD ---> bgn == end)
        if ( n200 > N200_CUT ) {
            wndbnd[iwnd].end = wndbnd[iwnd].bgn;
        }

        // DBG
        //printf( "n10 window number %d, the n200 window has %d hits\n", iwnd, n200 );
        //for ( int j = 0; j < n200; ++j ) {
        //    printf( "%d  %d  %f\n", j, (n200bound.bgn+j)->icabiz, (n200bound.bgn+j)->tau );
        //}
	
	
    }
    
    // Remove element from range
    WindowBounds *wbbgn = wndbnd;
    WindowBounds *wbend = wndbnd + wbsize;
    wbend = remove_if( wbbgn, wbend, is_bgnend_same );
    wbsize = (int)(wbend - wbbgn);
}






bool compare_window_hit( const WindowBounds &x, const WindowBounds &y ) {
    int nx = (int)( x.end - x.bgn );
    int ny = (int)( y.end - y.bgn );
    return nx < ny;
}



/*
 * Daisy chains n10 windows as close as 20 nsec in t0
 * and chooses the one with highest number of hits
 *
 * Checked behaviour on 9th July 2019
*/
const float TAU_CHAINED_WIDTH = 20.;
void cut_doublet( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize ) {
    // Find those daisy-chained within 20 nsec
    // Loop on the n10 windows
    WindowBounds *wbbgn = wndbnd;
    WindowBounds *wbend = wndbnd + wbsize;
    WindowBounds *wbit[2] = { wbbgn, wbbgn };
    WindowBounds *wbsave;
    WindowBounds *wbdummy;
    WindowBounds *wbdbg;  // DBG
    while( wbit[1] != wbend ) {
        // Find all those chained, they will stay in range [wbit0, wbit1[
        while ( wbit[1] + 1 != wbend && (wbit[1]+1)->bgn->tau - wbit[1]->bgn->tau < TAU_CHAINED_WIDTH ) ++wbit[1];
        ++wbit[1];

        // DBG
        //printf( "CHAIN\n" );
        //wbdbg = wbit[0];
        //while ( wbdbg != wbit[1] ) {
        //    for ( int idbg = 0; idbg < (int)(wbdbg->end-wbdbg->bgn); ++idbg )
        //        printf( "%f  ", ((wbdbg->bgn)+idbg)->tau );
        //    printf( "\n" );
        //    ++wbdbg;
        //}


        // Find the best among the chained
        wbsave = max_element( wbit[0], wbit[1], compare_window_hit );

        // DBG
        //printf( "BEST IS NUMBER = %d\n", (int)(wbsave-wbit[0]) );
        
        // Mark the others
        wbdummy = wbit[0];
        while ( wbdummy != wbit[1] ) {
            if ( wbdummy != wbsave ) wbdummy->end = wbdummy->bgn;
            ++wbdummy;
        }
        
        // Move on to the next possible chain
        wbit[0] = wbit[1];
    }

    // Remove the marked ones
    // Remove element from range
    wbbgn = wndbnd;
    wbend = wndbnd + wbsize;
    wbend = remove_if( wbbgn, wbend, is_bgnend_same );
    wbsize = (int)(wbend - wbbgn);
}



int getUSNhitsXX( CableTimeHit *ct, int ctsize, int sidx, float twid ) {
// Compute num. of hits within timing width "twid".
// Only hits in upper side in terms of timing are
// counted w.r.t the first hit having the index
// "sidx"

    int   i = -1,
		  n = -1;
	i = sidx;
	n = ctsize;
    while ( 1 ) {
		i++;
		if( ( i > n-1 ) || ( abs( ct[i].tau - ct[sidx].tau ) > twid ) ) break;
    }

    return abs( i - sidx );
}



int getBSNhitsXX( CableTimeHit *ct, int ctsize, float twin, float tcenter ) {
// Compute num. of hits within timing width "twin" 
// Hits are searched in both before and after sides 
// w.r.t the timing "tcenter". 
    int nxx = -1,
		nhits = -1;
	nxx = 0;
	nhits = ctsize;
    for ( int i = 0; i < nhits; i++ ) {
        if ( ct[i].tau < tcenter - twin/2. ){ continue; }
        if ( ct[i].tau > tcenter + twin/2. ){ break; }
        ++nxx;
    }
    return nxx;
}



// Only for 1.3 usec of AMBE
int getBSNhitsXX_1300AMBE( CableTimeHit *ct, int ctsize, float tcenter ) {
    int nxx = -1,
		nhits = -1;
	nxx = 0;
	nhits = ctsize;
    for ( int i = 0; i < nhits; i++ ) {
        if ( ct[i].tau < tcenter - 1100. ){ continue; }
        if ( ct[i].tau > tcenter +  200. ){ break; }
        ++nxx;
    }
    return nxx;
}



// Akutsu-san style Primary Selection
// Arguments:
// ct     = hits of the event (previously filled with fill_ct)
// ctsize = number of hits
// pvx    = primary vertex
// wb     = window bounds referring to ct array (filled in this function)
// wbsize = number of windows (filled in this function)
void searchCandidates( CableTimeHit *ct, int ctsize, float *pvx, WindowBounds *wb, int &wbsize, int *n200vec  ) {
	CableTimeHit _firsthit;
    _firsthit.icabiz = -1;
    _firsthit.tiskz = -1.;
    _firsthit.tau = -1.;
    _firsthit.sb = 'n';
    _firsthit.flag_bonsvtx = -1;

    bool     pre_t0_set = false;
    float    t0	 = -1.,
			 tds = -1.,
			 nvtxmct[3] = {};
	int   	 i = -1,
			 ngc = 0.,
			 tindex,
			 N10i = 0,
			 N10 = 0,
			 n200 = 0,
			 Nhits = -1,
			 Ncand = 0;

    //int n1300;  // Only for AMBE
    //const int N1300CUT = 975;  // Only for AMBE


	// Apply RBNR technique
    //cut_RBN( ct, ctsize ); // fiacob-style commented on 17mar2020 ambe AMBE
	doRBNReduction( ct, ctsize ); // akutsu-san-style


	// Calculate t-tof subtracted by primary vertex
	fill_sort_tau( ct, ctsize, pvx ); 	

	// Search for PMT hits clusters
	Nhits = ctsize;
    const float _tLow = 5000.;
    //const float _tHigh = 600000.;  // Original value
	const float _tHigh = 514000.;  // True situation
	//const float _tHigh = 300000.;  // Am/Be primary systematics estimation and activity 075504 evaluation
	//const float _tHigh = 819000.;  // Am/Be secondary systematics estimation
    const float T0TH = 18.;
    const int N10TH = 7;
    const int MAXN10 = 50;
    const float DPREVT0 = 20.;
    //    const int N200CUT = 100; //CPM 190121 CHANGED N200CUT TO 140 FOR GD ANALYSIS
    const int N200CUT = 140; 
    const int MAXNP = 500;
    for ( i = 0; i < Nhits; i++ ) {
		if ( _firsthit.icabiz == -1 )	  { _firsthit = ct[i]; }
		if ( ct[i].tau < _tLow )	  { continue; }
		if ( ct[i].tau > _tHigh-10. ) { continue; }


		N10i = getUSNhitsXX( ct, ctsize, i, 10. );
        if( N10i < N10TH || N10i > MAXN10 ){ continue; }

        // Store info of previous peak when encountering a new peak.
        // We regard time diff of t0 of two N10 peaks greater than
        // 20 ns as two seperated peaks.
        // dt is t0 of previous N10 peak
        if ( pre_t0_set && ct[i].tau - t0 > DPREVT0 ) { 
			if ( N10 >= N10TH && n200 < N200CUT	&& t0 / 1000. - 1 > T0TH ) {// Original one (to be restored)	
            //if ( N10 >= N10TH && n200 < N200CUT   && t0 / 1000. - 1 > T0TH && n1300 < N1300CUT ) {  // AMBE
                wb[Ncand].bgn = ct + tindex;
                wb[Ncand].end = ct + tindex + N10;
				++Ncand;

				if ( Ncand >= MAXNP - 1 ) {
                    cerr << " ---> ERROR in function " << __func__ << " Ncand >= MAXNP - 1" << endl;
                    exit( EXIT_FAILURE );
                }
			}
			N10 = 0;
        }

        if ( N10i <= N10 ){ continue; }
		//select a better peak in this 20ns window.
        N10			= N10i;
		tindex		= i;
        t0			= ct[i].tau;
		n200		= getBSNhitsXX( ct, ctsize, 200., t0+5. ); 
        //n1300       = getBSNhitsXX_1300AMBE( ct, ctsize, t0+5. ); // Only for AMBE
        pre_t0_set	= true;
    }
 


    // Fill the last peak. IMPORTANT!!!
    if( N10 > 0	&& n200 < N200CUT && t0 / 1000. - 1 > T0TH ) { // Original ( to be restored )
    //if ( N10 > 0  && n200 < N200CUT && t0 / 1000. - 1 > T0TH && n1300 < N1300CUT ) {  // AMBE
        // Save result to array
		if( N10 >= N10TH ) {
            wb[Ncand].bgn = ct + tindex;
            wb[Ncand].end = ct + tindex + N10;
	    n200vec[Ncand] = n200; //190121 CPM save n200
			Ncand += 1;
			N10 = 0;
		}
	}



	wbsize = Ncand;
}




//=========================
//
// GLOBAL TAURMS FUNCTION
//
//=========================
namespace rms {
int nhit;
int cable[100];
float t[100];
float tau[100];

float taurms( float *x ) {
    float tof;
    for ( int i = 0; i < nhit; ++i ) {
        tof = 
        (geopmt_.xyzpm[cable[i]-1][0]-x[0]) * (geopmt_.xyzpm[cable[i]-1][0]-x[0]) +
        (geopmt_.xyzpm[cable[i]-1][1]-x[1]) * (geopmt_.xyzpm[cable[i]-1][1]-x[1]) +
        (geopmt_.xyzpm[cable[i]-1][2]-x[2]) * (geopmt_.xyzpm[cable[i]-1][2]-x[2]);
        tof = sqrt( tof ) / CWATER;
        tau[i] = t[i] - tof;
    }

    // Compute mean value
    float taumean = 0.;
    for ( int i = 0; i < nhit; ++i ) taumean += tau[i];
    taumean /= (float) nhit;

    // Compute RMS
    float taurms = 0.;
    for ( int i = 0; i < nhit; ++i ) taurms += ( tau[i] - taumean ) * ( tau[i] - taumean );
    taurms /= (float) nhit;
    taurms = sqrt( taurms );

    // DBG
    //for ( int i = 0; i < nhit; ++i ) printf( "%d  %f\n", i, tau[i] );
    //printf( "%s  %f\n", "mean", taumean );
    //printf( "%s  %f\n", "trms", taurms );

    return taurms;
}

}

// END OF RMS NAMESPACE




void cart2sphe( float *u ) {
    u[3] = sqrt( u[0]*u[0] + u[1]*u[1] + u[2]*u[2] );
    u[4] = atan2( sqrt( u[0]*u[0] + u[1]*u[1] ), u[2] );
    u[5] = atan2( u[1], u[0] );
}

float computedist( float *u, float *v ) {
    float num = u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
    float den = ( u[0]*u[0] + u[1]*u[1] + u[2]*u[2] ) * ( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    den = sqrt( den );
    float wannacos = num / den;
    if ( 1. < abs( wannacos ) && abs( wannacos ) < 1.1 ) {
        wannacos = wannacos > 0 ? 1. : -1.;
    }

    return acos( wannacos );
}

bool spheremean_dist_compare( const Hit &a, const Hit &b ) { return a.spheremean_dist < b.spheremean_dist; }



void Window::init( CableTimeHit *first, CableTimeHit *last, float *_vtx ) {
    // Save vertex
    vtx[0] = _vtx[0];
    vtx[1] = _vtx[1];
    vtx[2] = _vtx[2];

    // General purpose info
    nhit = last - first;
    tauwidth = (first + nhit - 1)->tau - first->tau;

    // Loop through hits
    int cable;
    //printf( "*** WINDOW DBG ***\n" );
    //printf( "vtx[0-2] = %f  %f  %f\n", vtx[0], vtx[1], vtx[2] );
    for ( int i = 0; i < nhit; ++i ) {
        // Cable
        cable = first[i].icabiz;
        hit[i].cable = cable;

        // Time
        hit[i].t = first[i].tiskz;
        hit[i].tau = first[i].tau;

        // Coordinate
        //watch( cable );
        //watch( geopmt_.xyzpm[cable-1][0] );
        //watch( hit[i].co[0] );
        hit[i].co[0] = geopmt_.xyzpm[cable-1][0];
        hit[i].co[1] = geopmt_.xyzpm[cable-1][1];
        hit[i].co[2] = geopmt_.xyzpm[cable-1][2];
        cart2sphe( hit[i].co );

        // Vertex-subtracted coordinates
        hit[i].vco[0] = hit[i].co[0] - vtx[0];
        hit[i].vco[1] = hit[i].co[1] - vtx[1];
        hit[i].vco[2] = hit[i].co[2] - vtx[2];
        cart2sphe( hit[i].vco );

        // Vertex-subtracted normalized coordinates
        hit[i].nvco[0] = hit[i].vco[0] / hit[i].vco[3];
        hit[i].nvco[1] = hit[i].vco[1] / hit[i].vco[3];
        hit[i].nvco[2] = hit[i].vco[2] / hit[i].vco[3];
        hit[i].nvco[3] = hit[i].vco[3] / hit[i].vco[3];
        hit[i].nvco[4] = hit[i].vco[4];
        hit[i].nvco[5] = hit[i].vco[5];
        
        // DBG
        // hit[i].nvco[4] = hit[i].vco[4];
        // hit[i].nvco[5] = hit[i].vco[5];
        //printf( "co[0-5] = %f  %f  %f  %f  %f  %f\n", hit[i].co[0], hit[i].co[1], hit[i].co[2], hit[i].co[3], hit[i].co[4], hit[i].co[5] );
        //printf( "vco[0-5] = %f  %f  %f  %f  %f  %f\n", hit[i].vco[0], hit[i].vco[1], hit[i].vco[2], hit[i].vco[3], hit[i].vco[4], hit[i].vco[5] );
        //printf( "nvco[0-5] = %f  %f  %f  %f  %f  %f\n", hit[i].nvco[0], hit[i].nvco[1], hit[i].nvco[2], hit[i].nvco[3], hit[i].nvco[4], hit[i].nvco[5] );

        // Tdelta
        if ( i < nhit - 1 )
            hit[i].tdelta = first[i+1].tau - first[i].tau;

        // Stau
        hit[i].stau = first[i].tau - first[0].tau;

        // Signal / Background info
        hit[i].sb = first[i].sb;


        // DBG
        //printf( "%d  %d  %f  %f  %f  %f  %f  %f  %f  %f\n", i, hit[i].cable, hit[i].t, hit[i].co[0], hit[i].co[1], hit[i].co[2], hit[i].vco[0], hit[i].vco[1], hit[i].vco[2], hit[i].stau );
    }
}



void Window::init_variant( vector<Int_t> &fCab, vector<Float_t> &fTim, vector<Float_t> &fTau, int _nhit, float *_vtx ) {
    // Save vertex
    vtx[0] = _vtx[0];
    vtx[1] = _vtx[1];
    vtx[2] = _vtx[2];

    // General purpose info
    nhit = _nhit;
    tauwidth = fTau[nhit-1] - fTau[0];

    // Loop through hits
	int cable;
    //printf( "*** WINDOW DBG ***\n" );
    //printf( "vtx[0-2] = %f  %f  %f\n", vtx[0], vtx[1], vtx[2] );
    for ( int i = 0; i < nhit; ++i ) {
        // Cable
		cable = fCab[i];
        hit[i].cable = cable;

        // Time
        hit[i].t = fTim[i];
        hit[i].tau = fTau[i];

        // Coordinate
        //watch( cable );
        //watch( geopmt_.xyzpm[cable-1][0] );
        //watch( hit[i].co[0] );
        hit[i].co[0] = geopmt_.xyzpm[cable-1][0];
        hit[i].co[1] = geopmt_.xyzpm[cable-1][1];
        hit[i].co[2] = geopmt_.xyzpm[cable-1][2];
        cart2sphe( hit[i].co );

        // Vertex-subtracted coordinates
        hit[i].vco[0] = hit[i].co[0] - vtx[0];
        hit[i].vco[1] = hit[i].co[1] - vtx[1];
        hit[i].vco[2] = hit[i].co[2] - vtx[2];
        cart2sphe( hit[i].vco );

        // Vertex-subtracted normalized coordinates
        hit[i].nvco[0] = hit[i].vco[0] / hit[i].vco[3];
        hit[i].nvco[1] = hit[i].vco[1] / hit[i].vco[3];
        hit[i].nvco[2] = hit[i].vco[2] / hit[i].vco[3];
        hit[i].nvco[3] = hit[i].vco[3] / hit[i].vco[3];
        hit[i].nvco[4] = hit[i].vco[4];
        hit[i].nvco[5] = hit[i].vco[5];
        
        // DBG
        // hit[i].nvco[4] = hit[i].vco[4];
        // hit[i].nvco[5] = hit[i].vco[5];
        //printf( "co[0-5] = %f  %f  %f  %f  %f  %f\n", hit[i].co[0], hit[i].co[1], hit[i].co[2], hit[i].co[3], hit[i].co[4], hit[i].co[5] );
        //printf( "vco[0-5] = %f  %f  %f  %f  %f  %f\n", hit[i].vco[0], hit[i].vco[1], hit[i].vco[2], hit[i].vco[3], hit[i].vco[4], hit[i].vco[5] );
        //printf( "nvco[0-5] = %f  %f  %f  %f  %f  %f\n", hit[i].nvco[0], hit[i].nvco[1], hit[i].nvco[2], hit[i].nvco[3], hit[i].nvco[4], hit[i].nvco[5] );

        // Tdelta
        if ( i < nhit - 1 )
            hit[i].tdelta = fTau[i+1] - fTau[i];

        // Stau
        hit[i].stau = fTau[i] - fTau[0];

        // Signal / Background info
        hit[i].sb = 'b'; // nosbi convention ;first[i].sb;


        // DBG
        //printf( "%d  %d  %f  %f  %f  %f  %f  %f  %f  %f\n", i, hit[i].cable, hit[i].t, hit[i].co[0], hit[i].co[1], hit[i].co[2], hit[i].vco[0], hit[i].vco[1], hit[i].vco[2], hit[i].stau );
    }
}




/*
 * Return value:
 *   true = ok
 *   flase = spheremean norm is zero
 *
 * Computed value:
 *   normspheremean
 *   spheremean on vertex-subtracted sphere
*/
void Window::init_spheremean() {
    // Compute un-normalized spheremean
    for ( int i = 0; i < 3; ++i ) {
        spheremean[i] = 0.;
        for ( int ihit = 0; ihit < nhit; ++ihit ) {
            spheremean[i] += hit[ihit].vco[i] / hit[ihit].vco[3];
        }
    }

    // Compute norm of spheremean
    spheremean[3] = 0.;
    for ( int i = 0; i < 3; ++i ) spheremean[3] += spheremean[i]*spheremean[i];
    spheremean[3] = sqrt( spheremean[3] );
    
    // Return false (error state) in case norm of spheremean is zero
    if ( spheremean[3] == 0. ) {
        spheremeanflag = false;
        return;
    }

    // Compute spheremean if possible
    for ( int i = 0; i < 3; ++i ) spheremean[i] /= spheremean[3];
    for ( int i = 0; i < 3; ++i ) {
        spheremean[4] = atan2( sqrt( spheremean[0]*spheremean[0] + spheremean[1]*spheremean[1] ), spheremean[2] );
        spheremean[5] = atan2( spheremean[1], spheremean[0] );
    }

    // Return true (ok state) in case spheremean is computed successfully
    spheremeanflag = true;
    return;
}



void Window::init_distancevector() {
    // Compute distance from spheremean
    // Ordering is still in tau ( as always... )
    for ( int i = 0; i < nhit; ++i ) {
        hit[i].spheremean_dist = computedist( spheremean, hit[i].vco );
    }
}


/*
void Fitter::init_vtx( const Window &w, float *vtx ) {
    nhit = w.nhit;
    for ( int i = 0; i < nhit; ++i ) guesst[i] = w.hit[i].t;
    for ( int i = 0; i < 3; ++i ) guessvtx[i] = vtx[i];
}
*/

void cube_sampler( float *side, float *x ) {
    float u;
    u = gRandom->Rndm(); // [0, 1]
    x[0] = u * ( side[1] - side[0] ) + side[0];  // [side[0], side[1]]
    
    u = gRandom->Rndm(); // [0, 1]
    x[1] = u * ( side[3] - side[2] ) + side[2];  // [side[2], side[3]]
    
    u = gRandom->Rndm(); // [0, 1]
    x[2] = u * ( side[5] - side[4] ) + side[4];  // [side[4], side[5]] 
}

void cylinder_sampler( const float radius, const float semiheight, float *x ) {
    float u;
    do {
       u = gRandom->Rndm();
       x[0] = (2.*u - 1.) * radius;
       u = gRandom->Rndm();
       x[1] = (2.*u - 1.) * radius;
    }
    while( x[0]*x[0] + x[1]*x[1] > radius*radius );

    u = gRandom->Rndm();
    x[2] = (2.*u - 1.) * semiheight;
}

bool is_inside_sk( const float *x ) {
    const float R = 1690.;
    const float H2 = 1810.;
    return ( x[0]*x[0]+x[1]*x[1] < R*R && abs( x[2] ) < H2 );
}
void sk_sampler( float *x ) {
    const float radius = 1690.;
    const float semiheight = 1810.;
    float u;
    do {
       u = gRandom->Rndm();
       x[0] = (2.*u - 1.) * radius;
       u = gRandom->Rndm();
       x[1] = (2.*u - 1.) * radius;
    }
    while( x[0]*x[0] + x[1]*x[1] > radius*radius );

    u = gRandom->Rndm();
    x[2] = (2.*u - 1.) * semiheight;
}



// vtx in centimeter, tau NOT sorted
float Fitter::compute_taurms( const Window &w, float *vtx ) {
    int cable;
    float tof;
    float tau[100];
    for ( int i = 0; i < w.nhit; ++i ) {
        cable = w.hit[i].cable;
        tof = 
        (geopmt_.xyzpm[cable-1][0]-vtx[0]) * (geopmt_.xyzpm[cable-1][0]-vtx[0]) +
        (geopmt_.xyzpm[cable-1][1]-vtx[1]) * (geopmt_.xyzpm[cable-1][1]-vtx[1]) +
        (geopmt_.xyzpm[cable-1][2]-vtx[2]) * (geopmt_.xyzpm[cable-1][2]-vtx[2]);
        tof = sqrt( tof ) / CWATER;
        tau[i] = w.hit[i].t - tof;
    }

    // Compute mean value
    float taumean = 0.;
    for ( int i = 0; i < w.nhit; ++i ) taumean += tau[i];
    taumean /= (float) w.nhit;

    // Compute RMS
    float taurms = 0.;
    for ( int i = 0; i < w.nhit; ++i ) taurms += ( tau[i] - taumean ) * ( tau[i] - taumean );
    taurms /= (float) w.nhit;
    taurms = sqrt( taurms );

    // DBG
    //for ( int i = 0; i < nhit; ++i ) printf( "%d  %f\n", i, tau[i] );
    //printf( "%s  %f\n", "mean", taumean );
    //printf( "%s  %f\n", "trms", taurms );

    return taurms;
}



void Fitter::sample_taurms( const Window &w, const float radius, const float semiheight, int nsample, float *stat ) {
    float vtx[3];
    float taurms[10000];
    TH1D htaurms( "htaurms", "htaurms", 100, 0, 100 );

    float taurms_min[4] = { 9999, 9999, 9999, 9999 };

    // DBG
    //TFile *frms = new TFile( "frms.root", "RECREATE" );
    //TTree *trms = new TTree( "trms", "trms" );
    //TBranch *brrms = trms->Branch( "brrms", &bufrms, "vtx0/F:vtx1:vtx2:val" );

    // Sample in the cylinder
    for ( int i = 0; i < nsample; ++i ) {
        cylinder_sampler( radius, semiheight, vtx );
        taurms[i] = compute_taurms( w, vtx );

        //DBG
        //printf( "%f %f %f %f\n", vtx[0], vtx[1], vtx[2], taurms[i] );

        if ( taurms[i] < taurms_min[3] ) {
            taurms_min[0] = vtx[0];
            taurms_min[1] = vtx[1];
            taurms_min[2] = vtx[2];
            taurms_min[3] = taurms[i];
        }

        htaurms.Fill( taurms[i] );

        // DBG
        //bufrms.vtx0 = vtx[0];
        //bufrms.vtx1 = vtx[1];
        //bufrms.vtx2 = vtx[2];
        //bufrms.val = taurms;

        //trms->Fill();
    }

    //sample_mean_stddev( taurms, nsample, stat );

    stat[0] = htaurms.GetMean();
    stat[1] = htaurms.GetRMS();
    stat[2] = htaurms.GetSkewness();
    stat[3] = htaurms.GetKurtosis();
    double quantile[3];
    double probsum[3] = { 0.25, 0.50, 0.75 };
    //probsum[0] = 0.25; probsum[1] = 0.50; probsum[2] = 0.75;
    htaurms.GetQuantiles( 3, quantile, probsum );
    stat[4] = quantile[0];  // first quartile
    stat[5] = quantile[1];  // median
    stat[6] = quantile[2];  // thrid quartile
    stat[7] = quantile[2] - quantile[0];  // inter-quartile range

    stat[8] = taurms_min[0];  // minx
    stat[9] = taurms_min[1];  // miny
    stat[10] = taurms_min[2];  // minz
    stat[11] = taurms_min[3];  // min val taurms
    //trms->Write();
    //frms->Close();
    //cerr << "frms written" << '\n';
}



bool is_bonsvtx_marked( const CableTimeHit &x ) { return x.flag_bonsvtx == 1; }

CableTimeHit* bwd_taufind( CableTimeHit *ct, int ctsize, CableTimeHit *start, float width ) {
    CableTimeHit *it = start;
    CableTimeHit *ctendr = ct - 1;
    while ( it != ctendr && start->tau - it->tau < width ) --it;
    ++it;

    return it;
}

CableTimeHit *fwd_taufind( CableTimeHit *ct, int ctsize, CableTimeHit *start, float width ) {
    CableTimeHit *it = start;
    CableTimeHit *ctend = ct + ctsize;
    while ( it != ctend && it->tau - start->tau < width ) {
        //printf( "%s  %d  %f\n", __func__, (int)(it - start), it->tau );  // DBG
        ++it;
    }

    return it;
}

void surround_n10bonsvtx( CableTimeHit *ct_bonsvtx, int ctbsize, WindowBounds n10bvx, CableTimeHit *surround, int &surroundsize ) {
    // Find 1.3 usec window centered in n10bvx
    const float SURROUND_WIDTH_BVX = 1300.;  // Typically surround window has about 70 hits
    WindowBounds surbnd;  // surround bounds
    surbnd.bgn = bwd_taufind( ct_bonsvtx, ctbsize, n10bvx.bgn, SURROUND_WIDTH_BVX / 2. );
    surbnd.end = fwd_taufind( ct_bonsvtx, ctbsize, n10bvx.bgn, SURROUND_WIDTH_BVX / 2. );
    
    // Copy 1.3 usec window
    surroundsize = surbnd.end - surbnd.bgn;
    for ( int i = 0; i < surroundsize; ++i ) surround[i] = surbnd.bgn[i];

    // Mark n10bvx in surround window
    int n10size = n10bvx.end - n10bvx.bgn;
    int n10offset = n10bvx.bgn - surbnd.bgn;
    for ( int i = 0; i < n10size; ++i ) {
        surround[i + n10offset].flag_bonsvtx = 1; 
    }
}



CableTimeHit* find_medoid( CableTimeHit *first, CableTimeHit *last ) {
    int size = last - first;
    int idx = ( size - 1 ) / 2;
    return first + idx;
}



void surround_n10ntagvtx( CableTimeHit *ct_ntagvtx, int ctnsize, int n10nvx_size, CableTimeHit *surround, int &surroundsize ) {
    // Find first and last marked
    CableTimeHit *ctend = ct_ntagvtx + ctnsize;
    CableTimeHit *bgnmark = find_if( ct_ntagvtx, ctend, is_bonsvtx_marked );
    CableTimeHit *endmark = bgnmark;
    for ( int i = 1; i < n10nvx_size; ++i ) endmark = find_if( endmark, ctend, is_bonsvtx_marked );

    // Find medoid
    CableTimeHit *medoid = find_medoid( bgnmark, endmark );

    // Find bwd fwd
    WindowBounds surbnd;
    const float SURROUND_WIDTH_NVX = 220.;
    surbnd.end = fwd_taufind( ct_ntagvtx, ctnsize, medoid, SURROUND_WIDTH_NVX / 2. ); 
    surbnd.bgn = bwd_taufind( ct_ntagvtx, ctnsize, medoid, SURROUND_WIDTH_NVX / 2. );
    
    // Copy 220 nsec window
    surroundsize = surbnd.end - surbnd.bgn;
    for ( int i = 0; i < surroundsize; ++i ) surround[i] = surbnd.bgn[i];
}



void dryfind_n10( CableTimeHit *ct, int ctsize, WindowBounds *wndbnd, int &wbsize ) {
    // Reset number of windows
    wbsize = 0;

    // Loop through event
    CableTimeHit *eventbgn = ct;
    CableTimeHit *eventend = ct + ctsize;
    CableTimeHit *eventbgn_ntag = upper_bound( eventbgn, eventend, TAU_BGN_NTAG, compare_tau ); 
    CableTimeHit *bound[2] = { eventbgn_ntag, eventbgn_ntag };
    int n10;
    do {
        // Find 10 nsec window [bound0, bound1[
        bound[1] = find_n10_end( bound[0], eventend );

        // Save if necessary
        n10 = (int)(bound[1] - bound[0]);
        if ( N10_LO_CUT <= n10 && n10 <= N10_HI_CUT ) {
            wndbnd[wbsize].bgn = bound[0];
            wndbnd[wbsize].end = bound[1];
            ++wbsize;
        }

        // DBG
        //printf( "n10 = %d\n", n10 );
        //for ( int i = 0; i < n10; ++i ) {
            //printf( "%d  %d  %f\n", i, (bound[0]+i)->icabiz, (bound[0]+i)->tau );
        //}

        // Consider next hit
        ++bound[0];
    }
    while ( bound[1] != eventend );
}



WindowBounds select_n10ntagvtx( CableTimeHit *ct, int ctsize, WindowBounds *wb, int wbsize ) {
    float density[1000];
    int nhit;
    float time;
    for ( int i = 0; i < wbsize; ++i ) {
        nhit = wb[i].end - wb[i].bgn;
        time = wb[i].bgn[nhit-1].tau - wb[i].bgn[0].tau;
        density[i] = (float) nhit / time;

        // DBG
        //printf( "*** CAND %d ***\n", i );
        //watch( nhit );
        //watch( time );
        //watch( wb[i].bgn[nhit-1].tau );
        //watch( wb[i].bgn[0].tau );
        //watch( density[i] );
        //for ( int j = 0; j < wb[i].end - wb[i].bgn; ++j ) {
        //    printf( "%d %f %c %d\n", j, wb[i].bgn[j].tau, wb[i].bgn[j].sb, wb[i].bgn[j].flag_bonsvtx );
        //}
    }

    int idx = max_element( density, density + wbsize ) - density;

    //watch( idx );  // DBG
    return wb[idx];
}



bool ccf_is_outofsk( const Fitter::FuncPoint &x ) {
    if ( !is_inside_sk( x.vtx ) ) return true;
    return false;
}



bool ccf_is_bad_vtx( const Fitter::FuncPoint &x ) {
    if ( !is_inside_sk( x.vtx ) ) return true;
    if ( !isfinite( x.val ) ) return true;
    return false;
}



bool ccf_comp_val( const Fitter::FuncPoint &x, const Fitter::FuncPoint &y ) { return x.val < y.val; }



void Fitter::concentric_cube_fitter( const Window &w, const float *inivtx, const float iniside, int ncycle, float cyclefactor ) {
    // Check cyclefactor to be < 1.0
    if ( cyclefactor >= 1. ) {
        printf( " ---> ERROR: in Fitter::concentric_cube_fitter cyclefactor must be < 1.0\n" );
        flag = -1;
        return;
    }

    // Variables
    float side;
    float extr[6];
    const int NSAMPLE = 1000;
    struct FuncPoint guess; 
    struct FuncPoint buf[NSAMPLE];
    struct FuncPoint *bufend;
    struct FuncPoint checkmin;

    // Initial guess
    guess.vtx[0] = inivtx[0];
    guess.vtx[1] = inivtx[1];
    guess.vtx[2] = inivtx[2];
    guess.val = compute_taurms( w, guess.vtx );
    
    // Initial side
    side = iniside;

    //-----------------
    // Loop on cycles
    //-----------------
    
    // FILE *pdbg = fopen( "dbg.txt", "w" ); // DBG

    for ( int icycle = 0; icycle < ncycle; ++icycle ) {
        // Flag is cycle
        flag = icycle;

        // Compute extremes
        extr[0] = guess.vtx[0] - side / 2.;
        extr[1] = guess.vtx[0] + side / 2.;
        extr[2] = guess.vtx[1] - side / 2.;
        extr[3] = guess.vtx[1] + side / 2.;
        extr[4] = guess.vtx[2] - side / 2.;
        extr[5] = guess.vtx[2] + side / 2.;
        //watch( extr[0] ); watch( extr[1] ); watch( extr[2] ); watch( extr[3] ); watch( extr[4] ); watch( extr[5] );  // DBG

        // Sample in cube
        for ( int isample = 0; isample < NSAMPLE; ++isample ) {
            cube_sampler( extr, buf[isample].vtx );
            buf[isample].val = compute_taurms( w, buf[isample].vtx ); 
            // fprintf( pdbg, "%f %f %f %f\n", buf[isample].vtx[0], buf[isample].vtx[1], buf[isample].vtx[2], buf[isample].val );  // DBG
        }

        // Remove out-of-SK, infinite, and nan values
        bufend = remove_if( buf, buf + NSAMPLE, ccf_is_bad_vtx );

        // Totally bad sample case
        if ( bufend - buf == 0 ) {
            minimum = guess;
            return;
        }

        // Update best guess
        checkmin = *min_element( buf, bufend, ccf_comp_val );
        if ( checkmin.val < guess.val ) {
            guess = checkmin;
        }

        // Update for next step
        side *= cyclefactor; 

        //printf( "( icycle, guess ) = %d %f %f %f %f\n", icycle, guess.vtx[0], guess.vtx[1], guess.vtx[2], guess.val ); // DBG
    }

    // fclose( pdbg ); // DBG

    // Save minimum
    minimum = guess;
}


void ccf_findwnd( CableTimeHit *ctbvx, int ctsize, WindowBounds wndbnd, float *vtx, CableTimeHit *selwnd, int &selwndsize ) {
    CableTimeHit bigwnd[MAXPM];
    CableTimeHit litwnd[MAXPM];
    int bigwndsize = -1;
    int litwndsize = -1;
    WindowBounds candidate_wndbnd[1000];
    int candidate_size = -1;
    surround_n10bonsvtx( ctbvx, ctsize, wndbnd, bigwnd, bigwndsize ); 
    fill_sort_tau( bigwnd, bigwndsize, vtx );
    surround_n10ntagvtx( bigwnd, bigwndsize, wndbnd.end - wndbnd.bgn, litwnd, litwndsize ); 
    dryfind_n10( litwnd, litwndsize, candidate_wndbnd, candidate_size );
    cut_n200( litwnd, litwndsize, candidate_wndbnd, candidate_size );
    WindowBounds selected_wndbnd = select_n10ntagvtx( litwnd, litwndsize, candidate_wndbnd, candidate_size );
    
    selwndsize = selected_wndbnd.end - selected_wndbnd.bgn;
    for ( int i = 0; i < selwndsize; ++i ) selwnd[i] = selected_wndbnd.bgn[i];
}



float ccf_compute_taurms( CableTimeHit *selwnd, int selwndsize ) {
    long double mean, rms, tau[1000];

    for ( int i = 0; i < selwndsize; ++i ) tau[i] = selwnd[i].tau - selwnd[0].tau;
    
    mean = 0.;
    for ( int i = 0; i < selwndsize; ++i ) mean += tau[i];
    mean /= (long double) selwndsize;
    
    for ( int i = 0; i < selwndsize; ++i ) rms += ( tau[i] - mean ) * ( tau[i] - mean );
    rms = sqrt( rms / (long double) selwndsize );

    return rms;
}



bool ccf_seltaurms_is_bad( const Fitter::FuncPoint &x ) {
    int fpclass = fpclassify( x.seltaurms );
    if ( fpclass == FP_INFINITE || fpclass == FP_NAN || fpclass == FP_SUBNORMAL ) return true;
    return false;
}



bool ccf_seldensity_is_bad( const Fitter::FuncPoint &x ) {
    int fpclass = fpclassify( x.seldensity );
    if ( fpclass == FP_INFINITE || fpclass == FP_NAN || fpclass == FP_SUBNORMAL ) return true;
    return false;
}



bool ccf_comp_seltaurms( const Fitter::FuncPoint &x, const Fitter::FuncPoint &y ) {
    return x.seltaurms < y.seltaurms;
}



bool ccf_comp_seldensity( const Fitter::FuncPoint &x, const Fitter::FuncPoint &y ) {
    return x.seldensity < y.seldensity;
}



void Fitter::refreshwnd_concentric_cube_fitter( CableTimeHit *ctbvx, int ctsize, WindowBounds iniwndbnd, const float *inivtx, const float iniside, int ncycle, float cyclefactor ) {
    // Check cyclefactor to be < 1.0
    if ( cyclefactor >= 1. ) {
        printf( " ---> ERROR: in Fitter::concentric_cube_fitter cyclefactor must be < 1.0\n" );
        flag = -1;
        return;
    }

    // Variables
    float side;
    float extr[6];
    const int NSAMPLE = 1000;
    struct FuncPoint guess; 
    struct FuncPoint buf[NSAMPLE];
    struct FuncPoint *bufend;
    struct FuncPoint checkmin;
    CableTimeHit selwnd[1000];
    int selwndsize;
    CableTimeHit iniwnd[1000];
    int iniwndsize;

    // Initial guess
    guess.vtx[0] = inivtx[0];
    guess.vtx[1] = inivtx[1];
    guess.vtx[2] = inivtx[2];
    //guess.val = compute_taurms( w, guess.vtx );
    iniwndsize = iniwndbnd.end - iniwndbnd.bgn;
    for ( int i = 0; i < iniwndsize; ++i ) iniwnd[i] = iniwndbnd.bgn[i];
    guess.seltaurms = ccf_compute_taurms( iniwnd, iniwndsize );
    //guess.seldensity = ccf_compute_density( iniwnd, iniwndsize );

    // Initial side
    side = iniside;

    //-----------------
    // Loop on cycles
    //-----------------
    
    // FILE *pdbg = fopen( "dbg.txt", "w" ); // DBG

    for ( int icycle = 0; icycle < ncycle; ++icycle ) {
        // Flag is cycle
        flag = icycle;

        // Compute extremes
        extr[0] = guess.vtx[0] - side / 2.;
        extr[1] = guess.vtx[0] + side / 2.;
        extr[2] = guess.vtx[1] - side / 2.;
        extr[3] = guess.vtx[1] + side / 2.;
        extr[4] = guess.vtx[2] - side / 2.;
        extr[5] = guess.vtx[2] + side / 2.;
        //watch( extr[0] ); watch( extr[1] ); watch( extr[2] ); watch( extr[3] ); watch( extr[4] ); watch( extr[5] );  // DBG

        // Sample in cube
        for ( int isample = 0; isample < NSAMPLE; ++isample ) {
            cube_sampler( extr, buf[isample].vtx );
            //buf[isample].val = refreshwnd_compute_taurms( w, buf[isample].vtx ); 
            // fprintf( pdbg, "%f %f %f %f\n", buf[isample].vtx[0], buf[isample].vtx[1], buf[isample].vtx[2], buf[isample].val );  // DBG
        }

        // Remove out-of-SK
        bufend = remove_if( buf, buf + NSAMPLE, ccf_is_outofsk );

        // Totally bad sample case
        if ( bufend - buf == 0 ) {
            minimum = guess;
            return;
        }

        // Loop on vertexes
        for ( int i = 0; i < bufend - buf; ++i ) {
            ccf_findwnd( ctbvx, ctsize, iniwndbnd, buf[i].vtx, selwnd, selwndsize );
            buf[i].seltaurms = ccf_compute_taurms( selwnd, selwndsize );
            //buf[i].seldensity = (float) selwndsize / buf[i].seltaurms;
        }

        // Remove strange values
        bufend = remove_if( buf, bufend, ccf_seltaurms_is_bad );
        //bufend = remove_if( buf, bufend, ccf_seldensity_is_bad );

        // Update best guess
        checkmin = *min_element( buf, bufend, ccf_comp_seltaurms );
        //checkmin = *min_element( buf, bufend, ccf_comp_seldensity );
        if ( checkmin.val < guess.val ) {
            guess = checkmin;
        }

        // Update for next step
        side *= cyclefactor; 

        //printf( "( icycle, guess ) = %d %f %f %f %f\n", icycle, guess.vtx[0], guess.vtx[1], guess.vtx[2], guess.val ); // DBG
    }

    // fclose( pdbg ); // DBG

    // Save minimum
    minimum = guess;
}






void fvfill_N10nvx( const Window &w, int &N10nvx ) {
    N10nvx = w.nhit;
}



void fvfill_N300nvx( CableTimeHit *ct, int ctsize, const WindowBounds &wb, int &N300nvx ) {
    const float N300_TAUWIDTH = 300.;  // Typically surround window has about 70 hits

    // MY APPROACH
    // Find N300 window
    //CableTimeHit *wb_medoid = find_medoid( wb.bgn, wb.end );  // Medoid in wb range, not in ct range
    //CableTimeHit *medoid = ct;
    //while ( abs( medoid->tau - wb_medoid->tau ) > 0.1 ) ++medoid;  // Medoid in ct range
    //WindowBounds bnd;  // surround bounds
    //bnd.bgn = bwd_taufind( ct, ctsize, medoid, N300_TAUWIDTH / 2. );
    //bnd.end = fwd_taufind( ct, ctsize, medoid, N300_TAUWIDTH / 2. );

    // Computation of N300
    //N300nvx = bnd.end - bnd.bgn; 

    // AKUTSU-SAN APPROACH
    float center = wb.bgn[0].tau + 5.;
    N300nvx = 0;
    for ( int i = 0; i < ctsize; ++i ) {
        if ( abs( ct[i].tau - center ) < N300_TAUWIDTH / 2. ) ++N300nvx;
    }
}

void fvfill_N300S_akutsu( CableTimeHit *ctbvx, int ctbvxsize, const Window &w, int N10nvx, int &N300S ) {
    const float N300_TAUWIDTH = 300.;  // Typically surround window has about 70 hits
    float center = w.hit[0].tau + 5.;
    CableTimeHit ctnvx[MAXPM];
    int idx[2] = { 0, 0 };

    while ( abs( ctbvx[idx[0]].tau - center ) >= 1300./2. ) ++idx[0];
    idx[1] = idx[0];
    while( abs( ctbvx[idx[1]].tau - center ) < 1300./2.) ++idx[1];

    int ctnvxsize = idx[1] - idx[0];
    for ( int i = 0; i < ctnvxsize; ++i ) ctnvx[i] = ctbvx[idx[0]+i];

    // AKUTSU-SAN APPROACH
    int N300nvx = 0;
    for ( int i = 0; i < ctnvxsize; ++i ) {
        if ( abs( ctnvx[i].tau - center ) < N300_TAUWIDTH / 2. ) ++N300nvx;
    }

    N300S = N300nvx - N10nvx;
}



void diagnose_N200nvx( CableTimeHit *ct, int ctsize, const WindowBounds &wb, int &N200nvx ) {
    // Find N200 window
    const float N200_TAUWIDTH = 200.;
    CableTimeHit *wb_medoid = find_medoid( wb.bgn, wb.end );  // Medoid in wb range
    CableTimeHit *medoid = ct;
    while ( abs( medoid->tau - wb_medoid->tau ) > 0.1 ) ++medoid;  // Medoid in ct range
    WindowBounds bnd;
    bnd.bgn = bwd_taufind( ct, ctsize, medoid, N200_TAUWIDTH / 2. );
    bnd.end = fwd_taufind( ct, ctsize, medoid, N200_TAUWIDTH / 2. );

    // Computation of N200
    N200nvx = bnd.end - bnd.bgn;
}



//---------------------------------------
// Auxiliary functions for fvfill_Nclus
//---------------------------------------
float compute_angular_distance( const Hit &x, const Hit &y ) {
    float dist = 0.;
    for ( int i = 0; i < 3; ++i ) dist += x.nvco[i] * y.nvco[i];
    dist = acos( dist );

    return dist;
}



void Window::init_distancematrix() {
    // Upper right part of matrix
    for ( int i = 0; i < nhit; ++i ) {
        for ( int j = i+1; j < nhit; ++j ) {
            dmtx[i][j] = compute_angular_distance( hit[i], hit[j] );
        }
    }

    // Lower left part of matrix
    for ( int i = 0; i < nhit; ++i ) {
        for ( int j = 0; j < i; ++j ) {
            dmtx[i][j] = dmtx[j][i];
        }
    }

    // Diagonal
    for ( int i = 0; i < nhit; ++i ) {
        dmtx[i][i] = 0.;
    }
}



void fill_adjacency_matrix( Window &w, float thr ) {
    // Fill all
    for ( int i = 0; i < w.nhit; ++i ) {
        for ( int j = 0; j < w.nhit; ++j ) {
            if ( w.dmtx[i][j] < thr ) w.amtx[i][j] = 1;
            else w.amtx[i][j] = 0;
        }
    }

    // Set diagonal to 0
    for ( int i = 0; i < w.nhit; ++i ) w.amtx[i][i] = 0;

    // DBG
    /*
    printf( "*** DISTANCE MATRIX ***\n" );
    for ( int i = 0; i < w.nhit; ++i ) {
        for ( int j = 0; j < w.nhit; ++j ) {
            printf( "%4.3f  ", w.dmtx[i][j] );
        }
        printf( "\n" );
    }
    
    printf( "*** ADJACENCY MATRIX ***\n" );
    for ( int i = 0; i < w.nhit; ++i ) {
        for ( int j = 0; j < w.nhit; ++j ) {
            printf( "%d  ", w.amtx[i][j] );
        }
        printf( "\n" );
    }
    */

}



void BK_report_maxclique( vector<int> R, vector< vector<int> > &maxclique ) {
    sort( R.begin(), R.end() );
    vector< vector<int> >::iterator it;
    it = find( maxclique.begin(), maxclique.end(), R );
    if ( it == maxclique.end() ) maxclique.push_back( R );

    // DBG
    //printf( "BK_report_maxclique\n" );
    //int size = R.size();
    //for ( int i = 0; i < size; ++i ) printf( "%d  ", R[i] );
    //printf( "\n" );
}



void BK_set_neighbour( Window &w, int v, vector<int> &N ) {
    N.resize( 0 );
    for ( int i = 0; i < w.nhit; ++i ) {
        if ( w.amtx[v][i] == 1 ) N.push_back( i );
    }
}



void BK_prepare_R2( const vector<int> &R, int v, vector<int> &R2 ) {
    R2 = R;
    R2.push_back( v );
    sort( R2.begin(), R2.end() );
}



void BK_prepare_P2( const vector<int> &P, const vector<int> &N, vector<int> &P2 ) {
    vector<int>::iterator it;
    P2.resize( min( P.size(), N.size() ) );
    it = set_intersection( P.begin(), P.end(), N.begin(), N.end(), P2.begin() );
    P2.resize( it - P2.begin() );
}



void BK_prepare_X2( const vector<int> &X, const vector<int> &N, vector<int> &X2 ) {
    vector<int>::iterator it;
    X2.resize( min( X.size(), N.size() ) );
    it = set_intersection( X.begin(), X.end(), N.begin(), N.end(), X2.begin() );
    X2.resize( it - X2.begin() );
}



void print_vector( const vector<int> &x ) {
    int size = x.size();
    for ( int i = 0; i < size; ++i ) printf( "%d  ", x[i] );
    printf( "\n" );
}



void BronKerbosch( Window &w, vector<int> R, vector<int> P, vector<int> X, vector< vector<int> > &maxclique ) {
    //printf( "BronKerbosch\n" );  // DBG
    if ( P.empty() && X.empty() ) {
        BK_report_maxclique( R, maxclique );
        return;
    }
    
    int Psize = P.size();
    int v;
    vector<int> N, R2, P2, X2;
    for ( int i = Psize-1; i >= 0; --i ) {
        v = P.back();
        //watch( v );
        BK_set_neighbour( w, v, N );

        BK_prepare_R2( R, v, R2 );
        BK_prepare_P2( P, N, P2 ); 
        BK_prepare_X2( X, N, X2 );
        BronKerbosch( w, R2, P2, X2, maxclique );

        P.pop_back();
        X.push_back( v );
        sort( X.begin(), X.end() );
    }
}



// Returns value of Binomial Coefficient C(n, k)  
int binomial_coefficient( int n, int k ) {  
    int res = 1;  
     
    // Since C(n, k) = C(n, n-k)  
    if ( k > n - k )  
        k = n - k;  
                        
    // Calculate value of  
    // [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]  
    for ( int i = 0; i < k; ++i ) {  
        res *= (n - i);  
        res /= (i + 1);  
    }  
                                                               
    return res;  
}  



// Nclus = number of cliques having cluster_verteces verteces
// Adjacency matrix filled with relation (distance[i][j] <= angular_threshold)
void fvfill_Nclus( Window &w, float angular_threshold, int cliqueminsize, int &Nclus ) {
    watch( __func__ );
    watch( w.nhit );
    // Fill adjacency matrix
    int amtx[100][100];
    fill_adjacency_matrix( w, angular_threshold );

    // Preapre sets of vertices for BronKerbosch algorithm
    vector<int> R, X;
    vector<int> P( w.nhit );
    for ( int i = 0; i < w.nhit; ++i ) P[i] = i;
    
    // Run BronKerbosch algorithm (find all maximal cliques)
    vector< vector<int> > maxclique;
    BronKerbosch( w, R, P, X, maxclique );
    
    // Compute number of hits involved in cliques having at least cliqueminsize vertices
    int nmaxclique = maxclique.size();
    int cliquesize;
    set<int> bufset;
    Nclus = 0;
    for ( int i = 0; i < nmaxclique; ++i ) {
        cliquesize = maxclique[i].size();
        if ( cliquesize >= cliqueminsize ) {
            bufset.insert( maxclique[i].begin(), maxclique[i].end() );
        }

        // DBG
        //printf( "CLIQUE NUMBER %d:   ", i );
        //for ( int j = 0; j < cliquesize; ++j ) printf ( "%d  ", maxclique[i][j] );
        //printf( "\n" );
        //watch( bufset.size() );
    }

    Nclus = bufset.size();
}



void fvfill_Nclus_3clique( Window &w, float angular_threshold, int &Nclus ) {
    // Fill adjacency matrix
    fill_adjacency_matrix( w, angular_threshold );

    // Take all combinations
    set<int> bufset;
    Nclus = 0;
    for ( int i = 0; i < w.nhit-2; ++i ) {
        for ( int j = i+1; j < w.nhit-1; ++j ) {
            for ( int k = j+1; k < w.nhit; ++k ) {
                if ( w.amtx[i][j] == 1 && w.amtx[j][k] == 1 && w.amtx[i][k] == 1 ) {  // is clique!!
                    bufset.insert( i );
                    bufset.insert( j );
                    bufset.insert( k );
                }
            }
        }
    }

    Nclus = bufset.size();
}



void fvfill_Nclus_akutsu( const Window &w, int ncth, float thr, int &Nclus ) {
    // Search cluster.
    int   index[w.nhit],
		  flag[w.nhit],
    	  nc,
		  nc_m,
		  ncut	=0;

    float dalpha;
    float v1[3];
    float v2[3];

	for ( int i = 0; i < w.nhit; ++i ) flag[i] = 0;
    for ( int i = 0; i < w.nhit; ++i ) {
        if( flag[i] != 0 ) continue;  // skip hits that are already in clusters 
        for( int j = 0; j < w.nhit; ++j ) index[j] = 0;

        index[i] = 1; // first hit in a cluster
        nc_m=0;
        while( 1 ) {
            for( int j = 0; j < w.nhit; ++j ) {
                v1[0] = w.hit[j].nvco[0];
                v1[1] = w.hit[j].nvco[1];
                v1[2] = w.hit[j].nvco[2];
                if( flag[j] != 0 ) continue; // skip hits that are already in clusters 
                // scan index
                for( int k = 0; k < w.nhit; ++k ) {
                    if( k == j )			continue;       // do not compute angle to itself
                    if( index[k] == 0 ) 	continue;		// skip non-candidate hit

                    v2[0] = w.hit[k].nvco[0];
                    v2[1] = w.hit[k].nvco[1];
                    v2[2] = w.hit[k].nvco[2];
                    dalpha = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
                    if ( dalpha > thr ) index[j] = 1;
                }
            }

            // count hits in cluster
            nc = 0;
            for ( int j = 0; j < w.nhit; ++j ) {
                if ( index[j] == 1 ) ++nc;
            }
            if ( nc > nc_m ) nc_m = nc;
            else break; // no more hits belong to this cluster, stop
        }

		// this is a cluster
        if( nc_m >= ncth ) {
            for( int j = 0; j < w.nhit; ++j ) {
                if( index[j] == 1 ) {
                    ++ncut;
                    flag[j] = ncut;
                }
            }
        }
    }


    Nclus = ncut;
}



void computeNClusters( const Window &w, Int_t N10n, Int_t ncth, Float_t thr, int N10nvx, int &NcS ) {
    //Fill the positions
    vector<TVector3> hv;
    for ( int i = 0; i < N10n; ++i ) {
        hv.push_back( TVector3( w.hit[i].nvco[0], w.hit[i].nvco[1], w.hit[i].nvco[2] ) );
    }


    // Search cluster.
    Int_t index[N10n],
		  flag[N10n],
    	  nc,
		  nc_m,
      		  ncut	=0;

	for(Int_t i=0; i<N10n; i++){ flag[i]=0; }
	TVector3 v1,
			 v2;
    for(Int_t i=0; i<N10n; i++)
	{
        if( flag[i]!=0 ){ continue; } // skip hits that are already in clusters 
        for(Int_t j=0; j<N10n; j++){ index[j]=0; }

        index[i]=1; // first hit in a cluster
        nc_m=0;
        while(1)
		{
            for(Int_t j=0; j<N10n; j++)
			{
				v1.SetXYZ(0., 0., 0.);
				v1=hv[j];
                if( flag[j]!=0 ) continue; // skip hits that are already in clusters 
                // scan index
                for(Int_t k=0; k<N10n; k++)
				{
                    if( k==j )			continue;       // do not compute angle to itself
                    if( index[k]==0 ) 	continue;		// skip non-candidate hit

					v2.SetXYZ(0.,0.,0.);
					v2=hv[k];	
                    Float_t dalpha=0.;
					dalpha=v1.Dot( v2 );
                    if ( dalpha>thr ) index[j] = 1;
                }
            }

            // count hits in cluster
            nc=0;
            for(Int_t j=0; j<N10n; j++)
			{
                if( index[j]==1 ) nc++;
            }
            if( nc>nc_m ) nc_m=nc;
            else break; // no more hits belong to this cluster, stop
        }

		// this is a cluster
        if( nc_m>=ncth )
		{ 
            for(Int_t j=0; j<N10n; j++)
			{
                if( index[j]==1 )
				{
                    ncut ++;
                    flag[j]=ncut;
                }
            }
        }
    }
    //    return ncut;
    
    NcS = N10nvx - ncut;
}



//-------------------------------------------
// Auxiliary functions for fvfill_cang_stat
//-------------------------------------------
TH1F* llrca_pdf[2][10];

float compute_cang_3points( const Hit &A, const Hit &B, const Hit &C ) {
    // Compute distances among hits
    double a2, b2, c2;
    a2 = b2 = c2 = 0.;
    for ( int i = 0; i < 3; ++i ) {
        a2 += ( C.nvco[i] - B.nvco[i] ) * ( C.nvco[i] - B.nvco[i] );
        b2 += ( A.nvco[i] - C.nvco[i] ) * ( A.nvco[i] - C.nvco[i] );
        c2 += ( B.nvco[i] - A.nvco[i] ) * ( B.nvco[i] - A.nvco[i] );
    }

    // Compute radius of the circumcenter of the triangle
    double num, den, radius;
    num = den = radius = 0.;
    num = sqrt(a2)*sqrt(b2)*sqrt(c2);
    den += 2.*a2*b2 + 2.*a2*c2 + 2.*b2*c2;
    den -= a2*a2 + b2*b2 + c2*c2;
    den = sqrt( den );
    radius = num / den;

    // Check on radius
    if ( radius <= 0. ) return 0.;
    else if ( radius >= 1. ) return 89.9999;
    
    // Compute cherenkov angle
    const double RAD2DEG = 180. / TMath::Pi();
    double cang = asin( radius ) * RAD2DEG;

    // Check on cherenkov angle
    if ( cang <= 0. ) return 0.;
    else if ( cang >= 90. ) return 89.9999;

    return cang;
}



void fvfill_llrca( const Window &w, float &llrca, float &nllrca ) {
    // Fill Cherenkov angle array
    float cang[19600];
    float wannabe_cang;
    int cntgood = 0, cntnan = 0;
    watch( w.nhit );
    for ( int i = 0; i < w.nhit-2; ++i ) {
        for ( int j = i+1; j < w.nhit-1; ++j ) {
            for ( int k = j+1; k < w.nhit; ++k ) {
                wannabe_cang = compute_cang_3points( w.hit[i], w.hit[j], w.hit[k] );
                //watch( wannabe_cang );
                if ( isfinite( wannabe_cang ) ) {
                    cang[cntgood] = wannabe_cang;
                    ++cntgood;
                }
                else {
                    ++cntnan;
                }
            }
        }
    }
    //watch( cntgood );
    //watch( cntnan );

    // Compute llrca
    int type;
    type = w.nhit - 7;
    if ( type < 0 ) type = 0;
    if ( type > 9 ) type = 9;

    int bkgbin, sigbin;
    long double bkgprob, sigprob, bkgloglik, sigloglik;
    bkgloglik = sigloglik = 0.;
    for ( int i = 0; i < cntgood; ++i ) {
        bkgbin = llrca_pdf[0][type]->GetXaxis()->FindBin( cang[i] );
        sigbin = llrca_pdf[1][type]->GetXaxis()->FindBin( cang[i] );
        bkgprob = llrca_pdf[0][type]->GetBinContent( bkgbin );
        sigprob = llrca_pdf[1][type]->GetBinContent( sigbin );
        bkgloglik += log( bkgprob );
        sigloglik += log( sigprob );

        //watch( bkgprob );
        //watch( sigprob );
        //watch( bkgloglik );
        //watch( sigloglik );
    }
    llrca = bkgloglik - sigloglik;
    nllrca = ( bkgloglik - sigloglik ) / ( bkgloglik + sigloglik );
    
    // DBG
    //watch( __func__ );
    //watch( w.nhit );
    //watch( type );
    //watch( llrca );
}



void fvfill_cang_stat( const Window &w, float &cangmean, float &cangstddev, float &cangskew, float &cangkurt, int &cangcntnan ) {
    // Fill Cherenkov angle array
    float cang[19600];
    float wannabe_cang;
    int cntgood = 0, cntnan = 0;
    for ( int i = 0; i < w.nhit-2; ++i ) {
        for ( int j = i+1; j < w.nhit-1; ++j ) {
            for ( int k = j+1; k < w.nhit; ++k ) {
                wannabe_cang = compute_cang_3points( w.hit[i], w.hit[j], w.hit[k] );
                //watch( wannabe_cang );
                if ( isfinite( wannabe_cang ) ) {
                    cang[cntgood] = wannabe_cang;
                    ++cntgood;
                }
                else {
                    ++cntnan;
                }
            }
        }
    }
    //watch( cntgood );
    //watch( cntnan );

    // Compute mean, standard deviation, skewness, and kurtosis
    cangmean = 0.;
    for ( int i = 0; i < cntgood; ++i ) {
        cangmean += cang[i] / (float) cntgood;
    }

    cangstddev = 0.;
    for ( int i = 0; i < cntgood; ++i ) {
        cangstddev += ( cang[i] - cangmean ) * ( cang[i] - cangmean ) / (float) cntgood;
    }
    cangstddev = sqrt( cangstddev );

    float residue;
    cangskew = 0.;
    cangkurt = 0.;
    for ( int i = 0; i < cntgood; ++i ) {
        residue = ( cang[i] - cangmean ) / cangstddev;
        cangskew += residue*residue*residue;
        cangkurt += residue*residue*residue*residue;
    }
    cangskew /= (float) cntgood;
    cangkurt /= (float) cntgood;
}



//--------------------------------------
// Auxiliary functions for fvfill_beta
//--------------------------------------
TF1 *legendre1, *legendre2, *legendre3, *legendre4, *legendre5;

float beta_compute_cos( const Hit &A, const Hit &B ) {
    float res = 0.;
    for ( int i = 0; i < 3; ++i ) {
        res += A.nvco[i] * B.nvco[i];
    }

    if ( res <= -1.1 || res >= 1.1 ) {
        cerr << " ---> ERROR in function " << __func__ << ", cosine out of range" << '\n';
        exit( EXIT_FAILURE );
    }
    else if ( -1.1 < res && res < -1. ) res = -1.;  // Correct for truncations
    else if ( 1. < res && res < 1.1 ) res = 1.;  // Correct for truncations

    return res;
}



void fvfill_beta( const Window &w, float *beta ) {
    // Compute array of cosines
    int cnt = 0;
    float cosvec[1225];
    for ( int i = 0; i < w.nhit-1; ++i ) {
        for ( int j = i+1; j < w.nhit; ++j ) {
            cosvec[cnt] = beta_compute_cos( w.hit[i], w.hit[j] ); 
            //watch( cosvec[cnt] );
            ++cnt;
        }
    }
    //watch( cnt );

    // Compute un-normalized betas
    beta[0] = beta[1] = beta[2] = beta[3] = beta[4] = 0.;
    for ( int i = 0; i < cnt; ++i ) {
        beta[0] += legendre1->Eval( cosvec[i] ); 
        beta[1] += legendre2->Eval( cosvec[i] );
        beta[2] += legendre3->Eval( cosvec[i] );
        beta[3] += legendre4->Eval( cosvec[i] );
        beta[4] += legendre5->Eval( cosvec[i] );
    }
   
    // Normalize betas
    float norm = 2.;
    norm /= (float)w.nhit * ( (float)w.nhit - 1. ); 
    for ( int b = 0; b < 5; ++b ) beta[b] *= norm;
    
    // DBG
    //watch( beta[0] );
    //watch( beta[1] );
    //watch( beta[2] );
    //watch( beta[3] );
    //watch( beta[4] );
}



//-------------------------------------------
// Auxiliary functions for fvfill_accepave
//-------------------------------------------
long double get_effcos( long double costh ) {
    // Cal effective cos theta 
    // See also: /skofl/src/sklib/coseffsk.F
    long double effc=0.;
    effc    +=0.205349;
    effc    +=0.523981*costh;
    effc    +=0.389951*costh*costh;
    effc    -=0.131959*costh*costh*costh;

    return effc;
}



float compute_acptweight_akutsu( const float *vtx, const float *pmt ) {
    //-----------------
    // Akutsu version
    //-----------------
    float R = 0.;
    for ( int i = 0; i < 3; ++i ) R += ( pmt[i] - vtx[i] ) * ( pmt[i] - vtx[i] );
    R = sqrt( R );
    if ( R == 0. ) R = 0.1;
    
    // Barrel
    float costh = 0.;
    float rho = 0.;
    if ( pmt[2] > -1800. && pmt[2] < 1800. ) {
        costh += pmt[0] * ( pmt[0] - vtx[0] );
        costh += pmt[1] * ( pmt[1] - vtx[1] );
        rho = 0.;
        rho += pmt[0] * pmt[0];
        rho += pmt[1] * pmt[1];
        rho = sqrt( rho );
        costh /= rho;
        costh /= R;
    }

    // Top / Bottom
    else {
        costh = pmt[2] - vtx[2];
        costh /= R;
    }
    
    // Top / Barrel / Bottom
    costh = abs( costh );
    
    return costh;
}



long double compute_acptweight( const float *vtx_, const float *pmt_ ) {
    //----------------
    // Fabio version
    //----------------
    long double vtx[3];
    long double pmt[3];
    vtx[0] = vtx_[0];
    vtx[1] = vtx_[1];
    vtx[2] = vtx_[2];
    pmt[0] = pmt_[0];
    pmt[1] = pmt_[1];
    pmt[2] = pmt_[2];
    
    // Photon vector seen by PMT
    long double vec[3];
    for ( int i = 0; i < 3; ++i ) vec[i] = vtx[i] - pmt[i];
    long double vecnorm = sqrt( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] );
    if ( vecnorm == 0.  ) {
        cerr << " ---> ERROR in function " << __func__ << ": vecnorm is 0!!! EXITING PROGRAM" << endl;
        exit( EXIT_FAILURE );
    }

    // Vector orthogonal to PMT
    long double orthpmt[3];
    if ( pmt[2] < 1800. && pmt[2] > -1800. ) {  // Barrel
        orthpmt[0] = -pmt[0];
        orthpmt[1] = -pmt[1];
        orthpmt[2] = 0.;
    }
    else {  // Top or Bottom
        orthpmt[0] = 0.;
        orthpmt[1] = 0.;
        orthpmt[2] = -pmt[2];
    }
    long double orthpmtnorm = sqrt( orthpmt[0]*orthpmt[0] + orthpmt[1]*orthpmt[1] + orthpmt[2]*orthpmt[2] );

    // Cosine of photon incidence angle
    long double costh = ( vec[0]*orthpmt[0] + vec[1]*orthpmt[1] + vec[2]*orthpmt[2] ) / ( orthpmtnorm * vecnorm );
    if ( 0. <= costh && costh <= 1. ) {}  // Do nothing: cosine is fine
    else if ( -0.1 < costh && costh < 0. ) costh = 0.;  // Round error supposed: correct
    else if ( costh <= -0.1 ) {
        cerr << " ---> ERROR in function " << __func__ << " strange cosine, EXITING PROGRAM" << endl;
        watch( vtx[0] );
        watch( vtx[1] );
        watch( vtx[2] );
        watch( pmt[0] );
        watch( pmt[1] );
        watch( pmt[2] );
        fprintf( stderr, "%12.5f %12.5f %12.5f\n", (double)pmt[0], (double)pmt[1], (double)pmt[2] );
        watch( vec[0] );
        watch( vec[1] );
        watch( vec[2] );
        watch( vecnorm );
        watch( orthpmt[0] );
        watch( orthpmt[1] );
        watch( orthpmt[2] );
        watch( orthpmtnorm );
        watch( costh );
        exit( EXIT_FAILURE );
    }
    else if ( 1. < costh && costh < 1.1 ) costh = 1.;  // Round error supposed: correct
    else if ( 1.1 <= costh ) {
        cerr << " ---> ERROR in function " << __func__ << " strange cosine, EXITING PROGRAM" << endl;
        cerr << "costh = " << costh << endl;
        exit( EXIT_FAILURE );
    }

    // Efficient cosine
    long double effc = get_effcos( costh );

    // Weight
    const long double WT_ATT_LEN = 13757.; 
    long double weight = effc * exp( -vecnorm / WT_ATT_LEN ) / vecnorm / vecnorm;

    // DBG BGN
    if ( weight == INFINITY ) {
        watch( costh );
        watch( effc );
        watch( weight );

        exit( 1 );
    }
    // DBG END
    if ( weight < 1e-100 ) weight = 1e-100;
    return weight;
}



void fvfill_accepave( const Window &w, float &accepave ) {
    // Fill weights
    // Remember geopmt_.xyzpm[0-11145] refers to PMT with cable number [1-11146]
    long double weight[MAXPM];
    for ( int icab = 0; icab < MAXPM; ++icab ) {
        weight[icab] = compute_acptweight( w.vtx, geopmt_.xyzpm[icab] );
    }

    // Normalize weights by dividing for biggest weight
    long double maxweight = *max_element( weight, weight + MAXPM );
    for ( int i = 0; i < MAXPM; ++i ) weight[i] /= maxweight;

    // Find sum of weights
    long double sumweight = 0.;
    for ( int i = 0; i < MAXPM; ++i ) sumweight += weight[i];

    // Acceptance
    long double acpa = 0.;
    int icab;
    for ( int i = 0; i < w.nhit; ++i ) {
        icab = w.hit[i].cable - 1;
        acpa -= log10( weight[icab] / sumweight );
    }

    acpa /= (long double) w.nhit;
    accepave = acpa;
    //watch( accepave );
     
    //if ( fpclassify( accepave ) == FP_NAN || fpclassify( accepave ) == FP_INFINITE ) {
    /*if ( 1 ) {
        watch( w.nhit );
        watch( accepave );
        watch( sumweight );
        watch( maxweight );

        watch( w.vtx[0] );
        watch( w.vtx[1] );
        watch( w.vtx[2] );

        for ( int i = 0; i < w.nhit; ++i ) {
            watch( w.hit[i].cable-1 );
            watch( weight[w.hit[i].cable-1] );
            watch( weight[w.hit[i].cable-1] / sumweight );
            watch( log10( weight[w.hit[i].cable-1] / sumweight ) );
        }
        //exit(1);
    }
    */
}



void fvfill_mintaurms6( const Window &w, float &mintaurms6 ) {
    //watch( w.nhit );  // DBG
    float mean, rms;
    int idx[6];
    mintaurms6 = +9999.;
    // Loop over combinations
    for ( int i = 0; i < w.nhit-5; ++i ) {
        idx[0] = i;
        for ( int j = i+1; j < w.nhit-4; ++j ) {
            idx[1] = j;
            for ( int k = j+1; k < w.nhit-3; ++k ) {
                idx[2] = k;
                for ( int l = k+1; l < w.nhit-2; ++l ) {
                    idx[3] = l;
                    for ( int m = l+1; m < w.nhit-1; ++m ) {
                        idx[4] = m;
                        for ( int n = m+1; n < w.nhit; ++n ) {
                            idx[5] = n;
                            mean = 0.;
                            for ( int t = 0; t < 6; ++t ) {
                                //printf( "%2d  ", idx[t] );  // DBG
                                //watch( w.hit[idx[t]].stau );  // DBG
                                mean += w.hit[idx[t]].stau;
                            }
                            //printf( "\n" );  // DBG
                            mean /= 6.;
                            
                            rms = 0.;
                            for ( int t = 0; t < 6; ++t ) {
                                rms += ( w.hit[idx[t]].stau - mean ) * ( w.hit[idx[t]].stau - mean );
                            }
                            rms = sqrt( rms / 6. );
                            //watch( rms );  // DBG
                            
                            if ( rms < mintaurms6 ) mintaurms6 = rms;
                        }
                    }
                }
            }
        }
    }
    //watch( mintaurms6 );
}



void fvfill_ndwall( const Window &w, float &ndwall ) {
    float rho = sqrt( w.vtx[0]*w.vtx[0] + w.vtx[1]*w.vtx[1] );
    float dR = TANKR - rho;
    float dZ = TANKZ - abs( w.vtx[2] );

    ndwall = min( dR, dZ );
}



//-----------------------------------------
// Auxiliary functions for fvfill_ntowall
//-----------------------------------------

// par[2]*x*x + par[1]*x + par[0] = 0
// + = sol[0],   - = sol[1]
void secondgradeeq_solver( float *par, float *sol ) {
    float discr = sqrt( par[1]*par[1] - 4.*par[2]*par[0] );
    sol[0] = ( -par[1] + discr ) / ( 2.*par[2] );
    sol[1] = ( -par[1] - discr ) / ( 2.*par[2] );
}


// DIR must be already normalized
float elementary_towall( const float *vtx, const float *dir ) {
    // Compute time to reach cylinder radially
    float tR, par[3], sol[2];
    if ( dir[0] == 0. && dir[1] == 0. ) tR = INFINITY;  // Purely longitudinal
    else {
        par[0] = vtx[0]*vtx[0] + vtx[1]*vtx[1] - TANKR*TANKR;
        par[1] = 2.*vtx[0]*dir[0] + 2.*vtx[1]*dir[1];
        par[2] = dir[0]*dir[0] + dir[1]*dir[1];
        secondgradeeq_solver( par, sol );
        tR = sol[0];  // VERIFIED to be > 0, which is what I want
    }

    // Compute time to reach cylinder longitudinally
    float tZ, signZ;
    if ( dir[2] == 0. ) tZ = INFINITY;  // Purely radial
    else {
        signZ = dir[2] / abs( dir[2] );
        tZ = ( signZ*TANKZ - vtx[2] ) / dir[2];
    }

    // Choose shortest time
    return min( tR, tZ );
}



void fvfill_ntowall( const Window &w, float &ntowall ) {
    ntowall = elementary_towall( w.vtx, w.spheremean );
}



void fvfill_distancevector( const Window &w, float *distancevector ) {
    // Take distances from spheremean for all hits
    float buf[100];
    for ( int i = 0; i < w.nhit; ++i ) {
        buf[i] = w.hit[i].spheremean_dist;
    }

    // Sort in increasing order in distances
    sort( buf, buf + w.nhit );

    // Fill the distance vector
    for ( int i = 0; i < 7; ++i ) {
        distancevector[i] = buf[i];
    }
}



void fvfill_distance_stat( const Window &w, float &dmean, float &drms, float &ddiff ) {
    //for ( int i = 0; i < w.nhit; ++i ) printf( "%d  %f\n", i, w.hit[i].spheremean_dist );  // DBG

    dmean = 0.;
    for ( int i = 0; i < w.nhit; ++i ) dmean += w.hit[i].spheremean_dist;
    dmean /= (float) w.nhit;

    drms = 0.;
    for ( int i = 0; i < w.nhit; ++i ) drms += ( w.hit[i].spheremean_dist - dmean ) * ( w.hit[i].spheremean_dist - dmean );
    drms /= (float) w.nhit;
    drms = sqrt( drms );
    
    float dmax = max_element( w.hit, w.hit + w.nhit, spheremean_dist_compare )->spheremean_dist;
    float dmin = min_element( w.hit, w.hit + w.nhit, spheremean_dist_compare )->spheremean_dist;
    ddiff = dmax - dmin;

    // DBG
    //watch( dmean );
    //watch( drms );
    //watch( ddiff );
    //watch( dmax );
    //watch( dmin );
}



void fvfill_stau( const Window &w, float *stau ) {
    for ( int i = 0; i < 7; ++i ) {
        stau[i] = w.hit[i].stau;
    }
}



void fvfill_staugeom( const Window &w, float *staugeom ) {
    Hit buf[100];
    for ( int i = 0; i < w.nhit; ++i ) buf[i] = w.hit[i]; 
    sort( buf, buf + w.nhit, spheremean_dist_compare );

    for ( int i = 0; i < 7; ++i ) staugeom[i] = buf[i].stau;
}



void fvfill_init() {
    // For betas
    gSystem->Load( "libMathMore" );

    legendre1 = new TF1( "legendre1", "ROOT::Math::legendre([0],x)", -1., 1. );
    legendre2 = new TF1( "legendre2", "ROOT::Math::legendre([0],x)", -1., 1. );
    legendre3 = new TF1( "legendre3", "ROOT::Math::legendre([0],x)", -1., 1. );
    legendre4 = new TF1( "legendre4", "ROOT::Math::legendre([0],x)", -1., 1. );
    legendre5 = new TF1( "legendre5", "ROOT::Math::legendre([0],x)", -1., 1. );
    
    legendre1->SetParameters( 1, 0.0 );
    legendre2->SetParameters( 2, 0.0 );
    legendre3->SetParameters( 3, 0.0 );
    legendre4->SetParameters( 4, 0.0 );
    legendre5->SetParameters( 5, 0.0 );

    // For llrca
    TFile *ifile = new TFile( "/disk02/usr6/fiacob/ntag/prm/cangpdf/pdf/cangpdf.hntagRBNR_6us.root" );
    if ( ifile->IsZombie() ) {
        cerr << " ---> ERROR in function " << __func__ << ": " << ifile << " not found" << endl;
        exit( EXIT_FAILURE );
    }

    string hname[2][10];
    hname[0][0] = "hcangPDF_bkg_n10nle07"; hname[1][0] = "hcangPDF_mcn_n10nle07";
    hname[0][1] = "hcangPDF_bkg_n10neq08"; hname[1][1] = "hcangPDF_mcn_n10neq08";
    hname[0][2] = "hcangPDF_bkg_n10neq09"; hname[1][2] = "hcangPDF_mcn_n10neq09";
    hname[0][3] = "hcangPDF_bkg_n10neq10"; hname[1][3] = "hcangPDF_mcn_n10neq10";
    hname[0][4] = "hcangPDF_bkg_n10neq11"; hname[1][4] = "hcangPDF_mcn_n10neq11";
    hname[0][5] = "hcangPDF_bkg_n10neq12"; hname[1][5] = "hcangPDF_mcn_n10neq12";
    hname[0][6] = "hcangPDF_bkg_n10neq13"; hname[1][6] = "hcangPDF_mcn_n10neq13";
    hname[0][7] = "hcangPDF_bkg_n10neq14"; hname[1][7] = "hcangPDF_mcn_n10neq14";
    hname[0][8] = "hcangPDF_bkg_n10neq15"; hname[1][8] = "hcangPDF_mcn_n10neq15";
    hname[0][9] = "hcangPDF_bkg_n10nge16"; hname[1][9] = "hcangPDF_mcn_n10nge16";
    TH1F *bufb, *bufs;
    for ( int i = 0; i < 10; ++i ) {
        ifile->GetObject( hname[0][i].c_str(), bufb );
        ifile->GetObject( hname[1][i].c_str(), bufs );
        llrca_pdf[0][i] = new TH1F( *bufb );
        llrca_pdf[1][i] = new TH1F( *bufs );
        llrca_pdf[0][i]->SetDirectory( 0 );
        llrca_pdf[1][i]->SetDirectory( 0 );
        cout << llrca_pdf[0][i]->GetName() << " loaded correctly" << endl;
        cout << llrca_pdf[1][i]->GetName() << " loaded correctly" << endl;
    }

    ifile->Close();
    delete ifile;
}



void fvfill_end() {
    delete legendre1;
    delete legendre2;
    delete legendre3;
    delete legendre4;
    delete legendre5;
    
    for ( int i = 0; i < 2; ++i ) {
        for ( int j = 0; j < 10; ++j ) {
            delete llrca_pdf[i][j];
        }
    }
}



void fvfill_sbvec( const Window &w, char *sbvec, int &nsig, int &nbkg ) {
    nsig = 0;
    nbkg = 0;
    for ( int i = 0; i < w.nhit; ++i ) {
        if ( w.hit[i].sb == 's' ) {
            ++nsig;
            sbvec[i] = 's';
        }
        else if ( w.hit[i].sb == 'b' ) {
            ++nbkg;
            sbvec[i] = 'b';
        }
        /*
         * SBI 8jul2019
        else if ( w.hit[i].sb == 'S' || w.hit[i].sb == 'B' ) {
            cout << " ---> ERROR in function " << __func__ << ": unmasked hit found" << endl;
            exit( EXIT_FAILURE );
        }
        else {
            cout << " ---> ERROR in function " << __func__ << ": non-sense hit found" << endl; 
            exit( EXIT_FAILURE );
        }
        */
    } 
}


void strong_number_check( float x, string varname ) {
    // Associate word in any case
    int sw = fpclassify( x );
    string wrd;
    switch( sw ) {
        case FP_INFINITE : wrd = "FP_INFINITE" ; break;
        case FP_NAN      : wrd = "FP_NAN"      ; break;
        case FP_ZERO     : wrd = "FP_ZERO"     ; break;
        case FP_SUBNORMAL: wrd = "FP_SUBNORMAL"; break;
        default          : wrd = "OK"          ; break;
    }

    // Exit only if necessary
    if ( sw == FP_INFINITE || sw == FP_NAN || sw == FP_SUBNORMAL ) {
        cout << " ---> ERROR in function " << __func__ << endl;
        cout << " ---> Variable " << varname << " has value " << x << " which is classified as " << wrd << endl;
        cout << " ---> EXITING PROGRAM" << endl;
        exit( EXIT_FAILURE );
    }
}



bool fvcheck_pmtcable( const Window &w ) {
    for ( int i = 0; i < w.nhit; ++i ) {
        if ( w.hit[i].cable < 1 || 11146 < w.hit[i].cable ) return true;
    }

    return false; 
}


// ctbvx     = event with tau computed on bvx
// ctsize    = nhits in ctbvx
// wbbvx     = bounds of the initial window in ctbvx
// nvx       = neutron vertex
// ctnvx     = small event with tau in nvx
// ctnvxsize = nhits in ctnvx
// wbnvx     = bounds of the selected candidate in ctnvx
void select_n10ntagvtx_akutsu( CableTimeHit *ctbvx, int ctbvxsize, WindowBounds wbbvx, float *nvx, CableTimeHit *ctnvx, int &ctnvxsize, WindowBounds &wbnvx ) {
    const int EXTRA = 12; 
    int fstIdx = wbbvx.bgn - ctbvx;
    int fstIdxn = -1;
    int N10 = wbbvx.end - wbbvx.bgn;
    int nhitaim = N10 + EXTRA;
    int tmpIdx	=fstIdx;
    tmpIdx -= EXTRA / 2;
    int N10ni = 0;
    int N10n = 0;
    float t0n = 0.;

    if ( fstIdx + N10 + EXTRA / 2 >= ctbvxsize ) {
        cerr << "ERROR in function " << __func__ << " fstIdx + N10 + EXTRA / 2 >= ctbvxsize" << endl;
        exit( EXIT_FAILURE );
    }

    // Copy event
    ctnvxsize = nhitaim;
    for ( int i = 0; i < ctnvxsize; ++i ) 
        ctnvx[i] = ctbvx[i+tmpIdx];

    // Sort tau in nvx
    fill_sort_tau( ctnvx, ctnvxsize, nvx );

    // Find the window
    for ( int j = 0; j < nhitaim; ++j ) {
	    N10ni = getUSNhitsXX( ctnvx, ctnvxsize, j, 10. );	
		if( N10ni > N10n ) {
		    N10n = N10ni;
		    fstIdxn = j;
		    t0n = ctnvx[j].tau;
		}	
	}

    // Return window bounds referred to original ct
    wbnvx.bgn = ctnvx + fstIdxn;
    wbnvx.end = ctnvx + fstIdxn + N10n;
}



float nfit_akutsu( const Window &w, int nhits, float *_pvx, float *nvx, float discut ) {
    // Constants
    const float C_WATER = 21.5833;
    // Fill tiskz and cabiz
    vector<float> tiskz;
    vector<int> cabiz;
    for ( int i = 0; i < nhits; ++i ) {
        tiskz.push_back( w.hit[i].t );
        cabiz.push_back( w.hit[i].cable );
    }

	//scans the tank for a vertex of minimum t-rms 
	//for a given set of hits.
    Bool_t search	=kTRUE,
		   smaller	=kFALSE,
		   first	=kFALSE;

    Int_t cabizmin[nhits],
		  cabiz3[nhits],
		  maxscanxy,
		  maxscanz;

    Float_t inc=-1.,
			tiskzmin[nhits],
			tiskz2[nhits],
			tiskz3[nhits],
			VX=0.,
			VY=0.,
			VZ=0.,
			tVX=0.,
			tVY=0.,
			tVZ=0.,
			vx=0.,
			vy=0.,
			vz=0.,
			mintrms=9999.,
			mintmean=0.,
    		tmean=0.,
			trms=0.,
			trms1=0.,
			dis=-1.,
			tof=0.;

    for(Int_t i=0; i<nhits; i++){ tiskz2[i]=tiskz[i]; }

	( discut>200 ) ? inc=100 : inc=discut/2;
    maxscanz	=(Int_t)(2*TANKZ/(Float_t)inc);
    maxscanxy 	=(Int_t)(2*TANKR/(Float_t)inc);

	while( inc>0.5 )
	{
		for(Float_t x=0; x<maxscanxy; x++)
		{
			vx=inc*(x-maxscanxy/2.) + VX;
			for(Float_t y=0; y<maxscanxy; y++)
			{
				vy = inc*(y-maxscanxy/2.) + VY;
				if( TMath::Sqrt(vx*vx + vy*vy)>TANKR ){ continue; }
				for(Float_t z=0; z<maxscanz; z++)
				{
					vz = inc*(z-maxscanz/2.) + VZ;
					if( vz>TANKZ || vz<-TANKZ){ continue; }
	
					dis=0.;
					dis+=(vx-_pvx[0])*(vx-_pvx[0]);
					dis+=(vy-_pvx[1])*(vy-_pvx[1]);
					dis+=(vz-_pvx[2])*(vz-_pvx[2]);
					dis=TMath::Sqrt( dis );
					if( dis>discut ){ continue; }
					
					tmean = 0;
					trms = 0;
					for(Int_t i=0; i<nhits; i++)
					{
					   tiskz3[i] = tiskz2[i];
					   cabiz3[i] = cabiz[i];

					   tof=0.;
					   tof+=(vx-geopmt_.xyzpm[cabiz[i]-1][0])*(vx-geopmt_.xyzpm[cabiz[i]-1][0]);
					   tof+=(vy-geopmt_.xyzpm[cabiz[i]-1][1])*(vy-geopmt_.xyzpm[cabiz[i]-1][1]);
					   tof+=(vz-geopmt_.xyzpm[cabiz[i]-1][2])*(vz-geopmt_.xyzpm[cabiz[i]-1][2]);
					   tof=TMath::Sqrt( tof );
					   tof/=C_WATER;

					   tiskz3[i] -= tof;
					   tmean += tiskz3[i];
					}
					
					tmean = tmean/nhits;
					for(Int_t i=0; i<nhits; i++)
					{
					    trms+=(tiskz3[i]-tmean)*(tiskz3[i]-tmean);
					}
					trms=TMath::Sqrt( trms/nhits );
					
					if( trms<mintrms )
					{
						mintrms		=trms;
						mintmean	=tmean;
						tVX			=vx;
						tVY			=vy;
						tVZ			=vz;
						for(Int_t i=0; i<nhits; i++)
						{
							tiskzmin[i]=tiskz3[i];
							cabizmin[i]=cabiz3[i];
						}
					}
				}
			}
		}
	
		VX	=tVX;
		VY	=tVY;
		VZ	=tVZ;
		inc	=inc/2.;
		}
	
	nvx[0]=VX;
	nvx[1]=VY;
	nvx[2]=VZ;
	return mintrms;
}


// Akutsu-san style compute candidate nvx
void computeCandTauNvx( const Window &wndraw, Window &wndnvx, Float_t *vtx )
{
	Float_t tof=0.,
			ttau=0.;
	Int_t 	cab=-1,
			nhits=-1;
	vector<Float_t> tau;
	vector<Int_t>	idx;


	vector<Float_t> fCandTimRaw( wndraw.nhit );
	vector<Int_t> fCandCabRaw( wndraw.nhit );
	for ( int i = 0; i < wndraw.nhit; ++i ) {
		fCandTimRaw[i] = wndraw.hit[i].t;
		fCandCabRaw[i] = wndraw.hit[i].cable;
		//cout << fCandTimRaw[i] << " " << fCandCabRaw[i] << endl;  // DBG
	}

	nhits=(Int_t)fCandTimRaw.size();
	tau.reserve( nhits );
	idx.reserve( nhits );

    // TOF subtruction from fitted n cap. vtx
	const float CWATER = 299792458. * 1e-7 / 1.33;
    for (Int_t i=0; i<nhits; i++) 
	{
		tof=0.;
		ttau=0.;
		cab=fCandCabRaw[i]-1;
		for(Int_t j=0; j<3; j++)
		{
        	tof+=(vtx[j] - geopmt_.xyzpm[ cab ][ j ])*(vtx[j] - geopmt_.xyzpm[ cab ][ j ]);
		}
		tof=TMath::Sqrt( tof );
		tof/=CWATER;

		ttau=fCandTimRaw[i];
		ttau-=tof;

		tau.push_back( ttau ); 
 	}


	vector<Float_t> fCandTimNvx( nhits );
	vector<Float_t> fCandTauNvx( nhits );
	vector<Int_t>   fCandCabNvx( nhits );
	vector<Int_t>   fCandIdxNvx( nhits );
    TMath::Sort(nhits, &tau[0], &idx[0], kFALSE); // In increasing order

	fCandTimNvx.reserve( nhits );
	fCandTauNvx.reserve( nhits );	
	fCandCabNvx.reserve( nhits );	
	fCandIdxNvx.reserve( nhits );	
    for (Int_t i=0; i<nhits; i++)
	{
		fCandTimNvx[i] = fCandTimRaw[ idx[i] ];
		fCandTauNvx[i] = tau[ idx[i] ];
		fCandCabNvx[i] = fCandCabRaw[ idx[i] ];
		fCandIdxNvx[i] = idx[i];
	}

	// Put it into candidate on nvx
	wndnvx.init_variant( fCandCabNvx, fCandTimNvx, fCandTauNvx, nhits, vtx );
	
}



// Almost identical to Akutsu-san style
Int_t getUSNhitsXX( const Window &wnd, Int_t sidx, Float_t twid)
{
	vector<Float_t> v( wnd.nhit );
	for ( int i = 0; i < wnd.nhit; ++i ) {
		v[i] = wnd.hit[i].tau;
	}
// Compute num. of hits within timing width "twid".
// Only hits in upper side in terms of timing are
// counted w.r.t the first hit having the index
// "sidx"

    Int_t i=-1,
		  n=-1;
	i=sidx;
	n=(Int_t)v.size();
    while (1) 
	{
		i++;
		if( (i>n-1 )						 ||
			(TMath::Abs((v[i]-v[sidx]))>twid) 
		  )
		{
			break;
		}
    }
    return TMath::Abs(i - sidx);
}



// Akutsu-san style fill_feature_vector
Int_t computeVariables( CableTimeHit *ct_bonsvtx, int ctsize, WindowBounds wb, float *bonsvtx, FeatureVector &fv )
{
	Int_t 	Np			=0,  // Number of candidates, fiacob ---> Np = 1 (below)
		  	N10			=0,
			N10n		=0,
			N10ni		=0,
			nhitaim		=-1,
		  	fstIdx		=-1,
			fstIdxn		=-1,
			tmpIdx		=-1,
			craw		=-1,
			nindex[200]	={},
			Nc			=-1,
			N300		=-1;
	Float_t	traw		=0.,
			t0n			=0.,
			nvtx[3]		={},
			nvtxres		=0.,
			npdist		=0.,
			npdist_mct	=0.,
			newtrms		=0.,
			llrca		=0.,
			twall		=0.,
			dwall		=0.,
			acpt		=0.,
			beta[5]		={},
			mintrms[4]	={};


	// Go through each candidate and compute
	// its feature variables
	Np = 1;  // fiacob ---> 1 candidate at a time, (akutsu=0)
	for(Int_t i=0; i<Np; i++)
	{
		fstIdx		=-1;
		fstIdxn		=-1;
		tmpIdx		=-1;
		N10			=0;
		N10n		=0;
		N10ni		=0;
		nhitaim		=0;
		nvtx[0]		=-9999.;
		nvtx[1]		=-9999.;
		nvtx[2]		=-9999.;
		nvtxres		=0.;
		npdist		=0.;
		newtrms		=-100.;
		llrca		=9999.;
		beta[0]		=-99.;
		beta[1]		=-99.;
		beta[2]		=-99.;
		beta[3]		=-99.;
		beta[4]		=-99.;
		mintrms[0]	=-99.;
		mintrms[1]	=-99.;
		mintrms[2]	=-99.;
		mintrms[3]	=-99.;
		twall		=-99.;
		dwall		=-99.;
		Nc			=0;
		t0n			=0.;


		fstIdx		= wb.bgn - ct_bonsvtx;  //_res._tindex[i];
		N10			= wb.end - wb.bgn;  //_res._n10[i];
		const int EXTRA = 12;
		nhitaim 	=N10 + EXTRA;
		// Fit neutron capture vertex
		// using N10 hits	
		//
		//_hm->clearCandRaw();
		//_hm->setCandRaw(fstIdx, N10);
		//_f2p2g->minimizeStdDevTTof(_hm->CandTimRaw(), _hm->CandCabRaw(), N10, _pvx, nvtx, 10000);	
		Window wnd4fit;
		wnd4fit.init( wb.bgn, wb.end, bonsvtx );
		nvtxres = nfit_akutsu( wnd4fit, wnd4fit.nhit, bonsvtx, nvtx, 10000 );

		//
		// Select PMT hits in order to
		// compute N10n
		//
		tmpIdx	=fstIdx;
		tmpIdx	-=EXTRA/2;
		Window wndraw; // //_hm->clearCandRaw(); candidate on bvx
		wndraw.init( ct_bonsvtx + tmpIdx, ct_bonsvtx + tmpIdx + nhitaim, bonsvtx ); //_hm->setCandRaw(tmpIdx, nhitaim); candidate on bvx
		Window wndnvx; //_hm->clearCandNvx(); candidate on nvx
		computeCandTauNvx( wndraw, wndnvx, nvtx );//_hm->computeCandTauNvx(nvtx);		


		nhitaim=0;
		nhitaim = wndnvx.nhit;//nhitaim=(Int_t)_hm->CandTauNvx().size();

		for(Int_t j=0; j<nhitaim; j++)
		{
		//getUSNhitsXX(const vector<Float_t>& v, Int_t sidx, Float_t twid)
			N10ni=getUSNhitsXX( wndnvx, j, 10. );//_f2p2g->getUSNhitsXX(_hm->CandTauNvx(), j, 10.);	
			if( N10ni>N10n )
			{
				N10n=N10ni;
				fstIdxn=j;
				t0n=wndnvx.hit[j].tau;//_hm->CandTauNvx()[ j ];
			}	
		}
		Window wndneut;
		vector<Int_t> megadummycab( N10n );
		vector<Float_t> megadummytim( N10n );
		vector<Float_t> megadummytau( N10n );
		for ( int k = 0; k < N10n; ++k ) {
			megadummycab[k] = wndnvx.hit[fstIdxn+k].cable;
			megadummytim[k] = wndnvx.hit[fstIdxn+k].t;
			megadummytau[k] = wndnvx.hit[fstIdxn+k].tau;
		}
		wndneut.init_variant( megadummycab, megadummytim, megadummytau, N10n, nvtx ); //_hm->setSelectedCandHits(fstIdxn, N10n);	
		if ( wndneut.nhit < 7 || wndneut.nhit > 50 ) {
			cerr << "Limit 7 50" << '\n';
			return 2;
		}


		//=========================
		// Let's use my variables
		//=========================
		// Fill the window structure
		Window wnd;
		wnd.init( wb.bgn, wb.end, bonsvtx );
		if ( fvcheck_pmtcable( wnd ) ) {
			cerr << " ---> ERROR: fvcheck_pmtcable" << '\n';
			return 1;
		}


	    // Fill sbvec_bonsvtx and counters
		fvfill_sbvec( wnd, fv.sbvec_bonsvtx, fv.nsig_bonsvtx, fv.nbkg_bonsvtx );

		// Fitter
		float taurms_stat[12];
		Fitter fitter;
		//fitter.init_vtx( wnd, vtx );  // 16 Aug 2019: Possibly useless!
		fitter.sample_taurms( wnd, TANKR, TANKZ, 1000, taurms_stat );
		if ( fvcheck_pmtcable( wndneut ) ) {
			cerr << " ---> ERROR: fvcheck_pmtcable(wndneut)" << '\n';
			return 1;
		}
		wndneut.init_spheremean();
		if ( wndneut.spheremean[3] == 0. ) {
			// Considered a negative, no process further
			// Report to NtupleMaker
			cerr << "wndneut.spheremean[3] == 0." << '\n';
			return 1;
		}
		wndneut.init_distancevector();
		wndneut.init_distancematrix();


	    //----------------------
		// Classifer variables
		//----------------------
    
		// Akutsu-san (almost) variables
		fvfill_N10nvx( wndneut, fv.N10nvx );
		//fvfill_N300nvx( surround_bvx, surroundsize_bvx, selected_wndbnd_nvx, fv.N300nvx ); 
		fvfill_N300S_akutsu( ct_bonsvtx, ctsize, wndneut, fv.N10nvx, fv.N300S );
		//diagnose_N200nvx( ct_bonsvtx, ctsize, wndneut, fv.N200nvx ); //CPM N200 plot 180121
		//float angular_threshold = 0.97;
		//int cluster_threshold = 3;
		//fvfill_Nclus( wndneut, angular_threshold, cluster_threshold, fv.Nclus );  // Not sure is like Akutsu-san
		//fvfill_Nclus_3clique( wndneut, angular_threshold, fv.Nclus );
		fvfill_Nclus_akutsu( wndneut, 3, 0.97, fv.Nclus );
		computeNClusters( wndneut, wndneut.nhit, 3, 0.97, fv.N10nvx, fv.NcS );
		fvfill_cang_stat( wndneut, fv.cangmean, fv.cangstddev, fv.cangskew, fv.cangkurt, fv.cangcntnan );  // Akutsu takes lig-likelihood...
		fvfill_llrca( wndneut, fv.llrca, fv.nllrca );
		fvfill_beta( wndneut, fv.beta );
		fvfill_accepave( wndneut, fv.accepave );
		fv.taurms = nvtxres;  //fitter.minimum.val;
		fvfill_mintaurms6( wndneut, fv.mintaurms6 );
		fvfill_ndwall( wndneut, fv.ndwall );
		fvfill_ntowall( wndneut, fv.ntowall );

		// Fabio variables
		fvfill_distancevector( wndneut, fv.d );
		fvfill_distance_stat( wndneut, fv.dmean, fv.drms, fv.ddiff );
		fv.spheremeannorm = wndneut.spheremean[3];
		fv.tauwidth = wndneut.tauwidth;
		fvfill_stau( wndneut, fv.stau );
		fvfill_staugeom( wndneut, fv.staugeom );
		for ( int i = 0; i < 12; ++i ) fv.taurms_stat[i] = taurms_stat[i];

		// Strong number check on floating point numbers of classifier variables
		strong_number_check( fv.llrca, "llrca" );
		strong_number_check( fv.nllrca, "nllrca" );
		//strong_number_check( fv.cangmean, "cangmean" );
		//strong_number_check( fv.cangstddev, "cangstddev" );
		//strong_number_check( fv.cangskew, "cangskew" );
		//strong_number_check( fv.cangkurt, "cangkurt" );
		for ( int i = 0; i < 5; ++i ) strong_number_check( fv.beta[i], "beta[" + to_string(i) + "]" );
		strong_number_check( fv.accepave, "accepave" );
		strong_number_check( fv.taurms, "taurms" );
		strong_number_check( fv.mintaurms6, "mintaurms6" );
		strong_number_check( fv.ndwall, "ndwall" );
		strong_number_check( fv.ntowall, "ntowall" );
		for ( int i = 0; i < 7; ++i ) strong_number_check( fv.d[i], "d[" + to_string(i) + "]" );
		strong_number_check( fv.dmean, "dmean" );
		strong_number_check( fv.drms, "drms" );
		strong_number_check( fv.ddiff, "ddiff" );
		strong_number_check( fv.spheremeannorm, "spheremeannorm" );
		for ( int i = 0; i < 7; ++i ) strong_number_check( fv.stau[i], "stau[" + to_string(i) + "]" );
		for ( int i = 0; i < 7; ++i ) strong_number_check( fv.staugeom[i], "staugeom[" + to_string(i) + "]" );
		for ( int i = 0; i < 12; ++i ) strong_number_check( fv.taurms_stat[i], "taurms_stat[" + to_string(i) + "]" );


		//----------------------
		// Spectator variables
		//----------------------
    
		// Fill ntag vertex info
		fv.ntagvtx[0] = nvtx[0];  //  fitter.minimum.vtx[0];  // sd.xmin[0];
		fv.ntagvtx[1] = nvtx[1];  //  fitter.minimum.vtx[1];  // sd.xmin[1];
		fv.ntagvtx[2] = nvtx[2];  //  fitter.minimum.vtx[2];  // sd.xmin[2];
		fv.ntagvtx_val = nvtxres;  //  fitter.minimum.val;   // sd.funcmin;
		fv.ntagvtx_flag = fitter.flag;

		// Fill bonsai vertex info
		for ( int i = 0; i < 3; ++i ) fv.bonsvtx[i] = bonsvtx[i];
		fv.bonsvtx_val = fitter.compute_taurms( wnd, bonsvtx );

		// Bonsai - Ntag vtx distance
		fv.dist_bonsntagvtx = 0.;
		for ( int i = 0; i < 3; ++i ) fv.dist_bonsntagvtx += ( nvtx[i] - bonsvtx[i] )*( nvtx[i] - bonsvtx[i] );
		fv.dist_bonsntagvtx = sqrt( fv.dist_bonsntagvtx );
		fv.diff_bonsntagvtx_val = fv.bonsvtx_val - fv.ntagvtx_val;

		// Fill sbvec_ntagvtx
		fvfill_sbvec( wndneut, fv.sbvec_ntagvtx, fv.nsig_ntagvtx, fv.nbkg_ntagvtx );

		// Considered a positive
		// Report to NtupleMaker a normally processed event
		//return 0;



		//
		// Calculate hit vectors of N10n hits
		// using fitted n cap. vertex "nvtx"
		//
		//_hm->computeCandHitVectors(nvtx); I dont need this

		// Now on everything is commented, these were lines
		// of Akutsu-san to compute feature vector variables
		/*
		// Normal running mode
		if( !_saveCAng )
		{
			// Calculate feature variables
			// betas 		 
			_f2p2g->computeIsotropyBetas(beta, N10n, _hm->CandHitVec());
			llrca			=_f2p2g->computeCAngLLR(N10n, _hm->CandHitVec());
			twall			=_f2p2g->computeToWall(N10n, _hm->CandHitVec(), nvtx);
			dwall			=_f2p2g->computeDWall(nvtx);
			acpt			=_f2p2g->computeAcceptance(_hm->CandCabNvx(), N10n, nvtx);
			Nc				=_f2p2g->computeNClusters(_hm->CandHitVec(), N10n, 3, 0.97);
			N300			=_f2p2g->computeN300(_hm->TimRaw(), _hm->CabRaw(), nvtx, t0n+5.);
			//mintrms
			_f2p2g->computeMinTrms(_hm->CandTauNvx(), N10n, mintrms);
			newtrms			=_f2p2g->computeTrms(_hm->CandTauNvx(), N10n);
			npdist			=_f2p2g->computeVertexDist(nvtx, _pvx);

			nvtxres			=-100.;
			npdist_mct		=-100.;
			if( _res._mctruth_neutron[i]==1 )	// MC truth neutrons
			{
				nvtxres		=_f2p2g->computeVertexDist(nvtx, _res._nvtx_mct[i]);
				npdist_mct	=_f2p2g->computeVertexDist(_res._nvtx_mct[i], _mctpvx);
			}

			// fill the calculation results
			_res._nvtx[i][0]		=nvtx[0];
			_res._nvtx[i][1]		=nvtx[1];
			_res._nvtx[i][2]		=nvtx[2];

			_res._nvtxres[i]		=nvtxres;
			_res._npdist[i]			=npdist;
			_res._npdist_mct[i]		=npdist_mct;

			_res._beta1[i]			=beta[0];
			_res._beta2[i]			=beta[1];
			_res._beta3[i]			=beta[2];
			_res._beta4[i]			=beta[3];
			_res._beta5[i]			=beta[4];

			_res._mintrms6[i]		=mintrms[3];
			_res._trms[i]			=newtrms;

			_res._llrca[i]			=llrca;
			_res._n10n[i]			=N10n;
			_res._nc[i]				=Nc;
			_res._n300n[i]			=N300;
			_res._ntwall[i]			=twall;
			_res._ndwall[i]			=dwall;
			_res._accepAve[i]		=(Float_t)acpt/N10n;
			_res._t0n[i]			=t0n;
		}
		else
		{
			// This is very special mode.
			// If input PDFs used in above ** llrca ** computation 
			// need to be updated, then invoke this mode
			// by calling ** NeutronTag::setCherenkovAngleHist **.

			vector<Float_t> vcang;
			enum NTagCat::E_NTAG_CAT eNC=NTagCat::eNONE;
			if( _res._mctruth_neutron[i]==1 ){ eNC=NTagCat::eMCN; }
			else							 { eNC=NTagCat::eBKG; }

			_f2p2g	->compute3HitsCAng(N10n, _hm->CandHitVec(), vcang);
			_hca	->fillCAngHist(eNC, N10n, vcang);
		}
		*/
	}

	// NN output value and other variables
	// are computed
	//if( _isRunNN ){ runNeuralNetwork(); } // I dont need this

return 0;
}



// Return value:
// 0 == Processed normally, feature vector filled correctly
// 1 == Process stopped, report a false positive to NtupleMaker
int fill_feature_vector( CableTimeHit *ct_bonsvtx, int ctsize, WindowBounds wb, float *bonsvtx, FeatureVector &fv ) {
    // Fill the window structure
    Window wnd;
    wnd.init( wb.bgn, wb.end, bonsvtx );
    if ( fvcheck_pmtcable( wnd ) ) {
        cerr << " ---> ERROR: fvcheck_pmtcable" << '\n';
        return 1;
    }

    // DBG
    //cout << "BONSVTX " << bonsvtx[0] << " " << bonsvtx[1] << " " << bonsvtx[2] << endl;
    //for ( int i = 0; i < wnd.nhit; ++i ) {
        //cout << i << " " << wnd.hit[i].co[0] << " " << wnd.hit[i].co[1] << " " << wnd.hit[i].co[2] << " " << wnd.hit[i].co[3] << " " << wnd.hit[i].co[4] << " " << wnd.hit[i].co[5] << " " << wnd.hit[i].vco[0] << " " << wnd.hit[i].vco[1] << " " << wnd.hit[i].vco[2] << " " << wnd.hit[i].vco[3] << " " << wnd.hit[i].vco[4] << " " << wnd.hit[i].vco[5] << " " << wnd.hit[i].nvco[0] << " " << wnd.hit[i].nvco[1] << " " << wnd.hit[i].nvco[2] << " " << wnd.hit[i].nvco[3] << " " << wnd.hit[i].nvco[4] << " " << wnd.hit[i].nvco[5] << endl;
    //}
//    float t;
//    float tau;
//    float stau;  // Shifted tau: tau[i] - tau[0]
//    float tdelta;  // Tau delta[i] = tau[i+1] - tau[i]
//    int cable;
//    float co[6];  // PMT position x, y, z, rho, zenith, azimuth with respect to SK center
//    float vco[6];  // PMT position x, y, z, rho, zenith, azimuth with respect to vertex center
//    float nvco[6];  // Normalized PMT position x, y, z, rho, zenith, azimuth with respect to vertex center
//    float spheremean_dist;
//    char sb;

    // Fill sbvec_bonsvtx and counters
    fvfill_sbvec( wnd, fv.sbvec_bonsvtx, fv.nsig_bonsvtx, fv.nbkg_bonsvtx );

    // Fitter
    float taurms_stat[12];
    Fitter fitter;
    //fitter.init_vtx( wnd, vtx );  // 16 Aug 2019: Possibly useless!
    fitter.sample_taurms( wnd, TANKR, TANKZ, 1000, taurms_stat );

    // Try the swarm
    //Swarm swarm( is_inside_sk, sk_sampler );
    //rms::nhit = wnd.nhit;
    //for ( int i = 0; i < wnd.nhit; ++i ) {
    //    rms::cable[i] = wnd.hit[i].cable;
    //    rms::t[i] = wnd.hit[i].t;
    //}

    // Steepest descent for minimization
    //SteepestDescent sd;
    //sd.init_dimension( 3 );
    //sd.init_func_constr( rms::taurms, is_inside_sk );
    //float guess_vtx[3];
    //guess_vtx[0] = taurms_stat[8]; guess_vtx[1] = taurms_stat[9]; guess_vtx[2] = taurms_stat[10];
    //sd.extremalize_lim( guess_vtx, 0.2, -1, 24765 );  // limit on number of step given by diagonalSK / step

    // CONCENTRIC CUBIC FITTER BEGIN
    //float guess_vtx[3];
    //guess_vtx[0] = taurms_stat[8]; guess_vtx[1] = taurms_stat[9]; guess_vtx[2] = taurms_stat[10];
    //float ccf_cyclefactor = 0.5;
    //int ccf_ncycle = 4;
    //fitter.concentric_cube_fitter( wnd, guess_vtx, TANKZ * ccf_cyclefactor, ccf_ncycle, ccf_cyclefactor );
    //fprintf( stderr, "bonsvtx = %f %f %f %f\n", bonsvtx[0], bonsvtx[1], bonsvtx[2], fitter.compute_taurms( wnd, bonsvtx ) );
    //fprintf( stderr, "minimum = %f %f %f %f\n", fitter.minimum.vtx[0], fitter.minimum.vtx[1], fitter.minimum.vtx[2], fitter.minimum.val );  // DBG
    //fprintf( stderr, "distance = %f\n", sqrt((fitter.minimum.vtx[0]-bonsvtx[0])*(fitter.minimum.vtx[0]-bonsvtx[0]) + (fitter.minimum.vtx[1]-bonsvtx[1])*(fitter.minimum.vtx[1]-bonsvtx[1]) + (fitter.minimum.vtx[2]-bonsvtx[2])*(fitter.minimum.vtx[2]-bonsvtx[2])) );
    // CONCENTRIC CUBIC FITTER END

    // AKUTSU FITTER BEGIN
    fitter.minimum.val = nfit_akutsu( wnd, wnd.nhit, bonsvtx, fitter.minimum.vtx, 10000 );
    // AKUTSU FITTER END

    // ALTERNATIVE APPROACH START
    //CableTimeHit surround_bvx[MAXPM];
    //CableTimeHit surround_nvx[MAXPM];
    //int surroundsize_bvx = -1;
    //int surroundsize_nvx = -1;
    //WindowBounds candidate_wndbnd_nvx[1000];
    //int candidate_size_nvx = -1;
    //surround_n10bonsvtx( ct_bonsvtx, ctsize, wb, surround_bvx, surroundsize_bvx ); 
    //fill_sort_tau( surround_bvx, surroundsize_bvx, fitter.minimum.vtx );
    //surround_n10ntagvtx( surround_bvx, surroundsize_bvx, wb.end - wb.bgn, surround_nvx, surroundsize_nvx ); 
    //dryfind_n10( surround_nvx, surroundsize_nvx, candidate_wndbnd_nvx, candidate_size_nvx );
    //if ( candidate_size_nvx == 0 ) return 2;
    //cut_n200( surround_nvx, surroundsize_nvx, candidate_wndbnd_nvx, candidate_size_nvx );
    //if ( candidate_size_nvx == 0 ) return 2;
    //WindowBounds selected_wndbnd_nvx = select_n10ntagvtx( surround_nvx, surroundsize_nvx, candidate_wndbnd_nvx, candidate_size_nvx );
    //if ( candidate_size_nvx == 0 ) return 2;

    //printf( "\n\n*** N10 WINDOW ***\n" );
    //for ( int i = 0; i < wb.end - wb.bgn; ++i ) printf( "%d %f %c\n", i, wb.bgn[i].tau, wb.bgn[i].sb ); // DBG
    //printf( "\n*** SURROUND_BVX WINDOW ***\n" );
    //for ( int i = 0; i < surroundsize_bvx; ++i ) printf( "%d %f %c %d\n", i, surround_bvx[i].tau, surround_bvx[i].sb, surround_bvx[i].flag_bonsvtx );
    //printf( "\n*** SURROUND_NVX WINDOW ***\n" );
    //for ( int i = 0; i < surroundsize_nvx; ++i ) printf( "%d %f %c %d\n", i, surround_nvx[i].tau, surround_nvx[i].sb, surround_nvx[i].flag_bonsvtx );
    //watch( selected_wndbnd_nvx.bgn->tau );
    //watch( selected_wndbnd_nvx.end->tau ); 
    //watch( selected_wndbnd_nvx.end - selected_wndbnd_nvx.bgn );
    // ALTERNATIVE APPROACH END

    // AKUTSU APPROACH START
    CableTimeHit ctnvx[1000];
    int ctnvxsize = -1;
    WindowBounds selected_wndbnd_nvx;
    select_n10ntagvtx_akutsu( ct_bonsvtx, ctsize, wb, fitter.minimum.vtx, ctnvx, ctnvxsize, selected_wndbnd_nvx );
    if ( selected_wndbnd_nvx.end - selected_wndbnd_nvx.bgn < 7 || selected_wndbnd_nvx.end - selected_wndbnd_nvx.bgn > 50 ) {
        cerr << "Limit 7 50" << '\n';
        return 2;
    }
    // AKUTSU APPROACH END
    
    Window wndneut;
    wndneut.init( selected_wndbnd_nvx.bgn, selected_wndbnd_nvx.end, fitter.minimum.vtx );
    if ( fvcheck_pmtcable( wndneut ) ) {
        cerr << " ---> ERROR: fvcheck_pmtcable(wndneut)" << '\n';
        return 1;
    }
    wndneut.init_spheremean();
    if ( wndneut.spheremean[3] == 0. ) {
        // Considered a negative, no process further
        // Report to NtupleMaker
        cerr << "wndneut.spheremean[3] == 0." << '\n';
        return 1;
    }
    wndneut.init_distancevector();
    wndneut.init_distancematrix();
    //watch( selected_wndbnd_nvx.bgn->tau );
    //watch( selected_wndbnd_nvx.end->tau );
    //watch( selected_wndbnd_nvx.end - selected_wndbnd_nvx.bgn );


    //----------------------
    // Classifer variables
    //----------------------
    
    //DBG
    //for ( int i = 0; i < wndneut.nhit; ++i ) {
        //cout << wndneut.hit[i].t << " " << wndneut.hit[i].tau << " " << wndneut.hit[i].stau << " " << wndneut.hit[i].tdelta << " " << wndneut.hit[i].cable << " " << wndneut.hit[i].sb << endl;
    //}

    // Akutsu-san (almost) variables
    fvfill_N10nvx( wndneut, fv.N10nvx );
    //fvfill_N300nvx( surround_bvx, surroundsize_bvx, selected_wndbnd_nvx, fv.N300nvx ); 
    fvfill_N300S_akutsu( ct_bonsvtx, ctsize, wndneut, fv.N10nvx, fv.N300S );
    //float angular_threshold = 0.97;
    //int cluster_threshold = 3;
    //fvfill_Nclus( wndneut, angular_threshold, cluster_threshold, fv.Nclus );  // Not sure is like Akutsu-san
    //fvfill_Nclus_3clique( wndneut, angular_threshold, fv.Nclus );
    fvfill_Nclus_akutsu( wndneut, 3, 0.97, fv.Nclus );
    computeNClusters( wndneut, wndneut.nhit, 3, 0.97, fv.N10nvx, fv.NcS );
    fvfill_cang_stat( wndneut, fv.cangmean, fv.cangstddev, fv.cangskew, fv.cangkurt, fv.cangcntnan );  // Akutsu takes lig-likelihood...
    fvfill_llrca( wndneut, fv.llrca, fv.nllrca );
    fvfill_beta( wndneut, fv.beta );
    fvfill_accepave( wndneut, fv.accepave );
    fv.taurms = fitter.minimum.val;
    fvfill_mintaurms6( wndneut, fv.mintaurms6 );
    fvfill_ndwall( wndneut, fv.ndwall );
    fvfill_ntowall( wndneut, fv.ntowall );

    // Fabio variables
    fvfill_distancevector( wndneut, fv.d );
    fvfill_distance_stat( wndneut, fv.dmean, fv.drms, fv.ddiff );
    fv.spheremeannorm = wndneut.spheremean[3];
    fv.tauwidth = wndneut.tauwidth;
    fvfill_stau( wndneut, fv.stau );
    fvfill_staugeom( wndneut, fv.staugeom );
    for ( int i = 0; i < 12; ++i ) fv.taurms_stat[i] = taurms_stat[i];

    // Strong number check on floating point numbers of classifier variables
    strong_number_check( fv.llrca, "llrca" );
    strong_number_check( fv.nllrca, "nllrca" );
    //strong_number_check( fv.cangmean, "cangmean" );
    //strong_number_check( fv.cangstddev, "cangstddev" );
    //strong_number_check( fv.cangskew, "cangskew" );
    //strong_number_check( fv.cangkurt, "cangkurt" );
    for ( int i = 0; i < 5; ++i ) strong_number_check( fv.beta[i], "beta[" + to_string(i) + "]" );
    strong_number_check( fv.accepave, "accepave" );
    strong_number_check( fv.taurms, "taurms" );
    strong_number_check( fv.mintaurms6, "mintaurms6" );
    strong_number_check( fv.ndwall, "ndwall" );
    strong_number_check( fv.ntowall, "ntowall" );
    for ( int i = 0; i < 7; ++i ) strong_number_check( fv.d[i], "d[" + to_string(i) + "]" );
    strong_number_check( fv.dmean, "dmean" );
    strong_number_check( fv.drms, "drms" );
    strong_number_check( fv.ddiff, "ddiff" );
    strong_number_check( fv.spheremeannorm, "spheremeannorm" );
    for ( int i = 0; i < 7; ++i ) strong_number_check( fv.stau[i], "stau[" + to_string(i) + "]" );
    for ( int i = 0; i < 7; ++i ) strong_number_check( fv.staugeom[i], "staugeom[" + to_string(i) + "]" );
    for ( int i = 0; i < 12; ++i ) strong_number_check( fv.taurms_stat[i], "taurms_stat[" + to_string(i) + "]" );


    //----------------------
    // Spectator variables
    //----------------------
    
    // Fill ntag vertex info
    fv.ntagvtx[0] = fitter.minimum.vtx[0];  // sd.xmin[0];
    fv.ntagvtx[1] = fitter.minimum.vtx[1];  // sd.xmin[1];
    fv.ntagvtx[2] = fitter.minimum.vtx[2];  // sd.xmin[2];
    fv.ntagvtx_val = fitter.minimum.val;   // sd.funcmin;
    fv.ntagvtx_flag = fitter.flag;

    // Fill bonsai vertex info
    for ( int i = 0; i < 3; ++i ) fv.bonsvtx[i] = bonsvtx[i];
    fv.bonsvtx_val = fitter.compute_taurms( wnd, bonsvtx );

    // Bonsai - Ntag vtx distance
    fv.dist_bonsntagvtx = 0.;
    for ( int i = 0; i < 3; ++i ) fv.dist_bonsntagvtx += ( fitter.minimum.vtx[i] - bonsvtx[i] )*( fitter.minimum.vtx[i] - bonsvtx[i] );
    fv.dist_bonsntagvtx = sqrt( fv.dist_bonsntagvtx );
    fv.diff_bonsntagvtx_val = fv.bonsvtx_val - fv.ntagvtx_val;

    // Fill sbvec_ntagvtx
    fvfill_sbvec( wndneut, fv.sbvec_ntagvtx, fv.nsig_ntagvtx, fv.nbkg_ntagvtx );

    // Considered a positive
    // Report to NtupleMaker a normally processed event
    return 0;
}



/*
 * Check whether a selected window is signal or background
 * If signal returns index of secondary particle that matches (2.22 MeV gamma within 100 nsec)
 * If background returns -1
 *
 * Also fills t0, trgofst, and tds, that are important times
 * for sig / bkg decision
*/
/*
int candidate_is_signal( T2KLowE &t2kle, WindowBounds wb, float &t0, float &trgofst, float &tds ) {
    float secondary_pabs;
    
    // Fill trigger info
    sort( wb.bgn, wb.end, compare_time );  // Sort by tiskz
    t0 = wb.bgn->tiskz; 
    trginfo_( &trgofst );
    tds = t0 - 1000. + trgofst;
    sort( wb.bgn, wb.end, compare_tau );  // Re-sort by tau
    
    // Loop on secondary particles
    for ( int i = 0; i < t2kle.nscndprt; ++i ) {
        
        // Require 2.22 MeV gamma, with correct mechanism
        secondary_pabs = (t2kle.pscnd[i][0]*t2kle.pscnd[i][0])+(t2kle.pscnd[i][1]*t2kle.pscnd[i][1])+(t2kle.pscnd[i][2]*t2kle.pscnd[i][2]);
        secondary_pabs = sqrt( secondary_pabs );
        if ( t2kle.iprtscnd[i] == 22 && t2kle.lmecscnd[i] == 18 && abs( secondary_pabs - 2.22 ) < 0.1 ) {
            
            // Require correct trigger
           if ( abs( t2kle.tscnd[i] - tds ) < 100. ) return i;
        }

    }

    return -1;
}
*/


/*
 * VARIANT OF ABOVE FUNCTION
 * Check whether a selected window is signal or background
 * If signal returns index of secondary particle that matches (2.22 MeV gamma within 100 nsec)
 * If background returns -1
 *
 * Also fills t0, trgofst, and tds, that are important times
 * for sig / bkg decision
*/


/*int candidate_is_signal( int nscndprt, int iprtscnd[], int lmecscnd[], float tscnd[], float trgofst, float pscnd[][3], WindowBounds wb, float &t0, float &tds ) {
    float secondary_pabs;
    
    // Fill trigger info
    sort( wb.bgn, wb.end, compare_time );  // Sort by tiskz
    t0 = wb.bgn->tiskz; 
    //trginfo_( &trgofst );
    tds = t0 - 1000. + trgofst;
    sort( wb.bgn, wb.end, compare_tau );  // Re-sort by tau
    
    // Loop on secondary particles
    for ( int i = 0; i < nscndprt; ++i ) {
        
        // Require 2.22 MeV gamma, with correct mechanism
        secondary_pabs = (pscnd[i][0]*pscnd[i][0])+(pscnd[i][1]*pscnd[i][1])+(pscnd[i][2]*pscnd[i][2]);
        secondary_pabs = sqrt( secondary_pabs );
        if ( iprtscnd[i] == 22 && lmecscnd[i] == 18 && abs( secondary_pabs - 2.22 ) < 0.1 ) {
            
            // Require correct trigger
           if ( abs( tscnd[i] - tds ) < 100. ) return i;
        }

    }

    return -1;
}
*/


/*
 * VARIANT OF ABOVE FUNCTION
 * Check whether a selected window is signal or background
 * If signal returns index of secondary particle that matches (2.22 MeV gamma within 100 nsec)
 * If background returns -1
 *
 * Also fills t0, trgofst, and tds, that are important times
 * for sig / bkg decision
 * GD N CAPTURE ONLY ADAPTATION OF ABOVE FUNCTION 28/03/21
*/



/*int candidate_is_signal( int nscndprt, int iprtscnd[], int lmecscnd[], float tscnd[], float trgofst, float pscnd[][3], WindowBounds wb, float &t0, float &tds ) {
    float secondary_pabs;
    int nGam[500];
    float totGamEn[500];
    int prm_truall = 0;
    
    
    // Fill trigger info
    sort( wb.bgn, wb.end, compare_time );  // Sort by tiskz
    t0 = wb.bgn->tiskz; 
    //trginfo_( &trgofst );
    tds = t0 - 1000. + trgofst;
    sort( wb.bgn, wb.end, compare_tau );  // Re-sort by tau
    
    // Loop on secondary particles
    for ( int i = 0; i < nscndprt; ++i ) {
        
        // Require 7.9 or 8MeV gamma, with correct mechanism
        secondary_pabs = (pscnd[i][0]*pscnd[i][0])+(pscnd[i][1]*pscnd[i][1])+(pscnd[i][2]*pscnd[i][2]);
        secondary_pabs = sqrt( secondary_pabs );

	if ( lmecscnd[i] == 18 ) {
	  nGam[prm_truall]=0;
	  totGamEn[prm_truall]=0;
	  
	  for (Int_t j=0;j<nscndprt;j++) {
	    if (fabs((double)(tscnd[i]-tscnd[j]))<1.e-7) {//judge whether this is a new n-capture
	      //                      newTime=false;

	      if(iprtscnd[j]==22) {

		nGam[prm_truall]+=1;
		totGamEn[prm_truall]+=sqrt(pscnd[j][0]*pscnd[j][0] + pscnd[j][1]*pscnd[j][1] + pscnd[j][2]*pscnd[j][2]);
		
		
	      }//count gammas produced in capture

	    }
	  }
	    
           
	  if ((i==0||(i!=0 && fabs(tscnd[i-1] - tscnd[i])>1e-7)) && nGam[prm_truall]>1 && (fabs(totGamEn[prm_truall] - 7.9)<0.1||fabs(totGamEn[prm_truall] - 8.5)<0.1)){
	    ++prm_truall;
	    // Require correct trigger
	    if ( abs( tscnd[i] - tds ) < 100. ) return i;
	    
	    
	  }
	}

    }

    return -1;
}

*/


/*
 * VARIANT OF ABOVE FUNCTION
 * Check whether a selected window is signal or background
 * If signal returns index of secondary particle that matches (2.22 MeV gamma within 100 nsec)
 * If background returns -1
 *
 * Also fills t0, trgofst, and tds, that are important times
 * for sig / bkg decision
 * GD and H N CAPTURE ONLY ADAPTATION OF ABOVE FUNCTION 28/03/21
*/



int candidate_is_signal( int nscndprt, int iprtscnd[], int lmecscnd[], float tscnd[], float trgofst, float pscnd[][3], WindowBounds wb, float &t0, float &tds ) {
    float secondary_pabs;
    int nGam[500];
    float totGamEn[500];
    int prm_truall = 0;
    
    
    // Fill trigger info
    sort( wb.bgn, wb.end, compare_time );  // Sort by tiskz
    t0 = wb.bgn->tiskz; 
    //trginfo_( &trgofst );
    tds = t0 - 1000. + trgofst;
    sort( wb.bgn, wb.end, compare_tau );  // Re-sort by tau
    
    // Loop on secondary particles
    for ( int i = 0; i < nscndprt; ++i ) {

      // Require 2.22 MeV gamma, with correct mechanism
        secondary_pabs = (pscnd[i][0]*pscnd[i][0])+(pscnd[i][1]*pscnd[i][1])+(pscnd[i][2]*pscnd[i][2]);
        secondary_pabs = sqrt( secondary_pabs );
        
         
        
        // Require 7.9 or 8MeV gamma, with correct mechanism
       
	if ( lmecscnd[i] == 18 ) {
	  nGam[prm_truall]=0;
	  totGamEn[prm_truall]=0;
	  
	  for (Int_t j=0;j<nscndprt;j++) {
	    if (fabs((double)(tscnd[i]-tscnd[j]))<1.e-7) {//judge whether this is a new n-capture
	      //                      newTime=false;

	      if(iprtscnd[j]==22) {

		nGam[prm_truall]+=1;
		totGamEn[prm_truall]+=sqrt(pscnd[j][0]*pscnd[j][0] + pscnd[j][1]*pscnd[j][1] + pscnd[j][2]*pscnd[j][2]);
		
		
	      }//count gammas produced in capture

	    }
	  }
	    
           
	  if ((i==0||(i!=0 && fabs(tscnd[i-1] - tscnd[i])>1e-7)) && nGam[prm_truall]>1 && (fabs(totGamEn[prm_truall] - 7.9)<0.1||fabs(totGamEn[prm_truall] - 8.5)<0.1)){
	    ++prm_truall;
	    // Require correct trigger
	    if ( abs( tscnd[i] - tds ) < 100. ) return i;
	    
	    
	  }

	  if ( nGam[prm_truall] == 1 && fabs(totGamEn[prm_truall] - 2.22 ) < 0.1 ) {

	    ++prm_truall;
	    if ( abs( tscnd[i] - tds ) < 100. ) return i;
	    
	  }
	}

    }

    return -1;
}






// Variation of candidate_is_signal function
// used for data (so no true information
int candidate_trigger_info( float trgofst, WindowBounds wb, float &t0, float &tds ) {
    float secondary_pabs;
    
    // Fill trigger info
    sort( wb.bgn, wb.end, compare_time );  // Sort by tiskz
    t0 = wb.bgn->tiskz; 
    //trginfo_( &trgofst );
    tds = t0 - 1000. + trgofst;
    sort( wb.bgn, wb.end, compare_tau );  // Re-sort by tau
    
    return -1;
}


























