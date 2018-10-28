/*  Disciplina: CC6252 - Compiladores
 *  Projeto V - Analisador Semântico
 *  Desenvolvido por: João Victor Fernandes de Souza - RA: 22116012-0
 *                    Marcus Vinicius Sato Moré      - RA: 22115003-0
 */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
// Adicionando arquivo de funções auxiliares
#include "helpers.c"

typedef struct {
    char arr[50];
    int last;
} PilhaA;

typedef struct {
    char arr[50][3];
    int last;
} PilhaB;

int Tseq = 0;
int p = 0;

void printStack(PilhaB * B){
    for(int i = 0; i < 10; i++){
        printf("\n%d: %s", i, B->arr[i]);
    }
}

void solve(char op, char a[], char b[]){
    printf("\nLDA %s\n", b);

    switch(op){
        case '+':
            printf("ADA %s\n", a);
            break;
        case '-':
            printf("SUB %s\n", a);
            break;
        case '*':
            printf("MUL %s\n", a);
            break;
        case '/':
            printf("DIV %s\n", a);
            break;
        default:
            break;
    }

    Tseq++;
    printf("STA T%d\n", Tseq);

    //exit(0);
}

void push(void * pilha, void * value, bool isA){
    if( isA ) { // Insere 'value' em PilhaA
        PilhaA * A = (PilhaA*) pilha;
        char val = *((char*) value);
        A->last++;
        A->arr[A->last] = val;
    }
    else {
        PilhaB * B = (PilhaB*) pilha;
        char * val = (char*) value;
        B->last++;
        copy(B->arr[B->last], val);
    }
}

void * pop(void * pilha, bool isA){
    if( isA ){  
        PilhaA * A = (PilhaA*) pilha;
        A->last--;
        return &(A->arr[A->last+1]);
    }
    else{
        PilhaB * B = (PilhaB*) pilha;
        B->last--;
        return B->arr[B->last+1];
    }
}

void solveOne(PilhaA * A, PilhaB * B){
    char op = *((char*) pop(A, true));
                
    char * a = (char*) pop(B, false);
    char * b = (char*) pop(B, false);

    solve(op, a, b);
}

char top(PilhaA A){
    return A.last > -1 ? A.arr[A.last] : '0';
}

int priority(char op){
    return (op == '+' || op == '-') ? 0 : 1;
}

bool hasHigherOrEqual(PilhaA A, char op){
    char topOp = top(A);
    return topOp != '0' && priority(topOp) >= priority(op);
}

char * geraCodigo(char e[]){
    PilhaA A; 
    A.last = -1;
    PilhaB B;
    B.last = -1;

    while(e[p] != 0){
        //printf("\nLeitura: %d", p);
        //printf("\nChar: %c", e[p]);
        if(e[p] >= '0' && e[p] <= '9'){
            char v[] = { e[p], 0 };
            push(&B, v, false);
            p++;
        }
        else 
            if(e[p] == '+' || e[p] == '-' || e[p] == '*' || e[p] == '/'){
                if(hasHigherOrEqual(A, e[p])){
                    // Calcula a última operação da pilha
                    solveOne(&A, &B);
                    char v[3] = "T";
                    concat(v, (Tseq + '0'));
                    push(&B, v, false);
                }
                else {
                    push(&A, &e[p], true);
                    p++;
                }
            }
            else 
                if(e[p] == '('){
                    p++;
                    char * res = geraCodigo(e);
                    // printf("\nResultado Interno: %s", res);
                    // printStack(&B);
                    push(&B, res, false);
                    // printf("\nLast: %d", B.last);
                }
                else
                    if(e[p] == ')'){
                        // Resolve as operações pendentes na pilha
                        while(A.last != -1){
                            solveOne(&A, &B);
                            char v[3] = "T";
                            concat(v, (Tseq + '0'));
                            //printf("\nVariavel Criada: %s\n", v);
                            push(&B, v, false);
                        }
                        p++;
                        return (char*) pop(&B, false);
                    }
    }

    while(A.last != -1){
        solveOne(&A, &B);
        char v[3] = "T";
        concat(v, (Tseq + '0'));
        // printf("\nVariavel Criada: %s\n", v);
        push(&B, v, false);
    }

    return "End";
}

int main(){
    char e[200];
    printf("Digite a entrada: ");
    fflush(stdin);
    gets(e);
    printf("\nSaida:\n");

    geraCodigo(e);
    printf("\n");
}
