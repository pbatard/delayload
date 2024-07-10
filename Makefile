all: wininet-delaylib.lib delayload.exe

%-delaylib.lib: %.def
	dlltool --input-def $< --output-delaylib $@ --dllname $(basename $<).dll

%.exe: %.c
	gcc -o $@ $< -L . -lwininet-delaylib

clean:
	rm -rf *.lib *.exe
