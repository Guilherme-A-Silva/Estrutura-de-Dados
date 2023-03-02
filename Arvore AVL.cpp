/*
	# PROTOTIPO DE ARVORE #
	1-> Inserção
	2-> Remoção
	3-> Ordenação
	4-> Busca
	5-> Excluir Arvore

*/

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

/*
	# Struct da Arvore
	     Explicação
*/

struct arvore
{
	int dado, balanciamento;
	struct arvore *direita, *esquerda;
};

/*
	Variaveis globais
*/
int altura = 0; // Contador de niveis da arvore;
int h; // Controlador de balanciamento;
int QtEle = 1; // Quantidade de elementos;
int Altura (struct arvore *raiz)
{
	if(raiz == NULL)
	{
		return -1;
	}
	else
	{
		int esq = Altura(raiz->esquerda);
		int dir = Altura(raiz->direita);
		if(esq > dir)
			return esq + 1;
		else
			return dir + 1;
	}
}

arvore* remover(arvore *raiz, int valor)
{
	if(raiz == NULL)
	{
		cout << "VALOR NAO ENCONTRADO!"<< endl;
		system("pause");
		return NULL;
	}
	else
	{
		if(raiz->dado == valor)
		{
			if(raiz->esquerda == NULL && raiz->direita == NULL)
			{
				free(raiz);
				cout << "ELEMENTO REMOVIDO: !"<<valor<< endl;
				return NULL;
			}
		}
		else
		{
			if(valor < raiz->dado)
				raiz->esquerda = remover(raiz->esquerda, valor);
			else
				raiz->direita = remover(raiz->direita, valor);
			return raiz;
		}
	}
}

void Pre_ordem(struct arvore *raiz)
{
	cout << " "<< raiz->dado;
	if(raiz->esquerda != NULL)
		Pre_ordem(raiz->esquerda);
	if(raiz->direita != NULL)
		Pre_ordem(raiz->direita);
}

void Pos_ordem(struct arvore *raiz)
{
	if(raiz->esquerda != NULL)
		Pos_ordem(raiz->esquerda);
	if(raiz->direita != NULL)
		Pos_ordem(raiz->direita);
	cout << " "<< raiz->dado;
}

void Em_ordem(struct arvore *raiz)
{
	if(raiz->esquerda != NULL)
		Em_ordem(raiz->esquerda);
	cout << " "<< raiz->dado;
	if(raiz->direita != NULL)
		Em_ordem(raiz->direita);
}

struct arvore *Caso_1(struct arvore *raiz)
{
	struct arvore *DesBaEsq, *DesBaDir;
	DesBaEsq = raiz->esquerda;
	if(DesBaEsq->balanciamento == -1)
	{
		raiz->esquerda = DesBaEsq->direita;
		DesBaEsq->direita = raiz;
		raiz->balanciamento = 0;
		raiz = DesBaEsq;
	}
	else
	{
		DesBaDir = DesBaEsq->direita;
		DesBaEsq->direita = DesBaDir->esquerda;
		DesBaDir->esquerda = DesBaEsq;
		raiz->esquerda = DesBaDir->direita;
		DesBaDir->direita = raiz;
		if(DesBaDir->balanciamento == -1)
			raiz->balanciamento = 1;
		else
			raiz->balanciamento = 0;
		if(DesBaDir->balanciamento == 1)
			DesBaEsq->balanciamento = -1;
		else
			DesBaEsq->balanciamento = 0;
		raiz = DesBaDir;
	}
	raiz->balanciamento = 0;
	h = 1;
	return(raiz);
}

struct arvore *Caso_2(struct arvore *raiz)
{
	struct arvore *DesBaEsq, *DesBaDir;
	DesBaEsq = raiz->direita;
	if(DesBaEsq->balanciamento == 1)
	{
		raiz->direita = DesBaEsq->esquerda;
		DesBaEsq->esquerda = raiz;
		raiz->balanciamento = 0;
		raiz = DesBaEsq;
	}
	else
	{
		DesBaDir = DesBaEsq->esquerda;
		DesBaEsq->esquerda = DesBaDir->direita;
		DesBaDir->direita = DesBaEsq;
		raiz->direita = DesBaDir->esquerda;
		DesBaDir->esquerda = raiz;
		if(DesBaDir->balanciamento == 1)
			raiz->balanciamento = -1;
		else
			raiz->balanciamento = 0;
		if(DesBaDir->balanciamento == -1)
			DesBaEsq->balanciamento = 1;
		else
			DesBaEsq->balanciamento = 0;
		raiz = DesBaDir;
	}
	raiz->balanciamento = 0;
	h = 1;
	return(raiz);
}

