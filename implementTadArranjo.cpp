#include "TADS.h"
#include <iomanip>


//================== TAD LISTA ==================//
void criarListaVazia(TListaP &lp){
    lp.primeiro = new TCelula;
    lp.ultimo = lp.primeiro;
    lp.primeiro->proximo = NULL;
    lp.contItens = 0;
}

bool verifListaVazia(TListaP lp){
    return lp.contItens == 0;
}

void inserir(TListaP &lp, Tusuario usuario){
    lp.ultimo->proximo = new TCelula;
    lp.ultimo = lp.ultimo->proximo;
    lp.ultimo->usuario = usuario;
    lp.ultimo->proximo = NULL;
    lp.contItens++;
}

void mostrar(TListaP lp){
    if(verifListaVazia(lp)){
        cout << "Nenhum funcionário cadastrado!" << endl;
    }
    else{
        TCelula *aux = lp.primeiro->proximo; // Apontando para a primeira célula válida
        int contFuncionarios = 1;
        while(aux != NULL){
            cout << "      ID: " << aux->usuario.id << " - " << aux->usuario.nome << " - CPF: " << aux->usuario.cpf << " - Salário: R$" << aux->usuario.salario << endl << endl;
            aux = aux->proximo;
            contFuncionarios++;
        }
    }
}

TCelula *pegaAnteriorF(TListaP lp, int chave){
    if(verifListaVazia(lp)){
        cout << "Não foi encontrado funcionários cadastrados!" << endl;
    }
    else{
        TCelula *aux = lp.primeiro;

        while(aux->proximo != NULL){
            if(chave == aux->proximo->usuario.id){
                system("pause");
                return aux;
            }
            aux = aux->proximo;
        }
    }

    return NULL;
}

void retirar(TListaP &lp, int chave){
    TCelula *aux = pegaAnteriorF(lp,chave);
    if(aux != NULL){
        TCelula *alvo = aux->proximo;
        aux->proximo = alvo->proximo;
        cout << alvo->usuario.nome << " foi removido!" << endl;
        delete(alvo);
        lp.contItens--;

    }
    else{
        cout << "Funcionário não encontrado!" << endl;
    }
}

//================== TAD PILHA ==================//

void criarPilhaVazia(TPilhaP &pp){
    pp.topo = new TCelulaCliente;
    pp.fundo = pp.topo;
    pp.fundo->proximo = NULL;
    pp.contItens = 0;
}

bool verifPilhaVazia(TPilhaP pp){
    return pp.contItens == 0;
}

void empilhar(TPilhaP &pp, TCliente c){
    TCelulaCliente *aux = new TCelulaCliente;
    pp.topo->cliente = c;
    aux->proximo = pp.topo;
    pp.topo = aux;
    pp.contItens++;
}

void mostrarPilha(TPilhaP pp){
    if (verifPilhaVazia(pp)){
        cout << "Nenhuma venda encontrada!" << endl;
    }
    else{
        TCelulaCliente *aux;
        aux = pp.topo->proximo;
        while (aux != NULL){
            cout << "     " << aux->cliente.id << " - Cliente: " << aux->cliente.nome << " - CPF: " << aux->cliente.cpf << endl;
            cout << "     Produto Comprado: " << aux->cliente.quantidade << "X " << aux->cliente.prodComprado << " - Preço: R$" << fixed << setprecision(2) << aux->cliente.precoPagar << endl << endl;
            aux = aux->proximo;
        }
    }
}

