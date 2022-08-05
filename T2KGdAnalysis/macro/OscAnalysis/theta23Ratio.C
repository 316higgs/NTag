#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

void theta23Ratio() {
  TFile* fin    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* finmax = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.maximalmix.root");

  TH1F* h1_CCQE = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CCQE_maximalmix = (TH1F*)finmax->Get("NeutrinoOscillation/h1_OscProb_mode0");
  h1_CCQE_maximalmix -> SetFillStyle(0);
  h1_CCQE_maximalmix -> SetStats(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_CCQE_maximalmix -> GetXaxis() -> SetRangeUser(0, 1.5);
  h1_CCQE_maximalmix -> GetYaxis() -> SetRangeUser(0.9, 1.1);
  h1_CCQE_maximalmix -> SetTitleOffset(1.4, "Y");
  h1_CCQE_maximalmix -> SetYTitle("CCQE(cos#theta_{23}=0.511) / CCQE(cos#theta_{23}=0.532)");
  h1_CCQE_maximalmix -> Divide(h1_CCQE);
  h1_CCQE_maximalmix -> Draw();
  c1->RedrawAxis();
  
}