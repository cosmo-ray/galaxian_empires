#!/bin/sh
#yes i know it's very dirty, but hey, fuck you it's for windows(and i dont now why, when i add the -o option, gcc doesn't fin sdl libreary)
i486-mingw32-gcc *.c -I/usr/i486-mingw32/include/SDL/ -L/usr/i486-mingw32/lib/ -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lm
mv a.exe BoGH.exe
