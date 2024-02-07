#include "stdbool.h"
#include "curses.h"
#include "stdlib.h"
#include "string.h"
#include "signal.h"

#include "ascii.h"

#define DEBUG_FILE_NAME "build/keys.debug"

const int TEXT_CHUNK_SIZE = 10;

char *text_buffer;
FILE *debug_file;

void exit_handler()
{
    if (text_buffer != NULL)
        free(text_buffer);

    if (debug_file != NULL)
        fclose(debug_file);

    endwin();
    printf("nao~ nao~\n");
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGTERM, exit_handler);
    signal(SIGINT, exit_handler);

    initscr();
    raw();

    noecho();
    keypad(stdscr, true);

    int text_cap = TEXT_CHUNK_SIZE;
    int text_length = 0;

    text_buffer = malloc(text_cap * sizeof(char));
    debug_file = fopen(DEBUG_FILE_NAME, "w");

    for (int i = 0; i < text_cap; i++)
    {
        if (i + 1 == text_cap)
        {
            text_cap += TEXT_CHUNK_SIZE;

            text_buffer = realloc(text_buffer, text_cap * sizeof(char));
            if (text_buffer == NULL)
            {
                fprintf(stderr, "Failed to allocate memory :(\n");
                exit(EXIT_FAILURE);
            }
        }

        wclear(stdscr);
        printw("[%d/%d] %s", text_length, text_cap, text_buffer);

        int c = getch();

        fprintf(debug_file, "Char: %c | Dec: %d\n", c, c);
        fflush(debug_file);

        if (c == CTRL_C_KEY)
            break;

        switch (c)
        {
        case DELETE_KEY:
            int prev = i - 1;

            if (prev >= 0)
            {
                text_buffer[prev] = NULL_KEY;
                i -= 2;
                text_length--;
            }

            break;

        default:
            text_buffer[i] = (char)c;
            move(0, i);
            text_length++;
            break;
        }
    }

    exit_handler();

    return 0;
}