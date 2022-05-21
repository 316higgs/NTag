#source /usr/local/sklib_gcc4.8.5/cshenv_gcc4.8.5_skofl_16c+atmpd_16c
source /usr/local/sklib_gcc8/cshenv_gcc8_skofl_21a+atmpd_21a

setenv ANAT2KSK_ROOT /disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk
setenv T2KGdANA /home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis
setenv DECAYE /home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis/src/DecayeBox

if ( $?LD_LIBRARY_PATH ) then
	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$ANAT2KSK_ROOT/lib:$T2KGdANA/lib
else
	setenv LD_LIBRARY_PATH $ANAT2KSK_ROOT/lib:$T2KGdANA/lib
endif

#setenv PATH /usr/local/texlive/2020/bin/x86_64-linux:${PATH}
setenv PATH /usr/local/texlive/2021/bin/x86_64-linux:${PATH}
