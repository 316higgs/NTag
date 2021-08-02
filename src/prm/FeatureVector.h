#ifndef _FEATURE_VECTOR_H__
#define _FEATURE_VECTOR_H__



typedef struct {
    //-------------------------
    // Select event variables
    //-------------------------
    
    int nrun;
    int nsub;
    int nev;
    float dt0vtx;
    float dt0;
    
    //-----------------------
    // Classifier variables
    //-----------------------

    // Akutsu-san (almost) variables
    int N10nvx;
    int N300S;
    int Nclus;
    int NcS;
    float llrca;
    float nllrca;
    float cangmean;
    float cangstddev;
    float cangskew;
    float cangkurt;
    int cangcntnan;
    float beta[5];
    float accepave;
    float taurms;
    float mintaurms6;
    float ndwall;
    float ntowall;

    // Fabio variables
    float d[7];  // distance vector ( aka distances from spheremean )
    float dmean, drms, ddiff;
    float spheremeannorm;
    float tauwidth;
    float stau[7];
    float staugeom[7];
    // taurms_stat from 0 to 11:
    // mean, rms, skewness, kurtosis
    // 1st quartile, median, 3rd quartile, inter-quartile range
    // minx, miny, minz, val
    float taurms_stat[12];
    
    //----------------------
    // Spectator variables
    //----------------------
    int neutrondegree;  // 1 = neutron from primary interaction, 2 = neutron from interactions in water
    int n200; //CPM 190121 added n200 to spectator variables
    float ntagvtx[3], ntagvtx_val; 
    int   ntagvtx_flag;
    float bonsvtx[3], bonsvtx_val;

    float dist_bonsntagvtx;  // Distance between Bonsai vertex and Ntag vertex
    float diff_bonsntagvtx_val;  // Difference between Bonsai and Ntag taurms values
    float dist_truentagvtx;  // Distance between True neutron capture and Ntag vertex (filled in NtupleMaker)
    float truenvx[3];  // True neutron vtx
    float truebvx[3];  // True neutrino vtx
    float erec, wall, effwall, ovaq, angle;  // Bonsai vertex quality variables
    float timetrupos;  // -9999. in nbkg
    float timefalpos;  // -9999. in nsig
	float capture_time;  // Expressed in nsec
	float neutron_mom;  // MC neutron momentum [MeV / c], -9999. in nbkg

    int nsig_bonsvtx;
    int nbkg_bonsvtx; 
    char sbvec_bonsvtx[400];

    int nsig_ntagvtx;
    int nbkg_ntagvtx;
    char sbvec_ntagvtx[400];

	int nrunsk;
	int nsubsk;
	int nevsk;

} FeatureVector;



#endif  // _FEATURE_VECTOR_H__
