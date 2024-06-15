#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    int status = EXIT_SUCCESS;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur à SDL_Init: %s", SDL_GetError());
        status = EXIT_FAILURE;
        goto Quit;
    }

    window = SDL_CreateWindow(
        "MaPremiereFenetre", // title
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        640, // witdh
        480, // height
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE // flags
    );

    if(window == NULL)
    {
        fprintf(stderr, "Erreur à SDL_CreateWindow: %s", SDL_GetError());
        status = EXIT_FAILURE;
        goto Quit;
    }

    // pour éviter le thrown away de la fenetre qui
    // vient d'être créée:
    SDL_Delay(3000); // pause en ms


    SDL_DestroyWindow(window);

Quit:
    SDL_Quit();
    return status;
}