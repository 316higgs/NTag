#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void EnuResolution() {
  TFile* fin = new TFile("../../output/numu.etagON.root");

  TH1F* h1_ccqe          = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_ccqewTrueN    = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_wtrueNeutrons");
  TH1F* h1_ccqewoTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_wotrueNeutrons");
  TH1F* h1_ccqewneutron  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_wNeutrons");
  TH1F* h1_ccqewoneutron = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_woNeutrons");


  TH1F* h1_ccresdeltap   = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode3");
  TH1F* h1_ccresdeltapp  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode4");
  TH1F* h1_ccresdelta0   = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode5");
  TH1F* h1_ccresdeltapwTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_wtrueNeutrons");
  TH1F* h1_ccresdeltapwoTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_wotrueNeutrons");
  TH1F* h1_ccresdeltappwTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_wtrueNeutrons");
  TH1F* h1_ccresdeltappwoTrueN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_wotrueNeutrons");
  TH1F* h1_ccresdelta0wTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_wtrueNeutrons");
  TH1F* h1_ccresdelta0woTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_wotrueNeutrons");
  TH1F* h1_ccresdeltapwneutron   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_wNeutrons");
  TH1F* h1_ccresdeltapwoneutron  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_woNeutrons");
  TH1F* h1_ccresdeltappwneutron  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_wNeutrons");
  TH1F* h1_ccresdeltappwoneutron = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_woNeutrons");
  TH1F* h1_ccresdelta0wneutron   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_wNeutrons");
  TH1F* h1_ccresdelta0woneutron  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_woNeutrons");


  TH1F* h1_ccnonqe          = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode1");
  TH1F* h1_ccnonqewTrueN    = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_wtrueNeutrons");
  TH1F* h1_ccnonqewoTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_wotrueNeutrons");
  TH1F* h1_ccnonqewneutron  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_wNeutrons");
  TH1F* h1_ccnonqewoneutron = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_woNeutrons");


  TH1F* h1_nc          = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode2");
  TH1F* h1_ncwTrueN    = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_wtrueNeutrons");
  TH1F* h1_ncwoTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_wotrueNeutrons");
  TH1F* h1_ncwneutron  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_wNeutrons");
  TH1F* h1_ncwoneutron = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_woNeutrons");

  h1_ccqe         -> SetStats(0);
  h1_ccnonqe      -> SetStats(0);
  h1_ccresdeltap  -> SetStats(0);
  h1_ccresdeltapp -> SetStats(0);
  h1_ccresdelta0  -> SetStats(0);
  h1_nc           -> SetStats(0);

  h1_ccqe    -> SetLineWidth(2);
  h1_ccnonqe -> SetLineWidth(2);
  h1_nc      -> SetLineWidth(2);

  h1_ccqewneutron    -> SetStats(0);
  h1_ccnonqewneutron -> SetStats(0);
  h1_ccresdeltappwneutron -> SetStats(0);
  h1_ccresdeltapwneutron -> SetStats(0);
  h1_ccresdelta0wneutron -> SetStats(0);
  h1_ncwneutron      -> SetStats(0);

  h1_ccqewneutron    -> SetLineWidth(2);
  h1_ccnonqewneutron -> SetLineWidth(2);
  h1_ncwneutron      -> SetLineWidth(2);

  //---------------------------------------

  h1_ccqewTrueN          -> SetStats(0);
  h1_ccqewoTrueN         -> SetStats(0);
  h1_ccnonqewoTrueN      -> SetStats(0);
  h1_ccresdeltappwoTrueN -> SetStats(0);
  h1_ccresdeltapwoTrueN  -> SetStats(0);
  h1_ccresdelta0woTrueN  -> SetStats(0);
  h1_ncwoTrueN           -> SetStats(0);

  h1_ccqewoTrueN    -> SetLineWidth(2);
  h1_ccnonqewoTrueN -> SetLineWidth(2);
  h1_ncwoTrueN      -> SetLineWidth(2);

  h1_ccqewoTrueN         -> SetFillColor(kAzure-1);
  h1_ccresdeltappwoTrueN -> SetFillColor(kPink-8);
  h1_ccresdeltapwoTrueN  -> SetFillColor(kPink+1);
  h1_ccresdelta0woTrueN  -> SetFillColor(kGray+1);
  h1_ccnonqewoTrueN      -> SetFillColor(kOrange+8);
  h1_ncwoTrueN           -> SetFillColor(kTeal+9);

  h1_ccqewTrueN         -> SetFillColor(kAzure-1);
  h1_ccresdeltappwTrueN -> SetFillColor(kPink-8);
  h1_ccresdeltapwTrueN  -> SetFillColor(kPink+1);
  h1_ccresdelta0wTrueN  -> SetFillColor(kGray+1);
  h1_ccnonqewTrueN      -> SetFillColor(kOrange+8);
  h1_ncwTrueN           -> SetFillColor(kTeal+9);

  //---------------------------------------

  h1_ccqewoneutron         -> SetStats(0);
  h1_ccnonqewoneutron      -> SetStats(0);
  h1_ccresdeltappwoneutron -> SetStats(0);
  h1_ccresdeltapwoneutron  -> SetStats(0);
  h1_ccresdelta0woneutron  -> SetStats(0);
  h1_ncwoneutron           -> SetStats(0);

  h1_ccqewoneutron    -> SetLineWidth(2);
  h1_ccnonqewoneutron -> SetLineWidth(2);
  h1_ncwoneutron      -> SetLineWidth(2);

  h1_ccqewoneutron         -> SetFillColor(kAzure-1);
  h1_ccresdeltappwoneutron -> SetFillColor(kPink-8);
  h1_ccresdeltapwoneutron  -> SetFillColor(kPink+1);
  h1_ccresdelta0woneutron  -> SetFillColor(kGray+1);
  h1_ccnonqewoneutron      -> SetFillColor(kOrange+8);
  h1_ncwoneutron           -> SetFillColor(kTeal+9);

  h1_ccqewneutron         -> SetFillColor(kAzure-1);
  h1_ccresdeltappwneutron -> SetFillColor(kPink-8);
  h1_ccresdeltapwneutron  -> SetFillColor(kPink+1);
  h1_ccresdelta0wneutron  -> SetFillColor(kGray+1);
  h1_ccnonqewneutron      -> SetFillColor(kOrange+8);
  h1_ncwneutron           -> SetFillColor(kTeal+9);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_ccqe -> Draw();
  h1_ccqe -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqe      -> Draw("SAME");  
  ((TGaxis*)h1_ccnonqe->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqe -> SetTitleOffset(1.4, "Y");
  h1_ccnonqe -> SetTitleSize(0.035, "Y");
  h1_ccnonqe -> SetLabelSize(0.033, "Y");
  h1_ccresdeltapp -> Draw("SAME");
  h1_ccresdelta0  -> Draw("SAME");
  h1_ccresdeltap  -> Draw("SAME");
  h1_nc           -> Draw("SAME");

  TCanvas* c2 = new TCanvas("c2","w/ tagged neutrons",900,700);
  c2 -> SetGrid();
  h1_ccqewneutron -> Draw();
  h1_ccqewneutron -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqewneutron      -> Draw("SAME");
  ((TGaxis*)h1_ccnonqewneutron->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqewneutron -> SetTitleOffset(1.4, "Y");
  h1_ccnonqewneutron -> SetTitleSize(0.035, "Y");
  h1_ccnonqewneutron -> SetLabelSize(0.033, "Y");
  h1_ccresdeltappwneutron -> Draw("SAME");
  h1_ccresdelta0wneutron  -> Draw("SAME");
  h1_ccresdeltapwneutron  -> Draw("SAME");
  h1_ncwneutron           -> Draw("SAME");

  TCanvas* c3 = new TCanvas("c3","w/o tagged neutrons",900,700);
  c3 -> SetGrid();
  h1_ccqewoneutron -> Draw();
  h1_ccqewoneutron -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqewoneutron      -> Draw("SAME");
  ((TGaxis*)h1_ccnonqewoneutron->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqewoneutron -> SetTitleOffset(1.4, "Y");
  h1_ccnonqewoneutron -> SetTitleSize(0.035, "Y");
  h1_ccnonqewoneutron -> SetLabelSize(0.033, "Y");
  h1_ccresdeltappwoneutron -> Draw("SAME");
  h1_ccresdelta0woneutron  -> Draw("SAME");
  h1_ccresdeltapwoneutron  -> Draw("SAME");
  h1_ncwoneutron           -> Draw("SAME");


  TCanvas* c4 = new TCanvas("c4","w/ truth neutrons",900,700);
  c4 -> SetGrid();
  h1_ccqewTrueN -> Draw();
  h1_ccqewTrueN -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqewTrueN -> Draw("SAME");
  ((TGaxis*)h1_ccnonqewTrueN->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqewTrueN -> SetTitleOffset(1.4, "Y");
  h1_ccnonqewTrueN -> SetTitleSize(0.035, "Y");
  h1_ccnonqewTrueN -> SetLabelSize(0.033, "Y");
  h1_ccresdeltappwTrueN -> Draw("SAME");
  h1_ccresdelta0wTrueN  -> Draw("SAME");
  h1_ccresdeltapwTrueN  -> Draw("SAME");
  h1_ncwTrueN           -> Draw("SAME");

  TCanvas* c5 = new TCanvas("c5","w/o truth neutrons",900,700);
  c5 -> SetGrid();
  h1_ccqewoTrueN -> Draw();
  h1_ccqewoTrueN -> GetYaxis() -> SetRangeUser(0, 17500);
  h1_ccnonqewoTrueN -> Draw("SAME");
  ((TGaxis*)h1_ccnonqewoTrueN->GetXaxis())->SetMaxDigits(3);
  h1_ccnonqewoTrueN -> SetTitleOffset(1.4, "Y");
  h1_ccnonqewoTrueN -> SetTitleSize(0.035, "Y");
  h1_ccnonqewoTrueN -> SetLabelSize(0.033, "Y");
  h1_ccresdeltappwoTrueN -> Draw("SAME");
  h1_ccresdelta0woTrueN  -> Draw("SAME");
  h1_ccresdeltapwoTrueN  -> Draw("SAME");
  h1_ncwoTrueN           -> Draw("SAME");

}