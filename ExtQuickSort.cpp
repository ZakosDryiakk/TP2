#include "ExtQuickSort.hpp"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

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

void QuickSortExterno(FILE** ArqLi, FILE** ArqEi, FILE** ArqLs, FILE** ArqEs, int Esq, int Dir)
{
	int i, j;
	Piv pivo;
	if (Dir - Esq < 1) 
		return;

	Particao(ArqLi, ArqEi, ArqLs, ArqEs, &pivo, Esq, Dir, &i, &j);

	if(i - Esq < Dir -j)
	{
		QuickSortExterno(ArqLi, ArqEi, ArqLs, ArqEs, Esq, i);
		QuickSortExterno(ArqLi, ArqEi, ArqLs, ArqEs, j, Dir);
	}
	else
	{
		QuickSortExterno(ArqLi, ArqEi, ArqLs, ArqEs, j, Dir);
		QuickSortExterno(ArqLi, ArqEi, ArqLs, ArqEs, Esq, i);	
	}
}

void LeSup(FILE** ArqLs, Alu* ultLido, int* Ls, short* OndeLer)
{
	fseek(*ArqLs, (*Ls-1)*sizeof(Alu), SEEK_SET);
	fread(ultLido, sizeof(Alu) , 1, *ArqLs);
	(*Ls)--;
	*OndeLer = false;
}

void LeInf(FILE** ArqLi, Alu* ultLido, int* Li, short* OndeLer)
{
	fread(ultLido, sizeof(Alu), 1, *ArqLi);
	(*Li)++;
	*OndeLer = true;
}

void InserirPivo(Piv* pivo, Alu* ultLido, int* NRPivo)
{
	Piv novo;
	Piv* aux = new Piv;
	if(pivo->aluno == NULL)
	{
		pivo->aluno = ultLido;
		pivo->pos = 1;
		pivo->ant = NULL;
		pivo->prox = NULL;
		aux->aluno = pivo->aluno;
		aux->pos = pivo->pos;
		aux->ant = pivo->ant;
		aux->prox = pivo->prox;
	}
	else
	{
		aux->aluno = pivo->aluno;
		aux->pos = pivo->pos;
		aux->ant = pivo->ant;
		aux->prox = pivo->prox;
		while(ultLido->nota >= aux->aluno->nota && aux != NULL)
			aux = aux->prox;
	}
	
	novo.aluno = ultLido;
	novo.ant = aux->ant;
	novo.prox = aux;
	aux->ant = &novo;
	novo.pos = aux->pos;
	aux->pos++;

	*NRPivo++;
	delete aux;
}

void EscreveMax(FILE** ArqEs, Alu* A, int* Es)
{
	fseek(*ArqEs, (*Es-1)*sizeof(Alu), SEEK_SET);
	fwrite(&A, sizeof(Alu), 1, *ArqEs);
	(*Es)--;
}

void EscreveMin(FILE** ArqEi, Alu* A, int* Ei)
{
	fwrite(&A, sizeof(Alu), 1, *ArqEi);
	(*Ei)++;
}

void RetiraMax(Piv* pivo, Alu* A, int* NRPivo)
{
	Piv* aux = new Piv;
	aux->aluno = pivo->aluno;
	aux->pos = pivo->pos;
	aux->ant = pivo->ant;
	aux->prox = pivo->prox;

	while(aux->prox != NULL)
		aux = aux->prox;
	A = aux->aluno;
	aux->ant->prox = NULL;
	free(pivo);
	(*NRPivo)--;
}

void RetiraMin(Piv* pivo, Alu* A, int* NRPivo)
{
	Piv* aux = new Piv;
	aux->aluno = pivo->aluno;
	aux->pos = pivo->pos;
	aux->ant = pivo->ant;
	aux->prox = pivo->prox;

	A = aux->aluno;
	aux->prox->ant = NULL;
	free(pivo);
	(*NRPivo)--;
}

void Particao(FILE** ArqLi, FILE** ArqEi, FILE** ArqLs, FILE** ArqEs, Piv* pivo, int Esq, int Dir, int* i, int* j)
{
	int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRPivo = 0, Linf = INT_MIN, Lsup = INT_MAX;
	short OndeLer = true;
	Alu ultLido, A;
	fseek(*ArqLi, (Li-1)*sizeof(Alu), SEEK_SET);
	fseek(*ArqEi, (Ei-1)*sizeof(Alu), SEEK_SET);
	*i = Esq - 1;
	*j = Dir + 1;

	while(Ls >= Li)
	{
		if(NRPivo < 9) // Tamanho da memória principal, 10
		{
			if(OndeLer)
				LeSup(ArqLs, &ultLido, &Ls, &OndeLer);
			else
				LeInf(ArqLi, &ultLido, &Ls, &OndeLer);
			
			InserirPivo(pivo, &ultLido, &NRPivo);
			continue;
		}
		if(Ls == Es)
			LeSup(ArqLs, &ultLido, &Ls, &OndeLer);
		else if(Li == Ei)
			LeInf(ArqLi, &ultLido, &Ls, &OndeLer);
		else if(OndeLer)
			LeSup(ArqLs, &ultLido, &Ls, &OndeLer);
		else
			LeInf(ArqLi, &ultLido, &Ls, &OndeLer);

		if(ultLido.nota > Lsup)
		{
			*j = Es;
			EscreveMax(ArqEs, &ultLido, &Es);
			continue;
		}

		if(ultLido.nota < Linf)
		{
			*i = Ei;
			EscreveMin(ArqEi, &ultLido, &Ei);
			continue;
		}

		InserirPivo(pivo, &ultLido, &NRPivo);

		if(Ei - Esq < Dir - Es)
		{
			RetiraMin(pivo, &A, &NRPivo);
			EscreveMin(ArqEi, &A, &Ei);
			Linf = A.nota;
		}
		else
		{
			RetiraMax(pivo, &A, &NRPivo);
			EscreveMax(ArqEs, &A, &Es);
			Lsup = A.nota;
		}
	}

	while(Ei <= Es)
	{
		RetiraMin(pivo, &A, &NRPivo);
		EscreveMin(ArqEi, &A, &Ei);
	}
}