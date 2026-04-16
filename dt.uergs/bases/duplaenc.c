#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

No *criar_no(int num)
{
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    novo->valor = num;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

void inicializar_lista(No *inicio, No *fim)
{
    inicio->anterior = NULL;
    inicio->proximo = fim;
    fim->anterior = inicio;
    fim->proximo = NULL;
}

int lista_vazia(No *inicio, No *fim)
{
    return inicio->proximo == fim;
}


//insercoes 


void inserir_no_inicio(No *inicio, No *fim, int num)
{
    No *novo = criar_no(num);
    No *primeiro;

    (void)fim;
    if (novo == NULL)
    {
        return;
    }

    primeiro = inicio->proximo;
    novo->anterior = inicio;
    novo->proximo = primeiro;
    inicio->proximo = novo;
    primeiro->anterior = novo;
}

void inserir_no_fim(No *inicio, No *fim, int num)
{
    No *novo = criar_no(num);
    No *ultimo;

    if (novo == NULL)
    {
        return;
    }

    (void)inicio;
    ultimo = fim->anterior;
    novo->anterior = ultimo;
    novo->proximo = fim;
    ultimo->proximo = novo;
    fim->anterior = novo;
}

void inserir_no_meio(No *inicio, No *fim, int num, int ant)
{
    No *aux;
    No *novo = criar_no(num);
    No *ultimo;

    if (novo == NULL)
    {
        return;
    }

    aux = inicio->proximo;
    while (aux != fim && aux->valor != ant)
    {
        aux = aux->proximo;
    }

    if (aux == fim)
    {
        ultimo = fim->anterior;
        novo->anterior = ultimo;
        novo->proximo = fim;
        ultimo->proximo = novo;
        fim->anterior = novo;
        return;
    }

    novo->anterior = aux;
    novo->proximo = aux->proximo;
    aux->proximo->anterior = novo;
    aux->proximo = novo;
}

//REMOCOES
void remover_inicio(No *inicio, No *fim)
{
    No *remover;

    if (lista_vazia(inicio, fim))
    {
        printf("A lista ja esta vazia.\n");
        return;
    }

    remover = inicio->proximo;
    inicio->proximo = remover->proximo;
    remover->proximo->anterior = inicio;
    free(remover);
    printf("Elemento do inicio removido!\n");
}

void remover_no_fim(No *inicio, No *fim)
{
    No *aux;

    if (lista_vazia(inicio, fim))
    {
        printf("A lista ja esta vazia!\n");
        return;
    }

    aux = fim->anterior;
    fim->anterior = aux->anterior;
    aux->anterior->proximo = fim;
    free(aux);
    printf("Ultimo elemento removido!\n");
}

void remover_no_meio(No *inicio, No *fim, int valor_busca)
{

    No *aux;

    if (lista_vazia(inicio, fim))
    {
        printf("A lista esta vazia!\n");
        return;
    }
    if (inicio->valor==valor_busca)
    {
        remover_inicio(inicio, fim);
        return;
    }
    
/* tenho que verificar se o valor selecionado não esta no inicio,
caso sim devo chamar a funcao remover no inicio*/
    aux = inicio->proximo;

    while (aux != fim && aux->valor != valor_busca)
    {
        aux = aux->proximo;
    }

    if (aux == fim)
    {
        printf("Valor %d nao encontrado na lista!\n", valor_busca);
        return;
    }

    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;

    free(aux);
    printf("Elemento %d removido com sucesso!\n", valor_busca);
}

void imprimir(No *inicio, No *fim)
{
    No *no = inicio->proximo;
    printf("\n\tLista: ");
    while (no != fim)
    {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

int menu(void)
{
    int opcao;

    printf("==================================\n");
    printf("1 - Inserir no Inicio\n");
    printf("2 - Inserir no Fim\n");
    printf("3 - Inserir no Meio\n");
    printf("4 - Imprimir Lista\n");
    printf("5 - Remover no inicio\n");
    printf("6 - Remover no meio\n");
    printf("7 - Remover no final\n");
    printf("0 - Sair\n");
    printf("==================================\n");
    printf("Selecione a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

void liberar_lista(No *inicio, No *fim)
{
    No *aux = inicio->proximo;
    No *prox;

    while (aux != fim)
    {
        prox = aux->proximo;
        free(aux);
        aux = prox;
    }

    free(inicio);
    free(fim);
}

int main(void)
{
    int op = -1;
    int anterior = 0;
    int valor = 0;
    No *inicio = criar_no(0);
    No *fim = criar_no(0);

    if (inicio == NULL || fim == NULL)
    {
        free(inicio);
        free(fim);
        return 1;
    }

    inicializar_lista(inicio, fim);

    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_inicio(inicio, fim, valor);
            break;

        case 2:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_fim(inicio, fim, valor);
            break;

        case 3:
            printf("Digite o novo valor e o valor de referencia (anterior): ");
            scanf("%d %d", &valor, &anterior);
            inserir_no_meio(inicio, fim, valor, anterior);
            break;

        case 4:
            imprimir(inicio, fim);
            break;

        case 5:
            remover_inicio(inicio, fim);
            break;

        case 6:
            printf("Digite o valor que voce quer buscar: ");
            scanf("%d", &valor);
            remover_no_meio(inicio, fim, valor);
            break;

        case 7:
            remover_no_fim(inicio, fim);
            break;

        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (op != 0);

    liberar_lista(inicio, fim);
    return 0;
}
