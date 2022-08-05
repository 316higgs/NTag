#include "../include/NeutrinoEvents.h"
#include "DecayeBox.h"
#include "TGaxis.h"

void DecayeBox::SetHistoFrame() {
  h1_TaggedDecaye = new TH1F("h1_TaggedDecaye", "h1_TaggedDecaye; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_TaggedDecaye_CCQE = new TH1F("h1_TaggedDecaye_CCQE", "h1_TaggedDecaye@CCQE; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_TaggedDecaye_CCpi = new TH1F("h1_TaggedDecaye_CCpi", "h1_TaggedDecaye@CCPi; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);

  h2_dtn50 = new TH2D("h2_dtn50", "dt vs N50; dt[#musec]; N50", 100, 0, 50, 40, 0, 400);
  h2_dtn50 -> SetTitleOffset(1.3, "Y");
  h2_dtn50 -> SetTitleSize(0.035, "Y");
  h2_dtn50 -> SetLabelSize(0.035, "Y");
  h2_dtn50 -> SetTitleSize(0.035, "X");
  h2_dtn50 -> SetLabelSize(0.035, "X");
  h2_dtn50 -> SetStats(0);
  ((TGaxis*)h2_dtn50->GetXaxis())->SetMaxDigits(3);
}

void DecayeBox::SetHistoFormat() {
  h1_TaggedDecaye      -> SetLineWidth(2);
  h1_TaggedDecaye_CCQE -> SetLineWidth(2);
  h1_TaggedDecaye_CCpi -> SetLineWidth(2);
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
  int mode = TMath::Abs(numu->var<int>("mode"));
  for (int jsub=1; jsub<nse; jsub++) {
    float dt  = numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0);
    float N50 = numu->var<int>("fqn50", jsub);
    if (histofill==true && mode<=2 && nse==2) h2_dtn50 -> Fill(dt/1000., N50);

    if (dt/1000. < dtCut && N50 >= N50CutMin && N50 <= N50CutMax) Decaye++;
  }
  return Decaye;
}

int DecayeBox::GetTaggedDecaye(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  //All interactions
  h1_TaggedDecaye -> Fill(numu->var<int>("fqdcye"));

  //CCQE
  if (mode==1) h1_TaggedDecaye_CCQE -> Fill(numu->var<int>("fqdcye"));

  //CC pion productions
  if (mode==11 || mode==12 || mode==13 || mode==21) h1_TaggedDecaye_CCpi -> Fill(numu->var<int>("fqdcye"));

  return numu->var<int>("fqdcye");
}

void DecayeBox::cdDecayeBox(TFile* fout) {
  fout -> mkdir("DecayeBox");
  fout -> cd("DecayeBox");
}


void DecayeBox::WritePlots() {
  Double_t tot_decaye = h1_TaggedDecaye->Integral();
  h1_TaggedDecaye -> Scale(1./tot_decaye);
  h1_TaggedDecaye -> Write();

  Double_t tot_decaye_CCQE = h1_TaggedDecaye_CCQE->Integral();
  h1_TaggedDecaye_CCQE -> Scale(1./tot_decaye_CCQE);
  h1_TaggedDecaye_CCQE -> Write();

  Double_t tot_decaye_CCpi = h1_TaggedDecaye_CCpi->Integral();
  h1_TaggedDecaye_CCpi -> Scale(1./tot_decaye_CCpi);
  h1_TaggedDecaye_CCpi -> Write();

  h2_dtn50 -> Scale(1./SelectedParentNeutrinos[5]);
  h2_dtn50 -> Write();
}
