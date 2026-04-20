/*
---------------exercicio 5-----------------------

lista duplamente encadeada de ips

sempre que inserir um pc, deve ser criado um no com os dados do computador.
o usuario pode inserir no inicio, no fim, antes de um certo ip
ou depois de um certo ip, e tambem remover um ip da lista.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char ip[16];
    int patrimonio;
    struct node *anterior;
    struct node *proximo;
} node;

node *criar_no(const char *ip, int patrimonio)
{
    node *novo = (node *)malloc(sizeof(node));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }

    strncpy(novo->ip, ip, sizeof(novo->ip) - 1); //deixa uma posição para o \0=null
    novo->ip[sizeof(novo->ip) - 1] = '\0';
    novo->patrimonio = patrimonio;
    //iniciaçiza o ponteiro em NULL
    novo->anterior = NULL;
    novo->proximo = NULL;

    return novo;
}

void inserir_inicio(node **lista, const char *ip, int patrimonio)
{
    node *novo = criar_no(ip, patrimonio);

    if (novo == NULL)
    {
        return;
    }

    novo->proximo = *lista;

    if (*lista != NULL)
    {
        (*lista)->anterior = novo;
    }

    *lista = novo;
}

void inserir_fim(node **lista, const char *ip, int patrimonio)
{
    node *novo = criar_no(ip, patrimonio);
    node *aux;

    if (novo == NULL)
    {
        return;
    }

    if (*lista == NULL)
    {
        *lista = novo;
        return;
    }

    aux = *lista;
    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }

    aux->proximo = novo;
    novo->anterior = aux;
}

void inserir_antes_ip(node **lista, const char *ip_referencia, const char *novo_ip, int patrimonio)
{
    node *aux = *lista;
    node *novo;

    while (aux != NULL && strcmp(aux->ip, ip_referencia) != 0)
    {
        aux = aux->proximo;
    }

    if (aux == NULL)
    {
        printf("IP de referencia nao encontrado.\n");
        return;
    }

    if (aux->anterior == NULL)
    {
        inserir_inicio(lista, novo_ip, patrimonio);
        return;
    }

    novo = criar_no(novo_ip, patrimonio);
    if (novo == NULL)
    {
        return;
    }

    novo->proximo = aux;
    novo->anterior = aux->anterior;
    aux->anterior->proximo = novo;
    aux->anterior = novo;
}

void inserir_depois_ip(node **lista, const char *ip_referencia, const char *novo_ip, int patrimonio)
{
    node *aux = *lista;
    node *novo;

    while (aux != NULL && strcmp(aux->ip, ip_referencia) != 0)
    {
        aux = aux->proximo;
    }

    if (aux == NULL)
    {
        printf("IP de referencia nao encontrado.\n");
        return;
    }

    if (aux->proximo == NULL)
    {
        inserir_fim(lista, novo_ip, patrimonio);
        return;
    }

    novo = criar_no(novo_ip, patrimonio);
    if (novo == NULL)
    {
        return;
    }

    novo->anterior = aux;
    novo->proximo = aux->proximo;
    aux->proximo->anterior = novo;
    aux->proximo = novo;
}

void remover_ip(node **lista, const char *ip)
{
    node *aux = *lista;

    while (aux != NULL && strcmp(aux->ip, ip) != 0)
    {
        aux = aux->proximo;
    }

    if (aux == NULL)
    {
        printf("IP nao encontrado.\n");
        return;
    }

    if (aux->anterior != NULL)
    {
        aux->anterior->proximo = aux->proximo;
    }
    else
    {
        *lista = aux->proximo;
    }

    if (aux->proximo != NULL)
    {
        aux->proximo->anterior = aux->anterior;
    }

    printf("IP %s removido da lista.\n", aux->ip);
    free(aux);
}

void listar_lista(node *lista)
{
    node *aux = lista;

    if (aux == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    printf("Lista de computadores:\n");
    while (aux != NULL)
    {
        printf("IP: %s | Patrimonio: %d\n", aux->ip, aux->patrimonio);
        aux = aux->proximo;
    }
}

void menu()
{
    printf("\n===== MENU =====\n");
    printf("1 - Inserir no inicio\n");
    printf("2 - Inserir no fim\n");
    printf("3 - Inserir antes de um IP\n");
    printf("4 - Inserir depois de um IP\n");
    printf("5 - Listar computadores\n");
    printf("6 - Remover um IP\n");
    printf("7 - Sair\n");
    printf("Escolha uma opcao: ");
}

void liberar_lista(node **lista)
{
    node *aux;

    while (*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->proximo;
        free(aux);
    }
}

int main()
{
    node *lista = NULL;
    int op = 0;
    int patrimonio;
    char ip[16];
    char ip_referencia[16];

    while (1)
    {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("Digite o IP: ");
            scanf("%15s", ip);
            printf("Digite o patrimonio: ");
            scanf("%d", &patrimonio);
            inserir_inicio(&lista, ip, patrimonio);
            break;

        case 2:
            printf("Digite o IP: ");
            scanf("%15s", ip);
            printf("Digite o patrimonio: ");
            scanf("%d", &patrimonio);
            inserir_fim(&lista, ip, patrimonio);
            break;

        case 3:
            printf("Digite o IP de referencia: ");
            scanf("%15s", ip_referencia);
            printf("Digite o novo IP: ");
            scanf("%15s", ip);
            printf("Digite o patrimonio: ");
            scanf("%d", &patrimonio);
            inserir_antes_ip(&lista, ip_referencia, ip, patrimonio);
            break;

        case 4:
            printf("Digite o IP de referencia: ");
            scanf("%15s", ip_referencia);
            printf("Digite o novo IP: ");
            scanf("%15s", ip);
            printf("Digite o patrimonio: ");
            scanf("%d", &patrimonio);
            inserir_depois_ip(&lista, ip_referencia, ip, patrimonio);
            break;

        case 5:
            listar_lista(lista);
            break;

        case 6:
            printf("Digite o IP que deseja remover: ");
            scanf("%15s", ip);
            remover_ip(&lista, ip);
            break;

        case 7:
            printf("Saindo do programa.\n");
            liberar_lista(&lista);
            return 0;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    }
}
