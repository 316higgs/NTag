#!/bin/tcsh -f

set numode=$1
set oscchan=$2
set num=$3

source /usr/local/sklib_gcc4.8.5/cshenv_gcc4.8.5_skofl_16c+atmpd_16c

set top_dir=/disk01/usr5/rakutsu/t2k/Neutron/work/nnn/t2ksk_neutron
set exe_prog=$top_dir/genCangPDF/src/mrgCAngHists

set in_dir=$top_dir/genCangPDF_RBNR6/files/ntag_root
set in_prefix=$numode.$oscchan.$num.
set in_postfix=.t2kfcfvFQ.wmupimicap.hntag_cang.root
set nmerged=100

set outfile=./canghist.mrg.$numode.$oscchan.$num.root

$exe_prog $in_dir $in_prefix $in_postfix $nmerged $outfile
/usr/bin/sleep 1
