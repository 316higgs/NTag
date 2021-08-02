#include "T2KLowE.h"
#include "TROOT.h"
#include "TTree.h"

T2KLowE::T2KLowE() { 
    Is_mc = true; 
    Clear(); 
};

void T2KLowE::Clear() 
{
    //Is_mc = 0; // Never clear Is_mc, should be consistent

    // Data + MC Variables
    nrun = 0;
    nsub = 0;
    nev = 0;
    
    potot = 0;
    nhit = 0;
    n50 = 0;

    dt0 = 0;
    dt0vtx = 0;
    dt0type = 0;
    n30max = 0;
    n30time = 0;
    for (int i=0; i<3; i++) pos[i] = 0;
    for (int i=0; i<3; i++) bdir[i] = 0;
    erec = 0;
    wall = 0;
    effwall = 0;
    ovaq = 0;
    angle = 0;
    angle_likelihood = 0;
    angle_15ns = 0;
    angle_likelihood_15ns = 0;
    anglebinnum=0;
    for (int i=0;i<MAXBINNUM; i++) plotcontent[i] = 0.0;

    goodness = 0;

    //cossun = 0;
    //patlik = 0;
    //lsd = 0;
    //forwall = 0;

    if (!Is_mc) {
        mrrun = 0;
        for (int i=0; i<3; i++) date[i] = 0;
        for (int i=0; i<4; i++) time[i] = 0;
        elpsday = 0;
    }


    if (Is_mc) {
        // MC-only Variables
        mode = 0;
        wallv = 0;
        for (int i=0; i<3; i++) posv[i] = 0;
    
        npar = 0;
        for (int i=0; i<100; i++) {
            ipv[i] = 0;
            icrnv[i] = 0;
            for (int j=0; j<3; j++) dirv[i][j] = 0;
            pmomv[i] = 0;
        }

        npar2 = 0;
        for (int i=0; i<MAXVC; i++) {
            wallv2[i] = 0;
            ipv2[i] = 0;
            for (int j=0; j<3; j++) {
                posv2[i][j] = 0;
                dirv2[i][j] = 0;
            }
            pmomv2[i] = 0;
        }


        numnu = 0;
        for (int i=0; i<MAXVC; i++) {
            ipnu[i] = 0;
            pnu[i] = 0;
            for (int j=0; j<3; j++) dirnu[i][j] = 0;
        }

        ng1 = 0;
        ng2 = 0;
        toteg1 = 0;
        toteg2 = 0;

        num_primary_gammas = 0;
        num_neutron_gammas = 0;
        num_proton_gammas = 0;

        IsPionAbs = 0;

        // Required for T2KReWeight
        nscndprt = 0;
        for (int i = 0; i < MAXSCNDPRT; i++) {
            itrkscnd[i] = 0; 
            for (int j=0; j<3; j++) vtxscnd[i][j] = 0; 
            for (int j=0; j<3; j++) pscnd[i][j]   = 0; 
            iprtscnd[i] = 0; 
            tscnd[i]    = 0; 
            iprntprt[i] = 0; 
            lmecscnd[i] = 0; 
            iprnttrk[i] = 0; 
            iorgprt[i]  = 0; 
            iprntidx[i] = 0; 
            nchilds[i]  = 0;
            ichildidx[i]= 0;
            for (int j=0; j<3; j++) pprnt[i][j]     = 0;     
            for (int j=0; j<3; j++) pprntinit[i][j] = 0;     
            for (int j=0; j<3; j++) vtxprnt[i][j]   = 0;     
            iflgscnd[i] = 0; 
        }    
        
        npvcscnd = 0;
        for (int i=0; i<MAXVC; i++){
            nchildsvc[i]   = 0;
            ichildidxvc[i] = 0;
        }

        Neutmode = 0;
        Npne = 0;
        for (int i=0; i<MAXVC; i++) {
            Ipne[i] = 0;
            Abspne[i] = 0;
            for (int j=0; j<3; j++) Pvecne[i][j] = 0;
        }
        Npvc = 0;
        for (int i=0; i<MAXVC; i++) {
            Ipvc[i] = 0;
            Ichvc[i] = 0;
            Iorgvc[i] = 0;
            Iflvc[i] = 0;
            Abspvc[i] = 0;
            for (int j=0; j<3; j++) Pvc[i][j] = 0;
        }
        Crsx = 0;
        Crsy = 0;
        Crsz = 0;
        Crsphi = 0;
        Numbndn = 0;
        Numbndp = 0;
        Numfrep = 0;
        Numatom = 0;
        Ibound = 0;
        Nvert = 0;
        for (int i=0; i<MAXVERT; i++) {
            for (int j=0; j<3; j++) Posvert[i][j] = 0;
            Iflgvert[i] = 0;
        }
        Nvcvert = 0;
        for (int i=0; i<MAXVCVERT; i++) {
            for (int j=0; j<3; j++) Dirvert[i][j] = 0;
            Abspvert[i] = 0;
            Abstpvert[i] = 0;
            Ipvert[i] = 0;
            Iverti[i] = 0;
            Ivertf[i] = 0;
        }
        Fsiprob = 0;


        // "Reco" variables for T2K SK__h1 interface
        nring = 1;
        nhitac = 0;
        evis = 0;
        ip[0] = 0;
        dir[0][0] = 0;
        dir[0][1] = 0;
        dir[0][2] = 0;
        amom[0] = 0;
        amome[0] = 0;
        amomm[0] = 0;
        for (int i = 0; i < 2; i++) {
            pi0like[i] = 0;
            pi0mass[i] = 0;
            for (int j = 0; j < 2; j++) {
                pi0_e[i][j] = 0;
                for (int k = 0; k<3; k++) pi0_dir[i][j][k] = 0;
            }
        }
        nmue = 0;
    }

}


