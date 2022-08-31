#include "Gd1RmuonSelection.h"
#include "../../../include/NeutrinoEvents.h"

void Gd1RmuonSelection::SetHistoFrame() {
  h1_1RmuonEvents = new TH1F("h1_1RmuonEvents", "Selected Neutrino Events by 1R muon Selection; ; Selection Efficiency", 6, 0, 6);
  h1_Proto1RmuonEvents = new TH1F("h1_Proto1RmuonEvents", "Selected Neutrino Events by 1R muon Selection; ; Selection Efficiency", 6, 0, 6);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_dwall[i]          = new TH1F(TString::Format("h1_dwall_mode%d", i), "h1_dwall; fiTQun Dwall[cm]; Number of Neutrino Events", 60, 0, 600);
    h1_ringnum[i]        = new TH1F(TString::Format("h1_ringnum_mode%d", i), "h1_ringnum; Number of Rings; Number of Neutrino Events", 6, 0, 6);
    h1_emulikelihood[i]  = new TH1F(TString::Format("h1_emulikelihood_mode%d", i), "h1_emulikelihood; e-#{mu} Likelihood; Number of Neutrino Events", 3000, -1500, 1500);
    h1_Pmu[i]            = new TH1F(TString::Format("h1_Pmu_mode%d", i), "h1_Pmu; #{mu} Momentum P_{#mu}[MeV]; Number of Neutrino Events", 300, 0, 3000);
    h1_pimulikelihood[i] = new TH1F(TString::Format("h1_pimulikelihood_mode%d", i), "h1_pimulikelihood; #pi^{#pm}-#{mu} Likelihood; Number of Neutrino Events", 400, -300, 100);
  }
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


  h1_dwall[0] -> SetLineColor(kAzure-1);
  h1_dwall[0] -> SetFillColor(kAzure-1);
  h1_dwall[1] -> SetFillColor(kAzure-5);
  h1_dwall[1] -> SetLineColor(kAzure-5);
  h1_dwall[2] -> SetFillColor(kTeal+9);
  h1_dwall[2] -> SetLineColor(kTeal+9);
  h1_dwall[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_dwall[3] -> SetFillColor(kPink+1);
  h1_dwall[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_dwall[4] -> SetFillColor(kPink-8);
  h1_dwall[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_dwall[5] -> SetFillColor(kGray+1);
  h1_dwall[6] -> SetLineColor(kCyan-6);   //CC other
  h1_dwall[6] -> SetFillColor(kCyan-6);

  h1_ringnum[0] -> SetLineColor(kAzure-1);
  h1_ringnum[0] -> SetFillColor(kAzure-1);
  h1_ringnum[1] -> SetFillColor(kAzure-5);
  h1_ringnum[1] -> SetLineColor(kAzure-5);
  h1_ringnum[2] -> SetFillColor(kTeal+9);
  h1_ringnum[2] -> SetLineColor(kTeal+9);
  h1_ringnum[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_ringnum[3] -> SetFillColor(kPink+1);
  h1_ringnum[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_ringnum[4] -> SetFillColor(kPink-8);
  h1_ringnum[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_ringnum[5] -> SetFillColor(kGray+1);
  h1_ringnum[6] -> SetLineColor(kCyan-6);   //CC other
  h1_ringnum[6] -> SetFillColor(kCyan-6);

  h1_emulikelihood[0] -> SetLineColor(kAzure-1);
  h1_emulikelihood[0] -> SetFillColor(kAzure-1);
  h1_emulikelihood[1] -> SetFillColor(kAzure-5);
  h1_emulikelihood[1] -> SetLineColor(kAzure-5);
  h1_emulikelihood[2] -> SetFillColor(kTeal+9);
  h1_emulikelihood[2] -> SetLineColor(kTeal+9);
  h1_emulikelihood[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_emulikelihood[3] -> SetFillColor(kPink+1);
  h1_emulikelihood[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_emulikelihood[4] -> SetFillColor(kPink-8);
  h1_emulikelihood[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_emulikelihood[5] -> SetFillColor(kGray+1);
  h1_emulikelihood[6] -> SetLineColor(kCyan-6);   //CC other
  h1_emulikelihood[6] -> SetFillColor(kCyan-6);

  h1_Pmu[0] -> SetLineColor(kAzure-1);
  h1_Pmu[0] -> SetFillColor(kAzure-1);
  h1_Pmu[1] -> SetFillColor(kAzure-5);
  h1_Pmu[1] -> SetLineColor(kAzure-5);
  h1_Pmu[2] -> SetFillColor(kTeal+9);
  h1_Pmu[2] -> SetLineColor(kTeal+9);
  h1_Pmu[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_Pmu[3] -> SetFillColor(kPink+1);
  h1_Pmu[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_Pmu[4] -> SetFillColor(kPink-8);
  h1_Pmu[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_Pmu[5] -> SetFillColor(kGray+1);
  h1_Pmu[6] -> SetLineColor(kCyan-6);   //CC other
  h1_Pmu[6] -> SetFillColor(kCyan-6);

  h1_pimulikelihood[0] -> SetLineColor(kAzure-1);
  h1_pimulikelihood[0] -> SetFillColor(kAzure-1);
  h1_pimulikelihood[1] -> SetFillColor(kAzure-5);
  h1_pimulikelihood[1] -> SetLineColor(kAzure-5);
  h1_pimulikelihood[2] -> SetFillColor(kTeal+9);
  h1_pimulikelihood[2] -> SetLineColor(kTeal+9);
  h1_pimulikelihood[3] -> SetLineColor(kPink+1);   //CC RES(Delta+)
  h1_pimulikelihood[3] -> SetFillColor(kPink+1);
  h1_pimulikelihood[4] -> SetLineColor(kPink-8);   //CC RES(Delta++)
  h1_pimulikelihood[4] -> SetFillColor(kPink-8);
  h1_pimulikelihood[5] -> SetLineColor(kGray+1);   //CC RES(Delta0)
  h1_pimulikelihood[5] -> SetFillColor(kGray+1);
  h1_pimulikelihood[6] -> SetLineColor(kCyan-6);   //CC other
  h1_pimulikelihood[6] -> SetFillColor(kCyan-6);
}


float Gd1RmuonSelection::GetemuLikelihood(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  float likelihood = numu->var<float>("pidemu");
  if (mode==1)              h1_emulikelihood[0] -> Fill(likelihood);
  if (mode>=2 && mode<=10)  h1_emulikelihood[1] -> Fill(likelihood);
  if (mode>=31)             h1_emulikelihood[2] -> Fill(likelihood);
  if (mode==13)             h1_emulikelihood[3] -> Fill(likelihood);
  if (mode==11)             h1_emulikelihood[4] -> Fill(likelihood);
  if (mode==12)             h1_emulikelihood[5] -> Fill(likelihood);
  if (mode>=14 && mode<=30) h1_emulikelihood[6] -> Fill(likelihood);

  return likelihood;
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

bool Gd1RmuonSelection::C2Apply1RCheck(EvSelVar_t evsel, CC0PiNumu* numu, TreeManager* tree) {
  bool pass = false;
  if (evsel.pass[1]==true) pass = true;

  /*int mode = TMath::Abs(numu->var<int>("mode"));
  float Enu = numu->var<float>("pnu", 0);

  if (evsel.pass[1]==false && mode==1) {
    OneRingRejectCCQE = Enu;
    tree -> FillTree();
    //std::cout << "[Gd1RmuonSelection::C2Apply1RCheck()] 1R rejected CCQE: " << Enu << " GeV" << std::endl;
  }*/

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

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_emulikelihood[i] -> Write();
  }
}

