#!/bin/bash

make cleanNoSelection
make NoSelection.exe

if [ ! -f ./NoSelection.exe ]; then
  exit 2
fi


PUREWATER=/home/rakutsu/disk2/t2k/regene_mc/files/fcfq_fqmr_root
FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining
ANALYSISSTAGE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis

######
# 1st index: fiTQun input
# 2nd index: NTag input
# 3rd index: ROOT output 
# 4th index: Result summary .txt output
# 5th index: -MCType(fixed)
# 6th index: Gd/Water
# 7th index: -ETAG(fixed)
# 8th index: decay-e-tagging ON/OFF
######

##### FHC numu -> numu Gd MC #####
#./NoSelection.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/Nosel.fhc.numu.etagON.root\
#                   $ANALYSISSTAGE/result/fhc/Nosel.fhc.numu.neutrino.etagON.txt\
#                   $ANALYSISSTAGE/result/fhc/Nosel.fhc.numu.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

##### FHC numubar -> numubar MC #####
./NoSelection.exe $FITQUNDIR/0026Gd.numubar/rhc.numubar.fiTQun.0026Gd.NEUTcount09\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/rhc.numubar.ntag.0026Gd.NEUTcount09\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.etagON.NoSel.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.etagON.NoSel.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.etagON.NoSel.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR


