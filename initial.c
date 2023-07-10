/*
   
   10/07/2023 - Trabalho final de Introdução a ciência da computação - USP São Carlos 

   Created: Tiago Zero, José Carlos e Pietra Gullo 

   Documentação: 

*/

// venda -> codigo DOS produtoS -> deve imprimir os nomes, preços e o total (VE)

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

struct Produto{
	
	char *nome ;
	long long int qtd ; 
	double price ; 

} ;

typedef struct Produto produto_t ; 

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


// Inserir produto no mercado -> nome, qtd, preço (IP)

void IP(produto_t **produtos, long long int *tam, produto_t *atual){

	(*tam)++ ; 
	(*produtos) = (produto_t *) realloc(*produtos, (*tam)*sizeof(produto_t)) ;

	((*produtos)[(*tam)-1]).nome = (char *) calloc(strlen(atual->nome), sizeof(char)) ; 

	strcpy(((*produtos)[(*tam)-1]).nome, atual->nome) ;   
	((*produtos)[(*tam)-1]).qtd = atual->qtd ; ((*produtos)[(*tam)-1]).price = atual->price ; 

}

// aumentar o estoque -> codigo, qtd (AE) - um produto 

void AE(produto_t *produtos, long long int code, long long int qtd){ produtos[code].qtd += qtd ; }

// modificar preço -> codigo e novo preço (MP)

void MP(produto_t *produtos, long long int code, double price){ produtos[code].price = price ; }

// consultar saldo -> imprime saldo (CS)

void CS(double saldo){
	
	printf("%.2lf\n", saldo) ;
	
	for(int i = 1 ; i <= 50 ; i++) printf("-") ; 
	printf("\n") ; 

}

// consultar estoque -> listar codigo nome, qtd de tudo (CE)

void CE(produto_t *produtos, long long int tam){
	
	for (int i = 0; i < tam; i++){
		printf("%d %s %lld\n", i, produtos[i].nome, produtos[i].qtd);
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

		printf("n tenho arquivo\n") ; 
		scanf("%lld", &tamanho_estoque) ; 
		tamanho_estoque = 0;
		scanf("%lf", &saldo_vendas) ;

	}

	else{

		printf("tenho arquivo\n") ; 

	    fscanf(fp, "%lld", &tamanho_estoque) ; 	
		fscanf(fp, "%lf", &saldo_vendas) ; 

		produtos = (produto_t *) realloc(produtos, sizeof(produto_t)*tamanho_estoque) ; 

		printf("tamanho do estoque: %lld\n", tamanho_estoque);		

		fread(produtos, sizeof(produto_t), tamanho_estoque, fp) ; 

	}

	while(1){

		char tipo[3] ; scanf("%s", tipo) ; 

		if(!strcmp("FE", tipo)){

			if((fp = fopen("estoque.txt", "wb")) == NULL){
				printf("deu merda\n") ; 
				exit(1) ; 
			}


            // finalizar dia -> gravar infos num arquivo (FE) 
			fprintf(fp, "%lld\n", tamanho_estoque) ;
			fprintf(fp, "%lf\n", saldo_vendas) ; 

			fwrite(produtos, sizeof(produto_t), tamanho_estoque, fp) ;

			fclose(fp) ; 

			break ; 

		}

		else if(!strcmp("IP", tipo)){

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

		else if(!strcmp("AE", tipo)){
			long long int code, qtd ; scanf("%lld %lld", &code, &qtd) ; 
			AE(produtos, code, qtd) ; 
		}

		else if(!strcmp("MP", tipo)){
			long long int code ; double price ; scanf("%lld %lf", &code, &price) ;
			MP(produtos, code, price) ;  
		}

		else if(!strcmp("CS", tipo)) CS(saldo_vendas) ;

		else if(!strcmp("CE", tipo)) CE(produtos, tamanho_estoque) ;

	}

	// to do - desalocar as parada

}
