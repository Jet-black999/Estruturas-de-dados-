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
    if (*pilha == NULL) return NULL;
    
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
    if (*ocupadas >= MAX_VAGAS) return 0;
    veiculo *novo = criar_veiculo(placa);
    push_node(p1, novo);
    (*ocupadas)++;
    return 1;
}

static int retirar_carro(veiculo **p1, veiculo **p2, const char *placa, int *manobras) {
    veiculo *carro;

    // Desempilha P1 para P2 ate achar o carro
    while (*p1 != NULL && strcmp((*p1)->placa, placa) != 0) {
        carro = pop_node(p1);
        carro->manobras++; // Incrementa manobra ao ir para a rua
        push_node(p2, carro);
    }

    // Se a pilha esvaziou, o carro nao estava la
    if (*p1 == NULL) {
        while (*p2 != NULL) push_node(p1, pop_node(p2));
        return 0;
    }

    // Carro encontrado, remove definitivamente
    carro = pop_node(p1);
    *manobras = carro->manobras;
    free(carro);

    // Retorna os carros da P2 para a P1 (nao conta como manobra nova)
    while (*p2 != NULL) {
        push_node(p1, pop_node(p2));
    }

    return 1;
}

// NOVA FUNCAO: Exibe o estado da pilha sem altera-la
static void mostrar_estacionamento(veiculo *p1, int ocupadas) {
    printf("\n--- ESTADO DO ESTACIONAMENTO [%d/%d VAGAS] ---\n", ocupadas, MAX_VAGAS);
    if (p1 == NULL) {
        printf("[VAZIO]\n");
        return;
    }
    
    veiculo *atual = p1;
    printf("[TOPO - SAIDA]\n");
    while (atual != NULL) {
        printf(" -> Placa: %s | Manobras realizadas: %d\n", atual->placa, atual->manobras);
        atual = atual->proximo;
    }
    printf("[FUNDO - FIM DO BECO]\n");
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
    int opcao;
    char placa[8];
    int ocupadas = 0;
    int manobras = 0;

    do {
        printf("\n========================================\n");
        printf("1. Estacionar Carro (Entrada)\n");
        printf("2. Retirar Carro (Saida)\n");
        printf("3. Verificar Estacionamento (Auditoria)\n");
        printf("0. Sair\n");
        printf("========================================\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa buffer
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                if (ocupadas >= MAX_VAGAS) {
                    printf("\n[AVISO] Estacionamento LOTADO. O carro não pode entrar.\n");
                    break;
                }
                printf("Digite a placa do carro: ");
                scanf("%7s", placa);
                if (estacionar(&p1, placa, &ocupadas)) {
                    printf("\n[OK] Carro %s estacionado com sucesso.\n", placa);
                }
                break;

            case 2:
                if (ocupadas == 0) {
                    printf("\n[AVISO] Estacionamento ja esta vazio.\n");
                    break;
                }
                printf("Digite a placa do carro a retirar: ");
                scanf("%7s", placa);
                if (retirar_carro(&p1, &p2, placa, &manobras)) {
                    ocupadas--;
                    printf("\n[OK] Carro %s saiu. Foi manobrado %d vez(es).\n", placa, manobras);
                } else {
                    printf("\n[ERRO] Carro %s nao encontrado.\n", placa);
                }
                break;

            case 3:
                mostrar_estacionamento(p1, ocupadas);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberar_pilha(&p1);
    liberar_pilha(&p2);

    return 0;
}