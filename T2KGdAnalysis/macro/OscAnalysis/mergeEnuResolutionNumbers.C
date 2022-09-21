#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

void mergeEnuResolutionNumbers() {
  //FHC
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");

  //RHC
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  //TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");

  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral();
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral();
  Double_t GenN_numu_x_numu         = 190292;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


  TH1F* h1_All_numu     = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_EnuresoCCnonQE");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_Enureso_mode2");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_All_numubar     = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_EnuresoCCnonQE");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_Enureso_mode2");
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_All = new TH1F("h1_All", "h1_All", 50, -0.8, 0.8);
  h1_All -> Add(h1_All_numu, h1_All_numubar, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "All RMS = " << h1_All->GetRMS() << std::endl;

  TH1F* h1_CCQE = new TH1F("h1_CCQE", "h1_CCQE", 60, -1, 1);
  h1_CCQE -> Add(h1_CCQE_numu, h1_CCQE_numubar, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCQE RMS = " << h1_CCQE->GetRMS() << std::endl;

  TH1F* h1_CCnonQE = new TH1F("h1_CCnonQE", "h1_CCnonQE", 60, -1, 1);
  h1_CCnonQE -> Add(h1_CCnonQE_numu, h1_CCnonQE_numubar, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCnonQE RMS = " << h1_CCnonQE->GetRMS() << std::endl;
  std::cout << " " << std::endl;


  std::cout << "w/ tagged neutrons" << std::endl;
  //===== w/ tagged neutrons ======
  TH1F* h1_All_numu_wTagN     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_All_wTagN");
  TH1F* h1_CCQE_numu_wTagN    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCQE_wTagN");
  TH1F* h1_CCnonQE_numu_wTagN = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCnonQE_wTagN");
  TH1F* h1_NC_numu_wTagN      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_NC_wTagN");
  h1_CCQE_numu_wTagN -> SetStats(0);

  TH1F* h1_All_numubar_wTagN     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_All_wTagN");
  TH1F* h1_CCQE_numubar_wTagN    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCQE_wTagN");
  TH1F* h1_CCnonQE_numubar_wTagN = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCnonQE_wTagN");
  TH1F* h1_NC_numubar_wTagN      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_NC_wTagN");
  h1_CCQE_numubar_wTagN -> SetStats(0);

  TH1F* h1_All_wTagN = new TH1F("h1_All_wTagN", "h1_All", 60, -1, 1);
  h1_All_wTagN -> Add(h1_All_numu_wTagN, h1_All_numubar_wTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "All RMS = " << h1_All_wTagN->GetRMS() << std::endl;

  TH1F* h1_CCQE_wTagN = new TH1F("h1_CCQE_wTagN", "h1_CCQE", 60, -1, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_numu_wTagN, h1_CCQE_numubar_wTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCQE RMS = " << h1_CCQE_wTagN->GetRMS() << std::endl;

  TH1F* h1_CCnonQE_wTagN = new TH1F("h1_CCnonQE_wTagN", "h1_CCnonQE", 60, -1, 1);
  h1_CCnonQE_wTagN -> Add(h1_CCnonQE_numu_wTagN, h1_CCnonQE_numubar_wTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCnonQE RMS = " << h1_CCnonQE_wTagN->GetRMS() << std::endl;
  std::cout << " " << std::endl;


  std::cout << "w/o tagged neutrons" << std::endl;
  //===== w/o tagged neutrons ======
  TH1F* h1_All_numu_woTagN     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_All_woTagN");
  TH1F* h1_CCQE_numu_woTagN    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCQE_woTagN");
  TH1F* h1_CCnonQE_numu_woTagN = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCnonQE_woTagN");
  TH1F* h1_NC_numu_woTagN      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_NC_woTagN");

  TH1F* h1_All_numubar_woTagN     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_All_woTagN");
  TH1F* h1_CCQE_numubar_woTagN    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCQE_woTagN");
  TH1F* h1_CCnonQE_numubar_woTagN = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCnonQE_woTagN");
  TH1F* h1_NC_numubar_woTagN      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_NC_woTagN");

  TH1F* h1_All_woTagN = new TH1F("h1_All_woTagN", "h1_All", 60, -1, 1);
  h1_All_woTagN -> Add(h1_All_numu_woTagN, h1_All_numubar_woTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "All RMS = " << h1_All_woTagN->GetRMS() << std::endl;

  TH1F* h1_CCQE_woTagN = new TH1F("h1_CCQE_woTagN", "h1_CCQE", 60, -1, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_numu_woTagN, h1_CCQE_numubar_woTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCQE RMS = " << h1_CCQE_woTagN->GetRMS() << std::endl;

  TH1F* h1_CCnonQE_woTagN = new TH1F("h1_CCnonQE_woTagN", "h1_CCnonQE", 60, -1, 1);
  h1_CCnonQE_woTagN -> Add(h1_CCnonQE_numu_woTagN, h1_CCnonQE_numubar_woTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCnonQE RMS = " << h1_CCnonQE_woTagN->GetRMS() << std::endl;

}