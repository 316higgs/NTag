#include "NtupleMaker.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"
#include "TVirtualFitter.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TreeManager.h"


// These contain the common block variables 
#include <tqrealroot.h>
#include <loweroot.h>
#include <skheadC.h>
#include <skparmC.h>
#include <sktqC.h>
#include <skbadcC.h>
#include <geotnkC.h>
#include <geopmtC.h>
#include <skwaterlenC.h>
#include <DataDefinition.h>
#include <Reformatter.h>
#include <vcworkC.h>
#include <zbsC.h>
#include <zbsmc.h>
#include "vcworkC.h"
#include "vcvrtxC.h"
#include "neworkC.h"
#include "neutcrsC.h"
#include "necardC.h"
#include "posinnucC.h"
#include "fsihistC.h"

#include "effwallf.h"
#include "wallsk.h"
#include "typepdf.hh"

#include "skroot.h"

using namespace std;


NtupleMaker::NtupleMaker() : ncg(), nstep(100), minNtof(4)
{
    angledown = 0;
    angleup   = 90;
    tchelow   = -500;
    tchehigh  = 1500;
    hcheren = new TH1D("hcheren", "Opening Cherenkov Angle from 3-PMT combinations", nstep, angledown, angleup);    
    SetQuiet();

    like_all = 0;
    like_fail = 0;

    // Set first/last SK runs in each MR run
    // Find these values using ncamma/SystematicErrors/FirstLastRun.py
    for (int i = 0; i < 100; i++) {
        mrfirst[i] = 0; mrlast[i] = 0;
    }
    mrfirst[29] = 66251;  mrlast[29] = 66295;
    mrfirst[30] = 66494;  mrlast[30] = 66521;
    mrfirst[31] = 66585;  mrlast[31] = 66608;
    mrfirst[32] = 66679;  mrlast[32] = 66726;
    mrfirst[33] = 66770;  mrlast[33] = 66902;
    mrfirst[34] = 66916;  mrlast[34] = 66945;
    mrfirst[36] = 67877;  mrlast[36] = 67978;
    mrfirst[37] = 68045;  mrlast[37] = 68175;
    mrfirst[38] = 68200;  mrlast[38] = 68208;
    mrfirst[41] = 69542;  mrlast[41] = 69586;
    mrfirst[42] = 69626;  mrlast[42] = 69720;
    mrfirst[43] = 69734;  mrlast[43] = 69753;
    mrfirst[44] = 70524;  mrlast[44] = 70619;
    mrfirst[45] = 70670;  mrlast[45] = 70721;
    mrfirst[46] = 70829;  mrlast[46] = 70882;
    mrfirst[47] = 70901;  mrlast[47] = 71042;
    mrfirst[48] = 71042;  mrlast[48] = 71067;
    mrfirst[49] = 71239;  mrlast[49] = 71245;
    mrfirst[55] = 72674;  mrlast[55] = 72733;
    mrfirst[56] = 72734;  mrlast[56] = 72767;
}


NtupleMaker::~NtupleMaker()
{
    //delete hcheren;
}


void NtupleMaker::OpenInfile(const char * _infile)
{
    infile = _infile;

    // Right now assume zbs=mc and root=data
    // Set MC modes
    isMC = infile.Contains("zbs");
    ncg.SetMC(isMC);

    zbsinit_(); // wrapper around kzinit/kzlimit
    kzeclr_();

    // Set SK Options
    std::string opt;

    if (isMC) opt = "31,30,29,27,26,25";
    else      opt = "31,30,29,26,25,16,15";
    skoptn_(opt.c_str(), opt.length() );

    
    
    // Open the file for reading
    luni = 10 ;
    //int ipt = 1; 
    //int ierr = 0;
    //char * disk = "DISK";
    if (isMC) {
        int  rw     = 0  ; // for reading
        char ftype;
        ftype = 'Z';
        cout << "Reading in mc from " << infile << endl;
        fort_fopen_(&luni, infile, &ftype, &rw);
        txtfile = infile.ReplaceAll(".zbs",".txt");
    }
    else {
      //Now, the data file is root format, include sklib class to read root file
     
      cout << "Reading in data from " << infile << endl;
      skroot_open_read_(&luni);
      skroot_set_input_file_(&luni, infile, strlen(infile));
      skroot_initialize_(&luni);

      mgr= skroot_get_mgr(&luni);
      datatree= mgr->GetTree();

      HEAD    = mgr->GetHEAD();
      TQREAL  = mgr->GetTQREALINFO();
      TQAREAL = mgr->GetTQAREALINFO();
      LOWE    = mgr->GetLOWE();
      ATMPD   = mgr->GetATMPD();
      UPMU    = mgr->GetUPMU();
      MU      = mgr->GetMU();
      SLE     = mgr->GetSLE();

      txtfile = infile.ReplaceAll(".root",".txt");
    }

    txtstream.open(txtfile.Data());

    //set_rflist_(&luni, infile, "DISK","",
    //            "RED","","",
    //            "recl=5670 status=old","","");
    //skopenf_(luni, ipt, "Z", ierr, 1);

    // Setup Bonsai
    //bonsai_ini_();

}


void NtupleMaker::OpenOutfile(const char * _outfile)
{
    outfile = _outfile;
    cout << "Writing to " << outfile << endl;
    fout_root = new TFile(outfile, "RECREATE");
    theOTree = new TTree("h1", "T2KLowE Common Ntuple");
    ncg.createTree(theOTree);
}

void NtupleMaker::Finish()
{
    theOTree->Write();
    //delete theOTree;
    fout_root->Close();
    //delete fout_root;
    //theOTree = 0;
    //fout_root = 0;

    if (isMC) {
        skclosef_(luni);
    }
    else {
        skroot_close_(&luni);

    }
    //bonsai_end_();
}


bool NtupleMaker::ReadNextEvent()
{
    bool status;

    ncg.Clear();

    // read the binary information
    if (isMC) status = ReadMCEvent();
    else      status = ReadDataEvent();
    
    if (!status) return false;

    /* - Do not read text file anymore
    // read the text information, common to both data & mc
    Float_t         dt0;
    Float_t         dt0vtx;    // dt0 corrected for vertex position
    Int_t           dt0type;   // Which gps was used
    Int_t           n30max;    // Maximum peak within 30 ns before event 
    Float_t         n30time;   // Time of the maximum 30 ns peak 

    int _entry, _run, _event;  // Stored for cross-checking

    txtstream >> _entry >> _run >> _event >> ncg.dt0 >> ncg.dt0vtx >> ncg.dt0type >> ncg.n30max >> ncg.n30time;
    
    // Fix time units
    ncg.dt0     *= 1e-3;
    ncg.dt0vtx  *= 1e-3;
    ncg.n30time *= 1e-3;
    
    cout << "TEST B: " << ncg.dt0 << " " << ncg.dt0vtx << " " << ncg.n30time << endl;
    
    if (_event != ncg.nev || (_run != ncg.nrun && !isMC) ) {
        cerr << "Mismatch: binary " << ncg.nrun << ", " << ncg.nev << "  text: " << _run << ", " << _event << endl;
    }
    */

    return true;
}



bool NtupleMaker::ReadMCEvent()
{

    //Read SHE trigger of event; fill in basic information, vertex etc
    int ierr = 0;
    int nother = 0;
    
    if (verbose)
        cout << endl << endl << "Reading new event... " << endl;
    while (1)
    {
        skcread_(luni, ierr);
        if (ierr==2) return false; // EOF: 
        else if (ierr > 0) continue; //RUNINF or PDST banks
        else break;
    }

    /*
    // Check trigger information
    if (skhead_.idtgsk&0x10000000)
    {
        nshe++;
    }
    else
    {
        nother++; //this is events triggered by HE but not SHE. Typically these do not have AFT trigger attached.
        cout << "Non-SHE trigger: " << skhead_.idtgsk << "; nother = " << nother <<  endl;
        if (skhead_.idtgsk != 7) cout << "Non-HE trigger: " << skhead_.idtgsk << endl; 
    }
    */

    // Get header information


    //get bank containing reconstructed vertex information
    float trgofst;
    trginfo_(&trgofst);

    skgetv_();
    //int bank = 0;
    //aprstbnk_(&bank);
 
    //sktqz total information

    // Get Bonsai information. Try from file, if not, run Bonsai
    
    double bonsai_vertex[3];
    double bonsai_dir[3];
    int    bsn50    = 0;
    //double bsgood1  = 0;
    double bsgoodness  = 0;
    //double bsgood3  = 0;
    double bsdirks  = 0;
    double bsenergy = 0;
    //double bscossun = 0;

    
    int ndata, isegm = 1;
    bool bonsai_loaded = false;

    
    kzget1_("LOWBS3", isegm, ndata, zbsget.idata, 6);
    if (zbsget.rdata[29] > 0.0001) {
        if (verbose) 
            cout << "Loading Bonsai3 fit information" << endl;

        bonsai_loaded = true;

        bonsai_vertex[0] = zbsget.rdata[0];
        bonsai_vertex[1] = zbsget.rdata[1];
        bonsai_vertex[2] = zbsget.rdata[2];
        bonsai_dir[0]    = zbsget.rdata[10];
        bonsai_dir[1]    = zbsget.rdata[11];
        bonsai_dir[2]    = zbsget.rdata[12];
        //bsgood1          = zbsget.rdata[13];
        bsgoodness       = zbsget.rdata[14]; 
        //bsgood3          = zbsget.rdata[15];
        bsdirks          = zbsget.rdata[16];
        bsenergy         = zbsget.rdata[29];
        bsn50            = zbsget.idata[30];
        //bscossun         = zbsget.rdata[31];

        if (verbose) 
            printf("Bonsai fit %fMeV, vertex (%f, %f, %f)\n",bsenergy,bonsai_vertex[0],bonsai_vertex[1],bonsai_vertex[2]);
    }

    if (!bonsai_loaded) {
        kzget1_("LOWBS", isegm, ndata, zbsget.idata, 6);
        if (zbsget.rdata[9] > 0.0001) {
            if (verbose) 
                cout << "Loading T2K Bonsai fit information" << endl;
            
            bonsai_loaded = true;
            
            bonsai_vertex[0] = zbsget.rdata[0];
            bonsai_vertex[1] = zbsget.rdata[1];
            bonsai_vertex[2] = zbsget.rdata[2];
            bonsai_dir[0]    = zbsget.rdata[3];
            bonsai_dir[1]    = zbsget.rdata[4];
            bonsai_dir[2]    = zbsget.rdata[5];
            bsgoodness       = zbsget.rdata[8]; 
            bsdirks          = zbsget.rdata[10];
            bsenergy         = zbsget.rdata[9];
            bsn50            = zbsget.idata[18];
            //bscossun         = zbsget.rdata[31];
            
            if (verbose) 
                printf("Bonsai fit %fMeV, vertex (%f, %f, %f)\n",bsenergy,bonsai_vertex[0],bonsai_vertex[1],bonsai_vertex[2]);
        }

    }
    
    if (!bonsai_loaded) {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "!!! No Bonasi information !!!!" << endl;
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
       //bonsai_fit_(&t0, tisend, qisend, cisend, &N10send, &tbsenergy, &tbsvx, &tbsvy, &tbsvz, &tbsgood);
    }
    

    //lowbs3get_();

    

  
    // Reconstruction quality
    double bsovaq = (bsgoodness*bsgoodness)-(bsdirks*bsdirks);

    // Call fiducial variables
    int idod=1; //from id wall
    double poswal[3]={0,0,0};
    double effwall = effwallf( idod, bonsai_vertex, bonsai_dir, poswal);


    ncg.nrun   = skhead_.nrunsk;
    ncg.nsub   = skhead_.nsubsk;
    ncg.nev    = skhead_.nevsk;

    ncg.potot = skq_.qismsk; //TQI->qismsk, total ID p.e.
    ncg.nhit  = skq_.nqisk; // Total ID hits
    ncg.n50   = bsn50;      // N50 from Bonasi fit

    for (int i=0; i<3; i++) {
        ncg.pos[i] = bonsai_vertex[i];
        ncg.bdir[i] = bonsai_dir[i];
    }
    ncg.erec     = bsenergy;
    ncg.wall     = wallsk(bonsai_vertex);
    ncg.effwall  = effwall;
    ncg.ovaq     = bsovaq;
    CherenkovAngle(bonsai_vertex, true);
    CherenkovAngle(bonsai_vertex, false);
    ncg.goodness = bsgoodness;  

    //ncg.n50      = ?;  // TK
    //ncg.cossun   = ?;  // TK
    //ncg.patlik   = ?;  // TK
    //ncg.lsd      = ?;  // TK
    //ncg.forwall  = ?;  // TK
    
    

    //
    // Load the MC banks
    // 
    nerdnebk_(); //read neut bank, output idata, rdata
    vcrdvccm_(); //for get input kinematic
        
    // 
    // Basic NEUT Information
    //
    for (int j=0; j<3; j++) ncg.posv[j] = vcvrtx_.pvtxvc[0][j];
    ncg.wallv  = wallsk(ncg.posv);

    //
    // Initial interactions
    //
    ncg.mode   = nework_.modene;
    ncg.numnu  = nework_.numne;
    for (int i = 0; i < ncg.numnu; i++) {
        ncg.ipnu[i] = nework_.ipne[i];
        MomAndDir( nework_.pne[i], ncg.pnu[i], ncg.dirnu[i] );
        //cout << "ipnu[" << i << "]=" << ncg.ipnu[i] << endl;
    }
        
    //
    // VECT bank - particles leaving the nucleus
    //
    ncg.npar = vcwork_.nvc;
    for (int i = 0; i < ncg.npar; i++) {
        pd2gt_(vcwork_.ipvc[i], ncg.ipv[i]);
        ncg.icrnv[i] = vcwork_.icrnvc[i];
        MomAndDir( vcwork_.pvc[i], ncg.pmomv[i], ncg.dirv[i] );
    }

    //
    // VECT2 secondarys in SKDetSim
    //
    GetVect2();


    //
    // Custom truth information
    // 
    ncg.IsPionAbs;     // Flag of pion absorption


    if (verbose) {
        printf("Neut Mode %d\n",nework_.modene);
        printf("neut vertex is (%f, %f, %f).\n", ncg.posv[0], ncg.posv[1], ncg.posv[2]);
    }

        
    //
    // Count up primary and secondary gammas
    //

    CountTrueGammas();

    //                                      \
    // Load secondary particle information
    //

    // Not now - this information not in Ueno's skdetsim files
    // Perhaps a newer version of skdetsim is required
    //GetScndPrt();


    //
    // Required for T2KReWeight
    //

    ncg.Neutmode = nework_.modene;
    ncg.Npne     = nework_.numne;
    for (int i = 0; i < ncg.Npne; i++) {
        ncg.Ipne[i]   = nework_.ipne[i];
        ncg.Abspne[i] = ncg.pnu[i];
        for (int j=0; j<3; j++) ncg.Pvecne[i][j] = nework_.pne[i][j];
    }

    ncg.Npvc = vcwork_.nvc;
    for (int i = 0; i < ncg.Npvc; i++) {
        ncg.Ipvc[i] = vcwork_.ipvc[i];
        ncg.Ichvc[i] = vcwork_.icrnvc[i];
        ncg.Iorgvc[i] = vcwork_.iorgvc[i];
        ncg.Iflvc[i] = vcwork_.iflgvc[i];
        ncg.Abspvc[i] = ncg.pmomv[i];
        for (int j=0; j<3; j++) ncg.Pvc[i][j] = vcwork_.pvc[i][j];
    }

    nerdcrsbk_();
    ncg.Crsx   = neutcrscom_.crsx;
    ncg.Crsy   = neutcrscom_.crsy;
    ncg.Crsz   = neutcrscom_.crsz;
    ncg.Crsphi = neutcrscom_.crsphi;
        
    nerdnetarg_();
    ncg.Numbndn = neuttarget_.numbndn;
    ncg.Numbndp = neuttarget_.numbndp;
    ncg.Numfrep = neuttarget_.numfrep;
    ncg.Numatom = neuttarget_.numatom;
    ncg.Ibound  = posinnuc_.ibound;

    ncg.Fsiprob = 1;
    ierr = 0;
    kzbloc_("fsihistvert", ierr);
    if (ierr != 0) {
        kzbloc_("fsihistpart", ierr);
        if (ierr != 0) {
            nerdfsibk_();

            ncg.Fsiprob = fsihist_.fsiprob;
            if (verbose) 
                cout  << "Fsiprob = " << fsihist_.fsiprob << endl;
            for (int i=0; i<ncg.Nvert; i++) {
                for (int j=0; j<3; j++) ncg.Posvert[i][j] = fsihist_.posvert[i][j];
                ncg.Iflgvert[i] = fsihist_.iflgvert[i];
            }
            ncg.Nvcvert = fsihist_.nvcvert;
            for (int i=0; i<fsihist_.nvcvert; i++) {
                for (int j=0; j<3; j++) ncg.Dirvert[i][j] = fsihist_.dirvert[i][j];
                ncg.Abspvert[i] = fsihist_.abspvert[i];
                ncg.Abstpvert[i] = fsihist_.abstpvert[i];
                ncg.Ipvert[i] = fsihist_.ipvert[i];
                ncg.Iverti[i] = fsihist_.iverti[i];
                ncg.Ivertf[i] = fsihist_.ivertf[i];
            }
            ncg.Nvert = fsihist_.nvert;
        }
    }



    kzget1_("T2KLE", isegm, ndata, zbsget.idata, 5);


    ncg.dt0 =     zbsget.rdata[0];
    ncg.dt0vtx =  zbsget.rdata[1];
    ncg.dt0type =   zbsget.idata[2];
    ncg.n30max =    zbsget.idata[3];
    ncg.n30time = zbsget.rdata[4];

    // Fix time units
    ncg.dt0     *= 1e-3;
    ncg.dt0vtx  *= 1e-3;
    ncg.n30time *= 1e-3;


    return true;
}

