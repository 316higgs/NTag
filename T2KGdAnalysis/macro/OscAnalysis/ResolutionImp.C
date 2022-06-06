#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void ResolutionImp() {
  //TFile* fin = new TFile("../../output/numu.etagON.root");
  TFile* fin = new TFile("../../output/numubar.etagON.root");

  TH1F* h1_AllEnureco    = (TH1F*)fin->Get("NeutrinoOscillation/h1_AllEnureco");
  TH1F* h1_AllProbRatio  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Allnumu_x_numu_OscProbRatio");
  TH1F* h1_CCQEProbRatio = (TH1F*)fin->Get("NeutrinoOscillation/h1_numu_x_numu_OscProbRatio_mode0");
  TH1F* h1_AllProbRatio_woTruthN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Allnumu_x_numu_OscProbRatio_woTruthNeutron");
  TH1F* h1_AllProbRatio_woTagN    = (TH1F*)fin->Get("NeutrinoOscillation/h1_Allnumu_x_numu_OscProbRatio_woNeutron");

  h1_AllEnureco   -> SetLineWidth(2);
  h1_AllProbRatio -> SetLineWidth(2);
  h1_AllProbRatio_woTruthN -> SetLineWidth(2);
  h1_AllProbRatio_woTagN   -> SetLineWidth(2);

  h1_AllEnureco   -> SetStats(0);
  h1_AllProbRatio -> SetStats(0);

  h1_AllEnureco   -> SetLineColor(kPink-3);
  h1_AllEnureco   -> SetFillColor(kPink-3);
  h1_AllEnureco   -> SetFillStyle(3003);
  h1_AllProbRatio -> SetLineColor(kTeal+2);

  h1_CCQEProbRatio -> SetFillStyle(0);
  h1_CCQEProbRatio -> SetStats(0);

  h1_AllProbRatio_woTruthN -> SetLineColor(kPink+1);
  h1_AllProbRatio_woTagN   -> SetLineColor(kOrange+1);
  h1_AllProbRatio_woTagN   -> SetStats(0);

  Double_t tot_AllEnureco = h1_AllEnureco -> Integral();
  //std::cout << tot_AllEnureco << std::endl;
  h1_AllEnureco -> Scale(1./tot_AllEnureco);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  h1_AllProbRatio_woTagN   -> SetTitle("Oscillation Probability(#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}) w/o tagged neutrons");
  h1_AllProbRatio_woTagN   -> Draw("SAME hist");
  h1_AllProbRatio -> Draw("SAME hist");
  h1_CCQEProbRatio -> Draw("SAME hist");
  h1_AllProbRatio_woTruthN -> Draw("SAME hist");
  
  /*TCanvas* c2 = new TCanvas("c2","c2",800,800);
  h1_AllProbRatio -> SetTitleOffset(1.4, "Y");
  h1_AllProbRatio -> SetTitleSize(0.035, "Y");
  h1_AllProbRatio -> SetLabelSize(0.033, "Y");
  //h1_AllProbRatio -> GetYaxis() -> SetRangeUser(0.02, 0.1);
  //h1_AllProbRatio -> GetXaxis() -> SetRangeUser(0.5, 0.7);
  h1_AllProbRatio -> Draw();
  h1_CCQEProbRatio -> Draw("SAME");*/

  int minbin = h1_AllProbRatio->FindBin(0.5);
  std::cout << "Enu = 0.5 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin) << std::endl;
  std::cout << "Enu = 0.55 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin+1) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin+1) << std::endl;
  std::cout << "Enu = 0.6 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin+2) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin+2) << std::endl;
  std::cout << "Enu = 0.65 GeV   No NTag: " << h1_AllProbRatio->GetBinContent(minbin+3) << " -> Ideal: " 
                                           << h1_CCQEProbRatio->GetBinContent(minbin+3) << std::endl;
}