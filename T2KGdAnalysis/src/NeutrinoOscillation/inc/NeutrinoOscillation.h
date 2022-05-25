#pragma once

#define INTERACTIONTYPE 3
#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TH2D.h"

//Oscillation probability
TH1F* h1_OscProb;

//Neutrino energy distribution
TH1F* h1_Enutrue[INTERACTIONTYPE];
TH1F* h1_Enureco[INTERACTIONTYPE];
TH1F* h1_Enureso[INTERACTIONTYPE];
TH1F* h1_AllEnutrue;
TH1F* h1_AllEnureco;
TH1F* h1_AllEnureso;
TH1F* h1_EnuresoCCRES_deltap;
TH1F* h1_EnuresoCCRES_deltapp;
TH1F* h1_EnuresoCCRES_delta0;
TH2F* h2_Reso_x_TrueEnu;

//Reconstructed neutrino events as a funtion of neutrino energy
TH1F* h1_numu_x_numu_NoOsc[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_NoOsc_wNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_NoOsc_woNeutron[INTERACTIONTYPE];

TH1F* h1_numu_x_numu_OscProb[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProb_wNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProb_woNeutron[INTERACTIONTYPE];

TH1F* h1_numu_x_numu_OscProbRatio[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProbRatio_wNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProbRatio_woNeutron[INTERACTIONTYPE];

TH1F* h1_Allnumu_x_numu_NoOsc;
TH1F* h1_Allnumu_x_numu_OscProb;
TH1F* h1_Allnumu_x_numu_OscProbRatio;

class NeutrinoOscillation {
  public:
  	NeutrinoOscillation() {};
  	virtual ~NeutrinoOscillation() {};

    float GetTrueEnu(CC0PiNumu* numu);
    float GetRecoEnu(CC0PiNumu* numu);
    float GetEnuResolution(CC0PiNumu* numu);
    void  GetReso_x_TrueEnu(CC0PiNumu* numu);

    float OscProbCalculator(CC0PiNumu* numu, bool histfill);
    float GetWgtNeutrino(CC0PiNumu* numu);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdNeutrinoOscillation(TFile* fout);
    void WritePlots();
};
