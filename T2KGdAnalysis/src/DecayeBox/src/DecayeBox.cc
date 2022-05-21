#include "../include/NeutrinoEvents.h"
#include "DecayeBox.h"
#include "TGaxis.h"

void DecayeBox::SetHistoFrame() {
  h2_dtn50 = new TH2D("h2_dtn50", "dt vs N50; dt[#musec]; N50", 100, 0, 50, 40, 0, 400);
  h2_dtn50 -> SetTitleOffset(1.3, "Y");
  h2_dtn50 -> SetTitleSize(0.035, "Y");
  h2_dtn50 -> SetLabelSize(0.035, "Y");
  h2_dtn50 -> SetTitleSize(0.035, "X");
  h2_dtn50 -> SetLabelSize(0.035, "X");
  h2_dtn50 -> SetStats(0);
  ((TGaxis*)h2_dtn50->GetXaxis())->SetMaxDigits(3);
}


int DecayeBox::GetDecayeInBox(CC0PiNumu* numu, 
	                            BeamMode::E_BEAM_MODE eMode, 
	                            OscChan::E_OSC_CHAN eOsc,
	                            float dtCut,
	                            float N50CutMin,
	                            float N50CutMax,
                              bool histofill) 
{
  int Decaye = 0;
  const int nse = numu->var<int>("fqnse");
  for (int jsub=1; jsub<nse; jsub++) {
    float dt  = numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0);
    float N50 = numu->var<int>("fqn50", jsub);
    if (histofill==true) h2_dtn50 -> Fill(dt/1000., N50);

    if (dt/1000. < dtCut && N50 >= N50CutMin && N50 <= N50CutMax) Decaye++;
  }
  return Decaye;
}

void DecayeBox::cdDecayeBox(TFile* fout) {
  fout -> mkdir("DecayeBox");
  fout -> cd("DecayeBox");
}


void DecayeBox::WritePlots() {
  h2_dtn50 -> Scale(1./SelectedParentNeutrinos[5]);
  h2_dtn50 -> Write();
}
