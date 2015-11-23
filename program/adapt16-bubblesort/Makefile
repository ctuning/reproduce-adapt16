#q=@

#OUTDIR=

CC:=clang
CFLAGS:=-DNUMELEMS=10000

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3 -fomit-frame-pointer -fmerge-all-constants -ftree-vectorize -funroll-loops -fassociative-math -freciprocal-math -ffinite-math-only -fno-trapping-math -fmodules-prune-interval=18 -fno-constant-cfstrings -fno-diagnostics-fixit-info -fno-dollars-in-identifiers -fno-elide-constructors -fno-elide-type -fno-lax-vector-conversions -fno-limit-debug-info -fno-sanitize-recover -fno-show-source-location -fno-signed-char -fno-use-cxa-atexit -fpascal-strings -fshow-overloads=all -fuse-init-array -fvisibility-inlines-hidden -fwritable-strings -momit-leaf-frame-pointer -msoft-float -mfloat-abi=softfp -mfpu=neon -mcpu=native -mrestrict-it

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
