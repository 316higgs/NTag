#include "TH1F.h"

float meanmultiplicity = 0.;

TH1F* h1_TaggedNeutrons;

void SetHistoFrame() {
  h1_TaggedNeutrons = new TH1F("h1_TaggedNeutrons", "Tagged Neutrons per Neutrino Event; Number of Tagged Neutrons per Neutrion Event; Number of Neutrino Events", 12, 0, 12);
}