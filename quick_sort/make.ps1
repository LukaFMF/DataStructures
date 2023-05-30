$CPL = "gcc";
$WRN = "-Wall","-Wextra","-Wno-discarded-qualifiers","-pedantic";
$OPT = "-O3"; #"-O0"
$DBG = "-g"; #"-O0"
$REQ = @($WRN) + @($OPT) + @($DBG);
$CMD = "demo.c","-o","demo.exe";
& $CPL $CMD $REQ;
