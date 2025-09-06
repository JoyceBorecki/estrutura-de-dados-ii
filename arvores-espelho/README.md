# Árvores Espelho

O espelho de uma árvore binária `T`, `esp(T)`, é a árvore binária definida recursivamente da seguinte forma:

- Se `T` for vazia então `esp(T)` é a árvore vazia;
- Se `T` tem raiz `Tr`, subárvore da esquerda `Te` e subárvore da direita `Td`, então `esp(T)` é a árvore binária com raiz `Tr`, subárvore esquerda `esp(Td)` e subárvore direita `esp(Te)`.

## Exemplo

![Árvore espelho](imagens/image.png)

## Exercício

Com base nessa definição, implemente duas funções:

1. A função **`eh_espelho`** que retorna `1` se duas árvores são espelhos entre si e `0` em contrário.  
   ```c
   int eh_espelho(Arvore *arv_a, Arvore *arv_b);
