#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TAM 4
#define True 1
#define False 0


typedef struct g{
    int **matriz;
    int ***states;
    int nVertices;
}grafo;

typedef struct l{
    int info[TAM];
    struct l* prox;
}lista;

int menorcaminho = 82;
int maiorcaminho = 0;
int destino[] = {3,3,3,3};
int flag = 0;
int maiorCidades = 0;
lista* quantidade_de_nos = NULL;

void printMatrix(grafo* g); // 
grafo* criaGrafo(int nVertices); //
grafo* inserirAresta(grafo *g, int o , int d);//
void printList(lista* l); // 
void addList(lista **l, int info[]); //
int searchList(lista *l, int info[]); // 
void removeList(lista **l, int info[]); //
void pop(lista **l); //
void deepSearch(grafo *g,lista* visitados, int **estadoOrigem, int partida);
int canGo(grafo *g, lista* visitados ,int origem);
int len(lista* l);
void printState(int state[]);
int ehAdjacente(int v1[], int v2[]);
int temAdjacencia(int v1[], int v2[]);
int tem1Diferenca(int v1[], int v2[]);
void copyVector(int v1[], int v2[], int tam);
int vetCompare(int source[], int dest[]);

int main(){
    grafo *g;
    int ncidades;
    int o, d;
    float menorcusto;
    float c;
    lista* l = NULL;
    int cityCount = 0;
    int estados[81][4];
    int cont = 0;
    for (int i=1;i<=3;i++)      //Geração dos conjuntos
        for(int j=1;j<=3;j++)
            for(int k=1;k<=3;k++)
                for(int l=1;l<=3;l++){
                    estados[cont][0]=i;
                    estados[cont][1]=j;
                    estados[cont][2]=k;
                    estados[cont][3]=l;
                    cont++;
                }

    g = criaGrafo(81);

    for(int i=0;i<81;i++){
        for(int j=i+1;j<81;j++){
            if(ehAdjacente(estados[i],estados[j])){
                g = inserirAresta(g,i+1,j+1);
                g->states[i][j] = estados[i];
                g->states[j][i] = estados[j];
            }
        }
    }

    /* for(int i=0;i<81;i++){
        for(int j=0;j<81;j++){
            if(g->matriz[i][j]){
                printState(g->states[i][j]); printf(" -> "); printState(g->states[j][i]);
                printf("\n");
            }
        }
    } */

    int estadoOriginal[] = {1,1,1,1};

    deepSearch(g, l, &estadoOriginal, 1);
    



    
    /* g = criaGrafo(ncidades);
    printf("Digite todas as arestas conforme o exemplo:\n 1 3 10.25\n Origem = 1, Destino = 3, Custo = 10.25\n"); 
    printf("Para finalizar digite um custo negativo\n");
    printf("OBS: as cidades vão de 1 a n, sendo n o primeiro número digitado.\n");
    
    scanf("%d %d %f",&o,&d,&c);
    menorcusto = c;
    
    while(c>0){
        g = inserirAresta(g,o,d,c);
        if(menorcusto>c)
            menorcusto = c;
        scanf("%d %d %f",&o,&d,&c);
    }

    int partida;
    float dinheiro;
    printf("Digite o ponto de partida (1 - %d) >> ",ncidades); scanf("%d",&partida);
    printf("Quanto você tem para gastar? >> "); scanf("%f", &dinheiro);
    flag = 1;
    deepSearch(g, l, partida, dinheiro);
    printList(quantidade_de_cidades); */


}

void copyVector(int *source, int *dest, int len){
    for(int i=0; i<len; i++)
        dest[i] = source[i];
}
void printState(int *state){
    printf("[");
    for(int i=0;i<TAM;i++)
        printf("%d ",state[i]);
    printf("]");
    
}
int len(lista* l){
    int cont = 1;
    if(l == NULL)
        return 0;
    while(l->prox!=NULL){
        l = l->prox;
        cont++;
    }
    return cont;
}

int vetCompare(int v1[], int v2[]){
    for( int i=0;i<TAM;i++){
        if(v1[i]!=v2[i])
            return False;
    }
    return True;
}

