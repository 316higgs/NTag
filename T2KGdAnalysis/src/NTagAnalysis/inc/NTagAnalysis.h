#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "TH1D.h"
#include "TFile.h"
#include "TGraphErrors.h"
//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "../../DistanceViewer/inc/DistanceViewer.h"
#include "../../NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "../../../include/NeutrinoEvents.h"

#define TRUETYPE 3
#define WINSTEP 6
#define WINDOWMIN 3
#define NOISECUT 18

TH1F* h1_NTrueN[TRUETYPE];
TH1F* h1_TrueNmultiplicity[INTERACTIONTYPE];
TH1F* h1_TotGammaE;

//Neutrino energy resolution w/ truth neutrons & w/o truth neutrons
TH1F* h1_Enureso_CCQE_trueN[2];
TH1F* h1_Enureso_CC2p2h_trueN[2];
TH1F* h1_Enureso_CCRES_deltap_trueN[2];
TH1F* h1_Enureso_CCRES_deltapp_trueN[2];
TH1F* h1_Enureso_CCRES_delta0_trueN[2];
TH1F* h1_Enureso_CCOther_trueN[2];
TH1F* h1_Enureso_NC_trueN[2];

//Neutrino energy resolution w/ tagged neutrons & w/o tagged neutrons
TH1F* h1_Enureso_All[2];
TH1F* h1_Enureso_CCnonQE[2];
TH1F* h1_Enureso_CCQE[2];
TH1F* h1_Enureso_CC2p2h[2];
TH1F* h1_Enureso_CCRES_deltap[2];
TH1F* h1_Enureso_CCRES_deltapp[2];
TH1F* h1_Enureso_CCRES_delta0[2];
TH1F* h1_Enureso_CCOther[2];
TH1F* h1_Enureso_NC[2];

//Noise rate and efficiencies for window optimization
TGraphErrors* g_NoiseRate[WINSTEP];

TGraphErrors* g_NNEffwin;
TGraphErrors* g_NNHEffwin;
TGraphErrors* g_NNGdEffwin;
TGraphErrors* g_OverallEffwin;
TGraphErrors* g_OverallHEffwin;
TGraphErrors* g_OverallGdEffwin;

TGraphErrors* g_NNEff;
TGraphErrors* g_NNHEff;
TGraphErrors* g_NNGdEff;
TGraphErrors* g_OverallEff;
TGraphErrors* g_OverallHEff;
TGraphErrors* g_OverallGdEff;

TGraphErrors* g_Purity;
TGraphErrors* g_FillNoiseRate;

int test1 = 0;
int test2 = 0;

int varwindowmax = 9999;

void SetWindowMax(int i) {
  switch (i) {
    case 0:
      varwindowmax = 535;
      break;
    case 1:
      varwindowmax = 400;
      break;
    case 2:
      varwindowmax = 350;
      break;
    case 3:
      varwindowmax = 300;
      break;
    case 4:
      varwindowmax = 250;
      break;
    case 5:
      varwindowmax = 200;
      break;
    default:
      std::cout << "varwindowmax is invalid." << std::endl;
      break;
  }
}

//Window max for scan graph
float WindowMax[WINSTEP]; //Step of time window scan
float eWindowMax[WINSTEP];

bool nonzeroTaggedNeutrons = false;
bool NoNeutron             = false;
bool NoNlike               = false;
bool OnlyOneisDecaye       = false;
bool OnlyOneNlike          = false;

void FlagReset() {
  nonzeroTaggedNeutrons = false;
  NoNlike               = false;
  NoNeutron             = false;
  OnlyOneisDecaye       = false;
  OnlyOneNlike          = false;
}


class NTagAnalysis {
  private:
    int AllTruthNeutrons;
    int TruthHNeutrons;
    int TruthGdNeutrons;
    int AllTruthCCQENeutrons;
    int TruthCCQEHNeutrons;
    int TruthCCQEGdNeutrons;
    int AllTruthNeutronsinFV;
    int TruthHNeutronsinFV;
    int TruthGdNeutronsinFV;

    //Truth particles in search window [3 us, XXX us]
    int AllTruthNeutronsinSearch[WINSTEP];
    int TruthHNeutronsinSearch[WINSTEP];
    int TruthGdNeutronsinSearch[WINSTEP];
    int AllTruthNeutronsinSearchFV[WINSTEP];
    int TruthHNeutronsinSearchFV[WINSTEP];
    int TruthGdNeutronsinSearchFV[WINSTEP];
    int TruthDecayeinSearch[WINSTEP];

