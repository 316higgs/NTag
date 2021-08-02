      subroutine fort_fopen(lun,fname,ftype, lmode)

#include "skhead.h"

      integer lun,lenchr
      character*512 fname
C      character*256 fname
      character*1   ftype
      integer lmode

C      fname = cname(1:len)
C      print *, 'fname test:', fname

!     lmode = {0,1} == {read, write} 

      if ( lmode .eq.0 ) then
         if (fname(1:5) .eq. '/disk') then
            print *, 'read as DISK: ', fname(1:lenchr(fname))
            call set_rflist(lun,fname,'DISK',' ','RED',' ',' ',
     &           'recl=5670 status=old',' ',' ')
         else
            print *, 'read as LOCAL: ', fname(1:lenchr(fname))
            call set_rflist(lun,fname,'LOCAL',' ','RED',' ',' ',
     &           'recl=5670 status=old',' ',' ')
         endif
      else
         if (fname(1:5) .eq. '/disk') then
            print *, 'write as DISK: ', fname(1:lenchr(fname))
            call set_rflist(lun,fname,'DISK',' ','WRT',' ',' ',
     &           'recl=5670 status=unknown',' ',' ')
         else
            print *, 'write as LOCAL: ', fname(1:lenchr(fname))
            call set_rflist(lun,fname,'LOCAL',' ','WRT',' ',' ',
     &           'recl=5670 status=unknown',' ',' ')
         endif
      endif ! end of lmode check

      
      CALL SKOPENF(LUN, 1 , ftype, IRET)
      IF (IRET.lt.0) THEN
        write(*,*) "reformat:***ERROR*** CAN NOT OPEN FILE ***", fname
        call exit(150)
      ENDIF
      call reset_rflist()
       
      return
      end

