////Pedro Benedicto de Melo Cardana

// TAD: Árvore binária de busca balanceada (AVL)

// Estruturas e tipos empregados -------------------------
typedef struct no {
  int valor;
  int altura; // fator de balanceamento do nó
  struct no *esq, *dir;
} No;
// -------------------------------------------------------

// Operações ---------------------------------------------
No *novoNo(int x);

int alturaNo(No *raiz);
int maior(int altA, int altB); // para determinar a maior altura
int calcularFator(No *raiz);   // calcula o fator de balanceamento

No *rotacaoEsquerda(No *raiz);
No *rotacaoDireita(No *raiz);
No *rotacaoDuplaEsquerda(No *raiz);
No *rotacaoDuplaDireita(No *raiz);

No *inserir(No *raiz, int x);
No *remover(No *raiz, int x);

No *menorNo(No *raiz); // auxilia na remoção
// -------------------------------------------------------

// Impressões --------------------------------------------
void imprimirPreOrdem(No *raiz);
void imprimirInOrdem(No *raiz);
void imprimirPosOrdem(No *raiz);
// -------------------------------------------------------
