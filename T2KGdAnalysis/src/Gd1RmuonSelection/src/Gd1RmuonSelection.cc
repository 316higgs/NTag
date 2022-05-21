#include "Gd1RmuonSelection.h"
#include "../../../include/NeutrinoEvents.h"

void Gd1RmuonSelection::SetHistoFrame() {
  h1_1RmuonEvents = new TH1F("h1_1RmuonEvents", "Selected Neutrino Events by 1R muon Selection; ; Entries", 6, 0, 6);
  h1_Proto1RmuonEvents = new TH1F("h1_Proto1RmuonEvents", "Selected Neutrino Events by 1R muon Selection; ; Entries", 6, 0, 6);
}

void Gd1RmuonSelection::SetHistoFormat() {
  h1_1RmuonEvents -> SetLineWidth(2);
  h1_1RmuonEvents -> SetLineColor(kOrange+0);
  h1_1RmuonEvents -> SetTitleOffset(1.4, "Y");
  h1_1RmuonEvents -> SetTitleSize(0.035, "Y");
  h1_1RmuonEvents -> SetLabelSize(0.033, "Y");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
  h1_1RmuonEvents -> SetStats(0);

  h1_Proto1RmuonEvents -> SetLineWidth(2);
  h1_Proto1RmuonEvents -> SetLineColor(kOrange+0);
  h1_Proto1RmuonEvents -> SetLineStyle(2);
  h1_Proto1RmuonEvents -> SetTitleOffset(1.4, "Y");
  h1_Proto1RmuonEvents -> SetTitleSize(0.035, "Y");
  h1_Proto1RmuonEvents -> SetLabelSize(0.033, "Y");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
  h1_Proto1RmuonEvents -> SetStats(0);
}


bool Gd1RmuonSelection::C1ApplyFCFV(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[0]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C2Apply1R(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[1]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C3Applymuonlike(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[2]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C4ApplyPmu200MeV(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[3]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C5Applydecaye(EvSelVar_t evsel,
	                                  CC0PiNumu* numu,
	                                  DecayeBox decayebox, 
	                                  BeamMode::E_BEAM_MODE eMode, 
	                                  OscChan::E_OSC_CHAN eOsc,
	                                  float dtCut,
	                                  float N50CutMin,
	                                  float N50CutMax,
                                    bool dtvsn50fill) 
{
  bool pass = false;
  int NumDecaye = decayebox.GetDecayeInBox(numu, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill);
  //std::cout << "NumDecaye in Gd1RmuonSelection::C5Applydecaye: " << NumDecaye << std::endl;
  if (NumDecaye<=1) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C5ApplyProtodecaye(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[4]==true) pass = true;
  return pass;	
}

bool Gd1RmuonSelection::C6Applynotpionlike(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[5]==true) pass = true;
  return pass;
}


bool Gd1RmuonSelection::Apply1RmuonSelection(EvSelVar_t evsel,
                                             CC0PiNumu* numu, 
	                                           DecayeBox decayebox, 
	                                           BeamMode::E_BEAM_MODE eMode, 
	                                           OscChan::E_OSC_CHAN eOsc,
	                                           float dtCut,
	                                           float N50CutMin,
	                                           float N50CutMax,
                                             bool dtvsn50fill) 
{
  bool pass = false;
  if (evsel.pass[0]==true &&
  	  evsel.pass[1]==true &&
  	  evsel.pass[2]==true &&
  	  evsel.pass[3]==true) 
  {
  	int NumDecaye = decayebox.GetDecayeInBox(numu, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill);
  	if (NumDecaye<=1 && evsel.pass[5]==true) pass = true;
  }
  return pass;
}

bool Gd1RmuonSelection::ApplyProto1RmuonSelection(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[0]==true &&
  	  evsel.pass[1]==true &&
  	  evsel.pass[2]==true &&
  	  evsel.pass[3]==true &&
  	  evsel.pass[4]==true &&
  	  evsel.pass[5]==true) 
  {
  	pass = true;
  }
  return pass;
}

void Gd1RmuonSelection::cdGd1RmuonSelection(TFile* fout) {
  fout -> mkdir("Gd1RmuonSelection");
  fout -> cd("Gd1RmuonSelection");
}

void Gd1RmuonSelection::WritePlots() {
  h1_1RmuonEvents      -> Write();
  h1_Proto1RmuonEvents -> Write();
}

