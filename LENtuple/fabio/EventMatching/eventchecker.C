#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include <TLatex.h>

#define BEFORE 52
#define AFTER 54

void eventchecker() {
	//TString lentuple_output = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.w.timingcut18microsec.root";
	//TString lentuple_output = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root"; //did not removed yet

	TString lentuple_output = "/disk02/usr6/sedi/LENtuple/output/fhc.numu.lentuple.0026Gd.NEUTcount000.part001.skip0.root";
	TString fitqun_output   = "/disk02/usr6/sedi/fiTQun/converted_output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root";
	std::cout << "LENtuple output file: " << lentuple_output << std::endl;
	std::cout << "fiTQun output file: " << fitqun_output << std::endl;
	std::cout << " " << std::endl;

	TFile* lentuple_fin = new TFile(lentuple_output);
	TFile* fitqun_fin   = new TFile(fitqun_output);

	TTree* lentuple_tree = static_cast<TTree*>lentuple_fin->Get("h1");
	TTree* fitqun_tree   = static_cast<TTree*>fitqun_fin->Get("h1");

	//Event matching via nev plots
    /*TH1D* h1_nev_nt = new TH1D("h1_nev_nt", "nev", 100, 0, 100);
	h1_nev_nt -> SetXTitle("LENtuple nev");
	h1_nev_nt -> SetYTitle("Entries");
	h1_nev_nt -> SetLineColor(kAzure-4);
	h1_nev_nt -> SetLineWidth(2);
	h1_nev_nt -> SetFillStyle(3003);
	h1_nev_nt -> SetFillColor(kAzure-4);
	h1_nev_nt.SetTitleOffset(1.3, "Y");
    h1_nev_nt.SetTitleSize(0.035, "Y");
    h1_nev_nt.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_nev_nt->GetXaxis())->SetMaxDigits(4);

	TH1D* h1_nev_ft = new TH1D("h1_nev_ft", "nev", 100, 0, 100);
	h1_nev_ft -> SetXTitle("fiTQun nev");
	h1_nev_ft -> SetYTitle("Entries");
	h1_nev_ft -> SetLineColor(kAzure-4);
	h1_nev_ft -> SetLineWidth(2);
	h1_nev_ft -> SetFillStyle(3003);
	h1_nev_ft -> SetFillColor(kAzure-4);
	h1_nev_ft.SetTitleOffset(1.3, "Y");
    h1_nev_ft.SetTitleSize(0.035, "Y");
    h1_nev_ft.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_nev_ft->GetXaxis())->SetMaxDigits(4);

	gROOT -> SetStyle("Plain");

    TCanvas* cev = new TCanvas("cev", "cev", 800, 800);
    cev->Divide(1,2);
    cev->cd(1);
	lentuple_tree -> Draw("nev>>h1_nev_nt");
	cev->cd(2);
	fitqun_tree -> Draw("nev>>h1_nev_ft");
	cev.SaveAs("./Figure/nev.pdf");*/

	//Event matching via nev plots
    TH1D* h1_nrun_nt = new TH1D("h1_nrun_nt", "nrun", 10, 999997, 1000000);
	h1_nrun_nt -> SetXTitle("LENtuple nrun");
	h1_nrun_nt -> SetYTitle("Entries");
	h1_nrun_nt -> SetLineColor(kAzure-4);
	h1_nrun_nt -> SetLineWidth(2);
	h1_nrun_nt -> SetFillStyle(3003);
	h1_nrun_nt -> SetFillColor(kAzure-4);
	h1_nrun_nt.SetTitleOffset(1.3, "Y");
    h1_nrun_nt.SetTitleSize(0.035, "Y");
    h1_nrun_nt.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_nrun_nt->GetXaxis())->SetMaxDigits(4);

	TH1D* h1_nrun_ft = new TH1D("h1_nrun_ft", "nrun", 10, 999997, 1000000);
	h1_nrun_ft -> SetXTitle("fiTQun nrun");
	h1_nrun_ft -> SetYTitle("Entries");
	h1_nrun_ft -> SetLineColor(kAzure-4);
	h1_nrun_ft -> SetLineWidth(2);
	h1_nrun_ft -> SetFillStyle(3003);
	h1_nrun_ft -> SetFillColor(kAzure-4);
	h1_nrun_ft.SetTitleOffset(1.3, "Y");
    h1_nrun_ft.SetTitleSize(0.035, "Y");
    h1_nrun_ft.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_nrun_ft->GetXaxis())->SetMaxDigits(4);

	gROOT -> SetStyle("Plain");

    TCanvas* crun = new TCanvas("crun", "crun", 800, 800);
    crun->Divide(1,2);
    crun->cd(1);
	lentuple_tree -> Draw("nrun>>h1_nrun_nt");
	crun->cd(2);
	fitqun_tree -> Draw("nrun>>h1_nrun_ft");
	crun.SaveAs("./Figure/nrun.pdf");

	//Event matching via nev plots
    /*TH1D* h1_nsub_nt = new TH1D("h1_nsub_nt", "nsub", 20, 0, 2);
	h1_nsub_nt -> SetXTitle("LENtuple nsub");
	h1_nsub_nt -> SetYTitle("Entries");
	h1_nsub_nt -> SetLineColor(kAzure-4);
	h1_nsub_nt -> SetLineWidth(2);
	h1_nsub_nt -> SetFillStyle(3003);
	h1_nsub_nt -> SetFillColor(kAzure-4);
	h1_nsub_nt.SetTitleOffset(1.3, "Y");
    h1_nsub_nt.SetTitleSize(0.035, "Y");
    h1_nsub_nt.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_nsub_nt->GetXaxis())->SetMaxDigits(4);

	TH1D* h1_nsub_ft = new TH1D("h1_nsub_ft", "nsub", 20, 0, 2);
	h1_nsub_ft -> SetXTitle("fiTQun nsub");
	h1_nsub_ft -> SetYTitle("Entries");
	h1_nsub_ft -> SetLineColor(kAzure-4);
	h1_nsub_ft -> SetLineWidth(2);
	h1_nsub_ft -> SetFillStyle(3003);
	h1_nsub_ft -> SetFillColor(kAzure-4);
	h1_nsub_ft.SetTitleOffset(1.3, "Y");
    h1_nsub_ft.SetTitleSize(0.035, "Y");
    h1_nsub_ft.SetLabelSize(0.035, "Y");
	((TGaxis*)h1_nsub_ft->GetXaxis())->SetMaxDigits(4);

	//gROOT -> SetStyle("Plain");

    TCanvas* csub = new TCanvas("csub", "csub", 800, 800);
    csub->Divide(1,2);
    csub->cd(1);
	lentuple_tree -> Draw("nsub>>h1_nsub_nt");
	csub->cd(2);
	fitqun_tree -> Draw("nsub>>h1_nsub_ft");
	csub.SaveAs("./Figure/nsub.pdf");*/



    //Event matching via Total event number
	int nevent_lentuple = lentuple_tree->GetEntries();
	int nevent_fitqun = fitqun_tree->GetEntries();
	std::cout << "LENtuple Event#: " << nevent_lentuple << ", fiTQun Event#: " << nevent_fitqun << std::endl;
	if(abs(nevent_lentuple-nevent_fitqun)==0) std::cout << "--> Total Event# matched!" << std::endl;
	else std::cout << "--> Events did NOT match... Please review output files." << std::endl;


	//fitqun_tree -> Scan("Entry$:fqnse:fq1rpos[0][2][0]:fq1rpos[0][2][1]:fq1rpos[0][2][2]");
	
	
    //Event matching via vertex
	float mcvertex_lentuple[3]   = 0.;
	float mcvertex_fitqun[3]     = 0.;
	float recovertex_lentuple[3] = 0.;
	//float recovertex_fitqun[3]   = 0.;
	float recovertex_fitqun[100][7][3] = 0.;

	lentuple_tree -> SetBranchAddress("posv", mcvertex_lentuple);
	lentuple_tree -> SetBranchAddress("pos", recovertex_lentuple);

	fitqun_tree -> SetBranchAddress("posv", mcvertex_fitqun);
	fitqun_tree -> SetBranchAddress("fq1rpos", recovertex_fitqun);

    //LENtuple vertex
	float mcvertex_lenbefore[3] = 0.;
	float mcvertex_lenafter[3]  = 0.;
	float recovertex_lenbefore[3] = 0.;
	float recovertex_lenafter[3]  = 0.;
	for (int ev=0; ev<nevent_lentuple; ev++) {
		lentuple_tree -> GetEntry(ev);
		//std::cout << "Event[" << ev << "]  MC vertex:[" << mcvertex_lentuple[0] << ", " << mcvertex_lentuple[1] << ", " << mcvertex_lentuple[2] << "]" << std::endl;
		//std::cout << "Event[" << ev << "]  Reco vertex:[" << recovertex_lentuple[0] << ", " << recovertex_lentuple[1] << ", " << recovertex_lentuple[2] << "]" << std::endl;
		if(ev==BEFORE) {
			for(int i=0; i<3; i++) {
				mcvertex_lenbefore[i] = mcvertex_lentuple[i];
				recovertex_lenbefore[i] = recovertex_lentuple[i];
			}
		}
		if(ev==AFTER) {
			for(int i=0; i<3; i++) {
				mcvertex_lenafter[i] = mcvertex_lentuple[i];
				recovertex_lenafter[i] = recovertex_lentuple[i];
			}
		}
	}

    //fiTQun vertex
	float mcvertex_fitbefore[3] = 0.;
	float mcvertex_fitafter[3]  = 0.;
	float recovertex_fitbefore[3] = 0.;
	float recovertex_fitafter[3]  = 0.;
	for (int ev=0; ev<nevent_fitqun; ev++) {
		fitqun_tree -> GetEntry(ev);
		//std::cout << "Event[" << ev << "]  MC vertex:[" << mcvertex_fitqun[0] << ", " << mcvertex_fitqun[1] << ", " << mcvertex_fitqun[2] << "]" << std::endl;
		//std::cout << "Event[" << ev << "]  Reco vertex:[" << recovertex_fitqun[0][2][0] << ", " << recovertex_fitqun[0][2][1] << ", " << recovertex_fitqun[0][2][2] << "]" << std::endl;
		if(ev==BEFORE) {
			for(int i=0; i<3; i++) {
				mcvertex_fitbefore[i] = mcvertex_fitqun[i];
				recovertex_fitbefore[i] = recovertex_fitqun[0][2][i];
			}
		}
		if(ev==AFTER) {
			for(int i=0; i<3; i++) {
				mcvertex_fitafter[i] = mcvertex_fitqun[i];
				recovertex_fitafter[i] = recovertex_fitqun[0][2][i];
			}
		}
	}

    //Event matching
	std::cout << "Before removed event" << std::endl;
	std::cout << "LENtuple MC Vertex: [" << mcvertex_lenbefore[0] << ", " << mcvertex_lenbefore[1] << ", " << mcvertex_lenbefore[2] << "]  Reco Vertex:[" << recovertex_lenbefore[0] << ", " << recovertex_lenbefore[1] << ", " << recovertex_lenbefore[2] << "]" << std::endl;
	std::cout << "fiTQun MC Vertex:   [" << mcvertex_fitbefore[0] << ", " << mcvertex_fitbefore[1] << ", " << mcvertex_fitbefore[2] << "]  Reco Vertex:[" << recovertex_fitbefore[0] << ", " << recovertex_fitbefore[1] << ", " << recovertex_fitbefore[2] << "]" << std::endl;
	std::cout << "After removed event" << std::endl;
	std::cout << "LENtuple MC Vertex: [" << mcvertex_lenafter[0] << ", " << mcvertex_lenafter[1] << ", " << mcvertex_lenafter[2] << "]  Reco Vertex:[" << recovertex_lenafter[0] << ", " << recovertex_lenafter[1] << ", " << recovertex_lenafter[2] << "]" << std::endl;
	std::cout << "fiTQun MC Vertex:   [" << mcvertex_fitafter[0] << ", " << mcvertex_fitafter[1] << ", " << mcvertex_fitafter[2] << "]  Reco Vertex:[" << recovertex_fitafter[0] << ", " << recovertex_fitafter[1] << ", " << recovertex_fitafter[2] << "]" << std::endl;
    if (abs(mcvertex_lenbefore[0]-mcvertex_fitbefore[0])==0 && abs(mcvertex_lenbefore[1]-mcvertex_fitbefore[1])==0 && abs(mcvertex_lenbefore[2]-mcvertex_fitbefore[2])==0) {
    	if (abs(recovertex_lenbefore[0]-recovertex_fitbefore[0])==0 && abs(recovertex_lenbefore[1]-recovertex_fitbefore[1])==0 && abs(recovertex_lenbefore[2]-recovertex_fitbefore[2])==0) {
    		std::cout << "---> Event matching confirmed." << std::endl;
    	}
    }
    else std::cout << "---> Event matching failed. Please review output files." << std::endl;
    
}