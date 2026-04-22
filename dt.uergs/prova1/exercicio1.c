#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------FILA DE IMPRESSÃO--------------------------------------------------------------------*/

#define total_estruturas 4

typedef struct Fila
{ 
    //nome do documento,util para realir busca
    char nome[50];

    // 2-diretor 1-funcionarios
    int cargo;

    // 2-RH 1-INformatica 0-Outros
    int departamento;

    // 1,5 ou 10
    int doc;
    
    //prioridade calculada a partir do cargo, departamento e tipo de documento
    int prio;

    // tv não precise desse ponteiro
    struct Fila *proximo;
    // Armazena o "tempo" de chegada do documento
     int time; 
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
        printf("\n-------------------------------------------M E N U --------------------------------:\n");
        printf("\n1 - Inserir documento\n");
        printf("\n2 - Imprimir documento\n");
        printf("\n3 - Descartar documento\n"); 
        printf("\n4- Listar documentos na fila de impressão\n");
        printf("\n5- Listar documentos na pilha de impressos\n");
        printf("\n6- Listar documentos na pilha de descartados\n");
        printf("\n7-buscar documento pelo nome na fila de impressão\n");
        printf("\n0 - Sair\n");
}

// inserir na lista conforme a prioridade

void inserir(fila *estruturas[], fila *nova, int cargo, int departamento, int doc, int prio, int tempo, char nome[])

{
    if (nova == NULL)
    {
        printf("memoria não alocada\n");
        return;
    }

    nova->cargo = cargo;
    nova->departamento = departamento;
    nova->doc = doc;
    nova->prio = prio;
    nova->proximo = NULL;

    // Armazena o "tempo" de chegada do documento
    nova->time = tempo;
    //pega o nime do documento inserido pelo usuario

    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0';
    

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
        printf("--------------------------------------------\n");
        printf("Documento impresso: %s\n", doc_impresso->nome);
        printf("--------------------------------------------\n");
    }
    else
    {
        printf("Nenhum documento para imprimir.\n");
    }

    // inserir na pilha de impressos
}

// retirar item da lista de impressão e inserir na pilha de descartados

void retirar_doc(fila *estruturas[])
{
    // remover da fila de impressão
    fila *doc_descartado = remover(estruturas);
    if (doc_descartado != NULL)
    {
        // inserir na pilha de descartados
        doc_descartado->proximo = estruturas[1]; // Aponta para o topo atual da pilha de descartados
        estruturas[1] = doc_descartado;          // Atualiza o topo da pilha de descartados
        printf("Documento descartado: %s\n", doc_descartado->nome);
    }
    else
    {
        printf("Nenhum documento para descartar.\n");
    }

    // inserir na pilha de descartados
}
int seletor(void)  
{
    int op = -1;

    do
    {
        menu();
        printf("Digite a opcao desejada: ");
        scanf("%d", &op);
    } while(op < 0 || op > 7);

    return op;
}
//listar documentos na fila de impressão 
void lista_fila (fila *estruturas[])
{
    if (estruturas[0] == NULL)
    {
        printf("Fila de impressão vazia.\n");
        return;
    }

    printf("Documentos na fila de impressão:\n");
    fila *atual = estruturas[0];
    while (atual != NULL)
    {
        printf("Nome: %s, Cargo: %d, Departamento: %d, Documento: %d, Prioridade: %d\n", atual->nome, atual->cargo, atual->departamento, atual->doc, atual->prio);
        atual = atual->proximo;
    }
}

void pilha_imprimidos(fila *estruturas[])
{
    if (estruturas[2] == NULL)
    {
        printf("Pilha de impressos vazia.\n");
        return;
    }

    printf("Documentos na pilha de impressos:\n");
    fila *atual = estruturas[2];
    while (atual != NULL)
    {
        printf("Nome: %s, Cargo: %d, Departamento: %d, Documento: %d, Prioridade: %d\n", atual->nome, atual->cargo, atual->departamento, atual->doc, atual->prio);
        atual = atual->proximo;
    }
}

void pilha_descartados(fila *estruturas[])
{
    if (estruturas[1] == NULL)
    {
        printf("Pilha de descartados vazia.\n");
        return;
    }

    printf("Documentos na pilha de descartados:\n");
    fila *atual = estruturas[1];
    while (atual != NULL)
    {
        printf("Nome: %s, Cargo: %d, Departamento: %d, Documento: %d, Prioridade: %d\n", atual->nome, atual->cargo, atual->departamento, atual->doc, atual->prio);
        atual = atual->proximo;
    }
}

