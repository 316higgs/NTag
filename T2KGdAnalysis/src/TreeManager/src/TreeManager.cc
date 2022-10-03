#include "TreeManager.h"
#include "TGaxis.h"

//TagID=0 for w/o tagged neutron sample, TagID=1 for w/ tagged neutron sample
void TreeManager::SetBranch(int TagID) {

  if (TagID==0) {
    woTagNtuple -> Branch("iclass", &iclass_woTagN, "iclass/I");

    //vector variables at neutrino interaction
    woTagNtuple -> Branch("Ibound", &Ibound_woTagN, "Ibound/I");
    woTagNtuple -> Branch("mode", &mode_woTagN, "mode/I");
    woTagNtuple -> Branch("numnu", &numnu_woTagN, "numnu/I");
    woTagNtuple -> Branch("pnu", pnu_woTagN, "pnu[numnu]/F");
    woTagNtuple -> Branch("ipnu", ipnu_woTagN, "ipnu[numnu]/I");
    woTagNtuple -> Branch("dirnu", dirnu_woTagN, "dirnu[numnu][3]/F");
    woTagNtuple -> Branch("npar", &npar_woTagN, "npar/I");
    woTagNtuple -> Branch("dirv", dirv_woTagN, "dirv[npar][3]");  //For MakeRF
    woTagNtuple -> Branch("wgtosc", &wgtosc_woTagN, "wgtosc/D");  //For MakeRF

    //vector variables at neutrino interaction + additional info
    woTagNtuple -> Branch("Npvc", &Npvc_woTagN, "Npvc/I");
    woTagNtuple -> Branch("Ipvc", Ipvc_woTagN, "Ipvc[Npvc]/I");
    woTagNtuple -> Branch("Ichvc", Ichvc_woTagN, "Ichvc[Npvc]/I");
    woTagNtuple -> Branch("Iflvc", Iflvc_woTagN, "Iflvc[Npvc]/I");

    //SK variables (for T2KReWeight)
    woTagNtuple -> Branch("nring", &nring_woTagN, "nring/I");
    woTagNtuple -> Branch("nev", &nev_woTagN, "nev/I");
    woTagNtuple -> Branch("nhitac", &nhitac_woTagN, "nhitac/I");
    woTagNtuple -> Branch("wall", &wall_woTagN, "wall/F");
    woTagNtuple -> Branch("evis", &evis_woTagN, "evis/F");

    //fiTQun variables
    // 1R fit
    woTagNtuple -> Branch("fqnse", &fqnse_woTagN, "fqnse/I");
    woTagNtuple -> Branch("fq1rdir", fq1rdir_woTagN, "fq1rdir[fqnse][7][3]/F");
    woTagNtuple -> Branch("fqmomm", &fqmomm_woTagN, "fqmomm/F");
    woTagNtuple -> Branch("fqmome", &fqmome_woTagN, "fqmome/F");
    // MR fit
    woTagNtuple -> Branch("fqnmrfit", &fqnmrfit_woTagN, "fqnmrfit/I");
    woTagNtuple -> Branch("fqmrdir", fqmrdir_woTagN, "fqmrdir[fqnmrfit][6][3]/F");
    woTagNtuple -> Branch("fqmrmom", fqmrmom_woTagN, "fqmrmom[fqnmrfit][6][3]/F");
    //woTagNtuple -> Branch("ip", &ip_woTagN, "ip/I");        //For T2KReWeight
    woTagNtuple -> Branch("ip", ip_woTagN, "ip[nring]/l");    //For T2KReWeight
    woTagNtuple -> Branch("ipp", &ipp_woTagN, "ipp/I");
    woTagNtuple -> Branch("ippp", &ippp_woTagN, "ippp/I");  //For MakeRF
    woTagNtuple -> Branch("evisible", &evisible_woTagN, "evisible/F");
    woTagNtuple -> Branch("elosssum_pipi", &elosssum_pipi_woTagN, "elosssum_pipi/F");

    //NIWG information
    //woTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_woTagN, "wgts_maqeh/I");
    woTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_woTagN, "wgts_maqeh/D");
    woTagNtuple -> Branch("DeltaPForEmiss0", &DeltaPForEmiss0_woTagN, "DeltaPForEmiss0/D");
  }
  else {
    wTagNtuple -> Branch("iclass", &iclass_wTagN, "iclass/I");

    //vector variables at neutrino interaction
    wTagNtuple -> Branch("Ibound", &Ibound_wTagN, "Ibound/I");
    wTagNtuple -> Branch("mode", &mode_wTagN, "mode/I");
    wTagNtuple -> Branch("numnu", &numnu_wTagN, "numnu/I");
    wTagNtuple -> Branch("pnu", pnu_wTagN, "pnu[numnu]/F");
    wTagNtuple -> Branch("ipnu", ipnu_wTagN, "ipnu[numnu]/I");
    wTagNtuple -> Branch("dirnu", dirnu_wTagN, "dirnu[numnu][3]/F");
    wTagNtuple -> Branch("npar", &npar_wTagN, "npar/I");
    wTagNtuple -> Branch("dirv", dirv_wTagN, "dirv[npar][3]");
    wTagNtuple -> Branch("wgtosc", &wgtosc_wTagN, "wgtosc/D");

    //vector variables at neutrino interaction + additional info
    wTagNtuple -> Branch("Npvc", &Npvc_wTagN, "Npvc/I");
    wTagNtuple -> Branch("Ipvc", Ipvc_wTagN, "Ipvc[Npvc]/I");
    wTagNtuple -> Branch("Ichvc", Ichvc_wTagN, "Ichvc[Npvc]/I");
    wTagNtuple -> Branch("Iflvc", Iflvc_wTagN, "Iflvc[Npvc]/I");

    //SK variables (for T2KReWeight)
    wTagNtuple -> Branch("nring", &nring_wTagN, "nring/I");
    wTagNtuple -> Branch("nev", &nev_wTagN, "nev/I");
    wTagNtuple -> Branch("nhitac", &nhitac_wTagN, "nhitac/I");
    wTagNtuple -> Branch("wall", &wall_wTagN, "wall/F");
    wTagNtuple -> Branch("evis", &evis_wTagN, "evis/F");

    //fiTQun variables
    // 1R fit
    wTagNtuple -> Branch("fqnse", &fqnse_wTagN, "fqnse/I");
    wTagNtuple -> Branch("fq1rdir", fq1rdir_wTagN, "fq1rdir[fqnse][7][3]/F");
    wTagNtuple -> Branch("fqmomm", &fqmomm_wTagN, "fqmomm/F");
    wTagNtuple -> Branch("fqmome", &fqmome_wTagN, "fqmome/F");
    // MR fit
    wTagNtuple -> Branch("fqnmrfit", &fqnmrfit_wTagN, "fqnmrfit/I");
    wTagNtuple -> Branch("fqmrdir", fqmrdir_wTagN, "fqmrdir[fqnmrfit][6][3]/F");
    wTagNtuple -> Branch("fqmrmom", fqmrmom_wTagN, "fqmrmom[fqnmrfit][6][3]/F");
    //wTagNtuple -> Branch("ip", &ip_wTagN, "ip/I");        //For T2KReWeight
    wTagNtuple -> Branch("ip", ip_wTagN, "ip[nring]/l");    //For T2KReWeight
    wTagNtuple -> Branch("ipp", &ipp_wTagN, "ipp/I");
    wTagNtuple -> Branch("ippp", &ippp_wTagN, "ippp/I");
    wTagNtuple -> Branch("evisible", &evisible_wTagN, "evisible/F");
    wTagNtuple -> Branch("elosssum_pipi", &elosssum_pipi_wTagN, "elosssum_pipi/F");

    //NIWG information
    //wTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_wTagN, "wgts_maqeh/I");
    wTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_wTagN, "wgts_maqeh/D");
    wTagNtuple -> Branch("DeltaPForEmiss0", &DeltaPForEmiss0_wTagN, "DeltaPForEmiss0/D");
  }
  
}