bool NtupleMaker::ReadDataEvent()
{
    static int iread=0;

    int ntotal=datatree->GetEntries();
    if (iread >= ntotal) return false;

    datatree->GetEntry(iread);
    iread++;
      

    static int nshe = 0;
    static int nother =0;

    /*
    // Check trigger information
    if (HEAD->idtgsk&0x10000000){
        nshe++;
    }
    else{
        nother++; //this is events triggered by HE but not SHE. Typically these do not have AFT trigger attached.
        cout << "Non-SHE trigger: " << HEAD->idtgsk << "; nother = " << nother <<  endl;
        if (HEAD->idtgsk != 7) cout << "Non-HE trigger: " << HEAD->idtgsk << endl; 
    }
    
    cout << "IDTGSK: " << HEAD->idtgsk << endl;
    if (HEAD->idtgsk & 0)  cout << "LE trigger" << endl;
    if (HEAD->idtgsk & 1)  cout << "HE trigger" << endl;
    if (HEAD->idtgsk & 2)  cout << "SLE trigger" << endl;
    if (HEAD->idtgsk & 3)  cout << "OD trigger" << endl;
    if (HEAD->idtgsk & 31) cout << "T2K trigger" << endl;
    */
  
    // Get Bonsai information. Try from file, if not, run Bonsai
  
    double bonsai_vertex[3];
    double bonsai_dir[3];
    int    bsn50    = 0;
    //double bsgood1  = 0;
    double bsgoodness  = 0;
    //double bsgood3  = 0;
    double bsdirks  = 0;
    double bsenergy = 0;
    //double bscossun = 0;

    
    int ndata, isegm = 1;
    bool bonsai_loaded = false;
  
  
    if (LOWE->bseffhit[11] > 0.0001) {
        if (verbose) 
            cout << "Loading Bonsai3 fit information" << endl;
    
        bonsai_loaded = true;
    
        bonsai_vertex[0] = LOWE->bsvertex[0];
        bonsai_vertex[1] = LOWE->bsvertex[1];
        bonsai_vertex[2] = LOWE->bsvertex[2];
        bonsai_dir[0]    = LOWE->bsdir[0];
        bonsai_dir[1]    = LOWE->bsdir[1];
        bonsai_dir[2]    = LOWE->bsdir[2];
        //bsgood1          = LOWE->bsgood[0];
        bsgoodness       = LOWE->bsgood[1]; 
        //bsgood3          = LOWE->bsgood[2];
        bsdirks          = LOWE->bsdirks;
        bsenergy         = LOWE->bsenergy;
        bsn50            = LOWE->bsn50;
        //bscossun         = LOWE->bscossun;
    
        if (verbose) 
            printf("Bonsai fit %fMeV, vertex (%f, %f, %f)\n",bsenergy,bonsai_vertex[0],bonsai_vertex[1],bonsai_vertex[2]);
    }

    if (!bonsai_loaded) {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "!!! No Bonasi information !!!!" << endl;
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        //bonsai_fit_(&t0, tisend, qisend, cisend, &N10send, &tbsenergy, &tbsvx, &tbsvy, &tbsvz, &tbsgood);
    }

  
    // Reconstruction quality
    double bsovaq = (bsgoodness*bsgoodness)-(bsdirks*bsdirks);
  
    // Call fiducial variables
    int idod=1; //from id wall
    double poswal[3]={0,0,0};
    double effwall = effwallf( idod, bonsai_vertex, bonsai_dir, poswal);
  
  
    ncg.nrun   = HEAD->nrunsk;
    ncg.nsub   = HEAD->nsubsk;
    ncg.nev    = HEAD->nevsk;

    ncg.mrrun = FindMRRun(HEAD->nrunsk);
    for (int i=0; i<3; i++) ncg.date[i] = HEAD->ndaysk[i];
    for (int i=0; i<4; i++) ncg.time[i] = HEAD->ntimsk[i];
    //ncg.elpsday = elapseday_(HEAD->ndaysk, HEAD->ntimsk);
  
    //ncg.potot = skq_.qismsk; //TQI->qismsk, total ID p.e.
    //ncg.nhit  = skq_.nqisk; // Total ID hits
    //not fill these two variables (potot, nhit) of data
    ncg.potot = 0;
    ncg.nhit = TQREAL->nhits;

    ncg.n50   = bsn50;      // N50 from Bonasi fit
  
  
    for (int i=0; i<3; i++) {
        ncg.pos[i] = bonsai_vertex[i];
        ncg.bdir[i] = bonsai_dir[i];
    }
    ncg.erec     = bsenergy;
    ncg.wall     = wallsk(bonsai_vertex);
    ncg.effwall  = effwall;
    ncg.ovaq     = bsovaq;
    CherenkovAngle(bonsai_vertex, true);
    CherenkovAngle(bonsai_vertex, false);
    ncg.goodness = bsgoodness;  

    
    ncg.dt0 = *reinterpret_cast<float*>(&LOWE->linfo[70]);
    ncg.dt0vtx = *reinterpret_cast<float*>(&LOWE->linfo[71]);
    ncg.dt0type = LOWE->linfo[72];
    ncg.n30max = LOWE->linfo[73];
    ncg.n30time = *reinterpret_cast<float*>(&LOWE->linfo[74]);

    // Fix time units
    ncg.dt0     *= 1e-3;
    ncg.dt0vtx  *= 1e-3;
    ncg.n30time *= 1e-3;
  
    return true;
}

