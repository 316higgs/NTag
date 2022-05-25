#!/bin/bash

make clean
make 

if [ ! -f ./analysis1Rmu.exe ]; then
  exit 2
fi

make MeanMultiplicity.exe
make PreScan.exe

FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining

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
#                   ./output/test.root\
#                   ./result/test.txt\
#                   -MCType Gd\
#                   -ETAG OFF

./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/etagONtest.root\
                   ./result/etagON.txt\
                   -MCType Gd\
                   -ETAG ON

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
COMMENTOUT

#./MeanMultiplicity.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       $NTAGDIR/noToFoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       ./output/MultiplicityTest.root\
#                       ./result/MultiplicityTest.txt\
#                       -MCType Gd\
#                       -ETAG OFF
