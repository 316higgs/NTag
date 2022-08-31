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
#include "include/multiplicity.h"

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
  TString MCTypeKeyword  = argv[5];
  TString MCType         = argv[6];
  TString ETAGKeyword    = argv[7];
  TString ETAG           = argv[8];
  TString BeamKeyword    = argv[9];
  TString Beam           = argv[10];
  TString OscKeyword     = argv[11];
  TString Osc            = argv[12];

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
  float vecvx  = 0.;
  float vecvy  = 0.;
  float vecvz  = 0.;
  tchev->SetBranchAddress("NTrueN", &NTrueN);
  tchev->SetBranchAddress("vecvx", &vecvx);
  tchev->SetBranchAddress("vecvy", &vecvy);
  tchev->SetBranchAddress("vecvz", &vecvz);
  //=========  TTree taggable variables  ============
  std::vector<int> *Type = 0;
  TBranch *bType = 0;
  std::vector<float> *E = 0;
  TBranch *bE = 0;
  std::vector<float> *t = 0;
  TBranch *bt = 0;
  std::vector<float> *DWall = 0;
  TBranch *bDWall = 0;
  std::vector<float> *tagvx = 0;
  TBranch *btagvx = 0;
  std::vector<float> *tagvy = 0;
  TBranch *btagvy = 0;
  std::vector<float> *tagvz = 0;
  TBranch *btagvz = 0;
  std::vector<float> *DistFromPV = 0;
  TBranch *bDistFromPV = 0;
  tchtaggable->SetBranchAddress("Type", &Type, &bType);
  tchtaggable->SetBranchAddress("E", &E, &bE);
  tchtaggable->SetBranchAddress("t", &t, &bt);
  tchtaggable->SetBranchAddress("DWall", &DWall, &bDWall);
  tchtaggable->SetBranchAddress("tagvx", &tagvx, &btagvx);
  tchtaggable->SetBranchAddress("tagvy", &tagvy, &btagvy);
  tchtaggable->SetBranchAddress("tagvz", &tagvz, &btagvz);
  tchtaggable->SetBranchAddress("DistFromPV", &DistFromPV, &bDistFromPV);
  //=========  TTree ntag variables  ============
  int NCandidates = 0;
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *TagClass = 0;
  TBranch *bTagClass = 0;
  std::vector<float> *FitT = 0;
  TBranch *bFitT = 0;
  std::vector<float> *NHits = 0;
  TBranch *bNHits = 0;
  std::vector<float> *TagIndex = 0;
  TBranch *bTagIndex = 0;
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);

  ResetNeutrinoEvents();
  InitNTagVariables();
  SetHistoFrame();

  //Histograms
  DecayeBox decayebox;
  decayebox.SetHistoFrame();

  Gd1RmuonSelection prmsel;
  prmsel.SetHistoFrame();
  prmsel.SetHistoFormat();

  NeutrinoOscillation neuosc;
  neuosc.SetHistoFrame();
  neuosc.SetHistoFormat();

  DistanceViewer ndistance;
  ndistance.SetHistoFrame();
  ndistance.SetHistoFormat();

  NTagAnalysis ntagana;
  ntagana.InitNeutrons();
  ntagana.SetHistoFrame();
  ntagana.SetHistoFormat();


  std::vector<float> TruthNeutronsperEvent;
  std::vector<float> TruthNeutronsperCCQEEvent;
  std::vector<float> TruthNeutronsperCCnonQEEvent;

  std::vector<float> TaggedNeutronsperEvent;
  std::vector<float> TaggedNeutronsperCCQEEvent;
  std::vector<float> TaggedNeutronsperCCnonQEEvent;


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

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchtaggable -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bType       -> GetEntry(tentry);
    bE          -> GetEntry(tentry);
    bDWall      -> GetEntry(tentry);
    btagvx      -> GetEntry(tentry);
    btagvy      -> GetEntry(tentry);
    btagvz      -> GetEntry(tentry);
    bDistFromPV -> GetEntry(tentry);
    bLabel      -> GetEntry(tentry);
    bTagClass   -> GetEntry(tentry);
    bFitT       -> GetEntry(tentry);
    bNHits      -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);

    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();

    //New 1R muon selection
    const EvSelVar_t evsel = numu->getEvSelVar();
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {

      int mode = TMath::Abs(numu->var<int>("mode"));

      TruthNeutronsperEvent.push_back(NTrueN);
      if (mode==1) TruthNeutronsperCCQEEvent.push_back(NTrueN);
      if (mode>=2 && mode<=30) TruthNeutronsperCCnonQEEvent.push_back(NTrueN);
      
      //if (NTrueN==0) continue;

      //Check neutrino events with tagged neutrons
      float numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, 0.75, TagIndex, NHits, FitT, Label, etagmode);
      TaggedNeutronsperEvent.push_back(numtaggedneutrons);
      if (mode==1) TaggedNeutronsperCCQEEvent.push_back(numtaggedneutrons);
      if (mode>=2 && mode<=30) TaggedNeutronsperCCnonQEEvent.push_back(numtaggedneutrons);

    } //New 1R muon selection
  }


  for (UInt_t i=0; i<TruthNeutronsperEvent.size(); ++i) {
    h1_TruthNeutrons -> Fill(TruthNeutronsperEvent.at(i));
    Truthmeanmultiplicity += TruthNeutronsperEvent.at(i);
  }
  //Truthmeanmultiplicity = Truthmeanmultiplicity/TruthNeutronsperEvent.size();

  for (UInt_t i=0; i<TruthNeutronsperCCQEEvent.size(); ++i) {
    h1_TruthNeutrons_CCQE -> Fill(TruthNeutronsperCCQEEvent.at(i));
    Truthmeanmultiplicity_CCQE += TruthNeutronsperCCQEEvent.at(i);
  }
  //Truthmeanmultiplicity_CCQE = Truthmeanmultiplicity_CCQE/TruthNeutronsperCCQEEvent.size();

  for (UInt_t i=0; i<TruthNeutronsperCCnonQEEvent.size(); ++i) {
    h1_TruthNeutrons_CCnonQE -> Fill(TruthNeutronsperCCnonQEEvent.at(i));
    Truthmeanmultiplicity_CCnonQE += TruthNeutronsperCCnonQEEvent.at(i);
  }
  //Truthmeanmultiplicity_CCnonQE = Truthmeanmultiplicity_CCnonQE/TruthNeutronsperCCnonQEEvent.size();


  for (UInt_t i=0; i<TaggedNeutronsperEvent.size(); ++i) {
    h1_TaggedNeutrons -> Fill(TaggedNeutronsperEvent.at(i));
    meanmultiplicity += TaggedNeutronsperEvent.at(i);
  }
  //meanmultiplicity = meanmultiplicity/TaggedNeutronsperEvent.size();

  for (UInt_t i=0; i<TaggedNeutronsperCCQEEvent.size(); ++i) {
    h1_TaggedNeutrons_CCQE -> Fill(TaggedNeutronsperCCQEEvent.at(i));
    meanmultiplicity_CCQE += TaggedNeutronsperCCQEEvent.at(i);
  }
  //meanmultiplicity_CCQE = meanmultiplicity_CCQE/TaggedNeutronsperCCQEEvent.size();

  for (UInt_t i=0; i<TaggedNeutronsperCCnonQEEvent.size(); ++i) {
    h1_TaggedNeutrons_CCnonQE -> Fill(TaggedNeutronsperCCnonQEEvent.at(i));
    meanmultiplicity_CCnonQE += TaggedNeutronsperCCnonQEEvent.at(i);
  }
  //meanmultiplicity_CCnonQE = meanmultiplicity_CCnonQE/TaggedNeutronsperCCnonQEEvent.size();


  std::fstream resultfile;
  resultfile.open(ResultSummary, std::ios_base::out);
  if (!resultfile.is_open()) {
    std::cout << "Results can not be written in " << ResultSummary << std::endl;
  }
  else {
    float Truthmultiplicity         = Truthmeanmultiplicity;
    float Truthmultiplicity_CCQE    = Truthmeanmultiplicity_CCQE;
    float Truthmultiplicity_CCnonQE = Truthmeanmultiplicity_CCnonQE;
    Truthmeanmultiplicity = Truthmeanmultiplicity/TruthNeutronsperEvent.size();
    Truthmeanmultiplicity_CCQE = Truthmeanmultiplicity_CCQE/TruthNeutronsperCCQEEvent.size();
    Truthmeanmultiplicity_CCnonQE = Truthmeanmultiplicity_CCnonQE/TruthNeutronsperCCnonQEEvent.size();

    resultfile << "----- Truth Info -----" << std::endl;
    resultfile << "Selected Neutrino Events : " << TruthNeutronsperEvent.size() << std::endl;
    resultfile << "Number of Neutrons       : " << Truthmultiplicity << std::endl;
    resultfile << "Mean Neutron Multiplicity: " << Truthmeanmultiplicity << std::endl;
    resultfile << "===== CCQE =====" << std::endl;
    resultfile << "Selected Neutrino Events : " << TruthNeutronsperCCQEEvent.size() << std::endl;
    resultfile << "Number of Neutrons       : " << Truthmultiplicity_CCQE << std::endl;
    resultfile << "Mean Neutron Multiplicity: " << Truthmeanmultiplicity_CCQE << std::endl;
    resultfile << "===== CC non-QE =====" << std::endl;
    resultfile << "Selected Neutrino Events : " << TruthNeutronsperCCnonQEEvent.size() << std::endl;
    resultfile << "Number of Neutrons       : " << Truthmultiplicity_CCnonQE << std::endl;
    resultfile << "Mean Neutron Multiplicity: " << Truthmeanmultiplicity_CCnonQE << std::endl;
    resultfile << " " << std::endl;

    float multiplicity         = meanmultiplicity;
    float multiplicity_CCQE    = meanmultiplicity_CCQE;
    float multiplicity_CCnonQE = meanmultiplicity_CCnonQE;
    meanmultiplicity = meanmultiplicity/TaggedNeutronsperEvent.size();
    meanmultiplicity_CCQE = meanmultiplicity_CCQE/TaggedNeutronsperCCQEEvent.size();
    meanmultiplicity_CCnonQE = meanmultiplicity_CCnonQE/TaggedNeutronsperCCnonQEEvent.size();

    resultfile << "----- Reco. Info -----" << std::endl;
    resultfile << "Selected Neutrino Events : " << TaggedNeutronsperEvent.size() << std::endl;
    resultfile << "Number of Neutrons       : " << multiplicity << std::endl;
    resultfile << "Mean Neutron Multiplicity: " << meanmultiplicity << std::endl;
    resultfile << "===== CCQE =====" << std::endl;
    resultfile << "Selected Neutrino Events : " << TaggedNeutronsperCCQEEvent.size() << std::endl;
    resultfile << "Number of Neutrons       : " << multiplicity_CCQE << std::endl;
    resultfile << "Mean Neutron Multiplicity: " << meanmultiplicity_CCQE << std::endl;
    resultfile << "===== CC non-QE =====" << std::endl;
    resultfile << "Selected Neutrino Events : " << TaggedNeutronsperCCnonQEEvent.size() << std::endl;
    resultfile << "Number of Neutrons       : " << multiplicity_CCnonQE << std::endl;
    resultfile << "Mean Neutron Multiplicity: " << meanmultiplicity_CCnonQE << std::endl;
  }


  TFile* fout = new TFile(OutputRootName, "RECREATE");
  std::cout << "Output: " << OutputRootName << std::endl;
  fout -> cd();

  Double_t totTruth = h1_TruthNeutrons -> Integral();
  h1_TruthNeutrons -> Scale(1./totTruth);
  h1_TruthNeutrons -> Write();

  Double_t totTruthCCQE = h1_TruthNeutrons_CCQE -> Integral();
  h1_TruthNeutrons_CCQE -> Scale(1./totTruthCCQE);
  h1_TruthNeutrons_CCQE -> Write();

  Double_t totTruthCCnonQE = h1_TruthNeutrons_CCnonQE -> Integral();
  h1_TruthNeutrons_CCnonQE -> Scale(1./totTruthCCnonQE);
  h1_TruthNeutrons_CCnonQE -> Write();


  Double_t totTag = h1_TaggedNeutrons -> Integral();
  h1_TaggedNeutrons -> Scale(1./totTag);
  h1_TaggedNeutrons -> Write();

  Double_t totTagCCQE = h1_TaggedNeutrons_CCQE -> Integral();
  h1_TaggedNeutrons_CCQE -> Scale(1./totTagCCQE);
  h1_TaggedNeutrons_CCQE -> Write();

  Double_t totTagCCnonQE = h1_TaggedNeutrons_CCnonQE -> Integral();
  h1_TaggedNeutrons_CCnonQE -> Scale(1./totTagCCnonQE);
  h1_TaggedNeutrons_CCnonQE -> Write();

}

