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
    float posZ
);

void defineCamera(Camera* camera, float* foco);

void desalocaCamera(Camera* camera);

#endif