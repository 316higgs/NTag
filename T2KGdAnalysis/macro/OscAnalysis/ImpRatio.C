#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void ImpRatio() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");

  TH1F* h1_AllProbRatio  = (TH1F*)fin->Get("NeutrinoOscillation/h1_All_OscProbRatio");
  TH1F* h1_CCQEProbRatio = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProbRatio_mode0");
  TH1F* h1_AllProbRatio_woTruthN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_All_OscProbRatio_woTruthNeutron");
  TH1F* h1_AllProbRatio_woTagN    = (TH1F*)fin->Get("NeutrinoOscillation/h1_All_OscProbRatio_woNeutron");

  h1_AllProbRatio -> SetLineWidth(2);
  h1_AllProbRatio_woTruthN -> SetLineWidth(2);
  h1_AllProbRatio_woTagN   -> SetLineWidth(2);

  h1_AllProbRatio -> SetStats(0);

  h1_AllProbRatio -> SetLineColor(kTeal+2);

  h1_CCQEProbRatio -> SetFillStyle(0);
  h1_CCQEProbRatio -> SetStats(0);

  h1_AllProbRatio_woTruthN -> SetLineColor(kPink+1);
  h1_AllProbRatio_woTagN   -> SetLineColor(kAzure+1);
  h1_AllProbRatio_woTagN   -> SetStats(0);

  h1_AllProbRatio_woTagN -> Sumw2();
  h1_AllProbRatio_woTagN -> Divide(h1_AllProbRatio);
  

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_AllProbRatio_woTagN -> GetYaxis() -> SetRangeUser(0, 2.);
  h1_AllProbRatio_woTagN -> SetYTitle("Shallowness #alpha");
  h1_AllProbRatio_woTagN -> SetTitleOffset(1.4, "Y");
  h1_AllProbRatio_woTagN -> SetTitleSize(0.035, "Y");
  h1_AllProbRatio_woTagN -> Draw("SAME hist");

  /*TLegend* legend = new TLegend(0.45, 0.2, 0.85, 0.5);
  legend -> SetTextSize(0.03);
  legend->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend->AddEntry((TObject*)0,"#kern[-0.4]{n-like threshold: 0.8}", "");
  //legend->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  //legend->AddEntry((TObject*)0,"#kern[-0.4]{n-like threshold: 0.8}", "");
  legend -> AddEntry(h1_AllProbRatio, "Selected 1R muon events", "L");
  legend -> AddEntry(h1_CCQEProbRatio, "Only CCQE(1p1h)", "L");
  legend -> AddEntry(h1_AllProbRatio_woTruthN, "w/o Truth Neutrons", "L");
  legend -> AddEntry(h1_AllProbRatio_woTagN, "w/o Tagged Neutrons", "L");
  legend->SetFillColor(0);
  legend->Draw();*/
}