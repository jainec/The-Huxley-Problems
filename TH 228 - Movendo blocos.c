#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int dado;
    void *prox;
}pilha;

int posicaoDe[30];
pilha *pi[30], *topo[30];

//prototipos
void criaPilhas(int n);
void push(int dado1, int i);
void pop(int i);
void moverAsobreB(int a, int b, int n);
void moverAacimaB(int a, int b, int n);
void pilhaAsobreB(int a, int b, int n);
void pilhaAacimaB(int a, int b);
void imprimir(int n);
void lerComandos(int n);

int main(){
    int n;
    scanf("%d", &n);     //recebe o numero de blocos do conjunto
    criaPilhas(n);
    lerComandos(n);
    imprimir(n);
    return 0;
}

//cria 'n' pilhas no vetor de pilhas
void criaPilhas(int n){
    int i;
    for(i = 0; i < n; i++){
        posicaoDe[i] = i;
        pi[i] = (pilha *) malloc(sizeof(pilha));
        pi[i]->dado = i;
        pi[i]->prox = NULL;
        topo[i] = pi[i];
    }
}

//coloca um elemento numa pilha
void push(int dado1, int i){
    pilha *aux;
    aux = (pilha *) malloc(sizeof(pilha));
    aux->dado = dado1;
    aux->prox = topo[i];
    topo[i] = aux;
}

//remove um elemento de uma pilha
void pop(int i){
    if(pi[i] == NULL) return;
    pilha *aux;
    aux = topo[i]->prox;
    free(topo[i]);
    topo[i] = aux;
}

/*
    mover a sobre b
    Onde a e b sao numeros(inteiros) de blocos, colocar o bloco a em cima do bloco b
    apos ter retornado todos os blocos acima de a e b para suas posicoes iniciais.
*/
void moverAsobreB(int a, int b, int n){
    pilha *aux;
    int piA = posicaoDe[a];
    int i = 0;
    while(topo[piA]->dado != a && i++ <= n){   //retorna todos os blocos acima de A para suas posicoes inicias
        aux = topo[piA]->prox;
        push(topo[piA]->dado, topo[piA]->dado);
        posicaoDe[topo[piA]->dado] = topo[piA]->dado;
        free(topo[piA]);
        topo[piA] = aux;
    }
    pop(piA);

    int piB = posicaoDe[b];
    i = 0;
    while(topo[piB]->dado != b && i++ <= n){   //retorna todos os blocos acima de B para suas posicoes inicias
        aux = topo[piB]->prox;
        push(topo[piB]->dado, topo[piB]->dado);
        posicaoDe[topo[piB]->dado] = topo[piB]->dado;
        free(topo[piB]);
        topo[piB] = aux;
    }
    push(a, posicaoDe[b]);
    posicaoDe[a] = posicaoDe[b];
}

/*
    mover a acima b
    Onde a e b sao numeros de blocos, colocar o bloco a no topo da pilha contendo b,
    apos ter retornado todos os blocos que estao acima de a para suas posicoes iniciais
*/
void moverAacimaB(int a, int b, int n){
    pilha *aux;
    int piA = posicaoDe[a];
    int i = 0;
    while(topo[piA]->dado != a && i++ <= n){   //retorna todos os blocos acima de A para suas posi��es inicias
        aux = topo[piA]->prox;
        push(topo[piA]->dado, topo[piA]->dado);
        posicaoDe[topo[piA]->dado] = topo[piA]->dado;
        free(topo[piA]);
        topo[piA] = aux;
    }
    pop(piA);
    push(a, posicaoDe[b]);
    posicaoDe[a] = posicaoDe[b];
}

