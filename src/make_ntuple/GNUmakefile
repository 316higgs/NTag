#
#  In case of building locally, set SKOFL_ROOT variable 
#      setenv SKOFL_ROOT   ... 
#  or directly set in this makefile 
# SKOFL_ROOT = /skofl
#
ifndef SKOFL_ROOT
  SKOFL_ROOT = ../../../..
endif

include $(SKOFL_ROOT)/config.gmk

LOCAL_INC = -I. -I$(NEUT_ROOT)/include

LOCAL_LIBS = -L. -l$(LIBNAME) \
                 -L$(NEUT_ROOT)/lib/Linux_pc -lzbsfns -lneutcore \
#		 $(APLIB)
#		-lsklowe_7.0 -lwtlib_5.1 -lbonsai_3.3 -lstmu -lska
#		-L/home/iida/relic/lib -lrelic  -lsollib_4.0


#APLIB =  -lapdrlib -lpolfit -laplib -lringlib  -ltp -ltf  -lringlib  \
#         -laplib -lmsfit -lmslib -lseplib -lmsfit -lprtlib -lmuelib \
#         -lffit -lodlib -lstmu -laplowe -lpolfit -lexpq  -laplib -lska 



#  Objects
CC_FILES := $(wildcard *.cc)
F_FILES := $(wildcard *.F)
H_FILES := $(wildcard *.h)

OBJS := $(notdir $(H_FILES:.h=.o))
FOBS := $(notdir $(F_FILES:.F=.o))

EXE = make_t2klowe_ntuple
LIBNAME = ntuplemaker


emptyrule:: $(EXE)

$(EXE) : lib$(LIBNAME).a $(EXE).o


lib$(LIBNAME).a : $(OBJS) $(FOBS)
	$(RM) $@
	$(AR) $@ $^
	$(RANLIB) $@


.cc.so: 
	$(CXX) $(CXXFLAGS) -c $*.cc 

#
#  Targets 
#

.PHONY:  clean setup includes install.includes depend lib install.lib exec install.exec


clean::
	$(RM) *.o *~ *.a *.exe *.so core* $(EXE)

setup::

lib:: lib$(LIBNAME).a $(OBJS)



