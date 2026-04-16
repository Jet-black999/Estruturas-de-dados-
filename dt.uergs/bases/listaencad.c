#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------LISTA ENCADEADA--------------------------------------------------------------------*/

// Correção 1: Definindo a struct corretamente
typedef struct No
{
    int valor;
    struct No *proximo;
} No;
/*-------------------------------inserções*/
// Inserção no início
void inserir_no_inicio(No **lista, int num)
{
    No *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        novo->proximo = *lista;
        *lista = novo;
    }
    else
    {
        printf("Erro ao alocar memoria!\n");
    }
}

// Inserção no fim
void inserir_no_fim(No **lista, int num)
{
    // Correção 2: sizeof em vez de sizeoff
    No *aux, *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        novo->proximo = NULL; // Correção 3: Faltava o ponto e vírgula

        // Se é o primeiro
        if (*lista == NULL)
        {
            *lista = novo;
        }
        else // Correção 4: Removido os parênteses do else()
        {
            aux = *lista;
            while (aux->proximo)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
    }
    else // Correção 5: Removido os parênteses do else()
    {
        printf("Erro ao alocar memoria\n");
    }
}

// Inserir no meio
void inserir_no_meio(No **lista, int num, int ant)
{
    No *aux, *novo = malloc(sizeof(No));
    if (novo)
    {
        novo->valor = num;
        // Confere se a lista está vazia
        if (*lista == NULL)
        {
            novo->proximo = NULL;
            *lista = novo;
        }
        else
        {
            aux = *lista;
            while (aux->valor != ant && aux->proximo)
            {
                aux = aux->proximo;
            }
            // Correção 6: Faltava ligar o nó anterior (aux) ao novo nó!
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
}

/*exclusões */
void remover_inicio(No **lista)
{
    if (*lista == NULL)
    {
        printf("A lista ja esta vazia\n");
        return;
    }
    No *remover = *lista;
    *lista = remover->proximo;

    free(remover);
    printf("Elemento do inicio removido!!\n");
}

void remover_no_meio(No **lista, int valor_busca) 
{
    if (*lista == NULL) 
    {
        printf("A lista esta vazia!\n");
        return;
    }

    No *aux = *lista;
    No *anterior = NULL;

    // Cenário especial: e se o valor que queremos remover for logo o primeiro?
    if (aux->valor == valor_busca) 
    {
        remover_inicio(lista); // Aproveitamos a função que já criamos!
        return;
    }

    // Percorre a lista buscando o valor
    while (aux != NULL && aux->valor != valor_busca) 
    {
        anterior = aux;
        aux = aux->proximo;
    }

    // Se o 'aux' chegou em NULL, significa que varremos a lista toda e não achamos o valor
    if (aux == NULL) 
    {
        printf("Valor %d não encontrado na lista!\n", valor_busca);
        return;
    }

    // Costura a lista: o anterior passa a apontar para o nó que vem DEPOIS do que será removido
    anterior->proximo = aux->proximo;
    
    free(aux); // Libera o nó do meio
    printf("Elemento %d removido com sucesso!\n", valor_busca);
}



void remover_no_fim(No **lista) 
{
    if (*lista == NULL) 
    {
        printf("A lista ja esta vazia!\n");
        return;
    }

    No *aux = *lista;
    No *anterior = NULL;

    // Cenário especial: a lista só tem 1 elemento
    if (aux->proximo == NULL) 
    {
        *lista = NULL; // A lista fica vazia
        free(aux);
        printf("Ultimo elemento removido!\n");
        return;
    }

    // Percorre até o final, sempre guardando quem é o nó anterior
    while (aux->proximo != NULL) 
    {
        anterior = aux;
        aux = aux->proximo;
    }

    anterior->proximo = NULL; // O penúltimo agora vira o último
    free(aux);                // Libera a memória do último
    printf("Ultimo elemento removido!\n");
}


// Imprimir
void imprimir(No *no)
{
    printf("\n\tLista: ");
    while (no)
    {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

// Correção 7: Menu organizado e com as opções certas
int menu()
{
    int opcao = -1;
    printf("==================================\n");
    printf("1 - Inserir no Inicio\n");
    printf("2 - Inserir no Fim\n");
    printf("3 - Inserir no Meio\n");
    printf("4 - Imprimir Lista\n");
    printf("5-Remover no inicio\n");
    printf("6-Remover no meio\n");
    printf("7-remover no final\n");


    printf("0 - Sair\n");
    printf("==================================\n");
    printf("Selecione a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

int main()
{
    int op = -1, anterior = 0, valor = 0;
    No *lista = NULL;

    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_inicio(&lista, valor);
            break;

        case 2:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_fim(&lista, valor);
            break;

        case 3:
            printf("Digite o novo valor e o valor de referencia (anterior): ");
            scanf("%d %d", &valor, &anterior);
            inserir_no_meio(&lista, valor, anterior);
            break;

        case 4:
            imprimir(lista);
            break;
        case 5:

            remover_inicio(&lista);
            break;

        case 6:
         printf("Digite o valor que voce quer buscar : ");
         scanf("%d", &valor);    
         remover_no_meio(&lista,valor);
            break;

        case 7:
            remover_no_fim(&lista);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}