#include "NTagAnalysis.h"
#include "../../DecayeBox/inc/DecayeBox.h"
#include "../../NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "../../../include/NeutrinoEvents.h"

void NTagAnalysis::SetHistoFrame() {
  for (int i=0; i<TRUETYPE; i++) {
    h1_NTrueN[i] = new TH1F(TString::Format("h1_NTrueN_type%d", i), "Truth Capture Neutrons; NTrueN; Entries", 20, 0, 20);
  }
  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueNmultiplicity[i] = new TH1F(TString::Format("h1_TrueNmultiplicity_mode%d", i), "Truth Capture Neutrons; NTrueN; Entries", 20, 0, 20);
  }
  h1_TotGammaE   = new TH1F("h1_TotGammaE", "Truth Total Gamma Energy; E[MeV]; Entries", 20, 0, 10);
  for (int i=0; i<2; i++) {
    if (i==0) {
      h1_Enureso_CCQE[i]          = new TH1F("h1_Enureso_CCQE_woNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCnonQE[i]       = new TH1F("h1_Enureso_CCnonQE_woNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap[i]  = new TH1F("h1_Enureso_CCRESdeltap_woNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp[i] = new TH1F("h1_Enureso_CCRESdeltapp_woNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0[i]  = new TH1F("h1_Enureso_CCRESdelta0_woNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC[i]            = new TH1F("h1_Enureso_NC_woNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);

      h1_Enureso_CCQE_trueN[i]          = new TH1F("h1_Enureso_CCQE_wotrueNeutrons", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCnonQE_trueN[i]       = new TH1F("h1_Enureso_CCnonQE_wotrueNeutrons", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap_trueN[i]  = new TH1F("h1_Enureso_CCRESdeltap_wotrueNeutrons", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp_trueN[i] = new TH1F("h1_Enureso_CCRESdeltapp_wotrueNeutrons", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0_trueN[i]  = new TH1F("h1_Enureso_CCRESdelta0_wotrueNeutrons", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC_trueN[i]            = new TH1F("h1_Enureso_NC_wotrueNeutrons", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
    }
    if (i==1) {
      h1_Enureso_CCQE[i]          = new TH1F("h1_Enureso_CCQE_wNeutrons", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCnonQE[i]       = new TH1F("h1_Enureso_CCnonQE_wNeutrons", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap[i]  = new TH1F("h1_Enureso_CCRESdeltap_wNeutrons", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp[i] = new TH1F("h1_Enureso_CCRESdeltapp_wNeutrons", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0[i]  = new TH1F("h1_Enureso_CCRESdelta0_wNeutrons", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC[i]            = new TH1F("h1_Enureso_NC_wNeutrons", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);

      h1_Enureso_CCQE_trueN[i]          = new TH1F("h1_Enureso_CCQE_wtrueNeutrons", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCnonQE_trueN[i]       = new TH1F("h1_Enureso_CCnonQE_wtrueNeutrons", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap_trueN[i]  = new TH1F("h1_Enureso_CCRESdeltap_wtrueNeutrons", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp_trueN[i] = new TH1F("h1_Enureso_CCRESdeltapp_wtrueNeutrons", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0_trueN[i]  = new TH1F("h1_Enureso_CCRESdelta0_wtrueNeutrons", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC_trueN[i]            = new TH1F("h1_Enureso_NC_wtrueNeutrons", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
    }
  }
}

void NTagAnalysis::SetHistoFormat() {
  for (int i=0; i<TRUETYPE; i++) {
    h1_NTrueN[i] -> SetLineWidth(2);
    h1_NTrueN[i] -> SetTitleOffset(1.4, "Y");
    h1_NTrueN[i] -> SetTitleSize(0.035, "Y");
    h1_NTrueN[i] -> SetLabelSize(0.033, "Y");
  }
  h1_NTrueN[0] -> SetLineColor(kViolet+3); //All truth neutrons
  h1_NTrueN[1] -> SetLineColor(kAzure-4);  //truth H-n neutrons
  h1_NTrueN[2] -> SetLineColor(kTeal-5);   //truth Gd-n neutrons

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueNmultiplicity[i] -> SetLineWidth(2);
    h1_TrueNmultiplicity[i] -> SetTitleOffset(1.4, "Y");
    h1_TrueNmultiplicity[i] -> SetTitleSize(0.035, "Y");
    h1_TrueNmultiplicity[i] -> SetLabelSize(0.033, "Y");
  }
  h1_TrueNmultiplicity[0] -> SetLineColor(kAzure-1);  //CCQE
  h1_TrueNmultiplicity[1] -> SetLineColor(kOrange+8); //CC non-QE
  h1_TrueNmultiplicity[2] -> SetLineColor(kPink+1);   //CCRES+
  h1_TrueNmultiplicity[3] -> SetLineColor(kPink-8);   //CCRES++
  h1_TrueNmultiplicity[4] -> SetLineColor(kGray+1);   //CCRES0
  h1_TrueNmultiplicity[5] -> SetLineColor(kTeal+9);   //NC

  h1_TotGammaE -> SetLineWidth(2);
  h1_TotGammaE -> SetLineColor(kAzure-4);
  h1_TotGammaE -> SetTitleOffset(1.4, "Y");
  h1_TotGammaE -> SetTitleSize(0.035, "Y");
  h1_TotGammaE -> SetLabelSize(0.033, "Y");

  for (int i=0; i<2; i++) {
    h1_Enureso_CCQE[i]          -> SetLineWidth(2);
    h1_Enureso_CCnonQE[i]       -> SetLineWidth(2);
    h1_Enureso_CCRES_deltap[i]  -> SetLineWidth(2);
    h1_Enureso_CCRES_deltapp[i] -> SetLineWidth(2);
    h1_Enureso_CCRES_delta0[i]  -> SetLineWidth(2);
    h1_Enureso_NC[i]            -> SetLineWidth(2);

    h1_Enureso_CCQE[i]          -> SetLineColor(kAzure-1);
    h1_Enureso_CCnonQE[i]       -> SetLineColor(kOrange+8);
    h1_Enureso_CCRES_deltap[i]  -> SetLineColor(kPink+1);
    h1_Enureso_CCRES_deltapp[i] -> SetLineColor(kPink-8);
    h1_Enureso_CCRES_delta0[i]  -> SetLineColor(kGray+1);
    h1_Enureso_NC[i]            -> SetLineColor(kTeal+9);

    h1_Enureso_CCQE_trueN[i]          -> SetLineWidth(2);
    h1_Enureso_CCnonQE_trueN[i]       -> SetLineWidth(2);
    h1_Enureso_CCRES_deltap_trueN[i]  -> SetLineWidth(2);
    h1_Enureso_CCRES_deltapp_trueN[i] -> SetLineWidth(2);
    h1_Enureso_CCRES_delta0_trueN[i]  -> SetLineWidth(2);
    h1_Enureso_NC_trueN[i]            -> SetLineWidth(2);

    h1_Enureso_CCQE_trueN[i]          -> SetLineColor(kAzure-1);
    h1_Enureso_CCnonQE_trueN[i]       -> SetLineColor(kOrange+8);
    h1_Enureso_CCRES_deltap_trueN[i]  -> SetLineColor(kPink+1);
    h1_Enureso_CCRES_deltapp_trueN[i] -> SetLineColor(kPink-8);
    h1_Enureso_CCRES_delta0_trueN[i]  -> SetLineColor(kGray+1);
    h1_Enureso_NC_trueN[i]            -> SetLineColor(kTeal+9);
  }
}


void NTagAnalysis::InitNeutrons() {
  AllTruthNeutrons     = 0;
  TruthHNeutrons       = 0;
  TruthGdNeutrons      = 0;
  AllTruthNeutronsinFV = 0;
  TruthHNeutronsinFV   = 0;
  TruthGdNeutronsinFV  = 0;

  PreEff   = 0.;
  PreHEff  = 0.;
  PreGdEff = 0.;

  PreEffinFV   = 0.;
  PreHEffinFV  = 0.;
  PreGdEffinFV = 0.;

  for (int i=0; i<WINSTEP; i++) {
    AllTruthNeutronsinSearch[i] = 0;
    TruthHNeutronsinSearch[i]   = 0;
    TruthGdNeutronsinSearch[i]  = 0;

    AllTruthNeutronsinSearchFV[i] = 0;
    TruthHNeutronsinSearchFV[i]   = 0;
    TruthGdNeutronsinSearchFV[i]  = 0;

    TruthDecayeinSearch[i]   = 0;

    AllCandidatesinWin[i]              = 0;
    TruthNeutroninCandidatesinWin[i]   = 0;
    TruthHNeutroninCandidatesinWin[i]  = 0;
    TruthGdNeutroninCandidatesinWin[i] = 0;
    TruthDecayeinCandidatesinWin[i]    = 0;
    TruthAccNoiseinCandidatesinWin[i]  = 0;

    AllCandidatesinWinFV[i]              = 0;
    TruthNeutroninCandidatesinWinFV[i]   = 0;
    TruthHNeutroninCandidatesinWinFV[i]  = 0;
    TruthGdNeutroninCandidatesinWinFV[i] = 0;
    TruthDecayeinCandidatesinWinFV[i]    = 0;
    TruthAccNoiseinCandidatesinWinFV[i]  = 0;

    for (int j=0; j<CUTSTEP; j++) {
      TaggedTruthNeutronsinWin[i][j]   = 0;
      TaggedTruthHNeutronsinWin[i][j]  = 0;
      TaggedTruthGdNeutronsinWin[i][j] = 0;
      MisTaggedDecayeinNlike[i][j]     = 0;
      MisTaggedAccNoiseinNlike[i][j]   = 0;
      AllNlikeCandidates[i][j]         = 0;

      TaggedTruthNeutronsinWinFV[i][j]   = 0;
      TaggedTruthHNeutronsinWinFV[i][j]  = 0;
      TaggedTruthGdNeutronsinWinFV[i][j] = 0;
      MisTaggedDecayeinNlikeFV[i][j]     = 0;
      MisTaggedAccNoiseinNlikeFV[i][j]   = 0;
      AllNlikeCandidatesFV[i][j]         = 0;

      TaggedTruthDecayeinWin[i][j]          = 0;
      MisTaggedTruthNeutronsinElike[i][j]   = 0;
      MisTaggedTruthHNeutronsinElike[i][j]  = 0;
      MisTaggedTruthGdNeutronsinElike[i][j] = 0;
      MisTaggedAccNoiseinElike[i][j]        = 0;
      AllElikeCandidates[i][j]              = 0;

      NoiseRate[i][j]  = 0.;
      eNoiseRate[i][j] = 0.;
    }

    NNEffinWin[i]    = 0.;
    NNHEffinWin[i]   = 0.;
    NNGdEffinWin[i]  = 0.;
    eNNEffinWin[i]   = 0.;
    eNNHEffinWin[i]  = 0.;
    eNNGdEffinWin[i] = 0.;

    OverallEffinWin[i]    = 0.;
    OverallHEffinWin[i]   = 0.;
    OverallGdEffinWin[i]  = 0.;
    eOverallEffinWin[i]   = 0.;
    eOverallHEffinWin[i]  = 0.;
    eOverallGdEffinWin[i] = 0.;

    WindowMax[i]  = 0.;
    eWindowMax[i] = 0.;
  }

  for (int i=0; i<CUTSTEP; i++) {
    NeutrinoEventswNoNlike[i]         = 0;
    NeutrinoEventswNlikes[i]          = 0;
    NeutrinoEventswOneNlike[i]        = 0;
    NeutrinoEventswOneNlikeDecaye[i]  = 0;
    NeutrinoEventswNoTruthNeutrons[i] = 0;

    NNEff[i]    = 0.;
    NNHEff[i]   = 0.;
    NNGdEff[i]  = 0.;
    eNNEff[i]   = 0.;
    eNNHEff[i]  = 0.;
    eNNGdEff[i] = 0.;

    NNEffinFV[i]   = 0.;
    NNHEffinFV[i]  = 0.;
    NNGdEffinFV[i] = 0.;

    OverallEff[i]    = 0.;
    OverallHEff[i]   = 0.;
    OverallGdEff[i]  = 0.;
    eOverallEff[i]   = 0.;
    eOverallHEff[i]  = 0.;
    eOverallGdEff[i] = 0.;

    OverallEffinFV[i]   = 0.;
    OverallHEffinFV[i]  = 0.;
    OverallGdEffinFV[i] = 0.;

    Purity[i]  = 0.;
    ePurity[i] = 0.;
  }

  for (int i=0; i<CUTSTEP-1; i++) {
    FillPurity[i]     = 0.;
    FillNoiseRate[i]  = 0.;
    FillTMVATH[i]     = 0.;

    FillePurity[i]    = 0.;
    FilleNoiseRate[i] = 0.;
    FilleTMVATH[i]    = 0.;
  }
}

void NTagAnalysis::GetTruthNeutrons(float NTrueN,
                                    UInt_t truthneutrons, 
                                    std::vector<int> *Type,
                                    std::vector<float> *E,
                                    std::vector<float> *DWall) 
{
  AllTruthNeutrons += NTrueN;
  h1_NTrueN[0] -> Fill(NTrueN);

  //Truth neutrons event by event
  int NumTruthHNeutrons  = 0;
  int NumTruthGdNeutrons = 0;

  for (UInt_t jentry=0; jentry<E->size(); ++jentry) {
    //Truth neutrons
    if (Type->at(jentry)==2) {
      h1_TotGammaE -> Fill(E->at(jentry));

      //in FV
      if (DWall->at(jentry)>0.) AllTruthNeutronsinFV++;

      //Truth H-n neutrons
      if (E->at(jentry) < 6.) {
        TruthHNeutrons++;
        NumTruthHNeutrons++;

        if (DWall->at(jentry)>0.) TruthHNeutronsinFV++;
      }
      //Truth Gd-n neutrons
      if (E->at(jentry) > 6.) {
        TruthGdNeutrons++;
        NumTruthGdNeutrons++;

        if (DWall->at(jentry)>0.) TruthGdNeutronsinFV++;
      }
    }
  }

  h1_NTrueN[1] -> Fill(NumTruthHNeutrons);
  h1_NTrueN[2] -> Fill(NumTruthGdNeutrons);
}


void NTagAnalysis::GetTruthNeutronsIntType(CC0PiNumu* numu, float NTrueN) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  //CCQE(1p1h)
  if (mode==1) h1_TrueNmultiplicity[0] -> Fill(NTrueN);

  //CC non-QE
  if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_TrueNmultiplicity[1] -> Fill(NTrueN);

  //CC RES (Delta+)
  if (mode==13) h1_TrueNmultiplicity[2] -> Fill(NTrueN);

  //CC RES (Delta++)
  if (mode==11) h1_TrueNmultiplicity[3] -> Fill(NTrueN);

  //CC RES (Delta0)
  if (mode==12) h1_TrueNmultiplicity[4] -> Fill(NTrueN);

  //NC
  if (mode>=31) h1_TrueNmultiplicity[5] -> Fill(NTrueN);
}


void NTagAnalysis::GetTruthNeutronsinSearch(UInt_t truthneutrons, 
                                            std::vector<int> *Type,
                                            std::vector<float> *t,
                                            float WinMin,
                                            std::vector<float> *E,
                                            std::vector<float> *DWall) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
      if (Type->at(jentry)==2) {
        if (iwin==0 && t->at(jentry) > WinMin) {
          AllTruthNeutronsinSearch[iwin]++;
          if (DWall->at(jentry) > 0.) AllTruthNeutronsinSearchFV[iwin]++;

          if (E->at(jentry) < 6.) {
            TruthHNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthHNeutronsinSearchFV[iwin]++;
          }
          if (E->at(jentry) > 6.) {
            TruthGdNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthGdNeutronsinSearchFV[iwin]++;
          } 
        }
        if (iwin!=0 && t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) {
          AllTruthNeutronsinSearch[iwin]++;
          if (DWall->at(jentry) > 0.) AllTruthNeutronsinSearchFV[iwin]++;

          if (E->at(jentry) < 6.) {
            TruthHNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthHNeutronsinSearchFV[iwin]++;
          }
          if (E->at(jentry) > 6.) {
            TruthGdNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthGdNeutronsinSearchFV[iwin]++;
          } 
        }
        //if (t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) TruthNeutronsinSearch[iwin]++;
      }
    }
  }
}

void NTagAnalysis::GetTruthDecayeinSearch(UInt_t truthneutrons, 
                                            std::vector<int> *Type,
                                            std::vector<float> *t,
                                            float WinMin) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
      if (Type->at(jentry)==1) {
        if (iwin==0 && t->at(jentry) > WinMin) TruthDecayeinSearch[iwin]++;
        if (iwin!=0 && t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) TruthDecayeinSearch[iwin]++;
        //if (t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) TruthDecayeinSearch[iwin]++;
      }
    }
  }
}



bool NTagAnalysis::DecayelikeChecker(bool etagmode, float NHits, float FitT) {
  bool etagboxin = false;
  if (etagmode) {
  	if (NHits>50 && FitT<20) etagboxin = true;
  }
  return etagboxin;
}

void NTagAnalysis::TruthBreakdowninWindow(std::vector<float> *TagClass, 
                                          std::vector<float> *t,
                                          std::vector<float> *DWall,
                                          std::vector<float> *TagIndex,
                                          std::vector<float> *Label,
                                          std::vector<float> *FitT,
                                          std::vector<float> *TagDWall) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    for (UInt_t ican=0; ican<TagClass->size(); ++ican) {
      
      //Flag that indicates this candidate is in the time window, or not.
      bool inwindow = false;
      //Flag that indicates this candidate is in FV, or not.
      bool inFV     = false;
      //Find corresponded truth info that matches with ican candidate
      for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
        if (TagIndex->at(ican)!=-1 && jentry==(UInt_t)TagIndex->at(ican)) {

          //Check this candidate is in the time window, or not through true time info
          //if not, skip this ican
          if (t->at(jentry) < varwindowmax) inwindow = true;
          if (DWall->at(jentry) > 0.) inFV = true;
        }
      }

      //If this candidate is in the time window, count correponded truth neutrons and decay electorns
      if (inwindow==true) {
        AllCandidatesinWin[iwin]++;
        if (Label->at(ican)==2 || Label->at(ican)==3) TruthNeutroninCandidatesinWin[iwin]++;
        if (Label->at(ican)==2) TruthHNeutroninCandidatesinWin[iwin]++;
        if (Label->at(ican)==3) TruthGdNeutroninCandidatesinWin[iwin]++;
        if (Label->at(ican)==1) TruthDecayeinCandidatesinWin[iwin]++;

        if (inFV==true) {
          AllCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==2 || Label->at(ican)==3) TruthNeutroninCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==2) TruthHNeutroninCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==3) TruthGdNeutroninCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==1) TruthDecayeinCandidatesinWinFV[iwin]++;
        }
      }

      //If this candidate is in the time window, count correponded truth noise
      if (FitT->at(ican) < varwindowmax) {
        AllCandidatesinWin[iwin]++;
        if (Label->at(ican)==0) TruthAccNoiseinCandidatesinWin[iwin]++;

        if (TagDWall->at(ican) > 0.) {
          AllCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==0) TruthAccNoiseinCandidatesinWinFV[iwin]++;
        }
      }
    }
  }
}


void NTagAnalysis::GetNlikeCandidatesinWindow(std::vector<float> *t,
                                              std::vector<float> *DWall,
                                              std::vector<float> *TagIndex,
                                              bool etagmode,
                                              std::vector<float> *NHits,
                                              std::vector<float> *FitT,
                                              std::vector<float> *TagOut,
                                              std::vector<float> *Label,
                                              std::vector<float> *TagDWall) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);

    for (UInt_t ican=0; ican<TagOut->size(); ican++) {
      //Flag that indicates this candidate is in the time window, or not.
      bool inwindow = false;
      //Flag that indicates this candidate is in FV, or not.
      bool inFV     = false;
      //Find corresponded truth info that matches with ican candidate
      for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
        if (TagIndex->at(ican)!=-1 && jentry==(UInt_t)TagIndex->at(ican)) {

          //Check this candidate is in the time window, or not through true time info
          //if not, skip this ican
          if (t->at(jentry) < varwindowmax) inwindow = true;
          if (DWall->at(jentry) > 0.) inFV = true;
        }
      }

      //If this candidate is in the time window, judge it is n-like or not.
      if (inwindow==true) {

        //threshold scan
        for (int ith=0; ith<CUTSTEP; ith++) {
          //Threshold
          if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
          if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;

          if (etagmode) {
            //bool etagboxin = this->DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican));
            bool etagboxin = false;
            if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==2) TaggedTruthHNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==3) TaggedTruthGdNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==1) MisTaggedDecayeinNlike[iwin][ith]++;

            if (inFV) {
              if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWinFV[iwin][ith]++;
              if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==2) TaggedTruthHNeutronsinWinFV[iwin][ith]++;
              if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==3) TaggedTruthGdNeutronsinWinFV[iwin][ith]++;
              if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==1) MisTaggedDecayeinNlikeFV[iwin][ith]++;
            }
          }
          else {
            if (TagOut->at(ican)>TMVATH[ith] && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==2) TaggedTruthHNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==3) TaggedTruthGdNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==1) MisTaggedDecayeinNlike[iwin][ith]++;

            if (inFV) {
              if (TagOut->at(ican)>TMVATH[ith] && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWinFV[iwin][ith]++;
              if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==2) TaggedTruthHNeutronsinWinFV[iwin][ith]++;
              if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==3) TaggedTruthGdNeutronsinWinFV[iwin][ith]++;
              if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==1) MisTaggedDecayeinNlikeFV[iwin][ith]++;
            }
          }

        } //threshold scan
      }

      //Noise contamination in n-like candidates
      for (int ith=0; ith<CUTSTEP; ith++) {
        if (FitT->at(ican) < varwindowmax) {
          if (etagmode) {
            bool etagboxin = false;
            if (etagmode) {
              if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;
            }
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==0) MisTaggedAccNoiseinNlike[iwin][ith]++;
            if (TagDWall->at(ican) > 0.) {
              if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==0) MisTaggedAccNoiseinNlikeFV[iwin][ith]++;
            }
          }
          else {
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==0) MisTaggedAccNoiseinNlike[iwin][ith]++;
            if (TagDWall->at(ican) > 0.) {
              if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==0) MisTaggedAccNoiseinNlikeFV[iwin][ith]++;
            }
          }
        }
      }

    } //candidates loop
  } //window scan
}


