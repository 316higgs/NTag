/*
 * Generated automatically by fh2h.pl
 * !!! DO NOT EDIT !!!
 * Edit the original fortran header file instead
 * or fix fh2h.pl if there is a translation bug.
 */


#ifndef FH2H_APFLSCNDPRT_H
#define FH2H_APFLSCNDPRT_H


#ifdef __cplusplus
extern "C" {
#endif


#ifndef IMPLICIT
#define IMPLICIT  /* Only to point out implicit types */
#endif


/*------ fortran header (without commons and data statements) ----------*/


#define MAXNSCNDPRT (4000)
/*     Warning: Make sure to change size of "nscndprt" below if changing this*/



/*common secndprc was here*/

/*      character*60   scndtags(11)*/
/*      character*660  scndtag*/
/*      equivalence (scndtag,scndtags(1))*/

/*     Warning: Size of nscndprt here must correspond to MAXSCNDPRT above*/
/*      data scndtags/ */
/*     &     'nscndprt[0,1000]:I,itrkscnd(nscndprt):I                 ,',*/
/*     &     'istakscnd(nscndprt):I                                   ,',*/
/*     $     'vtxscnd(3,nscndprt):R  ,pscnd(3,nscndprt):R             ,',*/
/*     $     'iprtscnd(nscndprt):I   ,tscnd(nscndprt):R               ,',*/
/*     $     'iprntprt(nscndprt):I   ,lmecscnd(nscndprt):I            ,',*/
/*     $     'iprnttrk(nscndprt):I   ,iorgprt(nscndprt):I             ,',*/
/*     $     'pprnt(3,nscndprt):R    ,iflgscnd(nscndprt):I            ,',*/
/*     $     'pprntinit(3,nscndprt):R,vtxprnt(3,nscndprt):R           ,',*/
/*     $     'iprntidx(nscndprt):I   ,nchilds(nscndprt):I             ,',*/
/*     $     'ichildidx(nscndprt):I  ,NPVCSCND[0,100]:I               ,',*/
/*     $     'NCHILDSVC(NPVCSCND):I  ,ICHILDIDXVC(NPVCSCND):I          '/ */


/*------ common blocks -------------------------------------------------*/

extern struct secndprc_common {
  int    nscndprtc;
  int    itrkscndc[MAXNSCNDPRT];
  int    istakscndc[MAXNSCNDPRT];
  float  vtxscndc[MAXNSCNDPRT][3];
  float  pscndc[MAXNSCNDPRT][3];
  int    iprtscndc[MAXNSCNDPRT];
  float  tscndc[MAXNSCNDPRT];
  int    iprntprtc[MAXNSCNDPRT];
  int    lmecscndc[MAXNSCNDPRT];
  int    iprnttrkc[MAXNSCNDPRT];
  int    iorgprtc[MAXNSCNDPRT];
  float  pprntc[MAXNSCNDPRT][3];
  int    iflgscndc[MAXNSCNDPRT];
  float  pprntinitc[MAXNSCNDPRT][3];
  float  vtxprntc[MAXNSCNDPRT][3];
  int    iprntidxc[MAXNSCNDPRT];
  int    nchildsc[MAXNSCNDPRT];
  int    ichildidxc[MAXNSCNDPRT];
  int    npvcscndc;
  int    nchildsvcc[100];
  int    ichildidxvcc[100];
} secndprc_;
#ifndef NO_EXTERN_COMMON_POINTERS
extern struct secndprc_common *secndprc;
#endif
#ifdef STATIC_COMMON_POINTERS
static struct secndprc_common *secndprc = &secndprc_;
#endif


/*------ data statements -----------------------------------------------*/


#ifndef NO_STATIC_DATA


#endif  /* #ifndef NO_STATIC_DATA */


/*------ end of fortran header -----------------------------------------*/


#ifdef __cplusplus
}
#endif


#endif  /* #ifndef FH2H_APFLSCNDPRT_H */
