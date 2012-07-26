#############
TARGET=c64xplus
CORE=c64plus 
BUILD= release
CGTOOLS=ti
C64XX_DERIVATIVE= c64xplus_intc
BIG_ENDIAN=0

#######################################

CSL3X_ROOT_DIR=\vobs\csl3x
include .\Makefile.inc

CSL_LIB_NAME = csl_$(C64XX_DERIVATIVE).lib

ifeq ($(BIG_ENDIAN), 1)
CSL_LIB_NAME = csl_$(C64XX_DERIVATIVE)e.lib
endif

MODULES = intc common
	ALL_OBJS = \
	$(CSL3X_ROOT_DIR)/src/intc/obj/$(CORE)/$(BUILD)/*.o  \
        $(CSL3X_ROOT_DIR)/src/common/obj/$(CORE)/$(BUILD)/csl_version.o

buildall: $(MODULES)
	$(AR) $(AR_OPTS) $(CSL_LIB_NAME) $(ALL_OBJS)
	echo "Built the lib $(CSL_LIB_NAME)"

common:
	cd $(CSL3X_ROOT_DIR)\src\common && $(MAKE) $(MAKE_FLAGS) -f Makefile objs DSTDIR=$(DSTDIR) PROCFILE=$(PROCFILE) CGTOOLS=$(CGTOOLS) CORE=$(CORE) BUILD=$(BUILD) TARGET=$(TARGET) CSL3X_ROOT_DIR=$(CSL3X_ROOT_DIR) C64XX_DERIVATIVE=$(C64XX_DERIVATIVE)

intc:
	cd $(CSL3X_ROOT_DIR)\src\intc && $(MAKE) $(MAKE_FLAGS) -f Makefile objs DSTDIR=$(DSTDIR) PROCFILE=$(PROCFILE) CGTOOLS=$(CGTOOLS) CORE=$(CORE) BUILD=$(BUILD) TARGET=$(TARGET) CSL3X_ROOT_DIR=$(CSL3X_ROOT_DIR) C64XX_DERIVATIVE=$(C64XX_DERIVATIVE)

cleanall:
	echo "Cleaning up all the obj dirs"
	cd $(CSL3X_ROOT_DIR)\src\intc && $(MAKE) $(MAKE_FLAGS) -f Makefile clean DSTDIR=$(DSTDIR) PROCFILE=$(PROCFILE) CGTOOLS=$(CGTOOLS) CORE=$(CORE) BUILD=$(BUILD) TARGET=$(TARGET) CSL3X_ROOT_DIR=$(CSL3X_ROOT_DIR)
	cd $(CSL3X_ROOT_DIR)\src\common && $(MAKE) $(MAKE_FLAGS) -f Makefile clean DSTDIR=$(DSTDIR) PROCFILE=$(PROCFILE) CGTOOLS=$(CGTOOLS) CORE=$(CORE) BUILD=$(BUILD) TARGET=$(TARGET) CSL3X_ROOT_DIR=$(CSL3X_ROOT_DIR)
