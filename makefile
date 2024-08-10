all:
	gcc -I src/include -L src/lib -o main.exe main.c assets/*.c -lmingw32 -lSDL2main -lSDL2

.PHONY: debug
debug:
	gcc -g3 -I src/include -L src/lib -o debug main.c assets/*.c -lmingw32 -lSDL2main -lSDL2
	gdb debug.exe

exec:
	.\main.exe