#ifndef __NtupleMaker_H__
#define __NtupleMaker_H__

#include "T2KLowE.h"
#include "TTree.h"
#include "TreeManager.h"
#include "SuperManager.h"
#include <fstream>

#include "ConnectionTable.h"
#include "apmueC.h"
#include "./include/fitqunoutC.h"
//#include "spliTChanOutC.h"

// 8jul2019
#include "FeatureVector.h"
#include "prm.h"

// Extract information from SK files
extern "C" {
    void zbsinit_();
    void skopenf_(int&, int&, const char*, int&, long);
    void skclosef_(int&);
    void skcread_(int&, int&);
    void skoptn_(const char*, long);
    void kzwrit_(int&);
    void trginfo_(float *trgofst);
    void kzinit_();
    void kzbloc_(const char*, int&);
    void kzeclr_();
    void skgetv_();
    void readfqzbsbank_(int*); //Added by Seidai
    void inpmt_(float*, int*); //Added by Seidai (2021.6.25)
    
    //void lowbs3get_();
    
    //void aprstbnk_(int*);
    //void bonsai_ini_();
    //void bonsai_fit_(float *t0, float *tisksend, float *qisksend, int *cabsend, int *ntisksend, float *tenergy, float *tvx, float *tvy, float *tvz, float *tbsgood);
    //void bonsai_end_();
    
    // Wrapper that avoids creating rflists externally
    //void fort_fopen_      (int*   , const char*, char*, int* );
    void fort_fopen_      (int*   , const char*, char*, int*, int );
    
    //Add for loading fortran subroutine
    void vcrdvccm_();
    //void nerdnebk_();
    void nerdnebk_( float* );
    void nerdcrsbk_();
    void nerdnetarg_();
    void nerdfsibk_();
    void vcclcm_();
    void pd2gt_(int&, int&);
    //float elapseday_(int*, int*);

    union zbsget {
        Int_t idata[999];
        Float_t rdata[999];
    }zbsget;
    
    void kzget1_(const char*, int&, int&, int*, long);
    
    // for decay-e search from muelib 
    //void muechk_( double*, int* ); 
    void muechk_( float*, int* ); 
    
}

const Int_t MAXPMT = 11146;

const int NMIS    = 17;
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





class TH1D;

class NtupleMaker
{
public:
    NtupleMaker();
    ~NtupleMaker();
    
    void OpenInfile(const char * infile);
    void OpenOutfile(const char * outfile);
	void SetAmbePosition(const char * ambepos);
    void OpenSbifile(const char * sbifile);
    void OpenInlogfile(const char * inlogfile);
    void OpenOutlogfile(const char * outlogfile);
    void Finish();
    
    bool ReadNextEvent();
    bool ReadMCEvent();
    bool ReadDataEvent();
    void SaveToTree();
    

    void SetVerbose() { verbose = true; };
    void SetQuiet()   { verbose = false; };

    int like_all;
    int like_fail;


private:
    
    TString  infile;
    TString  outfile;
    string sbifile;
    string inlogfile;
    string outlogfile;
    string rsfile;
    TString  txtfile;
    ifstream txtstream;
    int      luni;
    bool     isMC;
    bool     verbose;

    TH1D *hcheren;
    const int nstep;
    const int minNtof;
    double angledown;
    double angleup;
    double tchelow;
    double tchehigh;

    int mrfirst[100];
    int mrlast[100];

    TFile    *fout_root;
    TTree    *theOTree;
    T2KLowE  ncg; //used to store ngcamma variables

    //reading data
    TreeManager* mgr;
    TTree* datatree;

    Header    *HEAD;
    TQReal    *TQREAL;
    TQReal    *TQAREAL;
    LoweInfo  *LOWE;
    AtmpdInfo *ATMPD;
    UpmuInfo  *UPMU;
    MuInfo    *MU;
    SLEInfo   *SLE;

    // SBI and LOG management
    FILE *psbifile;
    FILE *pinlogfile;
    FILE *poutlogfile;

    int sbi_nevt;
    int sbi_ievt;
    int sbi_unmasked_nhit;
    int sbi_masked_nhit;
    
    int  inlog_ievt;
    int  inlog_nhit;
    char inlog_evtflag;
    
    int  outlog_ievt;
    int  outlog_nhit;
    char outlog_evtflag;

    void inlog_read_nextevt( FILE *pfile, int &ievt, int &nhit, char &evtflag );
    void outlog_write_nextevt( FILE *pfile, int ievt, int nhit, char evtflag );

    void MomAndDir( float* pin, Float_t &pout, Float_t *dirout);
    void GetScndPrt();
    void GetVect2();
    void CountTrueGammas();
    void CherenkovAngle(double *, bool limithits = true);
    double GetLinearLikelihood(TH1D *hche);
    double lfrsqrt(Double_t a2, Double_t b2, Double_t c2);
    int getNhits(Float_t *v, int start_index, Float_t width, int nhits);
    void MaxHitsInWindow   (Float_t *t, int ALLHITS, float width, int &maxnhits, int &maxindex); // with getNhits
    void MinimumWidthWindow(Float_t *t, int ALLHITS, float width, int &maxnhits, int &maxindex); // lftofsel
    Bool_t checkMiss(Int_t cab);
    int FindMRRun(int skrun);

	// AMBE
	bool is_ambe;
	float ambe_pos[3];
};
#endif 
