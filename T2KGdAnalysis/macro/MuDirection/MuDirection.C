#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

void MuDirection() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.root");

  TH1F* h1_CCQEX         = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode0");
  TH1F* h1_CCnonQEX      = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode1");
  TH1F* h1_CCRESdeltapX  = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode3");
  TH1F* h1_CCRESdeltappX = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode4");
  TH1F* h1_CCRESdelta0X  = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode5");
  TH1F* h1_CCOtherX      = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode6");
  TH1F* h1_NCX           = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoX_mode2");
  h1_CCQEX -> SetStats(0);

  THStack* hs_RecoDirX = new THStack("hs_RecoDirX", "Reco. muon direction; d^{reco}_{#mu X}; Number of Neutrino Events");
  hs_RecoDirX -> Add(h1_NCX);
  hs_RecoDirX -> Add(h1_CCOtherX);
  hs_RecoDirX -> Add(h1_CCRESdelta0X);
  hs_RecoDirX -> Add(h1_CCRESdeltapX);
  hs_RecoDirX -> Add(h1_CCRESdeltappX);
  hs_RecoDirX -> Add(h1_CCnonQEX);
  hs_RecoDirX -> Add(h1_CCQEX);

  TCanvas* cX = new TCanvas("cX", "cX", 900, 900);
  cX -> SetGrid();
  hs_RecoDirX -> SetMaximum(4000);
  hs_RecoDirX -> Draw();
  hs_RecoDirX ->GetYaxis()->SetTitleSize(0.035);
  hs_RecoDirX ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoDirX ->GetYaxis()->SetLabelSize(0.033);
  hs_RecoDirX -> Draw();
  
  cX->RedrawAxis();

  TLegend* legend1 = new TLegend(0.15, 0.45, 0.55, 0.85);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend1 -> AddEntry(h1_CCQEX, "CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCnonQEX, "CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCRESdeltapX, "CCRES(#Delta^{+})", "F");
  legend1 -> AddEntry(h1_CCRESdeltappX, "CCRES(#Delta^{++})", "F");
  legend1 -> AddEntry(h1_CCRESdelta0X, "CCRES(#Delta^{0})", "F");
  legend1 -> AddEntry(h1_CCOtherX, "CC-other", "F");
  legend1 -> AddEntry(h1_NCX, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw();



  TH1F* h1_CCQEY         = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode0");
  TH1F* h1_CCnonQEY      = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode1");
  TH1F* h1_CCRESdeltapY  = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode3");
  TH1F* h1_CCRESdeltappY = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode4");
  TH1F* h1_CCRESdelta0Y  = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode5");
  TH1F* h1_CCOtherY      = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode6");
  TH1F* h1_NCY           = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoY_mode2");
  h1_CCQEY -> SetStats(0);

  THStack* hs_RecoDirY = new THStack("hs_RecoDirY", "Reco. muon direction; d^{reco}_{#mu Y}; Number of Neutrino Events");
  hs_RecoDirY -> Add(h1_NCY);
  hs_RecoDirY -> Add(h1_CCOtherY);
  hs_RecoDirY -> Add(h1_CCRESdelta0Y);
  hs_RecoDirY -> Add(h1_CCRESdeltapY);
  hs_RecoDirY -> Add(h1_CCRESdeltappY);
  hs_RecoDirY -> Add(h1_CCnonQEY);
  hs_RecoDirY -> Add(h1_CCQEY);

  TCanvas* cY = new TCanvas("cY", "cY", 900, 900);
  cY -> SetGrid();
  hs_RecoDirY -> SetMaximum(4000);
  hs_RecoDirY -> Draw();
  hs_RecoDirY ->GetYaxis()->SetTitleSize(0.035);
  hs_RecoDirY ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoDirY ->GetYaxis()->SetLabelSize(0.033);
  hs_RecoDirY -> Draw();
  
  cY->RedrawAxis();

  TLegend* legend2 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend2 -> SetTextSize(0.03);
  legend2->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend2 -> AddEntry(h1_CCQEX, "CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CCnonQEX, "CC-2p2h", "F");
  legend2 -> AddEntry(h1_CCRESdeltapX, "CCRES(#Delta^{+})", "F");
  legend2 -> AddEntry(h1_CCRESdeltappX, "CCRES(#Delta^{++})", "F");
  legend2 -> AddEntry(h1_CCRESdelta0X, "CCRES(#Delta^{0})", "F");
  legend2 -> AddEntry(h1_CCOtherX, "CC-other", "F");
  legend2 -> AddEntry(h1_NCX, "NC", "F");
  legend2->SetFillColor(0);
  legend2->Draw();


  TH1F* h1_CCQEZ         = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode0");
  TH1F* h1_CCnonQEZ      = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode1");
  TH1F* h1_CCRESdeltapZ  = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode3");
  TH1F* h1_CCRESdeltappZ = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode4");
  TH1F* h1_CCRESdelta0Z  = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode5");
  TH1F* h1_CCOtherZ      = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode6");
  TH1F* h1_NCZ           = (TH1F*)fin->Get("NeutrinoOscillation/h1_DirResoZ_mode2");
  h1_CCQEZ -> SetStats(0);

  THStack* hs_RecoDirZ = new THStack("hs_RecoDirZ", "Reco. muon direction; d^{reco}_{#mu Z}; Number of Neutrino Events");
  hs_RecoDirZ -> Add(h1_NCZ);
  hs_RecoDirZ -> Add(h1_CCOtherZ);
  hs_RecoDirZ -> Add(h1_CCRESdelta0Z);
  hs_RecoDirZ -> Add(h1_CCRESdeltapZ);
  hs_RecoDirZ -> Add(h1_CCRESdeltappZ);
  hs_RecoDirZ -> Add(h1_CCnonQEZ);
  hs_RecoDirZ -> Add(h1_CCQEZ);

  TCanvas* cZ = new TCanvas("cZ", "cZ", 900, 900);
  cZ -> SetGrid();
  hs_RecoDirZ -> SetMaximum(4000);
  hs_RecoDirZ -> Draw();
  hs_RecoDirZ ->GetYaxis()->SetTitleSize(0.035);
  hs_RecoDirZ ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoDirZ ->GetYaxis()->SetLabelSize(0.033);
  hs_RecoDirZ -> Draw();
  
  cZ->RedrawAxis();

  TLegend* legend3 = new TLegend(0.45, 0.52, 0.85, 0.88);
  legend3 -> SetTextSize(0.03);
  legend3->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend3 -> AddEntry(h1_CCQEX, "CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CCnonQEX, "CC-2p2h", "F");
  legend3 -> AddEntry(h1_CCRESdeltapX, "CCRES(#Delta^{+})", "F");
  legend3 -> AddEntry(h1_CCRESdeltappX, "CCRES(#Delta^{++})", "F");
  legend3 -> AddEntry(h1_CCRESdelta0X, "CCRES(#Delta^{0})", "F");
  legend3 -> AddEntry(h1_CCOtherX, "CC-other", "F");
  legend3 -> AddEntry(h1_NCX, "NC", "F");
  legend3->SetFillColor(0);
  legend3->Draw();
}