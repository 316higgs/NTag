#include <TFile.h>
#include <TH1.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TStyle.h>

void Dist() {
	TFile* fwodummy = new TFile("test_lentuple.wo.mccomb.root");
	TFile* fwdummy  = new TFile("test_lentuple.root");

	TTree* tree = static_cast<TTree*>(fwdummy->Get("h1"));

    float Tiskz[685] = 0.;
	tree -> SetBranchAddress("tiskz", Tiskz[685]);

	int ndata = tree->GetEntries();
	//std::cout << ndata << std::endl;

	for (int i=0; i<ndata; i++) {
		tree -> GetEntry(i);

		std::cout << "PMT hit: " << Tiskz[i] << std::endl;
	}
}