/*
    pilha a sobre b
    Onde a e b sao numeros de blocos, mover a pilha de blocos formada por a e todos
    os blocos acima de a, em cima de b, isso, apos ter retornado todos os blocos acima
    de b para suas posicoes iniciais. A pilha formada por a e seus blocos superiores eh
    colocada em cima de b de modo que fique na mesma ordem anterior.
*/
void pilhaAsobreB(int a, int b, int n){
    int piB = posicaoDe[b], i = 0;
    pilha *aux;
    while(topo[piB]->dado != b && i++ <= n){   //retorna todos os blocos acima de B para suas posi��es inicias
        aux = topo[piB]->prox;
        push(topo[piB]->dado, topo[piB]->dado);
        posicaoDe[topo[piB]->dado] = topo[piB]->dado;
        free(topo[piB]);
        topo[piB] = aux;
    }

    int piA = posicaoDe[a];
    pilha *aux2, *top = NULL;
    aux = topo[piA];
    while(1){                               //guarda pilha de A em pilha auxiliar
        aux2 = (pilha *) malloc(sizeof(pilha));
        aux2->dado = aux->dado;
        aux2->prox = top;
        top = aux2;
        if(aux->dado == a)
            break;
        aux = topo[piA]->prox;
        free(topo[piA]);
        topo[piA] = aux;

    }
    pop(piA);
    aux = top;
    while(aux != NULL){                  //coloca pilha de A sobre pilha de B
        push(aux->dado, posicaoDe[b]);
        posicaoDe[aux->dado] = posicaoDe[b];
        aux = aux->prox;
    }
}

/*
    pilha a acima b
    Onde a e b sao n�meros de blocos, colocar a pilha formada pelo bloco a e blocos
    acima de a, no topo da pilha contendo o bloco b. A pilha formada por a nao perde
    a sua ordem anterior.
*/
void pilhaAacimaB(int a, int b){
    int piA = posicaoDe[a];
    pilha *aux, *aux2, *top = NULL;
    aux = topo[piA];
    while(1){                           //guarda pilha de A em pilha auxiliar
        aux2 = (pilha *) malloc(sizeof(pilha));
        aux2->dado = aux->dado;
        aux2->prox = top;
        top = aux2;
        if(aux->dado == a)
            break;
        aux = topo[piA]->prox;
        free(topo[piA]);
        topo[piA] = aux;

    }
    pop(piA);
    aux = top;
    while(aux != NULL){                  //coloca pilha de A sobre a pilha que contem B
        push(aux->dado, posicaoDe[b]);
        posicaoDe[aux->dado] = posicaoDe[b];
        aux = aux->prox;
    }
}

void imprimir(int n){
    int i;
    pilha *aux, *aux2, *top;

    for(i = 0; i < n; i++){ //00
        if(topo[i] != NULL){ //01
            printf("%d:", i);
            aux = topo[i];
            if(aux != pi[i]){         //guarda a pilha numa pilha auxiliar pra imprimir na ordem
                top = NULL;
                while(aux != NULL){
                    aux2 = (pilha *) malloc(sizeof(pilha));
                    aux2->dado = aux->dado;
                    aux2->prox = top;
                    top = aux2;
                    aux = topo[i]->prox;
                    free(topo[i]);
                    topo[i] = aux;
                }
                aux = top;
            }
            while(aux != NULL){
                printf(" %d", aux->dado);
                aux = aux->prox;
            }
            printf("\n");
        }//01
        else
            printf("%d:\n", i);
    }//00
}

void lerComandos(int n){
    char p1[6], p2[6], aux;
    int a, b;
    while(1){
        scanf("%s%c", &p1, &aux);
        if(strcmp(p1, "final") == 0) break;
        scanf("%d", &a);
        scanf("%s%c", &p2, &aux);
        scanf("%d", &b);
        if(!(a==b || posicaoDe[a] == posicaoDe[b])){
            if(b >= n)
                b = 0;
            if(a >= n)
                a = 0;
            if(strcmp(p1, "mover") == 0){
                if(strcmp(p2, "sobre") == 0)
                   moverAsobreB(a, b, n);
                else
                    moverAacimaB(a,b, n);
            }
            else
                if(strcmp(p2, "sobre") == 0)
                    pilhaAsobreB(a,b, n);
                else
                    pilhaAacimaB(a,b);
        }
    }
}
