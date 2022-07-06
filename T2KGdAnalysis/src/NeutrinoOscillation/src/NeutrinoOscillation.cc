#include "NeutrinoOscillation.h"
#include "TH1D.h"

void NeutrinoOscillation::SetHistoFrame() {

  h1_OscProbcheck = new TH1F("h1_OscProbcheck", "Oscillation Probability(numu->numu); Neutrino Events; Entries", 100, 0, 1);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_Enutrue[i] = new TH1F(TString::Format("h1_Enutrue_mode%d", i), "Truth Neutrino Energy; Truth Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0., 3.);
    h1_Enureco[i] = new TH1F(TString::Format("h1_Enureco_mode%d", i), "Reco. Neutrino Energy; Reconstructed Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_Enureso[i] = new TH1F(TString::Format("h1_Enureso_mode%d", i), "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);

    h1_TruthOscProb[i]      = new TH1F(TString::Format("h1_TruthOscProb_mode%d", i), "Oscillation Probability; Truth Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_TruthOscProbRatio[i] = new TH1F(TString::Format("h1_TruthOscProbRatio_mode%d", i), "Oscillation Probability; Truth Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_NoOsc[i]                = new TH1F(TString::Format("h1_NoOsc_mode%d", i), "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_NoOsc_wTruthNeutron[i]  = new TH1F(TString::Format("h1_NoOsc_wTruthNeutron_mode%d", i), "No Oscillation w/ Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_NoOsc_woTruthNeutron[i] = new TH1F(TString::Format("h1_NoOsc_woTruthNeutron_mode%d", i), "No Oscillation w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_NoOsc_wNeutron[i]       = new TH1F(TString::Format("h1_NoOsc_wNeutron_mode%d", i), "No Oscillation w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_NoOsc_woNeutron[i]      = new TH1F(TString::Format("h1_NoOsc_woNeutron_mode%d", i), "No Oscillation w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_OscProb[i]                = new TH1F(TString::Format("h1_OscProb_mode%d", i), "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_OscProb_wTruthNeutron[i]  = new TH1F(TString::Format("h1_OscProb_wTruthNeutron_mode%d", i), "Oscillation Probability w/ Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_OscProb_woTruthNeutron[i] = new TH1F(TString::Format("h1_OscProb_woTruthNeutron_mode%d", i), "Oscillation Probability w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_OscProb_wNeutron[i]       = new TH1F(TString::Format("h1_OscProb_wNeutron_mode%d", i), "Oscillation Probability w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_OscProb_woNeutron[i]      = new TH1F(TString::Format("h1_OscProb_woNeutron_mode%d", i), "Oscillation Probability w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_OscProbRatio[i]                = new TH1F(TString::Format("h1_OscProbRatio_mode%d", i), "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
    h1_OscProbRatio_wTruthNeutron[i]  = new TH1F(TString::Format("h1_OscProbRatio_wTruthNeutron_mode%d", i), "Oscillation Probability w/ Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
    h1_OscProbRatio_woTruthNeutron[i] = new TH1F(TString::Format("h1_OscProbRatio_woTruthNeutron_mode%d", i), "Oscillation Probability w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
    h1_OscProbRatio_wNeutron[i]       = new TH1F(TString::Format("h1_OscProbRatio_wNeutron_mode%d", i), "Oscillation Probability w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
    h1_OscProbRatio_woNeutron[i]      = new TH1F(TString::Format("h1_OscProbRatio_woNeutron_mode%d", i), "Oscillation Probability w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  
    h1_OscProb_mistag[i] = new TH1F(TString::Format("h1_OscProb_mistag_mode%d", i), "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  }

  h1_AllEnutrue     = new TH1F("h1_AllEnutrue",  "Truth Neutrino Energy; Truth Neutrino Energy E^{true}_{#nu}[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_AllEnureco     = new TH1F("h1_AllEnureco",  "Truth Neutrino Energy; Reconstructed Neutrino Energy E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_AllEnureso     = new TH1F("h1_AllEnureso",  "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 50, -0.8, 0.8);

  h2_Reso_x_TrueEnu = new TH2F("h2_Reso_x_TrueEnu", "Resolution vs Truth Neutrino Energy; Truth Neutrino Energy E^{true}_{#nu}[GeV]; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}", 60, 0, 3, 60, -1, 1);

  h1_All_NoOsc                = new TH1F("h1_All_NoOsc", "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_NoOsc_wTruthNeutron  = new TH1F("h1_All_NoOsc_wTruthNeutron", "No Oscillation w/ Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_NoOsc_woTruthNeutron = new TH1F("h1_All_NoOsc_woTruthNeutron", "No Oscillation w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_NoOsc_wNeutron       = new TH1F("h1_All_NoOsc_wNeutron", "No Oscillation w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_NoOsc_woNeutron      = new TH1F("h1_All_NoOsc_woNeutron", "No Oscillation w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

  h1_All_OscProb                = new TH1F("h1_All_OscProb", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_OscProb_wTruthNeutron  = new TH1F("h1_All_OscProb_wTruthNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/ Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_OscProb_woTruthNeutron = new TH1F("h1_All_OscProb_woTruthNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_OscProb_wNeutron       = new TH1F("h1_All_OscProb_wNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_OscProb_woNeutron      = new TH1F("h1_All_OscProb_woNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

  h1_All_OscProbRatio                = new TH1F("h1_All_OscProbRatio", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_All_OscProbRatio_wTruthNeutron  = new TH1F("h1_All_OscProbRatio_wTruthNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/ Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_All_OscProbRatio_woTruthNeutron = new TH1F("h1_All_OscProbRatio_woTruthNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_All_OscProbRatio_wNeutron       = new TH1F("h1_All_OscProbRatio_wNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_All_OscProbRatio_woNeutron      = new TH1F("h1_All_OscProbRatio_woNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);


  h2_TrueMuDirectionXY = new TH2F("h2_TrueMuDirectionXY", "dirv; X #mu direction; Y #mu direction ", 50, -1, 1, 50, -1, 1);
  h2_TrueMuDirectionRZ = new TH2F("h2_TrueMuDirectionRZ", "dirv; R^{2} #mu direction; Z #mu direction ", 50, 0, 2, 50, -1, 1);
  h2_RecoMuDirectionXY = new TH2F("h2_RecoMuDirectionXY", "fq1rdir; X #mu direction; Y #mu direction ", 50, -1, 1, 50, -1, 1);
  h2_RecoMuDirectionRZ = new TH2F("h2_RecoMuDirectionRZ", "fq1rdir; R^{2} #mu direction; Z #mu direction ", 50, 0, 2, 50, -1, 1);
  
}

void NeutrinoOscillation::SetHistoFormat() {
  h1_OscProbcheck -> SetLineWidth(2);
  h1_OscProbcheck -> SetLineColor(kAzure-4);
  h1_OscProbcheck -> SetFillColor(kAzure-4);
  h1_OscProbcheck -> SetTitleOffset(1.4, "Y");
  h1_OscProbcheck -> SetTitleSize(0.035, "Y");
  h1_OscProbcheck -> SetLabelSize(0.033, "Y");

  h1_Enutrue[0] -> SetLineColor(kAzure-1);  //CCQE
  h1_Enutrue[0] -> SetFillColor(kAzure-1);
  h1_Enutrue[1] -> SetLineColor(kAzure-5); //CC non-QE(2p2h)
  h1_Enutrue[1] -> SetFillColor(kAzure-5);
  h1_Enutrue[2] -> SetLineColor(kTeal+9);   //NC
  h1_Enutrue[2] -> SetFillColor(kTeal+9);
  h1_Enutrue[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_Enutrue[3] -> SetFillColor(kPink+1);
  h1_Enutrue[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_Enutrue[4] -> SetFillColor(kPink-8);
  h1_Enutrue[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_Enutrue[5] -> SetFillColor(kGray+1);
  h1_Enutrue[6] -> SetLineColor(kCyan-6);   //CC other
  h1_Enutrue[6] -> SetFillColor(kCyan-6);

  h1_Enureco[0] -> SetLineColor(kAzure-1);
  h1_Enureco[0] -> SetFillColor(kAzure-1);
  h1_Enureco[1] -> SetFillColor(kAzure-5);
  h1_Enureco[1] -> SetLineColor(kAzure-5);
  h1_Enureco[2] -> SetFillColor(kTeal+9);
  h1_Enureco[2] -> SetLineColor(kTeal+9);
  h1_Enureco[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_Enureco[3] -> SetFillColor(kPink+1);
  h1_Enureco[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_Enureco[4] -> SetFillColor(kPink-8);
  h1_Enureco[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_Enureco[5] -> SetFillColor(kGray+1);
  h1_Enureco[6] -> SetLineColor(kCyan-6);   //CC other
  h1_Enureco[6] -> SetFillColor(kCyan-6);

  h1_Enureso[0] -> SetLineColor(kAzure-1);
  h1_Enureso[0] -> SetFillColor(kAzure-1);
  h1_Enureso[1] -> SetFillColor(kAzure-5);
  h1_Enureso[1] -> SetLineColor(kAzure-5);
  h1_Enureso[2] -> SetFillColor(kTeal+9);
  h1_Enureso[2] -> SetLineColor(kTeal+9);
  h1_Enureso[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_Enureso[3] -> SetFillColor(kPink+1);
  h1_Enureso[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_Enureso[4] -> SetFillColor(kPink-8);
  h1_Enureso[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_Enureso[5] -> SetFillColor(kGray+1);
  h1_Enureso[6] -> SetLineColor(kCyan-6);   //CC other
  h1_Enureso[6] -> SetFillColor(kCyan-6);


  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TruthOscProb[i]      -> SetLineWidth(2);
    h1_TruthOscProbRatio[i] -> SetLineWidth(2);

    h1_NoOsc[i]           -> SetLineWidth(2);
    h1_NoOsc_wNeutron[i]  -> SetLineWidth(2);
    h1_NoOsc_woNeutron[i] -> SetLineWidth(2);

    h1_OscProb[i]           -> SetLineWidth(2);
    h1_OscProb_wNeutron[i]  -> SetLineWidth(2);
    h1_OscProb_woNeutron[i] -> SetLineWidth(2);

    h1_OscProbRatio[i]           -> SetLineWidth(2);
    h1_OscProbRatio_wNeutron[i]  -> SetLineWidth(2);
    h1_OscProbRatio_woNeutron[i] -> SetLineWidth(2);
  }

  h1_TruthOscProb[0] -> SetLineColor(kAzure-1);
  h1_TruthOscProb[1] -> SetLineColor(kAzure-5);
  h1_TruthOscProb[2] -> SetLineColor(kTeal+9);
  h1_TruthOscProb[3] -> SetLineColor(kPink+1);
  h1_TruthOscProb[4] -> SetLineColor(kPink-8);
  h1_TruthOscProb[5] -> SetLineColor(kGray+1);
  h1_TruthOscProb[6] -> SetLineColor(kCyan-6);

  h1_TruthOscProb[0] -> SetFillColor(kAzure-1);
  h1_TruthOscProb[1] -> SetFillColor(kAzure-5);
  h1_TruthOscProb[2] -> SetFillColor(kTeal+9);
  h1_TruthOscProb[3] -> SetFillColor(kPink+1);
  h1_TruthOscProb[4] -> SetFillColor(kPink-8);
  h1_TruthOscProb[5] -> SetFillColor(kGray+1);
  h1_TruthOscProb[6] -> SetFillColor(kCyan-6);

  h1_TruthOscProbRatio[0] -> SetLineColor(kAzure-1);
  h1_TruthOscProbRatio[1] -> SetLineColor(kAzure-5);
  h1_TruthOscProbRatio[2] -> SetLineColor(kTeal+9);
  h1_TruthOscProbRatio[3] -> SetLineColor(kPink+1);
  h1_TruthOscProbRatio[4] -> SetLineColor(kPink-8);
  h1_TruthOscProbRatio[5] -> SetLineColor(kGray+1);
  h1_TruthOscProbRatio[6] -> SetLineColor(kCyan-6);

  h1_NoOsc[0] -> SetLineColor(kAzure-1);
  h1_NoOsc[1] -> SetLineColor(kAzure-5);
  h1_NoOsc[2] -> SetLineColor(kTeal+9);
  h1_NoOsc[3] -> SetLineColor(kPink+1);
  h1_NoOsc[4] -> SetLineColor(kPink-8);
  h1_NoOsc[5] -> SetLineColor(kGray+1);
  h1_NoOsc[6] -> SetLineColor(kCyan-6);

  h1_NoOsc[0] -> SetFillColor(kAzure-1);
  h1_NoOsc[1] -> SetFillColor(kAzure-5);
  h1_NoOsc[2] -> SetFillColor(kTeal+9);
  h1_NoOsc[3] -> SetFillColor(kPink+1);
  h1_NoOsc[4] -> SetFillColor(kPink-8);
  h1_NoOsc[5] -> SetFillColor(kGray+1);
  h1_NoOsc[6] -> SetFillColor(kCyan-6);

  h1_NoOsc_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_NoOsc_wNeutron[1] -> SetLineColor(kAzure-5);
  h1_NoOsc_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_NoOsc_wNeutron[3] -> SetLineColor(kPink+1);
  h1_NoOsc_wNeutron[4] -> SetLineColor(kPink-8);
  h1_NoOsc_wNeutron[5] -> SetLineColor(kGray+1);
  h1_NoOsc_wNeutron[6] -> SetLineColor(kCyan-6);

  h1_NoOsc_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_NoOsc_wNeutron[1] -> SetFillColor(kAzure-5);
  h1_NoOsc_wNeutron[2] -> SetFillColor(kTeal+9);
  h1_NoOsc_wNeutron[3] -> SetFillColor(kPink+1);
  h1_NoOsc_wNeutron[4] -> SetFillColor(kPink-8);
  h1_NoOsc_wNeutron[5] -> SetFillColor(kGray+1);
  h1_NoOsc_wNeutron[6] -> SetFillColor(kCyan-6);

  h1_NoOsc_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_NoOsc_woNeutron[1] -> SetLineColor(kAzure-5);
  h1_NoOsc_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_NoOsc_woNeutron[3] -> SetLineColor(kPink+1);
  h1_NoOsc_woNeutron[4] -> SetLineColor(kPink-8);
  h1_NoOsc_woNeutron[5] -> SetLineColor(kGray+1);
  h1_NoOsc_woNeutron[6] -> SetLineColor(kCyan-6);

  h1_NoOsc_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_NoOsc_woNeutron[1] -> SetFillColor(kAzure-5);
  h1_NoOsc_woNeutron[2] -> SetFillColor(kTeal+9);
  h1_NoOsc_woNeutron[3] -> SetFillColor(kPink+1);
  h1_NoOsc_woNeutron[4] -> SetFillColor(kPink-8);
  h1_NoOsc_woNeutron[5] -> SetFillColor(kGray+1);
  h1_NoOsc_woNeutron[6] -> SetFillColor(kCyan-6);

  h1_OscProb[0] -> SetLineColor(kAzure-1);
  h1_OscProb[1] -> SetLineColor(kAzure-5);
  h1_OscProb[2] -> SetLineColor(kTeal+9);
  h1_OscProb[3] -> SetLineColor(kPink+1);
  h1_OscProb[4] -> SetLineColor(kPink-8);
  h1_OscProb[5] -> SetLineColor(kGray+1);
  h1_OscProb[6] -> SetLineColor(kCyan-6);

  h1_OscProb[0] -> SetFillColor(kAzure-1);
  h1_OscProb[1] -> SetFillColor(kAzure-5);
  h1_OscProb[2] -> SetFillColor(kTeal+9);
  h1_OscProb[3] -> SetFillColor(kPink+1);
  h1_OscProb[4] -> SetFillColor(kPink-8);
  h1_OscProb[5] -> SetFillColor(kGray+1);
  h1_OscProb[6] -> SetFillColor(kCyan-6);

  h1_OscProb_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_OscProb_wNeutron[1] -> SetLineColor(kAzure-5);
  h1_OscProb_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_OscProb_wNeutron[3] -> SetLineColor(kPink+1);
  h1_OscProb_wNeutron[4] -> SetLineColor(kPink-8);
  h1_OscProb_wNeutron[5] -> SetLineColor(kGray+1);
  h1_OscProb_wNeutron[6] -> SetLineColor(kCyan-6);

  h1_OscProb_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_OscProb_wNeutron[1] -> SetFillColor(kAzure-5);
  h1_OscProb_wNeutron[2] -> SetFillColor(kTeal+9);
  h1_OscProb_wNeutron[3] -> SetFillColor(kPink+1);
  h1_OscProb_wNeutron[4] -> SetFillColor(kPink-8);
  h1_OscProb_wNeutron[5] -> SetFillColor(kGray+1);
  h1_OscProb_wNeutron[6] -> SetFillColor(kCyan-6);

  h1_OscProb_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_OscProb_woNeutron[1] -> SetLineColor(kAzure-5);
  h1_OscProb_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_OscProb_woNeutron[3] -> SetLineColor(kPink+1);
  h1_OscProb_woNeutron[4] -> SetLineColor(kPink-8);
  h1_OscProb_woNeutron[5] -> SetLineColor(kGray+1);
  h1_OscProb_woNeutron[6] -> SetLineColor(kCyan-6);

  h1_OscProb_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_OscProb_woNeutron[1] -> SetFillColor(kAzure-5);
  h1_OscProb_woNeutron[2] -> SetFillColor(kTeal+9);
  h1_OscProb_woNeutron[3] -> SetFillColor(kPink+1);
  h1_OscProb_woNeutron[4] -> SetFillColor(kPink-8);
  h1_OscProb_woNeutron[5] -> SetFillColor(kGray+1);
  h1_OscProb_woNeutron[6] -> SetFillColor(kCyan-6);

  h1_OscProbRatio[0] -> SetLineColor(kAzure-1);
  h1_OscProbRatio[1] -> SetLineColor(kAzure-5);
  h1_OscProbRatio[2] -> SetLineColor(kTeal+9);
  h1_OscProbRatio[3] -> SetLineColor(kPink+1);
  h1_OscProbRatio[4] -> SetLineColor(kPink-8);
  h1_OscProbRatio[5] -> SetLineColor(kGray+1);
  h1_OscProbRatio[6] -> SetLineColor(kCyan-6);

  h1_OscProbRatio[0] -> SetFillColor(kAzure-1);
  h1_OscProbRatio[1] -> SetFillColor(kAzure-5);
  h1_OscProbRatio[2] -> SetFillColor(kTeal+9);
  h1_OscProbRatio[3] -> SetFillColor(kPink+1);
  h1_OscProbRatio[4] -> SetFillColor(kPink-8);
  h1_OscProbRatio[5] -> SetFillColor(kGray+1);
  h1_OscProbRatio[6] -> SetFillColor(kCyan-6);

  h1_OscProbRatio_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_OscProbRatio_wNeutron[1] -> SetLineColor(kAzure-5);
  h1_OscProbRatio_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_OscProbRatio_wNeutron[3] -> SetLineColor(kPink+1);
  h1_OscProbRatio_wNeutron[4] -> SetLineColor(kPink-8);
  h1_OscProbRatio_wNeutron[5] -> SetLineColor(kGray+1);
  h1_OscProbRatio_wNeutron[6] -> SetLineColor(kCyan-6);

  h1_OscProbRatio_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_OscProbRatio_wNeutron[1] -> SetFillColor(kAzure-5);
  h1_OscProbRatio_wNeutron[2] -> SetFillColor(kTeal+9);
  h1_OscProbRatio_wNeutron[3] -> SetFillColor(kPink+1);
  h1_OscProbRatio_wNeutron[4] -> SetFillColor(kPink-8);
  h1_OscProbRatio_wNeutron[5] -> SetFillColor(kGray+1);
  h1_OscProbRatio_wNeutron[6] -> SetFillColor(kCyan-6);

  h1_OscProbRatio_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_OscProbRatio_woNeutron[1] -> SetLineColor(kAzure-5);
  h1_OscProbRatio_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_OscProbRatio_woNeutron[3] -> SetLineColor(kPink+1);
  h1_OscProbRatio_woNeutron[4] -> SetLineColor(kPink-8);
  h1_OscProbRatio_woNeutron[5] -> SetLineColor(kGray+1);
  h1_OscProbRatio_woNeutron[6] -> SetLineColor(kCyan-6);

  h1_OscProbRatio_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_OscProbRatio_woNeutron[1] -> SetFillColor(kAzure-5);
  h1_OscProbRatio_woNeutron[2] -> SetFillColor(kTeal+9);
  h1_OscProbRatio_woNeutron[3] -> SetFillColor(kPink+1);
  h1_OscProbRatio_woNeutron[4] -> SetFillColor(kPink-8);
  h1_OscProbRatio_woNeutron[5] -> SetFillColor(kGray+1);
  h1_OscProbRatio_woNeutron[6] -> SetFillColor(kCyan-6);

  h2_Reso_x_TrueEnu -> SetStats(0);

  h2_TrueMuDirectionXY -> SetStats(0);
  h2_TrueMuDirectionRZ -> SetStats(0);
  h2_RecoMuDirectionXY -> SetStats(0);
  h2_RecoMuDirectionRZ -> SetStats(0);
}


float NeutrinoOscillation::GetTrueEnu(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float Enu = numu->var<float>("pnu", 0);
  h1_AllEnutrue -> Fill(Enu);

  //CCQE(1p1h)
  if (mode==1) h1_Enutrue[0] -> Fill(Enu);

  //CC non-QE
  //if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enutrue[1] -> Fill(Enu);
  if (mode>=2 && mode<=10) h1_Enutrue[1] -> Fill(Enu);

  //NC
  if (mode>=31) h1_Enutrue[2] -> Fill(Enu);

  //CC RES (Delta+)
  if (mode==13) h1_Enutrue[3] -> Fill(Enu);
  //CC RES (Delta++)
  if (mode==11) h1_Enutrue[4] -> Fill(Enu);
  //CC RES (Delta0)
  if (mode==12) h1_Enutrue[5] -> Fill(Enu);

  //CC other
  if (mode>=14 && mode<=30) h1_Enutrue[6] -> Fill(Enu);
  return Enu;
}

float NeutrinoOscillation::GetRecoEnu(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  //float Enu = numu->var<float>("fq1rmom", 0, 2);
  float Enu = numu->var<float>("erec");
  h1_AllEnureco -> Fill(Enu/1000.);

  /*if (Enu/1000. > 5.6 && Enu/1000. < 5.8) {
    std::cout << "Reco Enu = " << Enu/1000. << " GeV" << std::endl;
  }*/

  //CCQE(1p1h)
  if (mode==1) h1_Enureco[0] -> Fill(Enu/1000.);

  //CC non-QE
  //if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enureco[1] -> Fill(Enu/1000.);
  if (mode>=2 && mode<=10) h1_Enureco[1] -> Fill(Enu/1000.);

  //NC
  if (mode>=31) h1_Enureco[2] -> Fill(Enu/1000.);

  //CC RES (Delta+)
  if (mode==13) h1_Enureco[3] -> Fill(Enu/1000.);
  //CC RES (Delta++)
  if (mode==11) h1_Enureco[4] -> Fill(Enu/1000.);
  //CC RES (Delta0)
  if (mode==12) h1_Enureco[5] -> Fill(Enu/1000.);

  //CC other
  if (mode>=14 && mode<=30) h1_Enureco[6] -> Fill(Enu/1000.);
  return Enu;
}

float NeutrinoOscillation::GetEnuResolution(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  //float RecoEnu = numu->var<float>("fq1rmom", 0, 2);
  float RecoEnu = numu->var<float>("erec");
  //float EnuReso = TrueEnu - RecoEnu/1000.;
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;
  h1_AllEnureso -> Fill(EnuReso);

  //CCQE(1p1h)
  if (mode==1) h1_Enureso[0] -> Fill(EnuReso);

  //CC non-QE
  //if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enureso[1] -> Fill(EnuReso);
  if (mode>=2 && mode<=10) h1_Enureso[1] -> Fill(EnuReso);

  //NC
  if (mode>=31) h1_Enureso[2] -> Fill(EnuReso);

  //CC RES (Delta+)
  if (mode==13) h1_Enureso[3] -> Fill(EnuReso);
  //CC RES (Delta++)
  if (mode==11) h1_Enureso[4] -> Fill(EnuReso);
  //CC RES (Delta0)
  if (mode==12) h1_Enureso[5] -> Fill(EnuReso);

  //CC other
  if (mode>=14 && mode<=30) h1_Enureso[6] -> Fill(EnuReso);
  return EnuReso;
}

void NeutrinoOscillation::GetReso_x_TrueEnu(CC0PiNumu* numu) {
  float TrueEnu = numu->var<float>("pnu", 0);
  //float RecoEnu = numu->var<float>("fq1rmom", 0, 2);
  float RecoEnu = numu->var<float>("erec");
  //float EnuReso = TrueEnu - RecoEnu/1000.;
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;
  h2_Reso_x_TrueEnu -> Fill(TrueEnu, EnuReso);
}


void NeutrinoOscillation::GetTrueMuDirection(CC0PiNumu* numu) {
  float mudirx = numu->var<float>("dirv", 2, 0);
  float mudiry = numu->var<float>("dirv", 2, 1);
  float mudirz = numu->var<float>("dirv", 2, 2);
  float mudirR = sqrt( mudirx*mudirx + mudiry*mudiry );

  h2_TrueMuDirectionXY -> Fill(mudirx, mudiry);
  h2_TrueMuDirectionRZ -> Fill(mudirR, mudirz);
  //return mudir;
}

void NeutrinoOscillation::GetRecoMuDirection(CC0PiNumu* numu) {
  float mudirx = numu->var<float>("fq1rdir", 0, 2, 0);
  float mudiry = numu->var<float>("fq1rdir", 0, 2, 1);
  float mudirz = numu->var<float>("fq1rdir", 0, 2, 2);
  float mudirR = sqrt( mudirx*mudirx + mudiry*mudiry );

  h2_RecoMuDirectionXY -> Fill(mudirx, mudiry);
  h2_RecoMuDirectionRZ -> Fill(mudirR, mudirz);
  //return mudir;
}


float NeutrinoOscillation::OscProbCalculator(CC0PiNumu* numu, bool histfill) {
  float OscProb = numu->getOscWgt();
  if (histfill==true) h1_OscProbcheck -> Fill(OscProb);
  return OscProb;
}

float NeutrinoOscillation::GetWgtNeutrino(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");

  h1_All_NoOsc        -> Fill(RecoEnu/1000.);
  h1_All_OscProb      -> Fill(RecoEnu/1000., OscProb);
  h1_All_OscProbRatio -> Fill(RecoEnu/1000., OscProb);

  //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
  if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
    NoOscLegacy++;
    OscLegacy += OscProb;
  }

  
  //CCQE(1p1h)
  if (mode==1) {
    h1_TruthOscProb[0]      -> Fill(TrueEnu, OscProb);
    h1_TruthOscProbRatio[0] -> Fill(TrueEnu, OscProb);

  	h1_NoOsc[0]        -> Fill(RecoEnu/1000.);
    h1_OscProb[0]      -> Fill(RecoEnu/1000., OscProb);
    h1_OscProbRatio[0] -> Fill(RecoEnu/1000., OscProb);

    OscillatedCCQE += OscProb;
    if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
      NoOscOnlyCCQE++;
      OscOnlyCCQE += OscProb;
    }
  }

  //CC non-QE(2p2h)
  if (mode>=2 && mode<=10) {
    h1_TruthOscProb[1]      -> Fill(TrueEnu, OscProb);
    h1_TruthOscProbRatio[1] -> Fill(TrueEnu, OscProb);

  	h1_NoOsc[1]        -> Fill(RecoEnu/1000.);
    h1_OscProb[1]      -> Fill(RecoEnu/1000., OscProb);
    h1_OscProbRatio[1] -> Fill(RecoEnu/1000., OscProb);

    OscillatedCCnonQE += OscProb;
  }

  //NC
  if (mode>=31) {
    h1_TruthOscProb[2]      -> Fill(TrueEnu);
    h1_TruthOscProbRatio[2] -> Fill(TrueEnu);

  	h1_NoOsc[2]        -> Fill(RecoEnu/1000.);
    h1_OscProb[2]      -> Fill(RecoEnu/1000.);
    h1_OscProbRatio[2] -> Fill(RecoEnu/1000.);

    OscillatedNC++;
  }

  //CC RES (Delta+)
  if (mode==13) {
    h1_TruthOscProb[3]      -> Fill(TrueEnu, OscProb);
    h1_TruthOscProbRatio[3] -> Fill(TrueEnu, OscProb);

    h1_NoOsc[3]        -> Fill(RecoEnu/1000.);
    h1_OscProb[3]      -> Fill(RecoEnu/1000., OscProb);
    h1_OscProbRatio[3] -> Fill(RecoEnu/1000., OscProb);

    OscillatedCCRESp += OscProb;
  }
  //CC RES (Delta++)
  if (mode==11) {
    h1_TruthOscProb[4]      -> Fill(TrueEnu, OscProb);
    h1_TruthOscProbRatio[4] -> Fill(TrueEnu, OscProb);

    h1_NoOsc[4]        -> Fill(RecoEnu/1000.);
    h1_OscProb[4]      -> Fill(RecoEnu/1000., OscProb);
    h1_OscProbRatio[4] -> Fill(RecoEnu/1000., OscProb);

    OscillatedCCRESpp += OscProb;
  }
  //CC RES (Delta0)
  if (mode==12) {
    h1_TruthOscProb[5]      -> Fill(TrueEnu, OscProb);
    h1_TruthOscProbRatio[5] -> Fill(TrueEnu, OscProb);

    h1_NoOsc[5]        -> Fill(RecoEnu/1000.);
    h1_OscProb[5]      -> Fill(RecoEnu/1000., OscProb);
    h1_OscProbRatio[5] -> Fill(RecoEnu/1000., OscProb);

    OscillatedCCRES0 += OscProb;
  }
  //CC other
  if (mode>=14 && mode<=30) {
    h1_TruthOscProb[6]      -> Fill(TrueEnu, OscProb);
    h1_TruthOscProbRatio[6] -> Fill(TrueEnu, OscProb);

    h1_NoOsc[6]        -> Fill(RecoEnu/1000.);
    h1_OscProb[6]      -> Fill(RecoEnu/1000., OscProb);
    h1_OscProbRatio[6] -> Fill(RecoEnu/1000., OscProb);

    OscillatedCCOther += OscProb;
  }
  return OscProb;
}


float NeutrinoOscillation::GetWgtNeutrino_wTrueN(CC0PiNumu* numu, float NTrueN) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  float RecoEnu = numu->var<float>("erec");

  if (NTrueN==0) {
    h1_All_NoOsc_woTruthNeutron        -> Fill(RecoEnu/1000.);
    h1_All_OscProb_woTruthNeutron      -> Fill(RecoEnu/1000., OscProb);
    h1_All_OscProbRatio_woTruthNeutron -> Fill(RecoEnu/1000., OscProb);

    if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
      NoOscwoTrueN++;
      OscwoTrueN += OscProb;
    }


    //CCQE(1p1h)
    if (mode==1) {
      h1_NoOsc_woTruthNeutron[0]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[0]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woTruthNeutron[0] -> Fill(RecoEnu/1000., OscProb);

      //std::cout << "OscProb = " << OscProb << std::endl;
      OscillatedCCQE_woTrueN += OscProb;
    }

    //CC non-QE
    if (mode>=2 && mode<=10) {
      h1_NoOsc_woTruthNeutron[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woTruthNeutron[1] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCnonQE_woTrueN += OscProb;
    }

    //NC
    if (mode>=31) {
      h1_NoOsc_woTruthNeutron[2]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[2]      -> Fill(RecoEnu/1000.);
      h1_OscProbRatio_woTruthNeutron[2] -> Fill(RecoEnu/1000.);

      OscillatedNC_woTrueN++;
    }

    //CC RES (Delta+)
    if (mode==13) {
      h1_NoOsc_woTruthNeutron[3]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[3]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woTruthNeutron[3] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESp_woTrueN += OscProb;
    }
    //CC RES (Delta++)
    if (mode==11) {
      h1_NoOsc_woTruthNeutron[4]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[4]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woTruthNeutron[4] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESpp_woTrueN += OscProb;
    }
    //CC RES (Delta0)
    if (mode==12) {
      h1_NoOsc_woTruthNeutron[5]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[5]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woTruthNeutron[5] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRES0_woTrueN += OscProb;
    }
    //CC other
    if (mode>=14 && mode<=30) {
      h1_NoOsc_woTruthNeutron[6]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woTruthNeutron[6]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woTruthNeutron[6] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCOther_woTrueN += OscProb;
    }
  }
  else {
    h1_All_NoOsc_wTruthNeutron        -> Fill(RecoEnu/1000.);
    h1_All_OscProb_wTruthNeutron      -> Fill(RecoEnu/1000., OscProb);
    h1_All_OscProbRatio_wTruthNeutron -> Fill(RecoEnu/1000., OscProb);

    //CCQE(1p1h)
    if (mode==1) {
      h1_NoOsc_wTruthNeutron[0]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[0]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wTruthNeutron[0] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCQE_wTrueN += OscProb;
    }

    //CC non-QE
    if (mode>=2 && mode<=10) {
      h1_NoOsc_wTruthNeutron[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wTruthNeutron[1] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCnonQE_wTrueN += OscProb;
    }

    //NC
    if (mode>=31) {
      h1_NoOsc_wTruthNeutron[2]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[2]      -> Fill(RecoEnu/1000.);
      h1_OscProbRatio_wTruthNeutron[2] -> Fill(RecoEnu/1000.);

      OscillatedNC_wTrueN++;
    }

    //CC RES (Delta+)
    if (mode==13) {
      h1_NoOsc_wTruthNeutron[3]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[3]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wTruthNeutron[3] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESp_wTrueN += OscProb;
    }
    //CC RES (Delta++)
    if (mode==11) {
      h1_NoOsc_wTruthNeutron[4]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[4]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wTruthNeutron[4] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESpp_wTrueN += OscProb;
    }
    //CC RES (Delta0)
    if (mode==12) {
      h1_NoOsc_wTruthNeutron[5]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[5]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wTruthNeutron[5] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRES0_wTrueN += OscProb;
    }
    //CC other
    if (mode>=14 && mode<=30) {
      h1_NoOsc_wTruthNeutron[6]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wTruthNeutron[6]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wTruthNeutron[6] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCOther_wTrueN += OscProb;
    }
  }
  return OscProb;
}


void NeutrinoOscillation::cdNeutrinoOscillation(TFile* fout) {
  fout -> mkdir("NeutrinoOscillation");
  fout -> cd("NeutrinoOscillation");
}

void NeutrinoOscillation::WritePlots() {
  h1_OscProbcheck -> Write();

  h1_AllEnutrue     -> Write();
  h1_AllEnureco     -> Write();
  h1_AllEnureso     -> Write();
  h2_Reso_x_TrueEnu -> Write();

  h1_All_NoOsc        -> Write();
  h1_All_OscProb      -> Write();
  h1_All_OscProbRatio -> Sumw2();
  h1_All_OscProbRatio -> Divide(h1_All_NoOsc);
  h1_All_OscProbRatio -> Write();

  h1_All_NoOsc_wTruthNeutron        -> Write();
  h1_All_OscProb_wTruthNeutron      -> Write();
  h1_All_OscProbRatio_wTruthNeutron -> Sumw2();
  h1_All_OscProbRatio_wTruthNeutron -> Divide(h1_All_NoOsc_wTruthNeutron);
  h1_All_OscProbRatio_wTruthNeutron -> Write();

  h1_All_NoOsc_woTruthNeutron        -> Write();
  h1_All_OscProb_woTruthNeutron      -> Write();
  h1_All_OscProbRatio_woTruthNeutron -> Sumw2();
  h1_All_OscProbRatio_woTruthNeutron -> Divide(h1_All_NoOsc_woTruthNeutron);
  h1_All_OscProbRatio_woTruthNeutron -> Write();

  h1_All_NoOsc_wNeutron        -> Write();
  h1_All_OscProb_wNeutron      -> Write();
  h1_All_OscProbRatio_wNeutron -> Sumw2();
  h1_All_OscProbRatio_wNeutron -> Divide(h1_All_NoOsc_wTruthNeutron);
  h1_All_OscProbRatio_wNeutron -> Write();

  h1_All_NoOsc_woNeutron        -> Write();
  h1_All_OscProb_woNeutron      -> Write();
  h1_All_OscProbRatio_woNeutron -> Sumw2();
  h1_All_OscProbRatio_woNeutron -> Divide(h1_All_NoOsc_woTruthNeutron);
  h1_All_OscProbRatio_woNeutron -> Write();

  for (int i=0; i<INTERACTIONTYPE; i++) {
  	h1_Enutrue[i] -> Write();
  	h1_Enureco[i] -> Write();
  	h1_Enureso[i] -> Write();

    h1_TruthOscProb[i]      -> Write();
    h1_TruthOscProbRatio[i] -> Write();

  	h1_NoOsc[i]        -> Write();
  	h1_OscProb[i]      -> Write();
  	h1_OscProbRatio[i] -> Sumw2();
  	h1_OscProbRatio[i] -> Divide(h1_NoOsc[i]);
  	h1_OscProbRatio[i] -> Write();

    h1_NoOsc_wTruthNeutron[i]        -> Write();
    h1_OscProb_wTruthNeutron[i]      -> Write();
    h1_OscProbRatio_wTruthNeutron[i] -> Sumw2();
    h1_OscProbRatio_wTruthNeutron[i] -> Divide(h1_NoOsc_woTruthNeutron[i]);
    h1_OscProbRatio_wTruthNeutron[i] -> Write();

    h1_NoOsc_woTruthNeutron[i]        -> Write();
    h1_OscProb_woTruthNeutron[i]      -> Write();
    h1_OscProbRatio_woTruthNeutron[i] -> Sumw2();
    h1_OscProbRatio_woTruthNeutron[i] -> Divide(h1_NoOsc_woTruthNeutron[i]);
    h1_OscProbRatio_woTruthNeutron[i] -> Write();

    h1_NoOsc_wNeutron[i]        -> Write();
    h1_OscProb_wNeutron[i]      -> Write();
    h1_OscProbRatio_wNeutron[i] -> Sumw2();
    h1_OscProbRatio_wNeutron[i] -> Divide(h1_NoOsc_wNeutron[i]);
    h1_OscProbRatio_wNeutron[i] -> Write();

    h1_NoOsc_woNeutron[i]        -> Write();
    h1_OscProb_woNeutron[i]      -> Write();
    h1_OscProbRatio_woNeutron[i] -> Sumw2();
    h1_OscProbRatio_woNeutron[i] -> Divide(h1_NoOsc_woNeutron[i]);
    h1_OscProbRatio_woNeutron[i] -> Write();

    h1_OscProb_mistag[i] -> Write();
  }

  h2_TrueMuDirectionXY -> Write();
  h2_TrueMuDirectionRZ -> Write();
  h2_RecoMuDirectionXY -> Write();
  h2_RecoMuDirectionRZ -> Write();
}
