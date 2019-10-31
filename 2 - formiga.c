#include <stdio.h>
#include <stdlib.h>

typedef struct g{
    int **states;
    int *adjacencias;

}grafo;

grafo* criaGrafo();
void processamento(grafo** g, int* vet, int pos);
void printState(int* vet);
int buscaEstado(grafo* g, int* vet);
void buscaSolucao(grafo* g, int* config);

int main(){
    grafo* g = criaGrafo();
    int v[] = {1,-1};
    int pos = 0;
    for(int i=0;i<2;i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                for (int c = 0; c < 2; c++){
                    g->states[pos][0] = v[i]; 
                    g->states[pos][1] = v[j];
                    g->states[pos][2] = v[k];
                    g->states[pos][3] = v[c];
                    pos++;
                }
    for (int j = 0; j < 2; j++)
        for (int k = 0; k < 2; k++)
            for (int c = 0; c < 2; c++){
                g->states[pos][0] = v[j]; 
                g->states[pos][1] = v[k];
                g->states[pos][2] = v[c];
                pos++;
            }
    for (int k = 0; k < 2; k++)
        for (int c = 0; c < 2; c++){
            g->states[pos][0] = v[k]; 
            g->states[pos][1] = v[c];
            pos++;
        }
    for (int c = 0; c < 2; c++){
        g->states[pos][0] = v[c]; 
        pos++;
    }

    int vet[] = {1,1,1,1};
    pos = 0;
    processamento(&g, vet, pos);

    for(int i=0;i<31;i++){
        printState(g->states[i]); printf(" -> "); printState(g->states[g->adjacencias[i]]); printf("\n");
    }

    printf("Digite o estado inicial do Tubo (4 formigas) >> ");scanf("%d %d %d %d",vet,vet+1,vet+2,vet+3);

    buscaSolucao(g, vet);
 
    return 0;
}

void buscaSolucao(grafo* g, int* config){
    printState(config);printf("\n");
    int estado = buscaEstado(g, config);
    if(config[0]!=0)
        buscaSolucao(g, g->states[g->adjacencias[estado]]);
}

void printState(int* vet){
    printf("{");
    for(int i=0;i<4;i++)
        printf("%d ",vet[i]);
    printf("}");
}
void processamento(grafo** g , int* vet, int pos){
    int tam = 0;
    while(tam !=4 && vet[tam]!=0)
        tam++;
    if(tam == 0)
        return;
    int ini = 0;
    int fim = tam-1;

    int vetAux[4];
    for(int i=0;i<4;i++){
        vetAux[i] = vet[i];
    }
    int flagrealoc = 0;
    while(vet[ini]!=1 && ini!=fim)
        ini++;
    while(vet[fim]!=-1 && ini!=fim)
        fim--;
    if(ini > 0 || tam == 1){
        vetAux[0] = 0;
        flagrealoc = 1;
    }
    if(vetAux[tam-1]==1)
        vetAux[tam-1] = 0;
    int flag = 1;

    if(ini!=fim){ //Existe inversão
        if(ini+1 == fim){
            vetAux[ini]*=-1;
            vetAux[fim]*=-1;
        }else{ // ini == ini fim == fim
            if(vetAux[ini]!=vetAux[ini+1]){
                vetAux[ini]*=-1;
                vetAux[ini+1]*=-1;
                flag = 0;
            }
            if((fim-ini)%2 == 1 || flag == 1) // não faz os dois em casos ímpares
                if(vetAux[fim]!=vetAux[fim-1]){
                    vetAux[fim]*=-1;
                    vetAux[fim-1]*=-1;
                    flag = 0;
                }
            if(flag){ // não houve inversão anterior
                vetAux[ini+1]*=-1;
                vetAux[fim-1]*=-1;
            }
        }
    }
    //Caso haja inversão ou não
    //printState(vetAux);
    //printf("%d",buscaEstado(g,vetAux));
    if (flagrealoc){
        for(int i=1;i<4;i++){
            vetAux[i-1] = vetAux[i];
        } 
        vetAux[3]=0;
    }
    (*g)->adjacencias[pos] = buscaEstado(*g,vetAux);
    processamento(g, (*g)->states[pos+1], pos+1);
}

int buscaEstado(grafo* g, int* vet){
    int flag;
    for(int i = 0;i<31;i++){
        flag = 1;
        for(int j=0;j<4;j++){
            if(g->states[i][j] != vet[j]){
                flag = 0;
            }
        }
        if(flag)
            return i;
    }
}

grafo* criaGrafo(){
    grafo* g  = malloc(sizeof(grafo));
    g->states = (int**)calloc(sizeof(int*),31);
    for(int i=0;i<31;i++)
        g->states[i] = (int*)calloc(sizeof(int),4);
    
    g->adjacencias = (int*)calloc(sizeof(int),31);


}