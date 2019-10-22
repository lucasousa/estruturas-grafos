#include<stdio.h>
#define True 1
#define False 0
#define TAM 4

int main(){

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
