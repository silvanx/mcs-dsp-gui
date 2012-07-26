########## Settings that change from one module to another ###########
TARGET= c6482
CORE= c64plus
MODULE= intc
BUILD= release
CGTOOLS= ti

###########################################
#Root Directories			#
###########################################
CSL3X_ROOT_DIR= /vobs/csl3x
MODULE_SRC_DIR= .
MODULE_INC_DIR= .
MODULE_OBJ_DIR= ./obj/$(CORE)/$(BUILD)
MODULE_LIB_NAME   = csl_$(TARGET)_$(MODULE)_$(CORE).lib
COMMON_INC_DIR= $(CSL3X_ROOT_DIR)/inc
LIB_DIR= obj

############Include the compiler options specific makefile.inc
include $(CSL3X_ROOT_DIR)/Makefile.inc

##########################################################
#Find C Source Files					#

MODULE_C_FILES=$(wildcard *.c)
MODULE_ASM_FILES=$(wildcard *.asm)

MODULE_OBJ_FILES       =$(MODULE_C_FILES:%.c=$(MODULE_OBJ_DIR)/%.o)
MODULE_ASM_OBJ_FILES       =$(MODULE_ASM_FILES:%.asm=$(MODULE_OBJ_DIR)/%.o)

##########################################################
INC_DIR= -I$(MODULE_INC_DIR) -I$(COMMON_INC_DIR)

#######################################################################
#Beginning of makefile processing                                    #
#######################################################################
lib: $(MODULE_LIB_NAME)
	echo " Library created for $(MODULE) as $(MODULE_LIB_NAME)"
	echo "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"

objs: dirmake $(MODULE_OBJ_FILES) $(MODULE_ASM_OBJ_FILES) $(BADD_OBJ_FILE)
	@echo "Object files created"

dirmake:
	@if not exist obj\$(CORE)\$(BUILD) mkdir obj\$(CORE)\$(BUILD)


$(MODULE_OBJ_DIR)/%.o: $(MODULE_SRC_DIR)/%.asm
	$(CC) $(CC_OPTS) $(INC_DIR) $< -o $<

$(MODULE_OBJ_DIR)/%.o: $(MODULE_SRC_DIR)/%.c
	echo "Compiling $<"
	$(CC) $(CC_OPTS) $(INC_DIR) $< -o $<
	echo "Compiled $<"


$(MODULE_LIB_NAME):$(MODULE_OBJ_FILES) $(MODULE_ASM_OBJ_FILES)
	echo "Building  $(MODULE_LIB_NAME) the Lib"
	$(AR) $(AR_OPTS) $(MODULE_OBJ_DIR)/$(MODULE_LIB_NAME) $(MODULE_OBJ_FILES)

clean:
	@echo "Cleaning"
	$(RM_CMD) "$(MODULE_OBJ_DIR)\*.*"
	@echo "Completed Cleaning temporary files"

help:
	echo "USAGE >> clearmake -C gnu Makefile 
	echo "By default it builds $(CORE) $(BUILD) library for $(TARGET)
	echo "For any other targets, please use TARGET=<TARGET NAME> at command line like TARGET=5905 or TARGET=c6482.   
	echo "For any other Codegen tools, please use CGTOOLS=<CGTOOL NAME> at command line like CGTOOLS=rv" 
	echo "For any other core, please use CORE=<CORE NAME> at command line, like CORE=arm9 or CORE=c55"
	echo "For any other build type, please use BUILD=debug/release at command line.  
