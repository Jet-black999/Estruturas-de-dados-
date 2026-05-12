#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int valor;
    struct no *esq;
    struct no *dir;
} node;

static node *criar_no(int valor)
{
    node *novo = (node *)malloc(sizeof(node));

    if (novo == NULL)
    {
        printf("erro ao alocar memoria\n");
        exit(1);
    }

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

static void inserir_rec(node **tree, int valor)
{
    if (tree == NULL)
    {
        printf("arvore invalida\n");
        return;
    }

    if (*tree == NULL)
    {
        *tree = criar_no(valor);
        return;
    }

    if (valor == (*tree)->valor)
    {
        printf("valor ja existe na arvore\n");
        return;
    }

    if (valor < (*tree)->valor)
    {
        inserir_rec(&(*tree)->esq, valor);
    }
    else
    {
        inserir_rec(&(*tree)->dir, valor);
    }
}

void inserir(node **tree, int valor, int *raiz)
{
    if (tree == NULL)
    {
        printf("arvore invalida\n");
        return;
    }

    if (*tree == NULL)
    {
        *tree = criar_no(valor);

        if (raiz != NULL)
        {
            *raiz = valor;
        }

        return;
    }

    inserir_rec(tree, valor);
}

void listar(node *tree)
{
    if (tree == NULL)
    {
        return;
    }

    listar(tree->esq);
    printf("valor: %d | endereco: %p | esq: %p | dir: %p\n",
           tree->valor,
           (void *)tree,
           (void *)tree->esq,
           (void *)tree->dir);
    listar(tree->dir);
}

void liberar(node *tree)
{
    if (tree == NULL)
    {
        return;
    }

    liberar(tree->esq);
    liberar(tree->dir);
    free(tree);
}

void menu(void)
{
    printf("1 - inserir\n");
    printf("2 - listar\n");
    printf("-1 - sair\n");
}

int main(void)
{
    node *tree = NULL;
    int raiz = 0;
    int opcao;
    int valor;

    while (1)
    {
        menu();
        printf("Digite a opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            printf("entrada invalida\n");
            break;
        }

        if (opcao == -1)
        {
            break;
        }

        if (opcao == 1)
        {
            printf("Digite o valor que voce quer adicionar: ");

            if (scanf("%d", &valor) != 1)
            {
                printf("entrada invalida\n");
                break;
            }

            inserir(&tree, valor, &raiz);
        }
        else if (opcao == 2)
        {
            if (tree == NULL)
            {
                printf("arvore vazia\n");
            }
            else
            {
                printf("raiz: %d\n", raiz);
                listar(tree);
            }
        }
        else
        {
            printf("opcao invalida\n");
        }

        printf("\n");
    }

    liberar(tree);
    return 0;
}
