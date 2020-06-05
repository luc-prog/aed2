#include "produto.h"
#include "iomanip"

void criarArvoreVazia(TNo *&no){//CRIANDO ARVORE VAZIA
    no = NULL;
}

int inserirArvore(TNo *&no, TProduto p){  //INSERÇÃO
    if(no == NULL){//CONDIÇÃO PARA INSERIR
        no = new TNo;
        no->item = p;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else{
        if(p.preco < no->item.preco && p.chave != no->item.chave){
            inserirArvore(no->esquerda,p);// ANDA PARA O LADO ESQUERDO DO NO VISITADO
        }
        else{
            if(p.preco >= no->item.preco && p.chave != no->item.chave){
                inserirArvore(no->direita,p); // ANDA PARA A DIREITA, CASO TER UM ELEMENTO COM PREÇO REPETIDO ESTE FICA NA DIREITA DESSE NO
            }
            else{
                if(p.chave == no->item.chave){
                    cout << "Não posso inserir. Item já existe!" << endl;
                    return -1;
                }
            }
        }
    }
    return 0;
}

int inserirArq(TProduto x){ // INSERE OS PRODUTOS NA .TXT
    int i;
    stringstream q,p,c;

    fstream arquivo("produtos.txt",ios::out|ios::in|ios::ate);

    if(arquivo.is_open()){
        arquivo << x.nome+";";
        arquivo << x.tipo+";";
        q << x.quantidade; // FUNÇOES PARA CONVERSÃO DO TIPO STRING
        arquivo << q.str()+";";
        p << x.preco;
        arquivo << p.str()+";";
        c << x.chave;
        arquivo << c.str()+"\n";
        arquivo.close();
        return 0;
    }
    else{
        cout << "Problemas com o arquivo!" << endl;
        return -1;
    }
}

void cadProdut(TNo *&no){ // CADASTRAR PRODUTOS
    TProduto prod;
    int iAux;

    cout << "   ||============ CADASTRO DE PRODUTOS ============||" << endl;
    cout << "     Nome: ";
    cin.ignore();
    getline(cin,prod.nome);  // PRODUTOS COM ESPAÇO

    do{
        cout << "     Tipo: 1 - Eletrônicos || 2 - Móveis || 3 - Brinquedos "; // PARA SABER A Q TIPO O PRODUTO PERTENCE
        cin>> iAux;
        switch(iAux){
            case 1:
                prod.tipo = "Eletronico";
            break;
              case 2:
                prod.tipo = "Movel";
            break;
              case 3:
                prod.tipo = "Brinquedo";
            break;
        }
    }while(iAux != 1 && iAux != 2 && iAux != 3);
    cout << "     Quantidade: ";
    cin >> prod.quantidade;
    cout << "     Preço: ";
    cin >> prod.preco;
    cout << "     Código: ";
    cin >> prod.chave;
    cout << "   ||==============================================||" << endl;
    if(inserirArvore(no,prod) == 0){
        inserirArq(prod);
    }
}

void mostrar(TProduto p, string c){//MOSTRAR POREM COM FILTRO DE CADA TIPO DO PRODUTO
    if(c == "Eletronico" && p.tipo == "Eletronico"){
        cout << "     Nome: " << p.nome << endl;
        cout << "     Tipo: " << p.tipo << endl;
        cout << "     Preço: R$ " << fixed << setprecision(2) << p.preco << endl;
        cout << "     Quantidade: " << p.quantidade << endl;
        cout << "     Código: " << p.chave << endl;
        cout << "   ||============================================||" << endl;
    }
    else{
        if(c == "Movel" && p.tipo == "Movel"){
            cout << "     Nome: " << p.nome << endl;
            cout << "     Tipo: " << p.tipo << endl;
            cout << "     Preço: R$ "<< fixed << setprecision(2) << p.preco << endl;
            cout << "     Quantidade: " << p.quantidade << endl;
            cout << "     Código: " << p.chave << endl;
            cout << "   ||============================================||" << endl;
        }
        else{
            if(c == "Brinquedo" && p.tipo == "Brinquedo"){
            cout << "     Nome: " << p.nome << endl;
            cout << "     Tipo: " << p.tipo << endl;
            cout << "     Preço: R$ " << fixed << setprecision(2) << p.preco << endl;
            cout << "     Quantidade: " << p.quantidade << endl;
            cout << "     Código: " << p.chave << endl;
            cout << "   ||============================================||" << endl;
        }
        }
    }
}

void percorrerINOrdem(TNo *&no, string c){//FUNÇÃO DEDICADA AO MOSTRAR, PECORRE A ARVORE DO MENOR PARA O MAIOR E MANDA PARA A O MOSTRAR
    if(no!=NULL){
        percorrerINOrdem(no->esquerda,c);
        mostrar(no->item,c);
        percorrerINOrdem(no->direita,c);
    }
}

void filtroBusca(TNo *no){ // OPÇAO PARA ESCOLHER QUAL TIPO DO PRODUTO MOSTRAR
    int opc;

    cout << "   ||================= FILTRAR POR =================||" << endl;
    cout << "   ||1 - ELETRÔNICOS                                ||" << endl;
    cout << "   ||2 - MÓVEIS                                     ||" << endl;
    cout << "   ||3 - BRINQUEDOS                                 ||" << endl;
    cout << "   ||===============================================||" << endl;
    cout << "   Opção: ";
    cin >> opc;

    system("CLS");
    switch(opc){
        case 0:
            cout << "Obrigado por utilizar o programa!!<3 S2" << endl;
        break;

        case 1:
            cout << "   ||============ MOSTRANDO PRODUTOS ============||" << endl;
            percorrerINOrdem(no,"Eletronico"); // CHAMA PECCORER QUE POR SUA VEZ CHAMA O MOSTRAR
        break;

        case 2:
            cout << "   ||============ MOSTRANDO PRODUTOS ============||" << endl;
            percorrerINOrdem(no,"Movel");

        break;

        case 3:
            cout << "   ||============ MOSTRANDO PRODUTOS ============||" << endl;
            percorrerINOrdem(no,"Brinquedo");
        break;


        default:
            cout << "Erro 404: Not Found!" << endl;
        break;
    }
}

void retirarEditArq(TProduto x,TNo *no, TNo *raiz){ // DEDICADA QUANDO PRECISAR DE EDITAR O ARQUIVO SEJA PARA EXCLUIR OU MUDAR ALGO
    if(no == raiz){
        fstream arquivo("produtos.txt",ios::trunc|ios::out); // CASO VISITE O PRIMEIRO NÓ APAGA O ARQUIVO E INSIRE COM ELE VAZIO
        inserirArq(x);
    }else{
        inserirArq(x); // EM SEGUIDA IERE UM APOS O OUTRO NORMALMENTE
    }

}

void preOrdemArq(TNo *&no,TNo *raiz){// FUNÇÃO DEDICADA PARA SER USADA NO REITIRAR OU EDITAR ARQUIVO PECORRE NA ORDEM EM QUE OS ITENS FORAM COLOCADOS NA ARVORE
    if(no!=NULL){
        retirarEditArq(no->item,no,raiz);
        preOrdemArq(no->esquerda,raiz);
        preOrdemArq(no->direita,raiz);
    }
}

void pegarAnterior(TNo *no, TNo *&noE){ // USADA PARA RETIRAR ALGUM NO DA ARVORE

    if (noE->direita != NULL){
        pegarAnterior(no,noE->direita);
    }
    else{
        no->item = noE->item;
        no = noE;
        noE = noE->esquerda;
        delete no;
    }
}

int retirarNo(TNo *&no,double p,int c){

    TNo *aux;

    if(no == NULL){
        cout << "Registro não encontrado!" << endl;
        return -1;
    }
    else{
        if(p < no->item.preco){ // PECORRE PELO PREÇO
            retirarNo(no->esquerda,p,c);
        }
        else{
            if(p > no->item.preco){// PECORRE PELO PREÇO
                retirarNo(no->direita,p,c);
            }
            else{
                if(no->direita == NULL && no->item.chave == c){// VERIFICA SE A CHAVE É A MESMA PELO MOTIVO DE TER PREÇOS IGUAIS
                    aux = no;
                    no = no->esquerda;
                    delete aux;
                }
                else{
                    if(no->item.chave != c){
                        retirarNo(no->direita,p,c);
                    }
                    else{
                        if(no->esquerda != NULL){ // CASO A ESQUERDA TENHA ITEM BUSCA O ITEM MAIS A ESQUERDA
                            pegarAnterior(no,no->esquerda);
                            return 0;
                        }
                        else{ // CASO O NO N CONTENHA APOTADOR PARA DIREITA OU ESQUERDA
                            aux = no;
                            no = no->direita;
                            delete aux;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// REALIZA A PESQUISA NA ÁRVORE BINÁRIA
TNo *pesquisa(TNo *&n,int c,double p){
    // Produto não encontrado
    if (n == NULL){
        cout << "Registro não localizado na árvore" << endl;
        return NULL;
    }
    else {
        // Pesquisa na Esquerda
        if (p < n->item.preco && n->item.chave != c){
            pesquisa(n->esquerda,c,p);
        }
        else {
            // Pesquisa na Direita
            if (p >= n->item.preco && n->item.chave != c){
                pesquisa(n->direita,c,p);
            }
            else{ // Produto encontrado retorna o Nó
                return n;
            }
        }
    }
}

int lendoArq(TNo *&no,int quantTokens){// INSERE OS PRODUTOS NA ARVORE

    TProduto p;
    fstream arq("produtos.txt",ios::out|ios::in);

    if(arq.is_open()){
        string registro, token;
        string valores[quantTokens];
        int i, j, contToken;

        while(arq.good()){ // LE ATE O FINAL DO ARQUIVO
            getline(arq,registro);
            if(registro.length() > 0){
                token = "";
                for(j=0; j < quantTokens;j++){
                    valores[j] = token;
                }
                i=0;
                contToken=0;
                while(i <= int(registro.length())){
                   if(registro[i] != ';') {
                        token = token + registro[i];
                    }
                    else{
                       valores[contToken] = token;
                        contToken++;
                       token = "";

                    }
                    i++;
                }
                valores[contToken] = token;

                p.nome = valores[0];
                p.tipo = valores[1];
                p.quantidade = stoi(valores[2]);
                p.preco = stof(valores[3]);
                p.chave = stoi(valores[4]);
                inserirArvore(no,p);//INSERE NO STRUCT PRODUTO E COLOCA NA ARVORE
            }
        }
    }
    else{
        cout << "Problemas com a abertura do arquivo!" << endl;
	return -1;
    }
    arq.close();
    return 0;
}

int edicao(TNo *&no,int opc){//EDITAR PRODUTO
    int c;
    double p;
    TNo *aux;
    char resp;
    filtroBusca(no);//MOSTRA OS PRODUTOS DISPONIVEIS
    cout << "Informe o código do produto: ";
    cin >> c;
    cout << "Informe o preço: ";
    cin >> p;
    aux = pesquisa(no,c,p);
    system("CLS");
    if(aux != NULL){ //VERIFICA SE EXISTE O PRODUTO
        cout << "   ||============    MENU EDITOR     ============||" << endl;
        mostrar(aux->item,aux->item.tipo);
        cout << "Deseja realmente editar esse produto? (S/N) ";
        cin >> resp;
        if(aux != NULL && (resp == 'S' || resp == 's')){
            switch(opc){
                case 1:// OPÇAO PARA EDITAR UM CAMPO EM EXPECIFICO
                    // NOME
                    cout << "Informe o novo nome: ";
                    cin.ignore();
                    getline(cin,aux->item.nome);
                    cout << "Ediçao concluida! " << endl;
                return 0;

                case 2: // PREÇO
                    cout << "Informe o novo Preço: ";
                    cin >> aux->item.preco;
                    cout << "Ediçao concluida! " << endl;
                return 0;

                case 3: // QUANTIDADE
                    cout << "Informe a nova quantidade: ";
                    cin >> aux->item.quantidade;
                    cout << "Ediçao concluida! " << endl;
                return 0;
            }
        }
    }else{
        cout << "Produto não Encontrado" << endl;
        return -1;
    }
}

void menuEditar(TNo *&no){
    int opc = 1;

    cout << "   ||================= MENU EDITAR =================||" << endl;
    cout << "   ||1 - EDITAR NOME                                ||" << endl;
    cout << "   ||2 - EDITAR PREÇO                               ||" << endl;
    cout << "   ||3 - QUANTIDADE                                 ||" << endl;
    cout << "   ||===============================================||" << endl;
    cout << "   Opção: ";
    cin >> opc;
    system("CLS");
    switch(opc){
        case 1:
            if(edicao(no,opc)==0){// EDITA NA ARVORE
                preOrdemArq(no,no);//COLOCA NO ARQUIVO
            }
        break;

        case 2:
            if(edicao(no,opc)==0){
                preOrdemArq(no,no);
            }
        break;

        case 3:
            if(edicao(no,opc)==0){
                preOrdemArq(no,no);
            }
        break;

        default:
            cout << "Erro 404: Not Found!" << endl;
            system("pause");
        break;
    }
}

void menuRetirar(TNo *&no){
    int c;
    double p;
    char x;
    TNo *aux;
    cout << "Deseja Continuar ? (S/N)";
    cin >> x;
    if(x == 's' || x == 'S'){
        filtroBusca(no);
        cout << "   Informe o código do produto:";
        cin >> c;
        cout << "   Para otimizar a busca insira o preço: ";
        cin >> p;
        aux = pesquisa(no,c,p);
        if(aux != NULL){ // VERIFICA SE FOI ENCONTRADO O PRODUTO
            system("CLS");
            mostrar(aux->item,aux->item.tipo); // MOSTRA O ARQUIVO A SER RETIRADO
            cout << "Deseja retirar ? (S/N) ";
            cin >> x;
            if(x == 's' || x == 'S'){
                if(retirarNo(no,aux->item.preco,aux->item.chave)==0){ // RETIRA O NO
                    if(no!=NULL){ // CASO N TENHA SIDO O NÓ RAIZ INSERE OS NOVOS PRODUTOS
                        preOrdemArq(no,no);
                    }else{
                        fstream arquivo("produtos.txt",ios::out|ios::trunc); // CASO N TENHA MAIS PRODUTOS APAGA O ARQUIVO
                    }
                    cout << "Produto Retirado!" << endl;
                }
            }
        }
    }
}

TCliente cadCliente(TNo *&no){
    TCliente c; // Cliente
    int quantidade;
    bool quantValida = false;
    char opc;
    cout << "   ||========== CADASTRO DE CLIENTE ==========||" << endl;
    cout << "     Nome: ";
    cin >> c.nome;
    cout << "     CPF: ";
    cin >> c.cpf;
    cout << "     ID: ";
    cin >> c.id;

    cout << "     Produto: " << no->item.nome << " - Preço: " << no->item.preco << endl;
    c.prodComprado = no->item.nome;
    do{
        cout << "     Quantidade (1-" << no->item.quantidade << "): ";
        cin >> quantidade;
        if(quantidade <= no->item.quantidade){
            quantValida = true;
            c.precoPagar = no->item.preco * quantidade; // MULTIPLICANDO O PREÇO PELA QUANTIDADE DE PRODUTOS COMPRADOS
            c.quantidade = quantidade;
        }
    }while(quantValida == false);
    cout << "     Produto: " << quantidade << "X " << no->item.nome << " - Preço: " << no->item.preco*quantidade << endl;
    cout << "     Deseja confirmar a compra de " << quantidade << "X " << no->item.nome << "?(S/N): ";
    cin >> opc;

    if(opc == 's' || opc == 'S'){
        no->item.quantidade = no->item.quantidade - quantidade; // DIMINUINDO A QUANTIDADE TOTAL APÓS A VENDA DE N PRODUTOS

        // DANDO ERRO
        if(no->item.quantidade == 0){
            cout << "     RETIRADO POR ESTOQUE ABAIXO DE 0!" << endl;
            system("pause");
        }

        return c;
    }

}

void vendaProduto(TNo *&no, TPilhaP &pp){
    char opc;
    cout << "    Continuar com a venda de produtos?(S/N)";
    cin >> opc;
    if(opc == 's' || opc == 'S'){
        int cod;
        double preco;
        TNo *aux;
        cout << "   ||       VENDA DE PRODUTOS           ||" << endl;
        filtroBusca(no);
        cout << "   Insira o código do produto desejado: ";
        cin >> cod;
        cout << "   Para otimizar a busca insira o preço: ";
        cin >> preco;
        aux = pesquisa(no,cod,preco);
        if(aux != NULL){
            cout << "   Produto que será vendido -> " << aux->item.nome << endl;
            cout << "   Vender?(S/N): ";
            cin >> opc;

            if(opc == 's' || opc == 'S'){
                TCliente c;
                c = cadCliente(aux);

                if(aux->item.quantidade == 0){
                    retirarNo(no,aux->item.preco,aux->item.chave);
                    if(no != NULL){
                        preOrdemArq(no,no);
                    }else{
                        fstream arquivo("produtos.txt",ios::out|ios::trunc);
                    }
                }

                if(c.nome != ""){
                    empilhar(pp,c);
                    cout << "     O PRODUTO FOI VENDIDO!" << endl;
                    system("pause");
                }

            }
        }else{
            cout << "Produto não encontrado!" << endl;
            system("pause");
        }
    }
}

int salvar(TPilhaP pp){
    fstream arquivo("historico.txt",ios::trunc|ios::in|ios::out);

    if(arquivo.is_open()){
        TCelulaCliente *aux = pp.topo->proximo;
        stringstream id,preco,quantidade;

        while(aux != NULL){
            arquivo << aux->cliente.nome + ";";
            arquivo << aux->cliente.cpf + ";";
            arquivo << aux->cliente.prodComprado + ";";
            id.str("""");
            id << aux->cliente.id;
            arquivo << id.str() + ";";

            preco.str("""");
            preco << aux->cliente.precoPagar;
            arquivo << preco.str() + ";";

            quantidade.str("""");
            quantidade << aux->cliente.quantidade;
            arquivo << quantidade.str() + "\n";

            aux = aux->proximo;
        }

        arquivo.close();
    }
    else{
        cout << "Problema com o arquivo 'historico.txt'" << endl;
    }
}

int carregar_dados(TPilhaP &pp){
    fstream arquivo("historico.txt");

    if(arquivo.is_open()){
        string registro, token;
        TCliente cliente;
        int j, contToken, contRegistro;

        contRegistro = 1;

        while(arquivo.good()){
            getline(arquivo,registro);
            if(registro.length() > 0){
                token = ""; // LIMPANDO INICIAL
                j=0;
                contToken=0;

                while(j<=int(registro.length())){
                    if(registro[j] != ';'){
                        token = token + registro[j]; // Preenche a variável token
                    }
                    else{
                        if(contToken == 0){
                            cliente.nome = token;
                        }
                        if(contToken == 1) cliente.cpf = token;
                        if(contToken == 2) cliente.prodComprado = token;
                        if(contToken == 3) cliente.id = stoi(token);
                        if(contToken == 4) cliente.precoPagar = stod(token);

                        contToken++;

                        token = ""; // Limpa Token
                    }
                    j++;
                }
                cliente.quantidade = stoi(token); // Ultimo Token
                empilhar(pp,cliente);
                contRegistro++;
            }
        }
    }
    else{
        cout << "Problemas com a abertura do arquivo!" << endl;
        return -1;
    }
    arquivo.close();
    return 0;
}

// OPERAÇÕES BÁSICAS DO FUNCIONÁRIO
void Menu_Funcionario(TPilhaP pp){
    TNo *no;
    criarArvoreVazia(no);
    int opc;
    lendoArq(no,5); // LE OS DADOS DO ARQUIVO
    carregar_dados(pp);
    do{
        cout << "   ||========== MENU DA LOJA ==========||" << endl;
        cout << "   ||1 - GERENCIAMENTO DE PRODUTOS     ||" << endl;
        cout << "   ||2 - REALIZAR VENDA DE PRODUTOS    ||" << endl;
        cout << "   ||3 - HISTÓRICO DE VENDAS           ||" << endl;
        cout << "   ||0 - LOGOUT                        ||" << endl;
        cout << "   ||__________________________________||" << endl;
        cout << "   ||      LOGADO COMO FUNCIONÁRIO     ||" << endl;
        cout << "   ||==================================||" << endl;
        cout << "   |--> Opção: ";
        cin >> opc;

        system("CLS");

        switch(opc){

            case 0:
                cout << "Programa Finalizado!" << endl;
            break;

            case 1:
                menuProd(no);
            break;

            case 2:
                vendaProduto(no,pp);
                salvar(pp);
            break;

            case 3:
                cout << "   ||=============== HISTÓRICO DE COMPRAS ===============||" << endl;
                mostrarPilha(pp);
                cout << "   ||====================================================||" << endl;
                system("pause");
            break;

            default:
                cout << "Opção inválida!" << endl;
            break;
        }

        if(opc != 0) system("CLS");

    }while(opc != 0);
}

// MENU DO GERENCIAMENTO DE PRODUTOS
void menuProd(TNo *&no){
    int opc=1;
        while(opc != 0){
            cout << "   ||================= MENU PRODUTOS =================||" << endl;
            cout << "   ||1 - CADASTRAR PRODUTOS                           ||" << endl;
            cout << "   ||2 - MOSTRAR PRODUTOS                             ||" << endl;
            cout << "   ||3 - RETIRAR PRODUTO                              ||" << endl;
            cout << "   ||4 - EDITAR                                       ||" << endl;
            cout << "   ||0 - RETORNAR AO MENU                             ||" << endl;
            cout << "   ||=================================================||" << endl;
            cout << "   Opção: ";
            cin >> opc;

            system("CLS");
            switch(opc){
                case 0:
                    cout << "Retornando ao menu!" << endl;
                break;

                case 1:
                    cadProdut(no);
                    cout << "Dados inseridos com sucesso!" << endl;
                break;

                case 2:
                    filtroBusca(no);
                break;

                case 3:
                    menuRetirar(no);
                break;

                case 4:
                    menuEditar(no);
                break;

                default:
                    cout << "Erro 404: Not Found!" << endl;
                break;
            }
            system("pause");
            if(opc!=0) system("CLS");
       }
}
