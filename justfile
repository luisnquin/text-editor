
build:
    @gcc main.c -o ./build/text-editor -lncurses

run *ARGS: build
    @./build/text-editor {{ ARGS }}
