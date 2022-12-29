#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <locale.h>
#include <queue>
using namespace std;

void adj(int** G, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				G[i][j] = 0;
			}
			if (i < j) {
				if (rand() % 100 > 50) {
					G[i][j] = rand() % 15;
				}
				else {
					G[i][j] = 0;
				}
				G[j][i] = G[i][j];
			}
		}
	}
}

void print_adj(int** G, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void BFSD(int s, int** G, int* dist, int n) {
	queue <int> q;
	q.push(s);
	dist[s] = 0;
	while (!q.empty()) {
		s = q.front();
		q.pop();
		printf("%d ", s);
		for (int i = 0; i < n; i++) {
			if ((G[s][i] != 0) && (dist[i] == 1000)) {
				q.push(i);
				dist[i] = dist[s] + G[s][i];
			}
		}
	}
	printf("\n");
}

int main() {
	int** G;	// ��������� �� ��������� �� ������ ���������
	int* ex;	// ��������������
	int* dist, *step;
	int i, j, n, max = 0, min = 0;


	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	printf("������� ������ �����: ");
	scanf("%d", &n);
	printf("\n");

	G = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		G[i] = (int*)malloc(n * sizeof(int));
	}
	dist = (int*)malloc(n * sizeof(int));
	ex = (int*)malloc(n * sizeof(int));
	step = (int*)malloc(n * sizeof(int));

	printf("����������������� ���������� ���� \n");
	adj(G, n);
	print_adj(G, n);

	for (i = 0; i < n; i++) {
		max = -1;

		for (j = 0; j < n; j++) {
			dist[j] = 1000;
		}

		printf("�� ������� %d: ", i);
		BFSD(i, G, dist, n);
		for ( j = 0; j < n; j++)
		{
			if (dist[j] != 1000) {
				printf("%d\t", dist[j]);
				if (dist[j] > max)
					max = dist[j];
			}
			else
				printf("��� �������\t");
		}
		ex[i] = max;
		printf("\n\n");
	}

	printf("��������������� �����: ");
	for (i = 0; i < n; i++) {
		printf("%d ", ex[i]);
	}

	min = ex[0];
	max = ex[0];
	for (i = 0; i < n; i++) {
		if (ex[i] > max)
			max = ex[i];
		if (ex[i] < min)
			min = ex[i];
	}
	printf("\n������� �����: %d\t", max);
	printf("\n");
	printf("������ �����: %d\n\n", min);

	printf("������������ �������: ");
	for (i = 0; i < n; i++) {
		if (ex[i] == max) {
			printf("%d\t", i);
		}
	}
	printf("\n����������� �������: ");
	for (i = 0; i < n; i++) {
		if (ex[i] == min) {
			printf("%d\t", i);
		}
	}
	printf("\n");

	
	for (int i = 0; i < n; i++) {
		step[i] = 0;
		for (int j = 0; j < n; j++) {
			if (G[i][j] != 0)
				step[i]++;
		}
		switch (step[i]) {
		case 0: printf("������� %d ������������\n", i);
			break;
		case 1:printf("������� %d ��������\n", i );
			break;
		default:
			if (step[i] == n-1)
				printf("������� %d ������������\n", i );
		}
	}

	for (i = 0; i < n; i++) {
		free(G[i]);
	}
	free(G);
	free(ex);
	free(dist);
	free(step);

	getchar();
	getchar();
}