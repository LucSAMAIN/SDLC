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

    SDL_Window *window = SDL_CreateWindow(
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
        return EXIT_FAILURE;
    }

    // pour éviter le thrown away de la fenetre qui
    // vient d'être créée:
    SDL_Delay(3000); // pause en ms


    SDL_Quit();
    return EXIT_SUCCESS;
}