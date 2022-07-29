#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

void EnuOscillation() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.cut1.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.0.511.root");
  //TFile* fin = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.noinpmt.root");

  TH1F* h1_trueCCQE         = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode0");
  TH1F* h1_trueCCnonQE      = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode1");
  TH1F* h1_trueCCRESdeltap  = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode3");
  TH1F* h1_trueCCRESdeltapp = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode4");
  TH1F* h1_trueCCRESdelta0  = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode5");
  TH1F* h1_trueCCOther      = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode6");
  TH1F* h1_trueNC           = (TH1F*)fin->Get("NeutrinoOscillation/h1_TruthOscProb_mode2");
  h1_trueCCQE -> SetStats(0);
  h1_trueCCQE         -> SetFillColor(kAzure-1);
  h1_trueCCnonQE      -> SetFillColor(kAzure-5);
  h1_trueCCRESdeltap  -> SetFillColor(kPink+1);
  h1_trueCCRESdeltapp -> SetFillColor(kPink-8);
  h1_trueCCRESdelta0  -> SetFillColor(kGray+1);
  h1_trueCCOther      -> SetFillColor(kCyan-6);
  h1_trueNC           -> SetFillColor(kTeal+9);

  THStack* hs_trueOsc = new THStack("hs_trueOsc", "Neutrino Oscillation for Truth; Truth Neutrino Energy E_{#nu}; Number of Neutrino Events");
  hs_trueOsc -> Add(h1_trueNC);
  hs_trueOsc -> Add(h1_trueCCOther);
  hs_trueOsc -> Add(h1_trueCCRESdelta0);
  hs_trueOsc -> Add(h1_trueCCRESdeltap);
  hs_trueOsc -> Add(h1_trueCCRESdeltapp);
  hs_trueOsc -> Add(h1_trueCCnonQE);
  hs_trueOsc -> Add(h1_trueCCQE);


  TH1F* h1_RecoEnu = (TH1F*)fin->Get("NeutrinoOscillation/h1_AllEnureco");
  h1_RecoEnu -> SetStats(0);
  h1_RecoEnu -> SetLineWidth(3);
  h1_RecoEnu -> SetLineColor(kViolet+3);


  TH1F* h1_CCQE         = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CCnonQE      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCRESdeltap  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode3");
  TH1F* h1_CCRESdeltapp = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode4");
  TH1F* h1_CCRESdelta0  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode5");
  TH1F* h1_CCOther      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode6");
  TH1F* h1_NC           = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE -> SetStats(0);

  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "Neutrino Oscillation for Reco; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
  hs_RecoOsc -> Add(h1_NC);
  hs_RecoOsc -> Add(h1_CCOther);
  hs_RecoOsc -> Add(h1_CCRESdelta0);
  hs_RecoOsc -> Add(h1_CCRESdeltap);
  hs_RecoOsc -> Add(h1_CCRESdeltapp);
  hs_RecoOsc -> Add(h1_CCnonQE);
  hs_RecoOsc -> Add(h1_CCQE);


  TH1F* h1_CCQE_wTagN         = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CCnonQE_wTagN      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCRESdeltap_wTagN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode3");
  TH1F* h1_CCRESdeltapp_wTagN = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode4");
  TH1F* h1_CCRESdelta0_wTagN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode5");
  TH1F* h1_CCOther_wTagN      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode6");
  TH1F* h1_NC_wTagN           = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_wTagN -> SetStats(0);

  THStack* hs_RecoOsc_wTagN = new THStack("hs_RecoOsc_wTagN", "Neutrino Oscillation for Reco w/ tagged neutrons; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
  hs_RecoOsc_wTagN -> Add(h1_NC_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCRESdelta0_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCRESdeltap_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCRESdeltapp_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCnonQE_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_wTagN);


  TH1F* h1_CCQE_woTagN         = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CCnonQE_woTagN      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCRESdeltap_woTagN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode3");
  TH1F* h1_CCRESdeltapp_woTagN = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode4");
  TH1F* h1_CCRESdelta0_woTagN  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode5");
  TH1F* h1_CCOther_woTagN      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode6");
  TH1F* h1_NC_woTagN           = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_woTagN -> SetStats(0);

  THStack* hs_RecoOsc_woTagN = new THStack("hs_RecoOsc_woTagN", "Neutrino Oscillation for Reco w/o tagged neutrons; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
  hs_RecoOsc_woTagN -> Add(h1_NC_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCRESdelta0_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCRESdeltap_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCRESdeltapp_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCnonQE_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_woTagN);


  gROOT -> SetStyle("Plain");

  
  TCanvas* c0 = new TCanvas("c0","c0",900,700);
  c0 -> SetGrid();
  hs_trueOsc -> Draw();
  hs_trueOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_trueOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_trueOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_trueOsc -> Draw();
  c0->RedrawAxis();

  TLegend* legend0 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend0 -> SetTextSize(0.03);
  legend0->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend0->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend0 -> AddEntry(h1_trueCCQE, "CCQE(1p1h)", "F");
  legend0 -> AddEntry(h1_trueCCnonQE, "CC-2p2h", "F");
  legend0 -> AddEntry(h1_trueCCRESdeltap, "CCRES(#Delta^{+})", "F");
  legend0 -> AddEntry(h1_trueCCRESdeltapp, "CCRES(#Delta^{++})", "F");
  legend0 -> AddEntry(h1_trueCCRESdelta0, "CCRES(#Delta^{0})", "F");
  legend0 -> AddEntry(h1_trueCCOther, "CC-other", "F");
  legend0 -> AddEntry(h1_trueNC, "NC", "F");
  legend0 -> SetFillColor(0);
  legend0 -> Draw() ;
  
  

  
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  hs_RecoOsc -> SetMaximum(1090);
  //hs_RecoOsc -> SetMaximum(2090);
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc -> Draw();
  
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend1 -> AddEntry(h1_CCQE, "CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCnonQE, "CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCRESdeltap, "CCRES(#Delta^{+})", "F");
  legend1 -> AddEntry(h1_CCRESdeltapp, "CCRES(#Delta^{++})", "F");
  legend1 -> AddEntry(h1_CCRESdelta0, "CCRES(#Delta^{0})", "F");
  legend1 -> AddEntry(h1_CCOther, "CC-other", "F");
  legend1 -> AddEntry(h1_NC, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;


  /*
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_RecoEnu -> GetYaxis()-> SetRangeUser(0, 8000);  //numu
  //h1_RecoEnu -> GetYaxis()-> SetRangeUser(0, 6000);  //numubar
  ((TGaxis*)h1_RecoEnu->GetYaxis())->SetMaxDigits(4);
  h1_RecoEnu ->GetYaxis()->SetTitleSize(0.038);
  h1_RecoEnu ->GetYaxis()->SetTitleOffset(1.3);
  h1_RecoEnu ->GetYaxis()->SetLabelSize(0.036);
  h1_RecoEnu -> Draw();
  //hs_RecoOsc -> SetMaximum(1090);
  //hs_RecoOsc -> SetMaximum(2090);
  hs_RecoOsc -> Draw("SAME");
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  //hs_RecoOsc -> Draw();
  
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.35, 0.85, 0.85);
  legend1 -> SetTextSize(0.03);
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend1 -> AddEntry(h1_RecoEnu, "No Oscillation", "L");
  legend1 -> AddEntry(h1_CCQE, "CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCnonQE, "CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCRESdeltap, "CCRES(#Delta^{+})", "F");
  legend1 -> AddEntry(h1_CCRESdeltapp, "CCRES(#Delta^{++})", "F");
  legend1 -> AddEntry(h1_CCRESdelta0, "CCRES(#Delta^{0})", "F");
  legend1 -> AddEntry(h1_CCOther, "CC-other", "F");
  legend1 -> AddEntry(h1_NC, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
  */
  
  
  TCanvas* c2 = new TCanvas("c2","w/ TagN",900,700);
  c2 -> SetGrid();
  hs_RecoOsc_wTagN -> SetMaximum(1090);
  //hs_RecoOsc_wTagN -> SetMaximum(2090);
  hs_RecoOsc_wTagN -> Draw();
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc_wTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_wTagN -> Draw();
  c2->RedrawAxis();

  TLegend* legend2 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend2 -> SetTextSize(0.03);
  legend2->AddEntry((TObject*)0,"#kern[-0.25]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC(w/ tagged neutrons) }","");
  //legend2->AddEntry((TObject*)0,"#kern[-0.25]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC(w/ tagged neutrons) }","");
  legend2 -> AddEntry(h1_CCQE, "CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CCnonQE, "CC(2p2h+others)", "F");
  legend2 -> AddEntry(h1_CCRESdeltap, "CCRES(#Delta^{+})", "F");
  legend2 -> AddEntry(h1_CCRESdeltapp, "CCRES(#Delta^{++})", "F");
  legend2 -> AddEntry(h1_CCRESdelta0, "CCRES(#Delta^{0})", "F");
  legend2 -> AddEntry(h1_CCOther, "CC-other", "F");
  legend2 -> AddEntry(h1_NC, "NC", "F");
  legend2->SetFillColor(0);
  legend2->Draw() ;


  TCanvas* c3 = new TCanvas("c3","w/o TagN",900,700);
  c3 -> SetGrid();
  hs_RecoOsc_woTagN -> SetMaximum(1090);
  //hs_RecoOsc_woTagN -> SetMaximum(2090);
  hs_RecoOsc_woTagN -> Draw();
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc_woTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_woTagN -> Draw();
  c3->RedrawAxis();

  TLegend* legend3 = new TLegend(0.45, 0.45, 0.85, 0.85);
  legend3 -> SetTextSize(0.03);
  legend3->AddEntry((TObject*)0,"#kern[-0.25]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC(w/o tagged neutrons) }","");
  //legend3->AddEntry((TObject*)0,"#kern[-0.25]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC(w/o tagged neutrons) }","");
  legend3 -> AddEntry(h1_CCQE, "CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CCnonQE, "CC(2p2h+others)", "F");
  legend3 -> AddEntry(h1_CCRESdeltap, "CCRES(#Delta^{+})", "F");
  legend3 -> AddEntry(h1_CCRESdeltapp, "CCRES(#Delta^{++})", "F");
  legend3 -> AddEntry(h1_CCRESdelta0, "CCRES(#Delta^{0})", "F");
  legend3 -> AddEntry(h1_CCOther, "CC-other", "F");
  legend3 -> AddEntry(h1_NC, "NC", "F");
  legend3->SetFillColor(0);
  legend3->Draw();
  
}