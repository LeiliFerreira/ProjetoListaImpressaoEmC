#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[100];
} Arquivo;

struct No {
    Arquivo dado;
    struct No *prox;
};

typedef struct{
    struct No *inicio;
} Lista;

void menu() {
    printf("\n****************************************\n");
	printf("******* Gerenciador de Impressão *******\n\n");
	printf("Menu de operações\n\n");
	printf("1 - Adicionar um arquivo para impressão\n");
	printf("2 - Remover um arquivo da fila de impressão\n");
	printf("3 - Listar trabalhos da fila de impressão\n");
	printf("4 - Limpar fila de impressão\n");
	printf("5 - Guardar fila de impressão\n");
	printf("6 - Restaurar fila de impressão\n");
	printf("7 - Sair do Gerenciador de Impressão\n\n");

	printf("Digite a opção desejada: ");
}

void ler(Arquivo *pe) {
	scanf("%s", pe->nome);
}

void inserir_inicio(Lista *plista, Arquivo dado) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    novo->dado = dado;
    novo->prox = plista->inicio;
    plista->inicio = novo;
}

void mostrar(Lista lista) {
    struct No * pi;
	for (pi = lista.inicio; pi != NULL; pi = pi->prox) {
    printf("%s\n", pi->dado.nome);}
}

void deletarItem(Lista *plista) {
	if (plista -> inicio == NULL) {
		printf("Lista vazia!\n");
	} else {
		struct No* pi = plista -> inicio;
		plista -> inicio = pi->prox;
		free(pi);
	}
}

void deletarLista(Lista *plista) {
	struct No* pi;
	while (plista -> inicio != NULL) {
	pi = plista -> inicio;
	plista -> inicio = pi ->prox;
	free(pi);
	}
}

void salvar(Lista *lista) {
	FILE *file = fopen("lista_para_impressao.txt", "w");
	struct No* pi;
	for (pi = lista->inicio; pi != NULL; pi = pi->prox) {
  	fwrite(pi->dado.nome, strlen(pi->dado.nome), 1, file);
  	fwrite("\n", sizeof(char[1]), 1, file);

	}
	fclose(file);
}

void restaurar(Lista lista) {

	FILE *Arquivo;
	char ch[100];

	Arquivo = fopen("lista_para_impressao.txt", "r");

	if (Arquivo == NULL) {
	printf("O arquivo não existe");
	return 1;
	}

	while (fgets(ch, 100, Arquivo) != NULL) {
	printf("\nArquivo recuperado:\n "); 
	printf("%s", ch);
	}

	fclose(Arquivo);
	return 0;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	Lista lista;
  	lista.inicio = NULL;
  	int op;
  	menu ();
  	scanf("%d", &op);
  	while (op != 7) {
    	if (op ==1) {
        	Arquivo e;
          	ler(&e);
          	inserir_inicio(&lista, e);
       	} else if (op == 3) {
        	printf("\nArquivos existentes: \n\n");
		mostrar(lista);
   		} else if(op == 2) {
    		deletarItem(&lista);
		} else if (op == 4) {
			deletarLista(&lista);
		} else if (op == 5) {
		salvar(&lista);
		} else if(op == 6) {
			restaurar(lista);
		}

		menu();
      	scanf("%d", &op);
		}		
	if (op == 7) {
    sleep(1);
    system("cls");
    printf("Finalizando...");
    sleep(2);
    system("cls");
    printf("Você saiu do gerenciador!");
	}
}
