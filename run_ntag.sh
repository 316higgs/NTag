#!/bin/bash

source skenv_py.sh

EXE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/ntag/ntag_mc/ntag_mc

EXECUTE()
{
	ncount=$1
	npart=$2
	nskip=$3

	Ncount=`printf "%03d" "$ncount"`
	Npart=`printf "%03d" "$npart"`
	INPUT=/disk02/usr6/sedi/LENtuple/output/fhc.numu.lentuple.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.root
	OUTPUT=/disk02/usr6/sedi/Ntag/output/fhc.numu.ntag.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.root

	echo $INPUT
	echo $OUTPUT

	$EXE $INPUT\
	     $OUTPUT

    if [ $? -eq 0 ]; then
    	echo "[### Ntag ###] Finished sucessfully."
    else
    	echo "[### Ntag ###] Aborted."
    fi
}

#EXECUTE XCount Xpart Xskip
EXECUTE 0 1 0