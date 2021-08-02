/////////////////////////////////////////////////
//                                             //
// Extract input variables for NN which are    //
// output from ntag_mc.                        //
// Line up of input variables can be checked   //
// from createNtagTree() in ntag_mc.cc.        //
//                                             //
// Author: Seidai (2021/6/30)                  //
//                                             //
/////////////////////////////////////////////////


#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#include "NNinputExtraction.h"


void TTreeCall(TString filename) {
	f = new TFile(filename);
	tree = static_cast<TTree*>f->Get("ntag");

	if (filename.Index("sig")==-1) id = false;
	if (id) std::cout << "File: " << filename << ", Type: Signal" << std::endl;
	else std::cout << "File: " << filename << ", Type: BKG" << std::endl;

	tree -> SetBranchAddress("nrun", &runnumber);
	tree -> SetBranchAddress("nsub", &subnumber);
	tree -> SetBranchAddress("nev", &eventnumber);
	tree -> SetBranchAddress("dt0vtx", &dt0vtx);
	tree -> SetBranchAddress("dt0", &dt0);
 
   tree -> SetBranchAddress("N10nvx", &N10nvx);
	tree -> SetBranchAddress("N300S", &N300S);
	tree -> SetBranchAddress("NcS", &NcS);
   tree -> SetBranchAddress("beta1", &beta1);
	tree -> SetBranchAddress("beta2", &beta2);
	tree -> SetBranchAddress("beta3", &beta3);
	tree -> SetBranchAddress("beta4", &beta4);
	tree -> SetBranchAddress("beta5", &beta5);
	tree -> SetBranchAddress("ndwall", &ndwall);
	tree -> SetBranchAddress("ntowall", &ntowall);
	tree -> SetBranchAddress("d0", &d0);
	tree -> SetBranchAddress("d1", &d1);
	tree -> SetBranchAddress("d2", &d2);
	tree -> SetBranchAddress("d3", &d3);
	tree -> SetBranchAddress("d4", &d4);
	tree -> SetBranchAddress("d5", &d5);
	tree -> SetBranchAddress("d6", &d6);
	tree -> SetBranchAddress("dmean", &dmean);
	tree -> SetBranchAddress("drms", &drms);
	tree -> SetBranchAddress("ddiff", &ddiff);

	tree -> SetBranchAddress("neutrondegree", &neutrondegree);
	tree -> SetBranchAddress("ntagvtx", ntagvtx);
	tree -> SetBranchAddress("bonsvtx", bonsvtx);
	tree -> SetBranchAddress("dist_bonsntagvtx", &dist_bonsntagvtx);
	tree -> SetBranchAddress("dist_truentagvtx", &dist_truentagvtx);
	tree -> SetBranchAddress("erec", &erec);
	tree -> SetBranchAddress("wall", &wall);
	tree -> SetBranchAddress("effwall", &effwall);
	tree -> SetBranchAddress("ovaq", &ovaq);
	tree -> SetBranchAddress("angle", &angle);
	tree -> SetBranchAddress("timetrupos", &timetrupos);
	tree -> SetBranchAddress("timefalpos", &timefalpos);
	tree -> SetBranchAddress("capture_time", &capture_time);
	tree -> SetBranchAddress("neutron_mom", &neutron_mom);
}//TTreeCall()

