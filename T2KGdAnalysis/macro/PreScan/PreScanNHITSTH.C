#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void PreScanNHITSTH() {
  TFile* fin120 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH10.root");
  TFile* fin160 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH15.root");
  TFile* fin200 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH35.root");
  TFile* fin280 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH45.root");

  float NHITSTH[5];
  float eNHITSTH[5];

  float PreEff[5];
  float PreHEff[5];
  float PreGdEff[5];
  float ePreEff[5];
  float ePreHEff[5];
  float ePreGdEff[5];
  for (int i=0; i<5; i++) {
    eNHITSTH[i]   = 0.;
    ePreEff[i]   = 0.;
    ePreHEff[i]  = 0.;
    ePreGdEff[i] = 0.;

    switch (i) {
      case 0:
        NHITSTH[i]  = 10;
        PreEff[i]   = 60.1157;
        PreHEff[i]  = 33.467;
        PreGdEff[i] = 92.6152;
        break;
      case 1:
        NHITSTH[i]  = 15;
        PreEff[i]   = 58.8382;
        PreHEff[i]  = 32.2373;
        PreGdEff[i] = 91.375;
        break;
      case 2:
        NHITSTH[i]  = 25;
        PreEff[i]   = 48.7288;
        PreHEff[i]  = 18.3119;
        PreGdEff[i] = 85.8249;
        break;
      case 3:
        NHITSTH[i]  = 35;
        PreEff[i]   = 33.6678;
        PreHEff[i]  = 1.92117;
        PreGdEff[i] = 72.3845;
        break;
      case 4:
        NHITSTH[i]  = 45;
        PreEff[i]   = 17.8791;
        PreHEff[i]  = 0.104068;
        PreGdEff[i] = 39.5568;
        break;
    }

    PreEff[i] /= 100.;
    PreHEff[i] /= 100.;
    PreGdEff[i] /= 100.;
  }
  TGraphErrors* g_NHITSTH_x_PreEff   = new TGraphErrors(5, NHITSTH, PreEff, eNHITSTH, ePreEff);
  TGraphErrors* g_NHITSTH_x_PreHEff  = new TGraphErrors(5, NHITSTH, PreHEff, eNHITSTH, ePreHEff);
  TGraphErrors* g_NHITSTH_x_PreGdEff = new TGraphErrors(5, NHITSTH, PreGdEff, eNHITSTH, ePreGdEff);

  g_NHITSTH_x_PreEff   -> SetMarkerColor(kPink-5);
  g_NHITSTH_x_PreEff   -> SetLineColor(kPink-5);
  g_NHITSTH_x_PreEff   -> SetMarkerStyle(20);
  g_NHITSTH_x_PreEff   -> SetMarkerSize(1.0);
  g_NHITSTH_x_PreHEff  -> SetMarkerColor(kAzure-4);
  g_NHITSTH_x_PreHEff  -> SetLineColor(kAzure-4);
  g_NHITSTH_x_PreHEff  -> SetMarkerStyle(20);
  g_NHITSTH_x_PreHEff  -> SetMarkerSize(1.0);
  g_NHITSTH_x_PreGdEff -> SetMarkerColor(kTeal-5);
  g_NHITSTH_x_PreGdEff -> SetLineColor(kTeal-5);
  g_NHITSTH_x_PreGdEff -> SetMarkerStyle(20);
  g_NHITSTH_x_PreGdEff -> SetMarkerSize(1.0);

  TCanvas* c = new TCanvas("c", "c", 800, 800);
  c -> cd();
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(5., 0., 50., 1.);
  frame -> SetXTitle("Threshold of Numbef of Hits");
  frame -> SetYTitle("Pre-selection Efficiency");
  frame -> SetTitleOffset(1.1, "Y");
  g_NHITSTH_x_PreEff   -> Draw("PL");
  g_NHITSTH_x_PreHEff  -> Draw("PL");
  g_NHITSTH_x_PreGdEff -> Draw("PL");
  c -> SaveAs("../../figure/PreScan/NHITSTH_x_PreEff.535us.pdf");


}