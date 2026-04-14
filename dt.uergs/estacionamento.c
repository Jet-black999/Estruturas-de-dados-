#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAGAS 10

typedef struct veiculo {
    char placa[8];
    int manobras;
    struct veiculo *proximo;
} veiculo;

static void push_node(veiculo **pilha, veiculo *node) {
    node->proximo = *pilha;
    *pilha = node;
}

static veiculo *pop_node(veiculo **pilha) {
    veiculo *topo;

    if (*pilha == NULL) {
        return NULL;
    }

    topo = *pilha;
    *pilha = topo->proximo;
    topo->proximo = NULL;
    return topo;
}

static veiculo *criar_veiculo(const char *placa) {
    veiculo *novo = (veiculo *)malloc(sizeof(veiculo));

    if (novo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    strncpy(novo->placa, placa, 7);
    novo->placa[7] = '\0';
    novo->manobras = 0;
    novo->proximo = NULL;

    return novo;
}

static int estacionar(veiculo **p1, const char *placa, int *ocupadas) {
    veiculo *novo;

    if (*ocupadas >= MAX_VAGAS) {
        return 0;
    }

    novo = criar_veiculo(placa);
    push_node(p1, novo);
    (*ocupadas)++;

    return 1;
}

static int retirar_carro(veiculo **p1, veiculo **p2, const char *placa, int *manobras) {
    veiculo *carro;

    while (*p1 != NULL && strcmp((*p1)->placa, placa) != 0) {
        carro = pop_node(p1);
        carro->manobras++;
        push_node(p2, carro);
    }

    if (*p1 == NULL) {
        while (*p2 != NULL) {
            push_node(p1, pop_node(p2));
        }
        return 0;
    }

    carro = pop_node(p1);
    *manobras = carro->manobras;
    free(carro);

    while (*p2 != NULL) {
        push_node(p1, pop_node(p2));
    }

    return 1;
}

static void liberar_pilha(veiculo **pilha) {
    veiculo *atual;

    while (*pilha != NULL) {
        atual = pop_node(pilha);
        free(atual);
    }
}

int main(void) {
    veiculo *p1 = NULL;
    veiculo *p2 = NULL;
    char operacao;
    char placa[8];
    int ocupadas = 0;
    int manobras = 0;

    /*
     * Entrada por linha:
     * E placa  ou  1 placa -> entrada
     * S placa  ou  2 placa -> saida
     */
    while (scanf(" %c %7s", &operacao, placa) == 2) {
        if (operacao == 'E' || operacao == 'e' || operacao == '1') {
            if (estacionar(&p1, placa, &ocupadas)) {
                printf("Carro %s entrou no estacionamento.\n", placa);
            } else {
                printf("Sem vaga: carro %s foi embora.\n", placa);
            }
        } else if (operacao == 'S' || operacao == 's' || operacao == '2') {
            if (retirar_carro(&p1, &p2, placa, &manobras)) {
                ocupadas--;
                printf("Carro %s saiu. Foi manobrado %d vez(es).\n", placa, manobras);
            } else {
                printf("Carro %s nao encontrado no estacionamento.\n", placa);
            }
        } else {
            printf("Operacao invalida: %c\n", operacao);
        }
    }

    liberar_pilha(&p1);
    liberar_pilha(&p2);

    return 0;
}
