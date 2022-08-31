#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void NTrueN() {
  TFile* finnumu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* finnumubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");

  TH1F* h1_NTrueN_numu    = (TH1F*)finnumu->Get("NTagAnalysis/h1_NTrueN_type0");
  TH1F* h1_NTrueN_numubar = (TH1F*)finnumubar->Get("NTagAnalysis/h1_NTrueN_type0");

  h1_NTrueN_numu    -> SetStats(0);
  h1_NTrueN_numubar -> SetStats(0);

  h1_NTrueN_numu    -> SetLineColor(kAzure-5);
  h1_NTrueN_numu    -> SetFillColor(kAzure-5);
  h1_NTrueN_numu    -> SetFillColorAlpha(kAzure-5, 0.5);
  h1_NTrueN_numubar -> SetLineColor(kPink-5);
  h1_NTrueN_numubar -> SetFillColor(kPink-5);
  h1_NTrueN_numubar -> SetFillColorAlpha(kPink-5, 0.5);

  //Double_t tot_numu = h1_NTrueN_numu->Integral();
  //h1_NTrueN_numu -> Scale(1./tot_numu);
  //Double_t tot_numubar = h1_NTrueN_numubar->Integral();
  //h1_NTrueN_numubar -> Scale(1./tot_numubar);


  TH1F* h1_NTrueNH_numu    = (TH1F*)finnumu->Get("NTagAnalysis/h1_NTrueN_type1");
  TH1F* h1_NTrueNH_numubar = (TH1F*)finnumubar->Get("NTagAnalysis/h1_NTrueN_type1");

  h1_NTrueNH_numu    -> SetStats(0);
  h1_NTrueNH_numubar -> SetStats(0);

  h1_NTrueNH_numu    -> SetLineColor(kAzure-5);
  h1_NTrueNH_numu    -> SetFillColor(kAzure-5);
  h1_NTrueNH_numu    -> SetFillColorAlpha(kAzure-5, 0.5);
  h1_NTrueNH_numubar -> SetLineColor(kPink-5);
  h1_NTrueNH_numubar -> SetFillColor(kPink-5);
  h1_NTrueNH_numubar -> SetFillColorAlpha(kPink-5, 0.5);

  //Double_t tot_numuH = h1_NTrueNH_numu->Integral();
  //h1_NTrueNH_numu -> Scale(1./tot_numuH);
  //Double_t tot_numubarH = h1_NTrueNH_numubar->Integral();
  //h1_NTrueNH_numubar -> Scale(1./tot_numubarH);


  TH1F* h1_NTrueNGd_numu    = (TH1F*)finnumu->Get("NTagAnalysis/h1_NTrueN_type2");
  TH1F* h1_NTrueNGd_numubar = (TH1F*)finnumubar->Get("NTagAnalysis/h1_NTrueN_type2");

  h1_NTrueNGd_numu    -> SetStats(0);
  h1_NTrueNGd_numubar -> SetStats(0);

  h1_NTrueNGd_numu    -> SetLineColor(kAzure-5);
  h1_NTrueNGd_numu    -> SetFillColor(kAzure-5);
  h1_NTrueNGd_numu    -> SetFillColorAlpha(kAzure-5, 0.5);
  h1_NTrueNGd_numubar -> SetLineColor(kPink-5);
  h1_NTrueNGd_numubar -> SetFillColor(kPink-5);
  h1_NTrueNGd_numubar -> SetFillColorAlpha(kPink-5, 0.5);

  //Double_t tot_numuGd = h1_NTrueNGd_numu->Integral();
  //h1_NTrueNGd_numu -> Scale(1./tot_numuGd);
  //Double_t tot_numubarGd = h1_NTrueNGd_numubar->Integral();
  //h1_NTrueNGd_numubar -> Scale(1./tot_numubarGd);


  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","All",700,700);
  c1 -> SetGrid();
  ((TGaxis*)h1_NTrueN_numu->GetXaxis())->SetMaxDigits(3);
  h1_NTrueN_numu -> SetYTitle("Number of Neutrons");
  h1_NTrueN_numu    -> Draw();
  h1_NTrueN_numubar -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.5, 0.55, 0.87, 0.75);
  legend1 -> SetTextSize(0.03);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{ All Neutron Captures }","");
  legend1 -> AddEntry(h1_NTrueN_numu, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC", "F");
  legend1 -> AddEntry(h1_NTrueN_numubar, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw() ;


  TCanvas* c2 = new TCanvas("c2","H-n",700,700);
  c2 -> SetGrid();
  ((TGaxis*)h1_NTrueNH_numu->GetXaxis())->SetMaxDigits(3);
  h1_NTrueNH_numu -> SetYTitle("Number of Neutrons");
  h1_NTrueNH_numu    -> Draw();
  h1_NTrueNH_numubar -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.5, 0.55, 0.87, 0.75);
  legend2 -> SetTextSize(0.03);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.3]{ H-n Signal }","");
  legend2 -> AddEntry(h1_NTrueN_numu, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC", "F");
  legend2 -> AddEntry(h1_NTrueN_numubar, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC", "F");
  legend2 -> SetFillColor(0);
  legend2 -> Draw() ;


  TCanvas* c3 = new TCanvas("c3","Gd-n",700,700);
  c3 -> SetGrid();
  ((TGaxis*)h1_NTrueNGd_numu->GetXaxis())->SetMaxDigits(3);
  h1_NTrueNGd_numu -> SetYTitle("Number of Neutrons");
  h1_NTrueNGd_numu    -> Draw();
  h1_NTrueNGd_numubar -> Draw("SAME");

  TLegend* legend3 = new TLegend(0.5, 0.55, 0.87, 0.75);
  legend3 -> SetTextSize(0.03);
  legend3 -> AddEntry((TObject*)0,"#kern[-0.3]{ Gd-n Signal }","");
  legend3 -> AddEntry(h1_NTrueN_numu, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC", "F");
  legend3 -> AddEntry(h1_NTrueN_numubar, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC", "F");
  legend3 -> SetFillColor(0);
  legend3 -> Draw() ;

}