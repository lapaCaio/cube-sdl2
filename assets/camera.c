#include "camera.h"
#include "algebra.h"
#include <stdlib.h>

void defineCamera(Camera* camera, float* foco)
{
    camera->foco[0] = foco[0];
    camera->foco[1] = foco[1];
    camera->foco[2] = foco[2];

    float* vetorFrente = calcularVetor3d(camera->posicao, camera->foco);
    normalizarVetor3d(vetorFrente);
    
    float* vetorEsquerda = calcularProdutoVetorial3d(camera->cima, vetorFrente);
    normalizarVetor3d(vetorEsquerda);
    
    float* vetorCima = calcularProdutoVetorial3d(vetorFrente, vetorEsquerda);

    printf("VetorCima: (%f, %f, %f)\n", vetorCima[0], vetorCima[1], vetorCima[2]);

    camera->cima[0] = vetorCima[0];
    camera->cima[1] = vetorCima[1];
    camera->cima[2] = vetorCima[2];

    camera->viewMatrix[0][0] = vetorEsquerda[0];
    camera->viewMatrix[0][1] = vetorEsquerda[1];
    camera->viewMatrix[0][2] = vetorEsquerda[2];
    camera->viewMatrix[0][3] = -vetorEsquerda[0]*camera->posicao[0] -vetorEsquerda[1]*camera->posicao[1] -vetorEsquerda[2]*camera->posicao[2];

    camera->viewMatrix[1][0] = vetorCima[0];
    camera->viewMatrix[1][1] = vetorCima[1];
    camera->viewMatrix[1][2] = vetorCima[2];
    camera->viewMatrix[3][3] = -vetorCima[0]*camera->posicao[0] -vetorCima[1]*camera->posicao[1] -vetorCima[2]*camera->posicao[2];

    camera->viewMatrix[2][0] = vetorFrente[0];
    camera->viewMatrix[2][1] = vetorFrente[1];
    camera->viewMatrix[2][2] = vetorFrente[2];
    camera->viewMatrix[2][3] = -vetorFrente[0]*camera->posicao[0] -vetorFrente[1]*camera->posicao[1] -vetorFrente[2]*camera->posicao[2];


    free(vetorFrente);
    free(vetorCima);
    free(vetorEsquerda);
}

Camera* criaCamera(
    float posX,
    float posY,
    float posZ
)
{
    Camera* novaCamera = (Camera*) malloc(sizeof(Camera));

    if(novaCamera == NULL)
    {
        return  NULL;
    }
    
    novaCamera->posicao = (float*) malloc(sizeof(float)*3);
    novaCamera->foco = (float*) malloc(sizeof(float) * 3);
    novaCamera->cima = (float*) malloc(sizeof(float) * 3);

    novaCamera->posicao[0] = posX;
    novaCamera->posicao[1] = posY;
    novaCamera->posicao[2] = posZ;

    novaCamera->foco[0] = 0;
    novaCamera->foco[1] = 0;
    novaCamera->foco[2] = 0;

    novaCamera->cima[0] = 0;
    novaCamera->cima[1] = 1;
    novaCamera->cima[0] = 0;

    novaCamera->viewMatrix = alocaIdentidade4d();

    defineCamera(novaCamera, novaCamera->foco);

    return novaCamera;
}

void desalocaCamera(Camera* camera)
{
    if(camera == NULL)
    {
        printf("ERRO: Tentativa de desalocar uma camera NULL");
        exit(1);
    }

    free(camera->posicao);
    free(camera->foco);
    free(camera->cima);
    
    for(int i=0; i < 4; i++)
    {
        free(camera->viewMatrix[i]);
    }

    free(camera->viewMatrix);
    free(camera);
}