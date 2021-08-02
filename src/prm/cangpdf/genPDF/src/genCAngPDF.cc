#include <iostream>
#include <string>
#include <cstdlib>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

#include "CherenkovAngle3.h"
#include "NTagCategory.h"
#include "HistCherenkovAngle.h"

using namespace std;

const int NTYP=CAng3::N_N10N_TYP;


int main(int argc, char** argv)
{
	string s_outfile=argv[1];
	
//////////////////////////////////////////////////////////
	HistCherenkovAngle *hca=new HistCherenkovAngle();

	TH1F *hmcn[NTYP];
	TH1F *hbkg[NTYP];
	TFile *fin=NULL;
	string sf="",
		   smcn="",
		   sbkg="";
	for(int i=2; i<argc; i++)
	{
		sf=argv[i];
		cout<<" loading : " << sf <<endl;

		fin=TFile::Open(sf.c_str(), "read");
		fin->cd();	
			for(int jtyp=0; jtyp<NTYP; jtyp++)
			{
				smcn="";	sbkg="";
				smcn=CAng3::S_CANG_DIST[NTagCat::eMCN][jtyp];
				sbkg=CAng3::S_CANG_DIST[NTagCat::eBKG][jtyp];
				hmcn[jtyp]=(TH1F*)fin->Get( smcn.c_str() )->Clone();
				hbkg[jtyp]=(TH1F*)fin->Get( sbkg.c_str() )->Clone();
				hmcn[jtyp]->SetDirectory( 0 );
				hbkg[jtyp]->SetDirectory( 0 );

				hca->addCAngHist(NTagCat::eMCN, jtyp, hmcn[jtyp]);	
				hca->addCAngHist(NTagCat::eBKG, jtyp, hbkg[jtyp]);	
			}
		fin->Close();
		delete fin;
	
		for(int jtyp=0; jtyp<NTYP; jtyp++)
		{
			delete hmcn[jtyp];		hmcn[jtyp]=NULL;
			delete hbkg[jtyp];		hbkg[jtyp]=NULL;
		}	
	}

//////////////////////////////////////////////////////////

	for(int jtyp=0; jtyp<NTYP; jtyp++)
	{
		hca->generateCAngPDF(NTagCat::eMCN, jtyp);
		hca->generateCAngPDF(NTagCat::eBKG, jtyp);
	}


	// An array of the above 1D PDF
	// Just for visual pourpose (i.e. to check the PDFs by "" eyes "")
	hca->makeCAngPDFArray(NTagCat::eMCN);
	hca->makeCAngPDFArray(NTagCat::eBKG);

//////////////////////////////////////////////////////////
	TFile *fout=TFile::Open(s_outfile.c_str(), "recreate");
	fout->cd();
		for(Int_t i=0; i<NTYP; i++)
		{
			hca->getCAngPDF(NTagCat::eMCN, i) ->Write();
		}
		for(Int_t i=0; i<NTYP; i++)
		{
			hca->getCAngPDF(NTagCat::eBKG, i) ->Write();
		}
		hca->getCAngPDFArray(NTagCat::eMCN)	  ->Write();
		hca->getCAngPDFArray(NTagCat::eBKG)	  ->Write();
	fout->Close();

return 0;
}
