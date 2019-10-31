#include <stdio.h>
#include <stdlib.h>

typedef struct g{
    int **states;
    int *adjacencias;

}grafo;

grafo* criaGrafo();
int idPos(int* vet);


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

    for(int i=0;i<31;i++)
        printf("{%d, %d, %d, %d}\n", g->states[i][0],g->states[i][1],g->states[i][2],g->states[i][3]);
    
    return 0;
}
int idPos(grafo* g ,int* vet){
    int tam = 0;
    while(tam !=4 && vet[tam]!=0)
        tam++;
    
    int ini = 0;
    int fim = tam-1;

    while(vet[ini]!=1 && ini!=fim)
        ini++;
    while(vet[fim]!=1 && ini!=fim)
        fim--;

    

}

grafo* criaGrafo(){
    grafo* g  = malloc(sizeof(grafo));
    g->states = (int**)calloc(sizeof(int*),31);
    for(int i=0;i<31;i++)
        g->states[i] = (int*)calloc(sizeof(int),4);
    
    g->adjacencias = (int*)calloc(sizeof(int),31);


}