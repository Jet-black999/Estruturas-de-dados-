//lista circular de ips  


typedef struct no 
{
    char ip[16];
    
    struct node *ant;

    struct node *prox;

} node;


//inserir 
void inserir(node **circle,node *inicio ,node* fim,char ip[]) 
{
    if(circle == NULL) 
    {
        printf("Memoria não alocada\n");
        return;
    }

    node *novo = (node *)malloc(sizeof(node));

    if(circle)
}


//buscar


//listar toda a lista 

//circule a lista ??? 

int main () 
{
int op = 0;
node *circle = NULL;
node *inicio = NULL;
node *fim = NULL;

while(1) 
{
menu();
op=verificar_opcao();

switch(op) 
{
    case 1:
    //inserir ip
    break;

    case 2:
    //buscar ip
    break;

    case 3:
    //listar ips
    break;

    case 0:
    //sair do programa
    return 0;


}


}