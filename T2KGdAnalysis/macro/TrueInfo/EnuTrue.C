#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void EnuTrue() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.noinpmt.root");

  TH1F* h1_ccqe         = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode0");
  TH1F* h1_ccnonqe      = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode1");
  TH1F* h1_nc           = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode2");
  TH1F* h1_ccresdeltap  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode3");
  TH1F* h1_ccresdeltapp = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode4");
  TH1F* h1_ccresdelta0  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode5");
  TH1F* h1_ccother      = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enutrue_mode6");

  h1_ccqe         -> SetStats(0);
  h1_ccnonqe      -> SetStats(0);
  h1_ccresdeltap  -> SetStats(0);
  h1_ccresdeltapp -> SetStats(0);
  h1_ccresdelta0  -> SetStats(0);
  h1_nc           -> SetStats(0);
  h1_ccother      -> SetStats(0);

  THStack* hs_true = new THStack("hs_true", "Truth; Truth Neutrino Energy E_{#nu}; Number of Neutrino Events");
  hs_true -> Add(h1_nc);
  hs_true -> Add(h1_ccother);
  hs_true -> Add(h1_ccresdelta0);
  hs_true -> Add(h1_ccresdeltap);
  hs_true -> Add(h1_ccresdeltapp);
  hs_true -> Add(h1_ccnonqe);
  hs_true -> Add(h1_ccqe);


  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  hs_true -> Draw();
  hs_true ->GetYaxis()->SetTitleSize(0.038);
  hs_true ->GetYaxis()->SetTitleOffset(1.3);
  hs_true ->GetYaxis()->SetLabelSize(0.036);
  hs_true -> Draw();
  //((TGaxis*)h1_ccqe->GetXaxis())->SetMaxDigits(3);
  //h1_ccqe -> SetTitleOffset(1.4, "Y");
  //h1_ccqe -> SetTitleSize(0.035, "Y");
  //h1_ccqe -> SetLabelSize(0.033, "Y");

  /*h1_ccqe         -> Draw();
  h1_ccnonqe      -> Draw("SAME");  
  h1_ccresdeltapp -> Draw("SAME");
  h1_ccresdelta0  -> Draw("SAME");
  h1_ccresdeltap  -> Draw("SAME");
  h1_nc           -> Draw("SAME");*/

  /*h1_ccqe         -> Draw();
  h1_nc           -> Draw("SAME");
  h1_ccnonqe      -> Draw("SAME"); 
  h1_ccresdeltapp -> Draw("SAME");
  h1_ccresdelta0  -> Draw("SAME");
  h1_ccresdeltap  -> Draw("SAME");*/

  /*h1_ccqe         -> Draw();
  h1_ccnonqe      -> Draw("SAME");
  h1_ccresdeltapp -> Draw("SAME");
  h1_ccresdelta0  -> Draw("SAME");
  h1_ccresdeltap  -> Draw("SAME");
  h1_nc           -> Draw("SAME");*/
  
  c1->RedrawAxis();

  TLegend* legend = new TLegend(0.53, 0.47, 0.87, 0.88);
  legend -> SetTextSize(0.03);
  //legend->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend -> AddEntry(h1_ccnonqe, "CC-2p2h", "F");
  legend -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend -> AddEntry(h1_ccother, "CC-other", "F");
  legend -> AddEntry(h1_nc, "NC", "F");
  legend->SetFillColor(0);
  legend->Draw() ;

}