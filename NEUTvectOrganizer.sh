#!/bin/bash

TOPDIR=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC
NEUTVECT=/disk02/usr6/pmehta/neutfile/flux.13anom.run1to9.fhc_neut.533.modified
EXE_Divide=/home/okumura/bin/skdump

NEUTvectOrganizer() {

    ### FHC or RHC
    MODE=$1
    ### neb or nmb or nue or num
	HEADER=$2
	### 00-99
	COUNTER=$3
    ### BUG checker
	BUG=0

	### Checker
	if [ $HEADER != "neb" ] && [ $HEADER != "nmb" ] && [ $HEADER != "nue" ] && [ $HEADER != "num" ]; then
		echo "[### NEUTvectOrganizer ###]  Head of file name is wrong: Such file does not exist."
		echo "[### NEUTvectOrganizer ###]  Candidate is below...  Please check /disk02/usr6/pmehta/neutfile/flux.13anom.run1to9.fhc_neut.533.modified"
		echo "                             -> neb or nmb or nue or num"
		BUG=1
	fi
	if [ $COUNTER -gt 99 ]; then
		echo "[### NEUTvectOrganizer ###]  File number is wrong: Such file does not exist.  Please fill in a number from 00-99."
		echo "[### NEUTvectOrganizer ###]  Please check /disk02/usr6/pmehta/neutfile/flux.13anom.run1to9.fhc_neut.533.modified"
		BUG=1
	fi

    ### Normal run
	if [ $BUG = 0 ]; then
		SRCNEUTVECT=$HEADER.h2o.sk.flux13a.neut_533.0$COUNTER.dat
		echo "[### NEUTvectOrganizer ###]  File name: $SRCNEUTVECT"
		echo "-------------------------------------------------------------"

		### Input file of original NEUT vector file
        INPUT=$NEUTVECT/$SRCNEUTVECT

        ### The directory for output files
		OUTPUTDIR=/disk02/usr6/sedi/NEUTvect
		### output file prefix
		OUTPUT=tmp.dat

        ### /home/okumura/bin/skdump makes output files at this directory temporarily
        ### Finally, these outputs are moved to NEUTvect after name changing
        EXE=$TOPDIR/exeNEUTvect
		mkdir $EXE
		cd $EXE

		### Execution of division
		$EXE_Divide -d 1000\
		            -o $OUTPUT\
		            $INPUT

        OUTnum=`ls -1 | wc -l`
        echo "-------------------------------------------------------------"
        echo "[### NEUTvectOrganizer ###]  $OUTnum files are created."
		### Name change
		### /home/okumura/bin/skdump makes output files with the format of tmp.dat.000 etc at EXE
		### change its name into the format of .dat and move it to the directory of OUTPUT
        for ((i=0;i<$OUTnum;i++))
        do
        	number=`printf "%03d" $i`

        	### original output format (tmp.dat.000 etc)
        	original=$OUTPUT.$number

        	### new format
        	new=$MODE.$HEADER.VECTcount0$COUNTER.part$number.dat
        	echo "$original -> $new"

        	mv $original $new
        	mv $new $OUTPUTDIR/$new
        	echo "[### NEUTvectOrganizer ###]  Divided file: $new is created at $OUTPUTDIR."
        	echo " "
        done
        cd $TOPDIR
        rm -rf $EXE
        echo "[### NEUTvectOrganizer ###]  $SRCNEUTVECT: Division succeed."
	fi
}

#NEUTvectOrganizer fhc num 99

for ((j=0;j<100;j++))
do
	count=`printf "%02d" $j`
	echo " "
	echo "-------------------------------------------------------------"
	echo "######"
	echo "[### NEUTvectOrganizer ###]  Job run[$j]: NEUTvectOrganizer fhc num $count"
	echo "######"
	NEUTvectOrganizer fhc num $count
done

if [ $? = 0 ]; then
	echo "[### NEUTvectOrganizer ###]  NEUTvectOrganizer is finished sucessfully."
else
	echo "[### NEUTvectOrganizer ###]  ERROR: NEUTvectOrganizer is aborted."
fi