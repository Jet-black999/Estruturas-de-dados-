#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int valor;
    struct node *proximo;
} node;

void inserir(node **pilha, int valor) {
    node *novo = (node *)malloc(sizeof(node));

    if (novo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    novo->valor = valor;
    novo->proximo = *pilha;
    *pilha = novo;
}

int desempilhar(node **pilha, int *sucesso) {
    node *remover;
    int valor;

    if (*pilha == NULL) {
        *sucesso = 0;
        return 0;
    }

    remover = *pilha;
    valor = remover->valor;
    *pilha = remover->proximo;
    free(remover);

    *sucesso = 1;
    return valor;
}

void imprimir_pilha(node *pilha, const char *titulo) {
    node *atual = pilha;

    printf("\n%s\n", titulo);

    if (atual == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("Endereco do no: %p | Valor do no: %d | Endereco do proximo: %p\n",
               (void *)atual, atual->valor, (void *)atual->proximo);
        atual = atual->proximo;
    }
}

void liberar_pilha(node **pilha) {
    int sucesso;

    while (*pilha != NULL) {
        desempilhar(pilha, &sucesso);
    }
}

void menu() {
    printf("\n--- Menu da Pilha ---\n");
    printf("1. Inserir elemento\n");
    printf("2. Imprimir pilha original\n");
    printf("3. Localizar e remover elemento\n");
    printf("0. Sair\n");
    printf("Opcao: ");
}

void remover_valor(node **pilha_original, int valor_remover) {
    node *pilha2 = NULL;
    int valor;
    int sucesso;
    int encontrado = 0;

    if (*pilha_original == NULL) {
        printf("\nA pilha original esta vazia.\n");
        return;
    }

    imprimir_pilha(*pilha_original, "Pilha original:");

    while (*pilha_original != NULL) {
        if ((*pilha_original)->valor == valor_remover) {
            desempilhar(pilha_original, &sucesso);
            encontrado = 1;
            break;
        }

        valor = desempilhar(pilha_original, &sucesso);
        inserir(&pilha2, valor);
    }

    if (encontrado) {
        printf("\nO valor %d foi removido da pilha.\n", valor_remover);
    } else {
        printf("\nO valor %d nao existe na pilha.\n", valor_remover);
    }

    imprimir_pilha(pilha2, "Pilha 2:");

    while (pilha2 != NULL) {
        valor = desempilhar(&pilha2, &sucesso);
        inserir(pilha_original, valor);
    }

    imprimir_pilha(*pilha_original, "Pilha original com o elemento removido:");
}

int main() {
    node *pilha_original = NULL;
    int op = -1;
    int valor;

    do {
        menu();
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Digite o valor a ser empilhado: ");
                scanf("%d", &valor);
                inserir(&pilha_original, valor);
                break;
            case 2:
                imprimir_pilha(pilha_original, "Pilha original:");
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                remover_valor(&pilha_original, valor);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (op != 0);

    liberar_pilha(&pilha_original);
    return 0;
}
