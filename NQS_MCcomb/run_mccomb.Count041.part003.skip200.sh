#!/bin/bash

### Current directroy
TOPDIR=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC

### source for necessary Environment variables
source $TOPDIR/skenv_py.sh

SOURCE=/disk02/usr6/pmehta/ncgamma/injedgedbl/dummyinj.csh

tbkgduration=496000 # back-up safety useconds: 1 usec at bgn, 1 usec at end
tbkginsert=18000

GENERATE()
{
        Xnum=$1
        Xpar=$2
        nskip=$3
        nindex=$4
        Xnum=`printf "%03d" $Xnum`
        part=`printf "%03d" $Xpar`
        index=`printf "%03d" $nindex`
        echo " "
        echo "----------------------------------------------------------------------------------------------"
        echo "[###### MCcomb ######]  Input : fhc.numu.fiTQun.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.zbs"
        echo "[###### MCcomb ######]  Output: fhc.numu.mccomb.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.zbs"
        echo "----------------------------------------------------------------------------------------------"
        echo " " 
        INPUT=/disk02/usr6/sedi/fiTQun/output/fhc.numu.fiTQun.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.zbs
        OUTPUT=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.zbs
        SBI=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.sbi

        INDEX=/disk02/usr6/pmehta/ncgamma/mccomb/work/index/fhc/numu.dummyidx.$index.txt

        ### Execution of MCcomb (1st index: index test file, 2nd index: value of tbkgduration, 3rd index: value of tblginsert, 
        ### 4th index: input from BONSAI, 5th index: MCcomb output, 6th index: .sbi file)
        $SOURCE $INDEX\
                $tbkgduration\
                $tbkginsert\
                $INPUT\
                $OUTPUT\
                $SBI >& /disk02/usr6/sedi/MCcomb/Log/log.fhc.numu.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.txt

        if [ $? = 0 ]; then
                echo "[###### MCcomb ######]  MCcomb is finished."
        else
                echo "[###### MCcomb ######]  ERROR: MCcomb is aborted."
        fi
}


GENERATE 41 3 200 41


<<COMMENTOUT
### input file (inherit from BONSAI)
#INPUT=$TOPDIR/BONSAIoutput/test_BONSAI.zbs
INPUT=/disk02/usr6/sedi/fiTQun/output/fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.zbs

### The directory for mccomb outputs
#OUTPUTDIR=$TOPDIR/MCcomboutput
### File format of MCcomb outputs (example)
#OUTPUT=$OUTPUTDIR/test_mccomb.zbs
OUTPUT=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount000.part001.skip0.zbs

#SBI=$OUTPUTDIR/test_mccomb.sbi
SBI=/disk02/usr6/sedi/MCcomb/output/fhc.numu.mccomb.0026Gd.NEUTcount000.part001.skip0.sbi

### MCcomb source
SOURCE=/disk02/usr6/pmehta/ncgamma/injedgedbl/dummyinj.csh

### Execution of MCcomb (1st index: index test file, 2nd index: value of tbkgduration, 3rd index: value of tblginsert, 
### 4th index: input from BONSAI, 5th index: MCcomb output, 6th index: .sbi file)
$SOURCE $INDEX\
        $tbkgduration\
        $tbkginsert\
        $INPUT\
        $OUTPUT\
        $SBI
COMMENTOUT