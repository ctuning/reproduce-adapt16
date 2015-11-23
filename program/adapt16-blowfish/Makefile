#q=@

#OUTDIR:=

CC:=clang
CFLAGS:=

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3  -fomit-frame-pointer -fno-inline -fmerge-all-constants -fno-zero-initialized-in-bss -funroll-loops -funsafe-math-optimizations -fno-trapping-math -fmodules-prune-after=90 -fmodules-prune-interval=22 -fno-builtin -fno-common -fno-constant-cfstrings -fno-diagnostics-fixit-info -fno-lax-vector-conversions -fno-limit-debug-info -fno-operator-names -fno-sanitize-recover -fno-show-source-location -fno-spell-checking -fno-unroll-loops -fpascal-strings -fshort-enums -ftemplate-backtrace-limit=398 -mno-global-merge -mregparm=25 -msoft-float -mstrict-align -march=native -mfpu=neon -munaligned-access -mrestrict-it

all: clean out out_opt
	#adb push out $(OUTDIR)
	#adb push out_opt $(OUTDIR)
out: __ic__helper__.o  base_hf1.o
	$(q)$(CC) $(CFLAGS) $^ base.c -o $@
out_opt: __ic__helper__.o  opt_hf1.o
	$(q)$(CC) $(CFLAGS) $^ base.c -o $@
__ic__helper__.o:
	$(q)$(CC) $(CFLAGS) __ic__helper__.c -c
base_hf1.o:
	$(q)$(CC) $(CFLAGS) $(FLAGS_BASE) base_hf1.c -c -o $@
opt_hf1.o:
	$(q)$(CC) $(CFLAGS) $(FLAGS_BEST) base_hf1.c -c -o $@
clean:
	rm -f out out_opt *.o
