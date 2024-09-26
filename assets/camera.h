#ifndef camera_h
#define camera_h

typedef struct camera
{
    float* posicao;
    float* foco;
    float* cima;
    float** viewMatrix;
} Camera;

Camera* criaCamera(
    float posX,
    float posY,
    float posZ,

    float focoX,
    float focoY,
    float focoZ
);

void defineCamera(Camera* camera);

void desalocaCamera(Camera* camera);

#endif