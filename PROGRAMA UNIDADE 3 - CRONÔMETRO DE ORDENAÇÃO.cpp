/*___________________________________________________________
 |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
 |	                                                         |
 |			ESTRUTURA DE DADOS                               |
 |														     |
 |			PROGRAMA DE ORDENAÇÃO                            |
 |			CRONÔMETRO DE DURAÇÃO DE CADA ORDENAÇÃO          |
 |														     |
 |			ALUNOS: ANTONIO JAILSON DA SILVA SEGUNDO	     |
 |					GUILHERME AUGUSTO SILVA				     |
 |					SAMUEL VITOR DE OLIVEIRA GALDINO	     |
 | _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
 */


#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define GT 100000

using namespace std;
int V[100000];   //  Array inicial
int V2[100000];  // Copia da Array
int Qt = 0;      // Controlador do Gerador
int Qt2 = 0;     // Controlador do Copiador
int controle = -1;
double InicioQuick, ParadaQuick, TempoQuick;
double InicioMerge, ParadaMerge, TempoMerge;
double InicioHeap, ParadaHeap, TempoHeap;
// Prototipação de funções

void  SelectionSort(int TAM);
void BubbleSort(int TAM);
void InsertionSort(int TAM);
void QuickSort(int V[], int ini, int TAM);
void TrocaMerge(int[], int, int, int);
void MergeSort(int V[], int ini, int TAM);
void ShellSort(int V[], int TAM);
void AmontoarHeap(int V[], int TAM, int raiz);
void HeapSort(int V[], int TAM);

