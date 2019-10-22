#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TAM 4
#define True 1
#define False 0


typedef struct g{
    int **adjacencias;
    int **states;
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
void deepSearch(grafo *g,int **visitados, int *estadoOrigem, int partida);
int canGo(grafo *g, int **visitados ,int origem);
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
    g = criaGrafo(81);
    int **visitados = calloc(sizeof(int*),81);
    for(int i=0;i<81;i++)
        visitados[i] = (int*)calloc(sizeof(int),4);

    int cont = 0;


    for (int i=1;i<=3;i++)      //Geração dos conjuntos
        for(int j=1;j<=3;j++)
            for(int k=1;k<=3;k++)
                for(int l=1;l<=3;l++){
                    g->states[cont][0]=i;
                    g->states[cont][1]=j;
                    g->states[cont][2]=k;
                    g->states[cont][3]=l;
                    cont++;
                }

    for(int i=0;i<81;i++){
        printState(g->states[i]); printf(" %d \n",i);
    }


    for(int i=0;i<81;i++){
        for(int j=i+1;j<81;j++){
            if(ehAdjacente(g->states[i],g->states[j])){
                g = inserirAresta(g,i,j);
            }
        }
    }



    for(int i=0;i<81;i++){
        printf("linha %d: ", i);
        for(int j=0;j<3;j++){
            printf("%d ", g->adjacencias[i][j]);
        }
        printf("\n");
    } 

    int initialState[] = {1,1,1,1};
    //getchar();
    printf("Vou fazer a busca agora\n");
    deepSearch(g, visitados, initialState, 0);
    printf("Terminei a Busca\n");

    printf("O maior caminho é: %d\n",maiorcaminho);
    printf("O maior caminho é: %d\n",menorcaminho);


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

int existenaLista(int **lista, int *vet){
    for(int i=0;lista[i][0] != 0;i++){
        if(lista[i][0] == vet[0] && lista[i][1] == vet[1] && lista[i][2] == vet[2] && lista[i][3] == vet[3])
            return True;
    }
    return False;
}

void deepSearch(grafo *g,int **visitados, int *estadoOrigem, int partida){
    int pos = 0;
    while(visitados[pos][0]!=0){
        //printf("{%d, %d, %d, %d}\n",visitados[pos][0],visitados[pos][1],visitados[pos][2],visitados[pos][3]);
        pos++;
    }
    visitados[pos][0] = estadoOrigem[0];
    visitados[pos][1] = estadoOrigem[1];
    visitados[pos][2] = estadoOrigem[2];
    visitados[pos][3] = estadoOrigem[3];
    if(vetCompare(estadoOrigem, destino)){
        int tamanho = pos;
        if(tamanho > maiorcaminho)
            maiorcaminho = tamanho;
        if(tamanho < menorcaminho)
            menorcaminho = tamanho;
    }
    for(int i = 0; i < 3; i++){
        if(g->adjacencias[partida][i]!=0){
            if(!existenaLista(visitados, g->states[g->adjacencias[partida][i]])){
                //printf("estou na linha: %d \n",partida);
                //printf("Indo para a linha: %d \n",g->adjacencias[partida][i]);
                //getchar();
                deepSearch(g, visitados, g->states[g->adjacencias[partida][i]] ,g->adjacencias[partida][i]);
            }
        }
    }
    visitados[pos][0] = 0;
    visitados[pos][1] = 0;
    visitados[pos][2] = 0;
    visitados[pos][3] = 0;
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
    int pos = 0;
    while(g->adjacencias[o][pos]!=0)
        pos++;
    g->adjacencias[o][pos] = d;
    pos = 0;
    while(g->adjacencias[d][pos]!=0)
        pos++;
    g->adjacencias[d][pos] = o;
    return g;
}

/* void printMatrix(grafo* g){
    for(int i=0;i<g->nVertices;i++){
        for(int j=0;j<g->nVertices;j++)
            printf("%d ",g->matriz[i][j]);
        printf("\n");
    }
} */

grafo* criaGrafo(int nVertices){
    grafo *g;
    g = (grafo*)malloc(sizeof(grafo));
    g->nVertices = nVertices;
    g->states = (int**)calloc(sizeof(int*),nVertices);
    for(int i=0;i<nVertices;i++)
        g->states[i] = (int*)calloc(sizeof(int),4);
    
    g->adjacencias = (int**)calloc(sizeof(int*), nVertices);
    for(int i=0; i<nVertices;i++)
        g->adjacencias[i] = (int*)calloc(sizeof(int), 3);
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