#!/bin/bash

make cleanprotoanalysis
make protoanalysis.exe

if [ ! -f ./analysis1Rmu.exe ]; then
  exit 2
fi


FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/OldNTag
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
./protoanalysis.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part001.skip0.root\
                   $NTAGDIR/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part001.skip0.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.oldNtag.cut1.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.oldNtag.cut1.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.oldNtag.cut1.txt\
                   -MCType Gd\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUMU


##### FHC numubar -> numubar MC #####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   ./output/fhc/fhc.numubar_x_numubar.etagON.root\
#                   ./result/fhc/fhc.numubar_x_numubar.neutrino.etagON.txt\
#                   ./result/fhc/fhc.numubar_x_numubar.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMUBAR




##### RHC #####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.etagON.cut1.root\
#                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.etagON.cut1.txt\
#                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.etagON.cut1.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE RHC\
#                   -OSCCH NUMU

#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/rhc/rhc.numubar_x_numubar.etagON.root\
#                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.neutrino.etagON.txt\
#                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE RHC\
#                   -OSCCH NUMUBAR


#COMMENTOUT
