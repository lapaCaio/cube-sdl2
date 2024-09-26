# Cube SDL2 Project

Este projeto implementa a renderização de um objeto 3D em C usando a biblioteca SDL2. O código permite a manipulação do objeto através de várias transformações, incluindo rotação, translação e escala, que são aplicadas usando uma matriz de transformação (`modelMatrix`).

## Grupo
Caio Pereira Lapa, Gustavo Provete de Andrade, Ruan Vieira Ribeiro

## Estrutura do Projeto

```plaintext
/cube-sdl2
├── assets/                  # Arquivos de cabeçalho (.h) e arquivos de código (.c)
│   ├── algebra.c
│   ├── algebra.h
│   ├── objeto.c
│   ├── objeto.h
│   ├── tela.c
│   └── tela.h
├── debug/                   # Arquivos de debug
├── src/                  
│   ├── include/ 
│   │   └── SDL2/
│   └── lib/ 
│       ├── cmake/
│       └── pkgconfig/
├── cubo.dcg                 # Arquivo de definição do objeto 3D (cubo)
├── main.c                   # Arquivo principal 
├── Makefile                 # Script de build
├── README.md                # Documentação do projeto
└── SDL2.dll                 # Biblioteca SDL2 necessária para rodar o projeto
```

## Controles

- **W** - Move para cima
- **S** - Move para baixo
- **A** - Move para a esquerda
- **D** - Move para a direita
- **LSHIFT** - Move para frente (Necessita implementar perspectiva)
- **LCTRL** - Move para trás (Necessita implementar perspectiva)
- **MouseWheelUp** - Aumenta o tamanho do objeto
- **MouseWheelDown** - Diminui o tamanho do objeto
- **Y** e **H** - Rotaciona no eixo X, aumentando e diminuindo o ângulo
- **G** e **J** - Rotaciona no eixo Y, aumentando e diminuindo o ângulo
- **I** e **K** - Rotaciona no eixo Z, aumentando e diminuindo o ângulo

## Descrição do Projeto

Este projeto aborda as transformações de objetos na disciplina de Computação Gráfica, com foco na manipulação de um cubo tridimensional. Utilizando a biblioteca **SDL2**, foram implementadas funções para realizar transformações lineares, como:

- **Multiplicação de matrizes**: Permite a combinação de transformações para aplicar mudanças na posição e orientação do objeto.
- **Homogenização de pontos**: Assegura que as operações de transformação preservem a integridade do objeto, evitando deformações.

Essas transformações possibilitam alterar a posição dos pontos do objeto no espaço tridimensional, mantendo a forma original do cubo.

As funcionalidades implementadas até o momento incluem:

- **Translação**: Mover o objeto para diferentes direções (cima, baixo, esquerda, direita).
- **Rotação**: Rotacionar o objeto em torno dos eixos X, Y e Z.
- **Escala**: Aumentar ou diminuir o tamanho do objeto.
- **Angulação**: Ajustar o ângulo de rotação do objeto em torno dos eixos, modificando sua orientação no espaço.

**Nota**: As opções de mover para frente e mover para trás ainda não foram implementadas, pois é necessário desenvolver funções para gerar a noção de perspectiva.


## Arquivo de Objeto (cubo.dcg)

O arquivo de objetos define um objeto tridimensional a partir de seus vértices e arestas. A estrutura do arquivo de definição de objetos é a seguinte:

- Uma linha contendo um inteiro que informa a quantidade de vértices listados a seguir;
- Uma linha para cada vértice do objeto, sendo que em cada linha constam 3 floats representando, respectivamente, as coordenadas x, y e z do vértice;
- Uma linha contendo um inteiro que informa a quantidade de arestas listadas a seguir;
- Uma linha para cada aresta do objeto, sendo que em cada linha constam 2 inteiros representando os vértices que formam a aresta.

```plaintext
8
-5 5 1
5 5 1
5 -5 1
-5 -5 1
-5 5 11
5 5 11
5 -5 11
-5 -5 11
12
0 1
1 2
2 3
3 0
4 5
5 6
6 7
7 4
0 4
1 5
2 6
3 7
```
