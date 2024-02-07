
build:
    @gcc main.c -o ./build/text-editor -lncurses

run: build
    @./build/text-editor
