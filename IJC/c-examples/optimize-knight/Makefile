
# make run -- test of 3 code variants

CFLAGS = -O2 -funroll-all-loops # -omit-frame-pointer -mcpu=i686 -march=i686
PROGS = kun1 kun2 kun3

all: $(PROGS)

dump: $(PROGS)
	for i in $(PROGS); do objdump -d $$i >"$$i.asm"; done

asm:
	for i in $(PROGS); do $(CC) $(CFLAGS) -S $$i.c ; done

clean:
	rm -f $(PROGS) *.s *.asm

run: $(PROGS)
	for i in $(PROGS); do \
	    echo -n "Running program $$i: " ; \
	    /usr/bin/time ./$$i 2>&1 >/dev/null | head -1 | sed 's/user.*//' ; \
	done

pack:
	tar czvf kun.tar.gz  *.c Makefile
#
