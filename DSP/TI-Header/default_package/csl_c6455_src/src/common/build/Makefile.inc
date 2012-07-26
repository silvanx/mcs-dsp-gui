########## Settings that change from one module to another ###########
TARGET=
CORE=
MODULE=
BUILD=
CGTOOLS=

###########################################
#Root Directories			#
###########################################
CSL3X_ROOT_DIR= /vobs/csl3x
MODULE_SRC_DIR= .
MODULE_INC_DIR= .
MODULE_OBJ_DIR= obj/$(CORE)/$(BUILD)
MODULE_LIB_NAME   = csl_$(TARGET)_$(MODULE)_$(CORE).lib
COMMON_INC_DIR= $(CSL3X_ROOT_DIR)/inc
LIB_DIR= obj

############Include the compiler options specific makefile.inc
include $(CSL3X_ROOT_DIR)/Makefile.inc

##########################################################
#Find C/Assembly Source Files					#
BADD_C_FILE=$(CSL3X_ROOT_DIR)/src/common/csl_$(MODULE)GetBaseAddress.c
BADD_OBJ_FILE=$(MODULE_OBJ_DIR)/csl_$(MODULE)GetBaseAddress.o
MODULE_C_FILES=$(wildcard *.c)
MODULE_ASM_FILES=$(wildcard *.asm)
###MODULE_ASM_FILES=$(wildcard $(CGTOOLS)/*.asm)
MODULE_C_OBJ_FILES=$(MODULE_C_FILES:%.c=$(MODULE_OBJ_DIR)/%.o)
###MODULE_ASM_OBJ_FILES=$(MODULE_ASM_FILES:$(CGTOOLS)\%.asm=$(MODULE_OBJ_DIR)/%.o)

MODULE_ASM_OBJ_FILES=$(MODULE_ASM_FILES:%.asm=$(MODULE_OBJ_DIR)/%.o)
MODULE_OBJ_FILES=$(MODULE_C_OBJ_FILES) $(MODULE_ASM_OBJ_FILES)

##########################################################
INC_DIR= -I$(MODULE_INC_DIR) -I$(COMMON_INC_DIR) -I$(CSL3X_ROOT_DIR)/../inc

