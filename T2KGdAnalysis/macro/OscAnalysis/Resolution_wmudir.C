#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Resolution_wmudir() {
  TFile* fin1 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut1.root");
  TFile* fin2 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut2.root");
  TFile* fin3 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut3.root");
  TFile* fin4 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut4.root");
  TFile* fin5 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut5.root");
  TFile* fin6 = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut6.root");
  //TFile* fin = new TFile("../../output/numubar.etagON.root");

  TH1F* h1_AllEnuReso1 = (TH1F*)fin1->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_AllEnuReso2 = (TH1F*)fin2->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_AllEnuReso3 = (TH1F*)fin3->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_AllEnuReso4 = (TH1F*)fin4->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_AllEnuReso5 = (TH1F*)fin5->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_AllEnuReso6 = (TH1F*)fin6->Get("NeutrinoOscillation/h1_AllEnureso");

  h1_AllEnuReso6 -> SetStats(0);

  h1_AllEnuReso1 -> SetLineWidth(2);
  h1_AllEnuReso2 -> SetLineWidth(2);
  h1_AllEnuReso3 -> SetLineWidth(2);
  h1_AllEnuReso4 -> SetLineWidth(2);
  h1_AllEnuReso5 -> SetLineWidth(2);
  h1_AllEnuReso6 -> SetLineWidth(2);

  h1_AllEnuReso1 -> SetLineColor(kRed-4);
  h1_AllEnuReso2 -> SetLineColor(kOrange-7);
  h1_AllEnuReso3 -> SetLineColor(kOrange+0);
  h1_AllEnuReso4 -> SetLineColor(kSpring-6);
  h1_AllEnuReso5 -> SetLineColor(kAzure-5);
  h1_AllEnuReso6 -> SetLineColor(kViolet-3);

  Double_t tot1 = h1_AllEnuReso1->Integral();
  h1_AllEnuReso1 -> Scale(1./tot1);
  Double_t tot2 = h1_AllEnuReso2->Integral();
  h1_AllEnuReso2 -> Scale(1./tot2);
  Double_t tot3 = h1_AllEnuReso3->Integral();
  h1_AllEnuReso3 -> Scale(1./tot3);
  Double_t tot4 = h1_AllEnuReso4->Integral();
  h1_AllEnuReso4 -> Scale(1./tot4);
  Double_t tot5 = h1_AllEnuReso5->Integral();
  h1_AllEnuReso5 -> Scale(1./tot5);
  Double_t tot6 = h1_AllEnuReso6->Integral();
  h1_AllEnuReso6 -> Scale(1./tot6);

  h1_AllEnuReso6->GetYaxis()->SetTitleOffset(1.3);
  h1_AllEnuReso6->SetYTitle("Area Normalized");

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_AllEnuReso6 -> Draw();
  h1_AllEnuReso5 -> Draw("SAME");
  h1_AllEnuReso4 -> Draw("SAME");
  h1_AllEnuReso3 -> Draw("SAME");
  h1_AllEnuReso2 -> Draw("SAME");
  h1_AllEnuReso1 -> Draw("SAME");

  /*hs_reso -> SetMaximum(9400);
  hs_reso -> Draw();
  hs_reso ->GetYaxis()->SetTitleSize(0.038);
  hs_reso ->GetYaxis()->SetTitleOffset(1.3);
  hs_reso ->GetYaxis()->SetLabelSize(0.036);
  hs_reso -> Draw();*/

  TLegend* legend0 = new TLegend(0.57, 0.45, 0.89, 0.85);
  legend0 -> SetTextSize(0.03);
  legend0->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend0->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend0 -> AddEntry(h1_AllEnuReso1, "-1#leq cos#theta_{#mu}#leq 1", "L");
  legend0 -> AddEntry(h1_AllEnuReso2, "0#leq cos#theta_{#mu}#leq 1", "L");
  legend0 -> AddEntry(h1_AllEnuReso3, "0.2#leq cos#theta_{#mu}#leq 1", "L");
  legend0 -> AddEntry(h1_AllEnuReso4, "0.4#leq cos#theta_{#mu}#leq 1", "L");
  legend0 -> AddEntry(h1_AllEnuReso5, "0.6#leq cos#theta_{#mu}#leq 1", "L");
  legend0 -> AddEntry(h1_AllEnuReso6, "0.8#leq cos#theta_{#mu}#leq 1", "L");
  legend0 -> SetFillColor(0);
  legend0 -> Draw() ;

}