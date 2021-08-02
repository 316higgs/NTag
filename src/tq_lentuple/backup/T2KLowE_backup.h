#ifndef __T2KLowE_h__
#define __T2KLowE_h__

#include "TROOT.h"
#include "TTree.h"
#include "tqrealroot.h"
#include <vector>
#include "skheadC.h"

#include "FeatureVector.h"
#include "runsummanager.h"

#define MAXVC 100
#define MAXVERT 300
#define MAXVCVERT 900
#define MAXSCNDPRT 500
#define MAXBINNUM 1000

class T2KLowE //for storing NCGamma variables
{
public:
    Int_t           Is_mc;       //MC:1, Data:0

    // Data + MC Variables
    Int_t           nrun;
    Int_t           nsub;
    Int_t           nev;
    
    Float_t         potot;     //ID totpe (qismsk)
    Int_t           nhit;
    Int_t           n50;

    Float_t         dt0;
    Float_t         dt0vtx;    // dt0 corrected for vertex position
    Int_t           dt0type;   // Which gps was used
    Int_t           n30max;    // Maximum peak within 30 ns before event 
    Float_t         n30time;   // Time of the maximum 30 ns peak 
    Float_t         pos[3];    // Bonsai fit vertex
    Float_t         bdir[3];
    Float_t         erec;      // Bonsai fit energy
    Float_t         wall;
    Float_t         effwall;
    Float_t         ovaq;
    Float_t         angle;     // Cherenkov angle from 3-hit pmt angle plot 
    Float_t         angle_likelihood;
    Float_t         angle_15ns;     // Cherenkov angle from 3-hit pmt angle plot 
    Float_t         angle_likelihood_15ns;

    Float_t         goodness;  // Bonsai fit goodness
    Int_t           anglebinnum; //Bin number of 3 hit-pmt angle plot (0-90 degrees)
    Float_t         plotcontent[MAXBINNUM];  //Bin content of 3 hit-pmt angle plot
    //Int_t           n50;
    //Float_t         cossun;
    //Float_t         patlik;
    //Float_t         lsd;
    //Float_t         forwall;

    Int_t           mrrun;
    Int_t           date[3];
    Int_t           time[4];
    Float_t         elpsday;

    Int_t           nmue;                    

    // MC-only Variables
    Int_t           mode;               // neutrino interaction mode
    Float_t         wallv;              
    Float_t         posv[3];            //vertex position of initial (primary) interaction

    Int_t           numnu;              
    Int_t           ipnu[MAXVC];        
    Float_t         pnu[MAXVC];         //momentum of interaction neutrino
    //Float_t       enu;                //Energy of interaction neutrino
    Float_t         dirnu[MAXVC][3];    

    
    Int_t           npar;               //# of particle of vector(primary interaction)
    Int_t           ipv[MAXVC];         //vector particle code: pid
    Int_t           icrnv[MAXVC];       
    Float_t         dirv[MAXVC][3];     //direction of vector particle
    Float_t         pmomv[MAXVC];       //momentum of vector particles

    Int_t           npar2;              
    Float_t         wallv2[MAXVC];      
    Int_t           ipv2[MAXVC];        
    Float_t         posv2[MAXVC][3];    
    Float_t         dirv2[MAXVC][3];    
    Float_t         pmomv2[MAXVC];      

    Int_t           ng1;                // # of primary gamma
    Int_t           ng2;                // # of secondary gamma
    Float_t         toteg1;             //total primary gamma energy
    Float_t         toteg2;             //total secondary gamma energy

    Int_t           num_primary_gammas; //Cherenkov photon # of primary gamma
    Int_t           num_neutron_gammas; //Cherenkov photon # due to neutron
    Int_t           num_proton_gammas;  //Cherenkov photon # due to proton

    Int_t           IsPionAbs;          // Flag for pion absorption
    
