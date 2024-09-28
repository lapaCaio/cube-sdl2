#include "projecao.h"
#include "algebra.h"
#include <stdlib.h>

void defineProjecaoPerspectiva(Projecao* projecao);
void defineProjecaoOrtografica(Projecao* projecao);

Projecao* criaProjecao(
    ProjecaoTipo projecaoTipo, 
    float right,
    float left, 
    float top, 
    float bottom, 
    float near, 
    float far)
{
    Projecao* novaProjecao = malloc(sizeof(Projecao));

    if(novaProjecao == NULL)
    {
        return NULL;
    }
    
    novaProjecao->left = left;
    novaProjecao->right = right;
    novaProjecao->top = top;
    novaProjecao->bottom = bottom;
    novaProjecao->near = near;
    novaProjecao->far = far;


    novaProjecao->projectionMatrix = alocaIdentidade4d();

    defineProjecao(novaProjecao, projecaoTipo);
    
    return novaProjecao;
}

void defineProjecao(Projecao* projecao, ProjecaoTipo projecaoTipo)
{
    if(projecaoTipo == ORTOGRAFICA)
    {
        defineProjecaoOrtografica(projecao);
    } 
    else if(projecaoTipo == PERSPECTIVA)
    {
        defineProjecaoPerspectiva(projecao);
    }
}

void defineProjecaoPerspectiva(Projecao* projecao)
{
    projecao->projectionMatrix[3][3] = 0;
    projecao->projectionMatrix[3][2] = -1;

    projecao->projectionMatrix[0][0] = (2*projecao->near) / (projecao->right - projecao->left);
    projecao->projectionMatrix[0][2] = (projecao->right + projecao->left) / (projecao->right - projecao->left);

    projecao->projectionMatrix[1][1] = (2*projecao->near) / (projecao->top - projecao->bottom);
    projecao->projectionMatrix[1][2] = (projecao->top + projecao->bottom) / (projecao->top - projecao->bottom);

    projecao->projectionMatrix[2][2] = -(projecao->far + projecao->near) / (projecao->far - projecao->near);
    projecao->projectionMatrix[2][3] = -(2*projecao->far*projecao->near) / (projecao->far - projecao->near);
}

void defineProjecaoOrtografica(Projecao* projecao)
{
    projecao->projectionMatrix[3][3] = 1;
    projecao->projectionMatrix[3][2] = 0;

    projecao->projectionMatrix[0][0] = 2 / (projecao->right - projecao->left);
    projecao->projectionMatrix[1][1] = 2 / (projecao->top - projecao->bottom);
    projecao->projectionMatrix[2][2] = -2 / (projecao->far - projecao->near);

    projecao->projectionMatrix[0][3] = -(projecao->right + projecao->left) / (projecao->right - projecao->left);
    projecao->projectionMatrix[1][3] = -(projecao->top + projecao->bottom) / (projecao->top - projecao->bottom);
    projecao->projectionMatrix[2][3] = -(projecao->far + projecao->near) / (projecao->far - projecao->near);
}

void desalocaProjecao(Projecao* projecao)
{
    for(int i=0; i < 4; i++)
    {
        free(projecao->projectionMatrix[i]);
    }

    free(projecao->projectionMatrix);
    free(projecao);
}