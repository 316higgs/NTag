#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Breakdown() {
  //fhc
  TFile* finPW = new TFile("../../output/fhc/fhc.numu_x_numu.water.root");
  TFile* finGd = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.root");

  //TFile* finPW = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");
  //TFile* finGd = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");

  //rhc
  //TFile* finPW = new TFile("../../output/numubar.water.root");
  //TFile* finGd = new TFile("../../output/numubar.etagON.root");


  TH1F* h1_1R_Gd      = (TH1F*)finGd->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_Proto1R_Gd = (TH1F*)finGd->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");

  TH1F* h1_Proto1R_PW = (TH1F*)finPW->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");

  h1_1R_Gd      -> SetStats(0);
  h1_Proto1R_Gd -> SetStats(0);
  h1_Proto1R_PW -> SetStats(0);

  h1_Proto1R_Gd -> SetLineStyle(2);
  h1_Proto1R_PW -> SetLineStyle(2);

  h1_Proto1R_PW -> SetLineColor(kAzure-3);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",1000,700);
  c1 -> SetGrid();
  h1_1R_Gd -> GetYaxis() -> SetRangeUser(0., 1.1);
  h1_1R_Gd      -> Draw();
  h1_Proto1R_Gd -> Draw("SAME");  
  h1_Proto1R_PW -> Draw("SAME");
  //c1->RedrawAxis();

  TLegend* legend = new TLegend(0.4, 0.65, 0.85, 0.85);
  legend -> SetTextSize(0.03);
  //legend->AddEntry((TObject*)0,"#kern[-0.6]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC}","");
  legend->AddEntry((TObject*)0,"#kern[-0.6]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  //legend->AddEntry((TObject*)0,"#kern[-0.6]{ RHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend -> AddEntry(h1_1R_Gd, "Gd MC: Decay-e cut with dt vs N50", "L");
  legend -> AddEntry(h1_Proto1R_Gd, "Gd MC: Decay-e #leq 1", "L");
  legend -> AddEntry(h1_Proto1R_PW, "Pure water MC: Decay-e #leq 1", "L");
  legend->SetFillColor(0);
  legend->Draw() ;

}