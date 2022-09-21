#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

void mergeDistance() {
  //FHC
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");

  //RHC
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");

  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral();
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral();
  Double_t GenN_numu_x_numu         = 190292;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_CCQE");
  //TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode1");
  //TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_CCnonQE");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_CCQE");
  //TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode1");
  //TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_CCnonQE");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_numubar -> SetStats(0);

  //h1_CCOther_numu -> SetLineColor(kCyan-8);
  //h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar   -> SetLineColor(kOrange+7);
  h1_CCQE_numubar   -> SetLineColor(kOrange+7);
  //h1_CC2p2h_numubar -> SetLineColor(kOrange+6);
  //h1_CC2p2h_numubar -> SetLineColor(kOrange+6);
  //h1_CCOther_numubar -> SetLineColor(kOrange+0);
  //h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar   -> SetFillColor(kOrange+7);
  h1_CCQE_numubar   -> SetFillColor(kOrange+7);
  //h1_CC2p2h_numubar -> SetFillColor(kOrange+6);
  //h1_CC2p2h_numubar -> SetFillColor(kOrange+6);
  //h1_CCOther_numubar -> SetFillColor(kOrange+0);
  //h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_CC2p2h_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //h1_CC2p2h_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //h1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCnonQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCnonQE_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "Truth Distance; Truth Neutron Flight Distance[m]; Number of Neutron Events");
  /*
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_CCnonQE_numubar);
  hs_RecoOsc -> Add(h1_CCnonQE_numu);
  //hs_RecoOsc -> Add(h1_CCOther_numubar);
  //hs_RecoOsc -> Add(h1_CCOther_numu);
  //hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  //hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
  */
  ///*
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_CCnonQE_numu);
  hs_RecoOsc -> Add(h1_CCnonQE_numubar);
  //hs_RecoOsc -> Add(h1_CCOther_numu);
  //hs_RecoOsc -> Add(h1_CCOther_numubar);
  //hs_RecoOsc -> Add(h1_CC2p2h_numu);
  //hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  //*/


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  //hs_RecoOsc -> SetMaximum(3100);
  //hs_RecoOsc -> SetMaximum(2000);
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.87, 0.87);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  //legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;

}