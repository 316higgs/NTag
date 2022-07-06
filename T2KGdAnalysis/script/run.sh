#!/bin/bash

make clean
make 

if [ ! -f ./analysis1Rmu.exe ]; then
  exit 2
fi

#make MeanMultiplicity.exe
#make PreScan.exe

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
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/noToFoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   ./output/fhc/fhc.numu.etagOFF.root\
#                   ./result/fhc/fhc.numu.neutrino.etagOFF.txt\
#                   ./result/fhc/fhc.numu.ntag.etagOFF.txt\
#                   -MCType Gd\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

#<<COMMENTOUT
#./analysis1Rmu.exe $PUREWATER/fhc/numu_x_numu/neut.fhc.numu_x_numu.00\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/numu_x_numu.water.root\
#                   $ANALYSISSTAGE/result/fhc/numu_x_numu.water.txt\
#                   $ANALYSISSTAGE/result/fhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

#./analysis1Rmu.exe $PUREWATER/rhc/numubar_x_numubar/neut.rhc.numubar_x_numubar.0\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.water.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.water.txt\
#                   $ANALYSISSTAGE/result/fhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMUBAR

#./analysis1Rmu.exe $PUREWATER/rhc/numubar_x_numubar/neut.rhc.numubar_x_numubar.0\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/rhc/rhc.numubar_x_numubar.water.root\
#                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.water.txt\
#                   $ANALYSISSTAGE/result/rhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE RHC\
#                   -OSCCH NUMUBAR



##### FHC numu -> numu Gd MC #####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagOFF.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagOFF.txt\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagOFF.txt\
#                   -MCType Gd\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU


##### FHC numubar -> numubar MC #####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/rhc.numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/rhc.numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   ./output/fhc/fhc.numubar_x_numubar.etagON.root\
#                   ./result/fhc/fhc.numubar_x_numubar.neutrino.etagON.txt\
#                   ./result/fhc/fhc.numubar_x_numubar.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMUBAR



##### RHC numubar -> numubar Gd MC #####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/rhc.numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/rhc.numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/rhc/Nosel.rhc.numubar.etagON.root\
#                   $ANALYSISSTAGE/result/rhc/Nosel.rhc.numubar.neutrino.etagON.txt\
#                   $ANALYSISSTAGE/result/rhc/Nosel.rhc.numubar.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE RHC\
#                   -OSCCH NUMUBAR

#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/rhc.numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/rhc.numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   ./output/numubar.etagON.root\
#                   ./result/numubar.neutrino.etagON.txt\
#                   ./result/numubar.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE RHC\
#                   -OSCCH NUMUBAR


#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/PreOptimized/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   ./output/etagON.optimized.root\
#                   ./result/etagON.optimized.txt\
#                   -MCType Gd\
#                   -ETAG ON
#COMMENTOUT

<<COMMENTOUT
#TWIDTH=120, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan2/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 120\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=160, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan0/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 160\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/tageoption//fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=240, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan1/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 240\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=280, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan3/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 280\
              -NHITSTH 25\
              -WINDOW 0
echo " "


#TWIDTH=200, NHITSTH=10
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan0/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 10\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=15
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan1/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 15\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/tageoption//fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=35
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan2/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 35\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=45
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan3/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 45\
              -WINDOW 0
echo " "
COMMENTOUT

#./MeanMultiplicity.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       $NTAGDIR/noToFoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       ./output/MultiplicityTest.root\
#                       ./result/MultiplicityTest.txt\
#                       -MCType Gd\
#                       -ETAG OFF
