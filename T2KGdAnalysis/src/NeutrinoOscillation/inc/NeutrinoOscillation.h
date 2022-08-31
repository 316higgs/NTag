#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "../../../include/NeutrinoEvents.h"
#include "TH2D.h"

//Oscillation probability
TH1F* h1_OscProbcheck;

//Neutrino energy distribution
TH1F* h1_Enutrue[INTERACTIONTYPE];
TH1F* h1_Enureco[INTERACTIONTYPE];
TH1F* h1_Enureso[INTERACTIONTYPE];
TH1F* h1_AllEnutrue;
TH1F* h1_AllEnureco;
TH1F* h1_AllEnureso;

TH1F* h1_EnuresoCCnonQE;
TH1F* h1_EnuresoCCRES_deltap;
TH1F* h1_EnuresoCCRES_deltapp;
TH1F* h1_EnuresoCCRES_delta0;

TH2F* h2_Reso_x_TrueEnu;

//Truth neutrino events as a function of neutrino energy
TH1F* h1_TruthOscProb[INTERACTIONTYPE];

//Reconstructed neutrino events as a funtion of neutrino energy
TH1F* h1_NoOsc[INTERACTIONTYPE];

TH1F* h1_OscProb[INTERACTIONTYPE];
TH1F* h1_OscProb_wNeutron[INTERACTIONTYPE];
TH1F* h1_OscProb_woNeutron[INTERACTIONTYPE];


//Selected 1R muon events (for each neutrino interaction mode)
TH1F* h1_OscProbRatio[INTERACTIONTYPE];

TH1F* h1_All_NoOsc;
TH1F* h1_All_OscProbRatio;

//Selected 1R muon events w/(o) truth neutrons
TH1F* h1_All_NoOsc_woTruthNeutron;
//Selected 1R muon events w/(o) tagged neutrons
TH1F* h1_All_NoOsc_woNeutron;

//Selected 1R muon events w/(o) truth neutrons
TH1F* h1_All_OscProbRatio_woTruthNeutron;
//Selected 1R muon events w/(o) tagged neutrons
TH1F* h1_All_OscProbRatio_woNeutron;


TH2F* h2_TrueMuDirectionXY;
TH2F* h2_TrueMuDirectionRZ;
TH2F* h2_RecoMuDirectionXY;
TH2F* h2_RecoMuDirectionRZ;

TH1F* h1_Truecosthetamu[INTERACTIONTYPE];
TH1F* h1_Recocosthetamu;
TH1F* h1_Resocosthetamu;
TH1F* h1_EnuRecoPrediction;
TH1F* h1_EnuResoPrediction;
TH2F* h2_pmu_x_costhetamu;
TH2F* h2_EnuReso_x_costhetamu;

class NeutrinoOscillation {
  public:
  	NeutrinoOscillation() {};
  	virtual ~NeutrinoOscillation() {};

    float GetTrueEnu(CC0PiNumu* numu);
    float GetRecoEnu(CC0PiNumu* numu);
    float GetEnuResolution(CC0PiNumu* numu, float theta, float thetamin, float thetamax);
    void  GetReso_x_TrueEnu(CC0PiNumu* numu);
    float GetTrueMuDirection(CC0PiNumu* numu, 
                             Int_t Npvc, 
                             Int_t* Ipvc,
                             Float_t Pvc[][3],
                             Int_t*  Iflvc,
                             Int_t*  Ichvc);
    float GetEnuRecoPrediction(float pmu, float costhetamu);
    float GetEnuResoPrediction(CC0PiNumu* numu, float Enu);
    float GetRecoMuDirection(CC0PiNumu* numu);
    float GetMuDirResolution(float truecostheta, float recocostheta);

    float OscProbCalculator(CC0PiNumu* numu, bool histfill);
    float GetWgtNeutrino(CC0PiNumu* numuC, float theta, float thetamin, float thetamax);
    float GetWgtNeutrino_wTrueN(CC0PiNumu* numu, float NTrueN, float theta, float thetamin, float thetamax);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdNeutrinoOscillation(TFile* fout);
    void WritePlots();
};
