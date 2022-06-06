#pragma once

//#define INTERACTIONTYPE 3
#define INTERACTIONTYPE 6
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
TH1F* h1_numu_x_numu_NoOsc_wTruthNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_NoOsc_woTruthNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_NoOsc_wNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_NoOsc_woNeutron[INTERACTIONTYPE];


TH1F* h1_numu_x_numu_OscProb[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProb_wTruthNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProb_woTruthNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProb_wNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProb_woNeutron[INTERACTIONTYPE];


//Selected 1R muon events (for each neutrino interaction mode)
TH1F* h1_numu_x_numu_OscProbRatio[INTERACTIONTYPE];
//Selected 1R muon events w/(o) truth neutrons (for each neutrino interaction mode)
TH1F* h1_numu_x_numu_OscProbRatio_wTruthNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProbRatio_woTruthNeutron[INTERACTIONTYPE];
//Selected 1R muon events w/(o) tagged neutrons (for each neutrino interaction mode)
TH1F* h1_numu_x_numu_OscProbRatio_wNeutron[INTERACTIONTYPE];
TH1F* h1_numu_x_numu_OscProbRatio_woNeutron[INTERACTIONTYPE];


//All Selected 1R muon events
TH1F* h1_Allnumu_x_numu_NoOsc;
//Selected 1R muon events w/(o) truth neutrons
TH1F* h1_Allnumu_x_numu_NoOsc_wTruthNeutron;
TH1F* h1_Allnumu_x_numu_NoOsc_woTruthNeutron;
//Selected 1R muon events w/(o) tagged neutrons
TH1F* h1_Allnumu_x_numu_NoOsc_wNeutron;
TH1F* h1_Allnumu_x_numu_NoOsc_woNeutron;

TH1F* h1_Allnumu_x_numu_OscProb;
//Selected 1R muon events w/(o) truth neutrons
TH1F* h1_Allnumu_x_numu_OscProb_wTruthNeutron;
TH1F* h1_Allnumu_x_numu_OscProb_woTruthNeutron;
//Selected 1R muon events w/(o) tagged neutrons
TH1F* h1_Allnumu_x_numu_OscProb_wNeutron;
TH1F* h1_Allnumu_x_numu_OscProb_woNeutron;

TH1F* h1_Allnumu_x_numu_OscProbRatio;
//Selected 1R muon events w/(o) truth neutrons
TH1F* h1_Allnumu_x_numu_OscProbRatio_wTruthNeutron;
TH1F* h1_Allnumu_x_numu_OscProbRatio_woTruthNeutron;
//Selected 1R muon events w/(o) tagged neutrons
TH1F* h1_Allnumu_x_numu_OscProbRatio_wNeutron;
TH1F* h1_Allnumu_x_numu_OscProbRatio_woNeutron;

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
    float GetWgtNeutrino_wTrueN(CC0PiNumu* numu, float NTrueN);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdNeutrinoOscillation(TFile* fout);
    void WritePlots();
};