void NNvar_Beta_Plot() {
	if(id) {
		h1_beta1[0] = new TH1D("h1_beta1_sig", "beta1; #beta_{1}; Event number", 50, -0.2, 1.2);
		h1_beta2[0] = new TH1D("h1_beta2_sig", "beta2; #beta_{2}; Event number", 50, -0.2, 1.2);
		h1_beta3[0] = new TH1D("h1_beta3_sig", "beta3; #beta_{3}; Event number", 50, -0.2, 1.2);
		h1_beta4[0] = new TH1D("h1_beta4_sig", "beta4; #beta_{4}; Event number", 50, -0.2, 1.2);
		h1_beta5[0] = new TH1D("h1_beta5_sig", "beta5; #beta_{5}; Event number", 50, -0.2, 1.2);
		color = kAzure-4;

		h1_beta1[0] -> SetLineWidth(2);
      h1_beta2[0] -> SetLineWidth(2);
      h1_beta3[0] -> SetLineWidth(2);
      h1_beta4[0] -> SetLineWidth(2);
      h1_beta5[0] -> SetLineWidth(2);

      h1_beta1[0] -> SetLineColor(color);
      h1_beta2[0] -> SetLineColor(color);
      h1_beta3[0] -> SetLineColor(color);
      h1_beta4[0] -> SetLineColor(color);
      h1_beta5[0] -> SetLineColor(color);

      h1_beta1[0] -> SetFillStyle(3003);
      h1_beta2[0] -> SetFillStyle(3003);
      h1_beta3[0] -> SetFillStyle(3003);
      h1_beta4[0] -> SetFillStyle(3003);
      h1_beta5[0] -> SetFillStyle(3003);

      h1_beta1[0] -> SetFillColor(color);
      h1_beta2[0] -> SetFillColor(color);
      h1_beta3[0] -> SetFillColor(color);
      h1_beta4[0] -> SetFillColor(color);
      h1_beta5[0] -> SetFillColor(color);
	}
	else {
		h1_beta1[1] = new TH1D("h1_beta1_bkg", "beta1; #beta_{1}; Event number", 50, -0.2, 1.2);
		h1_beta2[1] = new TH1D("h1_beta2_bkg", "beta2; #beta_{2}; Event number", 50, -0.2, 1.2);
		h1_beta3[1] = new TH1D("h1_beta3_bkg", "beta3; #beta_{3}; Event number", 50, -0.2, 1.2);
		h1_beta4[1] = new TH1D("h1_beta4_bkg", "beta4; #beta_{4}; Event number", 50, -0.2, 1.2);
		h1_beta5[1] = new TH1D("h1_beta5_bkg", "beta5; #beta_{5}; Event number", 50, -0.2, 1.2);
		color = kPink+2;

		h1_beta1[1] -> SetLineWidth(2);
      h1_beta2[1] -> SetLineWidth(2);
      h1_beta3[1] -> SetLineWidth(2);
      h1_beta4[1] -> SetLineWidth(2);
      h1_beta5[1] -> SetLineWidth(2);

      h1_beta1[1] -> SetLineColor(color);
      h1_beta2[1] -> SetLineColor(color);
      h1_beta3[1] -> SetLineColor(color);
      h1_beta4[1] -> SetLineColor(color);
      h1_beta5[1] -> SetLineColor(color);

      h1_beta1[1] -> SetFillStyle(3003);
      h1_beta2[1] -> SetFillStyle(3003);
      h1_beta3[1] -> SetFillStyle(3003);
      h1_beta4[1] -> SetFillStyle(3003);
      h1_beta5[1] -> SetFillStyle(3003);

      h1_beta1[1] -> SetFillColor(color);
      h1_beta2[1] -> SetFillColor(color);
      h1_beta3[1] -> SetFillColor(color);
      h1_beta4[1] -> SetFillColor(color);
      h1_beta5[1] -> SetFillColor(color);
	}

   int nevents = tree->GetEntries();
	for (int ev=0; ev<nevents; ev++) {
		tree -> GetEntry(ev);

      if(id) {
      	h1_beta1[0] -> Fill(beta1);
		   h1_beta2[0] -> Fill(beta2);
		   h1_beta3[0] -> Fill(beta3);
		   h1_beta4[0] -> Fill(beta4);
		   h1_beta5[0] -> Fill(beta5);
      }// signal if
      else {
      	h1_beta1[1] -> Fill(beta1);
		   h1_beta2[1] -> Fill(beta2);
		   h1_beta3[1] -> Fill(beta3);
		   h1_beta4[1] -> Fill(beta4);
		   h1_beta5[1] -> Fill(beta5);
      }// BKG if
	}//event loop
}//NNvar_Beta_Plot()

