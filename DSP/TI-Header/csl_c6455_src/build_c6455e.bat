gmake -f Makefile CGTOOLS=ti C64XX_DERIVATIVE=c6455 CORE=c64plus BUILD=release TARGET=c6455 BIG_ENDIAN=1 CSL3X_ROOT_DIR=%CSL3X_ROOT_DIR%\csl_c6455_src %1
@echo off
if cleanall EQU %1 goto DONE
@echo "Copying Lib file to folder %CSL3X_ROOT_DIR%\csl_c6455\lib"
copy /V /Y %CSL3X_ROOT_DIR%\csl_c6455_src\csl_c6455e.lib %CSL3X_ROOT_DIR%\csl_c6455\lib


:DONE
@echo on
