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
    int *nivel;
}grafo;

typedef struct l{
    int info;
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
void printList(lista* l);
void addList(lista **l, int info);
lista* searchList(lista *l, int info);
void removeList(lista **l, int info);
void pop(lista **l);
void deepSearch(grafo *g, lista *visitados, int *estadoOrigem, int partida);
int len(lista* l);
void printState(int state[]);
int ehAdjacente(int v1[], int v2[]);
int temAdjacencia(int v1[], int v2[]);
int tem1Diferenca(int v1[], int v2[]);
void copyVector(int v1[], int v2[], int tam);
int vetCompare(int source[], int dest[]);
int canGo(grafo *g ,lista* visitados, int partida);
grafo* atribuiNivel(grafo *g, int nivel, lista *fp, lista *ff);

int main(){
    grafo *g;
    int ncidades;
    int o, d;
    float menorcusto;
    float c;
    lista* l = NULL;
    g = criaGrafo(81);
    lista *visitados = NULL;

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
        for(int j=i+1;j<81;j++){
            if(ehAdjacente(g->states[i],g->states[j])){
                g = inserirAresta(g,i,j);
            }
        }
    }

    lista *ff, *fp;
    ff=NULL;
    fp=NULL;
    addList(&fp, 0);
    g = atribuiNivel(g, 1, fp, ff);

     for(int i=0;i<40;i++){
        printState(g->states[i]); printf(" %2d ",i);
        printf("linha %2d: ", i);
        for(int j=0;j<3;j++){
            printf("%.2d ", g->adjacencias[i][j]);
        }
        printf("   ////    ");
        printf("\t");printState(g->states[i+40]); printf(" %2d ",i+40);
        printf("linha %2d: ", i+40);
        for(int j=0;j<3;j++){
            printf("%2d ", g->adjacencias[i+40][j]);
        }
        printf("\n");
    }
    printf("      \t");printState(g->states[80]);printf("\n"); 


    int is[4];
    printf("Digite o estado inicial que a torre está:\n");
    printf("exemplo: 1 2 2 1\n");
    printf("o menor disco está na torre 1, o segundo menor está na torre 2,\n o terceiro na torre 2 e o maior disco na torre 1\n");
    scanf("%d %d %d %d", is, is+1, is+2, is+3);
    int isNumber = 3*3*3*(is[0]-1)+3*3*(is[1]-1)+3*(is[2]-1)+is[3]-1;
    printf("Isnumber %d \n", isNumber);
    deepSearch(g, visitados, is, isNumber);


    printf("O maior caminho é: %d\n",maiorcaminho);
    printf("O menor caminho é: %d\n",menorcaminho);


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

grafo* atribuiNivel(grafo *g, int nivel, lista *fp, lista *ff){
    if(!fp)
        return g;
    lista* aux = fp;
    while(aux){
        g->nivel[aux->info] = nivel;
        aux = aux->prox;
    }
    while(fp){
        for(int i=0; i<3; i++){
            if(g->nivel[g->adjacencias[fp->info][i]] == 0)
                addList(&ff, g->adjacencias[fp->info][i] );
        }
        fp=fp->prox;
    }
    lista* novaFF = NULL;
    return atribuiNivel(g, nivel+1, ff, novaFF);
    
} 

int canGo(grafo *g ,lista* visitados, int partida){
    if(partida == 80)
        return False;
    for(int i=0;i<3;i++)
        if(!searchList(visitados, g->adjacencias[partida][i]))
            return True;
    return False;

}

void deepSearch(grafo *g,lista *visitados, int *estadoOrigem, int partida){
    addList(&visitados, partida);
    if(!canGo(g, visitados, partida)){
        int tamanho = len(visitados)-1;
        if(tamanho > maiorcaminho)
            maiorcaminho = tamanho;
        if(tamanho < menorcaminho)
            menorcaminho = tamanho;
    }else
        for(int i = 2; i >= 0; i--)
            if(!searchList(visitados, g->adjacencias[partida][i]))
                if(g->nivel[g->adjacencias[partida][i]]>=g->nivel[partida])
                    deepSearch(g, visitados, g->states[g->adjacencias[partida][i]] ,g->adjacencias[partida][i]);
    removeList(&visitados, partida);
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
    
    g->nivel = (int*)calloc(sizeof(int), nVertices);

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

void removeList(lista **l, int info){
    if(*l == NULL)
        return;
    

    if((*l)->info == info || (*l)->prox == NULL){
        *l = (*l)->prox;
        return;
    }

    if((*l)->prox->info == info){
        (*l)->prox = (*l)->prox->prox;
        return;
    } 
    removeList(&((*l)->prox), info);
}

lista* searchList(lista *l, int info){
    lista* aux = l;
    for(;aux!=NULL && aux->info!=info;aux = aux->prox);
    return aux;
}

void addList(lista **l, int info){
    if(*l == NULL){
        *l = (lista*)malloc(sizeof(lista));
        (*l)->info = info;
        (*l)->prox = NULL;
        return;
    }
    addList(&((*l)->prox),info);
}

void printList(lista* l){
    for(lista* aux = l;aux!=NULL;aux = aux->prox)
        printf("%d ", aux->info);
    printf("\n");
}