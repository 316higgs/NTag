#pragma once

#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TTree.h"
#include "TFile.h"


TTree* tree;
float OneRingRejectCCQE = 0.;

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
