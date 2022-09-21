#include "NeutrinoOscillation.h"
#include "TH1D.h"

void NeutrinoOscillation::SetHistoFrame() {

  h1_OscProbcheck = new TH1F("h1_OscProbcheck", "Oscillation Probability(numu->numu); Neutrino Events; Entries", 100, 0, 1);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    //numu
    h1_Enutrue[i] = new TH1F(TString::Format("h1_Enutrue_mode%d", i), "Truth Neutrino Energy; Truth Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0., 3.);
    h1_Enureco[i] = new TH1F(TString::Format("h1_Enureco_mode%d", i), "Reco. Neutrino Energy; Reconstructed Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_Enureso[i] = new TH1F(TString::Format("h1_Enureso_mode%d", i), "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);

    h1_TruthOscProb[i]       = new TH1F(TString::Format("h1_TruthOscProb_mode%d", i), "Oscillation Probability; Truth Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_NoOsc[i]              = new TH1F(TString::Format("h1_NoOsc_mode%d", i), "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_OscProb[i]            = new TH1F(TString::Format("h1_OscProb_mode%d", i), "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_OscProb_wNeutron[i]   = new TH1F(TString::Format("h1_OscProb_wNeutron_mode%d", i), "Oscillation Probability w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
    h1_OscProb_woNeutron[i]  = new TH1F(TString::Format("h1_OscProb_woNeutron_mode%d", i), "Oscillation Probability w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

    h1_OscProbRatio[i]       = new TH1F(TString::Format("h1_OscProbRatio_mode%d", i), "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  
    h1_Truecosthetamu[i] = new TH1F(TString::Format("h1_Truecosthetamu_mode%d", i), "Scattering angle; #mu Scattering Angle cos#theta_{#mu}; Number of Neutrino Events", 50, -1, 1);
  }

  //numu
  h1_AllEnutrue     = new TH1F("h1_AllEnutrue",  "Truth Neutrino Energy; Truth Neutrino Energy E^{true}_{#nu}[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_AllEnureco     = new TH1F("h1_AllEnureco",  "Truth Neutrino Energy; Reconstructed Neutrino Energy E^{reco}_{#nu}[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_AllEnureso     = new TH1F("h1_AllEnureso",  "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 50, -0.8, 0.8);
  h1_EnuresoCCnonQE = new TH1F("h1_EnuresoCCnonQE", "Neutrino Energy Resolution; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
 
  h2_Reso_x_TrueEnu = new TH2F("h2_Reso_x_TrueEnu", "Resolution vs Truth Neutrino Energy; Truth Neutrino Energy E^{true}_{#nu}[GeV]; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}", 60, 0, 3, 60, -1, 1);

  //numu
  h1_All_NoOsc                = new TH1F("h1_All_NoOsc", "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  //h1_NoOscCCOther             = new TH1F("h1_NoOscCCOther", "No Oscillation; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_NoOsc_woTruthNeutron = new TH1F("h1_All_NoOsc_woTruthNeutron", "No Oscillation w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_All_NoOsc_woNeutron      = new TH1F("h1_All_NoOsc_woNeutron", "No Oscillation w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

  h1_All_OscProbRatio                = new TH1F("h1_All_OscProbRatio", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}); Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_All_OscProbRatio_woTruthNeutron = new TH1F("h1_All_OscProbRatio_woTruthNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Truth Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_All_OscProbRatio_woNeutron      = new TH1F("h1_All_OscProbRatio_woNeutron", "Oscillation Probability(#nu_{#mu}#rightarrow#nu_{#mu}) w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Ratio to No Oscillation", 60, 0, 3);
  h1_OscProbCCOther                  = new TH1F("h1_OscProbCCOther", "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_OscProbCCnonQE                  = new TH1F("h1_OscProbCCnonQE", "Oscillation Probability; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_OscProbCCOther_wNeutron         = new TH1F("h1_OscProbCCOther_wNeutron", "Oscillation Probability w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_OscProbCCOther_woNeutron        = new TH1F("h1_OscProbCCOther_woNeutron", "Oscillation Probability w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_OscProbCCnonQE_wNeutron         = new TH1F("h1_OscProbCCnonQE_wNeutron", "Oscillation Probability w/ Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  h1_OscProbCCnonQE_woNeutron        = new TH1F("h1_OscProbCCnonQE_woNeutron", "Oscillation Probability w/o Tagged Neutrons; Reconstructed Neurtino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);

  h2_TrueMuDirectionXY = new TH2F("h2_TrueMuDirectionXY", "Truth Dir; X #mu direction; Y #mu direction ", 100, -1, 1, 100, -1, 1);
  h2_TrueMuDirectionRZ = new TH2F("h2_TrueMuDirectionRZ", "Truth Dir; R^{2} #mu direction; Z #mu direction ", 100, 0, 2, 100, -1, 1);
  h2_RecoMuDirectionXY = new TH2F("h2_RecoMuDirectionXY", "fq1rdir; X #mu direction; Y #mu direction ", 100, -1, 1, 100, -1, 1);
  h2_RecoMuDirectionRZ = new TH2F("h2_RecoMuDirectionRZ", "fq1rdir; R^{2} #mu direction; Z #mu direction ", 100, 0, 2, 100, -1, 1);
  
  //h1_Truecosthetamu = new TH1F("h1_Truecosthetamu", "Scattering angle; #mu Scattering Angle cos#theta_{#mu}; Number of Neutrino Events", 50, -1, 1);
  h1_Recocosthetamu = new TH1F("h1_Recocosthetamu", "Scattering angle; #mu Scattering Angle cos#theta_{#mu}; Number of Neutrino Events", 50, -1, 1);
  h1_Resocosthetamu = new TH1F("h1_Resocosthetamu", "Scattering angle resolution; (cos#theta_{#mu}^{true}-cos#theta_{#mu}^{reco})/cos#theta_{#mu}^{true}; Number of Neutrino Events", 50, -1, 1);
  h1_EnuRecoPrediction = new TH1F("h1_EnuRecoPrediction", "Reco. Neutrino Energy; Reconstructed Neutrino Energy E_{#nu}^{reco}; Number of Neutrino Events", 60, 0, 3);
  h1_EnuResoPrediction = new TH1F("h1_EnuResoPrediction", "Predicted Neutrino Energy Resolution; (E^{true}_{#nu}-E^{predict}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
  h2_pmu_x_costhetamu = new TH2F("h2_pmu_x_costhetamu", "; Truth #mu Momentum p_{#mu}[MeV]; Truth #mu Scattering Angle cos#theta_{#mu}", 100, 0, 1000, 50, -1, 1);
  h2_EnuReso_x_costhetamu = new TH2F("h2_EnuReso_x_costhetamu", "; Truth #mu Scattering Angle cos#theta_{#mu}; (E^{true}_{#nu}-E^{predict}_{#nu})/E^{true}_{#nu} ", 50, -1, 1, 50, -1, 1);
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

    h1_OscProb[i]           -> SetLineWidth(2);
    h1_OscProb_wNeutron[i]  -> SetLineWidth(2);
    h1_OscProb_woNeutron[i] -> SetLineWidth(2);

    h1_OscProbRatio[i]      -> SetLineWidth(2);

    h1_Truecosthetamu[i] -> SetLineWidth(2);
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

  h1_OscProb[0] -> SetLineColor(kAzure-1);
  h1_OscProb[1] -> SetLineColor(kAzure-5);
  h1_OscProb[2] -> SetLineColor(kTeal+9);
  h1_OscProb[3] -> SetLineColor(kPink+1);
  h1_OscProb[4] -> SetLineColor(kPink-8);
  h1_OscProb[5] -> SetLineColor(kGray+1);
  h1_OscProb[6] -> SetLineColor(kCyan-6);
  h1_OscProbCCOther -> SetLineColor(kCyan-8);
  h1_OscProbCCnonQE -> SetLineColor(kCyan-8);

  h1_OscProb[0] -> SetFillColor(kAzure-1);
  h1_OscProb[1] -> SetFillColor(kAzure-5);
  h1_OscProb[2] -> SetFillColor(kTeal+9);
  h1_OscProb[3] -> SetFillColor(kPink+1);
  h1_OscProb[4] -> SetFillColor(kPink-8);
  h1_OscProb[5] -> SetFillColor(kGray+1);
  h1_OscProb[6] -> SetFillColor(kCyan-6);
  h1_OscProbCCOther -> SetFillColor(kCyan-8);
  h1_OscProbCCnonQE -> SetFillColor(kCyan-8);
  

  h1_OscProb_wNeutron[0] -> SetLineColor(kAzure-1);
  h1_OscProb_wNeutron[1] -> SetLineColor(kAzure-5);
  h1_OscProb_wNeutron[2] -> SetLineColor(kTeal+9);
  h1_OscProb_wNeutron[3] -> SetLineColor(kPink+1);
  h1_OscProb_wNeutron[4] -> SetLineColor(kPink-8);
  h1_OscProb_wNeutron[5] -> SetLineColor(kGray+1);
  h1_OscProb_wNeutron[6] -> SetLineColor(kCyan-6);
  h1_OscProbCCOther_wNeutron -> SetLineColor(kCyan-8);
  h1_OscProbCCnonQE_wNeutron -> SetLineColor(kCyan-8);

  h1_OscProb_wNeutron[0] -> SetFillColor(kAzure-1);
  h1_OscProb_wNeutron[1] -> SetFillColor(kAzure-5);
  h1_OscProb_wNeutron[2] -> SetFillColor(kTeal+9);
  h1_OscProb_wNeutron[3] -> SetFillColor(kPink+1);
  h1_OscProb_wNeutron[4] -> SetFillColor(kPink-8);
  h1_OscProb_wNeutron[5] -> SetFillColor(kGray+1);
  h1_OscProb_wNeutron[6] -> SetFillColor(kCyan-6);
  h1_OscProbCCOther_wNeutron -> SetFillColor(kCyan-8);
  h1_OscProbCCnonQE_wNeutron -> SetFillColor(kCyan-8);

  h1_OscProb_woNeutron[0] -> SetLineColor(kAzure-1);
  h1_OscProb_woNeutron[1] -> SetLineColor(kAzure-5);
  h1_OscProb_woNeutron[2] -> SetLineColor(kTeal+9);
  h1_OscProb_woNeutron[3] -> SetLineColor(kPink+1);
  h1_OscProb_woNeutron[4] -> SetLineColor(kPink-8);
  h1_OscProb_woNeutron[5] -> SetLineColor(kGray+1);
  h1_OscProb_woNeutron[6] -> SetLineColor(kCyan-6);
  h1_OscProbCCOther_woNeutron -> SetLineColor(kCyan-8);
  h1_OscProbCCnonQE_woNeutron -> SetLineColor(kCyan-8);

  h1_OscProb_woNeutron[0] -> SetFillColor(kAzure-1);
  h1_OscProb_woNeutron[1] -> SetFillColor(kAzure-5);
  h1_OscProb_woNeutron[2] -> SetFillColor(kTeal+9);
  h1_OscProb_woNeutron[3] -> SetFillColor(kPink+1);
  h1_OscProb_woNeutron[4] -> SetFillColor(kPink-8);
  h1_OscProb_woNeutron[5] -> SetFillColor(kGray+1);
  h1_OscProb_woNeutron[6] -> SetFillColor(kCyan-6);
  h1_OscProbCCOther_woNeutron -> SetFillColor(kCyan-8);
  h1_OscProbCCnonQE_woNeutron -> SetFillColor(kCyan-8);

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

  h1_Truecosthetamu[0] -> SetLineColor(kAzure-1);
  h1_Truecosthetamu[1] -> SetLineColor(kAzure-5);
  h1_Truecosthetamu[2] -> SetLineColor(kTeal+9);
  h1_Truecosthetamu[3] -> SetLineColor(kPink+1);
  h1_Truecosthetamu[4] -> SetLineColor(kPink-8);
  h1_Truecosthetamu[5] -> SetLineColor(kGray+1);
  h1_Truecosthetamu[6] -> SetLineColor(kCyan-6);

  h1_Truecosthetamu[0] -> SetFillColor(kAzure-1);
  h1_Truecosthetamu[1] -> SetFillColor(kAzure-5);
  h1_Truecosthetamu[2] -> SetFillColor(kTeal+9);
  h1_Truecosthetamu[3] -> SetFillColor(kPink+1);
  h1_Truecosthetamu[4] -> SetFillColor(kPink-8);
  h1_Truecosthetamu[5] -> SetFillColor(kGray+1);
  h1_Truecosthetamu[6] -> SetFillColor(kCyan-6);

  h2_Reso_x_TrueEnu -> SetStats(0);

  h2_TrueMuDirectionXY -> SetStats(0);
  h2_TrueMuDirectionRZ -> SetStats(0);
  h2_RecoMuDirectionXY -> SetStats(0);
  h2_RecoMuDirectionRZ -> SetStats(0);

  //h1_Truecosthetamu -> SetLineColor(kAzure+5);
  //h1_Truecosthetamu -> SetLineWidth(2);

  h1_Recocosthetamu -> SetLineColor(kAzure+5);
  h1_Recocosthetamu -> SetLineWidth(2);

  h1_Resocosthetamu -> SetLineColor(kAzure+5);
  h1_Resocosthetamu -> SetLineWidth(2);

  h1_EnuRecoPrediction -> SetLineColor(kAzure+5);
  h1_EnuRecoPrediction -> SetLineWidth(2);

  h1_EnuResoPrediction -> SetLineColor(kAzure+5);
  h1_EnuResoPrediction -> SetLineWidth(2);

  h2_pmu_x_costhetamu -> SetStats(0);
  h2_EnuReso_x_costhetamu -> SetStats(0);
}


float NeutrinoOscillation::GetTrueEnu(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float Enu = numu->var<float>("pnu", 0);
  h1_AllEnutrue -> Fill(Enu);

  //CCQE(1p1h)
  if (mode==1) h1_Enutrue[0] -> Fill(Enu);

  //CC non-QE
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
  float Enu = numu->var<float>("erec");
  h1_AllEnureco -> Fill(Enu/1000.);

  //CCQE(1p1h)
  if (mode==1) h1_Enureco[0] -> Fill(Enu/1000.);

  //CC non-QE
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

float NeutrinoOscillation::GetEnuResolution(CC0PiNumu* numu, float theta, float thetamin, float thetamax) {

  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;

  //See energy resolution at oscillation maximum
  if (theta>thetamin && theta<thetamax && RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {

    if (mode<31) h1_AllEnureso -> Fill(EnuReso);

    //CC non-QE
    if (mode>=2 && mode<=30) h1_EnuresoCCnonQE -> Fill(EnuReso);

    //CCQE(1p1h)
    if (mode==1) h1_Enureso[0] -> Fill(EnuReso);

    //CC 2p2h
    if (mode>=2 && mode<=10) h1_Enureso[1] -> Fill(EnuReso);

    //CC RES (Delta+)
    if (mode==13) h1_Enureso[3] -> Fill(EnuReso);
    //CC RES (Delta++)
    if (mode==11) h1_Enureso[4] -> Fill(EnuReso);
    //CC RES (Delta0)
    if (mode==12) h1_Enureso[5] -> Fill(EnuReso);

    //CC other
    if (mode>=14 && mode<=30) h1_Enureso[6] -> Fill(EnuReso);

    //NC
    if (mode>=31) {
      h1_AllEnureso -> Fill(EnuReso);
      h1_Enureso[2] -> Fill(EnuReso);
    }
  }

  return EnuReso;
}

void NeutrinoOscillation::GetReso_x_TrueEnu(CC0PiNumu* numu) {
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;
  h2_Reso_x_TrueEnu -> Fill(TrueEnu, EnuReso);
}


float NeutrinoOscillation::GetTrueMuDirection(CC0PiNumu* numu, 
                                              Int_t   Npvc, 
                                              Int_t*  Ipvc,
                                              Float_t Pvc[][3],
                                              Int_t*  Iflvc,
                                              Int_t*  Ichvc) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  
  //Truth muon scattering angle
  float costhetamu = 0.;

  //CC
  //if (mode < 31) {
    //Truth neutrino direction
    Float_t numomx = Pvc[0][0];
    Float_t numomy = Pvc[0][1];
    Float_t numomz = Pvc[0][2];
    Float_t numom  = std::sqrt(numomx*numomx + numomy*numomy + numomz*numomz);

    //Direction vector [mudirx, mudiry, mudirz]
    Float_t nudirx = numomx/numom;
    Float_t nudiry = numomy/numom;
    Float_t nudirz = numomz/numom;
    //std::cout << "nudir = [" << nudirx << ", " << nudiry << ", " << nudirz << "]" << std::endl;


    //Truth muon direction
    //Truth primary particles loop
    for (Int_t iprm=0; iprm<Npvc; iprm++) {

      //Truth muon from mu-neutrino
      if (std::abs(Ipvc[iprm])==13 && Ichvc[iprm]==1) {

        //Momentum
        Float_t mumomx = Pvc[iprm][0];
        Float_t mumomy = Pvc[iprm][1];
        Float_t mumomz = Pvc[iprm][2];
        Float_t mumom  = std::sqrt(mumomx*mumomx + mumomy*mumomy + mumomz*mumomz);

        //Direction vector [mudirx, mudiry, mudirz]
        Float_t mudirx = mumomx/mumom;
        Float_t mudiry = mumomy/mumom;
        Float_t mudirz = mumomz/mumom;
        Float_t mudirR = sqrt( mudirx*mudirx + mudiry*mudiry );

        //Tree
        TrueMuDirX = mudirx;
        TrueMuDirY = mudiry;
        TrueMuDirZ = mudirz;

        h2_TrueMuDirectionXY -> Fill(mudirx, mudiry);
        h2_TrueMuDirectionRZ -> Fill(mudirR, mudirz);

        //muon scattering angle
        Float_t InnerProduct = nudirx*mudirx + nudiry*mudiry + nudirz*mudirz;
        Float_t nudir = std::sqrt(nudirx*nudirx + nudiry*nudiry + nudirz*nudirz); //should be 1
        Float_t mudir = std::sqrt(mudirx*mudirx + mudiry*mudiry + mudirz*mudirz); //should be 1
        //std::cout << "nudir: " << nudir << ", mudir: " << mudir << std::endl;
        costhetamu = InnerProduct/(nudir * mudir);

        //h1_Truecosthetamu -> Fill(costhetamu);
        if (mode==1) h1_Truecosthetamu[0] -> Fill(costhetamu);
        if (mode>=2 && mode<=10) h1_Truecosthetamu[1] -> Fill(costhetamu);
        if (mode>=31) h1_Truecosthetamu[2] -> Fill(costhetamu);
        if (mode==13) h1_Truecosthetamu[3] -> Fill(costhetamu);
        if (mode==11) h1_Truecosthetamu[4] -> Fill(costhetamu);
        if (mode==12) h1_Truecosthetamu[5] -> Fill(costhetamu);
        if (mode>=14 && mode<=30) h1_Truecosthetamu[6] -> Fill(costhetamu);

        //Extract only CCQE(1p1h)
        //int mode = TMath::Abs(numu->var<int>("mode"));
        if (mode==1) {
        //if (mode>=2 && mode<=30) {
          float Enu     = this->GetEnuRecoPrediction(mumom, costhetamu);
          float EnuReso = this->GetEnuResoPrediction(numu, Enu);

          h2_pmu_x_costhetamu     -> Fill(mumom, costhetamu);
          h2_EnuReso_x_costhetamu -> Fill(costhetamu, EnuReso);
        }
      }
    }
  //}
  
  return costhetamu;
}

float NeutrinoOscillation::GetEnuRecoPrediction(float pmu, float costhetamu) {
  //Parameters
  float mp  = 938.272; // MeV : Proton mass
  float mn  = 939.565; // MeV : Neutron mass
  float mmu = 105.658; // MeV : muon mass
  float Eb  =     27.; // MeV : Mean binding energy of O16

  float Emu = std::sqrt(pmu*pmu + mmu*mmu); // MeV : muon energy

  //Predicted(Pseudo-reco) neutrino energy
  float Enu = (mp*mp - (mn - Eb)*(mn - Eb) - mmu*mmu + 2*(mn - Eb)*Emu) / (2*(mn - Eb - Emu + pmu*costhetamu));

  h1_EnuRecoPrediction -> Fill(Enu/1000.);

  return Enu;
}

float NeutrinoOscillation::GetEnuResoPrediction(CC0PiNumu* numu, float Enu) {
  float TrueEnu = numu->var<float>("pnu", 0);    // GeV
  float EnuReso = (TrueEnu - Enu/1000.)/TrueEnu;

  h1_EnuResoPrediction -> Fill(EnuReso);

  return EnuReso;
}

float NeutrinoOscillation::GetRecoMuDirection(CC0PiNumu* numu) {

  //Reconstructed muon scattering angle
  float costhetamu = 0.;

  //Reco neutrino direction
  float nudirx = beamDir[0];
  float nudiry = beamDir[1];
  float nudirz = beamDir[2];
  //std::cout << "nudir = [" << nudirx << ", " << nudiry << ", " << nudirz << "]" << std::endl;

  //Reco muon direction vector
  //muon hypothesis
  float mudirx = numu->var<float>("fq1rdir", 0, 2, 0);
  float mudiry = numu->var<float>("fq1rdir", 0, 2, 1);
  float mudirz = numu->var<float>("fq1rdir", 0, 2, 2);
  float mudirR = sqrt( mudirx*mudirx + mudiry*mudiry );

  //Tree
  RecoMuDirX = mudirx;
  RecoMuDirY = mudiry;
  RecoMuDirZ = mudirz;

  h2_RecoMuDirectionXY -> Fill(mudirx, mudiry);
  h2_RecoMuDirectionRZ -> Fill(mudirR, mudirz);

  //muon scattering angle
  float InnerProduct = nudirx*mudirx + nudiry*mudiry + nudirz*mudirz;
  float nudir = std::sqrt(nudirx*nudirx + nudiry*nudiry + nudirz*nudirz);  //should be 1
  float mudir = std::sqrt(mudirx*mudirx + mudiry*mudiry + mudirz*mudirz);  //should be 1
  costhetamu = InnerProduct/(nudir * mudir);
  h1_Recocosthetamu -> Fill(costhetamu);

  return costhetamu;
}

float NeutrinoOscillation::GetMuDirResolution(float truecostheta, float recocostheta) {
  float thetareso = (truecostheta - recocostheta)/truecostheta;
  h1_Resocosthetamu -> Fill(thetareso);

  return thetareso;
}



float NeutrinoOscillation::OscProbCalculator(CC0PiNumu* numu, bool histfill) {
  float OscProb = numu->getOscWgt();
  if (histfill==true) h1_OscProbcheck -> Fill(OscProb);
  return OscProb;
}

float NeutrinoOscillation::GetWgtNeutrino(CC0PiNumu* numu, float theta, float thetamin, float thetamax) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");

  if (theta>thetamin && theta<thetamax) {

    //All CC
    if (mode<31) {
      //### [CATEGORY: Selected 1R muon events(before NTag)] ###
      h1_All_NoOsc        -> Fill(RecoEnu/1000.);
      h1_All_OscProbRatio -> Fill(RecoEnu/1000., OscProb);

      //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
        NoOscLegacy++;
        OscLegacy += OscProb;
      }
    }

    //NC
    if (mode>=31) {

      //### [CATEGORY: Selected 1R muon events(before NTag)] ###
      h1_All_NoOsc        -> Fill(RecoEnu/1000.);
      h1_All_OscProbRatio -> Fill(RecoEnu/1000.);

      //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
        NoOscLegacy++;
        OscLegacy++;

        OscillatedNC++;
      }

      h1_TruthOscProb[2] -> Fill(TrueEnu);

      h1_NoOsc[2]        -> Fill(RecoEnu/1000.);
      h1_OscProb[2]      -> Fill(RecoEnu/1000.);
      h1_OscProbRatio[2] -> Fill(RecoEnu/1000.);
    }

  
    //CCQE(1p1h)
    if (mode==1) {
      h1_TruthOscProb[0]      -> Fill(TrueEnu, OscProb);

      h1_NoOsc[0]        -> Fill(RecoEnu/1000.);
      h1_OscProb[0]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio[0] -> Fill(RecoEnu/1000., OscProb);

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCQE += OscProb;

      //### [CATEGORY: Only CCQE signal(before NTag)] ###
      //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
        NoOscOnlyCCQE++;
        OscOnlyCCQE += OscProb;
      }
    }

    //CC 2p2h
    if (mode>=2 && mode<=10) {
      h1_TruthOscProb[1]      -> Fill(TrueEnu, OscProb);

      h1_NoOsc[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio[1] -> Fill(RecoEnu/1000., OscProb);

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCnonQE += OscProb;
    }

    //CC non-QE
    if (mode>=2 && mode<=30) {
      h1_OscProbCCnonQE -> Fill(RecoEnu/1000., OscProb);
    }

    //CC other
    if (mode>10 && mode<=30) {
      //h1_NoOscCCOther   -> Fill(RecoEnu/1000.);
      h1_OscProbCCOther -> Fill(RecoEnu/1000., OscProb);
    }

    //CC RES (Delta+)
    if (mode==13) {
      h1_TruthOscProb[3]      -> Fill(TrueEnu, OscProb);

      h1_NoOsc[3]        -> Fill(RecoEnu/1000.);
      h1_OscProb[3]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio[3] -> Fill(RecoEnu/1000., OscProb);

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRESp += OscProb;
    }
    //CC RES (Delta++)
    if (mode==11) {
      h1_TruthOscProb[4]      -> Fill(TrueEnu, OscProb);

      h1_NoOsc[4]        -> Fill(RecoEnu/1000.);
      h1_OscProb[4]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio[4] -> Fill(RecoEnu/1000., OscProb);

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRESpp += OscProb;
    }
    //CC RES (Delta0)
    if (mode==12) {
      h1_TruthOscProb[5]      -> Fill(TrueEnu, OscProb);

      h1_NoOsc[5]        -> Fill(RecoEnu/1000.);
      h1_OscProb[5]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio[5] -> Fill(RecoEnu/1000., OscProb);

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRES0 += OscProb;
    }
    //CC other
    if (mode>=14 && mode<=30) {
      h1_TruthOscProb[6]      -> Fill(TrueEnu, OscProb);

      h1_NoOsc[6]        -> Fill(RecoEnu/1000.);
      h1_OscProb[6]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio[6] -> Fill(RecoEnu/1000., OscProb);

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCOther += OscProb;
    }

  } //muon angle cut

  return OscProb;
}


float NeutrinoOscillation::GetWgtNeutrino_wTrueN(CC0PiNumu* numu, float NTrueN, float theta, float thetamin, float thetamax) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  float RecoEnu = numu->var<float>("erec");

  if (theta>thetamin && theta<thetamax) {
    if (NTrueN==0) {

      //All CC
      if (mode<31) {
        //### [CATEGORY: w/o truth neutrons] ###
        h1_All_NoOsc_woTruthNeutron        -> Fill(RecoEnu/1000.);
        h1_All_OscProbRatio_woTruthNeutron -> Fill(RecoEnu/1000., OscProb);

        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          NoOscwoTrueN++;
          OscwoTrueN += OscProb;
        }
      }
      

      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
        //CCQE(1p1h)
        if (mode==1) OscillatedCCQE_woTrueN += OscProb;

        //CC non-QE
        if (mode>=2 && mode<=10) OscillatedCCnonQE_woTrueN += OscProb;

        //CC RES (Delta+)
        if (mode==13) OscillatedCCRESp_woTrueN += OscProb;
        //CC RES (Delta++)
        if (mode==11) OscillatedCCRESpp_woTrueN += OscProb;
        //CC RES (Delta0)
        if (mode==12) OscillatedCCRES0_woTrueN += OscProb;
        //CC other
        if (mode>=14 && mode<=30) OscillatedCCOther_woTrueN += OscProb;
      }
    }
    else {
      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
        //CCQE(1p1h)
        if (mode==1) OscillatedCCQE_wTrueN += OscProb;

        //CC non-QE
        if (mode>=2 && mode<=10) OscillatedCCnonQE_wTrueN += OscProb;

        //CC RES (Delta+)
        if (mode==13) OscillatedCCRESp_wTrueN += OscProb;
        //CC RES (Delta++)
        if (mode==11) OscillatedCCRESpp_wTrueN += OscProb;
        //CC RES (Delta0)
        if (mode==12) OscillatedCCRES0_wTrueN += OscProb;
        //CC other
        if (mode>=14 && mode<=30) OscillatedCCOther_wTrueN += OscProb;
      }
    }


    //NC
    if (mode>=31) {

      if (NTrueN==0) {
        //### [CATEGORY: w/o truth neutrons] ###
        h1_All_NoOsc_woTruthNeutron        -> Fill(RecoEnu/1000.);
        h1_All_OscProbRatio_woTruthNeutron -> Fill(RecoEnu/1000.);

        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          NoOscwoTrueN++;
          OscwoTrueN ++;

          OscillatedNC_woTrueN++;
        }
      }
      else {
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedNC_wTrueN++;
      }
    }

  } //muon angle cut

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
  h1_EnuresoCCnonQE -> Write();

  h1_All_OscProbRatio -> Sumw2();
  h1_All_OscProbRatio -> Divide(h1_All_NoOsc);
  h1_All_OscProbRatio -> Write();

  h1_All_OscProbRatio_woTruthNeutron -> Sumw2();
  h1_All_OscProbRatio_woTruthNeutron -> Divide(h1_All_NoOsc_woTruthNeutron);
  h1_All_OscProbRatio_woTruthNeutron -> Write();

  h1_All_OscProbRatio_woNeutron -> Sumw2();
  h1_All_OscProbRatio_woNeutron -> Divide(h1_All_NoOsc_woNeutron);
  h1_All_OscProbRatio_woNeutron -> Write();

  for (int i=0; i<INTERACTIONTYPE; i++) {
  	h1_Enutrue[i] -> Write();
  	h1_Enureco[i] -> Write();
  	h1_Enureso[i] -> Write();

    h1_TruthOscProb[i]      -> Write();

  	h1_OscProb[i]      -> Write();
  	h1_OscProbRatio[i] -> Sumw2();
  	h1_OscProbRatio[i] -> Divide(h1_NoOsc[i]);
  	h1_OscProbRatio[i] -> Write();

    h1_OscProb_wNeutron[i]      -> Write();
    h1_OscProb_woNeutron[i]      -> Write();

    h1_Truecosthetamu[i] -> Write();
  }
  h1_OscProbCCnonQE -> Write();
  h1_OscProbCCOther -> Write();
  h1_OscProbCCnonQE_wNeutron  -> Write();
  h1_OscProbCCnonQE_woNeutron -> Write();
  h1_OscProbCCOther_wNeutron  -> Write();
  h1_OscProbCCOther_woNeutron -> Write();

  h2_TrueMuDirectionXY -> Write();
  h2_TrueMuDirectionRZ -> Write();
  h2_RecoMuDirectionXY -> Write();
  h2_RecoMuDirectionRZ -> Write();

  //h1_Truecosthetamu -> Write();
  h1_Recocosthetamu -> Write();
  h1_Resocosthetamu -> Write();
  h1_EnuRecoPrediction -> Write();
  h1_EnuResoPrediction -> Write();
  h2_pmu_x_costhetamu -> Write();
  h2_EnuReso_x_costhetamu -> Write();
}
