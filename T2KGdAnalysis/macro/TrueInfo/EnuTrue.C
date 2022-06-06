#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void EnuTrue() {
  TFile* fin = new TFile("../../output/etagONtest.root");

  TH1F* h1_ccqe         = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode0");
  TH1F* h1_ccnonqe      = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode1");
  TH1F* h1_nc           = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode2");
  TH1F* h1_ccresdeltap  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode3");
  TH1F* h1_ccresdeltapp = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode4");
  TH1F* h1_ccresdelta0  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode5");

  h1_ccqe         -> SetStats(0);
  h1_ccnonqe      -> SetStats(0);
  h1_ccresdeltap  -> SetStats(0);
  h1_ccresdeltapp -> SetStats(0);
  h1_ccresdelta0  -> SetStats(0);
  h1_nc           -> SetStats(0);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  ((TGaxis*)h1_ccqe->GetXaxis())->SetMaxDigits(3);
  //h1_ccqe -> SetTitleOffset(1.4, "Y");
  //h1_ccqe -> SetTitleSize(0.035, "Y");
  //h1_ccqe -> SetLabelSize(0.033, "Y");
  h1_ccqe         -> Draw();
  h1_ccnonqe      -> Draw("SAME");  
  h1_ccresdeltapp -> Draw("SAME");
  h1_ccresdelta0  -> Draw("SAME");
  h1_ccresdeltap  -> Draw("SAME");
  h1_nc           -> Draw("SAME");

}