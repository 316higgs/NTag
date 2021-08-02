#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>

#include "TFile.h"
#include "TH1F.h"

#include "CherenkovAngle3.h"
#include "NTagCategory.h"
#include "HistCherenkovAngle.h"

using namespace std;

const int NTYP=CAng3::N_N10N_TYP;


int main(int argc, char** argv)
{
	string in_dir	=argv[1];
	string prefix	=argv[2];
	string postfix	=argv[3];
	Int_t  nsubnum	=atoi( argv[4] );
	string outfile	=argv[5];

	cout<<endl;
	cout<<" Input files directory   : " << in_dir <<endl;
	cout<<" Prefix of input files   : " << prefix <<endl;
	cout<<" Postfix of input files  : " << postfix <<endl;
	cout<<" Number of mereged files : " << nsubnum <<endl;
	cout<<" " <<endl;
	cout<<" --------------- Start merging --------------- " <<endl;
	cout<<endl;


////////////////////////////////////////////////////////////////////

	HistCherenkovAngle *hca=new HistCherenkovAngle();

	TH1F *hmcn[NTYP];
	TH1F *hbkg[NTYP];
	TFile *fin=NULL;
	string sf="",
		   smcn="",
		   sbkg="";
	ostringstream oss;
	for(Int_t ifile=0; ifile<nsubnum; ifile++)
	{
		oss.str("");
		oss<< setfill('0') << setw(3) << ifile;
		sf="";
		sf=in_dir + "/" + prefix + oss.str() + postfix;
		cout<<" loading : " << sf <<endl;

		fin=TFile::Open(sf.c_str(), "read");
		fin->cd();	
			for(Int_t jtyp=0; jtyp<NTYP; jtyp++)
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
	
		for(Int_t jtyp=0; jtyp<NTYP; jtyp++)
		{
			delete hmcn[jtyp];		hmcn[jtyp]=NULL;
			delete hbkg[jtyp];		hbkg[jtyp]=NULL;
		}	
	}


////////////////////////////////////////////////////////////////////

	TFile *fout=TFile::Open(outfile.c_str(), "recreate");
	fout->cd();
		for(Int_t i=0; i<NTYP; i++)
		{
			hca->getCAngHist(NTagCat::eMCN, i) ->Write();
		}
		for(Int_t i=0; i<NTYP; i++)
		{
			hca->getCAngHist(NTagCat::eBKG, i) ->Write();
		}
	fout->Close();

	cout<<" --------------- Successfully finised --------------- " <<endl;
return 0;
}
