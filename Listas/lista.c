#include "lista.h"  //Carrega o arquivo .h criado
#include <stdio.h>  //Para usar printf ,...
#include <stdlib.h> //Para usar malloc, free, exit ...
#include <string.h> //Para usar strcmp

#define MAX 100 //estimativa do tamanho máximo da lista
#define boolean int //define tipo boleano (que não existe em C)
#define TRUE 1  
#define FALSE 0

// Implementação: lista sequencial

// Operações
//-------------------------------------------
boolean Vazia(lista *L) {
	//Retorna true (1) se vazia, false (0) caso contrário
	return (L->nelem == 0);
}

boolean Cheia(lista *L) {
	//Retorna true (1) se cheia, false (0) caso contrário
	return (L->nelem == MAX);
}

void Definir(lista *L) {
	/*Cria uma lista vazia. Este procedimento deve ser chamado
	para cada nova lista antes de qualquer outra operação.*/
	L->nelem = 0;
	L->A[0].chave = 0;
}

void Apagar(lista *L) {
	// Apaga "logicamente" uma lista
	L->nelem = 0;
}

boolean Inserir_posic(tipo_elem x, int p, lista *L) {
	/*Insere x, que é um novo elemento, na posição p da lista
	Se L = a_1, a_2,... a_n então temos a_1, a_2, ...
	a_{p-1}, x, a_{p+1}, ... an.
	Devolve true se sucesso, false caso contrário (isto é: L não tem nenhuma
	posição p ou lista cheia).
	Obs: Operação para LISTA NÃO-ORDENADA */

	int q;

	// Lista cheia ou posição não existe
	if (Cheia(L) || p > L->nelem + 1 || p < 1)
		return FALSE; //Inserção falhou

	for (q = L->nelem; q >= p; q--) //Copia vizinho p/ direita
   		L->A[q + 1] = L->A[q];
   		
   	L->A[p] = x;
   	L->nelem++;
   	return TRUE; //Inserção feita com sucesso
}

void Remover_posic(int *p, lista *L) {
	/*Só é chamada após a busca ter retornado a posição p
	do elemento a ser removido*/

	int i;

	for (i = *p + 1; i <= L->nelem; i++)
		L->A[i - 1] = L->A[i];

	L->nelem--;
}

void Impr_elem(tipo_elem t) {
	printf("chave: %d\n", t.chave);
	printf("nome: %s\n", t.info.nome);
	printf("idade: %d\n", t.info.idade);
	printf("media final: %4.2f\n", t.info.media_final);
	//... (eventuais demais dados)
}

void Imprimir(lista *L) {
	//Imprime os elementos em ordem

	int i;

	if (!Vazia(L)){
		for (i = 1; i <= L->nelem; i++) {
			printf("\n--------------------\n\n");
			Impr_elem(L->A[i]);
    	}
	}
	printf("\n--------------------\n");
}

int Tamanho(lista *L) {
	// Retorna o tamanho da lista. Se L é vazia retorna 0
	return L->nelem;
}

// Implementações para listas ordenadas
//-------------------------------------------
boolean Buscar_ord(tipo_chave x, lista *L, int *p) {
	/*Retorna true se x ocorre na lista e armazena seu índice no endereço p. Se x ocorre mais de
	uma vez, aramzena a posição da primeira ocorrência. Se x não ocorre, retorna false.
	Para listas ORDENADAS*/

	int esq, dir, meio;
	esq = 1;
	dir = L->nelem;

	while (esq <= dir) {
		meio = (esq + dir) / 2;
		//se encontramos o elemento
		if (L->A[meio].chave == x){
			*p = meio;
			return TRUE;
		}
		
		if (L->A[meio].chave < x)
      		esq = meio + 1;
    	else
      		dir = meio - 1;
  	}
  	return FALSE;
}

boolean Busca_bin(tipo_chave x, lista *L, int *p) {
	/*Armazena em p a posição de x na lista ORDENADA e retorna true.
	  Se x não ocorre, retorna false*/

	int inf = 1;
	int sup = L->nelem;
	int meio;

	while (!(sup < inf)) {
		meio = (inf + sup) / 2;
		if (L->A[meio].chave == x) {
			*p = meio; 
			return TRUE; //Sai da busca
		}
		
		if (L->A[meio].chave < x)
			inf = meio + 1;
    	else
    		sup = meio - 1;
    }
	return FALSE;
}

boolean Remover_ch(tipo_chave x, lista *L) {
	/*Remoção dada a chave. Retorna true, se removeu, ou
	false, caso contrário*/

	int *p;
	boolean removeu = FALSE;

	//se a busca binária funcionar
	if (Busca_bin(x, L, p)){
    	Remover_posic(p, L); //faz a remoção
    	removeu = TRUE;
	}

  return removeu;
}

//Atualiza as chaves da lista, enumerando os elementos em ordem crescente
void numerar(lista *L) {
	int i;
	
	for (i = 0; i <= L->nelem; i++)
		L->A[i].chave = (i + 1);
}

//Insere ordenado por nome
boolean Inserir_ord_Nome(tipo_elem x, lista *L) {
	if (Cheia(L))
		return FALSE;

	int i;
	for (i = L->nelem; i > 0 && strcmp(x.info.nome, L->A[i].info.nome) < 0; i--)
		L->A[i + 1] = L->A[i];

	L->A[i + 1] = x;
	L->nelem++;
	return TRUE;
}

//Insere ordenado por chave
boolean Inserir_ord_ch(tipo_elem x, lista *L) {
	if (Cheia(L) || Repetido(x.chave, L))
		return FALSE;

	int i;
	for (i = L->nelem; i > 0 && x.chave < L->A[i].chave; i--)
		L->A[i + 1] = L->A[i];
    
	L->A[i + 1] = x;
	L->nelem++;
	return TRUE;
}

boolean Buscar_Nome(char *nome, lista *L, int *p) {
	int i;
	
	for (i = 1; i <= L->nelem; i++) {
		if (strcmp(L->A[i].info.nome, nome) == 0) {
			*p = i;
			return TRUE;
		}
	}
	return FALSE;
}

boolean Buscar_ord_Nome(char *nome, lista *L, int *p) {
	int esq = 1, dir = L->nelem, meio;
	
	while (esq <= dir) {
		meio = (esq + dir) / 2;
		if (strcmp(nome, L->A[meio].info.nome) == 0) {
			*p = meio;
			return TRUE;
		}
	
		if (strcmp(nome, L->A[meio].info.nome) < 0)
    		dir = meio - 1;
    	else
    		esq = meio + 1;
    }
	return FALSE;
}

boolean Buscar(tipo_chave x, lista *L, int *p) {
	/*Retorna true, se x ocorre na posição p. Se x ocorre mais de
	uma vez, retorna a posição da primeira ocorrência. Se x não
	ocorre, retorna false.
	Para listas NÃO-ORDENADAS*/

	if (!Vazia(L)) {
		int i = 1;
		
		while (i <= L->nelem){
		
			if (L->A[i].chave == x) {
				*p = i;
				return TRUE;
			}
        	i++;
    	}
	}
	return FALSE; // Retorna false se não encontrou
}

boolean Repetido(tipo_chave chave, lista *L) {
	int i;
	
	for (i = 0; i <= L->nelem; i++) {
		if (L->A[i].chave == chave)
    		return TRUE;
    }
	return FALSE;
}
//-------------------------------------------