void deepSearch(grafo *g,lista* visitados, int **estadoOrigem, int partida){
    addList(&visitados, estadoOrigem);
    if(vetCompare(*estadoOrigem, destino)){
        int tamanho = len(visitados)-1;
        if(tamanho > maiorcaminho)
            maiorcaminho = tamanho;
        if(tamanho < menorcaminho)
            menorcaminho = tamanho;
    }
    for(int i = 0; i < g->nVertices; i++){
        if(g->matriz[partida][i]){
            if(!searchList(visitados, g->states[partida][i])){
                printf("estado[partida][i] = "); printState(g->states[partida][i]); printf("\n");
                printf("estado[i][partida] = "); printState(g->states[i][partida]); printf("\n");
                printf("eu já visitei: "); printList(visitados);
                //printf("Estou indo para o nó:"); setbuf(stdin,NULL); getchar();
                copyVector(g->states[i][partida], *estadoOrigem,4);
                deepSearch(g, visitados, estadoOrigem ,i);
            }
        }
    }
    printf("Estou removendo: %d\n", partida);
    pop(&visitados);
    printf("eu já visitei: ");printList(visitados);
    printf("Voltei do nó: %d",partida); setbuf(stdin,NULL); getchar();
}

void pop(lista **l){
    if(*l == NULL)
        return;
    
    if((*l)->prox == NULL){
        (*l) = NULL;
        return;
    }

    if((*l)->prox->prox == NULL){
        (*l)->prox = NULL;
        return;
    }

    pop(&((*l)->prox));
}

void removeList(lista **l, int info[]){
    if(*l == NULL)
        return;
    

    if(vetCompare((*l)->info, info) || (*l)->prox == NULL){
        *l = (*l)->prox;
        return;
    }

    if(vetCompare((*l)->prox->info, info)){
        (*l)->prox = (*l)->prox->prox;
        return;
    } 
    removeList(&((*l)->prox), info);
}

int searchList(lista *l, int info[]){
    if(l == NULL)
        return 0;
    if(vetCompare(l->info, info))
        return 1;
    return searchList(l->prox, info);
}

void addList(lista **l, int info[]){
    if(*l == NULL){
        *l = (lista*)malloc(sizeof(lista));
        copyVector(info,(*l)->info, 4);
        (*l)->prox = NULL;
        return;
    }
    addList(&((*l)->prox),info);
}

void printList(lista* l){
    for(lista* aux = l;aux!=NULL;aux = aux->prox)
        printState(aux->info);
    printf("\n");
}



grafo* inserirAresta(grafo *g, int o , int d){
    g->matriz[o-1][d-1] = 1;
    g->matriz[d-1][o-1] = 1;
    return g;
}

void printMatrix(grafo* g){
    for(int i=0;i<g->nVertices;i++){
        for(int j=0;j<g->nVertices;j++)
            printf("%d ",g->matriz[i][j]);
        printf("\n");
    }
}

grafo* criaGrafo(int nVertices){
    grafo *g;
    g = (grafo*)malloc(sizeof(grafo));
    g->nVertices = nVertices;
    g->matriz = (int**)calloc(sizeof(int*),nVertices);
    for(int i=0;i<nVertices;i++)
        g->matriz[i] = (int*)calloc(sizeof(int),nVertices);
    int tamStates = pow(3,TAM);
    g->states = (int***)calloc(sizeof(int**), tamStates);
    for(int i = 0;i<tamStates;i++){
        g->states[i] = (int**)calloc(sizeof(int*),tamStates);
    }
    return g;
}

int tem1Diferenca(int v1[], int v2[]){
    int cont = 0;
    for(int i=0;i<TAM;i++)
        if(v1[i]!=v2[i])
            cont++;
    if(cont == 1) return True;
    else return False;
}

int temAdjacencia(int v1[], int v2[]){
    int pos = 0;
    while(v1[pos] == v2[pos])
        pos++;
    for(int i=0;i<pos;i++)
        if(v1[i] == v1[pos] || v2[i] == v2[pos]) // Se existe um menor acima ou será colocado acima de um menor
            return False;
    return True;
}

int ehAdjacente(int v1[], int v2[]){
    if(tem1Diferenca(v1,v2))
        if(temAdjacencia(v1, v2))
            return True;
    return False;
}