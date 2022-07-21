#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TTree.h"
#include "TFile.h"


//=== Tree ===
TTree* tree;


//=== Tree Branch ===
//float OneRingRejectCCQE = 0.;

//Primary muon direction (truth and reco)
float TrueMuDirX = 0.;
float TrueMuDirY = 0.;
float TrueMuDirZ = 0.;
float RecoMuDirX = 0.;
float RecoMuDirY = 0.;
float RecoMuDirZ = 0.;


class TreeManager {
  public:
  	TreeManager(){
  		tree = new TTree("tree", "");
  	};
  	virtual ~TreeManager(){};

    void SetBranch();
  	void FillTree();
    void WriteTree(TString OutName);
};
