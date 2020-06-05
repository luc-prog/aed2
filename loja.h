#ifndef LOJA_H_INCLUDED
#define LOJA_H_INCLUDED

#include "TADS.h"
#include "produto.h"

void primeiroCadastro(); // REALIZA O PRIMEIRO CADASTRO E DEPOIS CHAMA O LOGIN
void login(TListaP lp); // PROCEDIMENTO DE LOGIN
void menuAdmin(TListaP lp); // MENU DO ADMINISTRADOR
void mostrarFuncionarios(TListaP lp); // MOSTRA OS DADOS DO FUNCION�RIO(ID,CPF,NOME E SAL�RIO)
void editarFuncionario(TListaP &lp); // EDITA OS DADOS DO FUNCION�RIO
int salvar_dados(TListaP lp); // SALVA OS DADOS EM UM ARQUIVO
//void MenuFuncionario(TPilhaP pp); // MENU DO FUNCION�RIO
#endif // LOJA_H_INCLUDED
