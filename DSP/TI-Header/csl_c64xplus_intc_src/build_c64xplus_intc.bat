gmake -f Makefile CGTOOLS=ti C64XX_DERIVATIVE=c64xplus_intc CORE=c64plus BUILD=release TARGET=c64xplus_intc CSL3X_ROOT_DIR=%CSL3X_ROOT_DIR%\csl_c64xplus_intc_src %1

@echo off
if cleanall EQU %1 goto DONE
@echo "Copying Lib file to folder %CSL3X_ROOT_DIR%\csl_c64xplus_intc\lib"
copy /V /Y %CSL3X_ROOT_DIR%\csl_c64xplus_intc_src\csl_c64xplus_intc.lib %CSL3X_ROOT_DIR%\csl_c64xplus_intc\lib

:DONE
@echo on
