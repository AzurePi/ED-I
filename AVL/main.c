////Pedro Benedicto de Melo Cardana

#include "avl.h"
#include <stdio.h>

int main() {
  No *raiz = NULL;
  int i;

  raiz = inserir(raiz, 5);
  raiz = inserir(raiz, 2);
  raiz = inserir(raiz, 10);

  printf("Pré-ordem: ");
  imprimirPreOrdem(raiz);
  printf("\n");
  printf("In-ordem: ");
  imprimirInOrdem(raiz);
  printf("\n");
  printf("Pós-ordem: ");
  imprimirPosOrdem(raiz);
  printf("\n");

  /*
  Qualquer inserção que desbalanceia a árvore e qualquer remoção causam
  "segmentation fault"
  */

  return 0;
}
