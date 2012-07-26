############Include the compiler options speific makefile.inc
#include Makefile.inc

#######################################################################
#Beginning of makefile processing                                    #
#######################################################################
lib: $(MODULE_LIB_NAME) $(MODULE_ASM_OBJ_FILES)
	@echo " Library created for $(MODULE) as $(MODULE_LIB_NAME)"
	@echo "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"

objs: dirmake $(MODULE_OBJ_FILES) $(MODULE_ASM_OBJ_FILES) $(BADD_OBJ_FILE)
	@echo "Object files created"

dirmake:
	@if not exist obj\$(CORE)\$(BUILD) mkdir obj\$(CORE)\$(BUILD) 

$(BADD_OBJ_FILE):$(BADD_C_FILE)
	@echo "Compiling $<"
	$(CC) $(CC_OPTS) $(INC_DIR) $(SRC_OPT)$< 
	@echo "Compiled $<"

$(MODULE_OBJ_DIR)/%.o: $(MODULE_SRC_DIR)/%.c
	@echo "Compiling $<"
	$(CC) $(CC_OPTS) $(INC_DIR) $(SRC_OPT)$< 
	@echo "Compiled $<"

$(MODULE_OBJ_DIR)/%.o: $(MODULE_SRC_DIR)/%.asm
	@echo "Compiling $<"
	$(ASM) $(ASM_OPTS) $(SRC_OPT)$< 
	@echo "Compiled $<"

	
$(MODULE_LIB_NAME):$(MODULE_OBJ_FILES) $(BADD_OBJ_FILE)
	@echo "Building  $(MODULE_LIB_NAME) the Lib"
	$(AR) $(AR_OPTS) $(MODULE_OBJ_DIR)/$(MODULE_LIB_NAME) $(MODULE_OBJ_FILES) $(BADD_OBJ_FILE) 

clean:
	@echo "Cleaning"
	$(RM_CMD) "$(MODULE_OBJ_DIR)\*.*"
	@echo "Completed Cleaning temporary files"

help:
	@echo "USAGE >> clearmake -C gnu Makefile 
	@echo "By default it builds $(CORE) $(BUILD) library for $(TARGET)
	@echo "For any other targets, please use TARGET=<TARGET NAME> at command line like TARGET=5905 or TARGET=trinity.   
	@echo "For any other Codegen tools, please use CGTOOLS=<CGTOOL NAME> at command line like CGTOOLS=rv" 
	@echo "For any other core, please use CORE=<CORE NAME> at command line, like CORE=arm9 or CORE=c55"
	@echo "For any other build type, please use BUILD=debug/release at command line.   
