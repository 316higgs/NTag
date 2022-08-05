#pragma once

#include "../src/DecayeBox/inc/DecayeBox.h"
#include "../src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"

#define SELECTIONCUTS 6
#define INTERACTIONTYPE 7

int processmax = 0;

int AllParentNeutrinos = 0;

//1R muon selection
int ProtoSelectedParentNeutrinos[SELECTIONCUTS];
int SelectedParentNeutrinos[SELECTIONCUTS];

void ResetNeutrinoEvents() {
  for (int i=0; i<SELECTIONCUTS; i++) {
    ProtoSelectedParentNeutrinos[i] = 0;
    SelectedParentNeutrinos[i] = 0;
  }
}

//Selected neutrino events
int ProtoSelectedCCQEevents    = 0;
int ProtoSelectedCCnonQEevents = 0;
int ProtoSelectedNCevents      = 0;
int SelectedCCQEevents    = 0;
int SelectedCCnonQEevents = 0;
int SelectedNCevents      = 0;

//Oscillated neutrino events with only legacy neutrino selection
float OscillatedCCQE    = 0.;
float OscillatedCCnonQE = 0.;
float OscillatedCCRES0  = 0.;
float OscillatedCCRESp  = 0.;
float OscillatedCCRESpp = 0.;
float OscillatedCCOther = 0.;
float OscillatedNC      = 0.;

//Oscillated neutrino events w/ tagged neutrons
float OscillatedCCQE_wTagN    = 0.;
float OscillatedCCnonQE_wTagN = 0.;
float OscillatedCCRES0_wTagN  = 0.;
float OscillatedCCRESp_wTagN  = 0.;
float OscillatedCCRESpp_wTagN = 0.;
float OscillatedCCOther_wTagN = 0.;
float OscillatedNC_wTagN      = 0.;

//Oscillated neutrino events w/o tagged neutrons
float OscillatedCCQE_woTagN    = 0.;
float OscillatedCCnonQE_woTagN = 0.;
float OscillatedCCRES0_woTagN  = 0.;
float OscillatedCCRESp_woTagN  = 0.;
float OscillatedCCRESpp_woTagN = 0.;
float OscillatedCCOther_woTagN = 0.;
float OscillatedNC_woTagN      = 0.;

//Oscillated neutrino events w/ truth neutrons
float OscillatedCCQE_wTrueN    = 0.;
float OscillatedCCnonQE_wTrueN = 0.;
float OscillatedCCRES0_wTrueN  = 0.;
float OscillatedCCRESp_wTrueN  = 0.;
float OscillatedCCRESpp_wTrueN = 0.;
float OscillatedCCOther_wTrueN = 0.;
float OscillatedNC_wTrueN      = 0.;

//Oscillated neutrino events w/o truth neutrons
float OscillatedCCQE_woTrueN    = 0.;
float OscillatedCCnonQE_woTrueN = 0.;
float OscillatedCCRES0_woTrueN  = 0.;
float OscillatedCCRESp_woTrueN  = 0.;
float OscillatedCCRESpp_woTrueN = 0.;
float OscillatedCCOther_woTrueN = 0.;
float OscillatedNC_woTrueN      = 0.;

//Oscillated neutrino events within [0.25 GeV, 1.5 GeV]
float NoOscLegacy   = 0.;
float NoOscOnlyCCQE = 0.;
float NoOscwoTrueN  = 0.;
float NoOscwoTagN   = 0.;

float OscLegacy   = 0.;
float OscOnlyCCQE = 0.;
float OscwoTrueN  = 0.;
float OscwoTagN   = 0.;


//1R muon selection + w/o truth neutrons
int SelectedNeutrinoswoTruthNeutrons = 0;
int ProtoSelectedNeutrinoswoTruthNeutrons = 0;


void Sequencial1RmuonSelection(Gd1RmuonSelection prmsel,
                               EvSelVar_t evsel,
                               CC0PiNumu* numu,
                               DecayeBox decayebox, 
                               BeamMode::E_BEAM_MODE eMode, 
                               OscChan::E_OSC_CHAN eOsc,
                               float dtCut,
                               float N50CutMin,
                               float N50CutMax,
                               bool dtvsn50fill) 
{
  if (prmsel.C1ApplyFCFV(evsel)) {
    SelectedParentNeutrinos[0]++;
    ProtoSelectedParentNeutrinos[0]++;

    if (prmsel.C2Apply1R(evsel)) {
      SelectedParentNeutrinos[1]++;
      ProtoSelectedParentNeutrinos[1]++;

      if (prmsel.C3Applymuonlike(evsel)) {
        SelectedParentNeutrinos[2]++;
        ProtoSelectedParentNeutrinos[2]++;

        if (prmsel.C4ApplyPmu200MeV(evsel)) {
          SelectedParentNeutrinos[3]++;
          ProtoSelectedParentNeutrinos[3]++;
          decayebox.GetTaggedDecaye(numu);

          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill)) {
            SelectedParentNeutrinos[4]++;

            if (prmsel.C6Applynotpionlike(evsel)) {
              SelectedParentNeutrinos[5]++;
            }
          }

          if (prmsel.C5ApplyProtodecaye(evsel)) {
            ProtoSelectedParentNeutrinos[4]++;

            if (prmsel.C6Applynotpionlike(evsel)) {
              ProtoSelectedParentNeutrinos[5]++;
            }
          }
        }
      }
    }
  }
}

void Sequencial1RmuonSelection_Pion(Gd1RmuonSelection prmsel,
                                    EvSelVar_t evsel,
                                    CC0PiNumu* numu,
                                    DecayeBox decayebox, 
                                    BeamMode::E_BEAM_MODE eMode, 
                                    OscChan::E_OSC_CHAN eOsc,
                                    float dtCut,
                                    float N50CutMin,
                                    float N50CutMax,
                                    bool dtvsn50fill) 
{
  //CC pion productions
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==11 || mode==12 || mode==13 || mode==21) {
    if (prmsel.C1ApplyFCFV(evsel)) {
      SelectedParentNeutrinos[0]++;
      ProtoSelectedParentNeutrinos[0]++;

      if (prmsel.C2Apply1R(evsel)) {
        SelectedParentNeutrinos[1]++;
        ProtoSelectedParentNeutrinos[1]++;

        if (prmsel.C3Applymuonlike(evsel)) {
          SelectedParentNeutrinos[2]++;
          ProtoSelectedParentNeutrinos[2]++;

          if (prmsel.C4ApplyPmu200MeV(evsel)) {
            SelectedParentNeutrinos[3]++;
            ProtoSelectedParentNeutrinos[3]++;

            if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill)) {
              SelectedParentNeutrinos[4]++;

              if (prmsel.C6Applynotpionlike(evsel)) {
                SelectedParentNeutrinos[5]++;
              }
            }

            if (prmsel.C5ApplyProtodecaye(evsel)) {
              ProtoSelectedParentNeutrinos[4]++;

              if (prmsel.C6Applynotpionlike(evsel)) {
                ProtoSelectedParentNeutrinos[5]++;
              }
            }
          }
        }
      }
    }
  }
}


void GetSelectedModeEvents(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==1) SelectedCCQEevents++;
  if (mode>=2 && mode<=30) SelectedCCnonQEevents++;
  if (mode>=31) SelectedNCevents++;
}

void GetProtoSelectedModeEvents(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==1) ProtoSelectedCCQEevents++;
  if (mode>=2 && mode<=30) ProtoSelectedCCnonQEevents++;
  if (mode>=31) ProtoSelectedNCevents++;
}