    // Required for T2KReWeight, extra secondary tracking
    Int_t           nscndprt;                
    Int_t           itrkscnd[MAXSCNDPRT];    //[nscndprt]
    Float_t         vtxscnd[MAXSCNDPRT][3];  //[nscndprt]
    Float_t         pscnd[MAXSCNDPRT][3];    //[nscndprt]
    Int_t           iprtscnd[MAXSCNDPRT];    //[nscndprt]
    Float_t         tscnd[MAXSCNDPRT];       //[nscndprt]
    Int_t           iprntprt[MAXSCNDPRT];    //[nscndprt]
    Int_t           lmecscnd[MAXSCNDPRT];    //[nscndprt]
    Int_t           iprnttrk[MAXSCNDPRT];    //[nscndprt]
    Int_t           iorgprt[MAXSCNDPRT];     //[nscndprt]
    Int_t           iprntidx[MAXSCNDPRT];    //[nscndprt]

    Int_t           nchilds[MAXSCNDPRT];     //[nscndprt]
    Int_t           ichildidx[MAXSCNDPRT];   //[nscndprt]
    
    Float_t         pprnt[MAXSCNDPRT][3];    //[nscndprt]   
    Float_t         pprntinit[MAXSCNDPRT][3];//[nscndprt]
    Float_t         vtxprnt[MAXSCNDPRT][3];  //[nscndprt]
    Int_t           iflgscnd[MAXSCNDPRT];    //[nscndprt]
    
    Int_t           npvcscnd;                
    Int_t           nchildsvc[MAXVC];        //[npvcscnd]
    Int_t           ichildidxvc[MAXVC];      //[npvcscnd]

    Int_t           Neutmode;                
    Int_t           Npne;                    
    Int_t           Ipne[MAXVC];             //[Npne]
    Float_t         Abspne[MAXVC];           //[Npne]
    Float_t         Pvecne[MAXVC][3];        //[Npne]
    Int_t           Npvc;                    
    Int_t           Ipvc[MAXVC];             //[Npvc]
    Int_t           Ichvc[MAXVC];            //[Npvc]
    Int_t           Iorgvc[MAXVC];           //[Npvc]
    Int_t           Iflvc[MAXVC];            //[Npvc]
    Float_t         Abspvc[MAXVC];           //[Npvc]
    Float_t         Pvc[MAXVC][3];           //[Npvc]
    Float_t         Crsx;                    
    Float_t         Crsy;                    
    Float_t         Crsz;                    
    Float_t         Crsphi;                  
    Int_t           Numbndn;                 
    Int_t           Numbndp;                 
    Int_t           Numfrep;                 
    Int_t           Numatom;                 
    Int_t           Ibound;                  
    Int_t           Nvert;                   
    Float_t         Posvert[MAXVERT][3];     //[Nvert]
    Int_t           Iflgvert[MAXVERT];       //[Nvert]
    Int_t           Nvcvert;                 
    Float_t         Dirvert[MAXVCVERT][3];   //[Nvcvert]
    Float_t         Abspvert[MAXVCVERT];     //[Nvcvert]
    Float_t         Abstpvert[MAXVCVERT];    //[Nvcvert]
    Int_t           Ipvert[MAXVCVERT];       //[Nvcvert]
    Int_t           Iverti[MAXVCVERT];       //[Nvcvert]
    Int_t           Ivertf[MAXVCVERT];       //[Nvcvert]
    Float_t         Fsiprob;                 

    Int_t           nring;                   
    UInt_t          nhitac;                  
    Float_t         evis;                    
    UInt_t          ip[10];                  
    Float_t         dir[10][3];              
    Float_t         amom[10];                
    Float_t         amome[10];               
    Float_t         amomm[10];               
    Float_t         pi0like[2];              
    Float_t         pi0_e[2][2];             
    Float_t         pi0_dir[2][2][3];        
    Float_t         pi0mass[2];              

    T2KLowE(); 
    ~T2KLowE() {} ;
    void SetMC(bool _isMC) { Is_mc = _isMC; }
    void Clear();
    //void setBranch(TTree *tree);
    void createTree (TTree *tree);  

    float trgofst;
    int nqiskz;
    int icabiz[30*MAXPM];
    float tiskz[30*MAXPM];
    float qiskz[30*MAXPM];

    int validfit;
    float tbgn;  // time of first hit of event
    float tend;  // time of last hit of event
    float tdur;  // time duration between first and last hit
    
    // Dummy header
    skhead_common dummy_head;
    RSTuple rstuple;
};

#endif
