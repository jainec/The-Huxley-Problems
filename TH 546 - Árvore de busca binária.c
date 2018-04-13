#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree{
    int valor;
    struct tree *pai, *dir, *esq;
}arvore;

arvore *raiz, *atual;

//Prototipos
void insere(int valor, char lado);
void criaArvore(char str[]);
int verificaBinaria(arvore *aux);
void executa(void);

int main(){
    raiz = NULL;
    atual = NULL;
    char str[1000];
    fgets(str, 1000, stdin);
    criaArvore(str);
    executa();
    return 0;
}

void insere(int valor, char lado){
    arvore *aux = (arvore*) malloc(sizeof(arvore));
    arvore *aux2 = (arvore*) malloc(sizeof(arvore));
    if(raiz == NULL){              //primeiro elemento adicionado
        aux2->valor = -1;
        aux2->pai = aux;
        aux2->esq = NULL;
        aux2->dir = NULL;

        aux->valor = valor;
        aux->pai = NULL;
        aux->dir = aux2;
        aux->esq = aux2;
        raiz = aux;
    }else{
        if(lado == 'e'){           //lado esquerdo
            aux2->valor = -1;
            aux2->pai = aux;
            aux2->esq = NULL;
            aux2->dir = NULL;

            aux->valor = valor;
            aux->pai = atual;
            aux->dir = aux2;
            aux->esq = aux2;
            atual->esq = aux;
        }else{                  //lado direito
            aux2->valor= -1;
            aux2->pai = aux;
            aux2->esq = NULL;
            aux2->dir = NULL;

            aux->valor = valor;
            aux->pai = atual;
            aux->dir = aux2;
            aux->esq = aux2;
            atual->dir = aux;
        }
    }
    atual = aux;
}

void criaArvore(char str[]){
    int i, valor;
    char c, lado;
    for(i = 0; i <strlen(str); i++){
        char aux[1000] = "";
        if(str[i] == '('){
            int a = 0;
            while(str[i+1] != '(' && str[i+1] != ')' && str[i+1] != ' '){
                aux[a] = str[++i];
                a++;
            }
            if(str[i+1] == ')'){
                if(lado=='e')
                    atual = atual->esq;
                else
                    atual = atual->dir;
            }else{
                valor = atoi(aux);
                insere(valor, lado);
                lado = 0;
            }
        }else if(str[i] == ')'){
            lado = 'd';
            atual = atual->pai;
        }
    }
}

int verificaBinaria(arvore *aux){
    if(aux == NULL)
        return 1;
    if (aux->valor != -1){
        if( (aux->esq->valor != -1 && aux->esq->valor > aux->valor) || (aux->dir->valor != -1 && aux->dir->valor < aux->valor) )
            return 0;
    }
    return verificaBinaria(aux->esq) && verificaBinaria(aux->dir);
}

void executa(){
    if(verificaBinaria(raiz))
        printf("VERDADEIRO");
    else
        printf("FALSO");
}
