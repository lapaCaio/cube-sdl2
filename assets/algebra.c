#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Ajusta valores de um matriz 4d para uma matriz identidade
void criaIdentidade4d(float **novaMatriz)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            novaMatriz[i][j] = 0.0f;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        novaMatriz[i][i] = 1.0f;
    }
}

// Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%1.2f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Multiplica uma matriz 4d por um ponto (x, y, z, w)
float *multMatriz4dPonto(float **matriz, float *ponto)
{
    float *resultado = (float *)malloc(4 * sizeof(float)); // LEMBRAR DE LIBERAR A MEMÓRIA DEPOIS

    for(int i=0; i < 4; i++)
    {
        resultado[i] = 0.0f;
    }

    // Multiplicação da matriz pelo vetor ponto
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultado[i] += matriz[i][j] * ponto[j];
        }
    }

    return resultado;
}

// Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB)
{
    float **resultado = (float **)malloc(4 * sizeof(float *));

    for (int i = 0; i < 4; i++)
    {
        resultado[i] = (float *)malloc(4 * sizeof(float));
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultado[i][j] = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                resultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrizB[i][j] = resultado[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        free(resultado[i]);
    }
    free(resultado);
}

float* calcularVetor3d(float* ponto3dInicio, float* ponto3dFim)
{
    float* vetor = malloc(sizeof(float)*3);

    for(int i=0; i < 3; i++)
    {
        vetor[i] = ponto3dFim[i] - ponto3dInicio[i];
    }

    return vetor;
}

float calcularMagnitudeVetor3d(float* vetor3d)
{
    float magnitude = 0.0f;

    for(int i=0; i < 3; i++)
    {
        magnitude += powf(vetor3d[i], 2);
    }

    return sqrt(magnitude);
}

void normalizarVetor3d(float** vetor3d)
{
    float magnitude = calcularMagnitudeVetor3d(vetor3d);

    for(int i=0; i < 3; i++)
    {
        (*vetor3d)[i] /= magnitude;
    }
}

float* calcularProdutoVetorial3d(float* vetor3d1, float*vetor3d2)
{
    float* produtoVetorial3d = malloc(sizeof(float)*3);

    produtoVetorial3d[0] = vetor3d1[1]*vetor3d2[2] - vetor3d1[2]*vetor3d2[1];
    produtoVetorial3d[1] = vetor3d1[2]*vetor3d2[0] - vetor3d1[0]*vetor3d2[2];
    produtoVetorial3d[2] = vetor3d1[0]*vetor3d2[1] - vetor3d1[1]*vetor3d2[0];

    return produtoVetorial3d;
}