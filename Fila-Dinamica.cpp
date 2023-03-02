/* 
   
   # FILA DINAMICA #

*/

// BIBLIOTECA UTILIZADAS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
// Controlador do tamanho

int tamanho = 0;	
int opc=0;	
// Estruturas

struct liga *inicio = NULL;
struct liga *fim_fila = NULL;

	struct liga{
	int dado;
	struct liga *prox;
};

void inser(int valor){
	setlocale(LC_ALL,"portuguese");
	struct liga *aux;
	aux = new(struct liga);
	aux->dado = valor;
	
		if(tamanho==0){
			inicio = aux;
			fim_fila = aux;
		}
		
		fim_fila->prox = aux;
		fim_fila = aux;
		aux->prox =  NULL;
		
		tamanho++;
		printf("\n Elemento inserido \n"); 
}

void exibir_fila(){
	setlocale(LC_ALL,"portuguese");
	struct liga *aux;
	
	if(inicio==NULL){
		printf("\t Fila VAZIA \n");
		return;
	}
	
	aux = inicio;
	
	while(aux!=NULL){
		printf(" %d |", aux->dado);
		aux = aux->prox;
	}
	printf("\n");
}
	
void remover(){
	setlocale(LC_ALL,"portuguese");
	struct liga *aux;
	
	if(inicio==NULL){
		printf("\t Fila VAZIA \n");
		return;
	}
	aux = inicio;
	printf("O Valor removido foi %d", inicio->dado);
	inicio = inicio->prox;
	delete(aux);
	tamanho--;
	printf("\n Elemento removido com sucesso\n");
	
}
int saida(){
	return 0;
}
void menu(){
	system("cls");
	setlocale(LC_ALL,"portuguese");
	printf("--------------------------------------------\n");
	printf("|-------------- Menu da FILA ---------------\n");
	printf("|------ [1] --- INSERIR ELEMENTO -----------\n");
	printf("|------ [2] --- REMOVER ELEMENTO -----------\n");
	printf("|------ [3] --- EXIBIR ELEMENTOS -----------\n");
	printf("|------ [4] --- SAIR DO PROGRAMA -----------\n");
	printf("|------ Digite sua opção: ");
	scanf("%d", &opc);
}
main(){
	int valor;
	do{
	menu();
	switch(opc)
	{
	case 1:
		printf("Insira o valor a ser inserido: ");
		scanf("%d", &valor);
		inser(valor);
		break;
	case 2:
		remover();
		break;
	case 3:
		exibir_fila();
		break;
	case 4:
		printf("SAINDO DO PROGRAMA......");
		saida();
		break;
	default:
		printf("Opção invalida");
		break;
	}
	system("pause");
	}while(opc!=4);
}
