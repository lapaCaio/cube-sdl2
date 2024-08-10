#include <stdio.h>
#include <SDL2/SDL.h>
#include "assets/objeto.h"
#include "assets/tela.h"
#include "assets/algebra.h"

#define transInicial 0.0f
#define transPasso 1.0f

#define escalaInicial 1.0f
#define escalaPasso 0.2f

// desenha um objeto na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto)
{
    for (int i = 0; i < objeto->nArestas; i++)
    {
        int ponto1 = objeto->arestas[i][0];
        int ponto2 = objeto->arestas[i][1];
        SDL_RenderDrawLine(renderer,
                           objeto->pontos[ponto1][0], objeto->pontos[ponto1][1],
                           objeto->pontos[ponto2][0], objeto->pontos[ponto2][1]);
    }
}

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL não inicializou! SDL Erro: %s\n", SDL_GetError());
    }

    SDL_Window *window = criaTela("CUBE SDL2");
    if (window == NULL)
    {
        printf("SDL não criou a janela! SDL Erro: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Ler o arquivo cubo.dcg e carregar o objeto 3D
    tObjeto3d *objeto = carregaObjeto("cubo.dcg");
    if (objeto == NULL)
    {
        desalocaTela(window);
        SDL_Quit();
        return 1;
    }

    criaIdentidade4d(objeto->modelMatrix);
    imprimeObjetoDBG(objeto);

    SDL_Event windowEvent;
    while (1)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }
        
        float transX = transInicial;
        float transY = transInicial;
        float transZ = transInicial;

        float escalaX = escalaInicial;
        float escalaY = escalaInicial;
        float escalaZ = escalaInicial;

        if(windowEvent.type == SDL_KEYDOWN)
        {
            if(windowEvent.key.keysym.sym == SDLK_w) { transY = transPasso; }
            if(windowEvent.key.keysym.sym == SDLK_s) { transY = -transPasso; }
            if(windowEvent.key.keysym.sym == SDLK_d) { transX = transPasso; }
            if(windowEvent.key.keysym.sym == SDLK_a) { transX = -transPasso; }
        }

        if(windowEvent.type == SDL_MOUSEWHEEL)
        {
            if(windowEvent.wheel.y > 0)
            {
                escalaX += escalaPasso;
                escalaY += escalaPasso;
            }

            if(windowEvent.wheel.y < 0)
            {
                escalaX -= escalaPasso;
                escalaY -= escalaPasso;
            }
        }

        transladaObjeto(objeto, transX, 0, 0);

        if(transX != transInicial || transY != transInicial || transZ != transInicial)
        {
            printf("Transladando...\n");
            transladaObjeto(objeto, transX, transY, transZ);
        }

        if(escalaX != escalaInicial || escalaY != escalaInicial || escalaZ != escalaInicial)
        {
            printf("Escalando...\n");
            escalaObjeto(objeto, escalaX, escalaY, escalaZ);
        }

        imprimeObjetoDBG(objeto);

        //===================================

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        desenhaObjetoTela(renderer, objeto->modelMatrix, objeto);

        SDL_RenderPresent(renderer);
    }

    // Liberar memória e encerrar
    desalocaObjeto(objeto);
    desalocaTela(window);
    SDL_Quit();

    return 1;
}
