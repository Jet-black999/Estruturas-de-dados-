#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *prox;
} Node;



void inserir(Node **lista, int valor)
{
    // Verificar se a lista foi inicializada e alocada
    if (lista == NULL)
    {
        printf("Lista não inicializada!\n");
        return;
    }
    else
    {
        // aloca memoria para o novo no
        Node *aux = (Node *)malloc(sizeof(Node));
        ;
        Node *novo = (Node *)malloc(sizeof(Node));
        if (novo == NULL)
        {
            printf("Erro: Falha na alocação de memória!\n");
            return;
        }
        novo->data = valor;
        novo->prox = *lista;

        if (*lista == NULL)
        {
            // lista foi alocada mais esta vazia
            *lista = novo;
        }
        else
        {
            // como ja tem aviao na lista
            Node *aux = *lista;

            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
}
    void listar(Node *lista)
    {
        while(lista != NULL)
        {
            printf("%d ", lista->data);
            lista = lista->prox;
        }
        printf("\n");
    }
void contar(Node* lista)
{
    int count = 0;
    while(lista != NULL)
    {
        count++;
        lista = lista->prox;
    }
    printf("Número de elementos na lista: %d\n", count);
}

void remover(Node **lista)
{
    Node *remover= NULL;

    // se a vila esta vazia
    if(*lista)
    {
        remover = *lista;
        *lista = remover->prox;
        free(remover);
    }
    else
    {
        printf("A fila esta vazia!\n");
    }
}

void menu()
{
    printf("1. Inserir elemento\n");
    printf("2. Listar elementos\n");
    printf("3. Contar número de elementos\n");
    printf("4. Remover o primeiro elemento\n");
    printf("0. Sair\n");
}

int main()
{
int op, valor;
Node *lista = NULL;
    do
    {
        
        menu();
        printf("Digite a opcao desejada: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir(&lista, valor);
            break;
        case 2:
            listar(lista);
            break;
        case 3:
            contar(lista);
            break;
        case 4:
            remover(&lista);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while(op!=0);
}
