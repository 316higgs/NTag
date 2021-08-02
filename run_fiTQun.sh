#!/bin/bash

source skenv_py.sh
#source /usr/local/sklib_g77/cshenv_g77_skofl_14c+atmpd_14c
#source /usr/local/sklib_g77/bashenv_g77_skofl_17a+atmpd_17a

source /home/skofl/sklib_gcc4.8.5/skofl_21a/env.sh

EXE=/home/sklb/reduction/test_21a/src/fiTQun/fitqun/fitqunv4r0c/fiTQun/runfiTQun

nskip=0
nproc=100
fqcard=/disk02/usr6/sedi/fiTQun/fiTQun.parameters.dat

EXECUTE()
{
	ncount=$1
	npart=$2
	Nskip=$3

	Ncount=`printf "%03d" "$ncount"`
    Npart=`printf "%03d" "$npart"`
	INPUT=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount$Ncount.part$Npart.skip$Nskip.zbs
	OUTPUT=/disk02/usr6/sedi/fiTQun/output/fhc.numu.fiTQun.0026Gd.NEUTcount$Ncount.part$Npart.skip$Nskip.zbs

	echo $INPUT
	echo $OUTPUT

    $EXE $INPUT\
         -p $fqcard\
         -s $nskip\
         -n $nproc\
         -o $OUTPUT

    if [ $? -eq 0 ]; then
    	echo "[### fiTQun ###] Finished sucessfully."
    else
    	echo "[### fiTQun ###] Aborted."
    fi
}

#EXECUTE XCount Xpart Xskip
EXECUTE 0 1 0