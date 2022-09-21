include $(SKOFL_ROOT)/config.gmk

LOCAL_LIBS += -L$(ANAT2KSK_ROOT)/lib -lcc0pinumu
LOCAL_LIBS += -L$(T2KGdANA)/lib -ldecayebox
LOCAL_LIBS += -L$(T2KGdANA)/lib -lgd1rmuonselection
LOCAL_LIBS += -L$(T2KGdANA)/lib -lneutrinooscillation
LOCAL_LIBS += -L$(T2KGdANA)/lib -ldistanceviewer
LOCAL_LIBS += -L$(T2KGdANA)/lib -lntaganalysis
LOCAL_LIBS += -L$(T2KGdANA)/lib -ltreemanager
LOCAL_LIBS += -L$(T2KGdANA)/lib -lnninputvariables
LOCAL_LIBS += -L$(ATMPD_ROOT)/lib -lThreeProb
LOCAL_INC += -I$(ANAT2KSK_ROOT)/include
CXXFLAGS += -std=c++11

analysis1Rmu.exe: analysis1Rmu.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

protoanalysis.exe: protoanalysis.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

MeanMultiplicity.exe: MeanMultiplicity.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

createOAinputs.exe: createOAinputs.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

PreScan.exe: PreScan.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

event.exe: event.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

#NoSelection.exe: NoSelection.o
#	$(RM) .$@
#	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

getNNvariables.exe: getNNvariables.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

cleanevent:
	$(RM) evevnt.o event.exe

cleanNoSelection:
	$(RM) NoSelection.o NoSelection.exe

cleanprotoanalysis:
	$(RM) protoanalysis.o protoanalysis.exe

cleancreateOAinputs:
	$(RM) createOAinputs.o createOAinputs.exe

clean:
	$(RM) *.o *.exe