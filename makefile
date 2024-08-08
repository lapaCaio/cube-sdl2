# Compilador e flags
CC = gcc
CFLAGS = -Wall -Iinclude `sdl2-config --cflags`

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin
ASSETS_DIR = assets

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/meu_projeto

# SDL2 flags
SDL2_LIBS = `sdl2-config --libs`

# Regra padrão
all: $(TARGET)

# Linkando o executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL2_LIBS)

# Compilando os arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Criar diretórios, se não existirem
$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
