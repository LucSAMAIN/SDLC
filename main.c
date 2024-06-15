#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

void shakeItUP(SDL_Window *myWindow)
{
    int posCarr = 0;
    int elapseTime = 0; // ms
    while(elapseTime < 50000)
    {
        switch(posCarr)
        {
            case 0:
                SDL_SetWindowPosition(myWindow, 0, 0);
                posCarr++;
                break;
            case 1:
                SDL_SetWindowPosition(myWindow, 500, 0);
                posCarr++;
                break;
            case 2:
                SDL_SetWindowPosition(myWindow, 500, 300);
                posCarr++;
                break;
            case 3:
                SDL_SetWindowPosition(myWindow, 0, 300);
                posCarr = 0;
                break;
        }
        SDL_Delay(1000);
        elapseTime += 1000;
    }
}



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

    shakeItUP(window);



    SDL_DestroyWindow(window);

Quit:
    SDL_Quit();
    return status;
}