include $(SKOFL_ROOT)/config.gmk

CXXFLAGS += -std=c++11

OBJS  =

EXEC_FILES = 

all: $(EXEC_FILES)


mrgCAngHists: mrgCAngHists.o HistCherenkovAngle.o
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

genCAngPDF: genCAngPDF.o HistCherenkovAngle.o
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)


clean:
	$(RM) *.o $(OBJS) $(EXEC_FILES)