void NTagAnalysis::GetElikeCandidatesinWindow(std::vector<float> *t,
                                    std::vector<float> *TagIndex,
                                    bool etagmode,
                                    std::vector<float> *NHits,
                                    std::vector<float> *FitT,
                                    std::vector<float> *TagOut,
                                    std::vector<float> *Label) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);

    for (UInt_t ican=0; ican<TagOut->size(); ican++) {
      //Flag that indicates this candidate is in the time window, or not.
      bool inwindow = false;

      //Find corresponded truth info that matches with ican candidate
      for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
        if (TagIndex->at(ican)!=-1 && jentry==(UInt_t)TagIndex->at(ican)) {

          //Check this candidate is in the time window, or not through true time info
          //if not, skip this ican
          if (t->at(jentry) < varwindowmax) inwindow = true;
        }
      }

      //If this candidate is in the time window, judge it is n-like or not.
      if (inwindow==true) {

        //threshold scan
        for (int ith=0; ith<CUTSTEP; ith++) {
          //Threshold
          if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
          if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;

          if (etagmode) {
            //bool etagboxin = this->DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican));
            bool etagboxin = false;
            if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==1) TaggedTruthDecayeinWin[iwin][ith]++;

            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && (Label->at(ican)==2 || Label->at(ican)==3)) MisTaggedTruthNeutronsinElike[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==2) MisTaggedTruthHNeutronsinElike[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==3) MisTaggedTruthGdNeutronsinElike[iwin][ith]++;
          }
        } //threshold scan
      }

      //Noise contamination in n-like candidates
      for (int ith=0; ith<CUTSTEP; ith++) {
        if (FitT->at(ican) < varwindowmax) {
          if (etagmode) {
            bool etagboxin = false;
            if (etagmode) {
              if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;
            }
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==0) MisTaggedAccNoiseinElike[iwin][ith]++;
          }
        }
      }

    } //candidates loop
  } //window scan
}

