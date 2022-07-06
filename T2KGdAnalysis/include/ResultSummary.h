
#include "NeutrinoEvents.h"

void WriteNeutrinoSummary(std::fstream resultfile) {
  resultfile << "[Neutrino] All Parent Neutrino Events: " << AllParentNeutrinos << std::endl;
  resultfile << " " << std::endl;

  resultfile << "[Neutrino] Selected CCQE Events   : " << ProtoSelectedCCQEevents    << " -> " << SelectedCCQEevents    << std::endl;
  resultfile << "[Neutrino] Selected CCnonQE Events: " << ProtoSelectedCCnonQEevents << " -> " << SelectedCCnonQEevents << std::endl;
  resultfile << "[Neutrino] Selected NC Events     : " << ProtoSelectedNCevents      << " -> " << SelectedNCevents      << std::endl;
  resultfile << " " << std::endl;

  resultfile << "[Neutrino] Oscillated CCQE Events     : " << OscillatedCCQE    << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedCCQE_wTrueN << ", w/o truth neutrons :" << OscillatedCCQE_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedCCQE_wTagN  << ", w/o tagged neutrons:" << OscillatedCCQE_woTagN  << std::endl;

  resultfile << "[Neutrino] Oscillated CC(2p2h) Events : " << OscillatedCCnonQE << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedCCnonQE_wTrueN << ", w/o truth neutrons :" << OscillatedCCnonQE_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedCCnonQE_wTagN  << ", w/o tagged neutrons:" << OscillatedCCnonQE_woTagN  << std::endl;

  resultfile << "[Neutrino] Oscillated CCRES0 Events   : " << OscillatedCCRES0  << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedCCRES0_wTrueN << ", w/o truth neutrons :" << OscillatedCCRES0_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedCCRES0_wTagN  << ", w/o tagged neutrons:" << OscillatedCCRES0_woTagN  << std::endl;

  resultfile << "[Neutrino] Oscillated CCRES+ Events   : " << OscillatedCCRESp  << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedCCRESp_wTrueN << ", w/o truth neutrons :" << OscillatedCCRESp_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedCCRESp_wTagN  << ", w/o tagged neutrons:" << OscillatedCCRESp_woTagN  << std::endl;

  resultfile << "[Neutrino] Oscillated CCRES++ Events  : " << OscillatedCCRESpp << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedCCRESpp_wTrueN << ", w/o truth neutrons :" << OscillatedCCRESpp_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedCCRESpp_wTagN  << ", w/o tagged neutrons:" << OscillatedCCRESpp_woTagN  << std::endl;

  resultfile << "[Neutrino] Oscillated CC Other Events : " << OscillatedCCOther << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedCCOther_wTrueN << ", w/o truth neutrons :" << OscillatedCCOther_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedCCOther_wTagN  << ", w/o tagged neutrons:" << OscillatedCCOther_woTagN  << std::endl;

  resultfile << "[Neutrino] Oscillated NC Events       : " << OscillatedNC      << std::endl;
  resultfile << "           w/ truth neutrons : " << OscillatedNC_wTrueN << ", w/o truth neutrons :" << OscillatedNC_woTrueN << std::endl;
  resultfile << "           w/ tagged neutrons: " << OscillatedNC_wTagN  << ", w/o tagged neutrons:" << OscillatedNC_woTagN  << std::endl;
  resultfile << " " << std::endl;
  
}