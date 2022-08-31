void NNcomparison() {

  TFile* finnumu = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.root");
  TFile* finnumubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.root");

  TH1F* h1_NNvar_Gd_numu[12];
  TH1F* h1_NNvar_H_numu[12];
  TH1F* h1_NNvar_AccNoise_numu[12];
  TH1F* h1_NNvar_Decaye_numu[12];

  TH1F* h1_NNvar_Gd_numubar[12];
  TH1F* h1_NNvar_H_numubar[12];
  TH1F* h1_NNvar_AccNoise_numubar[12];
  TH1F* h1_NNvar_Decaye_numubar[12];

  for (int i=0; i<12; i++) {
  	h1_NNvar_Gd_numu[i]       = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
  	h1_NNvar_H_numu[i]        = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
  	h1_NNvar_AccNoise_numu[i] = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_numu[i]   = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_numubar[i]       = (TH1F*)finnumubar->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_numubar[i]        = (TH1F*)finnumubar->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_numubar[i] = (TH1F*)finnumubar->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_numubar[i]   = (TH1F*)finnumubar->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

  	h1_NNvar_Gd_numu[i]       -> SetStats(0);
  	h1_NNvar_H_numu[i]        -> SetStats(0);
  	h1_NNvar_AccNoise_numu[i] -> SetStats(0);
    h1_NNvar_Decaye_numu[i]   -> SetStats(0);

    h1_NNvar_Gd_numubar[i]       -> SetStats(0);
    h1_NNvar_H_numubar[i]        -> SetStats(0);
    h1_NNvar_AccNoise_numubar[i] -> SetStats(0);
    h1_NNvar_Decaye_numubar[i]   -> SetStats(0);

    h1_NNvar_Gd_numu[i]       -> SetLineWidth(1);
    h1_NNvar_H_numu[i]        -> SetLineWidth(1);
    h1_NNvar_AccNoise_numu[i] -> SetLineWidth(1);
    h1_NNvar_Decaye_numu[i]   -> SetLineWidth(1);

    h1_NNvar_Gd_numubar[i]       -> SetLineWidth(1);
    h1_NNvar_H_numubar[i]        -> SetLineWidth(1);
    h1_NNvar_AccNoise_numubar[i] -> SetLineWidth(1);
    h1_NNvar_Decaye_numubar[i]   -> SetLineWidth(1);

    h1_NNvar_AccNoise_numu[i]    -> SetLineColor(kAzure-8);
    h1_NNvar_AccNoise_numubar[i] -> SetLineColor(kOrange-3);
  }

  TLegend* legend = new TLegend(0.46, 0.71, 0.87, 0.87);
  legend -> SetTextSize(0.06);
  legend -> AddEntry(h1_NNvar_AccNoise_numu[0], "#nu_{#mu}#rightarrow#nu_{#mu} MC", "L");
  legend -> AddEntry(h1_NNvar_AccNoise_numubar[0], "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu} MC", "L");
  legend -> SetFillColor(0);
  //legend->SetLineColor(0);
  //legend->SetFillColor(0);
  //legend->SetFillStyle(0);
  legend->SetBorderSize(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1000);
  //TCanvas* c1 = new TCanvas("c1", "c1", 700, 700);
  gPad->SetLogy();
  ///*
  c1 -> Divide(4,3);
  for (int i=0; i<12; i++) {
  	c1 -> cd(i+1);
    gPad->SetLogy();

    h1_NNvar_AccNoise_numu[i] -> Draw();
    h1_NNvar_AccNoise_numubar[i] -> Draw("SAME");
    if (i==0) legend -> Draw();

    //h1_NNvar_AccNoise_numu[i] -> Sumw2();
    //h1_NNvar_AccNoise_numu[i] -> Divide(h1_NNvar_AccNoise_numubar[i]);
    //h1_NNvar_AccNoise_numu[i] -> Draw("hist");
    
  }
  //*/

  //h1_NNvar_AccNoise_numu[0] -> Draw();
  //h1_NNvar_AccNoise_numubar[0] -> Draw("SAME");
  //legend -> Draw();

}