/*
void T2KLowE::setBranch(TTree *tree)   
{

    tree->SetBranchAddress("Is_mc",            &Is_mc);           //MC:1, Data:0

    // Data + MC Variables
    tree->SetBranchAddress("nrun",             &nrun);
    tree->SetBranchAddress("nsub",             &nsub);
    tree->SetBranchAddress("nev",              &nev);
    
    tree->SetBranchAddress("potot",            &potot);           //ID totpe (qismsk)
    tree->SetBranchAddress("nhit",             &nhit);
    tree->SetBranchAddress("n50",              &n50);

    tree->SetBranchAddress("pos[3]",           pos);              // Bonsai fit vertex 
    tree->SetBranchAddress("dir[3]",           dir);
    tree->SetBranchAddress("erec",             &erec);            // Bonsai fit energy
    tree->SetBranchAddress("wall",             &wall);
    tree->SetBranchAddress("effwall",          &effwall);
    tree->SetBranchAddress("ovaq",             &ovaq);
    tree->SetBranchAddress("angle",            &angle);           // Cherenkov angle from 3-hit pmt angle plot 
    tree->SetBranchAddress("angle_likelihood", &angle_likelihood);
    tree->SetBranchAddress("angle_15ns",            &angle_15ns);           // Cherenkov angle from 3-hit pmt angle plot 
    tree->SetBranchAddress("angle_likelihood_15ns", &angle_likelihood_15ns);
    tree->SetBranchAddress("anglebinnum", &anglebinnum);
    tree->SetBranchAddress("plotcontent", plotcontent);

    tree->SetBranchAddress("goodness",         &goodness);        // Bonsai fit goodness
   
    //tree->SetBranchAddress("cossun",           &cossun);
    //tree->SetBranchAddress("patlik",           &patlik);
    //tree->SetBranchAddress("lsd",              &lsd);
    //tree->SetBranchAddress("forwall",          &forwall);

    // Read the first entry to find out if this is an MC tree
    tree->GetEntry(0);
    if (Is_mc) {
        // MC-only Variables
        tree->SetBranchAddress("mode",               &mode);          // neutrino interaction mode
        tree->SetBranchAddress("wallv",              &wallv);
        tree->SetBranchAddress("posv",               posv);
     
        tree->SetBranchAddress("numnu",              &numnu);
        tree->SetBranchAddress("ipnu",               ipnu);     //[numnu]
        tree->SetBranchAddress("pnu",                pnu);      //[numnu]
        tree->SetBranchAddress("dirnu",              dirnu[100]); //[numnu]

        tree->SetBranchAddress("npar",               &npar);
        tree->SetBranchAddress("ipv",                ipv);      //[npar]
        tree->SetBranchAddress("icrnv",              icrnv);    //[npar]
        tree->SetBranchAddress("dirv",               dirv[100]);  //[npar]
        tree->SetBranchAddress("pmomv",              pmomv);    //[npar]

        tree->SetBranchAddress("npar2",              &npar2);
        tree->SetBranchAddress("wallv2",             wallv2);   //[npar2]
        tree->SetBranchAddress("ipv2",               ipv2);     //[npar2]
        tree->SetBranchAddress("posv2",              posv2[100]); //[npar2]
        tree->SetBranchAddress("dirv2",              dirv2[100]); //[npar2]
        tree->SetBranchAddress("pmomv2",             pmomv2);   //[npar2]

        tree->SetBranchAddress("ng1",                &ng1);           // # of primary gamma
        tree->SetBranchAddress("ng2",                &ng2);           // # of secondary gamma
        tree->SetBranchAddress("toteg1",             &toteg1);        //total primary gamma energy
        tree->SetBranchAddress("toteg2",             &toteg2);        //total secondary gamma energy

        tree->SetBranchAddress("num_primary_gammas", &num_primary_gammas);
        tree->SetBranchAddress("num_neutron_gammas", &num_neutron_gammas);
        tree->SetBranchAddress("num_proton_gammas",  &num_proton_gammas);

        tree->SetBranchAddress("IsPionAbs",          &IsPionAbs);     // Flag of pion absorption

        // Required for T2KReWeight
        tree->SetBranchAddress("Neutmode",           &Neutmode);
        tree->SetBranchAddress("Npne",               &Npne);
        tree->SetBranchAddress("Ipne",               Ipne);      //[Npne]
        tree->SetBranchAddress("Abspne",             Abspne);    //[Npne]
        tree->SetBranchAddress("Pvecne",             Pvecne[100]); //[Npne]
        tree->SetBranchAddress("Npvc",               &Npvc);
        tree->SetBranchAddress("Ipvc",               Ipvc);      //[Npvc]
        tree->SetBranchAddress("Ichvc",              Ichvc);     //[Npvc]
        tree->SetBranchAddress("Iorgvc",             Iorgvc);    //[Npvc]
        tree->SetBranchAddress("Iflvc",              Iflvc);     //[Npvc]
        tree->SetBranchAddress("Abspvc",             Abspvc);    //[Npvc]
        tree->SetBranchAddress("Pvc",                Pvc[100]);    //[Npvc]
        tree->SetBranchAddress("Crsx",               &Crsx);
        tree->SetBranchAddress("Crsy",               &Crsy);
        tree->SetBranchAddress("Crsz",               &Crsz);
        tree->SetBranchAddress("Crsphi",             &Crsphi);
        tree->SetBranchAddress("Numbndn",            &Numbndn);
        tree->SetBranchAddress("Numbndp",            &Numbndp);
        tree->SetBranchAddress("Numfrep",            &Numfrep);
        tree->SetBranchAddress("Numatom",            &Numatom);
        tree->SetBranchAddress("Ibound",             &Ibound);
        tree->SetBranchAddress("Nvert",              &Nvert);
        tree->SetBranchAddress("Posvert",            Posvert[300]); //[Nvert]
        tree->SetBranchAddress("Iflgvert",           Iflgvert);   //[Nvert]
        tree->SetBranchAddress("Nvcvert",            &Nvcvert);
        tree->SetBranchAddress("Dirvert",            Dirvert[900]); //[Nvcvert]
        tree->SetBranchAddress("Abspvert",           Abspvert);   //[Nvcvert]
        tree->SetBranchAddress("Abstpvert",          Abstpvert);  //[Nvcvert]
        tree->SetBranchAddress("Ipvert",             Ipvert);     //[Nvcvert]
        tree->SetBranchAddress("Iverti",             Iverti);     //[Nvcvert]
        tree->SetBranchAddress("Ivertf",             Ivertf);     //[Nvcvert]
        tree->SetBranchAddress("Fsiprob",            &Fsiprob);
    }

}
*/

