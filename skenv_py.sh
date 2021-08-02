top=/usr/local/sklib_gcc4.8.5

export SOFTVER="19b"
export SKOFL_ROOT=$top/skofl_${SOFTVER}
export CERN=$top/cern
export CERN_LEVEL=2005
export CERN_ROOT=$CERN/$CERN_LEVEL

export ROOTSYS=$top/root_v5.28.00h
export PYTHONPATH=$ROOTSYS/lib:${PYTHONPATH}
export ATMPD_ROOT=$top/atmpd_$SOFTVER

#export NEUTVER=neut_5.4.0
#export NEUTVER=neut_5.3.6.root_v5.28.00h
export NEUTVER=neut_5.3.3_Eb_patch
export NEUTROOT=/disk02/usr6/pmehta/ncgamma/mc/neut/$NEUTVER
export NEUT_ROOT=$NEUTROOT

export NEUTRON=1

export LD_LIBRARY_PATH="$SKOFL_ROOT/lib:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/disk02/usr6/pmehta/ncgamma/Prob3++:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="`$ROOTSYS/bin/root-config --libdir`:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/disk02/usr6/pmehta/ncgamma/T2KReWeight_v1r27p3/lib:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/disk02/usr6/pmehta/ncgamma/NIWGReWeight_v1r23p2:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/disk02/usr6/pmehta/ncgamma/mc/neut/neut_5.3.3_Eb_patch/lib/Linux_pc:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/disk02/usr6/pmehta/ncgamma/mc/skdetsim-skgd/geant4_work/tmp/Linux-g++/gtneut:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/usr/local/geant4.10/geant4.10.03.p02/lib64:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/usr/local/geant4.10/geant4.10.03.p02/share/Geant4-10.3.2/geant4make/config:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="/usr/local/sklib_gcc4.8.5/skofl_19a/src/root2zbs:$LD_LIBRARY_PATH"
#export LD_LIBRARY_PATH="/usr/local/sklib_gcc4.8.5/skofl_19b/const/connection.super.dat:$LD_LIBRARY_PATH"
#export LD_LIBRARY_PATH="/usr/local/sklib_gcc4.8.5/skofl_19b/const/connection.super.sk-4.dat:$LD_LIBRARY_PATH"
echo "here is skenv_py.sh echo"
echo $LD_LIBRARY_PATH
export PATH="$SKOFL_ROOT/bin:$ATMPD_ROOT/bin:$ROOTSYS/bin:$CERN_ROOT/bin:$PATH"
export SKPATH="${SKOFL_ROOT}/const:${ATMPD_ROOT}/const:${SKOFL_ROOT}/const/lowe:/skam/const"
export G4ENSDFSTATEDATA=/usr/local/sklib_gcc4.8.5/geant4.10.03.p01/share/Geant4-10.3.1/data/G4ENSDFSTATE2.1/
export SKDETSIMDIR=/disk02/usr6/pmehta/ncgamma/mc/skdetsim-skgd/

