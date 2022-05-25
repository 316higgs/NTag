#include "NeutrinoOscillation.h"
#include "TH1D.h"

void NeutrinoOscillation::SetHistoFrame() {

  h1_OscProb      = new TH1F("h1_OscProb", "Oscillation Probability(numu->numu); Neutrino Events; Entries", 100, 0, 1);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_Enutrue[i] = new TH1F(TString::Format("h1_Enutrue_mode%d", i), "Truth Neutrino Energy; Truth Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_Enureco[i] = new TH1F(TString::Format("h1_Enureco_mode%d", i), "Reco. Neutrino Energy; Reconstructed Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_Enureso[i] = new TH1F(TString::Format("h1_Enureso_mode%d", i), "Neutrino Energy Resolution; E^{true}_{#nu}-E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 40, -1, 1);

    h1_numu_x_numu_NoOsc[i]           = new TH1F(TString::Format("h1_numu_x_numu_NoOsc_mode%d", i), "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_numu_x_numu_NoOsc_wNeutron[i]  = new TH1F(TString::Format("h1_numu_x_numu_NoOsc_wNeutron_mode%d", i), "No Oscillation w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_numu_x_numu_NoOsc_woNeutron[i] = new TH1F(TString::Format("h1_numu_x_numu_NoOsc_woNeutron_mode%d", i), "No Oscillation w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_numu_x_numu_OscProb[i]           = new TH1F(TString::Format("h1_numu_x_numu_OscProb_mode%d", i), "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_numu_x_numu_OscProb_wNeutron[i]  = new TH1F(TString::Format("h1_numu_x_numu_OscProb_wNeutron_mode%d", i), "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_numu_x_numu_OscProb_woNeutron[i] = new TH1F(TString::Format("h1_numu_x_numu_OscProb_woNeutron_mode%d", i), "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_numu_x_numu_OscProbRatio[i]           = new TH1F(TString::Format("h1_numu_x_numu_OscProbRatio_mode%d", i), "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events/Number of Events(No Osc.)", 60, 0, 3);
    h1_numu_x_numu_OscProbRatio_wNeutron[i]  = new TH1F(TString::Format("h1_numu_x_numu_OscProbRatio_wNeutron_mode%d", i), "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events/Number of Events(No Osc.)", 60, 0, 3);
    h1_numu_x_numu_OscProbRatio_woNeutron[i] = new TH1F(TString::Format("h1_numu_x_numu_OscProbRatio_woNeutron_mode%d", i), "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events/Number of Events(No Osc.)", 60, 0, 3);
  }

  h1_AllEnutrue     = new TH1F("h1_AllEnutrue",  "Truth Neutrino Energy; E^{true}_{#nu}[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_AllEnureco     = new TH1F("h1_AllEnureco",  "Truth Neutrino Energy; E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_AllEnureso     = new TH1F("h1_AllEnureso",  "Neutrino Energy Resolution; E^{true}_{#nu}-E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 50, -0.8, 0.8);
  h1_EnuresoCCRES_deltap  = new TH1F("h1_EnuresoCCRES_deltap", "CC RES with final state neutrons; E^{true}_{#nu}-E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 60, -1, 1);
  h1_EnuresoCCRES_deltapp = new TH1F("h1_EnuresoCCRES_deltapp", "CC RES with final state neutrons; E^{true}_{#nu}-E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 60, -1, 1);
  h1_EnuresoCCRES_delta0  = new TH1F("h1_EnuresoCCRES_delta0", "CC RES with final state neutrons; E^{true}_{#nu}-E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 60, -1, 1);
  h2_Reso_x_TrueEnu = new TH2F("h2_Reso_x_TrueEnu", "Resolution vs Truth Neutrino Energy; Truth Neutrino Energy E^{true}_{#nu}[GeV]; E^{true}_{#nu}-E^{reco}_{#nu}[GeV]", 60, 0, 3, 60, -1, 1);

  h1_Allnumu_x_numu_NoOsc        = new TH1F("h1_Allnumu_x_numu_NoOsc", "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_Allnumu_x_numu_OscProb      = new TH1F("h1_Allnumu_x_numu_OscProb", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_Allnumu_x_numu_OscProbRatio = new TH1F("h1_Allnumu_x_numu_OscProbRatio", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events/Number of Events(No Osc.)", 60, 0, 3);
}

void NeutrinoOscillation::SetHistoFormat() {
  h1_OscProb -> SetLineWidth(2);
  h1_OscProb -> SetLineColor(kAzure-4);
  h1_OscProb -> SetFillColor(kAzure-4);
  h1_OscProb -> SetTitleOffset(1.4, "Y");
  h1_OscProb -> SetTitleSize(0.035, "Y");
  h1_OscProb -> SetLabelSize(0.033, "Y");

  h1_Enutrue[0] -> SetLineColor(kAzure-1);
  h1_Enutrue[0] -> SetFillColor(kAzure-1);
  h1_Enutrue[1] -> SetLineColor(kOrange+8);
  h1_Enutrue[1] -> SetFillColor(kOrange+8);
  h1_Enutrue[2] -> SetLineColor(kTeal+9);
  h1_Enutrue[2] -> SetFillColor(kTeal+9);

  h1_Enureco[0] -> SetLineColor(kAzure-1);
  h1_Enureco[1] -> SetLineColor(kOrange+8);
  h1_Enureco[2] -> SetLineColor(kTeal+9);
  h1_Enureco[0] -> SetFillColor(kAzure-1);
  h1_Enureco[1] -> SetFillColor(kOrange+8);
  h1_Enureco[2] -> SetFillColor(kTeal+9);

  h1_Enureso[0] -> SetLineColor(kAzure-1);
  h1_Enureso[1] -> SetLineColor(kOrange+8);
  h1_Enureso[2] -> SetLineColor(kTeal+9);
  h1_Enureso[0] -> SetFillColor(kAzure-1);
  h1_Enureso[1] -> SetFillColor(kOrange+8);
  h1_Enureso[2] -> SetFillColor(kTeal+9);

  h1_EnuresoCCRES_deltap  -> SetLineWidth(2);
  h1_EnuresoCCRES_deltapp -> SetLineWidth(2);
  h1_EnuresoCCRES_delta0  -> SetLineWidth(2);

  h1_EnuresoCCRES_deltap  -> SetLineColor(kPink+1);
  h1_EnuresoCCRES_deltapp -> SetLineColor(kPink-8);
  h1_EnuresoCCRES_delta0  -> SetLineColor(kGray+1);

  h1_EnuresoCCRES_deltap  -> SetFillColor(kPink+1);
  h1_EnuresoCCRES_deltapp -> SetFillColor(kPink-8);
  h1_EnuresoCCRES_delta0  -> SetFillColor(kGray+1);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_numu_x_numu_NoOsc[i]           -> SetLineWidth(2);
    h1_numu_x_numu_NoOsc_wNeutron[i]  -> SetLineWidth(2);
    h1_numu_x_numu_NoOsc_woNeutron[i] -> SetLineWidth(2);

    h1_numu_x_numu_OscProb[i]           -> SetLineWidth(2);
    h1_numu_x_numu_OscProb_wNeutron[i]  -> SetLineWidth(2);
    h1_numu_x_numu_OscProb_woNeutron[i] -> SetLineWidth(2);

    h1_numu_x_numu_OscProbRatio[i]           -> SetLineWidth(2);
    h1_numu_x_numu_OscProbRatio_wNeutron[i]  -> SetLineWidth(2);
    h1_numu_x_numu_OscProbRatio_woNeutron[i] -> SetLineWidth(2);
  }

  h1_numu_x_numu_NoOsc[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_NoOsc[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_NoOsc[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_NoOsc[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_NoOsc[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_NoOsc[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_NoOsc_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_NoOsc_wNeutron[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_NoOsc_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_NoOsc_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_NoOsc_wNeutron[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_NoOsc_wNeutron[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_NoOsc_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_NoOsc_woNeutron[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_NoOsc_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_NoOsc_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_NoOsc_woNeutron[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_NoOsc_woNeutron[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_OscProb[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_OscProb[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_OscProb[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_OscProb[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_OscProb[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_OscProb[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_OscProb_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_OscProb_wNeutron[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_OscProb_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_OscProb_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_OscProb_wNeutron[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_OscProb_wNeutron[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_OscProb_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_OscProb_woNeutron[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_OscProb_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_OscProb_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_OscProb_woNeutron[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_OscProb_woNeutron[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_OscProbRatio[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_OscProbRatio[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_OscProbRatio[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_OscProbRatio[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_OscProbRatio[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_OscProbRatio[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_OscProbRatio_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_OscProbRatio_wNeutron[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_OscProbRatio_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_OscProbRatio_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_OscProbRatio_wNeutron[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_OscProbRatio_wNeutron[2] -> SetFillColor(kTeal+9);

  h1_numu_x_numu_OscProbRatio_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_numu_x_numu_OscProbRatio_woNeutron[1] -> SetLineColor(kOrange+8);
  h1_numu_x_numu_OscProbRatio_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_numu_x_numu_OscProbRatio_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_numu_x_numu_OscProbRatio_woNeutron[1] -> SetFillColor(kOrange+8);
  h1_numu_x_numu_OscProbRatio_woNeutron[2] -> SetFillColor(kTeal+9);

  h2_Reso_x_TrueEnu -> SetStats(0);
}


float NeutrinoOscillation::GetTrueEnu(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float Enu = numu->var<float>("pnu", 0);
  h1_AllEnutrue -> Fill(Enu);

  //CCQE(1p1h)
  if (mode==1) {
  	h1_Enutrue[0] -> Fill(Enu);
  }

  //CC non-QE
  if (mode>=2 && mode<=30) {
  	h1_Enutrue[1] -> Fill(Enu);
  }

  //NC
  if (mode>=31) {
  	h1_Enutrue[2] -> Fill(Enu);
  }
  return Enu;
}

float NeutrinoOscillation::GetRecoEnu(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  //float Enu = numu->var<float>("fq1rmom", 0, 2);
  float Enu = numu->var<float>("erec");
  h1_AllEnureco -> Fill(Enu/1000.);

  //CCQE(1p1h)
  if (mode==1) {
  	h1_Enureco[0] -> Fill(Enu/1000.);
  }

  //CC non-QE
  if (mode>=2 && mode<=30) {
  	h1_Enureco[1] -> Fill(Enu/1000.);
  }

  //NC
  if (mode>=31) {
  	h1_Enureco[2] -> Fill(Enu/1000.);
  }
  return Enu;
}

float NeutrinoOscillation::GetEnuResolution(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  //float RecoEnu = numu->var<float>("fq1rmom", 0, 2);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = TrueEnu - RecoEnu/1000.;
  h1_AllEnureso -> Fill(EnuReso);

  //CCQE(1p1h)
  if (mode==1) {
  	h1_Enureso[0] -> Fill(EnuReso);
  }

  //CC non-QE
  if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) {
  	h1_Enureso[1] -> Fill(EnuReso);
  }
  //CC RES (Delta++)
  if (mode==11) h1_EnuresoCCRES_deltapp -> Fill(EnuReso);
  //CC RES (Delta0)
  if (mode==12) h1_EnuresoCCRES_delta0  -> Fill(EnuReso);
  //CC RES (Delta+)
  if (mode==13) h1_EnuresoCCRES_deltap  -> Fill(EnuReso);

  //NC
  if (mode>=31) {
  	h1_Enureso[2] -> Fill(EnuReso);
  }
  return EnuReso;
}

void NeutrinoOscillation::GetReso_x_TrueEnu(CC0PiNumu* numu) {
  float TrueEnu = numu->var<float>("pnu", 0);
  //float RecoEnu = numu->var<float>("fq1rmom", 0, 2);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = TrueEnu - RecoEnu/1000.;
  h2_Reso_x_TrueEnu -> Fill(TrueEnu, EnuReso);
}


float NeutrinoOscillation::OscProbCalculator(CC0PiNumu* numu, bool histfill) {
  float OscProb = numu->getOscWgt();
  if (histfill==true) h1_OscProb -> Fill(OscProb);
  return OscProb;
}

float NeutrinoOscillation::GetWgtNeutrino(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  //float RecoEnu = numu->var<float>("fq1rmom", 0, 2);
  float RecoEnu = numu->var<float>("erec");
  h1_Allnumu_x_numu_NoOsc        -> Fill(RecoEnu/1000.);
  h1_Allnumu_x_numu_OscProb      -> Fill(RecoEnu/1000., OscProb);
  h1_Allnumu_x_numu_OscProbRatio -> Fill(RecoEnu/1000., OscProb);
  
  //CCQE(1p1h)
  if (mode==1) {
  	h1_numu_x_numu_NoOsc[0]        -> Fill(RecoEnu/1000.);
    h1_numu_x_numu_OscProb[0]      -> Fill(RecoEnu/1000., OscProb);
    h1_numu_x_numu_OscProbRatio[0] -> Fill(RecoEnu/1000., OscProb);
  }

  //CC non-QE
  if (mode>=2 && mode<=30) {
  	h1_numu_x_numu_NoOsc[1]        -> Fill(RecoEnu/1000.);
    h1_numu_x_numu_OscProb[1]      -> Fill(RecoEnu/1000., OscProb);
    h1_numu_x_numu_OscProbRatio[1] -> Fill(RecoEnu/1000., OscProb);
  }

  //NC
  if (mode>=31) {
  	h1_numu_x_numu_NoOsc[2]        -> Fill(RecoEnu/1000.);
    h1_numu_x_numu_OscProb[2]      -> Fill(RecoEnu/1000., OscProb);
    h1_numu_x_numu_OscProbRatio[2] -> Fill(RecoEnu/1000., OscProb);
  }
  return OscProb;
}

void NeutrinoOscillation::cdNeutrinoOscillation(TFile* fout) {
  fout -> mkdir("NeutrinoOscillation");
  fout -> cd("NeutrinoOscillation");
}


void NeutrinoOscillation::WritePlots() {
  h1_OscProb    -> Write();

  h1_AllEnutrue     -> Write();
  h1_AllEnureco     -> Write();
  h1_AllEnureso     -> Write();
  h2_Reso_x_TrueEnu -> Write();
  h1_EnuresoCCRES_deltap  -> Write();
  h1_EnuresoCCRES_delta0  -> Write();
  h1_EnuresoCCRES_deltapp -> Write();

  h1_Allnumu_x_numu_NoOsc        -> Write();
  h1_Allnumu_x_numu_OscProb      -> Write();
  h1_Allnumu_x_numu_OscProbRatio -> Sumw2();
  h1_Allnumu_x_numu_OscProbRatio -> Divide(h1_Allnumu_x_numu_NoOsc);
  h1_Allnumu_x_numu_OscProbRatio -> Write();

  for (int i=0; i<INTERACTIONTYPE; i++) {
  	h1_Enutrue[i] -> Write();
  	h1_Enureco[i] -> Write();
  	h1_Enureso[i] -> Write();

  	h1_numu_x_numu_NoOsc[i]        -> Write();
  	h1_numu_x_numu_OscProb[i]      -> Write();
  	h1_numu_x_numu_OscProbRatio[i] -> Sumw2();
  	h1_numu_x_numu_OscProbRatio[i] -> Divide(h1_numu_x_numu_NoOsc[i]);
  	h1_numu_x_numu_OscProbRatio[i] -> Write();

    h1_numu_x_numu_NoOsc_wNeutron[i]        -> Write();
    h1_numu_x_numu_OscProb_wNeutron[i]      -> Write();
    h1_numu_x_numu_OscProbRatio_wNeutron[i] -> Sumw2();
    h1_numu_x_numu_OscProbRatio_wNeutron[i] -> Divide(h1_numu_x_numu_NoOsc_wNeutron[i]);
    h1_numu_x_numu_OscProbRatio_wNeutron[i] -> Write();

    h1_numu_x_numu_NoOsc_woNeutron[i]        -> Write();
    h1_numu_x_numu_OscProb_woNeutron[i]      -> Write();
    h1_numu_x_numu_OscProbRatio_woNeutron[i] -> Sumw2();
    h1_numu_x_numu_OscProbRatio_woNeutron[i] -> Divide(h1_numu_x_numu_NoOsc_woNeutron[i]);
    h1_numu_x_numu_OscProbRatio_woNeutron[i] -> Write();
  }
}
