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

        float NNVar = 0.;
        for (int ivar=0; ivar<NNVARIABLES; ivar++) {
          switch (ivar) {
            case 0:
              NNVar = NHits->at(jentry);
              break;
            case 1:
              NNVar = N200->at(jentry);
              break;
            case 2:
              NNVar = TRMS->at(jentry);
              break;
            case 3:
              NNVar = DWall->at(jentry);
              break;
            case 4:
              NNVar = DWallMeanDir->at(jentry);
              break;
            case 5:
              NNVar = OpeningAngleMean->at(jentry);
              break;
            case 6:
              NNVar = OpeningAngleStdev->at(jentry);
              break;
            case 7:
              NNVar = OpeningAngleSkew->at(jentry);
              break;
            case 8:
              NNVar = MeanDirAngleMean->at(jentry);
              break;
            case 9:
              NNVar = MeanDirAngleRMS->at(jentry);
              break;
            case 10:
              NNVar = Beta1->at(jentry);
              break;
            case 11:
              NNVar = Beta5->at(jentry);
              break;
            default:
              NNVar = 0.;
              break;  
          }

          if (Label->at(jentry)==0) h1_NNvar_AccNoise[ivar] -> Fill(NNVar);
          if (Label->at(jentry)==1) h1_NNvar_Decaye[ivar]   -> Fill(NNVar);
          if (Label->at(jentry)==2) h1_NNvar_H[ivar]        -> Fill(NNVar);
          if (Label->at(jentry)==3) h1_NNvar_Gd[ivar]       -> Fill(NNVar);
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