void troca(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Copiador()
{
	while(Qt2 != GT)
	{
		V2[Qt2] = V[Qt2];
		Qt2++;
	}
}

void Gerador()
{
	srand(time(NULL));
	while(Qt != GT)
	{
		V[Qt] = rand() % GT;
		Qt++;
	}
	Copiador();
	cout << " Valores gerados com sucesso ";
	Sleep(1000);
}
void SelectionSort(int TAM)
{
	int i, j;
	int menor;
	double inicio, parada, tempo;
	inicio = (double) clock() / CLOCKS_PER_SEC; //inicio do cronometro

    for (i = 0; i < TAM-1; i++)
    {

        menor = i;
        for (j = i+1; j < TAM; j++)
        if (V[j] < V[menor])
            menor = j;
        
        if(menor!=i)
            troca(V[menor], V[i]);
    }
	cout << " Vetor Ordenado " << endl;
	parada = (double) clock() / CLOCKS_PER_SEC; //parada do cronometro
	tempo = parada - inicio;                    //cálculo da duração
	cout << " Tempo de Ordenação: " << tempo;
	Sleep(2000);
	for(int i = 0; i < TAM; i++)
	{
		V[i] = V2[i];
	}
}

void BubbleSort(int TAM)
{
	double InicioBubble, ParadaBubble, TempoBubble;
	InicioBubble = (double) clock() / CLOCKS_PER_SEC;
	int temp, i, j;
	for(i = 0; i < TAM; i++)
	{
		for(j = i + 1; j < TAM; j++)
		{
			if(V[j] < V[i])
			{
				temp = V[i];
				V[i] = V[j];
				V[j] = temp;
			}
		}
	}
	cout << " Vetor Ordenado " << endl;
	ParadaBubble = (double) clock() / CLOCKS_PER_SEC;
	TempoBubble = ParadaBubble - InicioBubble;
	cout << " Tempo de Ordenação: " << TempoBubble;
	Sleep(2000);
	for(int i = 0; i < TAM; i++)
	{
		V[i] = V2[i];
	}
}

void InsertionSort(int TAM)
{
	double InicioInsertion, ParadaInsertion, TempoInsertion;
	InicioInsertion = (double) clock() / CLOCKS_PER_SEC;
	for(int i = 1; i < TAM; i++)
	{
		int temp = V[i];
		int j = i - 1;
		while(j >= 0 && temp <= V[j])
		{
			V[j + 1] = V[j];
			j = j - 1;
		}
		V[j + 1] = temp;
	}
	ParadaInsertion = (double) clock() / CLOCKS_PER_SEC;
	TempoInsertion = ParadaInsertion - InicioInsertion;
	cout << " Tempo de Ordenação: " << TempoInsertion;
	Sleep(2000);
	for(int i = 0; i < TAM; i++)
	{
		V[i] = V2[i];
	}
}

int divisaoquick(int V[], int ini, int TAM)
{
	int pivo = V[TAM];    // pivô
	int i = (ini - 1);

	for (int j = ini; j <= TAM - 1; j++)
	{
		//se elemento atual for menor que pivo, incrementa o elemento ini
		//troca elementos em i e j
		if (V[j] <= pivo)
		{
			i++;    // incremento do índice do menor elemento
			troca(V[i], V[j]);
		}
	}
	troca(V[i + 1], V[TAM]);
	return (i + 1);
}


void QuickSort(int V[], int ini, int TAM)
{
	if (ini < TAM)
	{
		//divisão do vetor
		int pivo = divisaoquick(V, ini, TAM);

		//ordena os sub vetores independentemente
		QuickSort(V, ini, pivo - 1);
		QuickSort(V, pivo + 1, TAM);
	}

	controle = 1;
}
void MergeSort(int V[], int ini, int TAM)
{
	int meio;
	if (ini < TAM)
	{
		//divide o vetor no meio e ordena independentemente usando merge sort
		meio = (ini + TAM) / 2;
		MergeSort(V, ini, meio);
		MergeSort(V, meio + 1, TAM);
		//vetor ordenado por merge ou conquista
		TrocaMerge(V, ini, TAM, meio);
	}
	controle = 2;
}
void TrocaMerge(int V[], int ini, int TAM, int meio)
{
	int i, j, k, c[TAM];
	i = ini;
	k = ini;
	j = meio + 1;
	while (i <= meio && j <= TAM)
	{
		if (V[i] < V[j])
		{
			c[k] = V[i];
			k++;
			i++;
		}
		else
		{
			c[k] = V[j];
			k++;
			j++;
		}
	}
	while (i <= meio)
	{
		c[k] = V[i];
		k++;
		i++;
	}
	while (j <= TAM)
	{
		c[k] = V[j];
		k++;
		j++;
	}
	for (i = ini; i < k; i++)
	{
		V[i] = c[i];
	}

}
void ShellSort(int V[], int TAM)
{
	double InicioShell, ParadaShell, TempoShell;
	InicioShell = (double) clock() / CLOCKS_PER_SEC;
	for (int vao = TAM / 2; vao > 0; vao /= 2)
	{
		for (int i = vao; i < TAM; i += 1)
		{
			//ordena sub listas criadas aplicando o vão
			int temp = V[i];

			int j;
			for (j = i; j >= vao && V[j - vao] > temp; j -= vao)
				V[j] = V[j - vao];

			V[j] = temp;
		}
	}
	cout << " Vetor Ordenado " << endl;
	ParadaShell = (double) clock() / CLOCKS_PER_SEC;
	TempoShell = ParadaShell - InicioShell;
	cout << " Tempo de Ordenação: " << TempoShell;
	Sleep(2000);
	for(int i = 0; i < TAM; i++)
	{
		V[i] = V2[i];
	}
}
void AmontoarHeap(int V[], int TAM, int raiz)
{
	int maior = raiz; // raiz é o maior elemento
	int esq = 2 * raiz + 1; // esquerda = 2*raiz + 1
	int dir = 2 * raiz + 2; // direita = 2*raiz + 2

	// Se o filho esq é maior que raiz
	if (esq < TAM && V[esq] > V[maior])
		maior = esq;

	// Se o filho dir é maior que o maior até o momento
	if (dir < TAM && V[dir] > V[maior])
		maior = dir;

	// Se maior não é raiz
	if (maior != raiz)
	{
		//troca raiz e maior
		troca(V[raiz], V[maior]);

		// Recursividade em AmontoarHeap na sub-arvore
		AmontoarHeap(V, TAM, maior);
	}
}
void HeapSort(int V[], int TAM)
{

	// construindo o monte/pilha
	for (int i = TAM / 2 - 1; i >= 0; i--)
		AmontoarHeap(V, TAM, i);

	// extraindo elementos do monte/pilha um por um
	for (int i = TAM - 1; i >= 0; i--)
	{
		// Move raiz atual para o fim
		troca(V[0], V[i]);

		// chama novamente AmontoarHeap no monte/pilha reduzido
		AmontoarHeap(V, i, 0);
	}
	controle = 3;
}
int main()
{
	int control;

	do
	{
		if(controle == 1)
		{
			cout << " Vetor Ordenado " << endl;
			ParadaQuick = (double) clock() / CLOCKS_PER_SEC;
			TempoQuick = ParadaQuick - InicioQuick;
			cout << " Tempo de Ordenação: " << TempoQuick;
			Sleep(2000);
			controle = -1;
			for(int i = 0; i < GT; i++)
			{
				V[i] = V2[i];
			}
		}
		if(controle == 2)
		{
			cout << " Vetor Ordenado " << endl;
			ParadaMerge = (double) clock() / CLOCKS_PER_SEC;
			TempoMerge = ParadaMerge - InicioMerge;
			cout << " Tempo de Ordenação: " << TempoMerge;
			Sleep(2000);
			controle = -1;
			for(int i = 0; i < GT; i++)
			{
				V[i] = V2[i];
			}
		}
		if(controle == 3)
		{
			cout << " Vetor Ordenado " << endl;
			ParadaHeap = (double) clock() / CLOCKS_PER_SEC;
			TempoHeap = ParadaHeap - InicioHeap;
			cout << " Tempo de Ordenação: " << TempoHeap;
			Sleep(2000);
			controle = -1;
			for(int i = 0; i < GT; i++)
			{
				V[i] = V2[i];
			}
		}


		system("cls");
		cout << "| - - - - - - - - - - - - - - - - - |" << endl;
		cout << "|        Menu de Interação          |" << endl;
		cout << "| - - - - - - - - - - - - - - - - - |" << endl;
		cout << "| [1] -> Gerador de Cem Mil Valores |" << endl;
		cout << "| [2] -> Selection Sort             |" << endl;
		cout << "| [3] -> BubbleSort                 |" << endl;
		cout << "| [4] -> Insertion Sort             |" << endl;
		cout << "| [5] -> Quick Sort                 |" << endl;
		cout << "| [6] -> Merge Sort                 |" << endl;
		cout << "| [7] -> Shell Sort                 |" << endl;
		cout << "| [8] -> Heap Sort                  |" << endl;
		cout << "| [9] -> Finalizar Programa         |" << endl;
		cout << "| - - - - - - - - - - - - - - - - - |" << endl;
		cout << "| Digite a opção que deseja: ";
		cin >> control;

		switch(control)
		{
		case 1:
			Gerador();
			for(int i = 0; i < 15; i++)
			{
				cout << " " << V[i] << endl;

			}
			Sleep(4000);
			break;
		case 2:
			cout << " Ordenando vetor... ";
			SelectionSort(GT);

			break;
		case 3:
			cout << " Ordenando vetor... ";
			BubbleSort(GT);
			break;
		case 4:
			cout << " Ordenando vetor... ";
			InsertionSort(GT);
			break;
		case 5:
			cout << " Ordenando vetor... ";
			InicioQuick = (double) clock() / CLOCKS_PER_SEC;
			QuickSort(V, 0, GT);
			break;
		case 6:
			cout << " Ordenando vetor... ";
			InicioMerge = (double) clock() / CLOCKS_PER_SEC;
			MergeSort(V, 0, GT);
			break;
		case 7:
			cout << " Ordenando vetor... ";
			ShellSort(V, GT);
			break;
		case 8:
			cout << " Ordenando vetor... ";
			InicioHeap = (double) clock() / CLOCKS_PER_SEC;
			HeapSort(V, GT);
			break;
		case 9:
			cout << "\n PROGRAMA FINALIZADO";
			break;
		default:
			cout << "\n OPÇÃO INVÁLIDA";
			break;
		}
	}
	while(control != 9);
}