void NTagAnalysis::Set1RmuonSamplewNTag(bool NoNlike, CC0PiNumu* numu, int mode) {
  float OscProb = numu->getOscWgt();
  float RecoEnu = numu->var<float>("erec");

  //use tagged neutrons info
  if (NoNlike) {
    h1_All_NoOsc_woNeutron        -> Fill(RecoEnu/1000.);
    h1_All_OscProb_woNeutron      -> Fill(RecoEnu/1000., OscProb);
    h1_All_OscProbRatio_woNeutron -> Fill(RecoEnu/1000., OscProb);

    //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
    if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
      NoOscwoTagN++;
      OscwoTagN += OscProb;
    }
  }
  else {
    h1_All_NoOsc_wNeutron        -> Fill(RecoEnu/1000.);
    h1_All_OscProb_wNeutron      -> Fill(RecoEnu/1000., OscProb);
    h1_All_OscProbRatio_wNeutron -> Fill(RecoEnu/1000., OscProb);
  }

  //CCQE(1p1h)
  if (mode==1) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[0]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[0]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[0] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCQE_woTagN += OscProb;
    }
    else {
      h1_NoOsc_wNeutron[0]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[0]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[0] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCQE_wTagN += OscProb;
    }
  }

  //CC non-QE(2p2h)
  if (mode>=2 && mode<=10) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[1] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCnonQE_woTagN += OscProb;
    }
    else {
      h1_NoOsc_wNeutron[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[1] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCnonQE_wTagN += OscProb;
    }
  }

  //NC
  if (mode>=31) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[2]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[2]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[2] -> Fill(RecoEnu/1000., OscProb);

      OscillatedNC_woTagN++;
    }
    else {
      h1_NoOsc_wNeutron[2]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[2]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[2] -> Fill(RecoEnu/1000., OscProb);

      OscillatedNC_wTagN++;
    }
  }

  //CC RES (Delta+)
  if (mode==13) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[3]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[3]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[3] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESp_woTagN += OscProb;
    }
    else {
      h1_NoOsc_wNeutron[3]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[3]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[3] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESp_wTagN += OscProb;
    }
  }
  //CC RES (Delta++)
  if (mode==11) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[4]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[4]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[4] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESpp_woTagN += OscProb;
    }
    else {
      h1_NoOsc_wNeutron[4]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[4]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[4] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRESpp_wTagN += OscProb;
    }
  }
  //CC RES (Delta0)
  if (mode==12) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[5]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[5]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[5] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRES0_woTagN += OscProb;
    }
    else {
      h1_NoOsc_wNeutron[5]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[5]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[5] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCRES0_wTagN += OscProb;
    }
  }

  //CC Others
  if (mode>=14 && mode<=30) {
    if (NoNlike) {
      h1_NoOsc_woNeutron[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb_woNeutron[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_woNeutron[1] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCOther_woTagN += OscProb;
    }
    else {
      h1_NoOsc_wNeutron[1]        -> Fill(RecoEnu/1000.);
      h1_OscProb_wNeutron[1]      -> Fill(RecoEnu/1000., OscProb);
      h1_OscProbRatio_wNeutron[1] -> Fill(RecoEnu/1000., OscProb);

      OscillatedCCOther_wTagN += OscProb;
    }
  }
}


void NTagAnalysis::GetMisTagNeutrinoEvents(CC0PiNumu* numu, float NTrueN, bool NoNlike) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  float RecoEnu = numu->var<float>("erec");

  if (NTrueN!=0 && NoNlike==true) {

    //CCQE
    if (mode==1) h1_OscProb_mistag[0] -> Fill(RecoEnu/1000., OscProb);

    //CC non-QE
    if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_OscProb_mistag[1] -> Fill(RecoEnu/1000., OscProb);

    //NC
    if (mode>=31) h1_OscProb_mistag[2] -> Fill(RecoEnu/1000.);

    //CCRES+
    if (mode==13) h1_OscProb_mistag[3] -> Fill(RecoEnu/1000., OscProb);

    //CCRES++
    if (mode==11) h1_OscProb_mistag[4] -> Fill(RecoEnu/1000., OscProb);

    //CCRES0
    if (mode==12) h1_OscProb_mistag[5] -> Fill(RecoEnu/1000., OscProb);
  }
}


