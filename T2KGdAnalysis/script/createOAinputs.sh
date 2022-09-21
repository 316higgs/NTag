#!/bin/bash

make cleancreateOAinputs
make createOAinputs.exe

if [ ! -f ./createOAinputs.exe ]; then
  exit 2
fi

#make MeanMultiplicity.exe
#make PreScan.exe

PUREWATER=/home/rakutsu/disk2/t2k/regene_mc/files/fcfq_fqmr_root
#FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output/DeltaPforEmiss0Added
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

#./analysis1Rmu.exe $PUREWATER/fhc/numubar_x_numubar/neut.fhc.numubar_x_numubar.02\*.0\*.t2kfcFQ.root\
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

  #### costheta23 = 0.511 ####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.maximalmix.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.maximalmix.txt\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.maximalmix.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

  #### with muon angle ####
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.OAinput.cut1.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.OAinput.cut1.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.OAinput.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
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



