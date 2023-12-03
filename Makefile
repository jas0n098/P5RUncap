CC=x86_64-w64-mingw32-gcc
CFLAGS=-Wall -s -shared

P5RUncap.asi: dllmain.c memory.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f P5RUncap.asi
