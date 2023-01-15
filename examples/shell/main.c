#include <stdio.h>
#include "nr_micro_shell.h"
#include <SDL2/SDL.h>

static SDL_Thread *nr_shell_thread = NULL;

static int nr_shell_thread_entry(void *data)
{
    char c;
    shell_init();
    while(1)
    {
        c = getchar();
        shell(c);
    }
    return 0;
}

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    nr_shell_thread = SDL_CreateThreadWithStackSize(nr_shell_thread_entry, "nr_shell_thread_entry", 8 * 1024, NULL);
    SDL_WaitThread(nr_shell_thread, NULL);
    SDL_Quit();
    return 0;
}