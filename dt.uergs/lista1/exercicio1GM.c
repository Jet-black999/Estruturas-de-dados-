#include <stdio.h>
#include <stdlib.h>

#define TOTAL_FILAS 8

typedef struct ticket {
    int id;
    int classe;
    struct ticket *prox;
} Ticket;

/* Vetores de controle das 8 filas para operacoes O(1) */
Ticket *inicio[TOTAL_FILAS] = {NULL};
Ticket *fim[TOTAL_FILAS] = {NULL};
int tamanho[TOTAL_FILAS] = {0};

const char *nomes_filas[] = {
    "1. Premium Leste", "1. Premium Oeste",
    "2. Pista Leste  ", "2. Pista Oeste  ",
    "3. Gold Leste   ", "3. Gold Oeste   ",
    "4. Cadeira Leste", "4. Cadeira Oeste"
};

void imprimir_painel() {
    printf("\n==== PAINEL DE FILAS ====\n");
    for (int i = 0; i < TOTAL_FILAS; i++) {
        printf("%s: %d pessoas\n", nomes_filas[i], tamanho[i]);
    }
    printf("=========================\n");
}

void inserir_fila(int classe, int id) {
    Ticket *novo = (Ticket *)malloc(sizeof(Ticket));
    if (!novo) {
        printf("[ERRO] Falha de alocacao de memoria.\n");
        return;
    }
    novo->id = id;
    novo->classe = classe;
    novo->prox = NULL;

    int idx_leste = (classe - 1) * 2;
    int idx_oeste = idx_leste + 1;
    int fila_escolhida;

    /* Otimizacao: escolhe a menor fila */
    if (tamanho[idx_leste] <= tamanho[idx_oeste]) {
        fila_escolhida = idx_leste;
    } else {
        fila_escolhida = idx_oeste;
    }

    if (inicio[fila_escolhida] == NULL) {
        inicio[fila_escolhida] = novo;
    } else {
        fim[fila_escolhida]->prox = novo;
    }
    
    fim[fila_escolhida] = novo;
    tamanho[fila_escolhida]++;

    printf("\n[INSERCAO] Fã ID %d direcionado para %s\n", id, nomes_filas[fila_escolhida]);
    imprimir_painel();
}

void remover_fila(int fila_alvo) {
    if (inicio[fila_alvo] == NULL) {
        printf("\n[ERRO] Fila %s ja esta vazia.\n", nomes_filas[fila_alvo]);
        return;
    }

    Ticket *remover = inicio[fila_alvo];
    inicio[fila_alvo] = remover->prox;
    
    if (inicio[fila_alvo] == NULL) {
        fim[fila_alvo] = NULL; /* Reseta o ponteiro de fim se esvaziar */
    }

    printf("\n[SAIDA] Fã ID %d entrou no estadio via %s.\n", remover->id, nomes_filas[fila_alvo]);
    free(remover);
    tamanho[fila_alvo]--;

    imprimir_painel();
}

void imprimir_fila_especifica(int fila_alvo) {
    Ticket *atual = inicio[fila_alvo];
    printf("\n--- Detalhes %s ---\n", nomes_filas[fila_alvo]);
    if (!atual) {
        printf("Fila vazia.\n");
        return;
    }
    while (atual != NULL) {
        printf("[ID: %d] -> ", atual->id);
        atual = atual->prox;
    }
    printf("NULL\n");
}

int validar_ingresso() {
    int classe;
    do {
        printf("Selecione o tipo de ingresso:\n");
        printf("1 - Pista Premium (Vermelho)\n");
        printf("2 - Pista (Rosa)\n");
        printf("3 - Cadeira Gold (Verde)\n");
        printf("4 - Cadeira (Marrom)\n");
        printf("Opcao: ");
        scanf("%d", &classe);
        if (classe < 1 || classe > 4) {
            printf("[ERRO] Classe invalida. Tente novamente.\n");
        }
    } while (classe < 1 || classe > 4);
    return classe;
}

int menu() {
    int op;
    printf("\n--- MENU ESTADIO ---\n");
    printf("1. Chegada de Fã (Inserir)\n");
    printf("2. Entrada no Estadio (Remover)\n");
    printf("3. Inspecionar fila especifica\n");
    printf("4. Ver Painel de Filas\n");
    printf("0. Encerrar\n");
    printf("Opcao: ");
    scanf("%d", &op);
    return op;
}

int main() {
    int op, classe, id_contador = 1000; /* ID simulado para os fas */
    int fila_escolhida;

    while (1) {
        op = menu();
        switch (op) {
            case 1:
                classe = validar_ingresso();
                inserir_fila(classe, id_contador++);
                break;
            case 2:
                imprimir_painel();
                printf("Qual fila liberou a catraca? (0 a 7): ");
                scanf("%d", &fila_escolhida);
                if(fila_escolhida >= 0 && fila_escolhida < 8) {
                    remover_fila(fila_escolhida);
                } else {
                    printf("[ERRO] Indice invalido.\n");
                }
                break;
            case 3:
                printf("Qual fila deseja inspecionar? (0 a 7): ");
                scanf("%d", &fila_escolhida);
                if(fila_escolhida >= 0 && fila_escolhida < 8) {
                    imprimir_fila_especifica(fila_escolhida);
                } else {
                    printf("[ERRO] Indice invalido.\n");
                }
                break;
            case 4:
                imprimir_painel();
                break;
            case 0:
                printf("Encerrando sistema...\n");
                return 0;
            default:
                printf("[ERRO] Opcao invalida.\n");
        }
    }
}