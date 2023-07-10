/*
   
   10/07/2023 - Trabalho final de Introdução a ciência da computação - USP São Carlos 

   Created: Tiago Zero, José Carlos e Pietra Gullo 

   Documentação: 

*/

// codigos produtos -> 0, ... n -> atribuidos sequencialmente -> altera quando retira um cara (?)

// Inserir produto no mercado -> nome, qtd, preço (IP)

// aumentar o estoque -> codigo, qtd (AE) - um produto 



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
	long long int qtd ; 
	double price ; 

} ;

typedef struct Produto produto_t ; 

void IP(produto_t **produtos, long long int *tam, produto_t *atual) ;

void leia_produto(char **nome, long long int *qtd, double *price){

	char c ; 
	
	*nome = NULL ; 
	
	int i = 0 ; 

	scanf(" %c", &c) ; 

	for(; ; i++){ 
		//printf("%c", c) ; 
		if(c == ' ') break ; 
		*nome = (char *) realloc(*nome, (i+1)*sizeof(char)) ;
		(*nome)[i] = c ;
		scanf("%c", &c) ; 
	}

	i++ ; 

	*nome = (char *) realloc(*nome, (i+1)*sizeof(char)) ; 
	(*nome)[i] = '\0' ;

	scanf("%lld", qtd) ; scanf("%lf", price) ; 

}

void IP(produto_t **produtos, long long int *tam, produto_t *atual){

	(*tam)++ ; 
	(*produtos) = (produto_t *) realloc(*produtos, (*tam)*sizeof(produto_t)) ;

	((*produtos)[(*tam)-1]).nome = (char *) calloc(strlen(atual->nome), sizeof(char)) ; 

	strcpy(((*produtos)[(*tam)-1]).nome, atual->nome) ;   
	((*produtos)[(*tam)-1]).qtd = atual->qtd ; ((*produtos)[(*tam)-1]).price = atual->price ; 

}

// consultar estoque -> listar codigo nome, qtd de tudo (CE)
void consultaEstoque(produto_t **produtos, long long int *tam){
	for (int i = 0; i < (*tam); i++){
		printf("%lld %s %d\n", i, (*produtos)[i].nome, (*produtos)[i].qtd);
	}
	for(int i = 0; i < 50; i++) printf("-");
	printf("\n");
}

int main(){

	FILE *fp ; 

	long long int tamanho_estoque = 0 ; double saldo_vendas = 0.00 ; 

	produto_t *produtos ; 
	produtos = (produto_t*)calloc(1, sizeof(produto_t)); 

	if((fp = fopen("estoque.txt", "rb")) == NULL){ // primeiro dia 

		printf("null \n");		

			
		scanf("%lld", &tamanho_estoque) ; 
		tamanho_estoque = 0;
		scanf("%lf", &saldo_vendas) ;

	}

	else{
		printf("arquivo exiat \n");		



	    fscanf(fp, "%lld", &tamanho_estoque) ; 
		fscanf(fp, "%lf", &saldo_vendas) ; 

		produtos = (produto_t *) realloc(produtos, sizeof(produto_t)*tamanho_estoque) ; 

		printf("tamanho do estoque: %lld\n", tamanho_estoque);		

		fread(produtos, sizeof(produto_t), tamanho_estoque, fp) ; 

		remove("estoque.txt") ; 
		fflush(fp);

	}

	while(1){

		char tipo[3] ; scanf("%s", tipo) ; 

		if(!strcmp("FE", tipo)){

			if((fp = fopen("estoque.txt", "wb")) == NULL){
				printf("deu merda\n") ; 
				exit(1) ; 
			}

			fprintf(fp, "%lld ", tamanho_estoque) ;
			fprintf(fp, "%.2lf ", saldo_vendas) ; 

			fwrite(produtos, sizeof(produto_t), tamanho_estoque, fp) ; 

			fclose(fp) ; 

			break ; 

		}

		if(!strcmp("IP", tipo)){

			char *nome ; long long int qtd ; double price ; 
			leia_produto(&nome, &qtd, &price) ; 
			
			//printf("adicionei %s\n", nome) ; 

			produto_t atual ; atual.nome = NULL ;

			atual.nome = (char *) calloc(strlen(nome)+1, sizeof(char)) ;

			strcpy(atual.nome, nome) ;  

			atual.qtd = qtd ; atual.price = price ; 

			IP(&produtos, &tamanho_estoque, &atual) ; 

			printf("adicionei %s\n", nome) ; 

		}

	}

	// to do - desalocar as parada

}