void buscar_documento(fila *estruturas[])
{
    char nome[50];
    int encontrado = 0;

    if (estruturas[0] == NULL)
    {
        printf("Fila de impressão vazia.\n");
        return;
    }

    printf("Digite o nome do documento que deseja buscar: ");
    scanf(" %49[^\n]", nome);

    fila *atual = estruturas[0];
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            printf("Nome: %s, Cargo: %d, Departamento: %d, Documento: %d, Prioridade: %d\n", atual->nome, atual->cargo, atual->departamento, atual->doc, atual->prio);
            encontrado = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Documento não encontrado na fila de impressão.\n");
    }
}

//validações para os campos de cargo, departamento e tipo de documento
int validar_cargo() 
{
    int cargo;
    do
    {
        printf("Digite o cargo (0 - Funcionario, 1 - Diretor): ");
        scanf("%d", &cargo);
        if (cargo < 0 || cargo > 1)
        {
            printf("Cargo inválido. Digite novamente.\n");
        }
    } while (cargo < 0 || cargo > 1);
    return cargo;
}

int validar_departamento()
{
    int departamento;
    do
    {
        printf("Digite o departamento (0 - Outros, 1 - Informatica, 2 - RH): ");
        scanf("%d", &departamento);
        if (departamento < 0 || departamento > 2)
        {
            printf("Departamento inválido. Digite novamente.\n");
        }
    } while (departamento < 0 || departamento > 2);
    return departamento;
}

int validar_doc()
{
    int doc;
    do
    {
        printf("Digite o tipo de documento (1, 5 ou 10): ");
        scanf("%d", &doc);
        if (doc != 1 && doc != 5 && doc != 10)
        {
            printf("Tipo de documento inválido. Digite novamente.\n");
        }
    } while (doc != 1 && doc != 5 && doc != 10);
    return doc;
}

int main()
{
    int op, cargo, departamento, doc;
    char nome[50];
    /* toda vez que uma impressão é adciona, o tempo
     é incrementado, e quando chegar a 10, 
    ou seja todas as impressoes que receberem estiverem a 10 contagens vao ter sua prioridade alternada receberam 5+
    */
    int tempo= 1;

    int contador = 0; //contador os valor de 10 em 10
    
    while (1)
    {
     //verificar se o tempo
      //chegou a 10, ou seja, se todas as impressoes que receberam estiverem a 5 contagens vao ter sua prioridade alternada receberam 5+
        if (contador==10) 
        {
        printf("---------------------------------------------\n");
        printf("Atualizando prioridades dos documentos na fila de impressão...\n");
            fila *atual = estruturas[0];
            while (atual != NULL)
            {
                if (tempo
                     - atual->time >= 10)
                {
                    atual->prio += 5; // Aumenta 5 naqueles que tiveram a foram adcionados primeiro 
                    atual->time = tempo
                    ; // Reinicia o tempo de chegada para o documento atualizado
                }
                atual = atual->proximo;
            }
            contador=0; // Reinicia o tempo após atualizar as prioridades
        }   

        op = seletor();
        switch (op)
        {
        case 1:
        //inserir na fila de impressão
            printf("Digite o nome do documento: ");
            scanf(" %49[^\n]", nome);
            //irei fazer a validações de todos os campos, pois estava dando erro 
            cargo=validar_cargo();
            
            departamento=validar_departamento();

            doc=validar_doc();

            //alocando a memoria para a nova estrutura e inserindo na fila de impressão
            fila *nova = (fila *)malloc(sizeof(fila));
            inserir(estruturas, nova, cargo, departamento, doc, Calcprioridade(cargo, departamento, doc), tempo, nome);
            
            tempo++; // tempo de impressão incrementado  a cada documento inserido
            contador++; // contador incrementado a cada documento inserido
            
        
        break;
        
        case 2:
        //imprimir documento
        imprimir_doc(estruturas);
        break;
        
        case 3:
        //descartar documento
        retirar_doc(estruturas);
        break;
        
        case 4:
        //listar documentos na fila de impressão 
        printf("---------------------------------------------\n");
        printf("Listagem dos documentos na fila de impressão:\n");
        lista_fila(estruturas);
        break;

        case 5:
        //listar documentos na pilha de impressos
        printf("---------------------------------------------\n");
        printf("Listagem dos documentos impressos:\n");
        pilha_imprimidos(estruturas);
        break;

        case 6:
        //listar documentos na pilha de descartados
        printf("---------------------------------------------\n");
        printf("Listagem dos documentos descartados:\n");
        pilha_descartados(estruturas);
        break;

        case 7:
        //buscar documento na fila de impressão
        printf("---------------------------------------------\n");
        printf("Busca por nome de documento na fila de impressão:\n");
        buscar_documento(estruturas);
        break;

        case 0:
        //sair  
        printf("Saindo do programa...\n");
        exit(0);
    }
    }

    return 0;
}
