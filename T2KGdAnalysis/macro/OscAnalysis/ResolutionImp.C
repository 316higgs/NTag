#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void ResolutionImp() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");

  //TH1F* h1_AllEnureco    = (TH1F*)fin->Get("NeutrinoOscillation/h1_AllEnureco");
  TH1F* h1_AllProbRatio  = (TH1F*)fin->Get("NeutrinoOscillation/h1_All_OscProbRatio");
  TH1F* h1_CCQEProbRatio = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProbRatio_mode0");
  TH1F* h1_AllProbRatio_woTruthN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_All_OscProbRatio_woTruthNeutron");
  TH1F* h1_AllProbRatio_woTagN    = (TH1F*)fin->Get("NeutrinoOscillation/h1_All_OscProbRatio_woNeutron");

  //h1_AllEnureco   -> SetLineWidth(2);
  h1_AllProbRatio -> SetLineWidth(2);
  h1_AllProbRatio_woTruthN -> SetLineWidth(2);
  h1_AllProbRatio_woTagN   -> SetLineWidth(2);

  //h1_AllEnureco   -> SetStats(0);
  h1_AllProbRatio -> SetStats(0);

  //h1_AllEnureco   -> SetLineColor(kPink-3);
  //h1_AllEnureco   -> SetFillColor(kPink-3);
  //h1_AllEnureco   -> SetFillStyle(3003);
  h1_AllProbRatio -> SetLineColor(kTeal+2);

  h1_CCQEProbRatio -> SetFillStyle(0);
  h1_CCQEProbRatio -> SetStats(0);

  h1_AllProbRatio_woTruthN -> SetLineColor(kPink+1);
  h1_AllProbRatio_woTagN   -> SetLineColor(kOrange+1);
  h1_AllProbRatio_woTagN   -> SetStats(0);

  //Double_t tot_AllEnureco = h1_AllEnureco -> Integral();
  //std::cout << tot_AllEnureco << std::endl;
  //h1_AllEnureco -> Scale(1./tot_AllEnureco);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  //h1_AllProbRatio_woTagN   -> SetTitle("Oscillation Probability(#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}) w/o tagged neutrons");
  h1_AllProbRatio_woTagN -> GetYaxis() -> SetRangeUser(0, 0.5);
  h1_AllProbRatio_woTagN -> SetTitleOffset(1.4, "Y");
  h1_AllProbRatio_woTagN -> SetTitleSize(0.035, "Y");
  //h1_AllProbRatio_woTagN -> SetLabelSize(0.033, "Y");
  h1_AllProbRatio_woTagN -> Draw("SAME hist");
  h1_AllProbRatio -> Draw("SAME hist");
  h1_CCQEProbRatio -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN -> Draw("SAME hist");

  TLegend* legend = new TLegend(0.45, 0.2, 0.85, 0.5);
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
  legend->Draw();

  int minbin = h1_AllProbRatio->FindBin(0.5);
  std::cout << "Enu = 0.5 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin) << std::endl;
  std::cout << "Enu = 0.55 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin+1) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin+1) << std::endl;
  std::cout << "Enu = 0.6 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin+2) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin+2) << " -> NTag: "
                                           << h1_AllProbRatio_woTagN->GetBinContent(minbin+2) << std::endl;
  std::cout << "Enu = 0.65 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin+3) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin+3) << std::endl;
}