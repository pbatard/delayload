all: wininet-delaylib.lib delayload.exe

WORKAROUND1: CFLAGS += -DWORKAROUND1
WORKAROUND1: all

WORKAROUND2: CFLAGS += -DWORKAROUND2
WORKAROUND2: all

%-delaylib.lib: %.def
	dlltool --input-def $< --output-delaylib $@ --dllname $(basename $<).dll

%.exe: %.c
	gcc $(CFLAGS) -o $@ $< -L . -lwininet-delaylib

clean:
	rm -rf *.lib *.exe
