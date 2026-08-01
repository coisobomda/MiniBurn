CC = clang
LDFLAGS = -Iinclude -lSDL2 -lGL

all: main

main: src/glad.c src/main.c src/render.c src/mesh.c src/mat4.c
	$(CC) src/main.c src/glad.c src/render.c src/mesh.c src/mat4.c -o program $(LDFLAGS)

.PHONY: all clean

clean: 
	rm -f program
