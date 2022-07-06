#include <iostream>
#include <iomanip>
#include <ios>
#include <unistd.h>
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "THStack.h"
#include "CC0PiNumu.h"  //src: /disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu
#include "DefBeamMode.h"
#include "DefOscChannels.h"

#include "include/NeutrinoEvents.h"
#include "include/NTagVariables.h"
#include "include/CLTOption.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"


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

  //=========  TTree h1 variables  ============
  UInt_t nrun = 0;
  Int_t nev  = 0;
  Int_t nsub = 0;
  Int_t Npvc;          //Number of primary particles
  Int_t Ipvc[100];     //PID 
  Int_t Iflvc[100];
  float posv[3];            //truth prompt vertex
  float fq1rpos[100][7][3]; //reconstructed prompt vertex
  tchfQ -> SetBranchAddress("nrun", &nrun);
  tchfQ -> SetBranchAddress("nev", &nev);
  tchfQ -> SetBranchAddress("nsub", &nsub);
  tchfQ -> SetBranchAddress("Npvc", &Npvc);
  tchfQ -> SetBranchAddress("Ipvc", Ipvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("posv", posv);
  tchfQ -> SetBranchAddress("fq1rpos", fq1rpos);
  //=========  TTree event variables  ============
  float RunNo    = 0.;
  float EventNo  = 0.;
  float SubrunNo = 0.;
  float NTrueN   = 0.;
  float vecvx    = 0.;
  float vecvy    = 0.;
  float vecvz    = 0.;
  tchev -> SetBranchAddress("RunNo", &RunNo);
  tchev -> SetBranchAddress("EventNo", &EventNo);
  tchev -> SetBranchAddress("SubrunNo", &SubrunNo);
  tchev -> SetBranchAddress("NTrueN", &NTrueN);
  tchev -> SetBranchAddress("vecvx", &vecvx);
  tchev -> SetBranchAddress("vecvy", &vecvy);
  tchev -> SetBranchAddress("vecvz", &vecvz);
  //=========  TTree taggable variables  ============
  //=========  TTree ntag variables  ============
  

  //Process
  if (MCTypeKeyword=="-MCType") {
    if (MCType=="Gd" || MCType=="gd") processmax = ntagEntries;
    else if (MCType=="Water" || MCType=="water") processmax = nfQEntries;
    else {
      std::cout << " " << std::endl;
      std::cout << "[!!!CLT error!!!] MC type can not be found. --- input Gd or Water" << std::endl;
      exit(-1); 
    }
  }
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);


  for (int ientry=0; ientry<processmax; ientry++) {

  	//Progress meter
    if(ientry>100 && ientry%100==0) std::cout << "[### analysis1Rmu ###]  Progress: " << 100.*ientry/processmax << "%" << std::endl;

    tchfQ -> GetEntry(ientry);
    tchev -> GetEntry(ientry);

    if (nev!=EventNo) {
      std::cout << std::setfill('0') << std::right << std::setw(4) << "[Process " << ientry << "] ";
      std::cout << std::setfill(' ');
      std::cout << "fiTQun event: " << std::right << std::setw(4) << "GetEntry(ientry " << ientry << ")=" << nev << ", vertex: [" << posv[0] << ", " << posv[1] << ", " << posv[2] << "]" << std::endl;
      std::cout << "             NTag event  : " << std::right << std::setw(4) << "GetEntry(NTagEv " << ientry << ")=" << EventNo << ", vertex: [" << vecvx << ", " << vecvy << ", " << vecvz << "]" << std::endl;
    }
    //std::cout << std::setfill('0') << std::right << std::setw(4) << "[Process " << ientry << "] ";
    //std::cout << std::setfill(' ');
    //std::cout << "fiTQun event: " << std::right << std::setw(4) << "GetEntry(ientry " << ientry << ")=" << nev << ", vertex: [" << posv[0] << ", " << posv[1] << ", " << posv[2] << "]" << std::endl;
    //std::cout << "             NTag event  : " << std::right << std::setw(4) << "GetEntry(NTagEv " << ientry << ")=" << EventNo << ", vertex: [" << vecvx << ", " << vecvy << ", " << vecvz << "]" << std::endl;
  }

}