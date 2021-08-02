#!/bin/bash

source skenv_py.sh

export tbkgduration=496000 # back-up safety useconds: 1 usec at bgn, 1 usec at end
export tbkginsert=18000

export EXE=/disk02/usr6/pmehta/ncgamma/injedgedbl/dummyinj.csh

EXECUTE()
{
    ncount=$1
    npart=$2
    nskip=$3
    nindex=$4
    Ncount=`printf "%03d" "$ncount"`
	Npart=`printf "%03d" "$npart"`
	Nindex=`printf "%03d" "$nindex"`

    f_dds_idx=/disk02/usr6/pmehta/ncgamma/mccomb/work/index/fhc/numu.dummyidx.$Nindex.txt

	INPUT=/disk02/usr6/sedi/fiTQun/output/fhc.numu.fiTQun.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.zbs
	OUTPUT=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.zbs
	SBI=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.sbi

	$EXE $f_dds_idx\
	     $tbkgduration\
	     $tbkginsert\
	     $INPUT\
	     $OUTPUT\
	     $SBI

	if [ $? -eq 0 ]; then
    	echo "[### MCcomb ###] Finished sucessfully."
    else
    	echo "[### MCcomb ###] Aborted."
    fi
}

#EXECUTE XCount Xpart Xskip Xindex
EXECUTE 0 1 0