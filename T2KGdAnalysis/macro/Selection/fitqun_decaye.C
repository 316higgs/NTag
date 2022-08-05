#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void fitqun_decaye() {
  TFile* finnumu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* finnumubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");

  TH1D* h1_all_decaye_numu = (TH1D*)finnumu->Get("DecayeBox/h1_TaggedDecaye");
  h1_all_decaye_numu -> SetLineColor(kAzure+1);
  h1_all_decaye_numu -> SetYTitle("Area Normalized");
  h1_all_decaye_numu -> SetLineWidth(3);
  h1_all_decaye_numu -> SetStats(0);

  TH1D* h1_all_decay_numubar = (TH1D*)finnumubar->Get("DecayeBox/h1_TaggedDecaye");
  h1_all_decay_numubar -> SetLineColor(kViolet-1);
  h1_all_decay_numubar -> SetLineWidth(3);
  h1_all_decay_numubar -> SetStats(0);

  TH1D* h1_CCpi_decay_numubar = (TH1D*)finnumubar->Get("DecayeBox/h1_TaggedDecaye_CCpi");
  h1_CCpi_decay_numubar -> SetLineColor(kOrange+9);
  h1_CCpi_decay_numubar -> SetLineWidth(3);
  h1_CCpi_decay_numubar -> SetStats(0);


  gROOT -> SetStyle("Plain");
  TLegend* legend = new TLegend(0.38, 0.6, 0.89, 0.8);
  legend -> SetTextSize(0.03);
  legend -> AddEntry(h1_all_decaye_numu, "FHC #nu_{#mu}#rightarrow#nu_{#mu} MC(All Interactions)", "L");
  legend -> AddEntry(h1_all_decay_numubar, "FHC #bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu} MC(All Interactions)", "L");
  legend -> AddEntry(h1_CCpi_decay_numubar, "FHC #bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu} MC(CC Pion Productions)", "L");
  legend ->AddEntry((TObject*)0,"#kern[-0.8]{ C1-C4 applied }","");
  /*legend -> SetLineColor(0);
  legend -> SetFillColor(0);
  legend -> SetFillStyle(0);
  legend -> SetLineStyle(0);*/
  legend -> SetShadowColor(0);

  TString notice;
  notice = "CCQE";
  TString notice1;
  notice1 = "C1-C4 applied";
  //TText* text0 = new TText(3.1,0.48,notice);
  TText* text0 = new TText(3.1,0.43,notice);
  text0 -> SetTextSize(0.045);
  //TText* text1 = new TText(3.1,0.43,notice1);
  TText* text1 = new TText(3.1,0.38,notice1);
  text1 -> SetTextSize(0.045);

  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> SetGrid();
  h1_all_decaye_numu -> Draw();
  h1_all_decay_numubar -> Draw("SAME");
  h1_CCpi_decay_numubar -> Draw("SAME");
  legend -> Draw();
  //text0 -> Draw();
  //text1 -> Draw();

}