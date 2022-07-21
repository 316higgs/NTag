
void randomness() {

  TFile* fin = new TFile("/disk02/usr6/sedi/fiTQun/converted_output/0026Gd.numubar/numubar_x_numubar.fiTQun.0026Gd.NEUTcount000.part001.skip0.root");
  TTree* tree = static_cast<TTree*>fin->Get("h1");
  float pnu = 0.;
  
  TH1F* h1_pnu = (TH1F*)fin->Get("pnu0");
  h1_pnu -> GetStdDev();
}