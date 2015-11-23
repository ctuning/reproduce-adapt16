#q=@

#OUTDIR:=

CC:=clang
CFLAGS:=

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3  -fomit-frame-pointer -funroll-loops -freciprocal-math -ffinite-math-only -fno-signed-zeros -fno-trapping-math -fmodules-prune-after=41 -fno-autolink -fno-builtin -fno-common -fno-constant-cfstrings -fno-dollars-in-identifiers -fno-lax-vector-conversions -fno-limit-debug-info -fno-merge-all-constants -fno-rtti -fno-sanitize-recover -fno-show-source-location -fno-unroll-loops -fno-use-init-array -fshow-overloads=best -fstrict-enums -ftemplate-backtrace-limit=478 -fvisibility-inlines-hidden -fwritable-strings -mno-global-merge -momit-leaf-frame-pointer -mregparm=5 -msoft-float -mstrict-align -march=armv7-a -mfloat-abi=softfp -mcpu=native

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
