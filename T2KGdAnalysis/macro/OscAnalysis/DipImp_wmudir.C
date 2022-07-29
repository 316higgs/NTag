#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void DipImp() {
  TFile* fin[6];

  for (int i=0; i<6; i++) {
   fin[i] = new TFile(TString::Format("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut%d.root", i+1));
  }
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");

  TH1F* h1_AllProbRatio[6];
  TH1F* h1_CCQEProbRatio[6];
  TH1F* h1_AllProbRatio_woTruthN[6];
  TH1F* h1_AllProbRatio_woTagN[6];

  for (int i=0; i<6; i++) {
    h1_AllProbRatio[i]  = (TH1F*)fin[i]->Get("NeutrinoOscillation/h1_All_OscProbRatio");
    h1_CCQEProbRatio[i] = (TH1F*)fin[i]->Get("NeutrinoOscillation/h1_OscProbRatio_mode0");
    h1_AllProbRatio_woTruthN[i] = (TH1F*)fin[i]->Get("NeutrinoOscillation/h1_All_OscProbRatio_woTruthNeutron");
    h1_AllProbRatio_woTagN[i]   = (TH1F*)fin[i]->Get("NeutrinoOscillation/h1_All_OscProbRatio_woNeutron");
  } 
  
  for (int i=0; i<6; i++) {
    h1_AllProbRatio[i] -> SetLineWidth(2);
    h1_AllProbRatio[i] -> SetStats(0);
    h1_AllProbRatio[i] -> SetLineColor(kTeal+2);

    h1_CCQEProbRatio[i] -> SetFillStyle(0);
    h1_CCQEProbRatio[i] -> SetStats(0);

    h1_AllProbRatio_woTruthN[i] -> SetLineWidth(2);
    h1_AllProbRatio_woTruthN[i] -> SetLineColor(kPink+1);
    h1_AllProbRatio_woTruthN[i] -> SetStats(0);

    h1_AllProbRatio_woTagN[i] -> SetLineWidth(2);
    h1_AllProbRatio_woTagN[i] -> SetLineColor(kOrange+1);
    h1_AllProbRatio_woTagN[i] -> SetStats(0);
  }

  h1_AllProbRatio_woTruthN[0] -> SetLineColor(kRed-4);
  h1_AllProbRatio_woTruthN[1] -> SetLineColor(kOrange-7);
  h1_AllProbRatio_woTruthN[2] -> SetLineColor(kOrange+0);
  h1_AllProbRatio_woTruthN[3] -> SetLineColor(kSpring-6);
  h1_AllProbRatio_woTruthN[4] -> SetLineColor(kAzure-5);
  h1_AllProbRatio_woTruthN[5] -> SetLineColor(kViolet-3);

  h1_AllProbRatio_woTagN[0] -> SetLineColor(kRed-4);
  h1_AllProbRatio_woTagN[1] -> SetLineColor(kOrange-7);
  h1_AllProbRatio_woTagN[2] -> SetLineColor(kOrange+0);
  h1_AllProbRatio_woTagN[3] -> SetLineColor(kSpring-6);
  h1_AllProbRatio_woTagN[4] -> SetLineColor(kAzure-5);
  h1_AllProbRatio_woTagN[5] -> SetLineColor(kViolet-3);
  


  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_AllProbRatio_woTagN[0] -> GetYaxis() -> SetRangeUser(0, 0.3);
  h1_AllProbRatio_woTagN[0] -> GetXaxis() -> SetRangeUser(0, 1.);
  h1_AllProbRatio_woTagN[0] -> SetTitleOffset(1.4, "Y");
  h1_AllProbRatio_woTagN[0] -> SetTitleSize(0.035, "Y");
  h1_AllProbRatio_woTagN[0] -> Draw("SAME hist");
  h1_AllProbRatio_woTagN[1] -> Draw("SAME hist");
  h1_AllProbRatio_woTagN[2] -> Draw("SAME hist");
  h1_AllProbRatio_woTagN[3] -> Draw("SAME hist");
  h1_AllProbRatio_woTagN[4] -> Draw("SAME hist");
  h1_AllProbRatio_woTagN[5] -> Draw("SAME hist");

  TLegend* legend1 = new TLegend(0.13, 0.51, 0.55, 0.89);
  legend1 -> SetTextSize(0.03);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.4]{w/o Tagged Neutrons}", "");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.4]{(n-like threshold: 0.75)}", "");
  //legend->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend1 -> AddEntry(h1_AllProbRatio_woTagN[0], "-1#leq cos#theta_{#mu}#leq 1", "L");
  legend1 -> AddEntry(h1_AllProbRatio_woTagN[1], "0#leq cos#theta_{#mu}#leq 1", "L");
  legend1 -> AddEntry(h1_AllProbRatio_woTagN[2], "0.2#leq cos#theta_{#mu}#leq 1", "L");
  legend1 -> AddEntry(h1_AllProbRatio_woTagN[3], "0.4#leq cos#theta_{#mu}#leq 1", "L");
  legend1 -> AddEntry(h1_AllProbRatio_woTagN[4], "0.6#leq cos#theta_{#mu}#leq 1", "L");
  legend1 -> AddEntry(h1_AllProbRatio_woTagN[5], "0.8#leq cos#theta_{#mu}#leq 1", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();


  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_AllProbRatio_woTruthN[0] -> GetYaxis() -> SetRangeUser(0, 0.3);
  h1_AllProbRatio_woTruthN[0] -> GetXaxis() -> SetRangeUser(0, 1.);
  h1_AllProbRatio_woTruthN[0] -> SetTitleOffset(1.4, "Y");
  h1_AllProbRatio_woTruthN[0] -> SetTitleSize(0.035, "Y");
  h1_AllProbRatio_woTruthN[0] -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN[1] -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN[2] -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN[3] -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN[4] -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN[5] -> Draw("SAME hist");

  TLegend* legend2 = new TLegend(0.13, 0.51, 0.55, 0.89);
  legend2 -> SetTextSize(0.03);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend2 -> AddEntry((TObject*)0,"#kern[-0.4]{w/o Truth Neutrons}", "");
  //legend->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend2 -> AddEntry(h1_AllProbRatio_woTruthN[0], "-1#leq cos#theta_{#mu}#leq 1", "L");
  legend2 -> AddEntry(h1_AllProbRatio_woTruthN[1], "0#leq cos#theta_{#mu}#leq 1", "L");
  legend2 -> AddEntry(h1_AllProbRatio_woTruthN[2], "0.2#leq cos#theta_{#mu}#leq 1", "L");
  legend2 -> AddEntry(h1_AllProbRatio_woTruthN[3], "0.4#leq cos#theta_{#mu}#leq 1", "L");
  legend2 -> AddEntry(h1_AllProbRatio_woTruthN[4], "0.6#leq cos#theta_{#mu}#leq 1", "L");
  legend2 -> AddEntry(h1_AllProbRatio_woTruthN[5], "0.8#leq cos#theta_{#mu}#leq 1", "L");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
}