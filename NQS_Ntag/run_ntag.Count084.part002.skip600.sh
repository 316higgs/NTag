#!/bin/bash

### Current directroy
TOPDIR=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC

### source for necessary Environment variables
source $TOPDIR/skenv_py.sh

SOURCE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/ntag/ntag_mc/ntag_mc

GENERATE() {
        Xnum=$1
        Xpar=$2
        nskip=$3
        Xnum=`printf "%03d" $Xnum`
        part=`printf "%03d" $Xpar`
        echo " "
        echo "---------------------------------------------------------------------------------------------------"
        echo "[###### n-tagging ######]  Input: fhc.numu.lentuple.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root"
        echo "[###### n-tagging ######]  Output: fhc.numu.ntag.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root"
        echo "                                   nsig_fhc.numu.ntag.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root"
        echo "                                   nbkg_fhc.numu.ntag.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root"
        echo "---------------------------------------------------------------------------------------------------"
        echo " "

        ### Input file from LENtuple
        INPUT=/disk02/usr6/sedi/LENtuple/output/fhc.numu.lentuple.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root
        ### output file
        OUTPUT=/disk02/usr6/sedi/Ntag/output/fhc.numu.ntag.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root
        BKG=/disk02/usr6/sedi/Ntag/output/fhc.numu.ntag_bkg.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root
        SIG=/disk02/usr6/sedi/Ntag/output/fhc.numu.ntag_sig.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.root

        ### Execution of Ntag
        $SOURCE $INPUT\
                $OUTPUT >& /disk02/usr6/sedi/Ntag/Log/log.fhc.numu.0026Gd.NEUTcount$Xnum.part$part.skip$nskip.txt

        if [ $? = 0 ]; then
                echo "[###### n-tagging ######]  N-tag is finished."
        else
                echo "[###### n-tagging ######]  ERROR: N-tag is aborted."
        fi
}

GENERATE 84 2 600



<<COMMENTOUT
### input file from LENtuple
#INPUT=LENtupleoutput/test_lentuple.root
#INPUT=/disk02/usr6/pmehta/lemc_Gd/flux.13anom.run1to9.fhc_neut.533.modified_skdetsim.dwallm50.gcalor_Gd/lentuple/lentp_numu.ncgamma_flux13a_neut533.000.root
#INPUT=LENtupleoutput/test.root
INPUT=/disk02/usr6/sedi/LENtuple/output/fhc.numu.lentuple.0026Gd.NEUTcount000.part001.skip0.root

### The directory for n-tagging outputs
#OUTPUTDIR=$TOPDIR/ntagoutput
### File format of n-tagging
#OUTPUT=$OUTPUTDIR/test_ntag0618_Pruthvi.root
OUTPUT=/disk02/usr6/sedi/Ntag/output/fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root
#BKG=test_ntag_bkg0618_Pruthvi.root
BKG=/disk02/usr6/sedi/Ntag/output/bkg/fhc.numu.ntag_bkg.0026Gd.NEUTcount000.part001.skip0.root
#SIG=test_ntag_sig0618_Pruthvi.root
SIG=/disk02/usr6/sedi/Ntag/output/signal/fhc.numu.ntag_sig.0026Gd.NEUTcount000.part001.skip0.root

### n-tag source file
#SOURCE=/disk02/usr6/pmehta/ntag_mc/ntag_mc
SOURCE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/ntag/ntag_mc/ntag_mc

### Execution of n-tagging (1st index: input from LENtuple, 2nd index: n-tag output)
$SOURCE $INPUT\
        $OUTPUT #>& /disk02/usr6/sedi/Ntag/Log/fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.txt

COMMENTOUT
