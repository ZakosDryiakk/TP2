#ifndef ExtQuickSort_hpp
#define ExtQuickSort_hpp

#include <stdio.h>

typedef struct Aluno Alu;

typedef struct Pivo Piv;

void QuickSortExterno(FILE**, FILE**, FILE**, FILE**, int, int);

void LeSup(FILE**, Alu*, int*, short*);
void LeInf(FILE**, Alu*, int*, short*);

void InserirPivo(Piv*, Alu*, int*);

void EscreveMax(FILE**, Alu*, int*);
void EscreveMin(FILE**, Alu*, int*);

void RetiraMax(Piv*, Alu*, int*);
void RetiraMin(Piv*, Alu*, int*);

void Particao(FILE**, FILE**, FILE**, FILE**, Piv*, int, int, int*, int*);

#endif