#include <stdio.h>
#include <SDL2/SDL.h>
#include "objeto.h"

//L� as informa��es de um arquivo e as carrega num novo objeto alocado
tObjeto3d *carregaObjeto(char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    tObjeto3d *objeto = (tObjeto3d*)malloc(sizeof(tObjeto3d));
    if (objeto == NULL) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return NULL;
    }

    // Lê a quantidade de pontos
    fscanf(arquivo, "%d", &(objeto->nPontos));

    // Aloca memória para os pontos
    objeto->pontos = (float**)malloc(objeto->nPontos * sizeof(float*));
    for (int i = 0; i < objeto->nPontos; i++) {
        objeto->pontos[i] = (float*)malloc(3 * sizeof(float));
        fscanf(arquivo, "%f %f %f", &objeto->pontos[i][0], &objeto->pontos[i][1], &objeto->pontos[i][2]);
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
void escalaObjeto(tObjeto3d *objeto, float escalaX, float escalaY, float escalaZ){

}

//Altera a modelMatrix de um objeto para translada-lo segundo os par�metros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ){

}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo X segundo o angulo informado
void rotacionaObjetoEixoX(tObjeto3d *objeto, float angulo){

}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Y segundo o angulo informado
void rotacionaObjetoEixoY(tObjeto3d *objeto, float angulo){

}

//Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo Z segundo o angulo informado
void rotacionaObjetoEixoZ(tObjeto3d *objeto, float angulo){

}

//Imprime um objeto no terminal
void imprimeObjetoDBG(tObjeto3d *objeto){

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

