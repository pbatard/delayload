MinGW delay load issue
======================

## Description

This repository provides a sample to replicate the MinGW delay loading issue.

So far, this issue has been found to happen when trying to link with the
`wininet`, `virtdisk`, `uxtheme` libraries. The use of `InternetCrackUrlA()`
from `wininet` is only provided here as an example, as many more calls and
DLLs are affected.

An initial discussion of the issue, on the MinGW mailing list, can be found
[here](https://sourceforge.net/p/mingw-w64/mailman/mingw-w64-public/thread/ea87573f-65ea-44a2-b4bb-ca96c0a136ab%40akeo.ie/#msg58793876).

## Workarounds

Two "workarounds" have been found to alleviate the issue:

1. Redefining `DECLSPEC_IMPORT` to use `__attribute__((visibility("hidden")))`
   instead of `__declspec (dllimport)`. However, this kind of workaround is
   problematic as, for instance, MinGW's `windows.h` header doest itself
   include more headers that use `DECLSPEC_IMPORT`, which mean redefining
   the macro **before** the relevant header inclusion is tricky.

2. Adding explicit references to the symbols that the linker appears to
   ignore (in this example `_InternetCrackUrlA@16`) so that they aren't
   discarded. Likewise, this workaround is problematic, as, even outside
   of having to identify all the problematic function calls, one must make
   sure these additional intrinsic function calls are referenced by the
   application or added as `-u` parameters when invoking `ld`, and since the
   decorations are not the same for 32 and 64 bit, one cannot just use a
   single common 32 + 64 bit implementation...

## Testing

1. Clone https://github.com/pbatard/delayload.git (this repository)
2. From a MinGW32 (**32-bit**) prompt, issue `make`.
3. Run `./delayload.exe` and observe the crash.
4. To test with the workarounds, issue `make clean` and then either
   `make WORKAROUND1` or `make WORKAROUND2`.
