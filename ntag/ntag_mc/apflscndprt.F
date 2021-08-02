      SUBROUTINE APFLSCNDPRT

      IMPLICIT NONE
#include "apscndry.h"      
#include "apflscndprt.h"
      INTEGER*4 IDATA(100),NDATA
      REAL*4    RDATA(100)
      EQUIVALENCE (IDATA(1),RDATA(1))

      INTEGER*4 lbank, i, j, lopc, lopc2

C-Locate BANK
      CALL KZBLOC('SCNDPRT',LBANK)
      IF (LBANK.eq.0) THEN
C         write(*,*) 'Event #',nevsk,':Doesn't contain SCNDPRT bank'
         write(*,*) 'APFLSCNDPRT:Does not contain SCNDPRT bank'
         RETURN
      ENDIF

C-READ number of segments
      CALL KZGET1('SCNDPRT',0,NDATA,IDATA)
      nscndprt = IDATA(1)
C- Add to MAX Y.H. 
      if (nscndprt.ge.secmaxrng) nscndprt=secmaxrng
      DO I=1,nscndprt
         CALL KZGET1('SCNDPRT',I,NDATA,IDATA)
         IF (NDATA.ne.13 .and. NDATA.ne.17 .and. NDATA.ne.27) THEN
            write(0,'(A17,$)') 'Error in apflscndprt:'
            write(0,*) 'Number of DATA is wrong(expected=13 or 17 or 27 !=',
     $                 NDATA,')'
            RETURN
         ENDIF
         
         IF (NDATA.eq.13) THEN
            itrkscnd(i)=IDATA(1)
            iprtscnd(i)=IDATA(2)
            DO J=1,3
               vtxscnd(J,I)=RDATA(2+J)
               pscnd(J,I)  =RDATA(5+j)
               pprnt(J,I)  =0
            END DO
            tscnd(I)   =RDATA(9)
            iprntprt(I)=IDATA(10)
            lmecscnd(i)=IDATA(11)
            iprnttrk(i)=idata(12)
            iorgprt(i)=idata(13)
            iflgscnd(i)=0

         ELSE IF (NDATA.eq.17) THEN
            itrkscnd(i)=IDATA(1)
            iprtscnd(i)=IDATA(2)
            DO J=1,3
               vtxscnd(J,I)=RDATA(2+J)
               pscnd(J,I)  =RDATA(5+j)
               pprnt(J,I)  =RDATA(8+j)
            END DO
            tscnd(I)   =RDATA(12)
            iprntprt(I)=IDATA(13)
            lmecscnd(i)=IDATA(14)
            iprnttrk(i)=idata(15)
            iorgprt(i)=idata(16)
            iflgscnd(i)=idata(17)

         ELSE IF (NDATA.eq.27) THEN

            itrkscnd(i)=IDATA(1)
            istakscnd(i)=IDATA(2)
            iprtscnd(i)=IDATA(3)
            DO J=1,3
               vtxscnd(J,I)=RDATA(3+J)
               pscnd(J,I)  =RDATA(6+j)
               pprnt(J,I)  =RDATA(9+j)
               pprntinit(J,I)=RDATA(12+j)
               vtxprnt(J,I)  =RDATA(15+j)
            END DO
            tscnd(I)   =RDATA(19)
            iprntprt(I)=IDATA(20)
            lmecscnd(i)=IDATA(21)
            iprnttrk(i)=idata(22)
            iorgprt(i)=idata(23)
            iflgscnd(i)=idata(24)
            iprntidx(i)=idata(25)
            nchilds(i)=idata(26)
            ichildidx(i)=idata(27)

         END IF
C         write(*,*) i,itrkscnd(i),iprtscnd(i),iprntprt(i),
C     $                   lmecscnd(i),iprnttrk(i),iorgprt(i),tscnd(i)
C 5000    format ('I4,I7,I7,I7,I7,I7,I7,F')
      end do
C      do 195 lopc=1,nscndprt
C         write(*,*) lopc,itrkscnd(lopc),iprtscnd(lopc),
C     $        iprntprt(lopc),lmecscnd(lopc),iprnttrk(lopc),
C     $        iorgprt(lopc)
C 195  continue


C-Locate BANK
      CALL KZBLOC('SCNDPRTVC',LBANK)
      IF (LBANK.eq.0) THEN
         write(*,*) 'APFLSCNDPRT:Does not contain SCNDPRTVC bank'
         goto 100
      ENDIF

C-READ number of segments
      CALL KZGET1('SCNDPRTVC',0,NDATA,IDATA)
      npvcscndc = IDATA(1)

      DO I=1,npvcscndc
         CALL KZGET1('SCNDPRTVC',I,NDATA,IDATA)
         IF (NDATA.ne.2) THEN
            write(0,'(A17,$)') 'Error in apflscndprt:'
            write(0,*) 'Number of DATA is wrong(expected=2 !=',
     $                 NDATA,')'
            RETURN
         ENDIF

            nchildsvc(i)=IDATA(1)         
            ichildidxvc(i)=IDATA(2)

      end do

      do lopc=1,npvcscndc
         nchildsvcc(lopc)  =nchildsvc(lopc)
         ichildidxvcc(lopc)=ichildidxvc(lopc)
      end do


C--debug
 100  nscndprtc=nscndprt
      if (nscndprtc.ge.MAXNSCNDPRT) nscndprtc=MAXNSCNDPRT
      do lopc=1,nscndprtc
C         write(*,*) lopc,itrkscnd(lopc),iprtscnd(lopc),
C     $        iprntprt(lopc),lmecscnd(lopc),iprnttrk(lopc),
C     $        iorgprt(lopc)
         itrkscndc(lopc)=itrkscnd(lopc)
         istakscndc(lopc)=istakscnd(lopc)
         iprtscndc(lopc)=iprtscnd(lopc)
         iprntprtc(lopc)=iprntprt(lopc)
         lmecscndc(lopc)=lmecscnd(lopc)
         iprnttrkc(lopc)=iprnttrk(lopc)
         iorgprtc(lopc) =iorgprt(lopc)
         do lopc2=1,3
            vtxscndc(lopc2,lopc)=vtxscnd(lopc2,lopc)
            pscndc(lopc2,lopc)=pscnd(lopc2,lopc)
            pprntc(lopc2,lopc)=pprnt(lopc2,lopc)
            pprntinitc(lopc2,lopc)=pprntinit(lopc2,lopc)
            vtxprntc(lopc2,lopc)=vtxprnt(lopc2,lopc)
         end do
         tscndc(lopc)=tscnd(lopc)
         iflgscndc(lopc)=iflgscnd(lopc)
         iprntidxc(lopc)=iprntidx(lopc)
         nchildsc(lopc)=nchilds(lopc)
         ichildidxc(lopc)=ichildidx(lopc)
      end do

      return
      END

