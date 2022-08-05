void NNinput() {

  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.NNtest.root");

  TH1F* h1_NNvar_Gd[12];
  TH1F* h1_NNvar_H[12];
  TH1F* h1_NNvar_AccNoise[12];
  TH1F* h1_NNvar_Decaye[12];

  for (int i=0; i<12; i++) {
  	h1_NNvar_Gd[i]       = (TH1F*)fin->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
  	h1_NNvar_H[i]        = (TH1F*)fin->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
  	h1_NNvar_AccNoise[i] = (TH1F*)fin->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye[i]   = (TH1F*)fin->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

  	h1_NNvar_Gd[i]    -> SetStats(0);
  	h1_NNvar_H[i]     -> SetStats(0);
  	h1_NNvar_AccNoise[i] -> SetStats(0);
    h1_NNvar_Decaye[i] -> SetStats(0);
  }

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1000);
  c1 -> Divide(4,3);
  for (int i=0; i<12; i++) {
  	c1 -> cd(i+1);
    gPad->SetLogy();
    if (i==0 || i==1 || i==3 || i==4) {
      h1_NNvar_AccNoise[i] -> Draw();
      h1_NNvar_Decaye[i] -> Draw("SAME");
      h1_NNvar_H[i]     -> Draw("SAME");
      h1_NNvar_Gd[i]    -> Draw("SAME");
    }
    if (i==10 || i==11) {
      h1_NNvar_Decaye[i]     -> Draw();
      h1_NNvar_Gd[i]    -> Draw("SAME");
      h1_NNvar_H[i] -> Draw("SAME");
      h1_NNvar_AccNoise[i] -> Draw("SAME");
    }
    if (i==2 || i==5 || i==6 || i==7 || i==8 || i==9) {
      h1_NNvar_H[i]     -> Draw();
      h1_NNvar_Gd[i]    -> Draw("SAME");
      h1_NNvar_Decaye[i] -> Draw("SAME");
      h1_NNvar_AccNoise[i] -> Draw("SAME");
    }
  }
}