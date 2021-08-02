/////////////////////////////////////////////////
//                                             //
// List of input variables for NN              //
//                                             //
// Author: Seidai (2021/6/30)                  //
//                                             //
/////////////////////////////////////////////////


//NN input variables
int runnumber;
int subnumber;
int eventnumber;
float dt0vtx; //?
float dt0;    //?

int N10nvx;
int N300S;
int NcS;
float beta1;
float beta2;
float beta3;
float beta4;
float beta5;
float ndwall;
float ntowall;
float d0;
float d1;
float d2;
float d3;
float d4;
float d5;
float d6;
float dmean;
float drms;
float ddiff;

int neutrondegree;
float ntagvtx[3];
float bonsvtx[3];
float dist_bonsntagvtx;
float dist_truentagvtx;
float erec;
float wall;
float effwall;
float ovaq;
float angle;
float timetrupos;
float timefalpos;
float capture_time;
float neutron_mom;

TFile* f;
TTree* tree;

bool id = true;

Color_t color = kAzure-4;

//histograms
TH1D* h1_beta1[2];
TH1D* h1_beta2[2];
TH1D* h1_beta3[2];
TH1D* h1_beta4[2];
TH1D* h1_beta5[2];

TH1D* h1_ndwall[2];
TH1D* h1_ntowall[2];

