#!/bin/bash

source /usr/local/sklib_gcc8/bashenv_gcc8_skofl_21b+atmpd_21b

ANAT2KSK_ROOT=/disk02/usr6/sedi/anat2ksk
T2KGdANA=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis
DECAYE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis/src/DecayeBox

if [ $?LD_LIBRARY_PATH ] ; then
	LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$ANAT2KSK_ROOT/lib:$T2KGdANA/lib"
else
	LD_LIBRARY_PATH="$ANAT2KSK_ROOT/lib:$T2KGdANA/lib"
fi

PATH="/usr/local/texlive/2021/bin/x86_64-linux:$PATH"