void NTagAnalysis::GetNeutrinoEventswNTag(std::vector<float> *TagOut,
                                          std::vector<float> *TagIndex,
                                          std::vector<float> *NHits,
                                          std::vector<float> *FitT,
                                          std::vector<float> *Label,
                                          float NTrueN,
                                          bool etagmode,
                                          CC0PiNumu* numu,
                                          NeutrinoOscillation neuosc,
                                          int NCUT) 
{
  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");
  //float EnuReso = TrueEnu - RecoEnu/1000.;
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;

  for (int ith=0; ith<CUTSTEP; ith++) {

    //Count the number of tagged neutrons
    int NumTaggedNeutrons       = 0;  //Number of n-like candidates of this event
    int NumTruthNeutronsinNlike = 0;  //Number of truth neutrons in n-like candidates of this event
    int NumTruthDecayeinNlike   = 0;  //Number of truth decay-e in n-like candidates of this event
    FlagReset();

    for (UInt_t ican=0; ican<TagOut->size(); ++ican) {

      //Check whether this candidate is n-like or e-like(for e-tagging ON)
      bool etagboxin = false;
      if (etagmode){
        if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

        if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false) NumTaggedNeutrons++;
        if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;
        if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==1) NumTruthDecayeinNlike++;
      }
      else {
        if (TagOut->at(ican)>TMVATH[ith]) NumTaggedNeutrons++;
        if (TagOut->at(ican)>TMVATH[ith] && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;
        if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==1) NumTruthDecayeinNlike++;
      }       
    }

    if (NumTaggedNeutrons==0) NoNlike = true;
    if (NumTaggedNeutrons>=1) nonzeroTaggedNeutrons = true;
    if (NumTaggedNeutrons==1) OnlyOneNlike = true;
    if (NumTaggedNeutrons==1 && NumTruthDecayeinNlike!=0) OnlyOneisDecaye = true;
    if (NumTruthNeutronsinNlike==0) NoNeutron = true;


    if (ith==NCUT) {
      //Reconstructed energy distribution w/o tagged neutrons
      this -> Set1RmuonSamplewNTag(NoNlike, numu, mode);

      //Reconstructed energy distribution w/o tagged neutrons
      this -> GetMisTagNeutrinoEvents(numu, NTrueN, NoNlike);
    }
    

    //See neutrino events that have no n-like candidates
    if (NoNlike==true) {
      NeutrinoEventswNoNlike[ith]+=neuosc.OscProbCalculator(numu, false);

      if (ith==NCUT) {

        //Reconstructed energy resolution w/o tagged neutrons
        //this -> Set1RmuonSamplewNTag(NoNlike, numu, mode);

        //Neutrino energy resolution
        test1++;
        //CCQE(1p1h)
        if (mode==1) h1_Enureso_CCQE[0] -> Fill(EnuReso);
        //CC non-QE
        if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enureso_CCnonQE[0] -> Fill(EnuReso);
        //CC RES(Delta++)
        if (mode==11) h1_Enureso_CCRES_deltapp[0] -> Fill(EnuReso);
        //CC RES(Delta0)
        if (mode==12) h1_Enureso_CCRES_delta0[0] -> Fill(EnuReso);
        //CC RES(Delta+)
        if (mode==13) h1_Enureso_CCRES_deltap[0] -> Fill(EnuReso);
        //NC
        if (mode>=31) h1_Enureso_NC[0] -> Fill(EnuReso);
      }
      
    }

    //See neutrino events that have more than one n-like candidates
    //if (nonzeroTaggedNeutrons==true) NeutrinoEventswNlikes[0][ith]++;
    if (nonzeroTaggedNeutrons==true) {
      //NeutrinoEventswNlikes[0][ith]+=neuosc.OscProbCalculator(numu, false);
      NeutrinoEventswNlikes[ith]+=neuosc.OscProbCalculator(numu, false);

      if (ith==NCUT) {
        //Reconstructed energy resolution w/ tagged neutrons
        //this -> Set1RmuonSamplewNTag(NoNlike, numu, mode);

        //Neutrino energy resolution
        test2++;
        //CCQE(1p1h)
        if (mode==1) h1_Enureso_CCQE[1] -> Fill(EnuReso);
        //CC non-QE
        if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enureso_CCnonQE[1] -> Fill(EnuReso);
        //CC RES(Delta++)
        if (mode==11) h1_Enureso_CCRES_deltapp[1] -> Fill(EnuReso);
        //CC RES(Delta0)
        if (mode==12) h1_Enureso_CCRES_delta0[1] -> Fill(EnuReso);
        //CC RES(Delta+)
        if (mode==13) h1_Enureso_CCRES_deltap[1] -> Fill(EnuReso);
        //NC
        if (mode>=31) h1_Enureso_NC[1] -> Fill(EnuReso);
      }
    }

    //See neutrino events that have one n-like candidate
    //if (OnlyOneNlike==true) NeutrinoEventswOneNlike[0][ith]++;
    //if (OnlyOneNlike==true) NeutrinoEventswOneNlike[0][ith]+=neuosc.OscProbCalculator(numu, false);
    if (OnlyOneNlike==true) NeutrinoEventswOneNlike[ith]+=neuosc.OscProbCalculator(numu, false);

    //See neutrino events that have one n-like candidate, but it is truth decay-e
    //if (OnlyOneisDecaye==true) NeutrinoEventswOneNlikeDecaye[0][ith]++;
    //if (OnlyOneisDecaye==true) NeutrinoEventswOneNlikeDecaye[0][ith]+=neuosc.OscProbCalculator(numu, false);
    if (OnlyOneisDecaye==true) NeutrinoEventswOneNlikeDecaye[ith]+=neuosc.OscProbCalculator(numu, false);

    //See neutrino events that have no tagged truth neutrons
    //if (nonzeroTaggedNeutrons==true && NoNeutron==true) NeutrinoEventswNoTruthNeutrons[0][ith]++;
    //if (nonzeroTaggedNeutrons==true && NoNeutron==true) NeutrinoEventswNoTruthNeutrons[0][ith]+=neuosc.OscProbCalculator(numu, false);
    if (nonzeroTaggedNeutrons==true && NoNeutron==true) NeutrinoEventswNoTruthNeutrons[ith]+=neuosc.OscProbCalculator(numu, false);
  }
}


