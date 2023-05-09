
CC = gcc
CFLAGS = -Wall -Wextra -pedantic `pkg-config --cflags sdl2`
CLIBS = `pkg-config --libs sdl2`

W_CC = x86_64-w64-mingw32-gcc.exe
W_PKG_CONFIG = x86_64-w64-mingw32-pkg-config.exe
W_CFLAGS = -Wall -Wextra -pedantic `$(W_PKG_CONFIG) --cflags sdl2`
W_CLIBS = `$(W_PKG_CONFIG) --libs sdl2`

main: main.c
	$(CC) $(CFLAGS) main.c $(CLIBS) -o main

windows: main.c
	$(W_CC) $(W_CFLAGS) -mconsole main.c $(W_CLIBS) -o main.exe
