#!/bin/bash

source skenv_py.sh

CARD=/disk02/usr6/sedi/SKDETSIM/sample.card

EXE=/disk02/usr6/pmehta/ncgamma/mc/skdetsim-skgd/skdetsim

source /usr/local/sklib_gcc4.8.5/geant4.9.6.p04/bin/geant4.sh
source /usr/local/sklib_gcc4.8.5/geant4.9.6.p04/share/Geant4-9.6.4/geant4make/geant4make.csh 
export G4NEUTRONHPDATA="/usr/local/sklib_gcc4.8.5/geant4.9.6.p04/share/Geant4-9.6.4/data/G4NDL4.2"
export G4WORKDIR=$soft/skdetsim-skgd/geant4_work/
export G4TMPDIR="${G4WORKDIR}/tmp/"
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4TMPDIR}/Linux-g++/gtneut/
export RANFILE="/home/atmpd/skdetsim/skdetsim-v13p90_for_atmnu_test/random.tbl.000"

EXECUTE()
{
	ncount=$1
	npart=$2

	Ncount=`printf "%03d" "$ncount"`
	Npart=`printf "%03d" "$npart"`
	INPUT=/disk02/usr6/sedi/NEUTvect/fhc.num.VECTcount$Ncount.part$Npart.dat
	OUTPUT=/disk02/usr6/sedi/SKDETSIM/output/fhc.numu.skdetsim.0026Gd.NEUTcount$Ncount.part$Npart.zbs

	echo $INPUT
	echo $OUTPUT

	$EXE $CARD\
	     $INPUT\
	     $OUTPUT

	if [ $? -eq 0 ]; then
    	echo "[### SKDETSIM ###] Finished sucessfully."
    else
    	echo "[### SKDETSIM ###] Aborted."
    fi
}

#EXECUTE XCount Xpart
EXECUTE 0 1