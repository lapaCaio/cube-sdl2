#include <stdio.h>
#include <stdlib.h>

//Ajusta valores de um matriz 4d para uma matriz identidade
void criaIdentidade4d(float **novaMatriz) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            novaMatriz[i][j] = 0.0f;
        } 
    }

    for(int i =0; i < 4; i++){
        novaMatriz[i][i] = 1.0f;
    }
}

//Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%1.2f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto) {
    float *resultado = (float *)malloc(4 * sizeof(float));  //LEMBRAR DE LIBERAR A MEMÓRIA DEPOIS

    // Multiplicação da matriz pelo vetor ponto
    for (int i = 0; i < 4; i++) {
        resultado[i] = 0.0f;  // Inicializa o elemento do resultado
        for (int j = 0; j < 4; j++) {
            resultado[i] += matriz[i][j] * ponto[j];
        }
    }

    return resultado; 
}

//Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB) {
    float **resultado = (float **)malloc(4 * sizeof(float *));

    for (int i = 0; i < 4; i++) {
        resultado[i] = (float *)malloc(4 * sizeof(float));
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultado[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                resultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrizB[i][j] = resultado[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        free(resultado[i]);
    }
    free(resultado);
}

// Função para converter pontos para coordenadas homogêneas
float** converterParaCoordenadasHomogeneas(float **pontos, int nPontos) {
    // Verificar se os dados estão corretamente alocados
    if (!pontos) {
        return NULL;
    }

    // Alocar memória para o vetor de coordenadas homogêneas
    float **homogeneas = (float **)malloc(nPontos * sizeof(float *));
    if (homogeneas == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < nPontos; i++) {
        homogeneas[i] = (float *)malloc(4 * sizeof(float)); // 4 coordenadas por ponto
        if (homogeneas[i] == NULL) {
            // Libera a memória alocada até o ponto onde falhou
            for (int j = 0; j < i; j++) {
                free(homogeneas[j]);
            }
            free(homogeneas);
            return NULL;
        }
        
        // Copiar coordenadas e adicionar o valor homogêneo
        homogeneas[i][0] = pontos[i][0]; // x
        homogeneas[i][1] = pontos[i][1]; // y
        homogeneas[i][2] = pontos[i][2]; // z
        homogeneas[i][3] = 1.0f; // w = 1 para coordenadas homogêneas
    }

    return homogeneas;
}

// Função para liberar a memória alocada para coordenadas homogêneas
void liberarCoordenadasHomogeneas(float **homogeneas, int nPontos) {
    if (homogeneas != NULL) {
        for (int i = 0; i < nPontos; i++) {
            free(homogeneas[i]);
        }
        free(homogeneas);
    }
}
