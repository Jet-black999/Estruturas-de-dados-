/*
    Show do Guns

    Existem 4 tipos de ingresso e 2 filas para cada tipo:
    - Fila Leste
    - Fila Oeste

    Sempre que alguem entra ou sai de uma fila, o painel com os totais
    deve ser atualizado.
*/

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_FILAS 8
#define ENTRADA_LESTE 1
#define ENTRADA_OESTE 2

typedef struct ticket
{
    int num;
    int classe;
    struct ticket *prox;
} Ticket;

Ticket *inicio[TOTAL_FILAS] = {NULL};
Ticket *fim[TOTAL_FILAS] = {NULL};
int total[TOTAL_FILAS] = {0};

const char *nomes_filas[TOTAL_FILAS] = {
    "Fila 1 Leste - Pista Premium",
    "Fila 1 Oeste - Pista Premium",
    "Fila 2 Leste - Pista",
    "Fila 2 Oeste - Pista",
    "Fila 3 Leste - Cadeira Gold",
    "Fila 3 Oeste - Cadeira Gold",
    "Fila 4 Leste - Cadeira",
    "Fila 4 Oeste - Cadeira"};

const char *nomes_ingressos[4] = {
    "Pista Premium - vermelho",
    "Pista - rosa",
    "Cadeira Gold - verde",
    "Cadeira - marrom"};

void limpar_buffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int ler_inteiro(const char *mensagem)
{
    int valor;

    while (1)
    {
        printf("%s", mensagem);

        if (scanf("%d", &valor) == 1)
        {
            limpar_buffer();
            return valor;
        }

        printf("Entrada invalida. Digite um numero.\n");
        limpar_buffer();
    }
}

void menu()
{
    printf("\n========== MENU ==========\n");
    printf("1 - Inserir pessoa na fila\n");
    printf("2 - Remover pessoa da fila\n");
    printf("3 - Imprimir uma fila\n");
    printf("4 - Imprimir painel das filas\n");
    printf("0 - Sair\n");
    printf("==========================\n");
}

void imprimir_painel()
{
    int i;

    printf("\n========== PAINEL DAS FILAS ==========\n");
    for (i = 0; i < TOTAL_FILAS; i++)
    {
        printf("%d - %-32s | %d pessoa(s)\n", i + 1, nomes_filas[i], total[i]);
    }
    printf("======================================\n");
}

int validar_ingresso()
{
    int classe;

    do
    {
        printf("\nTipos de ingresso:\n");
        printf("1 - %s\n", nomes_ingressos[0]);
        printf("2 - %s\n", nomes_ingressos[1]);
        printf("3 - %s\n", nomes_ingressos[2]);
        printf("4 - %s\n", nomes_ingressos[3]);

        classe = ler_inteiro("Digite o codigo do ingresso: ");

        if (classe < 1 || classe > 4)
        {
            printf("Codigo de ingresso invalido. Tente novamente.\n");
        }
    } while (classe < 1 || classe > 4);

    return classe;
}

int validar_entrada()
{
    int entrada;

    do
    {
        printf("\nEntradas disponiveis:\n");
        printf("1 - Leste\n");
        printf("2 - Oeste\n");

        entrada = ler_inteiro("Digite a entrada escolhida: ");

        if (entrada != ENTRADA_LESTE && entrada != ENTRADA_OESTE)
        {
            printf("Entrada invalida. Tente novamente.\n");
        }
    } while (entrada != ENTRADA_LESTE && entrada != ENTRADA_OESTE);

    return entrada;
}

int indice_fila(int classe, int entrada)
{
    return (classe - 1) * 2 + (entrada - 1);
}

void mostrar_filas_do_ingresso(int classe)
{
    int leste = indice_fila(classe, ENTRADA_LESTE);
    int oeste = indice_fila(classe, ENTRADA_OESTE);

    printf("\nFilas para %s:\n", nomes_ingressos[classe - 1]);
    printf("1 - Leste: %d pessoa(s)\n", total[leste]);
    printf("2 - Oeste: %d pessoa(s)\n", total[oeste]);

    if (total[leste] < total[oeste])
    {
        printf("Sugestao: entrada Leste esta menor.\n");
    }
    else if (total[oeste] < total[leste])
    {
        printf("Sugestao: entrada Oeste esta menor.\n");
    }
    else
    {
        printf("Sugestao: as duas entradas estao com o mesmo tamanho.\n");
    }
}

