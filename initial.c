/*
   
   10/07/2023 - Trabalho final de Introdução a ciência da computação - USP São Carlos 

   Created: Tiago Zero, José Carlos e Pietra Gullo 

   Documentação: 

*/

// codigos produtos -> 0, ... n -> atribuidos sequencialmente -> altera quando retira um cara (?)

// Inserir produto no mercado -> nome, qtd, preço (IP)

// aumentar o estoque -> codigo, qtd (AE) - um produto 

// modificar preço -> codigo e novo preço (MP)

// venda -> codigo DOS produtoS -> deve imprimir os nomes, preços e o total (VE)

// consultar estoque -> listar codigo nome, qtd de tudo (CE)

// consultar saldo -> imprime saldo (CS)

// finalizar dia -> gravar infos num arquivo (FE) 

// inicio: ler arquivo do dia anterior p salvar as infos do estoque no começo 

// saldo -> inicial + vendas 

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

struct Produto{
	
	char *nome ;
	int qtd ; 
	double price ; 

} ;

typedef struct Produto p ; 

void leia_produto(char **nome, int *qtd, double *price){

	char c ; 
	
	*nome = NULL ; 
	
	int i = 0 ; 

	for(; ; i++){
		scanf("%c", c) ; 
		if(c == ' ') break ; 
		*nome = realloc(*nome, (i+1)*sizeof(char)) ;
		nome[i] = c ; 
	}

	*nome = realloc(*nome, (i+1)*sizeof(char)) ; 
	nome[i] = '\0' ;

	scanf("%d", *qtd) ; scanf("%lf", *price) ; 

}

void IP(){

}

int main(){

	FILE *fp ; 

	int tamanho_estoque = 0 ; double saldo_vendas = 0.00 ; 

	if((fp = fopen("estoque.txt", "r")) == NULL){ // primeiro dia 
		
		scanf("%d", &tamanho_estoque) ; 
		scanf("%lf", &saldo_vendas) ;

	}

}
