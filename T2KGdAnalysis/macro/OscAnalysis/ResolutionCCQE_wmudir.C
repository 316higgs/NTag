#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void ResolutionCCQE_wmudir() {

  TFile* fin1 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut1.root");
  TFile* fin6 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut6.root");

  TH1F* h1_EnuRecoReso1 = (TH1F*)fin1->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_EnuRecoReso6 = (TH1F*)fin6->Get("NeutrinoOscillation/h1_Enureso_mode0");

  TH1F* h1_EnuPredictReso1 = (TH1F*)fin1->Get("NeutrinoOscillation/h1_EnuResoPrediction");
  TH1F* h1_EnuPredictReso6 = (TH1F*)fin6->Get("NeutrinoOscillation/h1_EnuResoPrediction");

  h1_EnuRecoReso1 -> SetStats(0);
  h1_EnuPredictReso1 -> SetStats(0);

  h1_EnuRecoReso1 -> SetFillStyle(0);
  h1_EnuRecoReso6 -> SetFillStyle(0);

  //h1_EnuRecoReso1 -> SetLineStyle(3);
  //h1_EnuPredictReso1 -> SetLineStyle(3);

  h1_EnuRecoReso1 -> SetLineWidth(2);
  h1_EnuRecoReso6 -> SetLineWidth(2);
  h1_EnuPredictReso1 -> SetLineWidth(2);
  h1_EnuPredictReso6 -> SetLineWidth(2);

  h1_EnuRecoReso1 -> SetLineColor(kPink-2);
  h1_EnuRecoReso6 -> SetLineColor(kPink-2);
  h1_EnuPredictReso1 -> SetLineColor(kAzure-8);
  h1_EnuPredictReso6 -> SetLineColor(kAzure-8);
  
  Double_t totreco = h1_EnuRecoReso1->Integral();
  h1_EnuRecoReso1 -> Scale(1./totreco);
  Double_t totpredict = h1_EnuPredictReso1->Integral();
  h1_EnuPredictReso1 -> Scale(1./totpredict);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();

  h1_EnuPredictReso1 -> Draw();
  h1_EnuRecoReso1 -> Draw("SAME");
  //h1_EnuRecoReso6 -> Draw("SAME");
  //h1_EnuPredictReso6 -> Draw("SAME");

  /*hs_reso -> SetMaximum(9400);
  hs_reso -> Draw();
  hs_reso ->GetYaxis()->SetTitleSize(0.038);
  hs_reso ->GetYaxis()->SetTitleOffset(1.3);
  hs_reso ->GetYaxis()->SetLabelSize(0.036);
  hs_reso -> Draw();*/

  TLegend* legend0 = new TLegend(0.55, 0.65, 0.89, 0.85);
  legend0 -> SetTextSize(0.03);
  legend0->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend0->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend0 -> AddEntry(h1_EnuRecoReso1, "E_{#nu}^{CCQE reco}(-1#leq cos#theta_{#mu}#leq 1)", "L");
  legend0 -> AddEntry(h1_EnuPredictReso1, "E_{#nu}^{CCQE predict}(-1#leq cos#theta_{#mu}#leq 1)", "L");
  //legend0 -> AddEntry(h1_EnuRecoReso6, "E_{#nu}^{CCQE reco}(0.8#leq cos#theta_{#mu}#leq 1)", "L");
  //legend0 -> AddEntry(h1_EnuPredictReso6, "E_{#nu}^{CCQE predict}(0.8#leq cos#theta_{#mu}#leq 1)", "L");
  legend0 -> SetFillColor(0);
  legend0 -> Draw() ;

}