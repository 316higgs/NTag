void MuonCapture() {

  TFile* finnumu    = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.muminus.root");
  TFile* finnumubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.muminus.root");

  TH1F* h1_tscnd_numu    = (TH1F*)finnumu->Get("NNInputVariables/h1_tscnd_capture");
  TH1F* h1_tscnd_numubar = (TH1F*)finnumubar->Get("NNInputVariables/h1_tscnd_capture");

  TH1F* h1_energy_numu    = (TH1F*)finnumu->Get("NNInputVariables/h1_energy_capture");
  TH1F* h1_energy_numubar = (TH1F*)finnumubar->Get("NNInputVariables/h1_energy_capture");

  h1_tscnd_numu -> SetStats(0);
  h1_tscnd_numu ->GetYaxis()->SetTitleSize(0.038);
  h1_tscnd_numu ->GetYaxis()->SetTitleOffset(1.3);
  h1_tscnd_numu ->GetYaxis()->SetLabelSize(0.036);
  h1_tscnd_numu -> SetLineColor(kAzure-8);
  h1_tscnd_numubar -> SetLineColor(kOrange-3);

  h1_energy_numu -> SetStats(0);
  h1_energy_numu ->GetYaxis()->SetTitleSize(0.038);
  h1_energy_numu ->GetYaxis()->SetTitleOffset(1.3);
  h1_energy_numu ->GetYaxis()->SetLabelSize(0.036);
  h1_energy_numu -> SetLineColor(kAzure-8);
  h1_energy_numubar -> SetLineColor(kOrange-3);


  TLegend* legend = new TLegend(0.42, 0.5, 0.6, 0.75);
  legend -> SetTextSize(0.03);
  legend -> AddEntry(h1_tscnd_numu, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC", "L");
  legend -> AddEntry(h1_tscnd_numubar, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC", "L");
  legend -> SetFillColor(0);
  legend->SetBorderSize(0);

  gROOT -> SetStyle("Plain");

  TCanvas* c2 = new TCanvas("c2", "c2", 800, 800);
  h1_energy_numu -> Draw();
  h1_energy_numubar -> Draw("SAME");
  legend -> Draw();

}