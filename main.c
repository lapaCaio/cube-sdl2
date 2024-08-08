#include <stdio.h>
#include <SDL2/SDL.h>
#include "assets/objeto.h"
#include "assets/tela.h"
#include "assets/algebra.h"

//desenha um objeto na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto){

}


int main( int argc, char * argv[] ){

    if (SDL_Init( SDL_INIT_EVERYTHING) < 0){
        printf("SDL n�o inicializou! SDL Erro: %s\n", SDL_GetError());
    }

    SDL_Window *window = criaTela("Hello SDL World!");

    if(window == NULL){
        printf("SDL n�o criou a janela! SDL Erro: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event windowEvent;

    while(1){
        if( SDL_PollEvent(&windowEvent)){
            if(windowEvent.type == SDL_QUIT){
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //ESCREVA AQUI O SEU PROGRAMA

        SDL_RenderPresent(renderer);
    }

    desalocaTela(window);
    SDL_Quit();

    return 1;
}
