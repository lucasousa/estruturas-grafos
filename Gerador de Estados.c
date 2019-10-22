#include<stdio.h>
#define True 1
#define False 0

typedef struct l{
    int info;
    struct l* prox;
}lista;


void printList(lista* l);
void addList(lista **l, int state[]);
lista* searchList(lista *l, int state[]);
void removeList(lista **l, int state[]);
void pop(lista **l);
int len(lista* l);


int main(){
    int startstate[4] = {1,1,1,1};



}

void printState(int state[], int size){
    for(int i=0;i<size;i++)
        printf("%d ", state[i]);
    printf("\n");
}

void move(int state[] ,int disk ,int tower){
    state[disk] = tower;
}

int canMove(int state[], int disk, int tower){
    for(int i=0;i<disk;i++)
        if(state[disk] == state[i]) //Nenhum disco acima 
            return False;
    for (int i = 0; i <= disk; i++) //se existe um disco menor naquela posição ou ele está naquela posição
        if(state[i]==tower)
            return False;
    return True;
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
void removeList(lista **l, int state[]){
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
lista* searchList(lista *l, int state[]){
    lista* aux = l;
    for(;aux!=NULL && aux->info!=info;aux = aux->prox);
    return aux;
}
void addList(lista **l, int state){
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

