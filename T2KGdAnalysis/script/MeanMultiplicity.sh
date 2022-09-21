#!/bin/bash

make clean
make MeanMultiplicity.exe

if [ ! -f ./MeanMultiplicity.exe ]; then
  exit 2
fi

FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining

#./MeanMultiplicity.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       ./output/fhc/fhc.numu_x_numu.MeanMultiplicity.root\
#                       ./result/fhc/fhc.numu_x_numu.MeanMultiplicity.txt\
#                       -MCType Gd\
#                       -ETAG ON\
#                       -BEAMMODE FHC\
#                       -OSCCH NUMU

#./MeanMultiplicity.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       ./output/fhc/fhc.numubar_x_numubar.MeanMultiplicity.root\
#                       ./result/fhc/fhc.numubar_x_numubar.MeanMultiplicity.txt\
#                       -MCType Gd\
#                       -ETAG ON\
#                       -BEAMMODE FHC\
#                       -OSCCH NUMUBAR

#./MeanMultiplicity.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                       ./output/rhc/rhc.numu_x_numu.MeanMultiplicity.root\
#                       ./result/rhc/rhc.numu_x_numu.MeanMultiplicity.txt\
#                       -MCType Gd\
#                       -ETAG ON\
#                       -BEAMMODE RHC\
#                       -OSCCH NUMU

./MeanMultiplicity.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                       $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                       ./output/rhc/rhc.numubar_x_numubar.MeanMultiplicity.root\
                       ./result/rhc/rhc.numubar_x_numubar.MeanMultiplicity.txt\
                       -MCType Gd\
                       -ETAG ON\
                       -BEAMMODE RHC\
                       -OSCCH NUMUBAR