void QtElementos(struct arvore *raiz, int dado)
{
	if(dado == raiz->dado)
	{
		system("pause");
	}
	else
		QtEle += 1;
}

struct arvore *inserir(struct arvore *raiz, int dado)
{
	if(raiz == NULL)
	{
		raiz = (struct arvore *) malloc(sizeof(struct arvore));
		raiz->dado = dado;
		raiz->esquerda = NULL;
		raiz->direita = NULL;
		raiz->balanciamento = 0;
		h = 0;
	}
	else if(dado == raiz->dado)
	{
		cout << endl << "ELEMENTO JA EXISTE" << endl;
		system("pause");
	}

	else if(dado < raiz->dado)
	{
		raiz->esquerda = inserir(raiz->esquerda, dado);
		if(h == 0)
		{
			switch(raiz->balanciamento)
			{
			case 1:
				raiz->balanciamento = 0;
				h = 1;
				break;
			case 0:
				raiz->balanciamento = -1;
				break;
			case -1:
				raiz = Caso_1(raiz);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		raiz->direita = inserir(raiz->direita, dado);
		if(h == 0)
		{
			switch(raiz->balanciamento)
			{
			case -1:
				raiz->balanciamento = 0;
				h = 1;
				break;
			case 0:
				raiz->balanciamento = 1;
				break;
			case 1:
				raiz = Caso_2(raiz);
				break;
			}
		}
		return (raiz);
	}
}
int main()
{
	struct arvore *raiz = NULL;
	int NovoDado, opcao = 0;

	while(opcao != 8)
	{
		system("cls");
		cout << "|-------------------------------------------|" << endl;
		cout << "|--- MENU DE OPERACOES DE ARVORE BINARIA ---|" << endl;
		cout << "|-------------------------------------------|" << endl;
		cout << "| [1] -> Inserir                            |" << endl;
		cout << "| [2] -> Remover                            |" << endl;
		cout << "| [3] -> Percurso em Pre Ordem              |" << endl;
		cout << "| [4] -> Percurso em Ordem Simetrica        |" << endl;
		cout << "| [5] -> Percurso em pos Ordem              |" << endl;
		cout << "| [6] -> Altura da arvore                   |" << endl;
		cout << "| [7] -> Quantidade de elementos            |" << endl;
		cout << "| [8] ->              Sair                  |" << endl;
		cout << "|-------------------------------------------|" << endl;
		cout << "             Digite sua opcao: ";
		cin >> opcao;
		switch(opcao)
		{
		case 1:
			cout << "QUAL O ELEMENTO A SER INSERIDO?";
			cin >> NovoDado;
			raiz = inserir(raiz, NovoDado);
			QtElementos(raiz, NovoDado);
			break;
		case 2:
			cout << "QUAL O ELEMENTO A SER REMOVIDO?";
			cin >> NovoDado;
			remover(raiz, NovoDado);
			break;
		case 3:
			if(raiz == NULL)
				cout << "ARVORE NAO EXISTE!";
			else
				Pre_ordem(raiz);
			break;
		case 4:
			if(raiz == NULL)
				cout << "ARVORE NAO EXISTE!";
			else
				Pos_ordem(raiz);
			cout<<endl;
			system("pause");
			break;
		case 5:
			if(raiz == NULL)
				cout << "ARVORE NAO EXISTE!";
			else
				Em_ordem(raiz);
			system("pause");
			break;
		case 6:
			if(raiz == NULL)
				cout << "NAO EXISTE NIVEL                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ";
			else
				altura = Altura(raiz);
			cout << " " << altura;
			altura = NULL;
			system("pause");
			break;
		case 7:
			if(raiz == NULL)
				cout << "ARVORE NAO EXISTE!";
			else if(raiz != NULL)
				cout << "Quantidade de elementos: " << QtEle<< endl;
			system("pause");
			break;
		case 8:
			break;
		default:
			cout << "Opcao Invalida" << endl;
			system("pause");
			break;
		}
	}
}