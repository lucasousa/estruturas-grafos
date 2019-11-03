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
float dinheirorestante = 0;
int caminhos = 0;
int caminhoatual = 0;
lista* quantidade_de_cidades = NULL;

void printMatrix(grafo* g);
grafo* criaGrafo(int nVertices);
grafo* inserirAresta(grafo *g, int o , int d, float p);
void printList(lista* l);
void addList(lista **l, int info);
lista* searchList(lista *l, int info);
void removeList(lista **l, int info);
void pop(lista **l);
void deepSearch(grafo *g, lista* visitados, int partida, float dinheiro);
int canGo(grafo *g, lista* visitados ,int cidade ,float dinheiro);
int len(lista* l);

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
    deepSearch(g, l, partida, dinheiro);
    printf("\n\nMáximo de Cidades que é possível percorrer no melhor caminho: %d\n",maiorCidades);
    printf("Dinheiro restante no melhor caminho: %.2f\n",dinheirorestante);
    printf("O mehor caminho foi o caminho de número: %d\n", caminhoatual);


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

void deepSearch(grafo *g,lista* visitados, int partida, float dinheiro){
    addList(&visitados, partida);
    if(!canGo(g, visitados, partida, dinheiro)){
        caminhos++;
        int cidades = len(visitados)-1;
        if(cidades > maiorCidades){
            maiorCidades = cidades;         // Guarda quantas cidades o melhor caminho possui, de acordo com os critérios requeridos
            dinheirorestante = dinheiro;    // Dinheiro restante do melhor caminho
            caminhoatual = caminhos;        // Guarda em qual caminho foi encontrado o melhor(primeiro, segundo ...)        
        }else if(maiorCidades == cidades  && dinheiro > dinheirorestante){ // mesma quantidade de cidades mas com mais dinheiro restante
            dinheirorestante = dinheiro;    
            caminhoatual = caminhos;
        }
        addList(&quantidade_de_cidades, len(visitados)-1);
    }
    for(int i = 0; i < g->nVertices; i++){
        if(!searchList(visitados, i+1))
            if(g->matriz[partida-1][i] != 0)
                if(dinheiro>=g->matriz[partida-1][i]){
                    //printf("eu já visitei: ");printList(visitados);
                    //printf("Estou indo para o nó: %d, tenho %.2f reais",i+1,dinheiro); setbuf(stdin,NULL); getchar();
                    deepSearch(g, visitados, i+1, dinheiro-g->matriz[partida-1][i]);
                }
    }
    //printf("Estou removendo: %d\n", partida);
    removeList(&visitados, partida);
    //printf("eu já visitei: ");printList(visitados);
    //printf("Voltei do nó: %d, tenho %.2f reais",partida, dinheiro); setbuf(stdin,NULL); getchar();
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