void NNvar_dwall_Plot() {
	if(id) {
		h1_ndwall[0] = new TH1D("h1_ndwall_sig", "dwall; D_{wall}; Event number", 50, 0, 1600);
		color = kAzure-4;

		h1_ndwall[0] -> SetLineWidth(2);
		h1_ndwall[0] -> SetLineColor(color);
		h1_ndwall[0] -> SetFillStyle(3003);
		h1_ndwall[0] -> SetFillColor(color);
		h1_ndwall[0].SetTitleOffset(1.3, "Y");
	   h1_ndwall[0].SetTitleSize(0.035, "Y");
	   h1_ndwall[0].SetLabelSize(0.035, "Y");
	}
	else {
		h1_ndwall[1] = new TH1D("h1_ndwall_bkg", "dwall; D_{wall}; Event number", 50, 0, 1600);
		color = kPink+2;

		h1_ndwall[1] -> SetLineWidth(2);
		h1_ndwall[1] -> SetLineColor(color);
		h1_ndwall[1] -> SetFillStyle(3003);
		h1_ndwall[1] -> SetFillColor(color);
		h1_ndwall[1].SetTitleOffset(1.3, "Y");
	   h1_ndwall[1].SetTitleSize(0.035, "Y");
	   h1_ndwall[1].SetLabelSize(0.035, "Y");
	}

	int nevents = tree->GetEntries();
	for (int ev=0; ev<nevents; ev++) {
		tree -> GetEntry(ev);

		if(id) h1_ndwall[0] -> Fill(ndwall);
		else h1_ndwall[1] -> Fill(ndwall);
	}
}//NNvar_dwall_Plot()

void NNvar_towall_Plot() {
	if(id) {
		h1_ntowall[0] = new TH1D("h1_ntowall_sig", "towall; To_{wall}; Event number", 50, -200, 4800);
		color = kAzure-4;

		h1_ntowall[0] -> SetLineWidth(2);
		h1_ntowall[0] -> SetLineColor(color);
		h1_ntowall[0] -> SetFillStyle(3003);
		h1_ntowall[0] -> SetFillColor(color);
		h1_ntowall[0].SetTitleOffset(1.3, "Y");
	   h1_ntowall[0].SetTitleSize(0.035, "Y");
	   h1_ntowall[0].SetLabelSize(0.035, "Y");
	}
	else {
		h1_ntowall[1] = new TH1D("h1_ntowall_bkg", "towall; To_{wall}; Event number", 50, -200, 4800);
		color = kPink+2;

		h1_ntowall[1] -> SetLineWidth(2);
		h1_ntowall[1] -> SetLineColor(color);
		h1_ntowall[1] -> SetFillStyle(3003);
		h1_ntowall[1] -> SetFillColor(color);
		h1_ntowall[1].SetTitleOffset(1.3, "Y");
	   h1_ntowall[1].SetTitleSize(0.035, "Y");
	   h1_ntowall[1].SetLabelSize(0.035, "Y");
	}

	int nevents = tree->GetEntries();
	for (int ev=0; ev<nevents; ev++) {
		tree -> GetEntry(ev);

		if(id) h1_ntowall[0] -> Fill(ntowall);
		else h1_ntowall[1] -> Fill(ntowall);
	}
}//NNvar_towall_Plot()


