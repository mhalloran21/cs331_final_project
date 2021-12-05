CFLAGS=-Wall

.PHONY: all
all: program

liba.so.1.0.0: a.h a.c
	gcc $(CFLAGS) -shared -fPIC -Wl,-soname,liba.so.1.0.0 -o liba.so.1.0.0 a.c -lc

libb.so.1.0.0: b.h b.c
	gcc $(CFLAGS) -shared -fPIC -Wl,-soname,libb.so.1.0.0 -o libb.so.1.0.0 b.c -lc

program: c.c liba.so.1.0.0 libb.so.1.0.0
	gcc $(CFLAGS) c.c -o program liba.so.1.0.0 libb.so.1.0.0

.PHONY: clean
clean:
	rm -f *.so*
	rm -f program

