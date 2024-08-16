/*
Lucas Furriel Rodrigues
Pedro Benedicto de Melo Cardana
*/
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//main feita para testar a ordena��o dos elementos da lista por chave
int main(int argc, char *argv[]){
	lista *l = malloc(sizeof(lista));
	tipo_elem *x = malloc(sizeof(tipo_elem));
	int op = 1; //vari�vel para controlar inser��o de novos elementos
	int i = 1; 
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	while (op){
		printf("Digite a chave: ");
		scanf("%d", &x->chave);
		printf("Digite o nome: ");
		scanf(" %[^\n]s", x->info.nome);
		/*printf("Digite a idade: ");
		scanf("%d", &x->info.idade);
		printf("Digite a m�dia: ");
		scanf("%f", &x->info.media_final);*/ //
		x->info.idade = i;
		x->info.media_final = i;
		i++;

		if(Inserir_ord_ch(*x, l))
			printf("INSERIDO COM SUCESSO\n");
		else
			printf("ERRO AO INSERIR\n");

		printf("\nInserir novo? <1> SIM <0> N�O\n");
		scanf("%d", &op);

		if (l->nelem == MAX){
			printf("\nLIMITE DA FILA ALCAN�ADO\n");
			op = 0;
		}
	}

	Imprimir(l);

	int p;
	Busca_bin(9, l, &p);
	printf("Busca %d", p);

	return 0;
}
