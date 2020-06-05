#ifndef TADS_H_INCLUDED
#define TADS_H_INCLUDED

#include <iostream>
#include "produto.h"

using namespace std;

// STRUCTS
struct Tusuario{
    string nome, cpf, senha;
    int id;
    double salario;
};

struct TCelula{
    Tusuario usuario;
    TCelula *proximo;
};

struct TCliente{
    string nome, cpf, prodComprado;
    int id, quantidade;
    double precoPagar;
};

struct TCelulaCliente{
    TCliente cliente;
    TCelulaCliente *proximo;
};

struct TListaP{
    TCelula *primeiro, *ultimo;
    int contItens;
};

struct TPilhaP{
    TCelulaCliente *fundo, *topo;
    int contItens;
};

//||========> TAD LISTA <=========||
void criarListaVazia(TListaP &lp);
bool verifListaVazia(TListaP lp);
void inserir(TListaP &lp, Tusuario usuario);
void mostrar(TListaP lp);
TCelula *pegaAnteriorF(TListaP lp, int chave);
void retirar(TListaP &lp, int chave);

//||=====> TAD PILHA <=====||
void criarPilhaVazia(TPilhaP &pp);
bool verifPilhaVazia(TPilhaP pp);
void empilhar(TPilhaP &pp, TCliente c);
void mostrarPilha(TPilhaP pp);
#endif // TADS_H_INCLUDED
