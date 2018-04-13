#include <stdio.h>

void fill(int pares, int array[], int indices[]);
void inicia(int novosIndices[], int pares);
int percorre(int i, int array[]);
int conta(int pares, int array[]);
void une(int pares, int array[], int novosIndices[], int indices[]);

int main(){
    int testes, pessoas, pares;
    scanf("%d", &testes);
    int i = 0;
    while(i < testes){
        scanf("%d %d", &pessoas, &pares);
        int array[pares*2], indices[pares*2], novosIndices[pares*2];
        if(pares == 1){
            fill(pares, array, indices);
            printf("2\n");
        }
        else{
            fill(pares, array, indices);
            inicia(novosIndices, pares);
            une(pares, array, novosIndices, indices);
        }
        i++;
    }
    return 0;
}

void fill(int pares, int array[], int indices[]){
    int i, a = 1;
    for(i = 0; i < pares*2; i++){
        scanf("%d", &array[i]);
        indices[i] = a;
        if((i+1) % 2 == 0)
            a++;
    }
}

void inicia(int novosIndices[], int pares){
    int i;
    for(i = 0; i < pares*2; i++)
        novosIndices[i] = -1;
}

int percorre(int i, int array[]){
    int j;
    for(j = 0; array[j] != -1; j++){
        if(array[j] == i)
            return 1;
    }
    return 0;
}

int conta(int pares, int array[]){
    int i, num = 0;
    for(i = 0; i < pares*2; i++){
        if(array[i] != -1)
            num++;
    }
    return num;
}

void une(int pares, int array[], int novosIndices[], int indices[]){
    int i = 0, j, a = 2, c = 0, maior = 0;
    while(c < pares*2){
        if(array[c] != 0){
            i = 0;
            a = 2;
            novosIndices[0] = array[c];
            novosIndices[1] = array[c+1];
            while(novosIndices[i] != -1){
                for(j = 0; j < pares*2; j++){
                    if(array[j] == novosIndices[i]){
                        array[j] = 0;
                        int aux = indices[j] == indices[j+1] ? j+1 : j-1;
                        if(percorre(array[aux], novosIndices) != 1){
                            novosIndices[a] = array[aux];
                            a++;
                        }
                        array[aux] = 0;
                    }
                }
                i++;
            }
        }
        int  p = conta(pares, novosIndices);
        if(p > maior)
            maior = p;
        inicia(novosIndices, pares);
        c++;
    }
        printf("%d\n", maior);
}
