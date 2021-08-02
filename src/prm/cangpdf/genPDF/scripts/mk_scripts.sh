#!/bin/bash

top_dir=/disk01/usr5/rakutsu/t2k/Neutron/work/nnn/t2ksk_neutron

MK_SHELL()
{
	g4mupimicap=$1
	numode=$2
	oscchan=$3
	num=$4

	if [ $g4mupimicap = with ]; then
		g4tmp=wmupimicap
	elif [ $g4mupimicap = without ]; then
		g4tmp=nomupimicap
	else
		echo $g4mupimicap "is not supported. "
		echo " -> EXIT "
		exit
	fi

	i=0
	while [ $i -lt 20 ]
	do
		tmp=`printf %03d $i`
		sub_start=`expr $i \* 5`
		sub_end=`expr $sub_start + 5`

		shell=cang.$numode.$oscchan.$num.$tmp.csh

#--- Make shell script for each $file w/ $nnumu>0 ---#
/usr/bin/cat > $shell << EOF
#!/bin/tcsh -f

set top_dir=$top_dir
set exe_ntag=\$top_dir/hntagRBNR/hntag.csh

set numode=$numode
set oscchan=$oscchan
set num=$num
set sub_start=$sub_start
set sub_end=$sub_end

set j=\$sub_start
while ( \$j < \$sub_end )
set sub=\`printf %03d \$j\`
set exe_dir=\$top_dir/genCangPDF_RBNR6/run/\$numode/\$oscchan/\$num.\$sub
set in_zbs_dir=\$top_dir/genCangPDF_RBNR6/files/in_zbs/$numode/$oscchan
set in_root_dir=\$top_dir/genCangPDF_RBNR6/files/in_root/$numode/$oscchan
set out_dir=\$top_dir/genCangPDF_RBNR6/files/ntag_root

set prefix=\${numode}.\$oscchan.\$num.\$sub.t2kfcfvFQ
set ntag_in_zbs=\$in_zbs_dir/\$prefix.${g4tmp}.cmb.zbs
set ntag_in_root=\$in_root_dir/\$prefix.root
set ntag_out=\$prefix.${g4tmp}.hntag_cang.root


cd \$top_dir/
/usr/bin/mkdir -p \$exe_dir
cd \$exe_dir/

/usr/bin/rm -f \$ntag_out
/usr/bin/cp \$ntag_in_zbs ./in_zbs.zbs
/usr/bin/cp \$ntag_in_root ./in_root.root

\$exe_ntag -i \$exe_dir/in_zbs.zbs -r \$exe_dir/in_root.root -o \$exe_dir/out_root.root --CAngPDF do_save_cang
/usr/bin/sleep 1


/usr/bin/mv out_root.root \$ntag_out
/usr/bin/mv -f \$ntag_out \$out_dir/ 

rm in_zbs.zbs
rm in_root.root

cd \$top_dir/
/usr/bin/rm -rf \$exe_dir
/usr/bin/sleep 1
set j=\`expr \$j + 1\`
end
EOF
/usr/bin/chmod +x $shell
qsub -eo -o /dev/null -q calib $shell

/usr/bin/rm $shell

i=`expr $i + 1`
done
/usr/bin/sleep 1
}

MK_SHELL with fhc numu_x_numu 005
MK_SHELL with fhc numu_x_nue 011
MK_SHELL with fhc nue_x_nue 013
MK_SHELL with fhc numubar_x_numubar 025
MK_SHELL with fhc numubar_x_nuebar 046
MK_SHELL with fhc nuebar_x_nuebar 041

MK_SHELL with rhc numu_x_numu 005
MK_SHELL with rhc numu_x_nue 041
MK_SHELL with rhc nue_x_nue 021
MK_SHELL with rhc numubar_x_numubar 014
MK_SHELL with rhc numubar_x_nuebar 051
MK_SHELL with rhc nuebar_x_nuebar 031
