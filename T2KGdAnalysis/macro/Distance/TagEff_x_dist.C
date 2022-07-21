#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void TagEff_x_dist() {
  TFile* fin_o = new TFile("../../../NTagEff/output/thresholdscan.original.root");
  TFile* fin_n = new TFile("../../../NTagEff/output/thresholdscan.train.root");
  //TFile* fin   = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");
  TFile* fin   = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.root");

  TH1D* h1_eff_x_dist_o    = (TH1D*)fin_o->Get("h1_tagging_eff_scan7");
  TH1D* h1_preeff_x_dist_o = (TH1D*)fin_o->Get("h1_pre_eff_scan7");
  TH1D* h1_NNeff_x_dist_o  = (TH1D*)fin_o->Get("h1_NN_eff_scan7");
  TH1D* h1_truedistance_o  = (TH1D*)fin_o->Get("h1_truedistance");

  TH1D* h1_eff_x_dist_n    = (TH1D*)fin_n->Get("h1_tagging_eff_scan8");
  TH1D* h1_preeff_x_dist_n = (TH1D*)fin_n->Get("h1_pre_eff_scan8");
  TH1D* h1_NNeff_x_dist_n  = (TH1D*)fin_n->Get("h1_NN_eff_scan8");
  TH1D* h1_truedistance_n  = (TH1D*)fin_n->Get("h1_truedistance");

  TH1D* h1_eff_x_dist    = (TH1D*)fin->Get("DistanceViewer/h1_OverallEff_dist_thr17");
  TH1D* h1_preeff_x_dist = (TH1D*)fin->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNeff_x_dist  = (TH1D*)fin->Get("DistanceViewer/h1_NNEff_dist_thr17");
  TH1D* h1_truedistance  = (TH1D*)fin->Get("DistanceViewer/h1_truedistance");

  h1_eff_x_dist_o    -> SetLineColor(kAzure+1);
  h1_preeff_x_dist_o -> SetLineColor(kAzure+1);
  h1_NNeff_x_dist_o  -> SetLineColor(kAzure+1);
  h1_truedistance_o  -> SetLineColor(kAzure+1);
  h1_truedistance_o  -> SetFillColor(0);
  h1_eff_x_dist_n    -> SetLineColor(kSpring-5);
  h1_preeff_x_dist_n -> SetLineColor(kSpring-5);
  h1_NNeff_x_dist_n  -> SetLineColor(kSpring-5);
  h1_truedistance_n  -> SetLineColor(kSpring-5);
  h1_truedistance_n  -> SetFillColor(0);
  h1_truedistance_n  -> SetLineWidth(2);
  h1_eff_x_dist      -> SetLineColor(kPink-9);
  h1_preeff_x_dist   -> SetLineColor(kPink-9);
  h1_NNeff_x_dist    -> SetLineColor(kPink-9);
  h1_eff_x_dist      -> SetLineWidth(3);
  h1_preeff_x_dist   -> SetLineWidth(3);
  h1_NNeff_x_dist    -> SetLineWidth(3);


  gROOT -> SetStyle("Plain");

  TCanvas* ceff = new TCanvas("ceff","ceff",800,800);
  ceff -> SetGrid();
  ceff -> cd();
  h1_eff_x_dist_o -> Draw();
  h1_eff_x_dist_n -> Draw("SAME");
  h1_eff_x_dist   -> Draw("SAME");
  //ceff -> SaveAs("../figure/TagEff_x_dist.pdf");

  TCanvas* cpreeff = new TCanvas("cpreeff","cpreeff",800,800);
  cpreeff -> SetGrid();
  cpreeff -> cd();
  h1_preeff_x_dist_o -> GetYaxis() -> SetRangeUser(0.4, 0.8);
  h1_preeff_x_dist_o -> Draw();
  h1_preeff_x_dist_n -> Draw("SAME");
  h1_preeff_x_dist   -> Draw("SAME");
  //cpreeff -> SaveAs("../figure/PreEff_x_dist.pdf");

  TCanvas* cnneff = new TCanvas("cnneff","cnneff",800,800);
  cnneff -> SetGrid();
  cnneff -> cd();
  h1_NNeff_x_dist_o -> GetYaxis() -> SetRangeUser(0., 0.8);
  h1_NNeff_x_dist_o -> Draw();
  h1_NNeff_x_dist_n -> Draw("SAME");
  h1_NNeff_x_dist   -> Draw("SAME");
  //cnneff -> SaveAs("../figure/NNEff_x_dist.pdf");

  /*TCanvas* cdist = new TCanvas("cdist", "cdist", 800, 800);
  cdist -> cd();
  //h1_truedistance_o -> Draw();
  //h1_truedistance_n -> Draw("SAME");
  h1_truedistance   -> Draw("SAME");
  cdist -> SaveAs("../figure/truedistance.pdf");*/

}