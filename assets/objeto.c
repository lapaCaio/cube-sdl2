#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "objeto.h"
#include "algebra.h"

//L� as informa��es de um arquivo e as carrega num novo objeto alocado
tObjeto3d *carregaObjeto(char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Não foi possível abrir o arquivo!");
        return NULL;
    }

    tObjeto3d *objeto = (tObjeto3d*)malloc(sizeof(tObjeto3d));
    if (objeto == NULL) {
        perror("Erro ao alocar memória. Não foi possível criar o objeto Cubo.");
        fclose(arquivo);
        return NULL;
    }

    // Lê a quantidade de pontos
    fscanf(arquivo, "%d", &(objeto->nPontos));

    // Aloca memória para os pontos
    objeto->pontos = (float**)malloc(objeto->nPontos * sizeof(float*));
    for (int i = 0; i < objeto->nPontos; i++) {
        objeto->pontos[i] = (float*)malloc(4 * sizeof(float));
        fscanf(arquivo, "%f %f %f", &objeto->pontos[i][0], &objeto->pontos[i][1], &objeto->pontos[i][2]);
        objeto->pontos[i][3] = 1.0f;
    }

    // Lê a quantidade de arestas
    fscanf(arquivo, "%d", &(objeto->nArestas));

    // Aloca memória para as arestas
    objeto->arestas = (int**)malloc(objeto->nArestas * sizeof(int*));
    for (int i = 0; i < objeto->nArestas; i++) {
        objeto->arestas[i] = (int*)malloc(2 * sizeof(int));
        fscanf(arquivo, "%d %d", &objeto->arestas[i][0], &objeto->arestas[i][1]);
    }

    // Inicializa a matriz de modelo como uma matriz identidade 4x4
    objeto->modelMatrix = (float**)malloc(4 * sizeof(float*));
    for (int i = 0; i < 4; i++) {
        objeto->modelMatrix[i] = (float*)malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++) {
            objeto->modelMatrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    fclose(arquivo);
    return objeto;
}

//Altera a modelMatrix de um objeto para redimenciona-lo segundo os par�metros escalaX, escalaY e escalaZ
void escalaObjeto(tObjeto3d *objeto, float escalaX, float escalaY, float escalaZ)
{
    float **matrizHomogeneaEscala = (float**) malloc(4*sizeof(float*));
    for(int i=0; i < 4; i++)
    {
        matrizHomogeneaEscala[i] = (float*) malloc(4*sizeof(float));
    }

    criaIdentidade4d(matrizHomogeneaEscala);

    matrizHomogeneaEscala[0][0] = escalaX;
    matrizHomogeneaEscala[1][1] = escalaY;
    matrizHomogeneaEscala[2][2] = escalaZ;

    //Escala os pontos e salva-os
    moverParaOrigemMultiplicarERetornar(matrizHomogeneaEscala, objeto->modelMatrix);

    
    //Libera o espaço da matriz de escala criada
    for(int i=0; i<4; i++)
    {
        free(matrizHomogeneaEscala[i]);
    }
    free(matrizHomogeneaEscala);
}

