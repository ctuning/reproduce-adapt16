#q=@

#OUTDIR:=

CC:=clang
CFLAGS:=

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3 -ffp-contract=on -fomit-frame-pointer -fmerge-all-constants -fno-zero-initialized-in-bss -funroll-loops -ffast-math -funsafe-math-optimizations -fassociative-math -freciprocal-math -fno-signed-zeros -fno-trapping-math -flimit-debug-info -fmodules-prune-after=81 -fno-assume-sane-operator-new -fno-builtin -fno-common -fno-dollars-in-identifiers -fno-elide-type -fno-lax-vector-conversions -fno-limit-debug-info -fno-sanitize-recover -fno-signed-char -fno-spell-checking -fno-threadsafe-statics -fno-use-cxa-atexit -fshort-enums -fvisibility-inlines-hidden -fwritable-strings -momit-leaf-frame-pointer -mstrict-align -march=armv7-a -mtune=native -mcpu=native -munaligned-access

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
