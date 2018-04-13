#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//prototipos
void lerArray(int n, int array[]);
int qtdCerta(int sorteados[], int array[]);
void maxNminHeap(int n, int ganhadores[], char codigos[n][20], int sorteados[], int ganhadores2[], char codigos2[n][20]);

int main(){
    int sorteados[10], n;
    lerArray(10, sorteados);
    scanf("%d", &n);
    char codigos[n][20], codigos2[n][20];
    int ganhadores[n], ganhadores2[n];
    maxNminHeap(n, ganhadores, codigos, sorteados, ganhadores2, codigos2);
    return 0;
}

void lerArray(int n, int array[]){
    int i;
    for(i = 0; i < n; i++)
        scanf("%d", &array[i]);
}

int qtdCerta(int sorteados[], int array[]){
    int i, j, num = 0;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 15; j++){
            if(array[j] == sorteados[i]){
                num++;
                break;
            }
        }
    }
    return num;
}

void maxNminHeap(int n, int ganhadores[], char codigos[n][20], int sorteados[], int ganhadores2[], char codigos2[n][20]){
    char string[20];
    int i, marcados[15], acertos = 0, acertos2 = 11, a = 0, b = 0;
    for(i = 0; i < n; i++){
        scanf("%s", &string);
        lerArray(15, marcados);
        int c = qtdCerta(sorteados, marcados);
        if(c > acertos){
            acertos = c;
            a = 0;
        }
        if(c == acertos){
            acertos = c;
            ganhadores[a] = acertos;
            strcpy(codigos[a], string);
            a++;
        }
         if(c < acertos2){
            acertos2 = c;
            b = 0;
        }
        if(c == acertos2){
            acertos2 = c;
            ganhadores[b] = acertos2;
            strcpy(codigos2[b], string);
            b++;
        }
    }
    ganhadores[a] = -1;
    ganhadores2[b] = -1;
    int count = 0;
    printf("Faixa: %d acertos\n", acertos);
    for(i = 0; ganhadores[i] != -1; i++){
        printf("%s\n", codigos[i]);
        count++;
    }
    if(count == 1) printf("%d ganhador\n", count);
    else printf("%d ganhadores\n", count);

    printf("\n");

    count = 0;
    printf("Faixa: %d acertos\n", acertos2);
    for(i = 0; ganhadores2[i] != -1; i++){
        printf("%s\n", codigos2[i]);
        count++;
    }
    if(count == 1) printf("%d ganhador\n", count);
    else printf("%d ganhadores\n", count);
}