void NTagAnalysis::GetResolutionwTrueN(CC0PiNumu* numu, float NTrueN) {

  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;

  if (NTrueN==0) {
    //CCQE
    if (mode==1) h1_Enureso_CCQE_trueN[0] -> Fill(EnuReso);
    //CC non-QE
    if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enureso_CCnonQE_trueN[0] -> Fill(EnuReso);
    //CC RES (Delta++)
    if (mode==11) h1_Enureso_CCRES_deltapp_trueN[0] -> Fill(EnuReso);
    //CC RES (Delta0)
    if (mode==12) h1_Enureso_CCRES_delta0_trueN[0] -> Fill(EnuReso);
    //CC RES (Delta+)
    if (mode==13) h1_Enureso_CCRES_deltap_trueN[0] -> Fill(EnuReso);
    //NC
    if (mode>=31) h1_Enureso_NC_trueN[0] -> Fill(EnuReso);
  }
  else {
    //CCQE
    if (mode==1) h1_Enureso_CCQE_trueN[1] -> Fill(EnuReso);
    //CC non-QE
    if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30)) h1_Enureso_CCnonQE_trueN[1] -> Fill(EnuReso);
    //CC RES (Delta++)
    if (mode==11) h1_Enureso_CCRES_deltapp_trueN[1] -> Fill(EnuReso);
    //CC RES (Delta0)
    if (mode==12) h1_Enureso_CCRES_delta0_trueN[1] -> Fill(EnuReso);
    //CC RES (Delta+)
    if (mode==13) h1_Enureso_CCRES_deltap_trueN[1] -> Fill(EnuReso);
    //NC
    if (mode>=31) h1_Enureso_NC_trueN[1] -> Fill(EnuReso);
  }
}


