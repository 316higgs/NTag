#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void MuDirection() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.root");

  TH2F* h2_TrueMuDirectionXY = (TH2F*)fin->Get("NeutrinoOscillation/h2_TrueMuDirectionXY");
  TH2F* h2_TrueMuDirectionRZ = (TH2F*)fin->Get("NeutrinoOscillation/h2_TrueMuDirectionRZ");
    
  TH2F* h2_RecoMuDirectionXY = (TH2F*)fin->Get("NeutrinoOscillation/h2_RecoMuDirectionXY");
  TH2F* h2_RecoMuDirectionRZ = (TH2F*)fin->Get("NeutrinoOscillation/h2_RecoMuDirectionRZ");

  TH1F* h1_DirResoX = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX");
  TH1F* h1_DirResoY = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY");
  TH1F* h1_DirResoZ = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ");
  h1_DirResoX -> SetLineColor(kPink-5);
  h1_DirResoZ -> SetLineColor(kSpring-1);
  h1_DirResoX -> SetStats(0);
  h1_DirResoY -> SetStats(0);
  h1_DirResoZ -> SetStats(0);


  gROOT -> SetStyle("Plain");
  //gStyle->SetPalette(kCandy);
  //TColor::InvertPalette();
    
  h2_TrueMuDirectionXY->SetContour(99);
  h2_TrueMuDirectionRZ->SetContour(99);
  h2_RecoMuDirectionXY->SetContour(99);
  h2_RecoMuDirectionRZ->SetContour(99);
    
  /*TCanvas* c1 = new TCanvas("c1","c1",900,900);
  c1 -> SetGrid();
  h2_TrueMuDirectionXY -> Draw("COLZ");

  TCanvas* c2 = new TCanvas("c2","c2",900,900);
  c2 -> SetGrid();
  h2_TrueMuDirectionRZ -> Draw("COLZ");

  TCanvas* c3 = new TCanvas("c3","c3",900,900);
  c3 -> SetGrid();
  h2_RecoMuDirectionXY -> Draw("COLZ");

  TCanvas* c4 = new TCanvas("c4","c4",900,900);
  c4 -> SetGrid();
  h2_RecoMuDirectionRZ -> Draw("COLZ");*/

  TCanvas* c5 = new TCanvas("c5", "c5", 900, 900);
  c5 -> SetGrid();
  h1_DirResoY -> SetXTitle("(d^{true}-d^{reco})/d^{true}");
  ((TGaxis*)h1_DirResoY->GetYaxis())->SetMaxDigits(4);
  h1_DirResoY -> Draw();
  h1_DirResoX -> Draw("SAME");
  h1_DirResoZ -> Draw("SAME");

  /*TF1* f = new TF1("f", "[0]*exp(-(x-[1])**2/(2*[2]**2))", -1, 1);
  f -> SetParameter(0, 100000);
  f -> SetParameter(1, 5);
  f -> SetParameter(2, 50);
  h1_DirResoX -> Fit("gaus", "", "", -0.6, 0.6);*/

  TLegend* legend1 = new TLegend(0.55, 0.55, 0.87, 0.75);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend1 -> AddEntry(h1_DirResoX, "X-direction", "L");
  legend1 -> AddEntry(h1_DirResoY, "Y-direction", "L");
  legend1 -> AddEntry(h1_DirResoZ, "Z-direction", "L");
  legend1->SetFillColor(0);
  legend1->Draw();

}
