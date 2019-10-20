#include<stdio.h>
#include<stdlib.h>

typedef struct g{
    float **matriz;
    int nVertices;
}grafo;

typedef struct l{
    int info;
    struct l* prox;
}lista;

int flag = 0;
int maiorCidades = 0;
lista* quantidade_de_cidades = NULL;

void printMatrix(grafo* g);
grafo* criaGrafo(int nVertices);
grafo* inserirAresta(grafo *g, int o , int d, float p);
void printList(lista* l);
void addList(lista **l, int info);
lista* searchList(lista *l, int info);
void removeList(lista **l, int info);
void pop(lista **l);
void widthSearch(grafo *g, lista* visitados, int partida, float dinheiro);
int canGo(grafo *g, lista* visitados ,int cidade ,float dinheiro);
int len(lista* l);
void defineSequencia(grafo* g, int sequencia[], int partida);
int menordovet(int vet[], int tam);

int main(){  
    
    
    
    grafo *g;
    int ncidades;
    int o, d;
    float menorcusto;
    float c;
    lista* l = NULL;
    int cityCount = 0;

    printf("Digite a quantidade de cidades >> "); scanf("%d",&ncidades);
    g = criaGrafo(ncidades);
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
    widthSearch(g, l, partida, dinheiro);
    printList(quantidade_de_cidades);


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

int canGo(grafo *g, lista* visitados, int cidade ,float dinheiro){
    for(int i = 0; i < g->nVertices;i++){
        if(g->matriz[cidade-1][i] != 0)
            if(!searchList(visitados, i+1))
                if(dinheiro >= g->matriz[cidade-1][i])
                    return 1;
    }
    return 0;

}

int menordovet(int vet[], int tam){
    int menor=0, menorindice = 0, indice = 0;
    while(menor==0 && indice<tam){
        menor = vet[indice];
        menorindice++;
        indice++;
    }
    menorindice--;
    if(indice == tam)
        return 0;
    for(int i = menorindice+1;i<tam;i++){
        if(vet[i]!=0 && vet[i] < menor){
            menor = vet[i];
            menorindice = i;
        }
    }
    vet[menorindice] = 0;
    return menorindice+1;
}

void defineSequencia(grafo* g, int sequencia[], int partida){
    int  menorAnt = 0.001, menor = g->matriz[partida-1][0];
    int aux[g->nVertices];
    for(int i=0;i<g->nVertices;i++)
        aux[i] = g->matriz[partida-1][i];
    int proximapos = 1;
    int pos = 0;
    while(proximapos!=0){
        proximapos = menordovet(aux, g->nVertices);
        sequencia[pos] = proximapos;
        pos++;
    }
}



void widthSearch(grafo *g,lista* visitados, int partida, float dinheiro){
    int *sequencia = calloc(sizeof(int),g->nVertices);
    addList(&visitados, partida);
    if(!canGo(g, visitados, partida, dinheiro))
        addList(&quantidade_de_cidades, len(visitados)-1);
    defineSequencia(g, sequencia, partida);
    
    printf("sequencia : ");
    for( int i=0;sequencia[i]!=0;i++)
        printf("%d ", sequencia[i]);
    printf("\n");
        
    for(int i = 0; sequencia[i]!=0 ; i++){
        if(!searchList(visitados, sequencia[i]))
            if(dinheiro>=g->matriz[partida-1][sequencia[i]-1]){
                printf("eu já visitei: ");printList(visitados);
                printf("Estou indo para o nó: %d, tenho %.2f reais",sequencia[i],dinheiro); setbuf(stdin,NULL); getchar();
                widthSearch(g, visitados, sequencia[i], dinheiro-g->matriz[partida-1][sequencia[i]-1]);
            }
    }
    printf("Estou removendo: %d\n", partida);
    removeList(&visitados, partida);
    printf("eu já visitei: ");printList(visitados);
    printf("Voltei do nó: %d, tenho %.2f reais",partida, dinheiro); setbuf(stdin,NULL); getchar();
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



grafo* inserirAresta(grafo *g, int o , int d, float p){
    g->matriz[o-1][d-1] = p;
    g->matriz[d-1][o-1] = p;
    return g;
}

void printMatrix(grafo* g){
    for(int i=0;i<g->nVertices;i++){
        for(int j=0;j<g->nVertices;j++)
            printf("%.2f ",g->matriz[i][j]);
        printf("\n");
    }
}

grafo* criaGrafo(int nVertices){
    grafo *g;
    g = (grafo*)malloc(sizeof(grafo));
    g->nVertices = nVertices;
    g->matriz = (float**)calloc(sizeof(float*),nVertices);
    for(int i=0;i<nVertices;i++)
        g->matriz[i] = (float*)calloc(sizeof(float),nVertices);
    return g;
}