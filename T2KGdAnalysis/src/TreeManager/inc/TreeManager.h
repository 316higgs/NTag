#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TTree.h"
#include "TFile.h"


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

int ipnu_woTagN = 0;
int ipnu_wTagN  = 0;

Float_t dirnu_woTagN[100][3];
Float_t dirnu_wTagN[100][3];

// === vector variables at neutrino interaction + additional info
int Npvc_woTagN = 0;
int Npvc_wTagN  = 0;

int Ipvc_woTagN = 0;
int Ipvc_wTagN  = 0;

int Ichvc_woTagN = 0;
int Ichvc_wTagN  = 0;

int Iflvc_woTagN = 0;
int Iflvc_wTagN  = 0;

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
Int_t ipp_woTagN;
Int_t ipp_wTagN;

Float_t evisible_woTagN;
Float_t evisible_wTagN;

Float_t elosssum_pipi_woTagN;
Float_t elosssum_pipi_wTagN;

// === NIWG information
Int_t wgts_maqeh_woTagN;
Int_t wgts_maqeh_wTagN;

Double_t DeltaPForEmiss0_woTagN;
Double_t DeltaPForEmiss0_wTagN;


class TreeManager {
  public:
  	TreeManager(int TagID){
  		if (TagID==0) woTagNtuple = new TTree("woTagNtuple", "");
      else wTagNtuple = new TTree("wTagNtuple", "");
  	};
  	virtual ~TreeManager(){};

    void SetBranch(int TagID);
  	void FillTree(int TagID);
    void WriteTree(TString OutName, int TagID);
};
