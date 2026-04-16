#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int valor;
    struct node* proximo;
} node;

void remover(node **lista) {
    node *remover = NULL;

    if (*lista != NULL) {
        remover = *lista;
        *lista = remover->proximo;
        free(remover);
    } else {
        printf("A pilha esta vazia!\n");
    }
}

void inserir(node **lista, int valor) {
    node *aux = (node *)malloc(sizeof(node));

    if (aux == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    aux->valor = valor;
    aux->proximo = *lista;
    *lista = aux;
}

void listar(node *lista) {
    if (lista == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    while (lista != NULL) {
        printf("%d ", lista->valor);
        lista = lista->proximo;
    }
    printf("\n");
}

void menu() {
    printf("\n--- Console Administrativo da Pilha ---\n");
    printf("1. Inserir elemento no topo (Push)\n");
    printf("2. Remover elemento do topo (Pop)\n");
    printf("3. Listar pilha\n");
    printf("0. Encerrar execucao\n");
    printf("Diretiva de execucao: ");
}

int main() {
    node *lista = NULL;
    int num, op = -1;

    do {
        menu();
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Informe o valor numerico a ser empilhado: ");
                scanf("%d", &num);
                inserir(&lista, num);
                break;
            case 2:
                remover(&lista);
                break;
            case 3:
                listar(lista);
                break;
            case 0:
                printf("Saindo do programa...\n");
                while (lista != NULL) {
                    remover(&lista);
                }
                break;
            default:
                printf("Diretiva invalida. Submeta uma instrucao valida.\n");
        }
    } while (op != 0);

    return 0;
}