void NTagAnalysis::SummaryTruthInfoinSearch(float WinMin, TString outputname) {
  std::ofstream ofs(outputname);
  if (!ofs) {
    std::cout << "Can not open .txt file: " << outputname << std::endl;
  }
  ofs << "[Truth Info] All Truth Neutrons(Gd+H)      : " << AllTruthNeutrons     << std::endl;
  ofs << "[Truth Info] Truth H-n Neutrons            : " << TruthHNeutrons       << std::endl;
  ofs << "[Truth Info] Truth Gd-n Neutrons           : " << TruthGdNeutrons      << std::endl;
  ofs << "[Truth Info] All Truth Neutrons(Gd+H) in FV: " << AllTruthNeutronsinFV << std::endl;
  ofs << "[Truth Info] Truth H-n Neutrons in FV      : " << TruthHNeutronsinFV   << std::endl;
  ofs << "[Truth Info] Truth Gd-n Neutrons in FV     : " << TruthGdNeutronsinFV  << std::endl;
  ofs << " " << std::endl;
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    ofs << "===== [" << WinMin << " us, " << varwindowmax << " us] =====" << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us]: " << AllTruthNeutronsinSearch[iwin] << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us]: " << TruthHNeutronsinSearch[iwin] << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us]: " << TruthGdNeutronsinSearch[iwin] << std::endl;
    ofs << "[Truth Info] Truth Decay e in [" << WinMin << " us, " << varwindowmax << " us] : " << TruthDecayeinSearch[iwin]   << std::endl;

    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << AllTruthNeutronsinSearchFV[iwin] << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << TruthHNeutronsinSearchFV[iwin] << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << TruthGdNeutronsinSearchFV[iwin] << std::endl;

    ofs << "[Candidates] Truth Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us]     : " << TruthNeutroninCandidatesinWin[iwin]   << std::endl;
    ofs << "[Candidates] Truth H-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] : " << TruthHNeutroninCandidatesinWin[iwin]  << std::endl;
    ofs << "[Candidates] Truth Gd-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us]: " << TruthGdNeutroninCandidatesinWin[iwin] << std::endl;
    ofs << "[Candidates] Truth Decay e in Candidates in [" << WinMin << " us, " << varwindowmax << " us]      : " << TruthDecayeinCandidatesinWin[iwin]    << std::endl;
    ofs << "[Candidates] Truth Acc. Noise in Candidates in [" << WinMin << " us, " << varwindowmax << " us]   : " << TruthAccNoiseinCandidatesinWin[iwin]  << std::endl;
    ofs << "[Candidates] All Candidates in [" << WinMin << " us, " << varwindowmax << " us]   : " << AllCandidatesinWin[iwin] << std::endl;

    ofs << "[Candidates] Truth Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV     : " << TruthNeutroninCandidatesinWinFV[iwin]   << std::endl;
    ofs << "[Candidates] Truth H-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV : " << TruthHNeutroninCandidatesinWinFV[iwin]  << std::endl;
    ofs << "[Candidates] Truth Gd-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << TruthGdNeutroninCandidatesinWinFV[iwin] << std::endl;
    ofs << "[Candidates] Truth Decay e in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV      : " << TruthDecayeinCandidatesinWinFV[iwin]    << std::endl;
    ofs << "[Candidates] Truth Acc. Noise in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV   : " << TruthAccNoiseinCandidatesinWinFV[iwin]  << std::endl;
    ofs << "[Candidates] All Candidates in [" << WinMin << " us, " << varwindowmax << " us]   : " << AllCandidatesinWinFV[iwin] << std::endl;

    GetPreEfficiency(iwin);
    ofs << "[   Pre    ] Pre-selection Efficiency(Gd+H): " << PreEff*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(H)   : " << PreHEff*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(Gd)  : " << PreGdEff*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(Gd+H) in FV: " << PreEffinFV*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(H) in FV   : " << PreHEffinFV*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(Gd) in FV  : " << PreGdEffinFV*100 << " %" << std::endl;

    for (int ith=0; ith<CUTSTEP; ith++) {
      if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
      if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;
      ofs << "[    NN    ] ===== Threshold: " << TMVATH[ith] << " =====" << std::endl;
      ofs << "[    NN    ]  ----------- n-like candidates -----------"   << std::endl;
      ofs << "[    NN    ] Tagged Truth Neutrons(Gd+H) in Search Window: " << TaggedTruthNeutronsinWin[iwin][ith]   << std::endl;
      ofs << "[    NN    ] Tagged Truth H-n Neutrons in Search Window  : " << TaggedTruthHNeutronsinWin[iwin][ith]  << std::endl;
      ofs << "[    NN    ] Tagged Truth Gd-n Neutrons in Search Window : " << TaggedTruthGdNeutronsinWin[iwin][ith] << std::endl;
      ofs << "[    NN    ] Mis-tagged Truth Decay-e in Search Window   : " << MisTaggedDecayeinNlike[iwin][ith]     << std::endl;
      ofs << "[    NN    ] Mis-tagged Acc. Noise in Search Window      : " << MisTaggedAccNoiseinNlike[iwin][ith]   << std::endl;
      AllNlikeCandidates[iwin][ith] = TaggedTruthNeutronsinWin[iwin][ith] 
                                    + MisTaggedDecayeinNlike[iwin][ith]
                                    + MisTaggedAccNoiseinNlike[iwin][ith];
      ofs << "[    NN    ] All Tagged Neutrons (n-like candidates)     : " << AllNlikeCandidates[iwin][ith] << std::endl;

      ofs << "[    NN    ] Tagged Truth Neutrons(Gd+H) in Search Window in FV: " << TaggedTruthNeutronsinWinFV[iwin][ith]   << std::endl;
      ofs << "[    NN    ] Tagged Truth H-n Neutrons in Search Window in FV  : " << TaggedTruthHNeutronsinWinFV[iwin][ith]  << std::endl;
      ofs << "[    NN    ] Tagged Truth Gd-n Neutrons in Search Window in FV : " << TaggedTruthGdNeutronsinWinFV[iwin][ith] << std::endl;
      ofs << "[    NN    ] Mis-tagged Truth Decay-e in Search Window in FV   : " << MisTaggedDecayeinNlikeFV[iwin][ith]     << std::endl;
      ofs << "[    NN    ] Mis-tagged Acc. Noise in Search Window in FV      : " << MisTaggedAccNoiseinNlikeFV[iwin][ith]   << std::endl;
      AllNlikeCandidatesFV[iwin][ith] = TaggedTruthNeutronsinWinFV[iwin][ith] 
                                      + MisTaggedDecayeinNlikeFV[iwin][ith]
                                      + MisTaggedAccNoiseinNlikeFV[iwin][ith];
      ofs << "[    NN    ] All Tagged Neutrons (n-like candidates)     : " << AllNlikeCandidatesFV[iwin][ith] << std::endl;

      NoiseRate[iwin][ith] = GetNoiseRate(MisTaggedDecayeinNlike[iwin][ith], MisTaggedAccNoiseinNlike[iwin][ith], SelectedParentNeutrinos[5],
                                          varwindowmax, WINDOWMIN, NOISECUT);
      ofs << "[    NN    ] Noise Rate: " << NoiseRate[iwin][ith]*100. << " %" << std::endl;
      ofs << "[    NN    ]  ----------- e-like candidates -----------"   << std::endl;
      ofs << "[    NN    ] Tagged Truth Decay-e in Search Window       : " << TaggedTruthDecayeinWin[iwin][ith]          << std::endl;
      ofs << "[    NN    ] Tagged Truth Neutrons(Gd+H) in Search Window: " << MisTaggedTruthNeutronsinElike[iwin][ith]   << std::endl;
      ofs << "[    NN    ] Tagged Truth H-n Neutrons in Search Window  : " << MisTaggedTruthHNeutronsinElike[iwin][ith]  << std::endl;
      ofs << "[    NN    ] Tagged Truth Gd-n Neutrons in Search Window : " << MisTaggedTruthGdNeutronsinElike[iwin][ith] << std::endl;
      ofs << "[    NN    ] Mis-tagged Acc. Noise in Search Window      : " << MisTaggedAccNoiseinElike[iwin][ith]        << std::endl;
      AllElikeCandidates[iwin][ith] = TaggedTruthDecayeinWin[iwin][ith] 
                                    + MisTaggedTruthNeutronsinElike[iwin][ith]
                                    + MisTaggedAccNoiseinElike[iwin][ith];
      ofs << "[    NN    ] All Tagged decay-e (e-like candidates)      : " << AllElikeCandidates[iwin][ith] << std::endl;
      
      GetNNEfficiency(iwin);
      ofs << "[    NN    ] NN Efficiency(Gd+H): " << NNEff[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(H)   : " << NNHEff[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(Gd)  : " << NNGdEff[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(Gd+H) in FV: " << NNEffinFV[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(H) in FV   : " << NNHEffinFV[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(Gd) in FV  : " << NNGdEffinFV[ith]*100 << " %" << std::endl;

      GetOverallEfficiency(iwin);
      ofs << "[  Overall ] Overall Efficiency(Gd+H): " << OverallEff[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(H)   : " << OverallHEff[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(Gd)  : " << OverallGdEff[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(Gd+H) in FV: " << OverallEffinFV[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(H) in FV   : " << OverallHEffinFV[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(Gd) in FV  : " << OverallGdEffinFV[ith]*100 << " %" << std::endl;
      GetPurity(iwin);
      ofs << "[  Purity  ] Purity: " << Purity[ith]*100 << std::endl;
    }
    ofs << " " << std::endl;
  }
  ofs << " " << std::endl;
  for (int ith=0; ith<CUTSTEP; ith++) {
    ofs << "[    NN    ] ===== Threshold: " << TMVATH[ith] << " =====" << std::endl;
    ofs << "[    NN    ] ===== 1R muon Samples with NTag Info ====="   << std::endl;
    ofs << "[    NN    ] Neutrino Events with No Tagged Neutrons: " << NeutrinoEventswNoNlike[ith]         << std::endl;
    ofs << "[    NN    ] Neutrino Events with Tagged Neutrons   : " << NeutrinoEventswNlikes[ith]          << std::endl;
    ofs << "[    NN    ] Neutrino Events with Only One Nlike    : " << NeutrinoEventswOneNlike[ith]        << std::endl;
    ofs << "[    NN    ] Neutrino Events with One Nlike Decay-e : " << NeutrinoEventswOneNlikeDecaye[ith]  << std::endl;
    ofs << "[    NN    ] Neutrino Events with No Truth Neutrons : " << NeutrinoEventswNoTruthNeutrons[ith] << std::endl;
  }
}

void NTagAnalysis::SetNoiseRateGraph() {

  for (int i=0; i<WINSTEP; i++) {
    g_NoiseRate[i] = new TGraphErrors(CUTSTEP, TMVATH, NoiseRate[i], eTMVATH, eNoiseRate[i]);
    g_NoiseRate[i] -> SetMarkerSize(1.0);
    g_NoiseRate[i] -> SetMarkerStyle(20);

    switch (i) {
      case 0:
        g_NoiseRate[i] -> SetMarkerColor(kViolet-7);
        g_NoiseRate[i] -> SetLineColor(kViolet-7);
        break;
      case 1:
        g_NoiseRate[i] -> SetMarkerColor(kAzure+1);
        g_NoiseRate[i] -> SetLineColor(kAzure+1);
        break;
      case 2:
        g_NoiseRate[i] -> SetMarkerColor(kTeal+5);
        g_NoiseRate[i] -> SetLineColor(kTeal+5);
        break;
      case 3:
        g_NoiseRate[i] -> SetMarkerColor(kYellow-3);
        g_NoiseRate[i] -> SetLineColor(kYellow-3);
        break;
      case 4:
        g_NoiseRate[i] -> SetMarkerColor(kOrange+7);
        g_NoiseRate[i] -> SetLineColor(kOrange+7);
        break;
      case 5:
        g_NoiseRate[i] -> SetMarkerColor(kRed-3);
        g_NoiseRate[i] -> SetLineColor(kRed-3);
        break;
      case 6:
        g_NoiseRate[i] -> SetMarkerColor(kPink-8);
        g_NoiseRate[i] -> SetLineColor(kPink-8);
        break;
    }
  }
}

void NTagAnalysis::GetEfficiencyforWinOpt() {
  //Threshold that noise rate becomes ~2%
  //note that this loop inverts the order of time window!(starts from 200 us, but not 535 us)
  int inthr[WINSTEP];       //inthr = threshold / 0.05  !!! should be set by hand !!!
  int inwin[WINSTEP];       //index of window step that correponds to above calculation
  //float WindowMax[WINSTEP]; //Step of time window scan
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    switch (iwin) {
      case 0: //200us
        //inthr[iwin] = 10;
        inthr[iwin] = 8;
        inwin[iwin] = 5;
        WindowMax[iwin] = 200;
        break;
      case 1: //250us
        //inthr[iwin] = 11;
        inthr[iwin] = 9;
        inwin[iwin] = 4;
        WindowMax[iwin] = 250;
        break;
      case 2: //300us
        //inthr[iwin] = 12;
        inthr[iwin] = 9;
        inwin[iwin] = 3;
        WindowMax[iwin] = 300;
        break;
      case 3: //350us
        //inthr[iwin] = 13;
        inthr[iwin] = 10;
        inwin[iwin] = 2;
        WindowMax[iwin] = 350;
        break;
      case 4: //400us
        //inthr[iwin] = 13;
        inthr[iwin] = 11;
        inwin[iwin] = 1;
        WindowMax[iwin] = 400;
        break;
      case 5: //535us
        //inthr[iwin] = 14;
        inthr[iwin] = 11;
        inwin[iwin] = 0;
        WindowMax[iwin] = 535;
        break;
    }

    NNEffinWin[iwin]   = (float)TaggedTruthNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthNeutroninCandidatesinWin[inwin[iwin]];
    NNHEffinWin[iwin]  = (float)TaggedTruthHNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthHNeutroninCandidatesinWin[inwin[iwin]];
    NNGdEffinWin[iwin] = (float)TaggedTruthGdNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthGdNeutroninCandidatesinWin[inwin[iwin]];

    OverallEffinWin[iwin]   = (float)TaggedTruthNeutronsinWin[inwin[iwin]][inthr[iwin]] / AllTruthNeutronsinFV;
    OverallHEffinWin[iwin]  = (float)TaggedTruthHNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthHNeutronsinFV;
    OverallGdEffinWin[iwin] = (float)TaggedTruthGdNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthGdNeutronsinFV;
  }
}

void NTagAnalysis::GetPreEfficiency(int windowstep) {
  //Pre-selection
  PreEff       = (float)TruthNeutroninCandidatesinWin[windowstep] / AllTruthNeutronsinSearch[windowstep];
  PreHEff      = (float)TruthHNeutroninCandidatesinWin[windowstep] / TruthHNeutronsinSearch[windowstep];
  PreGdEff     = (float)TruthGdNeutroninCandidatesinWin[windowstep] / TruthGdNeutronsinSearch[windowstep];

  PreEffinFV   = (float)TruthNeutroninCandidatesinWinFV[windowstep] / AllTruthNeutronsinSearchFV[windowstep];
  PreHEffinFV  = (float)TruthHNeutroninCandidatesinWinFV[windowstep] / TruthHNeutronsinSearchFV[windowstep];
  PreGdEffinFV = (float)TruthGdNeutroninCandidatesinWinFV[windowstep] / TruthGdNeutronsinSearchFV[windowstep];
}

void NTagAnalysis::GetNNEfficiency(int windowstep) {
  for (int ith=0; ith<CUTSTEP; ith++) {
    NNEff[ith]       = (float)TaggedTruthNeutronsinWin[windowstep][ith] / TruthNeutroninCandidatesinWin[windowstep];
    NNHEff[ith]      = (float)TaggedTruthHNeutronsinWin[windowstep][ith] / TruthHNeutroninCandidatesinWin[windowstep];
    NNGdEff[ith]     = (float)TaggedTruthGdNeutronsinWin[windowstep][ith] / TruthGdNeutroninCandidatesinWin[windowstep];

    NNEffinFV[ith]   = (float)TaggedTruthNeutronsinWinFV[windowstep][ith] / TruthNeutroninCandidatesinWinFV[windowstep];
    NNHEffinFV[ith]  = (float)TaggedTruthHNeutronsinWinFV[windowstep][ith] / TruthHNeutroninCandidatesinWinFV[windowstep];
    NNGdEffinFV[ith] = (float)TaggedTruthGdNeutronsinWinFV[windowstep][ith] / TruthGdNeutroninCandidatesinWinFV[windowstep];
  }
}

void NTagAnalysis::GetOverallEfficiency(int windowstep) {
  for (int ith=0; ith<CUTSTEP; ith++) {
    OverallEff[ith]       = (float)TaggedTruthNeutronsinWin[windowstep][ith] / AllTruthNeutronsinSearch[windowstep];
    OverallHEff[ith]      = (float)TaggedTruthHNeutronsinWin[windowstep][ith] / TruthHNeutronsinSearch[windowstep];
    OverallGdEff[ith]     = (float)TaggedTruthGdNeutronsinWin[windowstep][ith] / TruthGdNeutronsinSearch[windowstep];

    OverallEffinFV[ith]   = (float)TaggedTruthNeutronsinWinFV[windowstep][ith] / AllTruthNeutronsinSearchFV[windowstep];
    OverallHEffinFV[ith]  = (float)TaggedTruthHNeutronsinWinFV[windowstep][ith] / TruthHNeutronsinSearchFV[windowstep];
    OverallGdEffinFV[ith] = (float)TaggedTruthGdNeutronsinWinFV[windowstep][ith] / TruthGdNeutronsinSearchFV[windowstep];
  }
}

void NTagAnalysis::GetPurity(int windowstep) {
  for (int ith=0; ith<CUTSTEP; ith++) {
    Purity[ith] = (float)TaggedTruthNeutronsinWin[windowstep][ith] / AllNlikeCandidates[windowstep][ith];
  }
}


void NTagAnalysis::SetEfficiencyGraph(int windowstep) {
  g_NNEffwin        = new TGraphErrors(WINSTEP, WindowMax, NNEffinWin, eWindowMax, eNNEffinWin);
  g_NNHEffwin       = new TGraphErrors(WINSTEP, WindowMax, NNHEffinWin, eWindowMax, eNNHEffinWin);
  g_NNGdEffwin      = new TGraphErrors(WINSTEP, WindowMax, NNGdEffinWin, eWindowMax, eNNGdEffinWin);
  g_OverallEffwin   = new TGraphErrors(WINSTEP, WindowMax, OverallEffinWin, eWindowMax, eOverallEffinWin);
  g_OverallHEffwin  = new TGraphErrors(WINSTEP, WindowMax, OverallHEffinWin, eWindowMax, eOverallHEffinWin);
  g_OverallGdEffwin = new TGraphErrors(WINSTEP, WindowMax, OverallGdEffinWin, eWindowMax, eOverallGdEffinWin);
  g_NNEffwin   -> SetMarkerColor(kPink-5);
  g_NNEffwin   -> SetLineColor(kPink-5);
  g_NNEffwin   -> SetMarkerStyle(20);
  g_NNEffwin   -> SetMarkerSize(1.0);
  g_NNHEffwin  -> SetMarkerColor(kAzure-4);
  g_NNHEffwin  -> SetLineColor(kAzure-4);
  g_NNHEffwin  -> SetMarkerStyle(20);
  g_NNHEffwin  -> SetMarkerSize(1.0);
  g_NNGdEffwin -> SetMarkerColor(kTeal-5);
  g_NNGdEffwin -> SetLineColor(kTeal-5);
  g_NNGdEffwin -> SetMarkerStyle(20);
  g_NNGdEffwin -> SetMarkerSize(1.0);
  g_OverallEffwin   -> SetMarkerColor(kPink-5);
  g_OverallEffwin   -> SetLineColor(kPink-5);
  g_OverallEffwin   -> SetMarkerStyle(20);
  g_OverallEffwin   -> SetMarkerSize(1.0);
  g_OverallHEffwin  -> SetMarkerColor(kAzure-4);
  g_OverallHEffwin  -> SetLineColor(kAzure-4);
  g_OverallHEffwin  -> SetMarkerStyle(20);
  g_OverallHEffwin  -> SetMarkerSize(1.0);
  g_OverallGdEffwin -> SetMarkerColor(kTeal-5);
  g_OverallGdEffwin -> SetLineColor(kTeal-5);
  g_OverallGdEffwin -> SetMarkerStyle(20);
  g_OverallGdEffwin -> SetMarkerSize(1.0);

  //windowstep=0 for [3 us, 535 us]
  GetPreEfficiency(windowstep);
  GetNNEfficiency(windowstep);
  GetOverallEfficiency(windowstep);
  GetPurity(windowstep);
  g_NNEff        = new TGraphErrors(CUTSTEP, TMVATH, NNEff, eTMVATH, eNNEff);
  g_NNHEff       = new TGraphErrors(CUTSTEP, TMVATH, NNHEff, eTMVATH, eNNHEff);
  g_NNGdEff      = new TGraphErrors(CUTSTEP, TMVATH, NNGdEff, eTMVATH, eNNGdEff);
  g_OverallEff   = new TGraphErrors(CUTSTEP, TMVATH, OverallEff, eTMVATH, eOverallEff);
  g_OverallHEff  = new TGraphErrors(CUTSTEP, TMVATH, OverallHEff, eTMVATH, eOverallHEff);
  g_OverallGdEff = new TGraphErrors(CUTSTEP, TMVATH, OverallGdEff, eTMVATH, eOverallGdEff);
  g_NNEff   -> SetMarkerColor(kPink-5);
  g_NNEff   -> SetLineColor(kPink-5);
  g_NNEff   -> SetMarkerStyle(20);
  g_NNEff   -> SetMarkerSize(1.0);
  g_NNHEff  -> SetMarkerColor(kAzure-4);
  g_NNHEff  -> SetLineColor(kAzure-4);
  g_NNHEff  -> SetMarkerStyle(20);
  g_NNHEff  -> SetMarkerSize(1.0);
  g_NNGdEff -> SetMarkerColor(kTeal-5);
  g_NNGdEff -> SetLineColor(kTeal-5);
  g_NNGdEff -> SetMarkerStyle(20);
  g_NNGdEff -> SetMarkerSize(1.0);
  g_OverallEff   -> SetMarkerColor(kPink-5);
  g_OverallEff   -> SetLineColor(kPink-5);
  g_OverallEff   -> SetMarkerStyle(20);
  g_OverallEff   -> SetMarkerSize(1.0);
  g_OverallHEff  -> SetMarkerColor(kAzure-4);
  g_OverallHEff  -> SetLineColor(kAzure-4);
  g_OverallHEff  -> SetMarkerStyle(20);
  g_OverallHEff  -> SetMarkerSize(1.0);
  g_OverallGdEff -> SetMarkerColor(kTeal-5);
  g_OverallGdEff -> SetLineColor(kTeal-5);
  g_OverallGdEff -> SetMarkerStyle(20);
  g_OverallGdEff -> SetMarkerSize(1.0);

  
  //make 20-point(not 21-point) purity curve
  for (int i=0; i<CUTSTEP-1; i++) {
    FillPurity[i]  = Purity[i];

    FillTMVATH[i]  = TMVATH[i];
    FilleTMVATH[i] = eTMVATH[i];
  }
  g_Purity = new TGraphErrors(CUTSTEP-1, FillTMVATH, FillPurity, FilleTMVATH, FillePurity);
  g_Purity -> SetMarkerColor(kPink-5);
  g_Purity -> SetLineColor(kPink-5);
  g_Purity -> SetMarkerStyle(20);
  g_Purity -> SetMarkerSize(1.0);

  //make 20-point(not 21-point) noise rate curve
  for (int i=0; i<CUTSTEP-1; i++) {
    FillNoiseRate[i] = NoiseRate[windowstep][i+1];

    FillTMVATH[i]  = TMVATH[i+1];
    FilleTMVATH[i] = eTMVATH[i+1];
  }
  g_FillNoiseRate = new TGraphErrors(CUTSTEP-1, FillTMVATH, FillNoiseRate, FilleTMVATH, FilleNoiseRate);
  g_FillNoiseRate -> SetMarkerColor(kGray+3);
  g_FillNoiseRate -> SetLineColor(kGray+3);
  g_FillNoiseRate -> SetMarkerStyle(20);
  g_FillNoiseRate -> SetMarkerSize(1.0);
}


float NTagAnalysis::GetTaggedNeutrons(std::vector<float> *TagOut,
                                      float Threshold,
                                      std::vector<float> *TagIndex,
                                      std::vector<float> *NHits,
                                      std::vector<float> *FitT,
                                      std::vector<float> *Label,
                                      bool etagmode) 
{
  //Count the number of tagged neutrons
  int NumTaggedNeutrons       = 0;  //Number of n-like candidates of this event
  int NumTruthNeutronsinNlike = 0;  //Number of truth neutrons in n-like candidates of this event
  int NumTruthDecayeinNlike   = 0;  //Number of truth decay-e in n-like candidates of this event

  for (UInt_t ican=0; ican<TagOut->size(); ++ican) {

    //Check whether this candidate is n-like or e-like(for e-tagging ON)
    bool etagboxin = false;
    if (etagmode){
      if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

      if (TagOut->at(ican)>Threshold && etagboxin==false) NumTaggedNeutrons++;
      if (TagOut->at(ican)>Threshold && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;
      if (TagOut->at(ican)>Threshold && etagboxin==false && Label->at(ican)==1) NumTruthDecayeinNlike++;
    }
    else {
      if (TagOut->at(ican)>Threshold) NumTaggedNeutrons++;
      if (TagOut->at(ican)>Threshold && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;        
      if (TagOut->at(ican)>Threshold && Label->at(ican)==1) NumTruthDecayeinNlike++;
    }       
  }
  return NumTaggedNeutrons;  
}


void NTagAnalysis::cdNTagAnalysis(TFile* fout) {
  fout -> mkdir("NTagAnalysis");
  fout -> cd("NTagAnalysis");
}

void NTagAnalysis::WritePlots() {
  for (int i=0; i<TRUETYPE; i++) h1_NTrueN[i] -> Write();
  h1_TotGammaE -> Write();

  for (int i=0; i<2; i++) {
    h1_Enureso_CCQE[i]          -> Write();
    h1_Enureso_CCnonQE[i]       -> Write();
    h1_Enureso_CCRES_deltap[i]  -> Write();
    h1_Enureso_CCRES_deltapp[i] -> Write();
    h1_Enureso_CCRES_delta0[i]  -> Write();
    h1_Enureso_NC[i]            -> Write();

    h1_Enureso_CCQE_trueN[i]          -> Write();
    h1_Enureso_CCnonQE_trueN[i]       -> Write();
    h1_Enureso_CCRES_deltap_trueN[i]  -> Write();
    h1_Enureso_CCRES_deltapp_trueN[i] -> Write();
    h1_Enureso_CCRES_delta0_trueN[i]  -> Write();
    h1_Enureso_NC_trueN[i]            -> Write();
  }

  for (int i=0; i<WINSTEP; i++) {
    g_NoiseRate[i] -> Write();
  }
  g_NNEffwin        -> Write();
  g_NNHEffwin       -> Write();
  g_NNGdEffwin      -> Write();
  g_OverallEffwin   -> Write();
  g_OverallHEffwin  -> Write();
  g_OverallGdEffwin -> Write();

  g_NNEff         -> Write();
  g_NNHEff        -> Write();
  g_NNGdEff       -> Write();
  g_OverallEff    -> Write();
  g_OverallHEff   -> Write();
  g_OverallGdEff  -> Write();
  g_Purity        -> Write();
  g_FillNoiseRate -> Write();
}

