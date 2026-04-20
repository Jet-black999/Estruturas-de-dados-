#include <stdio.h>
#include <stdlib.h>

/* --------Exercicio 6 da lista---------------
Escreva um programa que insira valores em uma lista. Você pode permitir a remocao do primeiro
elemento da lista. Quando isso ocorrer, esse elemento deve ser inserido em uma pilha e removido
da lista. Você deve permitir ao usuario imprimir a lista e a pilha a qualquer momento.
resumindo:
tirando o elemento da lista o mesmo vai para pilha
*/

typedef struct node
{
    int valor;
    struct node *proximo;
} node;

void inserir_pilha(node **pilha, int valor)
{
    node *aux = (node *)malloc(sizeof(node));

    if (aux == NULL)
    {
        printf("Erro ao alocar memoria para a pilha.\n");
        return;
    }

    aux->valor = valor;
    aux->proximo = *pilha;
    *pilha = aux;
}

void inserir_lista(node **lista, int valor)
{
    node *novo = (node *)malloc(sizeof(node));
    node *aux;

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria para a lista.\n");
        return;
    }

    novo->valor = valor;
    novo->proximo = NULL;

    if (*lista == NULL)
    {
        *lista = novo;
    }
    else
    {
        aux = *lista;

        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }

        aux->proximo = novo;
    }
}

void remover_lista(node **lista, node **pilha)
{
    node *remover;

    if (*lista != NULL)
    {
        remover = *lista;
        *lista = remover->proximo;

        inserir_pilha(pilha, remover->valor);
        printf("Elemento %d removido da lista e inserido na pilha.\n", remover->valor);

        free(remover);
    }
    else
    {
        printf("A lista esta vazia!\n");
    }
}

void listar(node *lista)
{
    node *aux = lista;

    if (aux == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    printf("Lista: ");
    while (aux != NULL)
    {
        printf("%d ", aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}

void listar_pilha(node *pilha)
{
    node *aux = pilha;

    if (aux == NULL)
    {
        printf("Pilha vazia.\n");
        return;
    }

    printf("Pilha: ");
    while (aux != NULL)
    {
        printf("%d ", aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}

void liberar_estrutura(node **estrutura)
{
    node *remover;

    while (*estrutura != NULL)
    {
        remover = *estrutura;
        *estrutura = remover->proximo;
        free(remover);
    }
}

void menu()
{
    printf("\n===== MENU =====\n");
    printf("1 - Inserir valor na lista\n");
    printf("2 - Remover primeiro da lista e enviar para a pilha\n");
    printf("3 - Imprimir lista\n");
    printf("4 - Imprimir pilha\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    node *lista = NULL;
    node *pilha = NULL;
    int op = 0, valor;

    while (1)
    {
        menu();
        scanf("%d", &op);

        while (op < 1 || op > 5)
        {
            printf("Opcao invalida. Digite novamente: ");
            scanf("%d", &op);
        }

        switch (op)
        {
        case 1:
            printf("Digite o valor para adicionar na lista: ");
            scanf("%d", &valor);
            inserir_lista(&lista, valor);
            printf("Valor %d inserido na lista.\n", valor);
            break;

        case 2:
            remover_lista(&lista, &pilha);
            break;

        case 3:
            listar(lista);
            break;

        case 4:
            listar_pilha(pilha);
            break;

        case 5:
            printf("Saindo do programa.\n");
            liberar_estrutura(&lista);
            liberar_estrutura(&pilha);
            return 0;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    }
}
