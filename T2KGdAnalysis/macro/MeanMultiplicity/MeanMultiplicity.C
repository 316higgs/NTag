
TH1F* h1_MeanMultiplicity_fhc;
TH1F* h1_MeanMultiplicity_rhc;

TH1F* h1_MeanMultiplicityCCQE_fhc;
TH1F* h1_MeanMultiplicityCCQE_rhc;

TH1F* h1_MeanMultiplicityCCnonQE_fhc;
TH1F* h1_MeanMultiplicityCCnonQE_rhc;

void MeanMultiplicity() {

  TFile* fin_skrate_fhc  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate_rhc  = new TFile("./rhc.sk_rate_tmp.root");

  //Normalization
  Double_t GenN_numu_x_numu       = 190292;
  Double_t GenN_numubar_x_numubar = 190909;

  TH1F* h1_skrate_numu_x_numu_fhc       = (TH1F*)fin_skrate_fhc->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar_fhc = (TH1F*)fin_skrate_fhc->Get("skrate_numu_bar_x_numu_bar");
  Double_t ExpN_numu_x_numu_fhc         = h1_skrate_numu_x_numu_fhc->Integral();
  Double_t ExpN_numubar_x_numubar_fhc   = h1_skrate_numubar_x_numubar_fhc->Integral();
  Double_t Norm_numu_x_numu_fhc         = (ExpN_numu_x_numu_fhc)/(GenN_numu_x_numu);
  Double_t Norm_numubar_x_numubar_fhc   = (ExpN_numubar_x_numubar_fhc)/(GenN_numubar_x_numubar);
  
  TH1F* h1_skrate_numu_x_numu_rhc       = (TH1F*)fin_skrate_rhc->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar_rhc = (TH1F*)fin_skrate_rhc->Get("skrate_numu_bar_x_numu_bar");
  Double_t ExpN_numu_x_numu_rhc         = h1_skrate_numu_x_numu_rhc->Integral();
  Double_t ExpN_numubar_x_numubar_rhc   = h1_skrate_numubar_x_numubar_rhc->Integral();
  Double_t Norm_numu_x_numu_rhc         = (ExpN_numu_x_numu_rhc)/(GenN_numu_x_numu);
  Double_t Norm_numubar_x_numubar_rhc   = (ExpN_numubar_x_numubar_rhc)/(GenN_numubar_x_numubar);

  //Neutrons
  //  All
  const int NumNeutrons_numu    = 90605;
  const int NumNeutrons_numubar = 182587;
  const int NumNeutrons_fhc  = Norm_numu_x_numu_fhc*NumNeutrons_numu + Norm_numubar_x_numubar_fhc*NumNeutrons_numubar;
  const int NumNeutrons_rhc  = Norm_numu_x_numu_rhc*NumNeutrons_numu + Norm_numubar_x_numubar_rhc*NumNeutrons_numubar;
  //  CCQE
  const int NumNeutronsCCQE_numu    = 58008;
  const int NumNeutronsCCQE_numubar = 99142;
  const int NumNeutronsCCQE_fhc  = Norm_numu_x_numu_fhc*NumNeutronsCCQE_numu + Norm_numubar_x_numubar_fhc*NumNeutronsCCQE_numubar;
  const int NumNeutronsCCQE_rhc  = Norm_numu_x_numu_rhc*NumNeutronsCCQE_numu + Norm_numubar_x_numubar_rhc*NumNeutronsCCQE_numubar;
  //  CC non-QE
  const int NumNeutronsCCnonQE_numu    = 30981;
  const int NumNeutronsCCnonQE_numubar = 81129;
  const int NumNeutronsCCnonQE_fhc  = Norm_numu_x_numu_fhc*NumNeutronsCCnonQE_numu + Norm_numubar_x_numubar_fhc*NumNeutronsCCnonQE_numubar;
  const int NumNeutronsCCnonQE_rhc  = Norm_numu_x_numu_rhc*NumNeutronsCCnonQE_numu + Norm_numubar_x_numubar_rhc*NumNeutronsCCnonQE_numubar;

  //Neutrinos
  //  All
  const int NumNeutrinos_numu    = 80522;
  const int NumNeutrinos_numubar = 71169;
  const int NumNeutrinos_fhc  = Norm_numu_x_numu_fhc*NumNeutrinos_numu + Norm_numubar_x_numubar_fhc*NumNeutrinos_numubar;
  const int NumNeutrinos_rhc  = Norm_numu_x_numu_rhc*NumNeutrinos_numu + Norm_numubar_x_numubar_rhc*NumNeutrinos_numubar;
  //  CCQE
  const int NumNeutrinosCCQE_numu    = 64871;
  const int NumNeutrinosCCQE_numubar = 49087;
  const int NumNeutrinosCCQE_fhc  = Norm_numu_x_numu_fhc*NumNeutrinosCCQE_numu + Norm_numubar_x_numubar_fhc*NumNeutrinosCCQE_numubar;
  const int NumNeutrinosCCQE_rhc  = Norm_numu_x_numu_rhc*NumNeutrinosCCQE_numu + Norm_numubar_x_numubar_rhc*NumNeutrinosCCQE_numubar;
  //  CC non-QE
  const int NumNeutrinosCCnonQE_numu    = 15077;
  const int NumNeutrinosCCnonQE_numubar = 21258;
  const int NumNeutrinosCCnonQE_fhc  = Norm_numu_x_numu_fhc*NumNeutrinosCCnonQE_numu + Norm_numubar_x_numubar_fhc*NumNeutrinosCCnonQE_numubar;
  const int NumNeutrinosCCnonQE_rhc  = Norm_numu_x_numu_rhc*NumNeutrinosCCnonQE_numu + Norm_numubar_x_numubar_rhc*NumNeutrinosCCnonQE_numubar;



  h1_MeanMultiplicity_fhc = new TH1F("h1_MeanMultiplicity_fhc", "h1_MeanMultiplicity", 2, 0, 2);
  h1_MeanMultiplicity_rhc = new TH1F("h1_MeanMultiplicity_rhc", "h1_MeanMultiplicity", 2, 0, 2);

  h1_MeanMultiplicity_fhc -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicity_fhc -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicity_fhc -> SetStats(0);
  h1_MeanMultiplicity_fhc -> SetLineWidth(3);
  h1_MeanMultiplicity_fhc -> SetLineColor(kAzure+2);
  //h1_MeanMultiplicity_fhc -> SetMarkerStyle(20);
  //h1_MeanMultiplicity_fhc -> SetMarkerSize(1);
  //h1_MeanMultiplicity_fhc -> SetMarkerSize(1);
  h1_MeanMultiplicity_fhc -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutrons_fhc; i++) h1_MeanMultiplicity_fhc -> Fill(0);
  h1_MeanMultiplicity_fhc -> Scale(1./NumNeutrinos_fhc);

  h1_MeanMultiplicity_rhc -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicity_rhc -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicity_rhc -> SetStats(0);
  h1_MeanMultiplicity_rhc -> SetLineWidth(3);
  h1_MeanMultiplicity_rhc -> SetLineColor(kOrange+8);
  h1_MeanMultiplicity_rhc -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutrons_rhc; i++) h1_MeanMultiplicity_rhc -> Fill(1);
  h1_MeanMultiplicity_rhc -> Scale(1./NumNeutrinos_rhc);


  h1_MeanMultiplicityCCQE_fhc    = new TH1F("h1_MeanMultiplicityCCQE_fhc", "h1_MeanMultiplicity", 2, 0, 2);
  h1_MeanMultiplicityCCQE_rhc = new TH1F("h1_MeanMultiplicityCCQE_rhc", "h1_MeanMultiplicity", 2, 0, 2);

  h1_MeanMultiplicityCCQE_fhc -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCQE_fhc -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCQE_fhc -> SetStats(0);
  h1_MeanMultiplicityCCQE_fhc -> SetLineWidth(3);
  h1_MeanMultiplicityCCQE_fhc -> SetLineColor(kAzure+2);
  h1_MeanMultiplicityCCQE_fhc -> SetLineStyle(9);
  h1_MeanMultiplicityCCQE_fhc -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCQE_fhc; i++) h1_MeanMultiplicityCCQE_fhc -> Fill(0);
  h1_MeanMultiplicityCCQE_fhc -> Scale(1./NumNeutrinosCCQE_fhc);

  h1_MeanMultiplicityCCQE_rhc -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCQE_rhc -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCQE_rhc -> SetStats(0);
  h1_MeanMultiplicityCCQE_rhc -> SetLineWidth(3);
  h1_MeanMultiplicityCCQE_rhc -> SetLineColor(kOrange+8);
  h1_MeanMultiplicityCCQE_rhc -> SetLineStyle(9);
  h1_MeanMultiplicityCCQE_rhc -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCQE_rhc; i++) h1_MeanMultiplicityCCQE_rhc -> Fill(1);
  h1_MeanMultiplicityCCQE_rhc -> Scale(1./NumNeutrinosCCQE_rhc);


  h1_MeanMultiplicityCCnonQE_fhc    = new TH1F("h1_MeanMultiplicityCCnonQE_fhc", "h1_MeanMultiplicity", 2, 0, 2);
  h1_MeanMultiplicityCCnonQE_rhc = new TH1F("h1_MeanMultiplicityCCnonQE_rhc", "h1_MeanMultiplicity", 2, 0, 2);

  h1_MeanMultiplicityCCnonQE_fhc -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCnonQE_fhc -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCnonQE_fhc -> SetStats(0);
  h1_MeanMultiplicityCCnonQE_fhc -> SetLineWidth(3);
  h1_MeanMultiplicityCCnonQE_fhc -> SetLineColor(kAzure+2);
  h1_MeanMultiplicityCCnonQE_fhc -> SetLineStyle(2);
  h1_MeanMultiplicityCCnonQE_fhc -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCnonQE_fhc; i++) h1_MeanMultiplicityCCnonQE_fhc -> Fill(0);
  h1_MeanMultiplicityCCnonQE_fhc -> Scale(1./NumNeutrinosCCnonQE_fhc);

  h1_MeanMultiplicityCCnonQE_rhc -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCnonQE_rhc -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCnonQE_rhc -> SetStats(0);
  h1_MeanMultiplicityCCnonQE_rhc -> SetLineWidth(3);
  h1_MeanMultiplicityCCnonQE_rhc -> SetLineColor(kOrange+8);
  h1_MeanMultiplicityCCnonQE_rhc -> SetLineStyle(2);
  h1_MeanMultiplicityCCnonQE_rhc -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCnonQE_rhc; i++) h1_MeanMultiplicityCCnonQE_rhc -> Fill(1);
  h1_MeanMultiplicityCCnonQE_rhc -> Scale(1./NumNeutrinosCCnonQE_rhc);


  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  if (NumNeutrons_rhc > NumNeutrons_fhc) h1_MeanMultiplicity_fhc -> SetMaximum(5);
  h1_MeanMultiplicity_fhc           -> Draw();
  h1_MeanMultiplicity_rhc        -> Draw("SAME");
  h1_MeanMultiplicityCCQE_fhc       -> Draw("SAME");
  h1_MeanMultiplicityCCQE_rhc    -> Draw("SAME");
  h1_MeanMultiplicityCCnonQE_fhc    -> Draw("SAME");
  h1_MeanMultiplicityCCnonQE_rhc -> Draw("SAME");


  // auxial lines for TLegend
  double x[10];  //Array size iteslf is meaaningless
  double y[10];
  for (int i=0; i<10; i++) {
    x[i] = i;
    y[i] = 0;
  }
  TGraph *graph_sample1 = new TGraph(10, x, y);
  graph_sample1 -> SetLineWidth(3);
  graph_sample1 -> SetLineColor(kBlack);

  TGraph *graph_sample2 = new TGraph(10, x, y);
  graph_sample2 -> SetLineWidth(3);
  graph_sample2 -> SetLineStyle(9);
  graph_sample2 -> SetLineColor(kBlack);

  TGraph *graph_sample3 = new TGraph(10, x, y);
  graph_sample3 -> SetLineWidth(3);
  graph_sample3 -> SetLineStyle(2);
  graph_sample3 -> SetLineColor(kBlack);

  TLegend* legend = new TLegend(0.55, 0.13, 0.87, 0.35);
  legend -> SetTextSize(0.035);
  legend -> AddEntry(h1_MeanMultiplicity_fhc, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC", "L");
  legend -> AddEntry(h1_MeanMultiplicity_rhc, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC", "L");
  legend -> AddEntry(graph_sample1, "All Interactions", "L");
  legend -> AddEntry(graph_sample2, "CCQE", "L");
  legend -> AddEntry(graph_sample3, "CC non-QE", "L");
  legend->SetFillColor(0);
  legend->Draw() ;
}
