#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void SimpleResolution() {
  TFile* fin1 = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");

  TH1F* h1_AllEnuReso1 = (TH1F*)fin1->Get("NeutrinoOscillation/h1_AllEnureso");

  h1_AllEnuReso1 -> SetStats(0);

  h1_AllEnuReso1 -> SetLineWidth(2);

  h1_AllEnuReso1 -> SetLineColor(kRed-4);

  Double_t tot1 = h1_AllEnuReso1->Integral();
  h1_AllEnuReso1 -> Scale(1./tot1);

  h1_AllEnuReso1->GetYaxis()->SetTitleOffset(1.3);
  h1_AllEnuReso1->SetYTitle("Area Normalized");

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_AllEnuReso1 -> Draw();

  TLegend* legend0 = new TLegend(0.57, 0.75, 0.89, 0.85);
  legend0 -> SetTextSize(0.03);
  //legend0->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend0->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend0 -> SetFillColor(0);
  legend0 -> Draw() ;

}