void NNinput() {

  TFile* finnumu = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.root");

  TH1F* h1_NNvar_Gd_numu[12];
  TH1F* h1_NNvar_H_numu[12];
  TH1F* h1_NNvar_AccNoise_numu[12];
  TH1F* h1_NNvar_Decaye_numu[12];

  for (int i=0; i<12; i++) {
    h1_NNvar_Gd_numu[i]       = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_numu[i]        = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_numu[i] = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_numu[i]   = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_numu[i]    -> SetStats(0);
    h1_NNvar_H_numu[i]     -> SetStats(0);
    h1_NNvar_AccNoise_numu[i] -> SetStats(0);
    h1_NNvar_Decaye_numu[i] -> SetStats(0);
  }

  TLegend* legend = new TLegend(0.4, 0.4, 0.87, 0.87);
  legend -> SetTextSize(0.06);
  legend -> AddEntry(h1_NNvar_Gd_numu[0], "Gd-n signal", "L");
  legend -> AddEntry(h1_NNvar_H_numu[0], "H-n signal", "L");
  legend -> AddEntry(h1_NNvar_Decaye_numu[0], "Decay-e", "L");
  legend -> AddEntry(h1_NNvar_AccNoise_numu[0], "Acc. noise", "L");
  legend -> SetFillColor(0);
  //legend->SetLineColor(0);
  //legend->SetFillColor(0);
  //legend->SetFillStyle(0);
  legend->SetBorderSize(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1000);
  c1 -> Divide(4,3);
  for (int i=0; i<12; i++) {
    c1 -> cd(i+1);
    //gPad->SetLogy();

    if (i==0 || i==1 || i==3 || i==4) {
      h1_NNvar_AccNoise_numu[i] -> Draw();
      h1_NNvar_H_numu[i]        -> Draw("SAME");
      h1_NNvar_Gd_numu[i]       -> Draw("SAME");
      h1_NNvar_Decaye_numu[i]   -> Draw("SAME");
      if (i==0) legend -> Draw();
    }

    else {
      h1_NNvar_Decaye_numu[i]   -> Draw();
      h1_NNvar_Gd_numu[i]       -> Draw("SAME");
      h1_NNvar_H_numu[i]        -> Draw("SAME");
      h1_NNvar_AccNoise_numu[i] -> Draw("SAME");
    }
    
  }

}