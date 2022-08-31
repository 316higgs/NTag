#include "TH1F.h"

float Truthmeanmultiplicity         = 0.;
float Truthmeanmultiplicity_CCQE    = 0.;
float Truthmeanmultiplicity_CCnonQE = 0.;

float meanmultiplicity         = 0.;
float meanmultiplicity_CCQE    = 0.;
float meanmultiplicity_CCnonQE = 0.;

TH1F* h1_TruthNeutrons;
TH1F* h1_TruthNeutrons_CCQE;
TH1F* h1_TruthNeutrons_CCnonQE;

TH1F* h1_TaggedNeutrons;
TH1F* h1_TaggedNeutrons_CCQE;
TH1F* h1_TaggedNeutrons_CCnonQE;

void SetHistoFrame() {
  h1_TruthNeutrons         = new TH1F("h1_TruthNeutrons", "Truth Neutrons per Neutrino Event; Number of Truth Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);
  h1_TruthNeutrons_CCQE    = new TH1F("h1_TruthNeutrons_CCQE", "Truth Neutrons per Neutrino Event; Number of Truth Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);
  h1_TruthNeutrons_CCnonQE = new TH1F("h1_TruthNeutrons_CCnonQE", "Truth Neutrons per Neutrino Event; Number of Truth Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);

  h1_TaggedNeutrons         = new TH1F("h1_TaggedNeutrons", "Tagged Neutrons per Neutrino Event; Number of Tagged Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);
  h1_TaggedNeutrons_CCQE    = new TH1F("h1_TaggedNeutrons_CCQE", "Tagged Neutrons per Neutrino Event; Number of Tagged Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);
  h1_TaggedNeutrons_CCnonQE = new TH1F("h1_TaggedNeutrons_CCnonQE", "Tagged Neutrons per Neutrino Event; Number of Tagged Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);
}