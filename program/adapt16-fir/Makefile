#q=@

#OUTDIR:=

CC:=clang
CFLAGS:=

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3  -ffp-contract=on -fomit-frame-pointer -fmerge-all-constants -fno-zero-initialized-in-bss -funroll-loops -ffast-math -fassociative-math -freciprocal-math -fno-trapping-math -fmodules-prune-after=46 -fno-builtin -fno-dollars-in-identifiers -fno-lax-vector-conversions -fno-merge-all-constants -fno-operator-names -fno-rtti -fno-show-column -fno-show-source-location -fno-spell-checking -fno-unroll-loops -fno-use-cxa-atexit -fshort-enums -fshow-overloads=all -fstrict-enums -fuse-init-array -mno-global-merge -momit-leaf-frame-pointer -mstrict-align -march=armv7-a -mfloat-abi=softfp -mcpu=native

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
