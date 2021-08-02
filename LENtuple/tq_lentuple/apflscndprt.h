
      integer MAXNSCNDPRT
      parameter (MAXNSCNDPRT=1000)
C     Warning: Make sure to change size of "nscndprt" below if changing this

      integer*4 nscndprtc,itrkscndc(MAXNSCNDPRT),istakscndc(MAXNSCNDPRT),
     &          iprtscndc(MAXNSCNDPRT),iprntprtc(MAXNSCNDPRT),
     &          lmecscndc(MAXNSCNDPRT),iprnttrkc(MAXNSCNDPRT),
     &          iorgprtc(MAXNSCNDPRT),iflgscndc(MAXNSCNDPRT),
     &          iprntidxc(MAXNSCNDPRT), nchildsc(MAXNSCNDPRT),
     &          ichildidxc(MAXNSCNDPRT), npvcscndc, 
     &          nchildsvcc(100), ichildidxvcc(100)

      real*4    vtxscndc(3,MAXNSCNDPRT),pscndc(3,MAXNSCNDPRT),
     &          tscndc(MAXNSCNDPRT),pprntc(3,MAXNSCNDPRT),
     &          pprntinitc(3,MAXNSCNDPRT),vtxprntc(3,MAXNSCNDPRT)

      common/secndprc/nscndprtc,itrkscndc,istakscndc,vtxscndc
     &               ,pscndc   ,iprtscndc,tscndc
     &               ,iprntprtc,lmecscndc
     &               ,iprnttrkc,iorgprtc
     &               ,pprntc,iflgscndc,pprntinitc,vtxprntc
     &               ,iprntidxc,nchildsc,ichildidxc
     &               ,npvcscndc, nchildsvcc, ichildidxvcc

C      character*60   scndtags(11)
C      character*660  scndtag
C      equivalence (scndtag,scndtags(1))

C     Warning: Size of nscndprt here must correspond to MAXSCNDPRT above
C      data scndtags/
C     &     'nscndprt[0,1000]:I,itrkscnd(nscndprt):I                 ,',
C     &     'istakscnd(nscndprt):I                                   ,',
C     $     'vtxscnd(3,nscndprt):R  ,pscnd(3,nscndprt):R             ,',
C     $     'iprtscnd(nscndprt):I   ,tscnd(nscndprt):R               ,',
C     $     'iprntprt(nscndprt):I   ,lmecscnd(nscndprt):I            ,',
C     $     'iprnttrk(nscndprt):I   ,iorgprt(nscndprt):I             ,',
C     $     'pprnt(3,nscndprt):R    ,iflgscnd(nscndprt):I            ,',
C     $     'pprntinit(3,nscndprt):R,vtxprnt(3,nscndprt):R           ,',
C     $     'iprntidx(nscndprt):I   ,nchilds(nscndprt):I             ,',
C     $     'ichildidx(nscndprt):I  ,NPVCSCND[0,100]:I               ,',
C     $     'NCHILDSVC(NPVCSCND):I  ,ICHILDIDXVC(NPVCSCND):I          '/