void T2KLowE::createTree (TTree *tree) {
    //creates the output file and tree for output
    //NCamma MC info

    tree->Branch("Is_mc",              &Is_mc,              "Is_mc/I");       //MC:1, Data:0

    // Data + MC Variables
    tree->Branch("nrun",               &nrun,               "nrun/I");
    tree->Branch("nsub",               &nsub,               "nsub/I");
    tree->Branch("nev",                &nev,                "nev/I");
    

    tree->Branch("dt0",                &dt0,                "dt0/F");
    tree->Branch("dt0vtx",             &dt0vtx,             "dt0vtx/F");
    tree->Branch("dt0type",            &dt0type,            "dt0type/I");
    tree->Branch("n30max",             &n30max,             "n30max/I");
    tree->Branch("n30time",            &n30time,            "n30time/F");
    tree->Branch("potot",              &potot,              "potot/F");     //ID totpe (qismsk)
    tree->Branch("nhit",               &nhit,               "nhit/I");     //ID hits (nqisk)
    tree->Branch("n50",                &n50,                "n50/I");     // N50 from Bonasi fit

    tree->Branch("pos",                pos,                 "pos[3]/F");    // Bonsai fit vertex
    tree->Branch("bdir",               bdir,                "bdir[3]/F");
    tree->Branch("erec",               &erec,               "erec/F");      // Bonsai fit energy
    tree->Branch("wall",               &wall,               "wall/F");
    tree->Branch("effwall",            &effwall,            "effwall/F");
    tree->Branch("ovaq",               &ovaq,               "ovaq/F");
    tree->Branch("angle",              &angle,              "angle/F");     // Cherenkov angle from 3-hit pmt  
    tree->Branch("angle_likelihood",   &angle_likelihood,   "angle_likelihood/F");
    tree->Branch("angle_15ns",              &angle_15ns,              "angle_15ns/F");     // Cherenkov angle from 3-hit pmt  
    tree->Branch("angle_likelihood_15ns",   &angle_likelihood_15ns,   "angle_likelihood_15ns/F");
    tree->Branch("anglebinnum", &anglebinnum, "anglebinnum/I");
    tree->Branch("plotcontent", plotcontent, "plotcontent[anglebinnum]/F");

    tree->Branch("goodness",           &goodness,           "goodness/F");  // Bonsai fit goodness

    //tree->Branch("cossun",             &cossun,             "cossun/F");
    //tree->Branch("patlik",             &patlik,             "patlik/F");
    //tree->Branch("lsd",                &lsd,                "lsd/F");
    //tree->Branch("forwall",            &forwall,            "forwall/F");


    if (!Is_mc) {
        tree->Branch("mrrun",   &mrrun,   "mrrun/I");
        tree->Branch("date",    date,     "date[3]/I");
        tree->Branch("time",    time,     "time[4]/I");
        tree->Branch("elpsday", &elpsday, "elpsday/F");
    }


    if (Is_mc) {
        // MC-only Variables
        tree->Branch("mode",               &mode,               "mode/I");          // neutrino interaction mode
        tree->Branch("wallv",              &wallv,              "wallv/F");
        tree->Branch("posv",               posv,                "posv[3]/F");
    
        tree->Branch("numnu",              &numnu,              "numnu/I");
        tree->Branch("ipnu",               ipnu,                "ipnu[numnu]/I");     
        tree->Branch("pnu",                pnu,                 "pnu[numnu]/F");      
        tree->Branch("dirnu",              dirnu,               "dirnu[numnu][3]/F"); 

        tree->Branch("npar",               &npar,               "npar/I");
        tree->Branch("ipv",                ipv,                 "ipv[npar]/I");      
        tree->Branch("icrnv",              icrnv,               "icrnv[npar]/I");    
        tree->Branch("dirv",               dirv,                "dirv[npar][3]/F");  
        tree->Branch("pmomv",              pmomv,               "pmomv[npar]/F");    

        tree->Branch("npar2",              &npar2,              "npar2/I");
        tree->Branch("wallv2",             wallv2,              "wallv2[npar2]/F");   
        tree->Branch("ipv2",               ipv2,                "ipv2[npar2]/I");     
        tree->Branch("posv2",              posv2,               "posv2[npar2][3]/F"); 
        tree->Branch("dirv2",              dirv2,               "dirv2[npar2][3]/F"); 
        tree->Branch("pmomv2",             pmomv2,              "pmomv2[npar2]/F");   

        tree->Branch("ng1",                &ng1,                "ng1/I");           // # of primary gamma
        tree->Branch("ng2",                &ng2,                "ng2/I");           // # of secondary gamma
        tree->Branch("toteg1",             &toteg1,             "toteg1/F");        //total primary gamma energy
        tree->Branch("toteg2",             &toteg2,             "toteg2/F");        //total secondary gamma energy

        tree->Branch("num_primary_gammas", &num_primary_gammas, "num_primary_gammas/I");
        tree->Branch("num_neutron_gammas", &num_neutron_gammas, "num_neutron_gammas/I");
        tree->Branch("num_proton_gammas",  &num_proton_gammas,  "num_proton_gammas/I");

        tree->Branch("IsPionAbs",          &IsPionAbs,          "IsPionAbs/I");     // Flag of pion absorption

        // Required for T2KReWeight
        tree->Branch("nscndprt",  &nscndprt, "nscndprt/I");
        tree->Branch("itrkscnd",  itrkscnd,  "itrkscnd[nscndprt]/I"); 
        tree->Branch("vtxscnd",   vtxscnd,   "vtxscnd[nscndprt][3]/F"); 
        tree->Branch("pscnd",     pscnd,     "pscnd[nscndprt][3]/F"); 
        tree->Branch("iprtscnd",  iprtscnd,  "iprtscnd[nscndprt]/I"); 
        tree->Branch("tscnd",     tscnd,     "tscnd[nscndprt]/F"); 
        tree->Branch("iprntprt",  iprntprt,  "iprntprt[nscndprt]/I"); 
        tree->Branch("lmecscnd",  lmecscnd,  "lmecscnd[nscndprt]/I"); 
        tree->Branch("iprnttrk",  iprnttrk,  "iprnttrk[nscndprt]/I"); 
        tree->Branch("iorgprt",   iorgprt,   "iorgprt[nscndprt]/I"); 
        tree->Branch("iprntidx",  iprntidx,  "iprntidx[nscndprt]/I"); 
        tree->Branch("nchilds",   nchilds,   "nchilds[nscndprt]/I"); 
        tree->Branch("ichildidx", ichildidx, "ichildidx[nscndprt]/I"); 
        tree->Branch("pprnt",     pprnt,     "pprnt[nscndprt][3]/F");  
        tree->Branch("pprntinit", pprntinit, "pprntinit[nscndprt][3]/F");  
        tree->Branch("vtxprnt",   vtxprnt,   "vtxprnt[nscndprt][3]/F");  
        tree->Branch("iflgscnd",  iflgscnd,  "iflgscnd[nscndprt]/I"); 


        tree->Branch("npvcscnd",    &npvcscnd,   "npvcscnd/I");
        tree->Branch("nchildsvc",   nchildsvc,   "nchildsvc[npvcscnd]/I");      
        tree->Branch("ichildidxvc", ichildidxvc, "ichildidxvc[npvcscnd]/I");      

        tree->Branch("Neutmode",  &Neutmode, "Neutmode/I");
        tree->Branch("Npne",      &Npne,     "Npne/I");
        tree->Branch("Ipne",      Ipne,      "Ipne[Npne]/I");      
        tree->Branch("Abspne",    Abspne,    "Abspne[Npne]/F");    
        tree->Branch("Pvecne",    Pvecne,    "Pvecne[Npne][3]/F"); 
        tree->Branch("Npvc",      &Npvc,     "Npvc/I");
        tree->Branch("Ipvc",      Ipvc,      "Ipvc[Npvc]/I");      
        tree->Branch("Ichvc",     Ichvc,     "Ichvc[Npvc]/I");     
        tree->Branch("Iorgvc",    Iorgvc,    "Iorgvc[Npvc]/I");    
        tree->Branch("Iflvc",     Iflvc,     "Iflvc[Npvc]/I");     
        tree->Branch("Abspvc",    Abspvc,    "Abspvc[Npvc]/F");    
        tree->Branch("Pvc",       Pvc,       "Pvc[Npvc][3]/F");    
        tree->Branch("Crsx",      &Crsx,     "Crsx/F");
        tree->Branch("Crsy",      &Crsy,     "Crsy/F");
        tree->Branch("Crsz",      &Crsz,     "Crsz/F");
        tree->Branch("Crsphi",    &Crsphi,   "Crsphi/F");
        tree->Branch("Numbndn",   &Numbndn,  "Numbndn/I");
        tree->Branch("Numbndp",   &Numbndp,  "Numbndp/I");
        tree->Branch("Numfrep",   &Numfrep,  "Numfrep/I");
        tree->Branch("Numatom",   &Numatom,  "Numatom/I");
        tree->Branch("Ibound",    &Ibound,   "Ibound/I");
        tree->Branch("Nvert",     &Nvert,    "Nvert/I");
        tree->Branch("Posvert",   Posvert,   "Posvert[Nvert][3]/F"); 
        tree->Branch("Iflgvert",  Iflgvert,  "Iflgvert[Nvert]/I");   
        tree->Branch("Nvcvert",   &Nvcvert,  "Nvcvert/I");
        tree->Branch("Dirvert",   Dirvert,   "Dirvert[Nvcvert][3]/F"); 
        tree->Branch("Abspvert",  Abspvert,  "Abspvert[Nvcvert]/F");   
        tree->Branch("Abstpvert", Abstpvert, "Abstpvert[Nvcvert]/F");  
        tree->Branch("Ipvert",    Ipvert,    "Ipvert[Nvcvert]/I");     
        tree->Branch("Iverti",    Iverti,    "Iverti[Nvcvert]/I");     
        tree->Branch("Ivertf",    Ivertf,    "Ivertf[Nvcvert]/I");     
        tree->Branch("Fsiprob",   &Fsiprob,  "Fsiprob/F");

        tree->Branch("nring",     &nring,    "nring/F");
        tree->Branch("nhitac",    &nhitac,   "nhitac/i");
        tree->Branch("evis",      &evis,     "evis/F");
        tree->Branch("ip",        ip,        "ip[nring]/i");
        tree->Branch("dir",       dir,       "dir[nring][3]/F");
        tree->Branch("amom",      amom,      "amom[nring]/F");
        tree->Branch("amome",     amome,     "amome[nring]/F");
        tree->Branch("amomm",     amomm,     "amomm[nring]/F");
        tree->Branch("pi0like",   pi0like,   "pi0like[2]/F");
        tree->Branch("pi0_e",     pi0_e,     "pi0_e[2][2]/F");
        tree->Branch("pi0_dir",   pi0_dir,   "pi0_dir[2][2][3]/F");
        tree->Branch("pi0mass",   pi0mass,   "pi0mass[2]/F");
        tree->Branch("nmue",      &nmue,     "nmue/I");

    }

}
