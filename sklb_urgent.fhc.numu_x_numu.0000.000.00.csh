#!/bin/tcsh -f

source /usr/local/sklib_g77/cshenv_g77_skofl_14c+atmpd_14c

set numode=fhc
set oscchan=numu_x_numu
set num=0000
set sub=000
set nskip=0
set nproc=100
set ssub=00


set top_dir=/disk01/usr5/rakutsu/t2k/mc/t2ksk_prod_19b
set exe_dir=$top_dir/exe/$numode/$oscchan/$num/$sub/$ssub
set exe_fq=$ATMPD_ROOT/bin/runfiTQun
set fqcard=$top_dir/scripts/fiTQun.parameters.dat

set in_dir=/disk01/usr5/rakutsu/t2k/mc/t2ksk_prod_19b
set in_file_dir=$in_dir/out/apzbs/$numode/$oscchan
set in_file=$in_file_dir/ap.$numode.$oscchan.$num.$sub.zbs
set out_file=fqv4r0.$numode.$oscchan.$num.$sub.$ssub.zbs
set out_dir=$top_dir/out/fqzbs
set log_dir=$top_dir/out/log/fqzbs/$numode/$oscchan
set fq_log=fqv4r0.$numode.$oscchan.$num.$sub.$ssub.log

/usr/bin/rm -rf $exe_dir
/usr/bin/mkdir -p $exe_dir
cd $exe_dir

/usr/bin/sleep 3

$exe_fq $in_file\
		  -p $fqcard\
		  -s $nskip\
		  -n $nproc\
		  -o $out_file >& $fq_log

/usr/bin/sleep 3
/usr/bin/mv -f $out_file $exe_dir/../
/usr/bin/mv -f $fq_log $log_dir/

cd $top_dir/
/usr/bin/rm -rf $exe_dir
