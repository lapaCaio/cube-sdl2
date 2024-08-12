#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "assets/objeto.h"
#include "assets/tela.h"
#include "assets/algebra.h"

/**
 * @authors Gustavo Provete de Andrade, Ruan Vieira Ribeiro e Caio Pereira Lapa
 */

#define transInicial 0.0f
#define transPasso 3.0f

#define escalaInicial 1.0f
#define escalaPasso 0.2f

#define rotInicial 0.0f
#define rotPasso (float)(2*M_PI/360)*2

// desenha um objeto na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matriz, tObjeto3d *objeto)
{
    for (int i = 0; i < objeto->nArestas; i++)
    {
        int ponto1Index = objeto->arestas[i][0];
        int ponto2Index = objeto->arestas[i][1];

        float *ponto1 = objeto->pontos[ponto1Index];
        float *ponto2 = objeto->pontos[ponto2Index];

        float *ponto1Transformado = multMatriz4dPonto(matriz, ponto1);
        float *ponto2Transformado = multMatriz4dPonto(matriz, ponto2);

        SDL_RenderDrawLine(renderer,
                           ponto1Transformado[0], ponto1Transformado[1],
                           ponto2Transformado[0], ponto2Transformado[1]);

        free(ponto1Transformado);
        free(ponto2Transformado);
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
        float transX = transInicial;
        float transY = transInicial;
        float transZ = transInicial;

        float escalaX = escalaInicial;
        float escalaY = escalaInicial;
        float escalaZ = escalaInicial;

        float rotX = rotInicial;
        float rotY = rotInicial;
        float rotZ = rotInicial;

        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }

            if(windowEvent.type == SDL_KEYDOWN)
            {
                if(windowEvent.key.keysym.sym == SDLK_w) { transY += -transPasso;}
                if(windowEvent.key.keysym.sym == SDLK_s) { transY += transPasso;}
                if(windowEvent.key.keysym.sym == SDLK_d) { transX += transPasso;}
                if(windowEvent.key.keysym.sym == SDLK_a) { transX += -transPasso;}
                if(windowEvent.key.keysym.sym == SDLK_LCTRL) { transZ += -transPasso; }
                if(windowEvent.key.keysym.sym == SDLK_LSHIFT) { transZ += transPasso; }

                if(windowEvent.key.keysym.sym == SDLK_g) { rotY += rotPasso; }
                if(windowEvent.key.keysym.sym == SDLK_j) { rotY -= rotPasso; }
                if(windowEvent.key.keysym.sym == SDLK_y) { rotX += rotPasso; }
                if(windowEvent.key.keysym.sym == SDLK_h) { rotX -= rotPasso; }
                if(windowEvent.key.keysym.sym == SDLK_i) { rotZ -= rotPasso; }
                if(windowEvent.key.keysym.sym == SDLK_k) { rotZ += rotPasso; }
            }

            if(windowEvent.type == SDL_MOUSEWHEEL)
            {
                if(windowEvent.wheel.y > 0)
                {
                    escalaX += escalaPasso;
                    escalaY += escalaPasso;
                    escalaZ += escalaPasso;
                }

                if(windowEvent.wheel.y < 0)
                {
                    escalaX -= escalaPasso;
                    escalaY -= escalaPasso;
                    escalaZ -= escalaPasso;
                }
            }
        }

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

        if(rotX != rotInicial || rotY != rotInicial || rotZ != rotInicial)
        {
            printf("Rotacionando...");
            rotacionaObjetoEixoX(objeto, rotX);
            rotacionaObjetoEixoY(objeto, rotY);
            rotacionaObjetoEixoZ(objeto, rotZ);
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
