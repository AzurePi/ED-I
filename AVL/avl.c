////Pedro Benedicto de Melo Cardana

// Implementação: Árvore binária de busca balanceada (AVL)
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

// Operações ---------------------------------------------

// Aloca um No com valor x na memória e retorna seu endereço
No *novoNo(int x) {
  No *novo = malloc(sizeof(No));
  novo->valor = x;
  novo->altura = 1; // todo nó é inserido como folha, e toda folha tem altura 1
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}

// Retorna a altura do No no endereço raiz
// Retorna 0 se raiz é NULL
int alturaNo(No *raiz) {
  if (raiz == NULL)
    return 0;
  return raiz->altura;
}

// Retorna o maior entre os dois valores
int maior(int a, int b) {
  if (a >= b)
    return a;
  return b;
}

// Retorna o fator de balanceamento do No no endereço raiz
// Retorna 0 se raiz é NULL
int calcularFator(No *raiz) {
  if (raiz == NULL)
    return 0;
  return alturaNo(raiz->esq) - alturaNo(raiz->dir);
}

// Operação de rotação à esquerda a partir do No em r
No *rotacaoEsquerda(No *r) {
  No *auxDir = r->dir;
  No *aux = auxDir->esq;

  // rotação
  auxDir->esq = r;
  r->dir = aux;

  // recalculamos a altura de quem foi movimentado
  if (r != NULL)
    r->altura = maior(alturaNo(r->esq), alturaNo(r->dir)) + 1;
  if (auxDir != NULL)
    auxDir->altura = maior(alturaNo(auxDir->esq), alturaNo(auxDir->dir)) + 1;

  return auxDir; // retorna a nova raiz
}

// Operação de rotação à esquerda a partir do No em r
No *rotacaoDireita(No *r) {
  No *auxEsq = r->esq;
  No *aux = auxEsq->dir;

  // rotação
  auxEsq->dir = r;
  r->esq = aux;

  // recalculamos a altura de quem foi movimentado
  if (r != NULL)
    r->altura = maior(alturaNo(r->esq), alturaNo(r->dir)) + 1;
  if (auxEsq != NULL)
    auxEsq->altura = maior(alturaNo(auxEsq->esq), alturaNo(auxEsq->dir)) + 1;

  return auxEsq; // retorna a nova raiz
}

// Composição de uma rotação à direita centrada no filho à direita, com de uma à
// esquerda centrada em r
No *rotacaoDuplaEsquerda(No *r) {
  r->dir = rotacaoDireita(r->dir);
  return rotacaoEsquerda(r);
}

// Composição de uma rotação à esquerda centrada no filho à esquerda com de uma
// à direita centrada em r
No *rotacaoDuplaDireita(No *r) {
  r->esq = rotacaoEsquerda(r->esq);
  return rotacaoDireita(r);
}

// realiza o balanceamento do No em raiz
No *balancear(No *raiz) {
  int fator = calcularFator(raiz);
  int fatorEsq = calcularFator(raiz->esq);
  int fatorDir = calcularFator(raiz->dir);

  // rotação Ã  esquerda
  if (fator < -1 && fatorDir <= 0)
    raiz = rotacaoEsquerda(raiz);
  // rotação Ã  direita
  else if (fator > 1 && fatorEsq >= 0)
    raiz = rotacaoDireita(raiz);
  // rotação dupla esquerda-direita
  else if (fator > 1 && fatorEsq < 0)
    raiz = rotacaoDuplaDireita(raiz);
  // rotação dupla direita-esquerda
  else if (fator < -1 && fatorDir > 0)
    raiz = rotacaoDuplaEsquerda(raiz);

  return raiz;
}

// Insere um No com valor x na árvore, a partir do endereço raiz
No *inserir(No *raiz, int x) {
  // se achamos um espaço vazio, inserimos
  if (raiz == NULL)
    return novoNo(x);

  // se é menor, vamos para a esquerda
  if (x < raiz->valor)
    raiz->esq = inserir(raiz->esq, x);
  // se é maior, vamos para a direita
  else if (x > raiz->valor)
    raiz->dir = inserir(raiz->dir, x);
  // se é igual
  else
    return raiz;

  // atualiza a altura do ná
  raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

  return balancear(raiz); // rebalanceaia a árvore e retorna
}

// Busca o No de valor x e o remove da árvore
No *remover(No *raiz, int x) {
  // se chegamos ao fim da árvore
  if (raiz == NULL)
    return NULL;

  if (x < raiz->valor)
    raiz->esq = remover(raiz->esq, x);
  else if (x > raiz->valor)
    raiz->dir = remover(raiz->dir, x);
  else {
    // se há uma ou nenhuma subárvore
    if (raiz->esq == NULL || raiz->dir == NULL) {
      // se há subárvore à esquerda, salva-a, do contrário, salva a à direita
      No *aux = raiz->esq ? raiz->esq : raiz->dir;

      // se não há subárvores
      if (aux == NULL) {
        aux = raiz;
        raiz = NULL;

        // se há uma única
      } else
        raiz = aux;

      free(aux);

      // se há duas subárvores
    } else {
      // subtituímos pelo menor valor à direita
      No *aux = menorNo(raiz->dir);
      raiz->valor = aux->valor;
      raiz->dir = remover(raiz->dir, aux->valor);
    }
  }

  // atualiza a altura do nó
  if (raiz != NULL)
    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

  return balancear(raiz); // rebalanceaia a árvore e retorna
}

No *menorNo(No *raiz) {
  No *aux = raiz;

  while (aux->esq != NULL)
    aux = aux->esq;

  return aux;
}

// Impressões --------------------------------------------

// Imprime a árvore em pré-ordem
void imprimirPreOrdem(No *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->valor);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
  }
}

// Imprime a árvore em in-ordem
void imprimirInOrdem(No *raiz) {
  if (raiz != NULL) {
    imprimirInOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    imprimirInOrdem(raiz->dir);
  }
}

// Imprime a árvore em pós-ordem
void imprimirPosOrdem(No *raiz) {
  if (raiz != NULL) {
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d ", raiz->valor);
  }
}
