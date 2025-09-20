#include <stdio.h>
#include <stdlib.h>

typedef enum { VERMELHO, PRETO } Cor;

typedef struct No {
    int valor;
    Cor cor;
    struct No *esq, *dir, *pai;
} No;

typedef struct {
    No *raiz;
} ArvoreRB;

No* novoNo(int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->cor = VERMELHO;
    no->esq = no->dir = no->pai = NULL;
    return no;
}

No* rotacaoEsq(No* raiz, No* x) {
    No* y = x->dir;
    x->dir = y->esq;
    if (y->esq) y->esq->pai = x;
    y->pai = x->pai;
    if (!x->pai) raiz = y;
    else if (x == x->pai->esq) x->pai->esq = y;
    else x->pai->dir = y;
    y->esq = x;
    x->pai = y;
    return raiz;
}

No* rotacaoDir(No* raiz, No* y) {
    No* x = y->esq;
    y->esq = x->dir;
    if (x->dir) x->dir->pai = y;
    x->pai = y->pai;
    if (!y->pai) raiz = x;
    else if (y == y->pai->dir) y->pai->dir = x;
    else y->pai->esq = x;
    x->dir = y;
    y->pai = x;
    return raiz;
}

No* corrigirInsercao(No* raiz, No* z) {
    while (z->pai && z->pai->cor == VERMELHO) {
        No* avo = z->pai->pai;
        if (z->pai == avo->esq) {
            No* tio = avo->dir;
            if (tio && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                z = avo;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    raiz = rotacaoEsq(raiz, z);
                }
                z->pai->cor = PRETO;
                avo->cor = VERMELHO;
                raiz = rotacaoDir(raiz, avo);
            }
        } else {
            No* tio = avo->esq;
            if (tio && tio->cor == VERMELHO) {
                z->pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                z = avo;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    raiz = rotacaoDir(raiz, z);
                }
                z->pai->cor = PRETO;
                avo->cor = VERMELHO;
                raiz = rotacaoEsq(raiz, avo);
            }
        }
    }
    raiz->cor = PRETO;
    return raiz;
}

No* inserir(No* raiz, int valor) {
    No* z = novoNo(valor);
    No* y = NULL;
    No* x = raiz;
    while (x) {
        y = x;
        if (z->valor < x->valor) x = x->esq;
        else x = x->dir;
    }
    z->pai = y;
    if (!y) raiz = z;
    else if (z->valor < y->valor) y->esq = z;
    else y->dir = z;
    return corrigirInsercao(raiz, z);
}

void imprimir(No* raiz, int nivel) {
    if (!raiz) return;
    imprimir(raiz->esq, nivel+1);
    for (int i=0; i<nivel; i++) printf("   ");
    printf("%d(%c)\n", raiz->valor, raiz->cor==VERMELHO?'R':'B');
    imprimir(raiz->dir, nivel+1);
}

int main() {
    ArvoreRB arv;
    arv.raiz = NULL;
    arv.raiz = inserir(arv.raiz, 10);
    arv.raiz = inserir(arv.raiz, 20);
    arv.raiz = inserir(arv.raiz, 30);
    arv.raiz = inserir(arv.raiz, 15);
    imprimir(arv.raiz, 0);
    return 0;
}
