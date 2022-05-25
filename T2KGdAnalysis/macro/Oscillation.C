#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Oscillation() {
  TFile* fin = new TFile("../output/etagONtest.root");

  TH1F* h1_AllEnureco   = (TH1F*)fin->Get("NeutrinoOscillation/h1_AllEnureco");
  TH1F* h1_AllProb      = (TH1F*)fin->Get("NeutrinoOscillation/h1_Allnumu_x_numu_OscProb");
  TH1F* h1_AllProbRatio = (TH1F*)fin->Get("NeutrinoOscillation/h1_Allnumu_x_numu_OscProbRatio");

  TH1F* h1_CCQEProbRatio          = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_mode0");
  TH1F* h1_CCQEProbRatiowNeutron  = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_wNeutron_mode0");
  TH1F* h1_CCQEProbRatiowoNeutron = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_woNeutron_mode0");

  TH1F* h1_CCnonQEProbRatio          = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_mode1");
  TH1F* h1_CCnonQEProbRatiowNeutron  = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_wNeutron_mode1");
  TH1F* h1_CCnonQEProbRatiowoNeutron = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_woNeutron_mode1");

  h1_AllEnureco   -> SetLineWidth(2);
  h1_AllProb      -> SetLineWidth(2);
  h1_AllProbRatio -> SetLineWidth(2);

  h1_AllEnureco   -> SetStats(0);
  h1_AllProb      -> SetStats(0);
  h1_AllProbRatio -> SetStats(0);

  h1_AllEnureco   -> SetLineColor(kPink-3);
  h1_AllEnureco   -> SetFillColor(kPink-3);
  h1_AllEnureco   -> SetFillStyle(3003);
  h1_AllProb      -> SetLineColor(kAzure+5);
  h1_AllProbRatio -> SetLineColor(kTeal+2);

  h1_CCQEProbRatio -> SetStats(0);
  h1_CCQEProbRatiowNeutron -> SetStats(0);
  h1_CCQEProbRatiowoNeutron -> SetStats(0);

  h1_CCQEProbRatiowNeutron -> SetLineStyle(7);
  h1_CCQEProbRatiowoNeutron -> SetLineStyle(3);

  h1_CCnonQEProbRatio -> SetStats(0);
  h1_CCnonQEProbRatiowNeutron -> SetStats(0);
  h1_CCnonQEProbRatiowoNeutron -> SetStats(0);

  h1_CCnonQEProbRatiowNeutron -> SetLineStyle(7);
  h1_CCnonQEProbRatiowoNeutron -> SetLineStyle(3);

  Double_t tot_AllEnureco = h1_AllEnureco->Integral();
  h1_AllEnureco -> Scale(1./tot_AllEnureco);

  Double_t tot_AllProb = h1_AllProb->Integral();
  h1_AllProb -> Scale(1./tot_AllProb);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,1200);
  c1 -> Divide(1,2);
  c1 -> cd(1);
  h1_AllEnureco -> Draw();
  h1_AllProb -> Draw("SAME");
  c1 -> cd(2);
  h1_AllProbRatio -> Draw("SAME");

  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> cd();
  h1_CCQEProbRatio -> Draw();
  h1_CCQEProbRatiowNeutron -> Draw("SAME");
  h1_CCQEProbRatiowoNeutron -> Draw("SAME");

  TCanvas* c3 = new TCanvas("c3", "c3", 900, 700);
  c3 -> cd();
  h1_CCnonQEProbRatio -> Draw();
  h1_CCnonQEProbRatiowNeutron -> Draw("SAME");
  h1_CCnonQEProbRatiowoNeutron -> Draw("SAME");

  /*TCanvas* c2 = new TCanvas("c2","w/ neutrons",900,700);
  c2 -> SetGrid();
  h1_ccqewneutron         -> Draw();
  h1_ccqewneutron -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqewneutron      -> Draw("SAME");
  //h1_ccnonqewneutron      -> Draw();
  //h1_ccnonqewneutron -> GetYaxis() -> SetRangeUser(0, 1000);
  ((TGaxis*)h1_ccnonqewneutron->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqewneutron -> SetTitleOffset(1.4, "Y");
  h1_ccnonqewneutron -> SetTitleSize(0.035, "Y");
  h1_ccnonqewneutron -> SetLabelSize(0.033, "Y");
  h1_ccresdeltappwneutron -> Draw("SAME");
  h1_ccresdelta0wneutron  -> Draw("SAME");
  h1_ccresdeltapwneutron  -> Draw("SAME");
  h1_ncwneutron           -> Draw("SAME");

  TCanvas* c3 = new TCanvas("c3","w/o neutrons",900,700);
  c3 -> SetGrid();
  h1_ccqewoneutron         -> Draw();
  h1_ccqewoneutron -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqewoneutron      -> Draw("SAME");
  //h1_ccnonqewoneutron      -> Draw();
  //h1_ccnonqewoneutron -> GetYaxis() -> SetRangeUser(0, 1000);
  ((TGaxis*)h1_ccnonqewoneutron->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqewoneutron -> SetTitleOffset(1.4, "Y");
  h1_ccnonqewoneutron -> SetTitleSize(0.035, "Y");
  h1_ccnonqewoneutron -> SetLabelSize(0.033, "Y");
  h1_ccresdeltappwoneutron -> Draw("SAME");
  h1_ccresdelta0woneutron  -> Draw("SAME");
  h1_ccresdeltapwoneutron  -> Draw("SAME");
  h1_ncwoneutron           -> Draw("SAME");*/

}