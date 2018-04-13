#include <stdio.h>
#include <stdlib.h>

typedef struct roleta{
    void *ant;
    int numero;
    void *prox;
}elemento;

elemento *inicio, *fim;

//prototipos
void preencheRoleta(int n);
void giraDireta(int V, int n);
void giraEsquerda(int V, int n);
int executaComandos(int n);

int main(){
    int n;
    //printf("Insira o numero de elementos da roleta: ");
    scanf("%d", &n);
    preencheRoleta(n);
    executaComandos(n);
    return 0;
}

 void preencheRoleta(int n){
    int i;
    for(i = 0; i < n; i++){  //inclue 'n' elementos na roleta
        elemento *aux, *auxAnt;
        aux = (elemento *) malloc(sizeof(elemento));
        scanf("%d", &aux->numero);

        if(inicio == NULL){  //se for o primeiro elemento da estrutura
            inicio = aux;
            fim = aux;
            aux->prox = fim;
            aux->ant = fim;
        }
        else{
            auxAnt = fim;
            fim->prox = aux;
            fim = aux;
            fim->prox = inicio;
            fim->ant = auxAnt;
        }
    }
    inicio->ant = fim;
 }

 void giraDireita(int V, int n){
    elemento *aux;
    aux = inicio;
    int i = 0;
    while(i < V){
        aux = aux->ant;
        i++;
    }
    inicio = aux;
    for(i = 0; i < n; i++){
        printf("%d ", aux->numero);
        aux = aux->prox;
    }
    printf("\n");
 }

 void giraEsquerda(int V, int n){
    elemento *aux;
    aux = inicio;
    int i = 0;
    while(i < V){
        aux = aux->prox;
        i++;
    }
    inicio = aux;
    for(i = 0; i < n; i++){
        printf("%d ", aux->numero);
        aux = aux->prox;
    }
    printf("\n");
 }

 int executaComandos(int n){
    char C;
    int V;
    while(1){
        //printf("Insira o comando desejado e o numero de vezes que o comando deve ser executado: ");
        scanf("%c", &C);
        if(C == 'S'){
            return 0;
        }
        else{
            scanf("%d", &V);
            if(C == 'D')
                giraDireita(V, n);
            else if(C == 'E')
                giraEsquerda(V, n);
        }
    }
 }