void inserir_na_fila(int classe, int entrada, int numero_ticket)
{
    int indice = indice_fila(classe, entrada);
    Ticket *novo = (Ticket *)malloc(sizeof(Ticket));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    novo->num = numero_ticket;
    novo->classe = classe;
    novo->prox = NULL;

    if (inicio[indice] == NULL)
    {
        inicio[indice] = novo;
        fim[indice] = novo;
    }
    else
    {
        fim[indice]->prox = novo;
        fim[indice] = novo;
    }

    total[indice]++;

    printf("\nIngresso %d inserido em: %s.\n", numero_ticket, nomes_filas[indice]);
    imprimir_painel();
}

void inserir_pista_premium(int entrada, int numero_ticket)
{
    inserir_na_fila(1, entrada, numero_ticket);
}

void inserir_pista(int entrada, int numero_ticket)
{
    inserir_na_fila(2, entrada, numero_ticket);
}

void inserir_cadeira_gold(int entrada, int numero_ticket)
{
    inserir_na_fila(3, entrada, numero_ticket);
}

void inserir_cadeira(int entrada, int numero_ticket)
{
    inserir_na_fila(4, entrada, numero_ticket);
}

void inserir_por_tipo(int classe, int entrada, int numero_ticket)
{
    switch (classe)
    {
    case 1:
        inserir_pista_premium(entrada, numero_ticket);
        break;
    case 2:
        inserir_pista(entrada, numero_ticket);
        break;
    case 3:
        inserir_cadeira_gold(entrada, numero_ticket);
        break;
    case 4:
        inserir_cadeira(entrada, numero_ticket);
        break;
    }
}

int validar_fila()
{
    int fila;

    do
    {
        imprimir_painel();
        fila = ler_inteiro("Digite o numero da fila (1 a 8): ");

        if (fila < 1 || fila > TOTAL_FILAS)
        {
            printf("Fila invalida. Tente novamente.\n");
        }
    } while (fila < 1 || fila > TOTAL_FILAS);

    return fila - 1;
}

void remover_da_fila(int indice)
{
    Ticket *remover;

    if (inicio[indice] == NULL)
    {
        printf("\n%s esta vazia. Ninguem foi removido.\n", nomes_filas[indice]);
        return;
    }

    remover = inicio[indice];
    inicio[indice] = inicio[indice]->prox;

    if (inicio[indice] == NULL)
    {
        fim[indice] = NULL;
    }

    printf("\nIngresso %d saiu da %s e entrou no estadio.\n",
           remover->num, nomes_filas[indice]);

    free(remover);
    total[indice]--;

    imprimir_painel();
}

void imprimir_fila(int indice)
{
    Ticket *aux = inicio[indice];

    printf("\n========== %s ==========\n", nomes_filas[indice]);

    if (aux == NULL)
    {
        printf("Fila vazia.\n");
        return;
    }

    while (aux != NULL)
    {
        printf("Ingresso: %d | Classe: %d\n", aux->num, aux->classe);
        aux = aux->prox;
    }
}

void liberar_filas()
{
    int i;

    for (i = 0; i < TOTAL_FILAS; i++)
    {
        while (inicio[i] != NULL)
        {
            Ticket *remover = inicio[i];
            inicio[i] = inicio[i]->prox;
            free(remover);
        }

        fim[i] = NULL;
        total[i] = 0;
    }
}

int main()
{
    int op;
    int classe;
    int entrada;
    int fila;
    int numero_ticket = 1;

    do
    {
        menu();
        op = ler_inteiro("Escolha uma opcao: ");

        switch (op)
        {
        case 1:
            classe = validar_ingresso();
            mostrar_filas_do_ingresso(classe);
            entrada = validar_entrada();
            inserir_por_tipo(classe, entrada, numero_ticket);
            numero_ticket++;
            break;

        case 2:
            fila = validar_fila();
            remover_da_fila(fila);
            break;

        case 3:
            fila = validar_fila();
            imprimir_fila(fila);
            break;

        case 4:
            imprimir_painel();
            break;

        case 0:
            liberar_filas();
            printf("Sistema encerrado.\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (op != 0);

    return 0;
}
