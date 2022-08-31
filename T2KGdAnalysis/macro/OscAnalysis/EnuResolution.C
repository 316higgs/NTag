#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void EnuResolution() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  //TFile* fin = new TFile("../../output/numubar.etagON.root");

  //CCQE(1p1h)
  TH1F* h1_ccqe        = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_ccqewTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_wTrueN");
  TH1F* h1_ccqewoTrueN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_woTrueN");
  TH1F* h1_ccqewTagN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_wTagN");
  TH1F* h1_ccqewoTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCQE_woTagN");

  //CC-RES
  TH1F* h1_ccresdeltap   = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode3");
  TH1F* h1_ccresdeltapp  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode4");
  TH1F* h1_ccresdelta0   = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode5");
  TH1F* h1_ccresdeltapwTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_wTrueN");
  TH1F* h1_ccresdeltapwoTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_woTrueN");
  TH1F* h1_ccresdeltappwTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_wTrueN");
  TH1F* h1_ccresdeltappwoTrueN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_woTrueN");
  TH1F* h1_ccresdelta0wTrueN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_wTrueN");
  TH1F* h1_ccresdelta0woTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_woTrueN");
  TH1F* h1_ccresdeltapwTagN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_wTagN");
  TH1F* h1_ccresdeltapwoTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltap_woTagN");
  TH1F* h1_ccresdeltappwTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_wTagN");
  TH1F* h1_ccresdeltappwoTagN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdeltapp_woTagN");
  TH1F* h1_ccresdelta0wTagN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_wTagN");
  TH1F* h1_ccresdelta0woTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCRESdelta0_woTagN");

  //CC-2p2h
  TH1F* h1_ccnonqe        = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode1");
  TH1F* h1_ccnonqewTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_wTrueN");
  TH1F* h1_ccnonqewoTrueN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_woTrueN");
  TH1F* h1_ccnonqewTagN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_wTagN");
  TH1F* h1_ccnonqewoTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCnonQE_woTagN");

  //CC-other
  TH1F* h1_ccother        = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode6");
  TH1F* h1_ccotherwTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCOther_wTrueN");
  TH1F* h1_ccotherwoTrueN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCOther_woTrueN");
  TH1F* h1_ccotherwTagN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCOther_wTagN");
  TH1F* h1_ccotherwoTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_CCOther_woTagN");

  //NC
  TH1F* h1_nc        = (TH1F*)fin->Get("NeutrinoOscillation/h1_Enureso_mode2");
  TH1F* h1_ncwTrueN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_wTrueN");
  TH1F* h1_ncwoTrueN = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_woTrueN");
  TH1F* h1_ncwTagN   = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_wTagN");
  TH1F* h1_ncwoTagN  = (TH1F*)fin->Get("NTagAnalysis/h1_Enureso_NC_woTagN");


  h1_ccqe         -> SetStats(0);
  h1_ccnonqe      -> SetStats(0);
  h1_ccother      -> SetStats(0);
  h1_ccresdeltap  -> SetStats(0);
  h1_ccresdeltapp -> SetStats(0);
  h1_ccresdelta0  -> SetStats(0);
  h1_nc           -> SetStats(0);

  h1_ccqe    -> SetLineWidth(2);
  h1_ccnonqe -> SetLineWidth(2);
  h1_nc      -> SetLineWidth(2);

  THStack* hs_reso = new THStack("hs_reso", "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events");
  hs_reso -> Add(h1_nc);
  hs_reso -> Add(h1_ccother);
  hs_reso -> Add(h1_ccresdelta0);
  hs_reso -> Add(h1_ccresdeltap);
  hs_reso -> Add(h1_ccresdeltapp);
  hs_reso -> Add(h1_ccnonqe);
  hs_reso -> Add(h1_ccqe);

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

  THStack* hs_resowTrueN = new THStack("hs_resowTrueN", "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events");
  hs_resowTrueN -> Add(h1_ncwTrueN);
  hs_resowTrueN -> Add(h1_ccotherwTrueN);
  hs_resowTrueN -> Add(h1_ccresdelta0wTrueN);
  hs_resowTrueN -> Add(h1_ccresdeltapwTrueN);
  hs_resowTrueN -> Add(h1_ccresdeltappwTrueN);
  hs_resowTrueN -> Add(h1_ccnonqewTrueN);
  hs_resowTrueN -> Add(h1_ccqewTrueN);

  THStack* hs_resowoTrueN = new THStack("hs_resowoTrueN", "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events");
  hs_resowoTrueN -> Add(h1_ncwoTrueN);
  hs_resowoTrueN -> Add(h1_ccotherwoTrueN);
  hs_resowoTrueN -> Add(h1_ccresdelta0woTrueN);
  hs_resowoTrueN -> Add(h1_ccresdeltapwoTrueN);
  hs_resowoTrueN -> Add(h1_ccresdeltappwoTrueN);
  hs_resowoTrueN -> Add(h1_ccnonqewoTrueN);
  hs_resowoTrueN -> Add(h1_ccqewoTrueN);

  //---------------------------------------

  h1_ccqewTagN    -> SetStats(0);
  h1_ccnonqewTagN -> SetStats(0);
  h1_ccresdeltappwTagN -> SetStats(0);
  h1_ccresdeltapwTagN -> SetStats(0);
  h1_ccresdelta0wTagN -> SetStats(0);
  h1_ncwTagN      -> SetStats(0);

  h1_ccqewTagN    -> SetLineWidth(2);
  h1_ccnonqewTagN -> SetLineWidth(2);
  h1_ncwTagN      -> SetLineWidth(2);

  h1_ccqewoTagN         -> SetStats(0);
  h1_ccnonqewoTagN      -> SetStats(0);
  h1_ccresdeltappwoTagN -> SetStats(0);
  h1_ccresdeltapwoTagN  -> SetStats(0);
  h1_ccresdelta0woTagN  -> SetStats(0);
  h1_ncwoTagN           -> SetStats(0);

  h1_ccqewoTagN    -> SetLineWidth(2);
  h1_ccnonqewoTagN -> SetLineWidth(2);
  h1_ncwoTagN      -> SetLineWidth(2);

  THStack* hs_resowTagN = new THStack("hs_resowTagN", "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events");
  hs_resowTagN -> Add(h1_ncwTagN);
  hs_resowTagN -> Add(h1_ccotherwTagN);
  hs_resowTagN -> Add(h1_ccresdelta0wTagN);
  hs_resowTagN -> Add(h1_ccresdeltapwTagN);
  hs_resowTagN -> Add(h1_ccresdeltappwTagN);
  hs_resowTagN -> Add(h1_ccnonqewTagN);
  hs_resowTagN -> Add(h1_ccqewTagN);

  THStack* hs_resowoTagN = new THStack("hs_resowoTagN", "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events");
  hs_resowoTagN -> Add(h1_ncwoTagN);
  hs_resowoTagN -> Add(h1_ccotherwoTagN);
  hs_resowoTagN -> Add(h1_ccresdelta0woTagN);
  hs_resowoTagN -> Add(h1_ccresdeltapwoTagN);
  hs_resowoTagN -> Add(h1_ccresdeltappwoTagN);
  hs_resowoTagN -> Add(h1_ccnonqewoTagN);
  hs_resowoTagN -> Add(h1_ccqewoTagN);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  hs_reso -> SetMaximum(9400);
  hs_reso -> Draw();
  hs_reso ->GetYaxis()->SetTitleSize(0.038);
  hs_reso ->GetYaxis()->SetTitleOffset(1.3);
  hs_reso ->GetYaxis()->SetLabelSize(0.036);
  hs_reso -> Draw();

  TLegend* legend0 = new TLegend(0.57, 0.45, 0.89, 0.85);
  legend0 -> SetTextSize(0.03);
  legend0->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend0->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend0 -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend0 -> AddEntry(h1_ccnonqe, "CC-2p2h", "F");
  legend0 -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend0 -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend0 -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend0 -> AddEntry(h1_ccother, "CC-other", "F");
  legend0 -> AddEntry(h1_nc, "NC", "F");
  legend0 -> SetFillColor(0);
  legend0 -> Draw() ;

  
  
  TCanvas* c2 = new TCanvas("c2","w/ tagged neutrons",900,700);
  c2 -> SetGrid();
  hs_resowTagN -> SetMaximum(9400);
  hs_resowTagN -> Draw();
  hs_resowTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_resowTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_resowTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_resowTagN -> Draw();

  TLegend* legend1 = new TLegend(0.55, 0.42, 0.89, 0.85);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.35]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.35]{ (w/ tagged neutrons)}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend1 -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_ccnonqe, "CC-2p2h", "F");
  legend1 -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend1 -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend1 -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend1 -> AddEntry(h1_ccother, "CC-other", "F");
  legend1 -> AddEntry(h1_nc, "NC", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw() ;


  TCanvas* c3 = new TCanvas("c3","w/o tagged neutrons",900,700);
  c3 -> SetGrid();
  hs_resowoTagN -> SetMaximum(9400);
  hs_resowoTagN -> Draw();
  hs_resowoTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_resowoTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_resowoTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_resowoTagN -> Draw();

  TLegend* legend2 = new TLegend(0.55, 0.42, 0.89, 0.85);
  legend2 -> SetTextSize(0.03);
  legend2->AddEntry((TObject*)0,"#kern[-0.35]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC}","");
  legend2->AddEntry((TObject*)0,"#kern[-0.35]{ (w/o tagged neutrons)}","");
  //legend2->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend2 -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_ccnonqe, "CC-2p2h", "F");
  legend2 -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend2 -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend2 -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend0 -> AddEntry(h1_ccother, "CC-other", "F");
  legend2 -> AddEntry(h1_nc, "NC", "F");
  legend2 -> SetFillColor(0);
  legend2 -> Draw() ;


  TCanvas* c4 = new TCanvas("c4","w/ truth neutrons",900,700);
  c4 -> SetGrid();
  hs_resowTrueN -> SetMaximum(9400);
  hs_resowTrueN -> Draw();
  hs_resowTrueN ->GetYaxis()->SetTitleSize(0.038);
  hs_resowTrueN ->GetYaxis()->SetTitleOffset(1.3);
  hs_resowTrueN ->GetYaxis()->SetLabelSize(0.036);
  hs_resowTrueN -> Draw();

  TLegend* legend3 = new TLegend(0.55, 0.42, 0.89, 0.85);
  legend3 -> SetTextSize(0.03);
  legend3->AddEntry((TObject*)0,"#kern[-0.35]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC}","");
  legend3->AddEntry((TObject*)0,"#kern[-0.35]{ (w/ truth neutrons)}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend3 -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_ccnonqe, "CC-2p2h", "F");
  legend3 -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend3 -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend3 -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend3 -> AddEntry(h1_ccother, "CC-other", "F");
  legend3 -> AddEntry(h1_nc, "NC", "F");
  legend3 -> SetFillColor(0);
  legend3 -> Draw() ;


  TCanvas* c5 = new TCanvas("c5","w/o truth neutrons",900,700);
  c5 -> SetGrid();
  hs_resowoTrueN -> SetMaximum(9400);
  hs_resowoTrueN -> Draw();
  hs_resowoTrueN ->GetYaxis()->SetTitleSize(0.038);
  hs_resowoTrueN ->GetYaxis()->SetTitleOffset(1.3);
  hs_resowoTrueN ->GetYaxis()->SetLabelSize(0.036);
  hs_resowoTrueN -> Draw();

  TLegend* legend4 = new TLegend(0.55, 0.42, 0.89, 0.85);
  legend4 -> SetTextSize(0.03);
  legend4 -> AddEntry((TObject*)0,"#kern[-0.35]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC}","");
  legend4 -> AddEntry((TObject*)0,"#kern[-0.35]{ (w/o truth neutrons)}","");
  //legend4->AddEntry((TObject*)0,"#kern[-0.5]{ #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} Mode }","");
  legend4 -> AddEntry(h1_ccqe, "CCQE(1p1h)", "F");
  legend4 -> AddEntry(h1_ccnonqe, "CC-2p2h", "F");
  legend4 -> AddEntry(h1_ccresdeltap, "CCRES(#Delta^{+})", "F");
  legend4 -> AddEntry(h1_ccresdeltapp, "CCRES(#Delta^{++})", "F");
  legend4 -> AddEntry(h1_ccresdelta0, "CCRES(#Delta^{0})", "F");
  legend4 -> AddEntry(h1_ccother, "CC-other", "F");
  legend4 -> AddEntry(h1_nc, "NC", "F");
  legend4 -> SetFillColor(0);
  legend4 -> Draw() ;
  

}