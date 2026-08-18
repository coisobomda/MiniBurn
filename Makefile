CC = clang
LDFLAGS = -Iinclude -lSDL2 -lGL -lm

all: main

main: src/glad.c src/main.c src/render.c src/mesh.c src/math/mat4.c src/math/radians.c src/texture.c src/stb_image.c src/camera.c src/math/normalize.c
	$(CC) -g src/main.c src/glad.c src/render.c src/mesh.c src/math/mat4.c src/math/radians.c src/texture.c src/stb_image.c src/camera.c src/math/normalize.c -o MiniBurn $(LDFLAGS)

.PHONY: all clean

clean: 
	rm -f program
