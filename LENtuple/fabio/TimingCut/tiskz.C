////////////////////////////////////////////////
//                                            //
// Check plots of tiskz(for adjustment of     //
// PMT hit timing cut).                       //
//                                            //
// Author: Seidai (2021.7.13)                 //
//                                            //
////////////////////////////////////////////////

#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TString.h"
#include "TText.h"


void tiskz() {
	//TString filename = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root";
	//TString filename = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.w.timingcut1microsec.root";
	//TString filename = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.w.timingcut5microsec.root";
	TString filename = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.w.timingcut18microsec.root";
	TFile* fin = new TFile(filename);
	TTree* tree = static_cast<TTree*>fin->Get("h1");

	//h1->Scan("Entry$:tiskz");

    //TH1D* h1_hittime = new TH1D("h1_hittime", "PMT hit timing(w/o timing cut)", 300, 0, 30000); //unit is nsec
	//TH1D* h1_hittime = new TH1D("h1_hittime", "PMT hit timing(1 microsec timing cut)", 300, 0, 30000); //unit is nsec
	//TH1D* h1_hittime = new TH1D("h1_hittime", "PMT hit timing(5 microsec timing cut)", 300, 0, 30000); //unit is nsec
	TH1D* h1_hittime = new TH1D("h1_hittime", "PMT hit timing(18 microsec timing cut)", 300, 0, 30000); //unit is nsec
	h1_hittime -> SetXTitle("PMT hit timing(nsec)");
	h1_hittime -> SetYTitle("Entries");
	h1_hittime -> SetLineColor(kAzure-4);
	h1_hittime -> SetLineWidth(2);
	h1_hittime -> SetFillStyle(3003);
	h1_hittime -> SetFillColor(kAzure-4);
	h1_hittime.SetTitleOffset(1.3, "Y");
    h1_hittime.SetTitleSize(0.035, "Y");
    h1_hittime.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_hittime->GetXaxis())->SetMaxDigits(4);

    gROOT -> SetStyle("Plain");

    TCanvas* c = new TCanvas("c", "c", 800, 800);
	
    //TText* text = new TText(15, 60, "1 microsec timing cut");
    //text -> SetTextSize(0.035);
    tree -> Draw("tiskz>>h1_hittime");
    //text -> Draw();
    //c.SaveAs("./Figure/PMThittiming.w.o.timingcut.pdf");
    //c.SaveAs("./Figure/PMThittiming.w.timingcut1microsec.pdf");
    //c.SaveAs("./Figure/PMThittiming.w.timingcut5microsec.pdf");
    c.SaveAs("./Figure/PMThittiming.w.timingcut18microsec.pdf");



	/*int ndata = tree->GetEntries();
	std::cout << "Recorded Event#: " << ndata << std::endl;

    int hitnum[100];
	int nqiskz;
	tree -> SetBranchAddress("nqiskz", &nqiskz);

	for (int ev=0; ev<ndata; ev++) {
		tree -> GetEntry(ev);
		hitnum[ev] = nqiskz;
		//std::cout << "hitnum[" << ev+1 << "]: " << hitnum[ev] << std::endl;

		//const int hits = hitnum[ev];
	}

    float tiskz[3198];
    tree -> SetBranchAddress("tiskz", tiskz);
    for (int hit=0; hit<3198; hit++) {
    	tree -> GetEntry(hit);
        std::cout << "tiskz[" << hit << "]: " << tiskz[hit] << std::endl;
    }*/

	/*for (int ev=0; ev<ndata; ev++) {
		tree -> GetEntry(ev);
		hitnum[ev] = nqiskz;
		//std::cout << "hitnum[" << ev+1 << "]: " << hitnum[ev] << std::endl;

		const int hits = hitnum[ev];
		std::cout << "Event[" << ev+1 << "]  hits: " << hits << std::endl;
		float tiskz[];
		
		for (int hit=0; hit<hits; hit++) {
			tree -> GetEntry(hit);
			std::cout << " | tiskz[" << hit+1 << "]: " << tiskz[hit] << std::endl;
		}
		std::cout << " " << std::endl;

	}*/

    //const int hits = hitnum[0];

	//float hittime[100][hits];
	/*float tiskz[];
	tree -> SetBranchAddress("tiskz", tiskz);
	std::cout << "For hitnum[0]: " << hitnum[0] << std::endl;
	for (int hit=0; hit<hitnum[0]; hit++) {
		tree -> GetEntry(hit);
		std::cout << "tiskz[" << hit+1 << "]: " << tiskz[hit] << std::endl;
		//hittime[0][hit] = tiskz[hit];
	}*/

    /*const int hitnum = 0;
	tree -> SetBranchAddress("nqiskz", &hitnum);

	for(int ev=0; ev<ndata; ev++) {
		tree -> GetEntry(ev);
		std::cout << "Event[" << ev+1 << "], nqiskz: " << hitnum << std::endl;

		float hittime[hitnum];
		tree -> SetBranchAddress("tiskz", hittime);

		for (int i=0; i<hitnum; i++) {
			//tree -> GetEntry(i);
			std::cout << "  tiskz[" << i+1 << "]: " << hittime[i] << " nsec" << std::endl;
		}
		std::cout << " " << std::endl;
	}*/



}