//Altera a modelMatrix de um objeto para translada-lo segundo os par�metros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ) 
{
    float **matrizHomogeneaTranslacao = (float**) malloc(4*sizeof(float*));
    for(int i=0; i < 4; i++)
    {
        matrizHomogeneaTranslacao[i] = (float*) malloc(4*sizeof(float));
    }

    criaIdentidade4d(matrizHomogeneaTranslacao);

    matrizHomogeneaTranslacao[0][3] = transX;
    matrizHomogeneaTranslacao[1][3] = transY;
    matrizHomogeneaTranslacao[2][3] = transZ;

    multMatriz4d(matrizHomogeneaTranslacao, objeto->modelMatrix);

    //Libera o espaço da matriz de escala criada
    for(int i=0; i<4; i++)
    {
        free(matrizHomogeneaTranslacao[i]);
    }

    free(matrizHomogeneaTranslacao);
}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo X segundo o angulo informado
void rotacionaObjetoEixoX(tObjeto3d *objeto, float angulo)
{
    //Cria a matriz de rotação do eixo X
    float **matriz4dRotacao = (float**) malloc(4*sizeof(float*));
    for(int i=0; i<4; i++)
    {
        matriz4dRotacao[i] = (float*) malloc(4*sizeof(float));
    }

    //Inicializa a matriz
    criaIdentidade4d(matriz4dRotacao);
    matriz4dRotacao[1][1] = cosf(angulo);
    matriz4dRotacao[1][2] = -sinf(angulo);
    matriz4dRotacao[2][1] = sinf(angulo);
    matriz4dRotacao[2][2] = cosf(angulo);

    //Rotaciona os pontos e salva-os
    moverParaOrigemMultiplicarERetornar(matriz4dRotacao, objeto->modelMatrix);


    //Libera o espaço da matriz de rotação criada
    for(int i=0; i<4; i++)
    {
        free(matriz4dRotacao[i]);
    }
    free(matriz4dRotacao);
    
}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Y segundo o angulo informado
void rotacionaObjetoEixoY(tObjeto3d *objeto, float angulo)
{
    //Cria a matriz de rotação do eixo Y
    float **matriz4dRotacao = (float**) malloc(4*sizeof(float*));
    for(int i=0; i<4; i++)
    {
        matriz4dRotacao[i] = (float*) malloc(4*sizeof(float));
    }

    //Inicializa a matriz
    criaIdentidade4d(matriz4dRotacao);
    matriz4dRotacao[0][0] = cosf(angulo);
    matriz4dRotacao[0][2] = -sinf(angulo);
    matriz4dRotacao[2][0] = sinf(angulo);
    matriz4dRotacao[2][2] = cosf(angulo);

    //Rotaciona os pontos do objeto
    moverParaOrigemMultiplicarERetornar(matriz4dRotacao, objeto->modelMatrix);


    //Libera o espaço da matriz de rotação criada
    for(int i=0; i<4; i++)
    {
        free(matriz4dRotacao[i]);
    }
    free(matriz4dRotacao);
}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Z segundo o angulo informado
void rotacionaObjetoEixoZ(tObjeto3d *objeto, float angulo)
{
    //Cria a matriz de rotação do eixo Z
    float **matriz4dRotacao = (float**) malloc(4*sizeof(float*));
    for(int i=0; i<4; i++)
    {
        matriz4dRotacao[i] = (float*) malloc(4*sizeof(float));
    }

    //Inicializa a matriz
    criaIdentidade4d(matriz4dRotacao);
    matriz4dRotacao[0][0] = cosf(angulo);
    matriz4dRotacao[0][1] = -sinf(angulo);
    matriz4dRotacao[1][0] = sinf(angulo);
    matriz4dRotacao[1][1] = cosf(angulo);


    //Rotaciona os pontos do objeto e salva-os
    moverParaOrigemMultiplicarERetornar(matriz4dRotacao, objeto->modelMatrix);
    //multMatriz4d(matriz4dRotacao, objeto->modelMatrix);


    //Libera o espaço da matriz de rotação criada
    for(int i=0; i<4; i++)
    {
        free(matriz4dRotacao[i]);
    }
    free(matriz4dRotacao);
}

//Imprime um objeto no terminal
void imprimeObjetoDBG(tObjeto3d *objeto) {
    // Imprime o número de pontos e arestas
    printf("Número de Pontos: %d\n", objeto->nPontos);
    printf("Número de Arestas: %d\n", objeto->nArestas);

    // Imprime as coordenadas dos pontos
    printf("Pontos:\n");
    for (int i = 0; i < objeto->nPontos; i++) {
        printf("Ponto %d: (%1.2f, %1.2f, %1.2f)\n", i, objeto->pontos[i][0], objeto->pontos[i][1], objeto->pontos[i][2]);
    }

    // Imprime as arestas (conexões entre os pontos)
    printf("Arestas:\n");
    for (int i = 0; i < objeto->nArestas; i++) {
        printf("Aresta %d: Ponto %d -> Ponto %d\n", i, objeto->arestas[i][0], objeto->arestas[i][1]);
    }

    // Imprime a matriz de modelagem 4x4
    printf("Matriz de Modelagem:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%1.2f ", objeto->modelMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

//Desaloca o objeto
void desalocaObjeto(tObjeto3d *objeto){
    if (objeto != NULL) {
        for (int i = 0; i < objeto->nPontos; i++) {
            free(objeto->pontos[i]);
        }
        free(objeto->pontos);

        for (int i = 0; i < objeto->nArestas; i++) {
            free(objeto->arestas[i]);
        }
        free(objeto->arestas);

        for (int i = 0; i < 4; i++) {
            free(objeto->modelMatrix[i]);
        }
        free(objeto->modelMatrix);

        free(objeto);
    }
}

void moverParaOrigemMultiplicarERetornar(float **matriz4d, float **modelMatrix)
{
    float tempX = modelMatrix[0][3];
    float tempY = modelMatrix[1][3];
    float tempZ = modelMatrix[2][3];

    modelMatrix[0][3] = 0.0f;
    modelMatrix[1][3] = 0.0f;
    modelMatrix[2][3] = 0.0f;

    multMatriz4d(matriz4d, modelMatrix);

    modelMatrix[0][3] = tempX;
    modelMatrix[1][3] = tempY;
    modelMatrix[2][3] = tempZ;
}



