#!/bin/bash

source skenv_py.sh

EXE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/LENtuple/fabio/tq_lentuple/make_t2klowe_ntuple

EXECUTE()
{
	ncount=$1
    npart=$2
    nskip=$3

    Ncount=`printf "%03d" "$ncount"`
    Npart=`printf "%03d" "$npart"`
    INPUT=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.zbs
    OUTPUT=/disk02/usr6/sedi/LENtuple/output/fhc.numu.lentuple.0026Gd.NEUTcount$Ncount.part$Npart.skip$nskip.root

    echo $INPUT
    echo $OUTPUT

    $EXE -i $INPUT\
         -o $OUTPUT

    if [ $? -eq 0 ]; then
    	echo "[### LENtuple ###] Finished sucessfully."
    else
    	echo "[### LENtuple ###] Aborted."
    fi
}

EXECUTE 32 1 300
#EXECUTE 0 1 0