void NtupleMaker::SaveToTree()
{
    theOTree->Fill();
}


void NtupleMaker::MomAndDir( float* pin, Float_t &pout, Float_t *dirout ) 
{
    double psq = 0;
    for (int j = 0; j < 3; j++)
        psq += pin[j]*pin[j];
    pout = sqrt(psq);
    
    for (int j=0; j<3; j++) 
        dirout[j] = pin[j] / pout;
}


void NtupleMaker::CountTrueGammas()
{
    // Find primary gammas
    Int_t ng1count   = 0;
    Float_t toteg1 = 0.0;
    
    for (int ivc=0; ivc < vcwork_.nvc; ivc++){
        //printf("%d %d %d %d\n", ivc, vcwork_.ipvc[ivc], vcwork_.iflgvc[ivc], vcwork_.icrnvc[ivc]);
        
        int particle_code = vcwork_.ipvc[ivc];
        int chase_flag    = vcwork_.icrnvc[ivc];
        
        //retrieve primary gamma information here
        if (particle_code == 22 && chase_flag){
            ng1count += 1;
            double eg1 = 0;
            for (int i=0; i < 3; i++) eg1 += TMath::Power(vcwork_.pvc[ivc][i],2);
            //printf("primary gamma: %d-th %5.2fMeV.\n", ng1count, TMath::Sqrt(eg1));
            toteg1 += TMath::Sqrt(eg1);
        }
    }
    if (verbose)
        printf("ng1 is %d\n", ng1count);
    
    // Find secondary gammas
    int ndata, isegm = 0, ng2count=0;
    kzget1_("scndgam", isegm, ndata, zbsget.idata, 7);
    if (ndata>0){
        ng2count = zbsget.idata[0];
    }
    else {
        cout << "Error retreive secondary gamma information" << endl;
        ng2count =-1;
    }
    Double_t egam=0.0, toteg2=0.0, pinc=0.0;
    for (Int_t ig2=0;ig2<ng2count;ig2++){
        kzget1_("scndgam", ig2, ndata, zbsget.idata, 7);
        pinc = zbsget.rdata[3];   //momentum of parent particle (MeV/c)
        egam = zbsget.rdata[4];   //secondary gammary energy (MeV)
        toteg2 += egam;
    }
    if (verbose)
        printf("ng2 is %d, toteg2 is %5.2fMeV\n", ng2count, toteg2);
    
    
    ncg.ng1    = ng1count;
    ncg.toteg1 = toteg1;
    ncg.ng2    = ng2count;
    ncg.toteg2 = toteg2;


    isegm = 0;
    kzget1_("chorg", isegm, ndata, zbsget.idata, 5);
    
    ncg.num_primary_gammas = zbsget.idata[1];
    ncg.num_neutron_gammas = zbsget.idata[11];
    ncg.num_proton_gammas  = zbsget.idata[18];

}


void NtupleMaker::GetScndPrt()
{
    int isegment = 0; // Get just the first segment to get Nvect2
    int ndata;        // Data length
    kzget1_("SNCDPRT", isegment, ndata, zbsget.idata, 8);
    ncg.nscndprt = zbsget.idata[0];
    cout << "nscndprt=" << ncg.nscndprt << ", ndata=" << ndata << endl;

    if ( ncg.nscndprt == 0 )  return;
    if ( ncg.nscndprt > MAXSCNDPRT ) ncg.nscndprt = MAXSCNDPRT;
    
    for (int i = 0 ; i < 28; i++ )
        cout << "idata[" << i << "]" << zbsget.idata[i] << "   "
             << "rdata[" << i << "]" << zbsget.rdata[i] 
             << endl;

    for (int i = 0; i < ncg.nscndprt; i++) {
        kzget1_("SNCDPRT", i, ndata, zbsget.idata, 8);

        //cout << "ndata[" << i << "]=" << ndata << endl;

        ncg.itrkscnd[i] = zbsget.idata[0];
        ncg.iprtscnd[i] = zbsget.idata[1];
        for (int j = 0 ; j < 3; j++) {
            ncg.vtxscnd[i][j] = zbsget.rdata[2+j];
            ncg.pscnd[i][j]   = zbsget.rdata[5+j];
        }
        ncg.tscnd[i]    = zbsget.rdata[8];
        ncg.iprntprt[i] = zbsget.idata[9];
        ncg.lmecscnd[i] = zbsget.idata[10];
        ncg.iprnttrk[i] = zbsget.idata[11];
        ncg.iorgprt[i]  = zbsget.idata[12];
        //iflgscnd[i] = 0; 
        //for (int j=0; j<3; j++) pprnt[i][j] = 0;     
    }
}


