
bool etagmode = false;

enum OscChan::E_OSC_CHAN CLTOptionOscMode(TString OscKeyWord, TString Osc) {
  enum OscChan::E_OSC_CHAN eOscMode = eNUMU;
  if (OscKeyWord=="-OSCCH") {
    if (Osc=="NUMU" || Osc=="numu") eOscMode = eNUMU;
    else if (Osc=="NUMUBAR" || Osc=="numubar") eOscMode = eNUMUBAR;
    else {
      std::cout << " " << std::endl;
      std::cout << "[!!!CLT error!!!] Oscillation channel can not be found. --- input NUMU/NUMUBAR" << std::endl;
      exit(-1);
    }
  }
  return eOscMode;
}

enum BeamMode::E_BEAM_MODE CLTOptionBeamMode(TString BeamKeyWord, TString Beam) {
  enum BeamMode::E_BEAM_MODE eBeamMode = eFHC;
  if (BeamKeyWord=="-BEAMMODE") {
    if (Beam=="FHC") eBeamMode = eFHC;
    else if (Beam=="RHC") eBeamMode = eRHC;
    else {
      std::cout << " " << std::endl;
      std::cout << "[!!!CLT error!!!] Oscillation channel can not be found. --- input FHC or RHC" << std::endl;
      exit(-1);
    }
  }
  return eBeamMode;
}

void CLTOptionETAG(TString ETAGKeyword, TString ETAG) {
  if (ETAGKeyword=="-ETAG") {
    if (ETAG=="ON" || ETAG=="On" || ETAG=="on") etagmode = true;
    else if (ETAG=="OFF" || ETAG=="Off" || ETAG=="off") etagmode = false;
    else {
      std::cout << " " << std::endl;
      std::cout << "[!!!CLT error!!!] Decay-e tagging mode can not be found. --- input ON or OFF" << std::endl;
      exit(-1);
    }
  }
}

void CLTOptionPrePara(TString PreParaKeyword, TString PrePara) {
  if (PreParaKeyword=="-TWIDTH" || PreParaKeyword=="-NHITSTH") {
    std::cout << "[### CLT Option Summary ###] " << PreParaKeyword << ": " << PrePara << std::endl;
  }
  else {
    std::cout << "[!!!CLT error!!!] Pre-selection parameter should be specified at command line." << std::endl;
    std::cout << "                  Please specify values with " << PreParaKeyword << " option." << std::endl;
    exit(-1);
  }
}

void CLTOptionWindow(TString WINDOWKeyword, TString WINDOW) {
  if (WINDOWKeyword=="-WINDOW") {
    std::cout << "[### CLT Option Summary ###] " << WINDOWKeyword << ": " << WINDOW << std::endl;
  }
  else {
    std::cout << "[!!!CLT error!!!] Window size should be specified at command line." << std::endl;
    std::cout << "                  Please specify values with " << WINDOWKeyword << " option." << std::endl;
    exit(-1);
  }
}


void CLTOptionSummary(TString ETAGKeyword, TString ETAG,
                      TString MCTypeKeyword, TString MCType) 
{
  bool etagoption = false;
  if (ETAGKeyword=="-ETAG") {
    etagoption = true;
    std::cout << "[### CLT Option Summary ###] e-tagging: " << ETAG << std::endl;
  }
  bool mctypeoption = false;
  if (MCTypeKeyword=="-MCType") {
    mctypeoption = true;
    std::cout << "[### CLT Option Summary ###] MC type: " << MCType << std::endl;
  }

  if (etagoption==false && mctypeoption==false) {
    std::cout << " " << std::endl;
    std::cout << "[### CLT Option Summary ###] No option" << std::endl;
  }
  
}
  