#ifndef projecao_h
#define projecao_h

typedef enum projecaoTipo
{
    ORTOGRAFICA,
    PERSPECTIVA
} ProjecaoTipo;

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

Projecao* criaProjecao(
    ProjecaoTipo projecaoTipo, 
    float right,
    float left, 
    float top, 
    float bottom, 
    float near, 
    float far);

void defineProjecao(Projecao* projecao, ProjecaoTipo projecaoTipo);

void desalocaProjecao(Projecao* projecao);

#endif