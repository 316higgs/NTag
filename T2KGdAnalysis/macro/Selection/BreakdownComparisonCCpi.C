#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void BreakdownComparisonCCpi() {
  //fhc
  TFile* finnumu        = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* finnumubar     = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");
  TFile* finnumubarccpi = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.CCpi.root");

  TH1F* h1_numu        = (TH1F*)finnumu->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_numubar     = (TH1F*)finnumubar->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_numubarccpi = (TH1F*)finnumubarccpi->Get("Gd1RmuonSelection/h1_1RmuonEvents");

  h1_numu        -> SetStats(0);
  h1_numubar     -> SetStats(0);
  h1_numubarccpi -> SetStats(0);

  h1_numu        -> SetLineWidth(3);
  h1_numubar     -> SetLineWidth(3);
  h1_numubarccpi -> SetLineWidth(3);

  //h1_numu        -> SetLineStyle(2);
  //h1_numubar     -> SetLineStyle(2);
  //h1_numubarccpi -> SetLineStyle(2);

  h1_numu    -> SetLineColor(kAzure+5);
  h1_numubar -> SetLineColor(kViolet-5);
  h1_numubarccpi -> SetLineColor(kOrange+9);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",1000,700);
  c1 -> SetGrid();
  h1_numu -> GetYaxis() -> SetRangeUser(0., 1.1);
  h1_numu        -> Draw();
  h1_numubar     -> Draw("SAME");
  h1_numubarccpi -> Draw("SAME");
  //c1->RedrawAxis();

  TLegend* legend = new TLegend(0.4, 0.65, 0.88, 0.85);
  legend -> SetTextSize(0.03);
  legend -> AddEntry(h1_numu, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC (All Interactions)", "L");
  legend -> AddEntry(h1_numubar, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC (All Interactions)", "L");
  legend -> AddEntry(h1_numubarccpi, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC (CC Pion Prductions)", "L");
  legend->SetFillColor(0);
  legend->Draw() ;

}