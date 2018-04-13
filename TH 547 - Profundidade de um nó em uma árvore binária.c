#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree{
    int valor;
    struct tree *pai, *dir, *esq;
}arvore;

arvore *raiz, *atual;

//Prototipos
void converte(char str[], char strConvertida[]);
void insere(int valor, char lado);
void criaArvore(char str[]);
int procuraN(arvore *aux, int n);
int calculaProfundidade();
void lerString(char strConvertida[]);
int verifica(int n);

int main(){
    raiz = NULL;       //inicializa o ponteiro raiz
    atual = NULL;      //inicializa o ponteiro atual que vai sempre apontar pra posição em que o novo nó deve ser inserido
    char str[1000];
    lerString(str);    //ler a string e converte os números
    int n;
    scanf("%d", &n);
    criaArvore(str);
    verifica(n);
    return 0;
}

//Essa fução recebe uma string (ex: (12(7(3()())(10()(11()())))(23(17()())(31()())))
//Retorna essa string com os numeros convertidos pra inteiro. Ex: o '12', o '1' ta na posição 1 do array
//enquanto o '2' ta na posição 2 do array. Essa função pega o '1' e o '2' converte pra um único numero (12)
//e insere o 12 na posição 1 do array
void converte(char str[], char strConvertida[]){
    int i = 0, a = 0, num = -1, b = 0;
    char aux[1000];
    while(str[i] != '\0'){
        if(str[i] == '(' || str[i] == ')' || str[i] == ' '){   //se não for um número mantém o carcter normalmente no array
            strConvertida[b] = str[i];
            b++;
            i++;
        }
        else {     //se for número
            while(str[i] != '(' && str[i] != ')' && str[i] != ' ' && str[i] != '\0'){   //enquanto continuar sendo número, coloca numa string auxiliar
                aux[a] = str[i];
                a++;
                i++;
            }
            aux[a] = '\0';
            num = atoi(aux);         //converte a string auxiliar para um inteiro
            strConvertida[b] = num;     //coloca o inteiro no array
            b++;
            a = 0;
            strConvertida[b] = '\0';
        }
    }
}

//insere um nó na árvore
void insere(int valor, char lado){
    arvore *aux = (arvore*) malloc(sizeof(arvore));
    arvore *aux2 = (arvore*) malloc(sizeof(arvore));
    if(raiz == NULL){              //primeiro elemento adicionado
        aux2->valor = -1;          //o aux é o nó com o valor que queremos inserir
        aux2->pai = aux;           //o aux2 é criado como 'folha' pro aux, recebendo valor de -1 para facilitar pra voltar pro pai na criaçao da arvore
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
    int i;
    char lado;
    for(i = 0; i<strlen(str); i++){
        if(str[i]=='('){
            int valor = 0;
            if(str[i+1]!= '(' && str[i+1] != ')' && str[i+1] != ' '){ //se encontrar um '(' e logo após um numero, coloca o numero na arvore
                valor = str[i+1];                                     //e laod recebe 'e' pois continua inserindo na esquerda
            }
            if(str[i+1] == ')'){    //se encontrar um '(' e em seguida ')' verifica p que lado da arvore ir
                if(lado == 'e')
                    atual = atual->esq;
                else
                    atual = atual->dir;
            }else{
                insere(valor, lado);
                lado = 'e';
            }
        }else if(str[i] == ')'){     //se encontrar um ')', lado recebe direita e volta pro pai
            lado = 'd';
            atual = atual->pai;
        }
    }
}

//função recursiva que faz uma busa do tipo LNR, se achar o 'n' procurado faz o atual apontar pra o nó
//que contem 'n' e retorna 0
int procuraN(arvore *aux, int n){
    if(aux != NULL){
        procuraN(aux->esq, n);
        if(aux->valor == n){
            atual = aux;
            return 0;
        }
        return procuraN(aux->dir, n);
    }
}

int calculaProfundidade(){  //começa de onde o ponteiro atual tá apontando e vai subindo na árvore ate chegar na raiz (retorna profundidade)
    int i = 0;
    while(atual != raiz){
        atual = atual->pai;
        i++;
    }
    return i;
}

void lerString(char strConvertida[]){
    char str[1000];
    fgets(str, 1000, stdin);
    setbuf(stdin, NULL);
    converte(str, strConvertida);
}

int verifica(int n){
    arvore *aux = raiz;
    int i = procuraN(aux, n);
    if(i == 0){
        int p = calculaProfundidade();
        printf("ESTA NA ARVORE\n");
        printf("%d", p);


    }else{
       printf("NAO ESTA NA ARVORE\n");
        printf("-1");
    }
}
