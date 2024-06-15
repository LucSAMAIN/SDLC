#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>



////////////////////////////////////////////////
/////////////// VAR GLOB ///////////////////////
///////////////////////////////////////////////

/*  
    DEBUT COULEURS
*/

SDL_Color ORANGE = {255, 127, 40, 255};
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color WHITE = {255, 255, 255, 255};

/*
    FIN COULEURS
*/

////////////////////////////////////////////////
/////////////// DECLARATION ////////////////////
////////////////////////////////////////////////

int setWindowColor(SDL_Renderer *rendeur, SDL_Color color);
void shakeItUP(SDL_Window *myWindow);
int initRendererAndWindow(SDL_Window **resultWindow, SDL_Renderer **resultRendeur);

////////////////////////////////////////////////
/////////////// DEFINITIONS/////////////////////
////////////////////////////////////////////////

int initRendererAndWindow(SDL_Window **resultWindow, SDL_Renderer **resultRendeur)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur à SDL_Init: %s", SDL_GetError());
        return -1;
    }

    *resultWindow = SDL_CreateWindow(
        "MaPremiereFenetre", // title
        SDL_WINDOWPOS_CENTERED, // x
        SDL_WINDOWPOS_CENTERED, // y
        640, // witdh
        480, // height
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE // flags
    );

    if(*resultWindow == NULL)
    {
        fprintf(stderr, "Erreur à SDL_CreateWindow: %s", SDL_GetError());
        return -1;
    }

    *resultRendeur = SDL_CreateRenderer(
        *resultWindow, // fenetre en question
        -1, // pilot - gere des truc mais aussi pas besoin de mettre le drapeau d'apres...
        SDL_RENDERER_ACCELERATED // via gpu
    );

    if(*resultRendeur == NULL)
    {
        fprintf(stderr, "Erreur à SDL_CreateRenderer: %s", SDL_GetError());
        return -1;
    }

    return 0;

}

int setWindowColor(SDL_Renderer *rendeur, SDL_Color color)
{
    // on choisit la couleur sur le pinceau:
    if(SDL_SetRenderDrawColor(rendeur, color.r, color.g, color.b, color.a) != 0)
    {
        fprintf(stderr, "Erreur à SDL_SetRenderDrawColor: %s", SDL_GetError());
        return -1;
    }

    // on peint en entier la fenetre associé a notre rendeur
    if(SDL_RenderClear(rendeur) != 0)
    {
        fprintf(stderr, "Erreur à SDL_RenderClear: %s", SDL_GetError());
        return -1;
    }

    SDL_RenderPresent(rendeur);

    return 0;
}



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

////////////////////////////////////////////////
////////////////// MAIN ////////////////////////
////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int status = EXIT_SUCCESS;

    if( 0 != initRendererAndWindow(&window, &renderer))
    {
        status = EXIT_FAILURE;
        goto Quit;
    }


    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);

    // damier du tuto:

    SDL_Rect rect[60];
    size_t i = 0;
    for(i = 0; i < 50; i++)
    {   
        rect[i].w = 50;
        rect[i].h = 50;
        rect[i].x = 100 * (i % 5) + 50 * ((i / 5) % 2);
        rect[i].y = 50 * (i / 5);
    }
    SDL_RenderFillRects(renderer, rect, 50); 
    SDL_RenderPresent(renderer);

   

    // Attendre pour constater le résultat:
    SDL_Delay(3000);
   



Quit:
    if(window != NULL)
        SDL_DestroyWindow(window);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return status;
}