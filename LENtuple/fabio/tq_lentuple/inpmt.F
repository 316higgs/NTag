      SUBROUTINE INPMT(POS,IPMT)

      IMPLICIT NONE

#include "skparm.h"
#include "skhead.h"
#include "geotnk.h"
#include "geopmt.h"
#include "skmisch.h"

      integer IPMT, i
      real pos(3), dwall, dpos(3)
      real RPMT
      real rr,r
      real sqrt, absvctsk
      parameter(RPMT=25.)        ! set r of PMT to 25 cm

      IPMT = 0
      RR=POS(1)**2+POS(2)**2
      R=SQRT(RR)
      dwall=RINTK-R
      if (dwall.gt.RPMT) then
* CHK TOP or BTM
         if (pos(3).gt.ZPINTK-RPMT) then    ! CHK TOP
            do i=7651,9398
               if ( imis(i).eq.0 ) then
               dpos(1)=xyzpm(1,i)-pos(1)
               dpos(2)=xyzpm(2,i)-pos(2)
               dpos(3)=xyzpm(3,i)-pos(3)
               if (absvctsk(dpos).lt.RPMT) then
                  IPMT=i
                  return
               endif
               endif
            enddo
         else if (pos(3).lt.-ZPINTK+RPMT) then    ! CHK PMT
            do i=9399,11146
               if ( imis(i).eq.0 ) then
               dpos(1)=xyzpm(1,i)-pos(1)
               dpos(2)=xyzpm(2,i)-pos(2)
               dpos(3)=xyzpm(3,i)-pos(3)
               if (absvctsk(dpos).lt.RPMT .and. imis(i).eq.0 ) then
                  IPMT=i
                  return
               endif
               endif
            enddo
         endif
*  outside 
         return
      else
* CHK BRL
         do i=1,7650
            if ( imis(i).eq.0 ) then
            dpos(1)=xyzpm(1,i)-pos(1)
            dpos(2)=xyzpm(2,i)-pos(2)
            dpos(3)=xyzpm(3,i)-pos(3)
            if (absvctsk(dpos).lt.RPMT .and. imis(i).eq.0 ) then
               IPMT=i
               return
            endif
            endif
          enddo
      endif
      return
      END