    //All candidates in window [3 us, XXX us]
    int AllCandidatesinWin[WINSTEP];
    //Truth breakdown of candidates in window [3 us, XXX us]
    int TruthNeutroninCandidatesinWin[WINSTEP];
    int TruthHNeutroninCandidatesinWin[WINSTEP];
    int TruthGdNeutroninCandidatesinWin[WINSTEP];
    int TruthDecayeinCandidatesinWin[WINSTEP];
    int TruthAccNoiseinCandidatesinWin[WINSTEP];

    //All candidates in window [3 us, XXX us] and in FV
    int AllCandidatesinWinFV[WINSTEP];
    //Truth breakdown of candidates in window [3 us, XXX us] and in FV
    int TruthNeutroninCandidatesinWinFV[WINSTEP];
    int TruthHNeutroninCandidatesinWinFV[WINSTEP];
    int TruthGdNeutroninCandidatesinWinFV[WINSTEP];
    int TruthDecayeinCandidatesinWinFV[WINSTEP];
    int TruthAccNoiseinCandidatesinWinFV[WINSTEP];

    //n-like candidates
    //Taggged truth neutrons/Mis-tagged decay-e/Mis-tagged acc. noise
    int TaggedTruthNeutronsinWin[WINSTEP][CUTSTEP];
    int TaggedTruthHNeutronsinWin[WINSTEP][CUTSTEP];
    int TaggedTruthGdNeutronsinWin[WINSTEP][CUTSTEP];
    int MisTaggedDecayeinNlike[WINSTEP][CUTSTEP];
    int MisTaggedAccNoiseinNlike[WINSTEP][CUTSTEP];
    int AllNlikeCandidates[WINSTEP][CUTSTEP];

    int TaggedTruthNeutronsinWinFV[WINSTEP][CUTSTEP];
    int TaggedTruthHNeutronsinWinFV[WINSTEP][CUTSTEP];
    int TaggedTruthGdNeutronsinWinFV[WINSTEP][CUTSTEP];
    int MisTaggedDecayeinNlikeFV[WINSTEP][CUTSTEP];
    int MisTaggedAccNoiseinNlikeFV[WINSTEP][CUTSTEP];
    int AllNlikeCandidatesFV[WINSTEP][CUTSTEP];

    //e-like candidates
    //Taggged truth decay-e/Mis-tagged neutrons/Mis-tagged acc. noise
    int TaggedTruthDecayeinWin[WINSTEP][CUTSTEP];
    int MisTaggedTruthNeutronsinElike[WINSTEP][CUTSTEP];
    int MisTaggedTruthHNeutronsinElike[WINSTEP][CUTSTEP];
    int MisTaggedTruthGdNeutronsinElike[WINSTEP][CUTSTEP];
    int MisTaggedAccNoiseinElike[WINSTEP][CUTSTEP];
    int AllElikeCandidates[WINSTEP][CUTSTEP];

    //
    float NoiseRate[WINSTEP][CUTSTEP];
    float eNoiseRate[WINSTEP][CUTSTEP];

    //Efficiencies for window optimization
    float NNEffinWin[WINSTEP];
    float NNHEffinWin[WINSTEP];
    float NNGdEffinWin[WINSTEP];
    float eNNEffinWin[WINSTEP];
    float eNNHEffinWin[WINSTEP];
    float eNNGdEffinWin[WINSTEP];

    float OverallEffinWin[WINSTEP];
    float OverallHEffinWin[WINSTEP];
    float OverallGdEffinWin[WINSTEP];
    float eOverallEffinWin[WINSTEP];
    float eOverallHEffinWin[WINSTEP];
    float eOverallGdEffinWin[WINSTEP];

    //Integrated efficiencies
    float PreEff;
    float PreHEff;
    float PreGdEff;

    float PreEffinFV;
    float PreHEffinFV;
    float PreGdEffinFV;

    float NNEff[CUTSTEP];
    float NNHEff[CUTSTEP];
    float NNGdEff[CUTSTEP];
    float eNNEff[CUTSTEP];
    float eNNHEff[CUTSTEP];
    float eNNGdEff[CUTSTEP];

    float NNEffinFV[CUTSTEP];
    float NNHEffinFV[CUTSTEP];
    float NNGdEffinFV[CUTSTEP];

    float OverallEff[CUTSTEP];
    float OverallHEff[CUTSTEP];
    float OverallGdEff[CUTSTEP];
    float eOverallEff[CUTSTEP];
    float eOverallHEff[CUTSTEP];
    float eOverallGdEff[CUTSTEP];

    float OverallEffinFV[CUTSTEP];
    float OverallHEffinFV[CUTSTEP];
    float OverallGdEffinFV[CUTSTEP];

