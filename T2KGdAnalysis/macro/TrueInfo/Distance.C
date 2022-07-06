#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Distance() {
  TFile* fin = new TFile("../../output/fhc.numu_x_numu.etagON.root");

  TH1F* h1_ccqe         = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_ccnonqe      = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_CCnonQE");
  TH1F* h1_nc           = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_NC");
  TH1F* h1_ccresdeltap  = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_CCRESdeltap");
  TH1F* h1_ccresdeltapp = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_CCRESdeltapp");
  TH1F* h1_ccresdelta0  = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_CCRESdelta0");

  h1_ccqe         -> SetStats(0);
  h1_ccnonqe      -> SetStats(0);
  h1_ccresdeltap  -> SetStats(0);
  h1_ccresdeltapp -> SetStats(0);
  h1_ccresdelta0  -> SetStats(0);
  h1_nc           -> SetStats(0);

  h1_ccqe         -> SetLineColor(kAzure-1);
  h1_ccqe         -> SetFillColor(kAzure-1);
  h1_ccnonqe      -> SetLineColor(kOrange+8);
  h1_ccnonqe      -> SetFillColor(kOrange+8);
  h1_ccresdeltap  -> SetLineColor(kPink+1);
  h1_ccresdeltap  -> SetFillColor(kPink+1);
  h1_ccresdeltapp -> SetLineColor(kPink-8);
  h1_ccresdeltapp -> SetFillColor(kPink-8);
  h1_ccresdelta0  -> SetLineColor(kGray+1);
  h1_ccresdelta0  -> SetFillColor(kGray+1);
  h1_nc           -> SetLineColor(kTeal+9);
  h1_nc           -> SetFillColor(kTeal+9);


  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  ((TGaxis*)h1_ccqe->GetXaxis())->SetMaxDigits(3);
  //h1_ccqe -> SetTitleOffset(1.4, "Y");
  //h1_ccqe -> SetTitleSize(0.035, "Y");
  //h1_ccqe -> SetLabelSize(0.033, "Y");
  h1_ccqe         -> Draw();
  h1_ccnonqe      -> Draw("SAME");  
  h1_ccresdeltapp -> Draw("SAME");
  h1_ccresdelta0  -> Draw("SAME");
  h1_ccresdeltap  -> Draw("SAME");
  h1_nc           -> Draw("SAME");

  TLegend* legend = new TLegend(0.5, 0.45, 0.87, 0.85);
  legend -> SetTextSize(0.03);
  legend->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend->AddEntry((TObject*)0,"#kern[-0.3]{ #bar{#nu}_{#mu} Disappearance Mode }","");
  legend -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend -> AddEntry(h1_ccnonqe, "CC(2p2h+others)", "F");
  legend -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend -> AddEntry(h1_nc, "NC", "F");
  legend->SetFillColor(0);
  legend->Draw() ;

}