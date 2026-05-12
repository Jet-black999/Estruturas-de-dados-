#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//tamanho padrao de ip
#define TAMIP 16

typedef struct No
{
    char ip[TAMIP];
    struct No *proximo;
} No;

//alocar no
No *criar_no(char ip[])
{
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    strncpy(novo->ip, ip, TAMIP - 1);
    novo->ip[TAMIP - 1] = '\0';
    novo->proximo = novo;

    return novo;
}

int lista_vazia(No *inicio)
{
    return inicio == NULL;
}
//inserir no no circulo 
void inserir_ip(No **inicio, char ip[])
{
    No *novo = criar_no(ip);
    No *ultimo;

    if (novo == NULL)
    {
        return;
    }

    if (lista_vazia(*inicio))
    {
        *inicio = novo;
        return;
    }

    ultimo = *inicio;
    while (ultimo->proximo != *inicio)
    {
        ultimo = ultimo->proximo;
    }

    ultimo->proximo = novo;
    novo->proximo = *inicio;
}

//listarr
void listar_ips(No *inicio)
{
    No *atual;

    if (lista_vazia(inicio))
    {
        printf("Lista de IPs vazia.\n");
        return;
    }

    atual = inicio;
    printf("\nLista circular de IPs:\n");
    do
    {
        printf("%s", atual->ip);
        atual = atual->proximo;

        if (atual != inicio)
        {
            printf(" -> ");
        }
    } while (atual != inicio);

    printf(" -> volta ao inicio\n\n");
}

void buscar_ip(No *inicio, char ip[])
{
    No *atual;
    int posicao = 1;

    if (lista_vazia(inicio))
    {
        printf("Lista de IPs vazia.\n");
        return;
    }

    atual = inicio;
    do
    {
        if (strcmp(atual->ip, ip) == 0)
        {
            printf("IP %s encontrado na posicao %d.\n", ip, posicao);
            return;
        }

        atual = atual->proximo;
        posicao++;
    } while (atual != inicio);

    printf("IP %s nao encontrado.\n", ip);
}

int menu(void)
{
    int opcao;

    printf("==================================\n");
    printf("1 - Inserir IP\n");
    printf("2 - Listar IPs\n");
    printf("3 - Buscar IP\n");
    printf("0 - Sair\n");
    printf("==================================\n");
    printf("Selecione a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}
//leberar a memoria/tava no exercicio circular que fi usei como base 
void liberar_lista(No *inicio)
{
    No *atual;
    No *proximo;

    if (lista_vazia(inicio))
    {
        return;
    }

    atual = inicio->proximo;
    while (atual != inicio)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(inicio);
}

int main(void)
{
    int op = -1;
    char ip[TAMIP];
    No *inicio = NULL;

    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            printf("Digite o IP: ");
            scanf(" %15s", ip);
            inserir_ip(&inicio, ip);
            break;

        case 2:
            listar_ips(inicio);
            break;

        case 3:
            printf("Digite o IP que deseja buscar: ");
            scanf(" %15s", ip);
            buscar_ip(inicio, ip);
            break;

        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (op != 0);

    
