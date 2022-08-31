#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void NTagOut() {

  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.NNtest.root");

  TH1F* h1_NTagOut_AccNoise = (TH1F*)fin->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye   = (TH1F*)fin->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H        = (TH1F*)fin->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd       = (TH1F*)fin->Get("NNInputVariables/h1_NTagOut_type3");

  THStack* hs_NTagOut = new THStack("hs_NTagOut", "TagOut; n-likelihood; Number of Neutron Candidates");
  hs_NTagOut -> Add(h1_NTagOut_AccNoise);
  hs_NTagOut -> Add(h1_NTagOut_Decaye);
  hs_NTagOut -> Add(h1_NTagOut_Gd);
  hs_NTagOut -> Add(h1_NTagOut_H);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  c1 -> SetLogy();
  //hs_NTagOut -> SetMaximum(1090);
  hs_NTagOut -> Draw();
  hs_NTagOut ->GetYaxis()->SetTitleSize(0.038);
  hs_NTagOut ->GetYaxis()->SetTitleOffset(1.3);
  hs_NTagOut ->GetYaxis()->SetLabelSize(0.036);
  hs_NTagOut -> Draw();
  c1 -> RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend1 -> AddEntry(h1_NTagOut_Gd, "Gd-n signal", "F");
  legend1 -> AddEntry(h1_NTagOut_H, "H-n signal", "F");
  legend1 -> AddEntry(h1_NTagOut_Decaye, "Decay-e", "F");
  legend1 -> AddEntry(h1_NTagOut_AccNoise, "Acc. noise", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;

}