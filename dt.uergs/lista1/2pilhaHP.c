#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    TIPO_NUMERO,
    TIPO_OPERADOR
} TipoNo;

typedef struct pilha
{
    int valor;
    char operador;
    TipoNo tipo;
    struct pilha *prox;
} Pilha;

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

int eh_operador(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Pilha *criar_numero(int valor)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }

    novo->valor = valor;
    novo->operador = '\0';
    novo->tipo = TIPO_NUMERO;
    novo->prox = NULL;

    return novo;
}

Pilha *criar_operador(char operador)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }

    novo->valor = 0;
    novo->operador = operador;
    novo->tipo = TIPO_OPERADOR;
    novo->prox = NULL;

    return novo;
}

void empilhar_no(Pilha **topo, Pilha *novo)
{
    if (novo == NULL)
    {
        return;
    }

    novo->prox = *topo;
    *topo = novo;
}

void empilhar_numero(Pilha **topo, int valor)
{
    empilhar_no(topo, criar_numero(valor));
}

void empilhar_operador(Pilha **topo, char operador)
{
    empilhar_no(topo, criar_operador(operador));
}

Pilha *desempilhar(Pilha **topo)
{
    Pilha *removido;

    if (*topo == NULL)
    {
        return NULL;
    }

    removido = *topo;
    *topo = removido->prox;
    removido->prox = NULL;

    return removido;
}

void mostrar_pilha(Pilha *topo)
{
    Pilha *aux = topo;

    printf("\n========== PILHA ==========\n");

    if (aux == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }

    while (aux != NULL)
    {
        printf("Endereco do no: %p | Valor do no: ", (void *)aux);

        if (aux->tipo == TIPO_NUMERO)
        {
            printf("%d", aux->valor);
        }
        else
        {
            printf("%c", aux->operador);
        }

        printf(" | Endereco do proximo no: %p\n", (void *)aux->prox);
        aux = aux->prox;
    }
}

void inserir_expressao(Pilha **topo)
{
    char linha[200];
    int i = 0;

    printf("\nDigite a expressao pos-fixada por partes.\n");
    printf("Exemplos: 1 2 -  |  4 5 +  |  *\n");
    printf("Expressao: ");

    if (fgets(linha, sizeof(linha), stdin) == NULL)
    {
        printf("Erro ao ler a expressao.\n");
        return;
    }

    while (linha[i] != '\0')
    {
        if (isspace((unsigned char)linha[i]))
        {
            i++;
        }
        else if (eh_operador(linha[i]) && !isdigit((unsigned char)linha[i + 1]))
        {
            empilhar_operador(topo, linha[i]);
            i++;
        }
        else if (isdigit((unsigned char)linha[i]) ||
                 ((linha[i] == '-' || linha[i] == '+') && isdigit((unsigned char)linha[i + 1])))
        {
            char *fim_numero;
            long valor = strtol(&linha[i], &fim_numero, 10);

            empilhar_numero(topo, (int)valor);
            i = (int)(fim_numero - linha);
        }
        else
        {
            printf("Token invalido ignorado: %c\n", linha[i]);
            i++;
        }
    }

    printf("\nExpressao empilhada.\n");
    mostrar_pilha(*topo);
}

int calcular_operacao(int esquerdo, int direito, char operador, int *erro)
{
    *erro = 0;

    switch (operador)
    {
    case '+':
        return esquerdo + direito;
    case '-':
        return esquerdo - direito;
    case '*':
        return esquerdo * direito;
    case '/':
        if (direito == 0)
        {
            printf("Erro: divisao por zero.\n");
            *erro = 1;
            return 0;
        }
        return esquerdo / direito;
    default:
        printf("Operador invalido.\n");
        *erro = 1;
        return 0;
    }
}

void calcular_topo(Pilha **topo)
{
    Pilha *no_operador;
    Pilha *direito;
    Pilha *esquerdo;
    int resultado;
    int erro;

    if (*topo == NULL)
    {
        printf("\nPilha vazia. Nao ha expressao para calcular.\n");
        return;
    }

    if ((*topo)->tipo != TIPO_OPERADOR)
    {
        printf("\nO topo da pilha nao possui operador. Nada foi calculado.\n");
        mostrar_pilha(*topo);
        return;
    }

    if ((*topo)->prox == NULL || (*topo)->prox->prox == NULL)
    {
        printf("\nFaltam operandos para realizar a operacao.\n");
        return;
    }

    if ((*topo)->prox->tipo != TIPO_NUMERO || (*topo)->prox->prox->tipo != TIPO_NUMERO)
    {
        printf("\nOs dois proximos nos precisam ser numeros para calcular o operador do topo.\n");
        return;
    }

    no_operador = desempilhar(topo);
    direito = desempilhar(topo);
    esquerdo = desempilhar(topo);

    resultado = calcular_operacao(esquerdo->valor, direito->valor, no_operador->operador, &erro);

    if (erro)
    {
        empilhar_no(topo, esquerdo);
        empilhar_no(topo, direito);
        empilhar_no(topo, no_operador);
        return;
    }

    printf("\nCalculo realizado: %d %c %d = %d\n",
           esquerdo->valor, no_operador->operador, direito->valor, resultado);

    free(no_operador);
    free(direito);
    free(esquerdo);

    empilhar_numero(topo, resultado);
    mostrar_pilha(*topo);
}

void liberar_pilha(Pilha **topo)
{
    Pilha *remover;

    while (*topo != NULL)
    {
        remover = desempilhar(topo);
        free(remover);
    }
}

void menu()
{
    printf("\n========== CALCULADORA HP ==========\n");
    printf("1 - Inserir expressao na pilha\n");
    printf("2 - Mostrar pilha\n");
    printf("3 - Calcular operador do topo\n");
    printf("0 - Sair\n");
    printf("====================================\n");
}

int main()
{
    Pilha *topo = NULL;
    int op;

    do
    {
        menu();
        op = ler_inteiro("Escolha uma opcao: ");

        switch (op)
        {
        case 1:
            inserir_expressao(&topo);
            break;

        case 2:
            mostrar_pilha(topo);
            break;

        case 3:
            calcular_topo(&topo);
            break;

        case 0:
            liberar_pilha(&topo);
            printf("Programa encerrado.\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (op != 0);

    return 0;
}
