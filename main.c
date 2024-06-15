#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur à SDL_Init: %s", SDL_GetError());
        return EXIT_FAILURE;
    }


    SDL_Quit(void);
    return EXIT_SUCCESS;
}