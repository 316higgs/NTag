#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void EnuTrue() {
  TFile* fin1 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* fin2 = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");

  TH1F* h1_ccqe1         = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode0");
  TH1F* h1_ccnonqe1      = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode1");
  TH1F* h1_nc1           = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode2");
  TH1F* h1_ccresdeltap1  = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode3");
  TH1F* h1_ccresdeltapp1 = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode4");
  TH1F* h1_ccresdelta01  = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode5");
  TH1F* h1_ccother1      = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enutrue_mode6");

  h1_ccqe1         -> SetStats(0);
  h1_ccnonqe1      -> SetStats(0);
  h1_ccresdeltap1  -> SetStats(0);
  h1_ccresdeltapp1 -> SetStats(0);
  h1_ccresdelta01  -> SetStats(0);
  h1_nc1           -> SetStats(0);
  h1_ccother1      -> SetStats(0);

  THStack* hs_true1 = new THStack("hs_true1", "Truth; Truth Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
  hs_true1 -> Add(h1_nc1);
  hs_true1 -> Add(h1_ccother1);
  hs_true1 -> Add(h1_ccresdelta01);
  hs_true1 -> Add(h1_ccresdeltap1);
  hs_true1 -> Add(h1_ccresdeltapp1);
  hs_true1 -> Add(h1_ccnonqe1);
  hs_true1 -> Add(h1_ccqe1);


  TH1F* h1_ccqe2         = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode0");
  TH1F* h1_ccnonqe2      = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode1");
  TH1F* h1_nc2           = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode2");
  TH1F* h1_ccresdeltap2  = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode3");
  TH1F* h1_ccresdeltapp2 = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode4");
  TH1F* h1_ccresdelta02  = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode5");
  TH1F* h1_ccother2      = (TH1F*)fin2->Get("NeutrinoOscillation/h1_Enutrue_mode6");

  h1_ccqe2         -> SetStats(0);
  h1_ccnonqe2      -> SetStats(0);
  h1_ccresdeltap2  -> SetStats(0);
  h1_ccresdeltapp2 -> SetStats(0);
  h1_ccresdelta02  -> SetStats(0);
  h1_nc2           -> SetStats(0);
  h1_ccother2      -> SetStats(0);

  THStack* hs_true2 = new THStack("hs_true2", "Truth; Truth Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
  hs_true2 -> Add(h1_nc2);
  hs_true2 -> Add(h1_ccother2);
  hs_true2 -> Add(h1_ccresdelta02);
  hs_true2 -> Add(h1_ccresdeltap2);
  hs_true2 -> Add(h1_ccresdeltapp2);
  hs_true2 -> Add(h1_ccnonqe2);
  hs_true2 -> Add(h1_ccqe2);


  TLegend* legend1 = new TLegend(0.53, 0.47, 0.87, 0.88);
  legend1 -> SetTextSize(0.03);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC (applied FCFV cut)}","");
  //legend1 ->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend1 -> AddEntry(h1_ccqe1, "CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_ccnonqe1, "CC-2p2h", "F");
  legend1 -> AddEntry(h1_ccresdeltap1, "CCRES(#Delta^{+})", "F");
  legend1 -> AddEntry(h1_ccresdeltapp1, "CCRES(#Delta^{++})", "F");
  legend1 -> AddEntry(h1_ccresdelta01, "CCRES(#Delta^{0})", "F");
  legend1 -> AddEntry(h1_ccother1, "CC-other", "F");
  legend1 -> AddEntry(h1_nc1, "NC", "F");
  legend1 -> SetFillColor(0);

  TLegend* legend2 = new TLegend(0.53, 0.47, 0.87, 0.88);
  legend2 -> SetTextSize(0.03);
  //legend->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend2 ->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC (applied FCFV cut)}","");
  legend2 -> AddEntry(h1_ccqe1, "CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_ccnonqe1, "CC-2p2h", "F");
  legend2 -> AddEntry(h1_ccresdeltap1, "CCRES(#Delta^{+})", "F");
  legend2 -> AddEntry(h1_ccresdeltapp1, "CCRES(#Delta^{++})", "F");
  legend2 -> AddEntry(h1_ccresdelta01, "CCRES(#Delta^{0})", "F");
  legend2 -> AddEntry(h1_ccother1, "CC-other", "F");
  legend2 -> AddEntry(h1_nc1, "NC", "F");
  legend2 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,900);
  c1 -> Divide(1,2);
  c1 -> cd(1);
  hs_true1 -> Draw();
  hs_true1 ->GetYaxis()->SetTitleSize(0.038);
  hs_true1 ->GetYaxis()->SetTitleOffset(1.3);
  hs_true1 ->GetYaxis()->SetLabelSize(0.036);
  hs_true1 -> Draw();
  c1->RedrawAxis();
  legend1->Draw() ;

  c1 -> cd(2);
  hs_true2 -> Draw();
  hs_true2 ->GetYaxis()->SetTitleSize(0.038);
  hs_true2 ->GetYaxis()->SetTitleOffset(1.3);
  hs_true2 ->GetYaxis()->SetLabelSize(0.036);
  hs_true2 -> Draw();
  c1->RedrawAxis();
  legend2->Draw() ;

}