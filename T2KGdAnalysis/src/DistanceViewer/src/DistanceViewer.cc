#include "DistanceViewer.h"
#include "TGaxis.h"

void DistanceViewer::SetHistoFrame() {
  h1_truedistance = new TH1F("h1_truedistance", "Truth Distance From PV; Truth distance[m]; Entries", 10, 0, 5);
  ((TGaxis*)h1_truedistance->GetYaxis())->SetMaxDigits(4);

  h1_truedistance_CCQE    = new TH1F("h1_truedistance_CCQE", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 10, 0, 5);
  h1_truedistance_CCnonQE = new TH1F("h1_truedistance_CCnonQE", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 10, 0, 5);
  h1_truedistance_NC      = new TH1F("h1_truedistance_NC", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 10, 0, 5);
  h1_truedistance_CCRESdeltap  = new TH1F("h1_truedistance_CCRESdeltap", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 10, 0, 5);
  h1_truedistance_CCRESdeltapp = new TH1F("h1_truedistance_CCRESdeltapp", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 10, 0, 5);
  h1_truedistance_CCRESdelta0  = new TH1F("h1_truedistance_CCRESdelta0", "Truth Distance From PV; Truth distance[m]; Number of Neutron Events", 10, 0, 5);

  h1_Candidatetruedistance = new TH1F("h1_Candidatetruedistance", "Truth Distance From PV; Truth distance[m]; Entries", 10, 0, 5);
  ((TGaxis*)h1_Candidatetruedistance->GetYaxis())->SetMaxDigits(4);

  for (int i=0; i<CUTSTEP; i++) {
    h1_Tagtruedistance[i] = new TH1F(TString::Format("h1_Tagtruedistance_thr%d", i), "Truth Distance of Tagged Truth Neutrons; Truth distance[m]; Entries", 10, 0, 5);
    ((TGaxis*)h1_Tagtruedistance[i]->GetYaxis())->SetMaxDigits(4);

    h1_NNEff_dist[i]      = new TH1F(TString::Format("h1_NNEff_dist_thr%d", i), "NN Classification Efficiency; Truth distance[m]; NN Classification Efficiency", 10, 0, 5);
    h1_OverallEff_dist[i] = new TH1F(TString::Format("h1_OverallEff_dist_thr%d", i), "Overall Tagging Efficiency; Truth distance[m]; Overall Tagging Efficiency", 10, 0, 5);
  }
  h1_PreEff_dist = new TH1F("h1_PreEff_dist", "Pre-seletion Efficiency; Truth distance[m]; Pre-selection Efficiency", 10, 0, 5); 
}

void DistanceViewer::SetHistoFormat() {
  h1_truedistance -> SetLineWidth(2);
  h1_truedistance -> SetLineColor(kAzure-4);
  h1_truedistance -> SetTitleOffset(1.4, "Y");
  h1_truedistance -> SetTitleSize(0.035, "Y");
  h1_truedistance -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCQE -> SetLineWidth(2);
  h1_truedistance_CCQE -> SetLineColor(kAzure-1);
  h1_truedistance_CCQE -> SetFillColor(kAzure-1);
  h1_truedistance_CCQE -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCQE -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCQE -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCnonQE -> SetLineWidth(2);
  h1_truedistance_CCnonQE -> SetLineColor(kCyan-8);
  h1_truedistance_CCnonQE -> SetFillColor(kCyan-8);
  h1_truedistance_CCnonQE -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCnonQE -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCnonQE -> SetLabelSize(0.033, "Y");

  h1_truedistance_NC -> SetLineWidth(2);
  h1_truedistance_NC -> SetLineColor(kTeal+9);
  h1_truedistance_NC -> SetFillColor(kTeal+9);
  h1_truedistance_NC -> SetTitleOffset(1.4, "Y");
  h1_truedistance_NC -> SetTitleSize(0.035, "Y");
  h1_truedistance_NC -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCRESdeltap -> SetLineWidth(2);
  h1_truedistance_CCRESdeltap -> SetLineColor(kPink+1);
  h1_truedistance_CCRESdeltap -> SetFillColor(kPink+1);
  h1_truedistance_CCRESdeltap -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCRESdeltap -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCRESdeltap -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCRESdeltapp -> SetLineWidth(2);
  h1_truedistance_CCRESdeltapp -> SetLineColor(kPink-8);
  h1_truedistance_CCRESdeltapp -> SetFillColor(kPink-8);
  h1_truedistance_CCRESdeltapp -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCRESdeltapp -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCRESdeltapp -> SetLabelSize(0.033, "Y");

  h1_truedistance_CCRESdelta0 -> SetLineWidth(2);
  h1_truedistance_CCRESdelta0 -> SetLineColor(kGray+1);
  h1_truedistance_CCRESdelta0 -> SetFillColor(kGray+1);
  h1_truedistance_CCRESdelta0 -> SetTitleOffset(1.4, "Y");
  h1_truedistance_CCRESdelta0 -> SetTitleSize(0.035, "Y");
  h1_truedistance_CCRESdelta0 -> SetLabelSize(0.033, "Y");

  for (int i=0; i<CUTSTEP; i++) {
    h1_NNEff_dist[i] -> SetLineWidth(2);
    h1_NNEff_dist[i] -> SetLineColor(kAzure-4);
    h1_NNEff_dist[i] -> SetStats(0);
    h1_NNEff_dist[i] -> SetTitleOffset(1.4, "Y");
    h1_NNEff_dist[i] -> SetTitleSize(0.035, "Y");
    h1_NNEff_dist[i] -> SetLabelSize(0.033, "Y");

    h1_OverallEff_dist[i] -> SetLineWidth(2);
    h1_OverallEff_dist[i] -> SetLineColor(kAzure-4);
    h1_OverallEff_dist[i] -> SetStats(0);
    h1_OverallEff_dist[i] -> SetTitleOffset(1.4, "Y");
    h1_OverallEff_dist[i] -> SetTitleSize(0.035, "Y");
    h1_OverallEff_dist[i] -> SetLabelSize(0.033, "Y");
  }
}


