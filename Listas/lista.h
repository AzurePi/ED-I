// TAD: lista seq.
#define MAX 100 //estimativa do tamanho máximo da lista
#define boolean int //define tipo boleano (que não existe em C)
#define TRUE 1  
#define FALSE 0


// Estruturas e tipos empregados
//-------------------------------------------
//Tipo chave
typedef int tipo_chave;

//Tipo registro
typedef struct {
	char nome[30];
	int idade;
	float media_final;
	//... (caso tenha mais campos)
} tipo_dado;

//Tipo elemento (registro + chave)
typedef struct {
	tipo_chave chave;
	tipo_dado info;
} tipo_elem;

//Tipo lista (sequencial encadeada)
typedef struct {
	int nelem; //número de elementos
	tipo_elem A[MAX + 1];
} lista;
//-------------------------------------------

// Operações
//-------------------------------------------
boolean Vazia(lista *L);
boolean Cheia(lista *L);
void Definir(lista *L);
void Apagar(lista *L);
boolean Inserir_posic(tipo_elem x, int p, lista *L);
boolean Busca_bin(tipo_chave x, lista *L, int *p); // Igual a 'Buscar_ord'
void Remover_posic(int *p, lista *L);
boolean Remover_ch(tipo_chave x, lista *L);
void Impr_elem(tipo_elem t);
void Imprimir(lista *L);
int Tamanho(lista *L);

// Implementadas por Lucas e Pedro:
// -----------------------------------------
boolean Inserir_ord_Nome(tipo_elem x, lista *L); //Insere ordenado por nome
boolean Buscar_Nome(char *nome, lista *L, int *p);  //Busca sequencial por nome
boolean Buscar_ord_Nome(char *nome, lista *L, int *p); //Busca ordenada por nome
boolean Inserir_ord_ch(tipo_elem x, lista *L);   //Insere ordenado por chave
boolean Buscar(tipo_chave x, lista *L, int *p);  //Busca sequencial por chave
boolean Buscar_ord(tipo_chave x, lista *L, int *p); //Busca binária por chave
//-------------------------------------------