void NtupleMaker::GetVect2()
{

    int isegment = 0; // Get just the first segment to get Nvect2
    int ndata;        // Data length
    kzget1_("CONVVECT", isegment, ndata, zbsget.idata, 8);
    ncg.npar2 = zbsget.idata[0];

    if ( ncg.npar2 == 0 )
        return;

    for (int i = 0; i < ncg.npar2; i++) {
        float ptmp[3];

        kzget1_("CONVVECT", i, ndata, zbsget.idata, 8);

        pd2gt_(zbsget.idata[1], ncg.ipv2[i]);

        ncg.posv2[i][0] = zbsget.rdata[2];
        ncg.posv2[i][1] = zbsget.rdata[3];
        ncg.posv2[i][2] = zbsget.rdata[4];
        ncg.wallv2[i]   = wallsk(ncg.posv2[i]);

        ptmp[0] = zbsget.rdata[5];
        ptmp[1] = zbsget.rdata[6];
        ptmp[2] = zbsget.rdata[7];

        MomAndDir( ptmp, ncg.pmomv2[i], ncg.dirv2[i] );
    }

}

void NtupleMaker::CherenkovAngle(double *pvx, bool limithits)
{

  Int_t goodcount=0, ipmt; 
  int icabbit=0xffff;

  //data
  if (!isMC){
      for (int i=0;i<TQREAL->nhits;i++){
          int realcable = TQREAL->cables[i] & icabbit;
          int icflag = TQREAL->cables[i]>>16;
          if (realcable<= MAXPM && !checkMiss(realcable)){
              if (icflag &1){
                  goodcount+=1;
              }
          }
      }
  }else{
      for (int i=0;i<sktqz_.nqiskz;i++){
	if (sktqz_.ihtiflz[i]&0x02 && sktqz_.icabiz[i] <= MAXPM && !combad_.ibad[sktqz_.icabiz[i]-1] && !checkMiss(sktqz_.icabiz[i]) && sktqz_.ihtiflz[i]&0x01){ //check if hits are in gate and not on bad/missing channels and hits that are main event
	    goodcount+=1;
	}
      }
    }
    
    const Int_t MAXN10 = 200;
   
    const int ALLHITS = goodcount;
    const Float_t C_WATER = 21.5833;

    Int_t   cabiz[ALLHITS], cabiz2[ALLHITS];
    Float_t tiskz[ALLHITS], tiskz2[ALLHITS];
    Float_t qiskz[ALLHITS], qiskz2[ALLHITS];
    Int_t   index[ALLHITS], nindex[MAXN10];
    Double_t dhit[3], dtmp;
    Float_t hitv_x[ALLHITS];
    Float_t hitv_y[ALLHITS];
    Float_t hitv_z[ALLHITS];
    Double_t rsqrd, opang, rnosq;
    Int_t icount=0;

    // Copy the TQ arrays
    if (isMC){
      for (int i=0; i<sktqz_.nqiskz; i++) 
	{
	  if (sktqz_.ihtiflz[i]&0x02 && sktqz_.icabiz[i] <= MAXPM && !combad_.ibad[sktqz_.icabiz[i]-1] && !checkMiss(sktqz_.icabiz[i]) && sktqz_.ihtiflz[i]&0x01) //check if hits are in gate and not on bad/missing channels and hits that are main event
	    {
	      cabiz2[icount] = sktqz_.icabiz[i];
	      tiskz2[icount] = sktqz_.tiskz[i];
	      qiskz2[icount] = sktqz_.qiskz[i];
	      icount+=1;
	    }
	}
    }else{    //Data
        cout << "About to load up TQREAL with " << TQREAL->nhits << endl;
        for (int i=0; i<TQREAL->nhits; i++){
            int realcable = TQREAL->cables[i] & icabbit;
            int icflag = TQREAL->cables[i]>>16;
	
            //if (TQREAL->cables[i] <= MAXPM && !checkMiss(TQREAL->cables[i])){ 
            if (realcable <= MAXPM && !checkMiss(realcable)){
                if (icflag&1){
                    cout<< "realcable "<<realcable<<" i "<<i <<std::endl;
                    cabiz2[icount] = realcable;
                    tiskz2[icount] = TQREAL->T[i];
                    qiskz2[icount] = TQREAL->Q[i];
                    icount+=1;
                }
            }
        }
    }
    
    //cout << "TOF correction..." << endl;

    // TOF subtraction for all hits in copied arrays
    for (int i=0; i<ALLHITS; i++) {
        //if (i % 100 == 0)	cout << "position : " << cabiz2[i]-1<<  geopmt_.xyzpm[cabiz2[i]-1][0]<<endl;
        Float_t tof;
        tof = TMath::Sqrt((pvx[0] - geopmt_.xyzpm[cabiz2[i]-1][0]) * (pvx[0] - geopmt_.xyzpm[cabiz2[i]-1][0])
                          +(pvx[1] - geopmt_.xyzpm[cabiz2[i]-1][1]) * (pvx[1] - geopmt_.xyzpm[cabiz2[i]-1][1])
                          +(pvx[2] - geopmt_.xyzpm[cabiz2[i]-1][2]) * (pvx[2] - geopmt_.xyzpm[cabiz2[i]-1][2])) / C_WATER;
        tiskz2[i] -= tof;
    }
 
  
    // Sort hits by TOF-corrected time
    TMath::Sort(ALLHITS, tiskz2, index, kFALSE); // In increasing order
    for (int i=0; i<ALLHITS; i++){
        cabiz[i] = cabiz2[ index[i] ];
        tiskz[i] = tiskz2[ index[i] ];
        qiskz[i] = qiskz2[ index[i] ];  
    }

    int N15      = 0;
    int N15index = 0;
    
    if (limithits)   {
        N15 = 183;
        MinimumWidthWindow(tiskz, ALLHITS, 15., N15, N15index);
    }
    else {
        MaxHitsInWindow(tiskz, ALLHITS, 15., N15, N15index);
    }

    int maxncmb = N15*N15*N15 / 6;
    vector<double> abc2(N15*N15, 0.0); 
    vector<double> maxcmb(maxncmb, 0.0);



    //making unit direction vector form vertex to selected tubes
    if (verbose)
        printf("N15 is %d at index %d.\n", N15, N15index);

    //zero histogram
    hcheren->Reset();

    for (int ii=N15index; ii < N15index+N15; ii++){
        for (int jj=0; jj<3; jj++){
            dhit[jj] = geopmt_.xyzpm[cabiz[ii]-1][jj]- pvx[jj];
        }
        dtmp= 1.0/TMath::Sqrt(dhit[0]*dhit[0]+dhit[1]*dhit[1]+dhit[2]*dhit[2]);
        int intmp= ii-N15index;
        hitv_x[intmp]= dhit[0]*dtmp;
        hitv_y[intmp]= dhit[1]*dtmp;
        hitv_z[intmp]= dhit[2]*dtmp;
    }


    int tmpindex_a=0, tmpindex_b=0, tmpindex_c=0;
    //Calculate lengths of difference vectors between directions
    for (int aa = 0; aa < N15-1; aa++) {
        for (int bb=aa+1; bb<N15; bb++) {
            tmpindex_a=aa*N15+bb;
            abc2[tmpindex_a] = (hitv_x[aa]-hitv_x[bb])*(hitv_x[aa]-hitv_x[bb])+(hitv_y[aa]-hitv_y[bb])*(hitv_y[aa]-hitv_y[bb])+(hitv_z[aa]-hitv_z[bb])*(hitv_z[aa]-hitv_z[bb]);
        }
    }
  
    //Do all direction triangles and fill histogram
    for (int aa=0;aa<N15-2;aa++){
        for (int bb=aa+1;bb<N15-1;bb++){
            tmpindex_a=aa*N15+bb;
            //dtmp= abc2[aa][bb];
            dtmp= abc2[tmpindex_a];
            for (int cc=bb+1;cc<N15;cc++){
                tmpindex_b=aa*N15+cc;
                tmpindex_c=bb*N15+cc;
                rsqrd = lfrsqrt(dtmp, abc2[tmpindex_b], abc2[tmpindex_c]);
                rnosq = TMath::Sqrt(rsqrd);
                opang = TMath::ASin(rnosq)*180.0/TMath::Pi(); 
                // if rnosq>1-->return pi/2
                hcheren->Fill(opang);
            }
        }
    }
    char xtitle[64];
  
 

    //Finding peak of max summation of neighboring 7 bins
    TString che_angle;
  
    Double_t unpack[nstep], b2deg=0.0, lsum=0.0;
    int nwindow=7, midpoint=3, look=100;
    int ilowbnd=41, ihibnd=67;
    int nrange, llook, ij=0, locale=0;
    Double_t lheight=0, peakangle=0.0;

    nrange = nstep-nwindow+1;
    b2deg  = 90.0/100.0;
  
    ncg.anglebinnum= nstep;
    for(int hh=0;hh<nstep;hh++){
        unpack[hh]=hcheren->GetBinContent(hh+1);
	ncg.plotcontent[hh] = hcheren->GetBinContent(hh);
    }
    for(int ii=0;ii<nrange;ii++){
        lsum=0.0;
        for (int jj=0;jj<nwindow;jj++){
            ij=ii+jj;
            lsum+=unpack[ij];
        }
        if (lheight<lsum){
            lheight=lsum;
            locale=ii+1+midpoint;}
    }
    peakangle=locale*b2deg;
    if (verbose)
        printf("Cherenkov angle is %f\n",  peakangle);

    //hcheren->Draw();
  
    double linear_like = GetLinearLikelihood(hcheren);
    if (verbose)
        printf("likelihood value is %f.\n", linear_like);

    //sprintf(xtitle,"#%d Cherenkov angle  (%7.2fns) likehood %f", nrow, tiskz[i], likev);
    //hcheren->GetXaxis()->SetTitle(xtitle);

    if (limithits) {
        ncg.angle =  peakangle;
        ncg.angle_likelihood = linear_like;
    }
    else {
        ncg.angle_15ns = peakangle;
        ncg.angle_likelihood_15ns = linear_like;
    }
  
    
    //delete hcheren;
    //else         cout << "Not deleting non-existant histogram" << endl;
    //delete p;
}



