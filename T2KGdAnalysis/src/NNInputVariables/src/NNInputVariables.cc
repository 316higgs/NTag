#include "NNInputVariables.h"



void NNInputVariables::SetHistoFrame(int vartype, TString histtitle) {

  switch (vartype) {
  	case 0:  //NHits
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 80, 0, 80);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 80, 0, 80);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 80, 0, 80);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 80, 0, 80);
      break;
    case 1:  //N200
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 80, 0, 80);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 80, 0, 80);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 80, 0, 80);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 80, 0, 80);
      break;
    case 2:  //TRMS
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, 0, 5);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, 0, 5);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, 0, 5);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, 0, 5);
      break;
    case 3:  //DWall
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, -150, 1600);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, -150, 1600);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, -150, 1600);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, -150, 1600);
      break;
    case 4:  //DWallMeanDir
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, 0, 5000);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, 0, 5000);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, 0, 5000);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, 0, 5000);
      break;
    case 5:  //OpeningAngleMean
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, 20, 100);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, 20, 100);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, 20, 100);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, 20, 100);
      break;
    case 6:  //OpeningAngleStdev
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, 0, 50);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, 0, 50);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, 0, 50);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, 0, 50);
      break;
    case 7:  //OpeningAngleSkew
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, -200, 200);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, -200, 200);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, -200, 200);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, -200, 200);
      break;
    case 8: //MeanDirAngleMean
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, 0, 100);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, 0, 100);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, 0, 100);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, 0, 100);
      break;
    case 9: //MeanDirAngleRMS
      h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, 0, 100);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, 0, 100);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, 0, 100);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, 0, 100);
      break;
    case 10:  //Beta1
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, -0.2, 1.1);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, -0.2, 1.1);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, -0.2, 1.1);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, -0.2, 1.1);
      break;
    case 11:  //Beta5
  	  h1_NNvar_Gd[vartype]       = new TH1F(TString::Format("h1_NNvar_Gd_type%d", vartype),    histtitle, 100, -0.2, 1.1);
      h1_NNvar_H[vartype]        = new TH1F(TString::Format("h1_NNvar_H_type%d", vartype),     histtitle, 100, -0.2, 1.1);
      h1_NNvar_AccNoise[vartype] = new TH1F(TString::Format("h1_NNvar_AccNoise_type%d", vartype), histtitle, 100, -0.2, 1.1);
      h1_NNvar_Decaye[vartype]   = new TH1F(TString::Format("h1_NNvar_Decaye_type%d", vartype), histtitle, 100, -0.2, 1.1);
      break;
  }
}

void NNInputVariables::SetHistoFormat(int vartype, TString histtitle) {
  h1_NNvar_Gd[vartype]       -> SetLineWidth(1);
  h1_NNvar_H[vartype]        -> SetLineWidth(1);
  h1_NNvar_AccNoise[vartype] -> SetLineWidth(1);
  h1_NNvar_Decaye[vartype]   -> SetLineWidth(1);

  h1_NNvar_Gd[vartype]       -> SetLineColor(kTeal-5);
  h1_NNvar_H[vartype]        -> SetLineColor(kAzure-4);
  h1_NNvar_AccNoise[vartype] -> SetLineColor(kGray+2);
  h1_NNvar_Decaye[vartype]   -> SetLineColor(kYellow-3);

  h1_NNvar_Gd[vartype]       -> SetTitleOffset(1.3, "Y");
  h1_NNvar_H[vartype]        -> SetTitleOffset(1.3, "Y");
  h1_NNvar_AccNoise[vartype] -> SetTitleOffset(1.3, "Y");
  h1_NNvar_Decaye[vartype]   -> SetTitleOffset(1.3, "Y");

  h1_NNvar_Gd[vartype]       -> SetTitleSize(0.035, "Y");
  h1_NNvar_H[vartype]        -> SetTitleSize(0.035, "Y");
  h1_NNvar_AccNoise[vartype] -> SetTitleSize(0.035, "Y");
  h1_NNvar_Decaye[vartype]   -> SetTitleSize(0.035, "Y");

  h1_NNvar_Gd[vartype]       -> SetLabelSize(0.035, "Y");
  h1_NNvar_H[vartype]        -> SetLabelSize(0.035, "Y");
  h1_NNvar_AccNoise[vartype] -> SetLabelSize(0.035, "Y");
  h1_NNvar_Decaye[vartype]   -> SetLabelSize(0.035, "Y");
}

