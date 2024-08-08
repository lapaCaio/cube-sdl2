all:
	gcc -I src/include -L src/lib -o main.exe main.c assets/*.c -lmingw32 -lSDL2main -lSDL2

.PHONY: debug
debug:
	gcc -I src/include -L src/lib -g -o debug/main main.c assets/*.c -lmingw32 -lSDL2main -lSDL2
	gdb debug/main.exe

exec:
	.\main.exe