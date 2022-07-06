#include "TreeManager.h"
#include "TGaxis.h"

void TreeManager::SetBranch() {
  tree -> Branch("OneRingRejectCCQE", &OneRingRejectCCQE, "OneRingRejectCCQE/F");
}

void TreeManager::FillTree() {
  tree -> Fill();
}

void TreeManager::WriteTree(TString OutName) {
  TFile* fout = new TFile(OutName, "RECREATE");
  fout -> cd();
  tree -> Write();
}