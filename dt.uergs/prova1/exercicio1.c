#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------FILA DE IMPRESSÃO--------------------------------------------------------------------*/

#define total_estruturas 4

typedef struct Fila
{ // 2-diretor 1-funcionarios
    int cargo;

    // 2-RH 1-INformatica 0-Outros
    int departamento;

    // 1,5 ou 10
    int doc;

    int prio;

    // tv não precise desse ponteiro
    struct Fila *proximo;
} fila;

/*  estrutras 0-fila de impressao/1-pilha de descartados/2-pilha de impressos
lembrando que para funcionar tenho que ser um array de ponteiros */

    fila *estruturas[total_estruturas] = {NULL};

// calculo de prioridade de impressão
int Calcprioridade(int cargo, int departamento, int doc)
{
    int prioridade = (cargo * 3) + (departamento * 2) + doc;
    return prioridade;
}
//print do menu 
void menu()
{
        printf("1 - Inserir documento\n");
        printf("2 - Imprimir documento\n");
        printf("3 - Descartar documento\n");
        printf("0 - Sair\n");
}

// inserir na lista conforme a prioridade

void inserir(fila *estruturas[], fila *nova, int cargo, int departamento, int doc, int prio)

{
    if (nova == "NULL")
    {
        printf("memoria não alocada\n");
    }

    nova->cargo = cargo;
    nova->departamento = departamento;
    nova->doc = doc;
    nova->prio = Calcprioridade(cargo, departamento, doc);
    nova->proximo = NULL;

    if (estruturas[0] == NULL)
    {
        estruturas[0] = nova;
    }
    else
    {
        fila *atual = estruturas[0];
        fila *anterior = NULL;

        while (atual != NULL && atual->prio >= nova->prio)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior == NULL)
        {
            nova->proximo = estruturas[0];
            estruturas[0] = nova;
        }
        else
        {
            anterior->proximo = nova;
            nova->proximo = atual;
        }
    }
}

// impressão do documento, ou seja, remoção da fila de impressão e inserção na pilha de impressos

// remover da fila de impressão

fila *remover(fila *estruturas[])
{
    if (estruturas[0] == NULL)
    {
        printf("Fila de impressão vazia.\n");
        return NULL;
    }

    fila *remover = estruturas[0];
    estruturas[0] = estruturas[0]->proximo;
    remover->proximo = NULL; // Desconecta o nó removido da lista

    return remover;
}

void imprimir_doc(fila *estruturas[])
{
    // remover da fila de impressão
    fila *doc_impresso = remover(estruturas);
    if (doc_impresso != NULL)
    {
        // inserir na pilha de impressos
        doc_impresso->proximo = estruturas[2]; // Aponta para o topo atual da pilha de impressos
        estruturas[2] = doc_impresso;          // Atualiza o topo da pilha de impressos
        printf("Documento impresso: %d\n", doc_impresso->doc);
    }
    else
    {
        printf("Nenhum documento para imprimir.\n");
    }

    // inserir na pilha de impressos
}

// retirar item da lista de impressão e inserir na pilha de descartados

retirar_doc(fila *estruturas[])
{
    // remover da fila de impressão
    fila *doc_descartado = remover(estruturas);
    if (doc_descartado != NULL)
    {
        // inserir na pilha de descartados
        doc_descartado->proximo = estruturas[1]; // Aponta para o topo atual da pilha de descartados
        estruturas[1] = doc_descartado;          // Atualiza o topo da pilha de descartados
        printf("Documento descartado: %d\n", doc_descartado->doc);
    }
    else
    {
        printf("Nenhum documento para descartar.\n");
    }

    // inserir na pilha de descartados
}
int seletor(op) 
{
while(op<=0 || op>3)
    {
        printf("Digite a opcao desejada:\n");
        printf("1 - Inserir documento\n");
        printf("2 - Imprimir documento\n");
        printf("3 - Descartar documento\n");
        printf("0 - Sair\n");
        scanf("%d", &op);
    }
    return op;

}



int main()
{

    fila *lista = NULL;

    int op, cargo, departamento, doc;

    while (1)
    {
        void menu();
        op=seletor(op);
        switch (op)
        {
        case 1:
        //inserir na fila de impressão
            printf("Digite o cargo (0 - Funcionario, 1 - Diretor): ");
            scanf("%d", &cargo);
            printf("Digite o departamento (0 - Outros, 1 - Informatica, 2 - RH): ");
            scanf("%d", &departamento);
            printf("Digite o tipo de documento (1, 5 ou 10): ");
            scanf("%d", &doc);

            fila *nova = (fila *)malloc(sizeof(fila));
            inserir(estruturas, nova, cargo, departamento, doc, Calcprioridade(cargo, departamento, doc));
        break;
        
        case 2:
        //imprimir documento
        imprimir_doc(estruturas);
        break;
        
        case 3:
        //descartar documento
        retirar_doc(estruturas);
        break;

        case 0:
        //sair  
        printf("Saindo do programa...\n");
        exit(0);
    }
    }

    return 0;
}