void TreeManager::FillBrankTree(int TagID) {

  for (int ientry=0; ientry<100; ientry++) {
    if (TagID==0) {
      //iclass_woTagN = 1302112;
      iclass_woTagN = 0;
      mode_woTagN   = 0;
      Ibound_woTagN = 0;
      numnu_woTagN  = 0;
      for (Int_t ivc=0; ivc<numnu_woTagN; ivc++) {
        pnu_woTagN[ivc]  = 0.;
        ipnu_woTagN[ivc] = 0.;
        for (int idir=0; idir<3; idir++) {
          dirnu_woTagN[ivc][idir] = 0.;
        }
      }

      Npvc_woTagN = 0;
      for (Int_t ivc=0; ivc<Npvc_woTagN; ivc++) {
        Ipvc_woTagN[ivc]  = 0;
        Ichvc_woTagN[ivc] = 0;
        Iflvc_woTagN[ivc] = 0;
      }

      npar_woTagN = 0;
      for (int iv=0; iv<npar_woTagN; iv++) {
        for (int idir=0; idir<3; idir++) {
          dirv_woTagN[iv][idir] = 0.;
        }
      }
      wgtosc_woTagN = 0.;
      
      nring_woTagN  = 0;
      nev_woTagN    = 0;
      nhitac_woTagN = 0;
      wall_woTagN   = 0.;
      evis_woTagN   = 0.;

      fqnse_woTagN = 0;
      for (Int_t ifq=0; ifq<fqnse_woTagN; ifq++) {
        for (int ihyp=0; ihyp<7; ihyp++) {
          for (int idir=0; idir<3; idir++) {
            fqmrdir_woTagN[ifq][ihyp][idir] = 0.;
            fqmrmom_woTagN[ifq][ihyp][idir] = 0.;
          }
        }
      }

      for (int iring=0; iring<nring_woTagN; iring++) {
        ip_woTagN[iring] = 0;
      }
      ipp_woTagN           = -1;
      ippp_woTagN          = -1;
      evisible_woTagN      = -1;
      elosssum_pipi_woTagN = -1;

      wgts_maqeh_woTagN = 1.;
      DeltaPForEmiss0_woTagN = 0.;

    }
    else {
      //iclass_wTagN = 1312112;
      iclass_wTagN = 0;
      mode_wTagN   = 0;
      Ibound_wTagN = 0;
      numnu_wTagN  = 0;
      for (Int_t ivc=0; ivc<numnu_wTagN; ivc++) {
        pnu_wTagN[ivc]  = 0.;
        ipnu_wTagN[ivc] = 0.;
        for (int idir=0; idir<3; idir++) {
          dirnu_wTagN[ivc][idir] = 0.;
        }
      }

      Npvc_wTagN = 0;
      for (Int_t ivc=0; ivc<Npvc_wTagN; ivc++) {
        Ipvc_wTagN[ivc]  = 0;
        Ichvc_wTagN[ivc] = 0;
        Iflvc_wTagN[ivc] = 0;
      }

      npar_wTagN = 0;
      for (int iv=0; iv<npar_wTagN; iv++) {
        for (int idir=0; idir<3; idir++) {
          dirv_wTagN[iv][idir] = 0.;
        }
      }
      wgtosc_wTagN = 0.;
      
      nring_wTagN  = 0;
      nev_wTagN    = 0;
      nhitac_wTagN = 0;
      wall_wTagN   = 0.;
      evis_wTagN   = 0.;

      fqnse_wTagN = 0;
      for (Int_t ifq=0; ifq<fqnse_wTagN; ifq++) {
        for (int ihyp=0; ihyp<7; ihyp++) {
          for (int idir=0; idir<3; idir++) {
            fqmrdir_wTagN[ifq][ihyp][idir] = 0.;
            fqmrmom_wTagN[ifq][ihyp][idir] = 0.;
          }
        }
      }

      for (int iring=0; iring<nring_wTagN; iring++) {
        ip_wTagN[iring] = 0;
      }
      ipp_wTagN           = -1;
      ippp_wTagN          = -1;
      evisible_wTagN      = -1;
      elosssum_pipi_wTagN = -1;

      wgts_maqeh_wTagN = 1.;
      DeltaPForEmiss0_wTagN = 0.;
    }

    this -> FillTree(TagID);
  }
  
}


void TreeManager::FillTree(int TagID) {
  if (TagID==0) woTagNtuple -> Fill();
  else wTagNtuple -> Fill();
}

void TreeManager::WriteTree(TString OutName, int TagID) {
  TFile* fout = new TFile(OutName, "RECREATE");
  fout -> cd();
  if (TagID==0) woTagNtuple -> Write();
  else wTagNtuple -> Write();
}