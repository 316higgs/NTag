#!/bin/tcsh -f

source /usr/local/sklib_gcc4.8.5/cshenv_gcc4.8.5_skofl_16c+atmpd_16c

set top_dir=/disk01/usr5/rakutsu/t2k/Neutron/work/nnn/t2ksk_neutron/genCangPDF_RBNR6
set exe_mrg=$top_dir/scripts/mrgCAngHists.csh
set exe_gen=$top_dir/../genCangPDF/src/genCAngPDF


$exe_mrg fhc numu_x_numu 005
$exe_mrg fhc numu_x_nue 011
$exe_mrg fhc nue_x_nue 013
$exe_mrg fhc numubar_x_numubar 025
$exe_mrg fhc numubar_x_nuebar 046
$exe_mrg fhc nuebar_x_nuebar 041
$exe_mrg rhc numu_x_numu 005
$exe_mrg rhc numu_x_nue 041
$exe_mrg rhc nue_x_nue 021
$exe_mrg rhc numubar_x_numubar 014
$exe_mrg rhc numubar_x_nuebar 051
$exe_mrg rhc nuebar_x_nuebar 031
/usr/bin/sleep 1


set gen_out=cangpdf.hntagRBNR6.root
set dir=`pwd`
/usr/bin/rm -f $gen_out

$exe_gen $gen_out\
		 $dir/canghist.mrg.fhc.numu_x_numu.005.root\
		 $dir/canghist.mrg.fhc.numu_x_nue.011.root\
		 $dir/canghist.mrg.fhc.nue_x_nue.013.root\
		 $dir/canghist.mrg.fhc.numubar_x_numubar.025.root\
		 $dir/canghist.mrg.fhc.numubar_x_nuebar.046.root\
		 $dir/canghist.mrg.fhc.nuebar_x_nuebar.041.root\
		 $dir/canghist.mrg.rhc.numu_x_numu.005.root\
		 $dir/canghist.mrg.rhc.numu_x_nue.041.root\
		 $dir/canghist.mrg.rhc.nue_x_nue.021.root\
		 $dir/canghist.mrg.rhc.numubar_x_numubar.014.root\
		 $dir/canghist.mrg.rhc.numubar_x_nuebar.051.root\
		 $dir/canghist.mrg.rhc.nuebar_x_nuebar.031.root

/usr/bin/sleep 1
/usr/bin/rm -f canghist.mrg.*.root
/usr/bin/mv $gen_out $top_dir/pdf/
