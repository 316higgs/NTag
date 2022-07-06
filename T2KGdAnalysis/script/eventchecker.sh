#!/bin/bash

make cleanevent
make event.exe

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

./event.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount066.part001.skip100.root\
            $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount066.part001.skip100.root\
            $ANALYSISSTAGE/output/test.root\
            $ANALYSISSTAGE/result/test.txt\
            $ANALYSISSTAGE/result/test.txt\
            -MCType Gd\
            -ETAG ON\
            -BEAMMODE FHC\
            -OSCCH NUMU