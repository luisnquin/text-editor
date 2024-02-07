#include "stdbool.h"
#include "curses.h"
#include "stdlib.h"
#include "signal.h"

void signal_handler()
{
    endwin();
    printf("nao~ nao~\n");
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    noecho();
    keypad(stdscr, true);

    initscr();

    printw("Hello!");

    char text[256];

    while (true)
    {
        char c = getch();
        printw("\n\n%c", c);

        move(30, 0);
    }

    return 0;
}