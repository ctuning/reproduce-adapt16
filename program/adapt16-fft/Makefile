#q=@

#OUTDIR:=

CC:=clang
CFLAGS:=

FLAGS_BASE:=-O3
FLAGS_BEST:=-O3 -ffp-contract=off -fno-inline -ftree-vectorize -ffast-math -fassociative-math -freciprocal-math -ffinite-math-only -fno-signed-zeros -fno-trapping-math -flimit-debug-info -fno-autolink -fno-dollars-in-identifiers -fno-elide-constructors -fno-lax-vector-conversions -fno-limit-debug-info -fno-operator-names -fno-rtti -fno-sanitize-recover -fno-spell-checking -fno-threadsafe-statics -fno-unroll-loops -fpascal-strings -ftrapv -fwrapv -fwritable-strings -mstrict-align -mtune=native -mrestrict-it

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
