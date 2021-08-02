#!/bin/sh

export RFLIST=/tmp/rflist.$$.$user.`hostname`

input=$1
output_root=$2

if [ X$output_root == X ]; then
  output_root = `basename lentp_$input`
fi

local1=LOCAL 
if [[ $input == /disk/* ]]; then
  local1=DISK
fi


EXE=`dirname $0`/make_t2klowe_ntuple

cat <<! > $RFLIST
10{{"$input",$local1,,RED,,,"recl=5670 status=old"}}
!

date
cat $RFLIST

#cd $ATMPD_ROOT/src/analysis/neutron/ntag
if [ X$GDB != X ] ; then
    gdb --args $EXE -i $input -o $output_root
else
    $EXE -i $input -o $output_root
fi

date
/bin/rm $RFLIST
