#ifndef projecao_h
#define projecao_h

typedef struct projecao
{
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;
    float** projectionMatrix;
} Projecao;

Projecao* criaProjecao();

void defineProjecao(Projecao* projecao);

void desalocaProjecao(Projecao* projecao);

#endif