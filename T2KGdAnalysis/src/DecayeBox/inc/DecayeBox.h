#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TH2D.h"

//number of decay-e
TH1F* h1_TaggedDecaye;
TH1F* h1_TaggedDecaye_CCQE;
TH1F* h1_TaggedDecaye_CCpi;

//dt vs N50 for decay-e cut
TH2D* h2_dtn50;

class DecayeBox {
  public:
  	DecayeBox(){};
  	virtual ~DecayeBox(){};

  	int GetDecayeInBox(CC0PiNumu* numu, 
  		               BeamMode::E_BEAM_MODE eMode, 
  		               OscChan::E_OSC_CHAN eOsc,
  		               float dtCut,
	                   float N50CutMin,
	                   float N50CutMax,
	                   bool histofill);

  	int GetTaggedDecaye(CC0PiNumu* numu);

  	void SetHistoFrame();
  	void SetHistoFormat();
    void cdDecayeBox(TFile* fout);
  	void WritePlots();
};
