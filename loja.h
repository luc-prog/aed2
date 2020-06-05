#ifndef LOJA_H_INCLUDED
#define LOJA_H_INCLUDED

#include "TADS.h"
#include "produto.h"

void primeiroCadastro(); // REALIZA O PRIMEIRO CADASTRO E DEPOIS CHAMA O LOGIN
void login(TListaP lp); // PROCEDIMENTO DE LOGIN
void menuAdmin(TListaP lp); // MENU DO ADMINISTRADOR
void mostrarFuncionarios(TListaP lp); // MOSTRA OS DADOS DO FUNCIONÁRIO(ID,CPF,NOME E SALÁRIO)
void editarFuncionario(TListaP &lp); // EDITA OS DADOS DO FUNCIONÁRIO
int salvar_dados(TListaP lp); // SALVA OS DADOS EM UM ARQUIVO
//void MenuFuncionario(TPilhaP pp); // MENU DO FUNCIONÁRIO
#endif // LOJA_H_INCLUDED
