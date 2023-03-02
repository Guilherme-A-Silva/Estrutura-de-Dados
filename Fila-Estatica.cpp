/* 
   
   # FILA DINAMICA #
    
*/

// Bibliotecas

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Variaveis globais

int top = 0, fila[10], back = 0, contador = 0;

//Função secundaria para inserção

int inserir(){
	system("cls");
	printf("Inserindo elemento na fila \n");
	contador = top+back;
	if(contador==10){
		printf("----------------------------");
		printf("\n \t | FILA CHEIA \t |\n");
		printf("----------------------------\n");
	}
	else if(top ==0){
		 top=1;
		printf("Informe o primeiro elemento a ser salvo: ");
		scanf("%d", & fila[0]);
	}
	else if( top!=0 &&  back<10){
		 back =  back+1;
		printf("Adicionando novos valores na fila \n");
		printf("Informe o valor a ser inserido: ");
		scanf("%d", & fila[ back]);
	}
}

// Função secundaria para remoção

int remover(){
	system("cls");
	char opc[3];
	printf("Tem certeza que deseja remover: [Sim / Não]  ");
	scanf("%s", &opc);
	if(strcmp(opc, "Sim")==0 || strcmp(opc, "sim")==0){
		 contador =  top+ back;
		for(int i=0; i< contador;i++){
			 fila[i] =  fila[i+1];  
		}
		back=back-1;
	}
}

//Função secundaria para exibição

int mostrar(){
	system("cls");
	int i;
	if(top==0 && back==0){
		printf("A Fila está vazia");
	}else{
		 contador=  top+ back;
		for(i=0; i< contador; i++){
			printf("%d - | %d \n", i+1, fila[i]);
		}
	}
}

// Função secundaria para saida

int sair(){
	system("cls");
	return 0;
}

// Função primaria

int main()
{
	int opc;
	do{
	printf("______________________________________ \n");
	printf("| -------------Menu----------------  |\n");
	printf("| [1] -  Insirir elementos  na fila  | \n");
	printf("| [2] -  Excluir elementos da fila   | \n");
	printf("| [3] -  Mostrar elementos da fila   |\n");
	printf("| [4] -  Sair do programa            |\n");
	printf("| Informe sua escolha: ");
	scanf("%d", &opc);
	
	(opc==1)? inserir(): (opc==2)? remover(): (opc==3)? mostrar():sair();
	}while(opc!=4);
}