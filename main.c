#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "assets/objeto.h"
#include "assets/tela.h"
#include "assets/algebra.h"
#include "assets/camera.h"
#include "assets/projecao.h"

/**
 * @authors Gustavo Provete de Andrade, Ruan Vieira Ribeiro e Caio Pereira Lapa
 */

#define transInicial 0.0f
#define transPasso 3.0f

#define escalaInicial 1.0f
#define escalaPasso 0.2f

#define rotInicial 0.0f
#define rotPasso (float)(2*M_PI/360)*2


void desenhaObjetoTela(SDL_Renderer *renderer, Projecao* projecao, Camera* camera, tObjeto3d *objeto);

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

    Camera* camera = criaCamera(-20.0f, 0.0f, 0.0f);
    if(camera == NULL)
    {
        printf("Não foi possivel criar objeto Camera");
        exit(1);
    }

    Projecao* projecao = criaProjecao(ORTOGRAFICA, 2, -2, 2, -2, 1, 10);
    if(projecao == NULL)
    {
        printf("Não foi possivel criar objeto Projecao");
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Ler o arquivo cubo.dcg e carregar o objeto 3D
    tObjeto3d *objeto = carregaObjeto("cubo.dcg");

    defineCamera(camera, objeto->pontos[0]);

    if (objeto == NULL)
    {
        desalocaTela(window);
        SDL_Quit();
        return 1;
    }

    //defineCamera(camera, objeto->pontos[0]);

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

                if(windowEvent.key.keysym.sym == SDLK_p) { defineProjecao(projecao, PERSPECTIVA); }
                if(windowEvent.key.keysym.sym == SDLK_o) { defineProjecao(projecao, ORTOGRAFICA); }

                if(windowEvent.key.keysym.sym == SDLK_c) 
                {
                    float* pontoModel = normalizarPonto4dEmModel(objeto->pontos[0], objeto);
                    defineCamera(camera, pontoModel);
                    free(pontoModel);
                }
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
            printf("Rotacionando...\n");
            rotacionaObjetoEixoX(objeto, rotX);
            rotacionaObjetoEixoY(objeto, rotY);
            rotacionaObjetoEixoZ(objeto, rotZ);
        }

        imprimeObjetoDBG(objeto);

        //===================================

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        desenhaObjetoTela(renderer, projecao, camera, objeto);

        SDL_RenderPresent(renderer);
    }

    // Liberar memória e encerrar
    desalocaObjeto(objeto);
    desalocaTela(window);
    SDL_Quit();

    return 1;
}

void realizarDivisaoPerspectiva(float* ponto4d);

void desenhaObjetoTela(SDL_Renderer *renderer, Projecao* projecao, Camera* camera, tObjeto3d *objeto)
{   
    printf("Desenhando objeto na tela...\n");

    float** matrizFinal = calcularMatrizMVP(objeto, camera, projecao);

    printf("Imprimindo matrix MVP:\n");
    imprimeMatriz4dDBG(matrizFinal);

    for (int i = 0; i < objeto->nArestas; i++) {
        int ponto1Index = objeto->arestas[i][0];
        int ponto2Index = objeto->arestas[i][1];

        float *ponto1 = objeto->pontos[ponto1Index];
        float *ponto2 = objeto->pontos[ponto2Index];

        float *ponto1Transformado = multMatriz4dPonto(matrizFinal, ponto1);
        float *ponto2Transformado = multMatriz4dPonto(matrizFinal, ponto2);

        realizarDivisaoPerspectiva(ponto1Transformado);
        realizarDivisaoPerspectiva(ponto2Transformado);

        float ponto1TransformadoTela2d[2] = {
            (ponto1Transformado[0] + 1.0f) * 0.5f * WIDTH,
            (1.0f - (ponto1Transformado[1] + 1.0f) * 0.5f) * HEIGHT
        };

        float ponto2TransformadoTela2d[2] = {
            (ponto2Transformado[0] + 1.0f) * 0.5f * WIDTH,
            (1.0f - (ponto2Transformado[1] + 1.0f) * 0.5f) * HEIGHT
        };

        SDL_RenderDrawLine(renderer,
                           ponto1TransformadoTela2d[0], ponto1TransformadoTela2d[1],
                           ponto2TransformadoTela2d[0], ponto2TransformadoTela2d[1]);

        free(ponto1Transformado);
        free(ponto2Transformado);
    }

    desalocaMatrix4d(matrizFinal);
}

void realizarDivisaoPerspectiva(float* ponto4d)
{
    if(ponto4d[3] != 0.0)
    {
        ponto4d[0] /= ponto4d[3];
        ponto4d[1] /= ponto4d[3];
        ponto4d[2] /= ponto4d[3];
    }
}