void NNInputVariables::SetNNinputHisto() {
  TString histtitle;
  for (int vartype=0; vartype<NNVARIABLES; vartype++) {
  	switch (vartype) {
  	  case 0:
  	    histtitle = "NHits; NHits; Area Normalized";
  	    break;
  	  case 1:
  	    histtitle = "N200; N200; Area Normalized";
  	    break;
  	  case 2:
  	    histtitle = "TRMS; TRMS; Area Normalized";
  	    break;
      case 3:
  	    histtitle = "DWall; DWall; Area Normalized";
  	    break;
  	  case 4:
  	    histtitle = "DWallMeanDir; DWallMeanDir; Area Normalized";
  	    break;
  	  case 5:
  	    histtitle = "OpeningAngleMean; OpeningAngleMean; Area Normalized";
  	    break;
      case 6:
  	    histtitle = "OpeningAngleStdev; OpeningAngleStdev; Area Normalized";
  	    break;
  	  case 7:
  	    histtitle = "OpeningAngleSkew; OpeningAngleSkew; Area Normalized";
  	    break;
  	  case 8:
  	    histtitle = "MeanDirAngleMean; MeanDirAngleMean; Area Normalized";
  	    break;
  	  case 9:
  	    histtitle = "MeanDirAngleRMS; MeanDirAngleRMS; Area Normalized";
  	    break;
  	  case 10:
  	    histtitle = "Beta1; Beta1; Area Normalized";
  	    break;
  	  case 11:
  	    histtitle = "Beta5; Beta5; Area Normalized";
  	    break;
  	}
  	this->SetHistoFrame(vartype, histtitle);
  	this->SetHistoFormat(vartype, histtitle);
  }

  for (int i=0; i<4; i++) {
    h1_NTagOut[i] = new TH1F(TString::Format("h1_NTagOut_type%d", i), "h1_NTagOut; TagOut; Number of Candidates", 100, 0, 1);
    h1_NTagOut[i] -> SetLineWidth(2);
  }
  h1_NTagOut[0] -> SetLineColor(kGray+2);
  h1_NTagOut[1] -> SetLineColor(kYellow-3);
  h1_NTagOut[2] -> SetLineColor(kAzure-4);
  h1_NTagOut[3] -> SetLineColor(kTeal-5);

  h1_NTagOut[0] -> SetFillColor(kGray+2);
  h1_NTagOut[1] -> SetFillColor(kYellow-3);
  h1_NTagOut[2] -> SetFillColor(kAzure-4);
  h1_NTagOut[3] -> SetFillColor(kTeal-5);


  h1_FitT_NHitsExcess = new TH1F("h1_FitT_NHitsExcess", "h1_FitT_NHitsExcess; FitT[#musec]; Entries", 80, 0, 20);
  //h1_lmecscnd_NHitsExcess = new TH1F("h1_lmecscnd_NHitsExcess", "h1_lmecscnd_NHitsExcess; lmecscnd; Number of Secondary Particles", 30, 0, 30);
  //h2_tscnd_lmecscnd_NHitsExcess = new TH2F("h2_tscnd_lmecscnd_NHitsExcess", "h1_tscnd_lmecscnd_NHitsExcess; tscnd; lmecscnd", 100, 0, 20, 30, 0, 30);

  //h2_NHits_x_NumAccNoise = new TH2F("h2_NHits_x_NumAccNoise", "h2_NHits_x_NumAccNoise; NHits; Number of Acc. Noise", 80, 0, 80, 80, 40, 120);
  //h2_N200_x_NumAccNoise  = new TH2F("h2_N200_x_NumAccNoise", "h2_N200_x_NumAccNoise; N200; Number of Acc. Noise", 80, 0, 80, 80, 40, 120);

  h1_FitT_NHitsExcess -> SetLineWidth(2);

  h1_IntID = new TH1F("h1_IntID", "h1_IntID; IntID; Area Normalized", 25, 5, 30);
  h1_KE = new TH1F("h1_KE", "h1_KE; E_{#gamma}[MeV]; Area Normalized", 20, 0, 10);
  h1_timediff = new TH1F("h1_timediff", "h1_timediff; t^{true} - t^{reco}[#musec]; Area Normalized", 50, -0.02, 0.02);

  //h2_tscnd_lmecscnd_NHitsExcess -> SetStats(0);
  //h2_NHits_x_NumAccNoise -> SetStats(0);
  //h2_N200_x_NumAccNoise  -> SetStats(0);
}


