#include <iostream>
#include <unistd.h>
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "THStack.h"
//#include "CC0PiNumu.h"  //src: /disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu
#include "DefBeamMode.h"
#include "DefOscChannels.h"

#include "include/NeutrinoEvents.h"
#include "include/NTagVariables.h"
#include "include/CLTOption.h"
#include "include/ResultSummary.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"
#include "src/NNInputVariables/inc/NNInputVariables.h"


int main(int argc, char **argv) {

  TString fiTQunFileName = argv[1];
  TString NtagFileName   = argv[2];
  TString OutputRootName = argv[3];
  TString ResultSummary  = argv[4];
  TString NTagSummary    = argv[5];
  TString MCTypeKeyword  = argv[6];
  TString MCType         = argv[7];
  TString ETAGKeyword    = argv[8];
  TString ETAG           = argv[9];
  TString BeamKeyword    = argv[10];
  TString Beam           = argv[11];
  TString OscKeyword     = argv[12];
  TString Osc            = argv[13];

  enum BeamMode::E_BEAM_MODE eMode;
  enum OscChan::E_OSC_CHAN eOsc;
  eMode = CLTOptionBeamMode(BeamKeyword, Beam);
  eOsc  = CLTOptionOscMode(OscKeyword, Osc);
  CLTOptionETAG(ETAGKeyword, ETAG);

  //=========  fiTQun output (TTree: h1)  ============
  TChain *tchfQ = new TChain("h1");
  int nfQFiles = tchfQ->Add( fiTQunFileName );
  if ( nfQFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree h1 from: " << fiTQunFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: event)  ============
  TChain *tchev = new TChain("event");
  int nevFiles = tchev->Add( NtagFileName );
  if ( nevFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree event from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Delayed info (TTree: taggable)  ============
  TChain *tchtaggable = new TChain("taggable");
  int ntaggableFiles = tchtaggable->Add( NtagFileName );
  if ( ntaggableFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree taggable from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  NTag output (TTree: ntag)  ============
  TChain *tchntag = new TChain("ntag");
  int ntagFiles = tchntag->Add( NtagFileName );
  if ( ntagFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree ntag from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //Load succeed
  std::cout << "[### analysis1Rmu ###]  Loaded " << nfQFiles       << " files from: " << fiTQunFileName << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << nevFiles       << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << ntaggableFiles << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << ntagFiles      << " files from: " << NtagFileName   << std::endl;


  const int nfQEntries       = tchfQ->GetEntries();       //total entries of TTree h1
  const int nevEntries       = tchev->GetEntries();       //total entries of TTree event
  const int ntaggableEntries = tchtaggable->GetEntries(); //total entries of TTree taggable
  const int ntagEntries      = tchntag->GetEntries();     //total entries of TTree ntag
  std::cout << "[### analysis1Rmu ###]  fiTQun output     : Processing " << nfQEntries       <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Event info        : Processing " << nevEntries       <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Delayed info      : Processing " << ntaggableEntries <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  NTag output       : Processing " << ntagEntries      <<" entries..." << std::endl;


  //=========  TTree event variables  ============
  float NTrueN = 0.;
  //=========  TTree taggable variables  ============
  std::vector<int> *Type = 0;
  TBranch *bType = 0;
  std::vector<float> *E = 0;
  TBranch *bE = 0;
  std::vector<float> *t = 0;
  TBranch *bt = 0;
  tchtaggable->SetBranchAddress("Type", &Type, &bType);
  tchtaggable->SetBranchAddress("E", &E, &bE);
  tchtaggable->SetBranchAddress("t", &t, &bt);
  //=========  TTree ntag variables  ============
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *TagClass = 0;
  TBranch *bTagClass = 0;
  std::vector<float> *FitT = 0;
  TBranch *bFitT = 0;
  std::vector<float> *TagIndex = 0;
  TBranch *bTagIndex = 0;
  std::vector<float> *NHits = 0;
  TBranch *bNHits = 0;
  std::vector<float> *N200 = 0;
  TBranch *bN200 = 0;
  std::vector<float> *TRMS = 0;
  TBranch *bTRMS = 0;
  std::vector<float> *DWall = 0;
  TBranch *bDWall = 0;
  std::vector<float> *DWallMeanDir = 0;
  TBranch *bDWallMeanDir = 0;
  std::vector<float> *OpeningAngleMean = 0;
  TBranch *bOpeningAngleMean = 0;
  std::vector<float> *OpeningAngleSkew = 0;
  TBranch *bOpeningAngleSkew = 0;
  std::vector<float> *OpeningAngleStdev = 0;
  TBranch *bOpeningAngleStdev = 0;
  std::vector<float> *MeanDirAngleMean = 0;
  TBranch *bMeanDirAngleMean = 0;
  std::vector<float> *MeanDirAngleRMS = 0;
  TBranch *bMeanDirAngleRMS = 0;
  std::vector<float> *Beta1 = 0;
  TBranch *bBeta1 = 0;
  std::vector<float> *Beta5 = 0;
  TBranch *bBeta5 = 0;
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N200", &N200, &bN200);
  tchntag->SetBranchAddress("TRMS", &TRMS, &bTRMS);
  tchntag->SetBranchAddress("DWall", &DWall, &bDWall);
  tchntag->SetBranchAddress("DWallMeanDir", &DWallMeanDir, &bDWallMeanDir);
  tchntag->SetBranchAddress("OpeningAngleMean", &OpeningAngleMean, &bOpeningAngleMean);
  tchntag->SetBranchAddress("OpeningAngleSkew", &OpeningAngleSkew, &bOpeningAngleSkew);
  tchntag->SetBranchAddress("OpeningAngleStdev", &OpeningAngleStdev, &bOpeningAngleStdev);
  tchntag->SetBranchAddress("MeanDirAngleMean", &MeanDirAngleMean, &bMeanDirAngleMean);
  tchntag->SetBranchAddress("MeanDirAngleRMS", &MeanDirAngleRMS, &bMeanDirAngleRMS);
  tchntag->SetBranchAddress("Beta1", &Beta1, &bBeta1);
  tchntag->SetBranchAddress("Beta5", &Beta5, &bBeta5);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu ======
  /*Int_t   Npvc;             //Number of primary particles
  Int_t   Ipvc[100];        //PID of primary particles
  Float_t Pvc[100][3];      //Momentum of primary particles
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Ichvc[100];       //Chase at detector simulation or not(1: chase/0: not chase)
  Int_t   nscndprt;         //Number of secondary particles
  Int_t   iprtscnd[1000];   //PID of the secondary particle
  Int_t   iprntprt[1000];   //PID of the parent of this secondary particle
  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  tchfQ -> SetBranchAddress("Npvc", &Npvc);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Ipvc", Ipvc);
  tchfQ -> SetBranchAddress("Ichvc", Ichvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("nscndprt", &nscndprt);
  tchfQ -> SetBranchAddress("iprtscnd", iprtscnd);
  tchfQ -> SetBranchAddress("iprntprt", iprntprt);
  tchfQ -> SetBranchAddress("pscnd", pscnd);*/

  ResetNeutrinoEvents();

  //Histograms
  DecayeBox decayebox;
  decayebox.SetHistoFrame();

  Gd1RmuonSelection prmsel;
  prmsel.SetHistoFrame();
  prmsel.SetHistoFormat();

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();


  //Process
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);

  for (int ientry=0; ientry<ntagEntries; ientry++) {

  	//Progress meter
    if(ientry>100 && ientry%100==0) std::cout << "[### analysis1Rmu ###]  Progress: " << 100.*ientry/ntagEntries << "%" << std::endl;

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchtaggable -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bType       -> GetEntry(tentry);
    bE          -> GetEntry(tentry);
    bLabel      -> GetEntry(tentry);
    bTagClass   -> GetEntry(tentry);
    bFitT       -> GetEntry(tentry);
    bNHits             -> GetEntry(tentry);
    bN200              -> GetEntry(tentry);
    bTRMS              -> GetEntry(tentry);
    bDWall             -> GetEntry(tentry);
    bDWallMeanDir      -> GetEntry(tentry);
    bOpeningAngleMean  -> GetEntry(tentry);
    bOpeningAngleSkew  -> GetEntry(tentry);
    bOpeningAngleStdev -> GetEntry(tentry);
    bMeanDirAngleMean  -> GetEntry(tentry);
    bMeanDirAngleRMS   -> GetEntry(tentry);
    bBeta1             -> GetEntry(tentry);
    bBeta5             -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {
      GetSelectedModeEvents(numu);

      for (UInt_t jentry=0; jentry<Label->size(); ++jentry) {
      	
      	for (int ivar=0; ivar<NNVARIABLES; ivar++) {
      	  switch (ivar) {
      	  	case 0:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, NHits, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, NHits, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, NHits, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, NHits, h1_NNvar_Gd);
      	  	case 1:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, N200, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, N200, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, N200, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, N200, h1_NNvar_Gd);
      	  	case 2:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, TRMS, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, TRMS, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, TRMS, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, TRMS, h1_NNvar_Gd);
      	  	case 3:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, DWall, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, DWall, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, DWall, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, DWall, h1_NNvar_Gd);
      	  	case 4:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, DWallMeanDir, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, DWallMeanDir, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, DWallMeanDir, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, DWallMeanDir, h1_NNvar_Gd);
      	  	case 5:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, OpeningAngleMean, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, OpeningAngleMean, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, OpeningAngleMean, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, OpeningAngleMean, h1_NNvar_Gd);
      	  	case 6:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, OpeningAngleStdev, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, OpeningAngleStdev, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, OpeningAngleStdev, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, OpeningAngleStdev, h1_NNvar_Gd);
      	  	case 7:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, OpeningAngleSkew, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, OpeningAngleSkew, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, OpeningAngleSkew, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, OpeningAngleSkew, h1_NNvar_Gd);
      	  	case 8:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, MeanDirAngleMean, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, MeanDirAngleMean, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, MeanDirAngleMean, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, MeanDirAngleMean, h1_NNvar_Gd);
      	  	case 9:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, MeanDirAngleRMS, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, MeanDirAngleRMS, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, MeanDirAngleRMS, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, MeanDirAngleRMS, h1_NNvar_Gd);
      	  	case 10:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, Beta1, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, Beta1, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, Beta1, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, Beta1, h1_NNvar_Gd);
      	  	case 11:
      	  	  nninputs.GetAccNoiseNNVariables(jentry, Label, ivar, Beta5, h1_NNvar_AccNoise);
      	  	  nninputs.GetDecayeNNVariables(jentry, Label, ivar, Beta5, h1_NNvar_Decaye);
      	  	  nninputs.GetHNNVariables(jentry, Label, ivar, Beta5, h1_NNvar_H);
      	  	  nninputs.GetGdNNVariables(jentry, Label, ivar, Beta5, h1_NNvar_Gd);
      	  }
      	}
      }
    }
  }


  TFile* fout = new TFile(OutputRootName, "RECREATE");
  std::cout << "Output: " << OutputRootName << std::endl;
  fout -> cd();

  decayebox.cdDecayeBox(fout);
  decayebox.WritePlots();
  gDirectory -> cd("..");

  prmsel.cdGd1RmuonSelection(fout);
  prmsel.WritePlots();
  gDirectory -> cd("..");

  nninputs.cdNNInputVariables(fout);
  nninputs.WritePlots();

}