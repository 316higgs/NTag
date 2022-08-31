#!/bin/bash

make clean
make getNNvariables.exe

if [ ! -f ./getNNvariables.exe ]; then
  exit 2
fi

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

#./getNNvariables.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.root\
#                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.txt\
#                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMU

./getNNvariables.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.muminus.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.muminus.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.muminus.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU

#./getNNvariables.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.postNN.root\
#                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.postNN.txt\
#                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.postNN.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMU


#./getNNvariables.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     ./output/fhc/fhc.numubar_x_numubar.preNN.muminus.root\
#                     ./result/fhc/fhc.numubar_x_numubar.neutrino.preNN.muminus.txt\
#                     ./result/fhc/fhc.numubar_x_numubar.ntag.preNN.muminus.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMUBAR

#./getNNvariables.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     ./output/fhc/fhc.numubar_x_numubar.postNN.root\
#                     ./result/fhc/fhc.numubar_x_numubar.neutrino.postNN.txt\
#                     ./result/fhc/fhc.numubar_x_numubar.ntag.postNN.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMUBAR

