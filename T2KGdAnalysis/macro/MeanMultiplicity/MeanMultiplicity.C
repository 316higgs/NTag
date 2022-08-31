
TH1F* h1_MeanMultiplicity_numu;
TH1F* h1_MeanMultiplicity_numubar;

TH1F* h1_MeanMultiplicityCCQE_numu;
TH1F* h1_MeanMultiplicityCCQE_numubar;

TH1F* h1_MeanMultiplicityCCnonQE_numu;
TH1F* h1_MeanMultiplicityCCnonQE_numubar;

void MeanMultiplicity() {

  const int NumNeutrons_numu     = 90605;
  const int NumNeutrinos_numu    = 80522;
  const int NumNeutrons_numubar  = 182587;
  const int NumNeutrinos_numubar = 80522;

  const int NumNeutronsCCQE_numu     = 58008;
  const int NumNeutrinosCCQE_numu    = 64871;
  const int NumNeutronsCCQE_numubar  = 99142;
  const int NumNeutrinosCCQE_numubar = 49087;

  const int NumNeutronsCCnonQE_numu     = 30981;
  const int NumNeutrinosCCnonQE_numu    = 15077;
  const int NumNeutronsCCnonQE_numubar  = 81129;
  const int NumNeutrinosCCnonQE_numubar = 21258;


  h1_MeanMultiplicity_numu    = new TH1F("h1_MeanMultiplicity_numu", "h1_MeanMultiplicity", 2, 0, 2);
  h1_MeanMultiplicity_numubar = new TH1F("h1_MeanMultiplicity_numubar", "h1_MeanMultiplicity", 2, 0, 2);

  h1_MeanMultiplicity_numu -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicity_numu -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicity_numu -> SetStats(0);
  h1_MeanMultiplicity_numu -> SetLineWidth(3);
  h1_MeanMultiplicity_numu -> SetLineColor(kAzure+2);
  //h1_MeanMultiplicity_numu -> SetMarkerStyle(20);
  //h1_MeanMultiplicity_numu -> SetMarkerSize(1);
  //h1_MeanMultiplicity_numu -> SetMarkerSize(1);
  h1_MeanMultiplicity_numu -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutrons_numu; i++) h1_MeanMultiplicity_numu -> Fill(0);
  h1_MeanMultiplicity_numu -> Scale(1./NumNeutrinos_numu);

  h1_MeanMultiplicity_numubar -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicity_numubar -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicity_numubar -> SetStats(0);
  h1_MeanMultiplicity_numubar -> SetLineWidth(3);
  h1_MeanMultiplicity_numubar -> SetLineColor(kOrange+8);
  h1_MeanMultiplicity_numubar -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutrons_numubar; i++) h1_MeanMultiplicity_numubar -> Fill(1);
  h1_MeanMultiplicity_numubar -> Scale(1./NumNeutrinos_numubar);


  h1_MeanMultiplicityCCQE_numu    = new TH1F("h1_MeanMultiplicityCCQE_numu", "h1_MeanMultiplicity", 2, 0, 2);
  h1_MeanMultiplicityCCQE_numubar = new TH1F("h1_MeanMultiplicityCCQE_numubar", "h1_MeanMultiplicity", 2, 0, 2);

  h1_MeanMultiplicityCCQE_numu -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCQE_numu -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCQE_numu -> SetStats(0);
  h1_MeanMultiplicityCCQE_numu -> SetLineWidth(3);
  h1_MeanMultiplicityCCQE_numu -> SetLineColor(kAzure+2);
  h1_MeanMultiplicityCCQE_numu -> SetLineStyle(9);
  h1_MeanMultiplicityCCQE_numu -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCQE_numu; i++) h1_MeanMultiplicityCCQE_numu -> Fill(0);
  h1_MeanMultiplicityCCQE_numu -> Scale(1./NumNeutrinosCCQE_numu);

  h1_MeanMultiplicityCCQE_numubar -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCQE_numubar -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCQE_numubar -> SetStats(0);
  h1_MeanMultiplicityCCQE_numubar -> SetLineWidth(3);
  h1_MeanMultiplicityCCQE_numubar -> SetLineColor(kOrange+8);
  h1_MeanMultiplicityCCQE_numubar -> SetLineStyle(9);
  h1_MeanMultiplicityCCQE_numubar -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCQE_numubar; i++) h1_MeanMultiplicityCCQE_numubar -> Fill(1);
  h1_MeanMultiplicityCCQE_numubar -> Scale(1./NumNeutrinosCCQE_numubar);


  h1_MeanMultiplicityCCnonQE_numu    = new TH1F("h1_MeanMultiplicityCCnonQE_numu", "h1_MeanMultiplicity", 2, 0, 2);
  h1_MeanMultiplicityCCnonQE_numubar = new TH1F("h1_MeanMultiplicityCCnonQE_numubar", "h1_MeanMultiplicity", 2, 0, 2);

  h1_MeanMultiplicityCCnonQE_numu -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCnonQE_numu -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCnonQE_numu -> SetStats(0);
  h1_MeanMultiplicityCCnonQE_numu -> SetLineWidth(3);
  h1_MeanMultiplicityCCnonQE_numu -> SetLineColor(kAzure+2);
  h1_MeanMultiplicityCCnonQE_numu -> SetLineStyle(2);
  h1_MeanMultiplicityCCnonQE_numu -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCnonQE_numu; i++) h1_MeanMultiplicityCCnonQE_numu -> Fill(0);
  h1_MeanMultiplicityCCnonQE_numu -> Scale(1./NumNeutrinosCCnonQE_numu);

  h1_MeanMultiplicityCCnonQE_numubar -> GetXaxis()->SetBinLabel(1, "#nu_{#mu}#rightarrow#nu_{#mu}");
  h1_MeanMultiplicityCCnonQE_numubar -> GetXaxis()->SetBinLabel(2, "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu}");
  h1_MeanMultiplicityCCnonQE_numubar -> SetStats(0);
  h1_MeanMultiplicityCCnonQE_numubar -> SetLineWidth(3);
  h1_MeanMultiplicityCCnonQE_numubar -> SetLineColor(kOrange+8);
  h1_MeanMultiplicityCCnonQE_numubar -> SetLineStyle(2);
  h1_MeanMultiplicityCCnonQE_numubar -> SetLabelSize(0.06);
  for (int i=0; i<NumNeutronsCCnonQE_numubar; i++) h1_MeanMultiplicityCCnonQE_numubar -> Fill(1);
  h1_MeanMultiplicityCCnonQE_numubar -> Scale(1./NumNeutrinosCCnonQE_numubar);


  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  if (NumNeutrons_numubar > NumNeutrons_numu) h1_MeanMultiplicity_numu -> SetMaximum(5);
  h1_MeanMultiplicity_numu           -> Draw();
  h1_MeanMultiplicity_numubar        -> Draw("SAME");
  h1_MeanMultiplicityCCQE_numu       -> Draw("SAME");
  h1_MeanMultiplicityCCQE_numubar    -> Draw("SAME");
  h1_MeanMultiplicityCCnonQE_numu    -> Draw("SAME");
  h1_MeanMultiplicityCCnonQE_numubar -> Draw("SAME");


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
  legend -> AddEntry(h1_MeanMultiplicity_numu, "FHC #nu_{#mu} #rightarrow #nu_{#mu} MC", "L");
  legend -> AddEntry(h1_MeanMultiplicity_numubar, "FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC", "L");
  legend -> AddEntry(graph_sample1, "All Interactions", "L");
  legend -> AddEntry(graph_sample2, "CCQE", "L");
  legend -> AddEntry(graph_sample3, "CC non-QE", "L");
  legend->SetFillColor(0);
  legend->Draw() ;
}
