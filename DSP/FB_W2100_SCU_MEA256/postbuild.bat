rem "${CG_TOOL_ROOT}/bin/hex${CG_TOOL_SUFFIX}.exe"  "${BuildArtifactFileName}" -o "${BuildArtifactFileBaseName}.a0" ../hex6x_rel.cfg
C:/ti/ccsv8/tools/compiler/c6000_7.4.24/bin/hex6x.exe %2 -o %3.a0 ../hex6x_rel.cfg
python ../ascii2bin.py %3

