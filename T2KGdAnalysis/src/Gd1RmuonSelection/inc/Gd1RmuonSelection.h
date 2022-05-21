#pragma once

#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/EvSelVar_t.h"
#include "../../DecayeBox/inc/DecayeBox.h"
#include "TH1D.h"

//Selected events by 1R muon selection
TH1F* h1_1RmuonEvents;
TH1F* h1_Proto1RmuonEvents;


class Gd1RmuonSelection {
  public:
  	Gd1RmuonSelection(){};
  	virtual ~Gd1RmuonSelection(){};

    bool C1ApplyFCFV(EvSelVar_t evsel);
    bool C2Apply1R(EvSelVar_t evsel);
    bool C3Applymuonlike(EvSelVar_t evsel);
    bool C4ApplyPmu200MeV(EvSelVar_t evsel);
    bool C5Applydecaye(EvSelVar_t evsel,
                       CC0PiNumu* numu,
                       DecayeBox decayebox, 
                       BeamMode::E_BEAM_MODE eMode, 
                       OscChan::E_OSC_CHAN eOsc,
                       float dtCut,
                       float N50CutMin,
                       float N50CutMax,
                       bool dtvsn50fill);
    bool C5ApplyProtodecaye(EvSelVar_t evsel);
    bool C6Applynotpionlike(EvSelVar_t evsel);

    bool Apply1RmuonSelection(EvSelVar_t evsel,
                              CC0PiNumu* numu,
                              DecayeBox decayebox, 
                              BeamMode::E_BEAM_MODE eMode, 
                              OscChan::E_OSC_CHAN eOsc,
                              float dtCut,
                              float N50CutMin,
                              float N50CutMax,
                              bool dtvsn50fill);
    bool ApplyProto1RmuonSelection(EvSelVar_t evsel);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdGd1RmuonSelection(TFile* fout);
    void WritePlots();
};