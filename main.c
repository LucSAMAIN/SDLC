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
SDL_Color RED = {255, 0, 0, 255};
SDL_Color GREEN = {0, 255, 0, 255};
SDL_Color BLUE = {0, 0, 255, 255};
SDL_Color PURPLE = {150, 0, 150, 255};

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

    
    // texture:
    SDL_Texture *maTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888, // format pixel ici rgb alpha
        SDL_TEXTUREACCESS_TARGET, // quel type d'acces = utilisation de la texture = ici en tant que cible du rendu (et pas la window)
        200, // largeur
        200 // hauteur
    );
   
   if(NULL == maTexture)
   {
        fprintf(stderr, "Erreur à SDL_CreateTexture: %s", SDL_GetError());
        status = EXIT_FAILURE;
        goto Quit;
   }

   if( 0 != SDL_SetRenderTarget(renderer, maTexture))
   {
        fprintf(stderr, "Erreur à SDL_SetRenderTarget: %s", SDL_GetError());
        status = EXIT_FAILURE;
        goto Quit;
   }

   SDL_SetRenderDrawColor(renderer, PURPLE.r, PURPLE.g, PURPLE.b, PURPLE.a);
   SDL_Rect rect = {50, 50, 100, 100};
   SDL_RenderFillRect(renderer, &rect);
   SDL_SetRenderTarget(renderer, NULL); // repasser la main a la window

    SDL_Rect dst = {0, 0, 50, 50};
    if(0 != SDL_RenderCopy(renderer, maTexture, NULL, &dst))
    {
        fprintf(stderr, "Erreur à SDL_RenderCopy: %s", SDL_GetError());
        status = EXIT_FAILURE;
        goto Quit;
    }

    SDL_RenderPresent(renderer);


    // Attendre pour constater le résultat:
    SDL_Delay(3000);
   



Quit:
    if(window != NULL)
        SDL_DestroyWindow(window);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(maTexture != NULL)
        SDL_DestroyTexture(maTexture);

    SDL_Quit();
    return status;
}