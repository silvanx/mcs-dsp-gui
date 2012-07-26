################  c64xx+ compiler and options ##########################
debug_CC=cl6x
debug_CC_OPTS= -mv6400+ -mo -ml3 -pdr -pdv -q -k -g -eo.o -fr$(MODULE_OBJ_DIR) -fs$(MODULE_OBJ_DIR) $(INC_DIR) -D$(C64XX_DERIVATIVE)
debug_ASM=cl6x
debug_ASM_OPTS= -mv6400+ -pdr -pdv -q -g -mo -ml3 -eo.o -fr$(MODULE_OBJ_DIR) -fs$(MODULE_OBJ_DIR) $(INC_DIR)
debug_AR= ar6x
debug_AR_OPTS= r 
debug_LNK= lnk6x 
debug_LNK_OPTS= -q -c -w -x 

release_CC=cl6x
release_CC_OPTS= -mv6400+ -mo -ml3 -o3 -q -k -eo.o -fr$(MODULE_OBJ_DIR) -fs$(MODULE_OBJ_DIR) $(INC_DIR) -D$(C64XX_DERIVATIVE)
release_ASM=cl6x
release_ASM_OPTS= -mv6400+ -mo -ml3 -o3 -q -k -eo.o -fr$(MODULE_OBJ_DIR) -fs$(MODULE_OBJ_DIR) $(INC_DIR)
release_AR= ar6x
release_AR_OPTS= r 
release_LNK= lnk6x 
release_LNK_OPTS= -q -c -w -x 

ifeq ($(C64XX_DERIVATIVE),c6455)
CSL_LIB=csl_c6455.lib
endif

ifeq ($(C64XX_DERIVATIVE),c6454)
CSL_LIB=csl_c6454.lib
endif

ifeq ($(C64XX_DERIVATIVE),c6482)
CSL_LIB=csl_c6482.lib
endif

INTC_LIB=csl_c64xplus_intc.lib
RTS_LIB= rts64plus.lib
CSL_LIB_DIR= $(CSL3X_ROOT_DIR)
RTS_LIB_DIR= $(TI_DIR)\c6000\cgtools\lib


################ OS specific stuff ##########################
OSYS = WIN
WIN_RM_CMD=@erase /Q
WIN_COPY=copy
UNIX_RM_CMD=-\rm
UNIX_COPY=\cp

############  Generic #################

CC= $($(BUILD)_CC)
CC_OPTS= $($(BUILD)_CC_OPTS)
ASM= $($(BUILD)_ASM)
ASM_OPTS= $($(BUILD)_ASM_OPTS)
AR= $($(BUILD)_AR)
AR_OPTS= $($(BUILD)_AR_OPTS)
LNK= $($(BUILD)_LNK)
LNK_OPTS= $($(BUILD)_LNK_OPTS)
COPY= -@$($(OSYS)_COPY)
SRC_OPT= $($(BUILD)_SRC_OPT)

ifeq ($(BIG_ENDIAN), 1)
CC_OPTS += -me
ASM_OPTS += -me

ifeq ($(C64XX_DERIVATIVE),c6455)
CSL_LIB=csl_c6455e.lib
endif

ifeq ($(C64XX_DERIVATIVE),c6454)
CSL_LIB=csl_c6454e.lib
endif

ifeq ($(C64XX_DERIVATIVE),c6482)
CSL_LIB=csl_c6482e.lib
endif

INTC_LIB=csl_c64xplus_intce.lib
RTS_LIB= rts64pluse.lib
endif


LIB= $(CSL_LIB_DIR)\$(CSL_LIB) $(RTS_LIB_DIR)\$(RTS_LIB) $(CSL_LIB_DIR)\$(INTC_LIB)

RM_CMD= $($(OSYS)_RM_CMD)