/*void NNInputVariables::GetCaptureMuon(Int_t nscndprt, Float_t* tscnd, Int_t* iprtscnd, Int_t* iprntprt, Float_t** pscnd) {
  
  //truth secondary loop
  for (Int_t itruth=0; itruth<nscndprt; itruth++) {
    
    //Gamma from mu- (not mu+!)
    if (iprntprt[itruth]==13 && std::abs(iprtscnd[itruth])==22) {
      h1_tscnd_capture -> Fill(tscnd[itruth]/1000.);

      float gammaenergy = std::sqrt( pscnd[itruth][0]*pscnd[itruth][0] + pscnd[itruth][1]*pscnd[itruth][1] + pscnd[itruth][2]*pscnd[itruth][2] );
      h1_KE -> Fill(gammaenergy);
    }
  }

}*/


void NNInputVariables::cdNNInputVariables(TFile* fout) {
  fout -> mkdir("NNInputVariables");
  fout -> cd("NNInputVariables");
}

void NNInputVariables::WritePlots() {
  for (int i=0; i<NNVARIABLES; i++) {
    Double_t tot_Gd;
    Double_t tot_H;
    Double_t tot_AccNoise;
    Double_t tot_Decaye;

    tot_Gd       = h1_NNvar_Gd[i]       -> Integral();
    tot_H        = h1_NNvar_H[i]        -> Integral();
    tot_AccNoise = h1_NNvar_AccNoise[i] -> Integral();
    tot_Decaye   = h1_NNvar_Decaye[i]   -> Integral();

    h1_NNvar_Gd[i]       -> Scale(1./tot_Gd);
    h1_NNvar_H[i]        -> Scale(1./tot_H);
    h1_NNvar_AccNoise[i] -> Scale(1./tot_AccNoise);
    h1_NNvar_Decaye[i]   -> Scale(1./tot_Decaye); 

    h1_NNvar_AccNoise[i] -> Write();
    h1_NNvar_Decaye[i]   -> Write();
    h1_NNvar_H[i]        -> Write();
    h1_NNvar_Gd[i]       -> Write();
  }

  for (int i=0; i<4; i++) h1_NTagOut[i] -> Write();

  h1_FitT_NHitsExcess -> Write();
  //h1_lmecscnd_NHitsExcess -> Write();
  //h2_tscnd_lmecscnd_NHitsExcess -> Write();
  //h2_NHits_x_NumAccNoise -> Write();
  //h2_N200_x_NumAccNoise  -> Write();

  Double_t tot_IntID  = h1_IntID->Integral();
  Double_t tot_energy = h1_KE->Integral();
  //Double_t tot_timediff = h1_timediff->Integral();
  if (tot_IntID != 0) h1_IntID  -> Scale(1./tot_IntID);
  if (tot_energy != 0) h1_KE -> Scale(1./tot_energy);
  //if (tot_timediff != 0) h1_timediff -> Scale(1./tot_timediff);
  h1_IntID  -> Write();
  h1_KE -> Write();
  h1_timediff -> Write();
}