    float Purity[CUTSTEP];
    float ePurity[CUTSTEP];
    float FillPurity[CUTSTEP-1];
    float FillePurity[CUTSTEP-1];
    float FillNoiseRate[CUTSTEP-1];
    float FilleNoiseRate[CUTSTEP-1];
    float FillTMVATH[CUTSTEP-1];
    float FilleTMVATH[CUTSTEP-1];

    //Neutrino events with neutron information
    float NeutrinoEventswNoNlike[CUTSTEP];
    float NeutrinoEventswNlikes[CUTSTEP];
    float NeutrinoEventswOneNlike[CUTSTEP];
    float NeutrinoEventswOneNlikeDecaye[CUTSTEP];
    float NeutrinoEventswNoTruthNeutrons[CUTSTEP];

  public:
  	NTagAnalysis() {};
  	virtual ~NTagAnalysis() {};

    void InitNeutrons();

    void GetTruthNeutrons(float NTrueN,
                          CC0PiNumu* numu, 
                          std::vector<int> *Type,
                          std::vector<float> *E,
                          std::vector<float> *DWall);

    void GetTruthNeutronsIntType(CC0PiNumu* numu, float NTrueN);

    void GetTruthNeutronsinSearch(UInt_t truthneutrons, 
                                  std::vector<int> *Type,
                                  std::vector<float> *t,
                                  float WinMin,
                                  std::vector<float> *E,
                                  std::vector<float> *DWall);
    void GetTruthDecayeinSearch(UInt_t truthneutrons, 
                                  std::vector<int> *Type,
                                  std::vector<float> *t,
                                  float WinMin);
    void SummaryTruthInfoinSearch(float WinMin, TString outputname);

    void TruthBreakdowninWindow(std::vector<float> *TagClass, 
                                std::vector<float> *t,
                                std::vector<float> *DWall,
                                std::vector<float> *TagIndex,
                                std::vector<float> *Label,
                                std::vector<float> *FitT,
                                std::vector<float> *TagDWall);

    void GetNlikeCandidatesinWindow(std::vector<float> *t,
                                    std::vector<float> *DWall,
                                    std::vector<float> *TagIndex,
                                    bool etagmode,
                                    std::vector<float> *NHits,
                                    std::vector<float> *FitT,
                                    std::vector<float> *TagOut,
                                    std::vector<float> *Label,
                                    std::vector<float> *TagDWall);
    void GetElikeCandidatesinWindow(std::vector<float> *t,
                                    std::vector<float> *TagIndex,
                                    bool etagmode,
                                    std::vector<float> *NHits,
                                    std::vector<float> *FitT,
                                    std::vector<float> *TagOut,
                                    std::vector<float> *Label);

    void GetNeutrinoEventswNTag(std::vector<float> *TagOut,
                                std::vector<float> *TagIndex,
                                std::vector<float> *NHits,
                                std::vector<float> *FitT,
                                std::vector<float> *Label,
                                float NTrueN,
                                bool etagmode,
                                CC0PiNumu* numu,
                                NeutrinoOscillation neuosc,
                                int NCUT,
                                float theta, float thetamin, float thetamax);

    void GetResolutionwTrueN(CC0PiNumu* numu, float NTrueN);

  	bool DecayelikeChecker(bool etagmode, float NHits, float FitT);

    void Set1RmuonSamplewNTag(bool NoNlike, CC0PiNumu* numu, float theta, float thetamin, float thetamax);

    //For neutron multiplicity measurement
    float GetTaggedNeutrons(std::vector<float> *TagOut,
                            float Threshold,
                            std::vector<float> *TagIndex,
                            std::vector<float> *NHits,
                            std::vector<float> *FitT,
                            std::vector<float> *Label,
                            bool etagmode);

    //Noise rate and efficiencies for window optimization
    void SetNoiseRateGraph();
    void GetEfficiencyforWinOpt();
    void SetEfficiencyGraph(int windowstep);

    //Integrated efficiencies as a function of TMVA threshold
    void GetPreEfficiency(int windowstep);
    void GetNNEfficiency(int windowstep);
    void GetOverallEfficiency(int windowstep);
    void GetPurity(int windowstep);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdNTagAnalysis(TFile* fout);
    void WritePlots();
};


float GetNoiseRate(int MisTaggedDecaye, int MisTaggedAccNoise, int ParentNeutrinos,
                   int varwindowmax, int windowmin, int noisecut) 
{
  float NoiseRate = ( MisTaggedDecaye + MisTaggedAccNoise*((float)(varwindowmax - WINDOWMIN)/(varwindowmax - NOISECUT)) )/ParentNeutrinos;
  return NoiseRate;
}

