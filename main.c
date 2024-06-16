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
int initRendererAndWindow(SDL_Window **resultWindow, SDL_Renderer **resultRendeur, int largeur, int hauteur);
SDL_Texture *loadImage(SDL_Renderer *rendeur, const char *path);

////////////////////////////////////////////////
/////////////// DEFINITIONS/////////////////////
////////////////////////////////////////////////

int initRendererAndWindow(SDL_Window **resultWindow, SDL_Renderer **resultRendeur, int largeur, int hauteur)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur à SDL_Init: %s", SDL_GetError());
        return -1;
    }

    if( SDL_CreateWindowAndRenderer(largeur, hauteur, SDL_WINDOW_SHOWN, resultWindow, resultRendeur) != 0)
    {
        fprintf(stderr, "Erreur à SDL_CreateWindowAndRenderer: %s", SDL_GetError());
        return -1;
    }
            
    return 0;

}

SDL_Texture *loadImage(SDL_Renderer *rendeur, const char *path)
{
    SDL_Surface *surface = SDL_LoadBMP(path);
    if(surface == NULL)
    {
        fprintf(stderr, "Erreur à SDL_LoadBMP: %s", SDL_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendeur, surface);
    SDL_FreeSurface(surface);
    if(texture == NULL)
    {
        fprintf(stderr, "Erreur à SDL_CreateTextureFromSurface: %s", SDL_GetError());
        return NULL;
    }


    return texture;

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
    SDL_Texture *maTexture = NULL;
    int status = EXIT_SUCCESS;

    if( 0 != initRendererAndWindow(&window, &renderer, 500, 500))
    {
        status = EXIT_FAILURE;
        goto Quit;
    }

    // Event:

    SDL_Event event;
    SDL_bool quit = SDL_FALSE;

    while(!quit)
    {
        SDL_PollEvent(&event);
            if(event.type == SDL_QUIT)
                quit = SDL_TRUE;
            SDL_Delay(20);
    }






    // rendre le travail affichable
    SDL_RenderPresent(renderer);
    // Attendre pour constater le résultat:
    SDL_Delay(1000);
   



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