#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

void CombinedEnuOscillation() {
  TFile* fin_numu = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.noinpmt.root");

  TH1F* h1_trueCCQE_numu         = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode0");
  TH1F* h1_trueCCnonQE_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode1");
  TH1F* h1_trueCCRESdeltap_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode3");
  TH1F* h1_trueCCRESdeltapp_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode4");
  TH1F* h1_trueCCRESdelta0_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode5");
  TH1F* h1_trueCCOther_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode6");
  TH1F* h1_trueNC_numu           = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_TruthOscProb_mode2");
  h1_trueCCQE_numu -> SetStats(0);
  h1_trueCCQE_numu         -> SetFillColor(kAzure-1);
  h1_trueCCnonQE_numu      -> SetFillColor(kAzure-5);
  h1_trueCCRESdeltap_numu  -> SetFillColor(kCyan-6);
  h1_trueCCRESdeltapp_numu -> SetFillColor(kCyan-6);
  h1_trueCCRESdelta0_numu  -> SetFillColor(kCyan-6);
  h1_trueCCRESdeltap_numu  -> SetLineColor(kCyan-6);
  h1_trueCCRESdeltapp_numu -> SetLineColor(kCyan-6);
  h1_trueCCRESdelta0_numu  -> SetLineColor(kCyan-6);
  h1_trueCCOther_numu      -> SetLineColor(kCyan-6);
  h1_trueNC_numu           -> SetFillColor(kTeal+9);

  TH1F* h1_trueCCQE_numubar         = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode0");
  TH1F* h1_trueCCnonQE_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode1");
  TH1F* h1_trueCCRESdeltap_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode3");
  TH1F* h1_trueCCRESdeltapp_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode4");
  TH1F* h1_trueCCRESdelta0_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode5");
  TH1F* h1_trueCCOther_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode6");
  TH1F* h1_trueNC_numubar           = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_TruthOscProb_mode2");
  h1_trueCCQE_numubar -> SetStats(0);
  h1_trueCCQE_numubar         -> SetFillColor(kOrange+7);
  h1_trueCCnonQE_numubar      -> SetFillColor(kOrange+6);
  h1_trueCCRESdeltap_numubar  -> SetFillColor(kOrange+0);
  h1_trueCCRESdeltapp_numubar -> SetFillColor(kOrange+0);
  h1_trueCCRESdelta0_numubar  -> SetFillColor(kOrange+0);
  h1_trueCCOther_numubar      -> SetFillColor(kOrange+0);
  h1_trueNC_numubar           -> SetFillColor(kTeal+9);

  h1_trueCCQE_numubar         -> SetLineColor(kOrange+7);
  h1_trueCCnonQE_numubar      -> SetLineColor(kOrange+6);
  h1_trueCCRESdeltap_numubar  -> SetLineColor(kOrange+0);
  h1_trueCCRESdeltapp_numubar -> SetLineColor(kOrange+0);
  h1_trueCCRESdelta0_numubar  -> SetLineColor(kOrange+0);
  h1_trueCCOther_numubar      -> SetLineColor(kOrange+0);
  h1_trueNC_numubar           -> SetLineColor(kTeal+9);

  THStack* hs_trueOsc = new THStack("hs_trueOsc", "Neutrino Oscillation for Truth; Truth Neutrino Energy E_{#nu}; Number of Neutrino Events");
  hs_trueOsc -> Add(h1_trueNC_numu);
  hs_trueOsc -> Add(h1_trueNC_numubar);
  hs_trueOsc -> Add(h1_trueCCOther_numubar);
  hs_trueOsc -> Add(h1_trueCCRESdelta0_numubar);
  hs_trueOsc -> Add(h1_trueCCRESdeltap_numubar);
  hs_trueOsc -> Add(h1_trueCCRESdeltapp_numubar);
  hs_trueOsc -> Add(h1_trueCCnonQE_numubar);
  hs_trueOsc -> Add(h1_trueCCOther_numu);
  hs_trueOsc -> Add(h1_trueCCRESdelta0_numu);
  hs_trueOsc -> Add(h1_trueCCRESdeltap_numu);
  hs_trueOsc -> Add(h1_trueCCRESdeltapp_numu);
  hs_trueOsc -> Add(h1_trueCCnonQE_numu);
  hs_trueOsc -> Add(h1_trueCCQE_numubar);
  hs_trueOsc -> Add(h1_trueCCQE_numu);

  //---------------------------------------

  TH1F* h1_recoCCQE_numu         = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_recoCCnonQE_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_recoCCRESdeltap_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode3");
  TH1F* h1_recoCCRESdeltapp_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode4");
  TH1F* h1_recoCCRESdelta0_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode5");
  TH1F* h1_recoCCOther_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode6");
  TH1F* h1_recoNC_numu           = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_recoCCQE_numu -> SetStats(0);
  h1_recoCCQE_numu         -> SetFillColor(kAzure-1);
  h1_recoCCnonQE_numu      -> SetFillColor(kAzure-5);
  h1_recoCCRESdeltap_numu  -> SetFillColor(kCyan-6);
  h1_recoCCRESdeltapp_numu -> SetFillColor(kCyan-6);
  h1_recoCCRESdelta0_numu  -> SetFillColor(kCyan-6);
  h1_recoCCRESdeltap_numu  -> SetLineColor(kCyan-6);
  h1_recoCCRESdeltapp_numu -> SetLineColor(kCyan-6);
  h1_recoCCRESdelta0_numu  -> SetLineColor(kCyan-6);
  h1_recoCCOther_numu      -> SetLineColor(kCyan-6);
  h1_recoNC_numu           -> SetFillColor(kTeal+9);

  TH1F* h1_recoCCQE_numubar         = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_recoCCnonQE_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_recoCCRESdeltap_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode3");
  TH1F* h1_recoCCRESdeltapp_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode4");
  TH1F* h1_recoCCRESdelta0_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode5");
  TH1F* h1_recoCCOther_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode6");
  TH1F* h1_recoNC_numubar           = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_recoCCQE_numubar -> SetStats(0);
  h1_recoCCQE_numubar         -> SetFillColor(kOrange+7);
  h1_recoCCnonQE_numubar      -> SetFillColor(kOrange+6);
  h1_recoCCRESdeltap_numubar  -> SetFillColor(kOrange+0);
  h1_recoCCRESdeltapp_numubar -> SetFillColor(kOrange+0);
  h1_recoCCRESdelta0_numubar  -> SetFillColor(kOrange+0);
  h1_recoCCOther_numubar      -> SetFillColor(kOrange+0);
  h1_recoNC_numubar           -> SetFillColor(kTeal+9);

  h1_recoCCQE_numubar         -> SetLineColor(kOrange+7);
  h1_recoCCnonQE_numubar      -> SetLineColor(kOrange+6);
  h1_recoCCRESdeltap_numubar  -> SetLineColor(kOrange+0);
  h1_recoCCRESdeltapp_numubar -> SetLineColor(kOrange+0);
  h1_recoCCRESdelta0_numubar  -> SetLineColor(kOrange+0);
  h1_recoCCOther_numubar      -> SetLineColor(kOrange+0);
  h1_recoNC_numubar           -> SetLineColor(kTeal+9);

  THStack* hs_recoOsc = new THStack("hs_recoOsc", "Neutrino Oscillation for Reco; Reconstructed Neutrino Energy E_{#nu}; Number of Neutrino Events");
  hs_recoOsc -> Add(h1_recoNC_numu);
  hs_recoOsc -> Add(h1_recoNC_numubar);
  hs_recoOsc -> Add(h1_recoCCOther_numubar);
  hs_recoOsc -> Add(h1_recoCCRESdelta0_numubar);
  hs_recoOsc -> Add(h1_recoCCRESdeltap_numubar);
  hs_recoOsc -> Add(h1_recoCCRESdeltapp_numubar);
  hs_recoOsc -> Add(h1_recoCCnonQE_numubar);
  hs_recoOsc -> Add(h1_recoCCOther_numu);
  hs_recoOsc -> Add(h1_recoCCRESdelta0_numu);
  hs_recoOsc -> Add(h1_recoCCRESdeltap_numu);
  hs_recoOsc -> Add(h1_recoCCRESdeltapp_numu);
  hs_recoOsc -> Add(h1_recoCCnonQE_numu);
  hs_recoOsc -> Add(h1_recoCCQE_numubar);
  hs_recoOsc -> Add(h1_recoCCQE_numu);



  gROOT -> SetStyle("Plain");

  
  TCanvas* c0 = new TCanvas("c0","c0",900,700);
  c0 -> SetGrid();
  hs_trueOsc -> Draw();
  hs_trueOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_trueOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_trueOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_trueOsc -> Draw();
  c0->RedrawAxis();

  TLegend* legend0 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend0 -> SetTextSize(0.03);
  legend0->AddEntry((TObject*)0,"#kern[-0.5]{ FHC MC }","");
  legend0 -> AddEntry(h1_trueCCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend0 -> AddEntry(h1_trueCCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend0 -> AddEntry(h1_trueCCnonQE_numu, "#nu_{#mu} CC-2p2h", "F");
  legend0 -> AddEntry(h1_trueCCnonQE_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend0 -> AddEntry(h1_trueCCOther_numu, "#nu_{#mu} CC-other", "F");
  legend0 -> AddEntry(h1_trueCCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend0 -> AddEntry(h1_trueNC_numu, "NC", "F");
  legend0 -> SetFillColor(0);
  legend0 -> Draw() ;

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  hs_recoOsc -> SetMaximum(2000);
  hs_recoOsc -> Draw();
  hs_recoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_recoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_recoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_recoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.6, 0.45, 0.85, 0.9);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.4]{ FHC MC }","");
  legend1 -> AddEntry(h1_trueCCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_trueCCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_trueCCnonQE_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_trueCCnonQE_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_trueCCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_trueCCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_trueNC_numu, "NC", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw() ;
  
}