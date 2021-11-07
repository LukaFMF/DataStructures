$CPL = "gcc";
$WRN = "-Wall","-Wextra","-Wno-discarded-qualifiers","-pedantic";
$OPT = "-O3"; #"-O0"
$REQ = @($WRN) + @($OPT);
$CMD = "demo.c","-o","demo.exe";
& $CPL $CMD $REQ;
