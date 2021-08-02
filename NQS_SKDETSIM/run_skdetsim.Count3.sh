#!/bin/bash

### Current directory
TOPDIR=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC

### source for necessary Environment variables
source $TOPDIR/skenv_py.sh

### SKDETSIM source files
DSDIR=/disk02/usr6/pmehta/ncgamma/mc/skdetsim-skgd

### References
source /usr/local/sklib_gcc4.8.5/geant4.9.6.p04/bin/geant4.sh
source /usr/local/sklib_gcc4.8.5/geant4.9.6.p04/share/Geant4-9.6.4/geant4make/geant4make.sh
export G4NEUTRONHPDATA="/usr/local/sklib_gcc4.8.5/geant4.9.6.p04/share/Geant4-9.6.4/data/G4NDL4.2"
export G4WORKDIR=$DSDIR/geant4_work
export G4TMPDIR="${G4WORKDIR}/tmp/"
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4TMPDIR}/Linux-g++/gtneut/
export RANFILE="/home/atmpd/skdetsim/skdetsim-v13p90_for_atmnu_test/random.tbl.000"
    
### PATH of card file
DSCARD=$TOPDIR/SKDETSIM/sample.card


### 
GENERATE()
{
	Xnum=$1

    ### File format: fhc.num.VECTcountXXX.partYYY.dat
    ### XXX is 000-099
    ### YYY is 001-003 (000 also exists, but do not use because it is empty)
    for ((count=0;count<10;count++))
    do
    	for ((p=1;p<4;p++))
    	do
    		part=`printf "%03d" $p`
    		echo " "
			echo "----------------------------------------------------------------------------------------------"
			echo "[###### SKDETSIM ######]  Input : fhc.num.VECTcount0$Xnum$count.part$part.dat"
			echo "[###### SKDETSIM ######]  Output: fhc.numu.skdetsim.0026Gd.NEUTcount0$Xnum$count.part$part.zbs"
			echo "----------------------------------------------------------------------------------------------"
			echo " "

			### MC input file from NEUT
			NEUTVECT=/disk02/usr6/sedi/NEUTvect/fhc.num.VECTcount0$Xnum$count.part$part.dat
			### output file of SKDETSIM
			DSOUT=/disk02/usr6/sedi/SKDETSIM/output/fhc.numu.skdetsim.0026Gd.NEUTcount0$Xnum$count.part$part.zbs

			### Execution of SKDETSIM
			$DSDIR/skdetsim $DSCARD\
			                $DSOUT\
			                $NEUTVECT &> /disk02/usr6/sedi/SKDETSIM/Log/fhc.numu.0026Gd.NEUTcount0$Xnum$count.part$part.txt
		done
	done

	if [ $? = 0 ]; then
		echo "[###### SKDETSIM #####]  SKDETSIM is finished."
	else
		echo "[###### SKDETSIM #####]  ERROR: SKDETSIM is aborted."
	fi
}


### 3 should be replaced into 0-9
### Replacement is done by qsub_skdetsim.py
GENERATE 3