#!/bin/bash

### Current directory
TOPDIR=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC

export FITQUN_ROOT=/home/sklb/reduction/test_21a/src/fiTQun/fitqun/fitqunv4r0c/fiTQun

source /home/skofl/sklib_gcc4.8.5/skofl_21a/env.sh

### Table file
CARD=$TOPDIR/fiTQun/fiTQun.parameters.dat

### fiTQun(v4rc) compiled file 
SOURCE=/home/sklb/reduction/test_21a/src/fiTQun/fitqun/fitqunv4r0c/fiTQun/runfiTQun

GENERATE()
{
        Xnum=$1
        Xpar=$2
        nskip=$3
        nproc=$4
        ### File format: fhc.numu.skdetsim.0026Gd.NEUTcountXXX.partYYY.zbs
        ### XXX is 000-099
        ### YYY is 001-003 (000 also exists, but do not use because it is empty)
        Xnum=`printf "%03d" $Xnum`
        part=`printf "%03d" $Xpar`
        echo " "
        echo "----------------------------------------------------------------------------------------------"
        echo "[###### fiTQun ######]  Input : fhc.numu.skdetsim.0026Gd.NEUTcount$Xnum.part$part.zbs"
        echo "[###### fiTQun ######]  Output: fhc.numu.fiTQun.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.zbs"
        echo "[###### fiTQun ######]  Skip  : Start from $nskip event"
        echo "----------------------------------------------------------------------------------------------"
        echo " "

        ### Input file from SKDETSIM
        INPUT=/disk02/usr6/sedi/SKDETSIM/output/fhc.numu.skdetsim.0026Gd.NEUTcount$Xnum.part$part.zbs
        ### output file from fiTQun
        OUTPUT=/disk02/usr6/sedi/fiTQun/output/fhc.numu.fiTQun.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.zbs

        ### Execution of fiTQun
                $SOURCE $INPUT\
                -p $CARD\
                -s $nskip\
                -n $nproc\
                -o $OUTPUT >& /disk02/usr6/sedi/fiTQun/Log/log.fhc.numu.0026Gd.NEUTcount$Xnum$count.part$part.skip$nskip.txt

        if [ $? = 0 ]; then
                echo "[###### fiTQun ######]  fiTQun is finished."
        else
                echo "[###### fiTQun ######]  ERROR: fiTQun is aborted."
        fi
}

### The second index means nproc (see above)
### 44 should be replaced into 0-9
### Replacement is done by qsub_fiTQun.py
#GENERATE 44 1 650 100
GENERATE 44 1 650 50
#COMMENTOUT
