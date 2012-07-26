include $(CSL3X_ROOT_DIR)\src\common\build\Makefile.inc
MODULE  = common
MODULE_OBJ_DIR= $(CSL3X_ROOT_DIR)/src/$(MODULE)/obj/$(CORE)/$(BUILD)
BADD_OBJ_FILE=
MODULE_C_FILES= csl_version.c
ifneq ($(C64XX_DERIVATIVE), c64xplus_intc)
MODULE_ASM_FILES= _csl_beginCriticalSection.asm _csl_endCriticalSection.asm
else
MODULE_ASM_FILES=
endif
MODULE_C_OBJ_FILES     = $(MODULE_C_FILES:%.c=$(MODULE_OBJ_DIR)/%.o)
MODULE_ASM_OBJ_FILES   = $(MODULE_ASM_FILES:%.asm=$(MODULE_OBJ_DIR)/%.o)
MODULE_OBJ_FILES       = $(MODULE_C_OBJ_FILES) $(MODULE_ASM_OBJ_FILES)
include $(CSL3X_ROOT_DIR)\src\common\build\Makefile

