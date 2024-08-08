# Regra principal que depende da regra 'compilaTrabalho'
all: compilaTrabalho

# Regra para compilar o trabalho, unindo todos os arquivos objeto
compilaTrabalho: main.o algebra.o objeto.o tela.o
	g++ main.o algebra.o objeto.o tela.o -o trabalhoCompilado -lSDL2

# Regras para criar os arquivos objeto individualmente
main.o: main.c
	gcc -c main.c

algebra.o: algebra.c
	gcc -c algebra.c

objeto.o: objeto.c
	gcc -c objeto.c

tela.o: tela.c
	gcc -c tela.c

# Regra para limpar os arquivos gerados
clean:
	rm -f *.o trabalhoCompilado

# Regra para executar o programa com um arquivo de entrada
run: compilaTrabalho
	./trabalhoCompilado $(file)

# Variável para armazenar o arquivo de entrada
file ?= cubo.dcg