double NtupleMaker::GetLinearLikelihood(TH1D *hcheren)
{
    float pli0=0.0, pli1=0.0;
    TF1 *pdfFcn = new TF1("typpdf", typPdf, 10, 90, 2);
    //TF1* pdfFcn = new TF1("typpdf", "pol1", 10, 90);
    pdfFcn->SetParameters(-0.00277, 0.000277);
    
    double nentry = hcheren->GetEntries();
    TH1D *hnorche= (TH1D*)hcheren->Clone();

    hnorche->Scale(1.0/nentry);

    TVirtualFitter::SetDefaultFitter("Minuit2");
    TFitResultPtr r=hnorche->Fit(pdfFcn, "RWLSQ");
    
    like_all++;
    if (!r->IsValid())
        like_fail++;
  
    pli0 = pdfFcn->GetParameter("p0");
    pli1 = pdfFcn->GetParameter("p1");
    
    Double_t  logm, yi, caltmp, sumlikeli=0.0, binlike=0.0;
    int nvpar, nparx;
    int numbin = hnorche->GetNbinsX();
    int fitlow = hnorche->FindBin(10.0); 
    Double_t hwidth = hnorche->GetBinWidth(1);
    for (int jj=fitlow;jj<numbin;jj++){
      //calculate likelihood
      yi=hnorche->GetBinContent(jj);
      caltmp=(pli1*jj*hwidth)+pli0;
      if (caltmp>0){
	binlike=yi*TMath::Log10(caltmp);}
      else {binlike=0.0;}
      sumlikeli+=binlike;
    }

    logm= sumlikeli;
    delete pdfFcn;
    return logm; //return log-likelihood value of linear-like
    
}

