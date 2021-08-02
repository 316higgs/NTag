#!/bin/bash

source /usr/local/sklib_gcc4.8.5/bashenv_gcc4.8.5_skofl_19b+atmpd_19b
export LD_LIBRARY_PATH=${SKOFL_ROOT}/lib:${ROOTSYS}/lib:$LD_LIBRARY_PATH

top_dir=/disk01/usr5/rakutsu/t2k/mc/t2ksk_prod_19b
exe_fnt=$top_dir/scripts/fillnt_simple.sh
exe_h2r=$SKOFL_ROOT/bin/h2root

TEMPLATE()
{
	Xcount=$1
    Xpart=$2
    Xskip=$3
    Xcount=`printf "%03d" $Xcount`
    Xpart=`printf "%03d" $Xpart`

    ### Input from fiTQun(.zbs file)
    PREFIX=fhc.numu.fiTQun.0026Gd.NEUTcount$Xcount.part$Xpart.skip$Xskip
    INPUT=/disk02/usr6/sedi/fiTQun/output/${PREFIX}.zbs

    ### Conversion zbs file into hbook file
    OUTPUT=/disk02/usr6/sedi/fiTQun/converted_output/${PREFIX}.hkb

    ### Conversion hbk file into root file
    SECOND_INPUT=$OUTPUT
    SECOND_OUTPUT=/disk02/usr6/sedi/fiTQun/converted_output/${PREFIX}.root

    $exe_fnt -o $OUTPUT\
                $INPUT

    /usr/bin/sleep 1

    $exe_h2r $SECOND_INPUT\
             $SECOND_OUTPUT\
             1 1 0 8000 0

    echo "----------------------------------------------------------------------------------------------"
    echo " Input zbs file from fiTQun: $INPUT"
    echo " -> hbook file: $OUTPUT"
    echo "    -> root file: $SECOND_OUTPUT"
    echo "----------------------------------------------------------------------------------------------"
}


#<<COMMENTOUT
for ((count=0;count<100;count++))
do
	for ((part=1;part<4;part++))
	do
		for ((skip=0;skip<10;skip++))
		do
			nskip=$((skip*100))
			TEMPLATE $count $part $nskip
		done
	done
done
#COMMENTOUT

#TEMPLATE 0 1 0

### When run it in NQS...
### /usr/local/bin/qsub -e /disk02/usr6/sedi/fiTQun/converted_Log/err.fhc.numu.0026Gd.conversion.log -o /disk02/usr6/sedi/fiTQun/converted_Log/fhc.numu.0026Gd.conversion.log ./example_fillnt.sh


#TEMPLATE 0 1 0

<< COMMENTOUT
### Input from fiTQun(.zbs file)
#PREFIX=fhc.num.fiTQun.0026Gd.NEUTcount000.part001
PREFIX=fhc.numu.fiTQun.0026Gd.NEUTcount000.part001.skip0
#in_file_fnt=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/fiTQunoutput/${PREFIX}.zbs
in_file_fnt=/disk02/usr6/sedi/fiTQun/output/${PREFIX}.zbs

### conversion into hbook file
#OUTDIR=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/LENtupleoutput/Ntuplecheck
#OUTDIR=/disk02/usr6/sedi/fiTQun/converted_output
#out_file_fnt=${OUTDIR}/${PREFIX}.hkb
out_file_fnt=/disk02/usr6/sedi/fiTQun/converted_output/${PREFIX}.hkb

### conversion above hbook file into root file
in_file_h2r=$out_file_fnt
#out_file_h2r=$OUTDIR/${PREFIX}.root
out_file_h2r=/disk02/usr6/sedi/fiTQun/converted_output/${PREFIX}.root

$exe_fnt -o $out_file_fnt\
		  $in_file_fnt

/usr/bin/sleep 1

$exe_h2r $in_file_h2r\
		  $out_file_h2r\
		  1 1 0 8000 0
COMMENTOUT