#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

#include <iostream>
#include <clocale>
#include <fstream>
#include <sstream>
#include "TADS.h"

using namespace std;

// TAD PARA OS PRODUTOS
struct TProduto{
    string nome,tipo;
    int chave,quantidade;
    double preco;
};

struct TNo{
    TNo *direita,*esquerda;
    TProduto item;
};

struct TPilhaP;

void criarArvoreVazia(TNo *&no);
void menuProd(TNo *&no);
int lendoArq(TNo *&no, int quantTokens);
void Menu_Funcionario(TPilhaP pp);
int salvar(TPilhaP pp);
#endif // PRODUTO_H_INCLUDED

