#q=@

#OUTDIR:=

CC:=clang
CFLAGS:=

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3 -fomit-frame-pointer -fno-inline -fno-zero-initialized-in-bss -ftree-vectorize -funroll-loops -ffast-math -fassociative-math -flimit-debug-info -fmodules-prune-interval=94 -fno-assume-sane-operator-new -fno-common -fno-diagnostics-fixit-info -fno-elide-constructors -fno-lax-vector-conversions -fno-limit-debug-info -fno-merge-all-constants -fno-signed-char -fno-unroll-loops -fno-use-cxa-atexit -fno-use-init-array -fpascal-strings -fshow-overloads=best -fstrict-enums -ftemplate-backtrace-limit=709 -fwrapv -mno-global-merge -momit-leaf-frame-pointer -mregparm=20 -msoft-float -mfloat-abi=softfp -mfpu=neon -mtune=native -munaligned-access -mrestrict-it


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