//main
void NNinputExtraction() {
   //TString sigfilename = "/disk02/usr6/sedi/Ntag/output/nsig_test_ntag0618_Pruthvi.root";
   //TString bkgfilename = "/disk02/usr6/sedi/Ntag/output/nbkg_test_ntag0618_Pruthvi.root";

   TString sigfilename = "/disk02/usr6/sedi/Ntag/output/nsig_fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root";
   TString bkgfilename = "/disk02/usr6/sedi/Ntag/output/nbkg_fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root";

   //signal
	TTreeCall(sigfilename);
	NNvar_Beta_Plot();
	NNvar_dwall_Plot();
	NNvar_towall_Plot();

   //bkg
   TTreeCall(bkgfilename);
   NNvar_Beta_Plot();
   NNvar_dwall_Plot();
   NNvar_towall_Plot();
	
   gROOT -> SetStyle("Plain");

   TCanvas* cbeta = new TCanvas("cbeta", "beta", 800, 800);
   cbeta->Divide(2,3);
   for (int i=0; i<6; i++) {
   	cbeta -> cd(i+1);
   	switch(i) {
   		case 0:
   		  h1_beta1[1] -> Draw();
   		  h1_beta1[0] -> Draw("SAME");
   		  break;
   		case 1:
   		  h1_beta2[1] -> Draw();
   		  h1_beta2[0] -> Draw("SAME");
   		  break;
   		case 2:
   		  h1_beta3[1] -> Draw();
   		  h1_beta3[0] -> Draw("SAME");
   		  break;
   		case 3:
   		  h1_beta4[1] -> Draw();
   		  h1_beta4[0] -> Draw("SAME");
   		  break;
   		case 4:
   		  h1_beta5[1] -> Draw();
   		  h1_beta5[0] -> Draw("SAME");
   		  break;
   		default:
   		  //TText* text = new TText(0,0.3,"File: "+sigfilename);
   		  TText* text = new TText(0,0.3,"File: nsig_fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root");
           text -> SetTextSize(0.05);
           text -> Draw();
           //TText* text = new TText(0,0.2,"File: "+bkgfilename);
           TText* text = new TText(0,0.2,"File: nbkg_fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root");
           text -> SetTextSize(0.05);
           text -> Draw();
           TText* text0 = new TText(0,0.4,"N-tag output (before NN)");
           text0 -> SetTextSize(0.05);
           text0 -> Draw();
           TLegend* legend = new TLegend(0, 0.5, 0.6, 0.9);
           legend -> SetTextSize(0.1);
           legend -> AddEntry(h1_beta1[0], "Signal", "F");
           legend -> AddEntry(h1_beta1[1], "BKG", "F");
           legend -> SetLineColor(0);
           legend -> SetFillColor(0);
           legend -> SetFillStyle(0);
           legend -> SetLineStyle(0);
           legend -> SetShadowColor(0);
           legend -> Draw();
   	}
   }
   cbeta.SaveAs("./Figure/beta.pdf");

   TCanvas* cdwall = new TCanvas("cdwall", "nDwall", 800, 800);
   h1_ndwall[1] -> Draw();
   h1_ndwall[0] -> Draw("SAME");
   TLegend* legend = new TLegend(0.4, 0.6, 0.8, 0.8);
   legend -> SetTextSize(0.035);
   legend -> AddEntry(h1_beta1[0], "Signal", "F");
   legend -> AddEntry(h1_beta1[1], "BKG", "F");
   legend -> SetLineColor(0);
   legend -> SetFillColor(0);
   legend -> SetFillStyle(0);
   legend -> SetLineStyle(0);
   legend -> SetShadowColor(0);
   legend -> Draw();
   cdwall.SaveAs("./Figure/dwall.pdf");

   TCanvas* ctowall = new TCanvas("ctowall", "ntowall", 800, 800);
   h1_ntowall[1] -> Draw();
   h1_ntowall[0] -> Draw("SAME");
   TLegend* legend = new TLegend(0.15, 0.7, 0.4, 0.85);
   legend -> SetTextSize(0.035);
   legend -> AddEntry(h1_beta1[0], "Signal", "F");
   legend -> AddEntry(h1_beta1[1], "BKG", "F");
   legend -> SetLineColor(0);
   legend -> SetFillColor(0);
   legend -> SetFillStyle(0);
   legend -> SetLineStyle(0);
   legend -> SetShadowColor(0);
   legend -> Draw();
   ctowall.SaveAs("./Figure/towall.pdf");

}//NNinputExtraction()


