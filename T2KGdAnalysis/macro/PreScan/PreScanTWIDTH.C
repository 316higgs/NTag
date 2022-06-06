#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void PreScanTWIDTH() {
  TFile* fin120 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH120.NHITSTH25.root");
  TFile* fin160 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH160.NHITSTH25.root");
  TFile* fin200 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH240.NHITSTH25.root");
  TFile* fin280 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH280.NHITSTH25.root");

  float TWIDTH[5];
  float eTWIDTH[5];

  float PreEff[5];
  float PreHEff[5];
  float PreGdEff[5];
  float ePreEff[5];
  float ePreHEff[5];
  float ePreGdEff[5];
  for (int i=0; i<5; i++) {
    eTWIDTH[i]   = 0.;
    ePreEff[i]   = 0.;
    ePreHEff[i]  = 0.;
    ePreGdEff[i] = 0.;

    switch (i) {
      case 0:
        TWIDTH[i]   = 120;
        PreEff[i]   = 38.119;
        PreHEff[i]  = 3.21794;
        PreGdEff[i] = 80.6826;
        break;
      case 1:
        TWIDTH[i]   = 160;
        PreEff[i]   = 44.9246;
        PreHEff[i]  = 10.5496;
        PreGdEff[i] = 86.8477;
        break;
      case 2:
        TWIDTH[i]   = 200;
        PreEff[i]   = 48.7288;
        PreHEff[i]  = 18.3119;
        PreGdEff[i] = 85.8249;
        break;
      case 3:
        TWIDTH[i]   = 240;
        PreEff[i]   = 49.9128;
        PreHEff[i]  = 22.949;
        PreGdEff[i] = 82.7974;
        break;
      case 4:
        TWIDTH[i]   = 280;
        PreEff[i]   = 53.2523;
        PreHEff[i]  = 26.4547;
        PreGdEff[i] = 85.9335;
        break;
    }

    PreEff[i] /= 100.;
    PreHEff[i] /= 100.;
    PreGdEff[i] /= 100.;
  }
  TGraphErrors* g_TWIDTH_x_PreEff   = new TGraphErrors(5, TWIDTH, PreEff, eTWIDTH, ePreEff);
  TGraphErrors* g_TWIDTH_x_PreHEff  = new TGraphErrors(5, TWIDTH, PreHEff, eTWIDTH, ePreHEff);
  TGraphErrors* g_TWIDTH_x_PreGdEff = new TGraphErrors(5, TWIDTH, PreGdEff, eTWIDTH, ePreGdEff);

  g_TWIDTH_x_PreEff   -> SetMarkerColor(kPink-5);
  g_TWIDTH_x_PreEff   -> SetLineColor(kPink-5);
  g_TWIDTH_x_PreEff   -> SetMarkerStyle(20);
  g_TWIDTH_x_PreEff   -> SetMarkerSize(1.0);
  g_TWIDTH_x_PreHEff  -> SetMarkerColor(kAzure-4);
  g_TWIDTH_x_PreHEff  -> SetLineColor(kAzure-4);
  g_TWIDTH_x_PreHEff  -> SetMarkerStyle(20);
  g_TWIDTH_x_PreHEff  -> SetMarkerSize(1.0);
  g_TWIDTH_x_PreGdEff -> SetMarkerColor(kTeal-5);
  g_TWIDTH_x_PreGdEff -> SetLineColor(kTeal-5);
  g_TWIDTH_x_PreGdEff -> SetMarkerStyle(20);
  g_TWIDTH_x_PreGdEff -> SetMarkerSize(1.0);

  TCanvas* c = new TCanvas("c", "c", 800, 800);
  c -> cd();
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(110., 0., 290., 1.);
  frame -> SetXTitle("Time Width of Hit Cluster Search[nsec]");
  frame -> SetYTitle("Pre-selection Efficiency");
  frame -> SetTitleOffset(1.1, "Y");
  g_TWIDTH_x_PreEff   -> Draw("PL");
  g_TWIDTH_x_PreHEff  -> Draw("PL");
  g_TWIDTH_x_PreGdEff -> Draw("PL");
  c -> SaveAs("../figure/PreScan/TWIDTH_x_PreEff.535us.pdf");


}