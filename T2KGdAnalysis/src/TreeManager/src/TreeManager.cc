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

    //vector variables at neutrino interaction + additional info
    woTagNtuple -> Branch("Npvc", &Npvc_woTagN, "Npvc/I");
    woTagNtuple -> Branch("Ipvc", Ipvc_woTagN, "Ipvc[Npvc]/I");
    woTagNtuple -> Branch("Ichvc", Ichvc_woTagN, "Ichvc[Npvc]/I");
    woTagNtuple -> Branch("Iflvc", Iflvc_woTagN, "Iflvc[Npvc]/I");

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
    woTagNtuple -> Branch("ipp", &ipp_woTagN, "ipp/I");
    woTagNtuple -> Branch("evisible", &evisible_woTagN, "evisible/F");
    woTagNtuple -> Branch("elosssum_pipi", &elosssum_pipi_woTagN, "elosssum_pipi/F");

    //NIWG information
    woTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_woTagN, "wgts_maqeh/I");
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

    //vector variables at neutrino interaction + additional info
    wTagNtuple -> Branch("Npvc", &Npvc_wTagN, "Npvc/I");
    wTagNtuple -> Branch("Ipvc", Ipvc_wTagN, "Ipvc[Npvc]/I");
    wTagNtuple -> Branch("Ichvc", Ichvc_wTagN, "Ichvc[Npvc]/I");
    wTagNtuple -> Branch("Iflvc", Iflvc_wTagN, "Iflvc[Npvc]/I");

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
    wTagNtuple -> Branch("ipp", &ipp_wTagN, "ipp/I");
    wTagNtuple -> Branch("evisible", &evisible_wTagN, "evisible/F");
    wTagNtuple -> Branch("elosssum_pipi", &elosssum_pipi_wTagN, "elosssum_pipi/F");

    //NIWG information
    wTagNtuple -> Branch("wgts_maqeh", &wgts_maqeh_wTagN, "wgts_maqeh/I");
    wTagNtuple -> Branch("DeltaPForEmiss0", &DeltaPForEmiss0_wTagN, "DeltaPForEmiss0/D");
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