Double_t NtupleMaker::lfrsqrt(Double_t a2, Double_t b2, Double_t c2)
{
  Double_t rsquare=0.0;
  Double_t tmpr2=0.0;

  //++allCount;

  tmpr2= a2*(2.*b2-a2) + b2*(2.*c2-b2) + c2*(2.*a2-c2);
  if (tmpr2>0){
    rsquare= a2*b2*c2/tmpr2;
  }else {
      //++negativeCount;
      //printf("lfrsqrd: Problem: %f, %f, %f, %f.\n", tmpr2, a2, b2, c2);
    return 2;
  }
  
  return rsquare;
}

int NtupleMaker::getNhits(Float_t *v, int start_index, Float_t width, int nhits)
// Get nhits from v[0] in time window = width
// v[] - hit timing, sorted in time
// width - time window width
// start_index - index of start pmt hit
// nhits - total number  of v[] hits
{
    int i = start_index;
    while (1) {
        i++;
        if((i > nhits-1 ) || (TMath::Abs((v[i]-v[start_index])) > width)) break;
    }
    return TMath::Abs(i - start_index);
}


void NtupleMaker::MaxHitsInWindow(Float_t *t, int ALLHITS, float width, int &maxnhits, int &maxindex)
{
    maxnhits = 0;
    maxindex = 0;

    //Finding max N15 and its index, limiting potential number of hits
    for (int in = 0; in < ALLHITS; in++) {

        // Limit to -500 to 1500 ns time window
        //if ( t[in] < tchelow)  continue;
        //if ( t[in] > tchehigh) continue;       
    
        // Calculate hits in 15 ns window 
        int N = getNhits(t, in, width, ALLHITS);
        if ( N > maxnhits) {
            maxnhits = N;
            maxindex = in;
        }
    }//ALLHITS

    if (verbose)
        cout << "MaxHitsInWindow, maxnhits=" << maxnhits << ", maxindex=" << maxindex << endl;
}


void NtupleMaker::MinimumWidthWindow(Float_t *t, int ALLHITS, float width, int &maxnhits, int &maxindex)
{
    // ----------------------------------------------------------------------
    // ---- get time ordered tof subtracted (vertex)
    // ----------------------------------------------------------------------
    
    // v is already sorted

    
    // ----------------------------------------------------------------------
    // ---- scan for the requested number of hits
    // ----------------------------------------------------------------------
    
    double dt   = 100000.;
    for (int i = 0; i < ALLHITS-maxnhits; i++) {
      //if ( t[i] < tchelow)  continue;
      //if ( t[i] > tchehigh) continue;       

        if (t[i+maxnhits] - t[i] < dt) {
            dt = t[i+maxnhits] - t[i];
            maxindex = i;
        }
    }

      
    // ----------------------------------------------------------------------
    // ---- if dt too big, find maximal number of hits fitting into twindow
    // ----------------------------------------------------------------------

    if (dt > width) {
        if (verbose)
            cout << "dt too wide: ";
        MaxHitsInWindow(t, ALLHITS, width, maxnhits, maxindex);
    }
    else {
        if (verbose)
            cout << "MinimumWidthWindow, maxnhits=" << maxnhits << ", maxindex=" << maxindex << endl;
    }
      
// ----------------------------------------------------------------------
}

Bool_t NtupleMaker::checkMiss (const Int_t cab)
{
  for (Int_t i=0; i<NMIS; i++) {
    if ( MISCH[i] == cab ) return kTRUE;
  }
  return kFALSE;
}


int NtupleMaker::FindMRRun(int skrun)
{
    for (int i = 0; i < 100; i++) {
        if (skrun >= mrfirst[i] && skrun <= mrlast[i])
            return i;
    }
    return 0;
}

