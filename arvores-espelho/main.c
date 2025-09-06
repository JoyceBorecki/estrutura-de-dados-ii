#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore {
    char valor;
    struct Arvore *esq, *dir;
} Arvore;

int eh_espelho(Arvore *a, Arvore *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    return (a->valor == b->valor) &&
           eh_espelho(a->esq, b->dir) &&
           eh_espelho(a->dir, b->esq);
}

Arvore* cria_espelho(Arvore *a) {
    if (a == NULL) return NULL;
    Arvore *n = (Arvore*) malloc(sizeof(Arvore));
    n->valor = a->valor;
    n->esq = cria_espelho(a->dir);
    n->dir = cria_espelho(a->esq);
    return n;
}

Arvore* novo_no(char valor) {
    Arvore *n = (Arvore*) malloc(sizeof(Arvore));
    n->valor = valor;
    n->esq = n->dir = NULL;
    return n;
}

int main() {
    Arvore *T = novo_no('A');
    T->esq = novo_no('B');
    T->dir = novo_no('C');
    T->esq->esq = novo_no('D');
    T->dir->esq = novo_no('E');
    T->dir->dir = novo_no('F');

    Arvore *E = cria_espelho(T);

    printf("São espelhos? %s\n", eh_espelho(T, E) ? "Sim" : "Não");

    return 0;
}
