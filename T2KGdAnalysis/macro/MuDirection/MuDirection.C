void MuDirection() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");

  TH1F* h1_CCQE          = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode0");
  TH1F* h1_CCnonQE       = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode1");
  TH1F* h1_CCRESdeltap   = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode3");
  TH1F* h1_CCRESdeltapp  = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode4");
  TH1F* h1_CCRESdelta0   = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode5");
  TH1F* h1_CCOther       = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode6");
  TH1F* h1_NC            = (TH1F*)fin->Get("NeutrinoOscillation/h1_Truecosthetamu_mode2");
  h1_CCQE  -> SetStats(0);

  THStack* hs_RecoDir  = new THStack("hs_RecoDir ", "Reco. muon direction; #mu Scattering Angle cos#theta_{#mu}; Number of Neutrino Events");
  hs_RecoDir  -> Add(h1_NC );
  hs_RecoDir  -> Add(h1_CCOther );
  hs_RecoDir  -> Add(h1_CCRESdelta0 );
  hs_RecoDir  -> Add(h1_CCRESdeltap );
  hs_RecoDir  -> Add(h1_CCRESdeltapp );
  hs_RecoDir  -> Add(h1_CCnonQE );
  hs_RecoDir  -> Add(h1_CCQE );

  TCanvas* c  = new TCanvas("c ", "c ", 900, 900);
  c  -> SetGrid();
  //hs_RecoDir  -> SetMaximum(4000);
  hs_RecoDir  -> Draw();
  ((TGaxis*)hs_RecoDir->GetYaxis())->SetMaxDigits(3);
  hs_RecoDir  ->GetYaxis()->SetTitleSize(0.035);
  hs_RecoDir  ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoDir  ->GetYaxis()->SetLabelSize(0.033);
  hs_RecoDir  -> Draw();
  
  c ->RedrawAxis();

  TLegend* legend1 = new TLegend(0.15, 0.45, 0.55, 0.85);
  legend1 -> SetTextSize(0.03);
  //legend1->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #nu_{#mu} #rightarrow #nu_{#mu} MC }","");
  legend1->AddEntry((TObject*)0,"#kern[-0.3]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  legend1 -> AddEntry(h1_CCQE , "CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCnonQE , "CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCRESdeltap , "CCRES(#Delta^{+})", "F");
  legend1 -> AddEntry(h1_CCRESdeltapp , "CCRES(#Delta^{++})", "F");
  legend1 -> AddEntry(h1_CCRESdelta0 , "CCRES(#Delta^{0})", "F");
  legend1 -> AddEntry(h1_CCOther , "CC-other", "F");
  legend1 -> AddEntry(h1_NC , "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw();

}