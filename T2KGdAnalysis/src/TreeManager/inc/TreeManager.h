#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TTree.h"
#include "TFile.h"


/*enum SampleChannel {
  numu_x_numu       = 13,
  numubar_x_numubar = 13,
  numu_x_nue        = 11,
  numubar_x_nuebar  = 11,
  nue_x_nue,
  nuebar_x_nuebar
};*/


//=== Tree ===
TTree* woTagNtuple;
TTree* wTagNtuple;


//=== Tree Branch ===

int iclass_woTagN = 0;
int iclass_wTagN  = 0;

int Ibound_woTagN = 0;
int Ibound_wTagN  = 0;

int mode_woTagN = 0;
int mode_wTagN  = 0;

// === vector variables at neutrino interaction
int numnu_woTagN = 0;
int numnu_wTagN  = 0;

Float_t pnu_woTagN[100];
Float_t pnu_wTagN[100];

int ipnu_woTagN[100];
int ipnu_wTagN[100];

Float_t dirnu_woTagN[100][3];
Float_t dirnu_wTagN[100][3];

Int_t npar_woTagN;
Int_t npar_wTagN;

Float_t dirv_woTagN[100][3];
Float_t dirv_wTagN[100][3];

Double_t wgtosc_woTagN;
Double_t wgtosc_wTagN;

// === vector variables at neutrino interaction + additional info
int Npvc_woTagN = 0;
int Npvc_wTagN  = 0;

int Ipvc_woTagN[100];
int Ipvc_wTagN[100];

int Ichvc_woTagN[100];
int Ichvc_wTagN[100];

int Iflvc_woTagN[100];
int Iflvc_wTagN[100];

// === SK variables (for T2KReWeight)
Int_t nring_woTagN;
Int_t nring_wTagN;

Int_t nev_woTagN;
Int_t nev_wTagN;

Int_t nhitac_woTagN;
Int_t nhitac_wTagN;

Float_t wall_wTagN;
Float_t wall_woTagN;

Float_t evis_wTagN;
Float_t evis_woTagN;

// === fiTQun variables
Int_t fqnse_woTagN = 0;
Int_t fqnse_wTagN  = 0;

Float_t fq1rdir_woTagN[100][7][3];
Float_t fq1rdir_wTagN[100][7][3];

Float_t fqmomm_woTagN;
Float_t fqmomm_wTagN;

Float_t fqmome_woTagN;
Float_t fqmome_wTagN;

Int_t fqnmrfit_woTagN;
Int_t fqnmrfit_wTagN;

Float_t fqmrdir_woTagN[100][6][3];
Float_t fqmrdir_wTagN[100][6][3];

Float_t fqmrmom_woTagN[100][6][3];
Float_t fqmrmom_wTagN[100][6][3];

// === MR variables
//Int_t ip_wTagN;
//Int_t ip_woTagN;
UInt_t ip_wTagN[100];
UInt_t ip_woTagN[100];

Int_t ipp_woTagN;
Int_t ipp_wTagN;

Int_t ippp_woTagN;
Int_t ippp_wTagN;

Float_t evisible_woTagN;
Float_t evisible_wTagN;

Float_t elosssum_pipi_woTagN;
Float_t elosssum_pipi_wTagN;

// === NIWG information
//Int_t wgts_maqeh_woTagN;
//Int_t wgts_maqeh_wTagN;
Double_t wgts_maqeh_woTagN;
Double_t wgts_maqeh_wTagN;

Double_t DeltaPForEmiss0_woTagN;
Double_t DeltaPForEmiss0_wTagN;


class TreeManager {
  public:
  	TreeManager(int TagID){
  		//if (TagID==0) woTagNtuple = new TTree("woTagNtuple", "");
      //else wTagNtuple = new TTree("wTagNtuple", "");

      if (TagID==0) woTagNtuple = new TTree("mtuple", "");
      else wTagNtuple = new TTree("mtuple", "");
  	};
  	virtual ~TreeManager(){};

    void FillBrankTree(int TagID);

    void SetBranch(int TagID);
  	void FillTree(int TagID);
    void WriteTree(TString OutName, int TagID);
};
