#include "projecao.h"
#include "algebra.h"

Projecao* criaProjecao()
{
    Projecao* novaProjecao = malloc(sizeof(Projecao));
    
    novaProjecao->left = 0;
    novaProjecao->right = 0;
    novaProjecao->top = 0;
    novaProjecao->bottom = 0;
    novaProjecao->near = 0;
    novaProjecao->far = 0;


    criaIdentidade4d(novaProjecao->projectionMatrix);
    
    
    return novaProjecao;
}

void defineProjecao(Projecao* projecao)
{

}