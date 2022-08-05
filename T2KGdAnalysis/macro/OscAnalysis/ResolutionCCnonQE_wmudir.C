#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void ResolutionCCnonQE_wmudir() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut6.root");

  TH1F* h1_EnuReso1 = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode1");
  TH1F* h1_EnuReso2 = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode3");
  TH1F* h1_EnuReso3 = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode4");
  TH1F* h1_EnuReso4 = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode5");
  TH1F* h1_EnuReso5 = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode6");

  h1_EnuReso1 -> Add(h1_EnuReso2);
  h1_EnuReso1 -> Add(h1_EnuReso3);
  h1_EnuReso1 -> Add(h1_EnuReso4);
  h1_EnuReso1 -> Add(h1_EnuReso5);

  std::cout << h1_EnuReso1 -> GetRMS() << std::endl;

  /*gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_EnuReso1 -> Draw();*/

}