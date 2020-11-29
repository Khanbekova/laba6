#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <iostream>
#include <time.h>
using namespace std;
typedef int tData;
typedef struct sNode {
	tData value;
	struct sNode *next;
} tNode;
tNode* create_list(int N, int k, int **A, int i)
{
	tNode *p_begin = NULL;
	tNode *p = NULL;
	//заполним односвязный список
	p_begin = (tNode *)malloc(sizeof(tNode));
	p = p_begin;
	p->next = NULL;
	p->value = i + 1;
	for (int x = 0; x < N; x++) {
		if (A[i][x]) {
			p->next = (tNode *)malloc(sizeof(tNode));
			p = p->next;
			//заполнить _новую_ структуру данных
			p->next = NULL;
			p->value = x + 1;
		}
	}
	return p_begin;
}

void print_list(tNode *p_begin)
{
	tNode *p = p_begin;
	while (p != NULL) {
		printf("-> %d ", p->value);
		p = p->next;
	}
}
tNode **p_begin;
void BFSSPISOK(int i, int *M) {
	queue <int> Q;
	Q.push(i);
	M[i] = 0;
	while (Q.empty() != true) {

		i = Q.front();
		tNode *p_b = p_begin[i];
		Q.pop();
		while (p_b->next != NULL) {
			int j = p_b->next->value - 1;
			p_b = p_b->next;
			if (M[j] > M[i] + p_b->value) {
				M[j] = 0;
				Q.push(j);
				M[j]= M[i] +1;

			}
		}
	}
}
void OGVG(int **A, int N, int i,int*M) {
	int j;
	stack <int> S;
		if (M[i] == 1000) {
			M[i] = 0;
			S.push(i);
			do {
				i = S.top();
				j = 0;
				while (j < N) {
					if ((A[i][j] == 1) && (M[j] > M[i] + A[i][j])) {
						S.push(j);
						M[j] = 0;
						M[j] = M[i] + 1;
						i = j;
						j = 0;
					}
					else
						j++;
					}
				S.pop();
			} while (S.empty() != true);
		}
	
}
void OGVGSPISOK (int i, int *M) {
	if (M[i] == 1000) {
		M[i] = 0;
	}
	tNode *p_b = p_begin[i];
	while (p_b->next != NULL) {
		int j = p_b->next->value - 1;
		if (M[j] == 1000) {
			M[j] = 0;
			M[j] = M[i] + 1;
			OGVGSPISOK(j, M);
		}
		p_b = p_b->next;
	}

	
}

int BFS(int**A, int*M, int i, int N) {
	queue <int> Q;
	int j;
	Q.push(i);
	M[i] =0 ;
	while (Q.empty() != true) {
		i = Q.front();
		Q.pop();
		for (j = 0; j < N; j++) {
			if ((A[i][j] == 1) && (M[j] > M[i] + A[i][j])) {
				M[j] = 0;
				Q.push(j);
				M[j]= M[i] +1 ;
			}
		}
	}
	return 0;
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N, i, j;
	printf("Ведите размер матрицы \n");
	scanf_s("%d", &N);
	clock_t start, end;
	srand(11);
	int *M = (int*)malloc(N * sizeof(int));
	int **A = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		A[i] = (int *)malloc(N * sizeof(int));
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = rand() % 2;
			A[j][i] = A[i][j];
			if (i == j) {
				A[i][j] = 0;
			}
		}
	}
	/*for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}*/
	for (i = 0; i < N; i++) {
		M[i] = 1000;
	}
	printf("\n\nПоиск расстояний в ширину на матрице:\n"); 
	start = clock();
	for (i = 0; i < N; i++) {
		BFS(A, M, i, N);
		/*printf("\n");
		for (int l = 0; l < N; l++) {
			printf("%d ", M[l]);
		}*/
		for (int l = 0; l < N; l++) {
			M[l] = 1000;
		}
	}
	end = clock();
	printf("Время: %lf   \n", (float)(end - start) / CLOCKS_PER_SEC);
	//printf("\n\n Список :\n");

	p_begin = (tNode**)malloc(N * sizeof(tNode*));

	for (i = 0; i < N; i++) {
		int k = 0;
		for (j = 0; j < N; j++) {
			if (A[i][j] == 1)
				k++;

		}
		p_begin[i] = create_list(N, k, A, i);
		//print_list(p_begin[i]);
		//printf("\n");
	}
	for (i = 0; i < N; i++) {
		M[i] = 0;
	}
	printf("\n\nПоиск расстояний в ширину на списках:\n");
	

	for (i = 0; i < N; i++) {
		M[i] = 1000;
	}
	start = clock();
	for (i = 0; i < N; i++) {
		BFSSPISOK(i, M);
		/*printf("\n");
		for (int l = 0; l < N; l++) {
			printf("%d ", M[l]);
		}*/
		for (int l = 0; l < N; l++) {
			M[l] = 1000;
		}
	}
	end = clock();
	printf("Время: %lf   \n", (float)(end - start) / CLOCKS_PER_SEC);

	printf("\n\nПоиск путей в глубину матрицей:\n");
	
	for (i = 0; i < N; i++) {
		M[i] = 1000;
	}
	start = clock();
	for (i = 0; i < N; i++) {
		OGVG(A, N, i, M);
		/*printf("\n");
		for (int l = 0; l < N; l++) {
			printf("%d ", M[l]);
		}*/
		for (int l = 0; l < N; l++) {
			M[l] = 1000;
		}
	}
	end = clock();
	printf("Время: %lf   \n", (float)(end - start) / CLOCKS_PER_SEC);
	printf("\n\nПоиск путей в глубину списками:\n");
	
	for (i = 0; i < N; i++) {
		M[i] = 1000;
	}
	start = clock();
	for (i = 0; i < N; i++) {
		OGVGSPISOK(i, M);
		/*printf("\n");
		for (int l = 0; l < N; l++) {
			printf("%d ", M[l]);
		}*/
		for (int l = 0; l < N; l++) {
			M[l] = 1000;
		}
	}
	end = clock();
	printf("Время: %lf   \n", (float)(end - start) / CLOCKS_PER_SEC);
	free(A);
	free(M);
	free(p_begin);
	_getch();
}