#include "TreeManager.h"
#include "TGaxis.h"

void TreeManager::SetBranch() {
  //tree -> Branch("OneRingRejectCCQE", &OneRingRejectCCQE, "OneRingRejectCCQE/F");

  tree -> Branch("TrueMuDirX", &TrueMuDirX, "TrueMuDirX/F");
  tree -> Branch("TrueMuDirY", &TrueMuDirY, "TrueMuDirY/F");
  tree -> Branch("TrueMuDirZ", &TrueMuDirZ, "TrueMuDirZ/F");
  tree -> Branch("RecoMuDirX", &RecoMuDirX, "RecoMuDirX/F");
  tree -> Branch("RecoMuDirY", &RecoMuDirY, "RecoMuDirY/F");
  tree -> Branch("RecoMuDirZ", &RecoMuDirZ, "RecoMuDirZ/F");
}

void TreeManager::FillTree() {
  tree -> Fill();
}

void TreeManager::WriteTree(TString OutName) {
  TFile* fout = new TFile(OutName, "RECREATE");
  fout -> cd();
  tree -> Write();
}