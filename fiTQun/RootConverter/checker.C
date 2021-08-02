////////////////////////////////////////////////
//                                            //
// Check lacked event number through          //
// conversion of .zbs -> .root.               //
// If true vertex position exist in PMT, such //
// events are removed by example_fillnt.sh.   //
// Converted .root file is used for charged   //
// particle side-analysis.                    //
// On the other hand, .root file from LENtuple//
// is used for neutron-side analysis.         //
// We need to check event-matching between    //
// them because of such event loss.           //
//                                            //
// Author: Seidai (2021.7.2)                  //
//                                            //
////////////////////////////////////////////////


#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include <TLatex.h>

void checker() {
    //Get names of input files from fiTQun
    TString filename;
    TString inputfilename[3000];
    int num = 0;
    for (int count=0; count<100; count++) {
        for (int part=1; part<4; part++) {
            for (int skip=0; skip<10; skip++) {
                num++;
                int nskip = skip * 100;
                if (count<10) filename = TString::Format("/disk02/usr6/sedi/fiTQun/converted_output/fhc.numu.fiTQun.0026Gd.NEUTcount00%i.part00%i.skip%i.root", count, part, nskip);
                if (count>=10 && count<100) filename = TString::Format("/disk02/usr6/sedi/fiTQun/converted_output/fhc.numu.fiTQun.0026Gd.NEUTcount0%i.part00%i.skip%i.root", count, part, nskip);
                inputfilename[num-1] = filename;
                //std::cout << "number[" << num << "]  file name: " << filename << std::endl;
            }
        }
    }

    //Calculation of lacked event number
    TFile* fin[3000];
    TTree* tree[3000];
    TString thisfile;
    int fulllost = 0;
    int lost = 0;
    int loss = 0;
    TH1D* h1_evloss = new TH1D("h1_evloss", "Event loss; lost event number; Entries", 10, 0, 10);
    h1_evloss -> SetLineColor(kAzure-4);
    h1_evloss -> SetLineWidth(2);
    h1_evloss -> SetFillStyle(3003);
    h1_evloss -> SetFillColor(kAzure-4);
    h1_evloss.SetTitleOffset(1.3, "Y");
    h1_evloss.SetTitleSize(0.035, "Y");
    h1_evloss.SetLabelSize(0.035, "Y");
    for (int i=0; i<3000; i++) {
        thisfile = inputfilename[i];
        fin[i] = new TFile(thisfile);
        //std::cout << "[" << i+1 << "]  File name: " << thisfile << std::endl;
        tree[i] = static_cast<TTree*>(fin[i]->Get("h1"));

        int ndata = tree[i]->GetEntries();
        //std::cout << "Number of recorded data in root file: " << ndata << " events" << std::endl;
        //std::cout << "Data loss: " << 100-ndata << " events" << std::endl;
        if (ndata==0) {
            fulllost++;
            //std::cout << "[" << i+1 << "]  File name: " << thisfile << std::endl;
            //std::cout << "Data loss: " << 100-ndata << " events" << std::endl;
        }
        if (100-ndata<10) lost++;
        if (100-ndata>10 && 100-ndata!=100) {
            loss++;
            //std::cout << "[" << i+1 << "]  File name: " << thisfile << std::endl;
            //std::cout << "Data loss: " << 100-ndata << " events" << std::endl;
        }
        h1_evloss -> Fill(100-ndata);
        delete fin[i];
        //std::cout << " " << std::endl;
    }
    
    std::cout << "===== Break down =====" << std::endl;
    std::cout << lost << "(loss<10events) + " << loss << "(10events<loss<100events) + " << fulllost << "(loss=100events) / 3000 files" << std::endl;
    TString breakdown0;
    breakdown0 += lost;
    breakdown0 += " (loss<10events) + ";
    TString breakdown1;
    breakdown1 += loss;
    breakdown1 += " (10events<loss<100events) + ";
    TString breakdown2;
    breakdown2 += fulllost;
    breakdown2 += " (loss=100events) / 3000 files";

    //tree->Scan("Entry$:fqnse:fq1rpos[0][2][0]:fq1rpos[0][2][1]:fq1rpos[0][2][2]");

    gROOT -> SetStyle("Plain");

    TCanvas* c = new TCanvas("c", "c", 800, 800);
    TText* text = new TText(3.7, 710, "fiTQun numu");
    text -> SetTextSize(0.035);
    /*TLatex* latex = new TLatex();
    latex -> SetTextHeight(0.035);
    latex->DrawLatex(3.7,700,"#nu_{#mu}");*/
    TText* text0 = new TText(3.7,660,breakdown0);
    text0 -> SetTextSize(0.035);
    TText* text1 = new TText(3.7,620,breakdown1);
    text1 -> SetTextSize(0.035);
    TText* text2 = new TText(3.7,580,breakdown2);
    text2 -> SetTextSize(0.035);
    h1_evloss -> Draw();
    text -> Draw();
    text0 -> Draw();
    text1 -> Draw();
    text2 -> Draw();
    c.SaveAs("./figure/fhc.numu.0026Gd.lossev.pdf");
}