float DistanceViewer::GetTruthDistance(CC0PiNumu *numu,
                                       float capturevtxx,
    	                                 float capturevtxy,
    	                                 float capturevtxz,
    	                                 float primaryvtxx,
                                       float primaryvtxy,
    	                                 float primaryvtxz) 
{
  int mode = TMath::Abs(numu->var<int>("mode"));
  float d_x = std::fabs(capturevtxx - primaryvtxx);
  float d_y = std::fabs(capturevtxy - primaryvtxy);
  float d_z = std::fabs(capturevtxz - primaryvtxz);
  float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);
  h1_truedistance -> Fill(d/100.);

  if (mode==1)         h1_truedistance_CCQE          -> Fill(d/100.);
  //if ((mode>=2 && mode<=10) || (mode>=14 && mode<=30))
  if (mode>=2 && mode<=30) h1_truedistance_CCnonQE -> Fill(d/100.);
  if (mode>=31)        h1_truedistance_NC           -> Fill(d/100.);
  if (mode==13)        h1_truedistance_CCRESdeltap  -> Fill(d/100.);
  if (mode==11)        h1_truedistance_CCRESdeltapp -> Fill(d/100.);
  if (mode==12)        h1_truedistance_CCRESdelta0  -> Fill(d/100.);
  return d;
}

void DistanceViewer::GetPreEffDistance(int tagindex,
                                       UInt_t matchtrue,
                                       float capturevtxx,
                                       float capturevtxy,
                                       float capturevtxz,
                                       float primaryvtxx,
                                       float primaryvtxy,
                                       float primaryvtxz) 
{
  //Find matchtrue match with tagindex
  if (tagindex!=-1 && matchtrue==(UInt_t)tagindex) {
    float d_x = std::fabs(capturevtxx - primaryvtxx);
    float d_y = std::fabs(capturevtxy - primaryvtxy);
    float d_z = std::fabs(capturevtxz - primaryvtxz);
    float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);
    h1_Candidatetruedistance -> Fill(d/100.);

    h1_PreEff_dist -> Fill(d/100.);
  }
}

void DistanceViewer::GetOverallEffDistance(int ith,
                                           int tagindex,
                                           UInt_t matchtrue,
                                           float capturevtxx,
                                           float capturevtxy,
                                           float capturevtxz,
                                           float primaryvtxx,
                                           float primaryvtxy,
                                           float primaryvtxz)
{

  //Find kentry match with jentry
  if (tagindex!=-1 && matchtrue==(UInt_t)tagindex) {
    float d_x = std::fabs(capturevtxx - primaryvtxx);
    float d_y = std::fabs(capturevtxy - primaryvtxy);
    float d_z = std::fabs(capturevtxz - primaryvtxz);
    float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

    h1_Tagtruedistance[ith] -> Fill(d/100.);

    h1_OverallEff_dist[ith] -> Fill(d/100.);
    h1_NNEff_dist[ith]      -> Fill(d/100.);
  }

}


void DistanceViewer::cdDistanceViewer(TFile* fout) {
  fout -> mkdir("DistanceViewer");
  fout -> cd("DistanceViewer");
}

void DistanceViewer::WritePlots() {
  h1_truedistance         -> Write();
  h1_truedistance_CCQE    -> Write();
  h1_truedistance_CCnonQE -> Write();
  h1_truedistance_NC      -> Write();
  h1_truedistance_CCRESdeltap  -> Write();
  h1_truedistance_CCRESdeltapp -> Write();
  h1_truedistance_CCRESdelta0  -> Write();

  h1_PreEff_dist -> Sumw2();
  h1_PreEff_dist -> Divide(h1_truedistance);
  h1_PreEff_dist -> Write();
  for (int i=0; i<CUTSTEP; i++) {
    h1_Tagtruedistance[i] -> Write();

    h1_NNEff_dist[i] -> Sumw2();
    h1_NNEff_dist[i] -> Divide(h1_Candidatetruedistance);
    h1_NNEff_dist[i] -> Write();

    h1_OverallEff_dist[i] -> Sumw2();
    h1_OverallEff_dist[i] -> Divide(h1_truedistance);
    h1_OverallEff_dist[i] -> Write();
  }
}

