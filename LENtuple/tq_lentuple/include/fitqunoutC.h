/*
 * Generated automatically by fh2h.pl
 * !!! DO NOT EDIT !!!
 * Edit the original fortran header file instead
 * or fix fh2h.pl if there is a translation bug.
 */


#ifndef FH2H_FITQUNOUT_H
#define FH2H_FITQUNOUT_H


#ifdef __cplusplus
extern "C" {
#endif


#ifndef IMPLICIT
#define IMPLICIT  /* Only to point out implicit types */
#endif


/*------ fortran header (without commons and data statements) ----------*/

/* Output information from fiTQun*/
/*                                 IPX=1 ; GAMMA*/
/*                                     2 ; ELECTRON*/
/*                                     3 ; MUON*/
/*                                     4 ; PION*/
/*                                     5 ; KAON*/
/*                                     6 ; PROTON*/
/*                                     7 ; CONE GENERATOR*/

/*  Fit information*/


/*common fitquninfo was here*/

/*  Time window information*/

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define MAXNPEAK (10)

/* Output information from spliTChan*/

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define MAXSE (10)





/*common fitquntwnd was here*/

/*  one ring fit information*/

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define MAXPX (7)

      



/*common fitqun1r was here*/

/*  pi0 fit information*/


/*common fitqunpi0 was here*/


/*  MR fit information*/

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define FQMAXNMRFIT (200)

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define FQMAXNRING (6)



/*common fitqunmr was here*/


/*  MS fit information*/

/*     ALSO HARDCODED IN NTUPLE MODULE*/
#define FQMSMAXRING (20)

/*     ALSO HARDCODED IN NTUPLE MODULE*/
#define FQMSMAXFIT (5)


/*     for each ms fit*/

/*     for each segment*/

/*common fitqunms was here*/


/*  2electron fit information*/
      

/*common fitqun2elec was here*/

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define FQTESTMAX1R (30)

/* also hardcoded in atmpd/src/analysis/official_ntuple/ntuple_module_fitqun.F*/
#define FQTESTMAXPI0 (30)


/*common fitqun1rtest was here*/


/*common fitqunpi0test was here*/


/*------ common blocks -------------------------------------------------*/

extern struct fitquninfo_common {
  int    ifqver;
  float  fqproctime[20];
} fitquninfo_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitquninfo_common *fitquninfo;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitquninfo_common *fitquninfo = &fitquninfo_;
#endif

extern struct fitquntwnd_common {
  float  trgoff;
  int    fqntwnd;
  int    fqtwnd_iclstr[MAXSE];
  int    fqtwnd_npeak[MAXSE];
  float  fqtwnd_prftt0[MAXSE];
  float  fqtwnd_prftpos[MAXSE][3];
  float  fqtwnd[MAXSE][2];
  float  fqtwnd_peakt0[MAXSE][MAXNPEAK];
  float  fqtwnd_peakiness[MAXSE][MAXNPEAK];
} fitquntwnd_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitquntwnd_common *fitquntwnd;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitquntwnd_common *fitquntwnd = &fitquntwnd_;
#endif

extern struct fitqun1r_common {
  int    fqnse;
  int    fqitwnd[MAXNPEAK];
  int    fqipeak[MAXNPEAK];
  int    fqnhitpmt[MAXNPEAK];
  float  fqtotq[MAXNPEAK];
  float  fq0rtotmu[MAXNPEAK];
  float  fq0rnll[MAXNPEAK];
  int    fqn50[MAXNPEAK];
  float  fqq50[MAXNPEAK];
  int    fq1rpcflg[MAXNPEAK][MAXPX];
  float  fq1rmom[MAXNPEAK][MAXPX];
  float  fq1rt0[MAXNPEAK][MAXPX];
  float  fq1rtotmu[MAXNPEAK][MAXPX];
  float  fq1rnll[MAXNPEAK][MAXPX];
  float  fq1rpos[MAXNPEAK][MAXPX][3];
  float  fq1rdir[MAXNPEAK][MAXPX][3];
  float  fq1rdconv[MAXNPEAK][MAXPX];
  float  fq1reloss[MAXNPEAK][MAXPX];
} fitqun1r_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqun1r_common *fitqun1r;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqun1r_common *fitqun1r = &fitqun1r_;
#endif

extern struct fitqunpi0_common {
  int    fqpi0pcflg[2];
  float  fqpi0mom1[2];
  float  fqpi0mom2[2];
  float  fqpi0momtot[2];
  float  fqpi0dconv1[2];
  float  fqpi0dconv2[2];
  float  fqpi0t0[2];
  float  fqpi0totmu[2];
  float  fqpi0nll[2];
  float  fqpi0mass[2];
  float  fqpi0photangle[2];
  float  fqpi0pos[2][3];
  float  fqpi0dir1[2][3];
  float  fqpi0dir2[2][3];
  float  fqpi0dirtot[2][3];
} fitqunpi0_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqunpi0_common *fitqunpi0;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqunpi0_common *fitqunpi0 = &fitqunpi0_;
#endif

extern struct fitqunmr_common {
  int    fqnmrfit;
  int    fqmrifit[FQMAXNMRFIT];
  int    fqmrnring[FQMAXNMRFIT];
  int    fqmrpcflg[FQMAXNMRFIT];
  float  fqmrnll[FQMAXNMRFIT];
  float  fqmrtotmu[FQMAXNMRFIT];
  int    fqmrpid[FQMAXNMRFIT][FQMAXNRING];
  float  fqmrmom[FQMAXNMRFIT][FQMAXNRING];
  float  fqmrdconv[FQMAXNMRFIT][FQMAXNRING];
  float  fqmreloss[FQMAXNMRFIT][FQMAXNRING];
  float  fqmrt0[FQMAXNMRFIT][FQMAXNRING];
  float  fqmrpos[FQMAXNMRFIT][FQMAXNRING][3];
  float  fqmrdir[FQMAXNMRFIT][FQMAXNRING][3];
} fitqunmr_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqunmr_common *fitqunmr;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqunmr_common *fitqunmr = &fitqunmr_;
#endif

extern struct fitqunms_common {
  int    fqmsnfit;
  int    fqmspcflg[FQMSMAXFIT];
  int    fqmsnseg[FQMSMAXFIT];
  int    fqmspid[FQMSMAXFIT];
  int    fqmsifit[FQMSMAXFIT];
  int    fqmsimer[FQMSMAXFIT];
  float  fqmstotmu[FQMSMAXFIT];
  float  fqmsnll[FQMSMAXFIT];
  float  fqmsmom[FQMSMAXFIT][FQMSMAXRING];
  float  fqmseloss[FQMSMAXFIT][FQMSMAXRING];
  float  fqmst0[FQMSMAXFIT][FQMSMAXRING];
  float  fqmspos[FQMSMAXFIT][FQMSMAXRING][3];
  float  fqmsdir[FQMSMAXFIT][FQMSMAXRING][3];
} fitqunms_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqunms_common *fitqunms;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqunms_common *fitqunms = &fitqunms_;
#endif

extern struct fitqun2elec_common {
  float  fq2elecmom1;
  float  fq2elecmom2;
  float  fq2elect0;
  float  fq2electotmu;
  float  fq2elecnll;
  float  fq2elecpos[3];
  float  fq2elecdir1[3];
  float  fq2elecdir2[3];
} fitqun2elec_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqun2elec_common *fitqun2elec;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqun2elec_common *fitqun2elec = &fitqun2elec_;
#endif

extern struct fitqun1rtest_common {
  int    fqtestn1r;
  int    fqtest1rstage[FQTESTMAX1R];
  int    fqtest1rse[FQTESTMAX1R];
  int    fqtest1rpid[FQTESTMAX1R];
  int    fqtest1rpcflg[FQTESTMAX1R];
  float  fqtest1rmom[FQTESTMAX1R];
  float  fqtest1rt0[FQTESTMAX1R];
  float  fqtest1rtotmu[FQTESTMAX1R];
  float  fqtest1rnll[FQTESTMAX1R];
  float  fqtest1rpos[FQTESTMAX1R][3];
  float  fqtest1rdir[FQTESTMAX1R][3];
  float  fqtest1rdconv[FQTESTMAX1R];
  float  fqtest1reloss[FQTESTMAX1R];
} fitqun1rtest_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqun1rtest_common *fitqun1rtest;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqun1rtest_common *fitqun1rtest = &fitqun1rtest_;
#endif

extern struct fitqunpi0test_common {
  int    fqtestnpi0;
  int    fqtestpi0stage[FQTESTMAXPI0];
  int    fqtestpi0pcflg[FQTESTMAXPI0];
  float  fqtestpi0mom1[FQTESTMAXPI0];
  float  fqtestpi0mom2[FQTESTMAXPI0];
  float  fqtestpi0momtot[FQTESTMAXPI0];
  float  fqtestpi0dconv1[FQTESTMAXPI0];
  float  fqtestpi0dconv2[FQTESTMAXPI0];
  float  fqtestpi0t0[FQTESTMAXPI0];
  float  fqtestpi0totmu[FQTESTMAXPI0];
  float  fqtestpi0nll[FQTESTMAXPI0];
  float  fqtestpi0mass[FQTESTMAXPI0];
  float  fqtestpi0photangle[FQTESTMAXPI0];
  float  fqtestpi0pos[FQTESTMAXPI0][3];
  float  fqtestpi0dir1[FQTESTMAXPI0][3];
  float  fqtestpi0dir2[FQTESTMAXPI0][3];
  float  fqtestpi0dirtot[FQTESTMAXPI0][3];
} fitqunpi0test_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct fitqunpi0test_common *fitqunpi0test;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct fitqunpi0test_common *fitqunpi0test = &fitqunpi0test_;
#endif


/*------ data statements -----------------------------------------------*/


#ifndef NO_STATIC_DATA


#endif  /* #ifndef NO_STATIC_DATA */


/*------ end of fortran header -----------------------------------------*/


#ifdef __cplusplus
}
#endif


#endif  /* #ifndef FH2H_FITQUNOUT_H */
