include $(SKOFL_ROOT)/config.gmk

LOCAL_LIBS += -L$(ANAT2KSK_ROOT)/lib -lcc0pinumu
LOCAL_LIBS += -L$(T2KGdANA)/lib -ldecayebox
LOCAL_LIBS += -L$(T2KGdANA)/lib -lgd1rmuonselection
LOCAL_LIBS += -L$(T2KGdANA)/lib -lneutrinooscillation
LOCAL_LIBS += -L$(T2KGdANA)/lib -ldistanceviewer
LOCAL_LIBS += -L$(T2KGdANA)/lib -lntaganalysis
LOCAL_LIBS += -L$(ATMPD_ROOT)/lib -lThreeProb
LOCAL_INC += -I$(ANAT2KSK_ROOT)/include
CXXFLAGS += -std=c++11

analysis1Rmu.exe: analysis1Rmu.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

MeanMultiplicity.exe: MeanMultiplicity.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

PreScan.exe: PreScan.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) *.o *.exe