/*void NNinputExtraction() {
	TString file = "/disk02/usr6/sedi/Ntag/output/nsig_test_ntag0618_Pruthvi.root";
	TString nickname = "nsig_test_ntag0618_Pruthvi.root";
	std::cout << "File: " << file << std::endl;

	TFile* f = new TFile(file);
	TTree* tree = static_cast<TTree*>f->Get("ntag");

	tree -> SetBranchAddress("nrun", &runnumber);
	tree -> SetBranchAddress("nsub", &subnumber);
	tree -> SetBranchAddress("nev", &eventnumber);
	tree -> SetBranchAddress("dt0vtx", &dt0vtx);
	tree -> SetBranchAddress("dt0", &dt0);

	tree -> SetBranchAddress("N10nvx", &N10nvx);
	tree -> SetBranchAddress("N300S", &N300S);
	tree -> SetBranchAddress("NcS", &NcS);
	tree -> SetBranchAddress("beta1", &beta1);
	tree -> SetBranchAddress("beta2", &beta2);
	tree -> SetBranchAddress("beta3", &beta3);
	tree -> SetBranchAddress("beta4", &beta4);
	tree -> SetBranchAddress("beta5", &beta5);
	tree -> SetBranchAddress("ndwall", &ndwall);
	tree -> SetBranchAddress("ntowall", &ntowall);
	tree -> SetBranchAddress("d0", &d0);
	tree -> SetBranchAddress("d1", &d1);
	tree -> SetBranchAddress("d2", &d2);
	tree -> SetBranchAddress("d3", &d3);
	tree -> SetBranchAddress("d4", &d4);
	tree -> SetBranchAddress("d5", &d5);
	tree -> SetBranchAddress("d6", &d6);
	tree -> SetBranchAddress("dmean", &dmean);
	tree -> SetBranchAddress("drms", &drms);
	tree -> SetBranchAddress("ddiff", &ddiff);

	tree -> SetBranchAddress("neutrondegree", &neutrondegree);
	tree -> SetBranchAddress("ntagvtx", ntagvtx);
	tree -> SetBranchAddress("bonsvtx", bonsvtx);
	tree -> SetBranchAddress("dist_bonsntagvtx", &dist_bonsntagvtx);
	tree -> SetBranchAddress("dist_truentagvtx", &dist_truentagvtx);
	tree -> SetBranchAddress("erec", &erec);
	tree -> SetBranchAddress("wall", &wall);
	tree -> SetBranchAddress("effwall", &effwall);
	tree -> SetBranchAddress("ovaq", &ovaq);
	tree -> SetBranchAddress("angle", &angle);
	tree -> SetBranchAddress("timetrupos", &timetrupos);
	tree -> SetBranchAddress("timefalpos", &timefalpos);
	tree -> SetBranchAddress("capture_time", &capture_time);
	tree -> SetBranchAddress("neutron_mom", &neutron_mom);

	//TH1D* h1_sig_nrun = new TH1D("h1_sig_nrun", "run number", 5, 999997, 1000001);
	TH1D* h1_nev = new TH1D("h1_nev", "event number", 100, 0, 1800);
	TH1D* h1_beta1 = new TH1D("h1_beta1", "beta1; #beta_{1}; Event number", 50, -0.2, 1.2);
	//h1_beta1 -> SetTitleSize(0.02, "X");
	h1_beta1 -> SetLineColor(kAzure-4);
	h1_beta1 -> SetLineWidth(2);
	h1_beta1 -> SetFillStyle(3003);
	h1_beta1 -> SetFillColor(kAzure-4);
	TH1D* h1_beta2 = new TH1D("h1_beta2", "beta2; #beta_{2}; Event number", 50, -0.2, 1.2);
	h1_beta2 -> SetLineColor(kAzure-4);
	h1_beta2 -> SetLineWidth(2);
	h1_beta2 -> SetFillStyle(3003);
	h1_beta2 -> SetFillColor(kAzure-4);
	TH1D* h1_beta3 = new TH1D("h1_beta3", "beta3; #beta_{3}; Event number", 50, -0.2, 1.2);
	h1_beta3 -> SetLineColor(kAzure-4);
	h1_beta3 -> SetLineWidth(2);
	h1_beta3 -> SetFillStyle(3003);
	h1_beta3 -> SetFillColor(kAzure-4);
	TH1D* h1_beta4 = new TH1D("h1_beta4", "beta4; #beta_{4}; Event number", 50, -0.2, 1.2);
	h1_beta4 -> SetLineColor(kAzure-4);
	h1_beta4 -> SetLineWidth(2);
	h1_beta4 -> SetFillStyle(3003);
	h1_beta4 -> SetFillColor(kAzure-4);
	TH1D* h1_beta5 = new TH1D("h1_beta5", "beta5; #beta_{5}; Event number", 50, -0.2, 1.2);
	h1_beta5 -> SetLineColor(kAzure-4);
	h1_beta5 -> SetLineWidth(2);
	h1_beta5 -> SetFillStyle(3003);
	h1_beta5 -> SetFillColor(kAzure-4);

	TH1D* h1_neutrondegree = new TH1D("h1_neutrondegree", "neutron degree; neutron degree; Event number", 5, -2, 3);
	//gStyle->SetTitleYOffset(3);
	h1_neutrondegree.SetTitleOffset(1.3, "Y");
	h1_neutrondegree.SetTitleSize(0.035, "Y");
	h1_neutrondegree.SetLabelSize(0.035, "Y");
	h1_neutrondegree -> SetLineColor(kAzure-4);
	h1_neutrondegree -> SetLineWidth(2);
	h1_neutrondegree -> SetFillStyle(3003);
	h1_neutrondegree -> SetFillColor(kAzure-4);

	TH1D* h1_ntagvtx[3];
	TH1D* h1_bonsvtx[3];
    for (int i=0; i<3; i++) {
       h1_ntagvtx[i] = new TH1D(TString::Format("h1_ntagvtx_%i", i), TString::Format("h1_ntagvtx_%i", i), 80, -2000, 2000);
       h1_ntagvtx[i] -> SetYTitle("Event number");
       if (i==0) h1_ntagvtx[i] -> SetXTitle("ntag vertex(X) [mm]");
       if (i==1) h1_ntagvtx[i] -> SetXTitle("ntag vertex(Y) [mm]");
       if (i==2) h1_ntagvtx[i] -> SetXTitle("ntag vertex(Z) [mm]");
       h1_ntagvtx[i] -> SetLineColor(kAzure-4);
       h1_ntagvtx[i] -> SetLineWidth(2);
       h1_ntagvtx[i] -> SetFillStyle(3003);
       h1_ntagvtx[i] -> SetFillColor(kAzure-4);

       //should be replaced into fiTQun later
       h1_bonsvtx[i] = new TH1D(TString::Format("h1_bonsvtx_%i", i), TString::Format("h1_bonsvtx_%i", i), 80, -2000, 2000);
       h1_bonsvtx[i] -> SetYTitle("Event number");
       if (i==0) h1_bonsvtx[i] -> SetXTitle("BONSAI vertex(X) [mm]");
       if (i==1) h1_bonsvtx[i] -> SetXTitle("BONSAI vertex(Y) [mm]");
       if (i==2) h1_bonsvtx[i] -> SetXTitle("BONSAI vertex(Z) [mm]");
       h1_bonsvtx[i] -> SetLineColor(kAzure-4);
       h1_bonsvtx[i] -> SetLineWidth(2);
       h1_bonsvtx[i] -> SetFillStyle(3003);
       h1_bonsvtx[i] -> SetFillColor(kAzure-4);
    }

	int nevents = tree->GetEntries();
	for (int ev=0; ev<nevents; ev++) {
		tree -> GetEntry(ev);

		//h1_sig_nrun -> Fill(sig_runnumber);
		h1_nev -> Fill(eventnumber);
		h1_beta1 -> Fill(beta1);
		h1_beta2 -> Fill(beta2);
		h1_beta3 -> Fill(beta3);
		h1_beta4 -> Fill(beta4);
		h1_beta5 -> Fill(beta5);

		h1_neutrondegree -> Fill(neutrondegree);

		for (int i=0; i<3; i++) {
        	h1_ntagvtx[i] -> Fill(ntagvtx[i]);
        	h1_bonsvtx[i] -> Fill(bonsvtx[i]);
        }

		//std::cout << "Event:[" << ev+1 << "] nev: " << eventnumber << std::endl;

		//std::cout << "Event[" << ev+1 << "] nrun: " << sig_runnumber << ", nsub: " << sig_subnumber << ", nev: " << sig_eventnumber
		//<< ", dt0vtx: " << sig_dt0vtx << ", dt0: " << sig_dt0 << std::endl;
	}


	gROOT -> SetStyle("Plain");

    TCanvas* cbeta = new TCanvas("cbeta", "beta", 800, 800);
    cbeta->Divide(2,3);

    cbeta -> cd(1);
    h1_beta1 -> Draw();

    cbeta -> cd(2);
    h1_beta2 -> Draw();

    cbeta -> cd(3);
    h1_beta3 -> Draw();

    cbeta -> cd(4);
    h1_beta4 -> Draw();

    cbeta -> cd(5);
    h1_beta5 -> Draw();

    cbeta -> cd(6);
    TText* text = new TText(0,0.5,"File: "+file);
    text -> SetTextSize(0.05);
    text -> Draw();
    TText* text0 = new TText(0,0.6,"N-tag output (before NN)");
    text0 -> SetTextSize(0.05);
    text0 -> Draw();
    cbeta.SaveAs("ntag/figure/beta.pdf");  

    TCanvas* cneutrondegree = new TCanvas("cneutrondegree", "neutron degree", 800, 800);
    h1_neutrondegree -> Draw();
    TText* textneutrondegree1 = new TText(0.3,330.0,nickname);
    textneutrondegree1 -> SetTextSize(0.03);
    TText* textneutrondegree2 = new TText(0.4,350.0,"N-tag output (before NN)");
    textneutrondegree2 -> SetTextSize(0.03);
    textneutrondegree1 -> Draw();
    textneutrondegree2 -> Draw();
    cneutrondegree.SaveAs("ntag/figure/neutrondegree.pdf");

    TCanvas* cntagvtx = new TCanvas("cntagvtx", "ntag vertex", 800, 800);
    cntagvtx->Divide(2, 2);

    TText* text1 = new TText(0,0.5,nickname);
    text1 -> SetTextSize(0.05);

    for (int i=0; i<4; i++) {
    	cntagvtx -> cd(i+1);
    	if (i<3) h1_ntagvtx[i] -> Draw();
    	else {
    		text0 -> Draw();
    		text1 -> Draw();
    	}
    }
    cntagvtx.SaveAs("ntag/figure/ntagvtx.pdf");

    TCanvas* cbonsvtx = new TCanvas("cbonsvtx", "BONSAI vertex", 800, 800);
    cbonsvtx->Divide(2, 2);

    for (int i=0; i<4; i++) {
    	cbonsvtx -> cd(i+1);
    	if (i<3) h1_bonsvtx[i] -> Draw();
    	else {
    		text0 -> Draw();
    		text1 -> Draw();
    	}
    }
    cbonsvtx.SaveAs("ntag/figure/bonsvtx.pdf");

}*/
