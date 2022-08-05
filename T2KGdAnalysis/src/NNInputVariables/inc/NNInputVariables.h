#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/EvSelVar_t.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/EvSelVar_t.h"
#include "../../DecayeBox/inc/DecayeBox.h"
#include "../../TreeManager/inc/TreeManager.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TString.h"

#define NNVARIABLES 12


TH1F* h1_NNvar_AccNoise[NNVARIABLES];
TH1F* h1_NNvar_Decaye[NNVARIABLES];
TH1F* h1_NNvar_H[NNVARIABLES];
TH1F* h1_NNvar_Gd[NNVARIABLES];


class NNInputVariables {
  public:

  	NNInputVariables(){};
  	virtual ~NNInputVariables(){};

    void SetNNvarName();

    void SetHistoFrame(int vartype, TString histtitle);
    void SetHistoFormat(int vartype, TString histtitle);
    void SetNNinputHisto();

    void GetAccNoiseNNVariables(UInt_t jentry, std::vector<float> *Label, int vartype, std::vector<float> *Var, TH1F* h1_NNvar_Noise[]);
    void GetDecayeNNVariables(UInt_t jentry, std::vector<float> *Label, int vartype, std::vector<float> *Var, TH1F* h1_NNvar_Decaye[]);
    void GetHNNVariables(UInt_t jentry, std::vector<float> *Label, int vartype, std::vector<float> *Var, TH1F* h1_NNvar_H[]);
    void GetGdNNVariables(UInt_t jentry, std::vector<float> *Label, int vartype, std::vector<float> *Var, TH1F* h1_NNvar_Gd[]);

    void cdNNInputVariables(TFile* fout);
    void WritePlots();
};

