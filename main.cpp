#include <stdio.h>
#include "ExtQuickSort.hpp"

struct Aluno
{
	int inscricao;
	double nota;
	char dados[85];
};

struct Pivo	// Pivo de lista encadeada
{
	Alu* aluno;
	Piv* ant;
	Piv* prox;
	int pos;
};

int main()
{
	FILE* ArqLs;
	FILE* ArqEs;
	FILE* ArqLi;
	FILE* ArqEi;
	Alu A;

	ArqLi = fopen("PROVAO.BIN", "r+b");
	if(ArqLi == NULL)
	{
		printf("Arquivo nao pode ser aberto.\n");
		return 1;
	} 
	ArqLs = fopen("PROVAO.BIN", "r+b");
	if(ArqLs == NULL)
	{
		printf("Arquivo nao pode ser aberto.\n");
		return 1;
	}
	ArqEi = fopen("PROVAO.BIN", "r+b");
	if(ArqEi == NULL)
	{
		printf("Arquivo nao pode ser aberto.\n");
		return 1;
	}
	ArqEs = fopen("PROVAO.BIN", "r+b");
	if(ArqEs == NULL)
	{
		printf("Arquivo nao pode ser aberto.\n");
		return 1;
	}

	QuickSortExterno(&ArqLi, &ArqEi, &ArqLs, &ArqEs, 1, 200);
	fflush(ArqLi);
	fclose(ArqEi);
	fclose(ArqLs);
	fclose(ArqEs);

	fseek(ArqLi, 0, SEEK_SET);

	while(fread(&A, sizeof(A), 1, ArqLi))
	{
		printf("Aluno: %lf\n", A.nota);
	}
	fclose(ArqLi);
	return 0;
}