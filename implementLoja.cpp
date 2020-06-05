#include "loja.h"
#include <string>

// REALIZA O PRIMEIRO CADASTRO E DEPOIS CHAMA O LOGIN
void primeiroCadastro(){
    TListaP lp;
    int cont=0;
    criarListaVazia(lp);

    fstream arquivo("login.txt",ios::in);

    if(arquivo.is_open()){
        string registro;
        // CONTA QUANTAS LINHAS TEM NO ARQUIVO
        while(arquivo.good()){
            cont++;
            getline(arquivo,registro);
        }
        arquivo.close();

        // VERIFICA SE O ARQUIVO ESTA VAZIO. SE SIM ENT�O DEVE REALIZAR O PRIMEIRO CADASTRO DO ADMINISTRADOR
        if(cont == 1){
            arquivo.open("login.txt",ios::in|ios::out);
            string login,senha;
            bool senha_menor = true;

            cout << "||================== PRIMEIRO CADASTRO ===================||" << endl;
            cout << "||SER� REALIZADO PRIMEIRAMENTE O CADASTRO DO ADMINISTRADOR||" << endl;
            cout << "||PARA QUE O MESMO TENHA ACESSO TOTAL AO PROGRAMA         ||" << endl;
            cout << "||========================================================||" << endl;
            cout << "  Login: ";
            cin >> login;
            cout << "Sua senha deve ter no m�nimo 8 caracteres!" << endl;
            do{
                cout << "Senha: ";
                cin >> senha;
                if(senha.length() < 8){ // VERIFICA SE A SENHA DIGITADA TEM NO M�NIMO 8 CARACTERES
                    cout << "Sua senha deve ter no m�nimo 8 caracteres!" << endl;
                }
                else{
                    senha_menor = false;
                }
            }while(senha_menor);

            arquivo << login+"\n";
            arquivo << senha+"\n";
            arquivo.close();
        }
    }
    login(lp);
}

// VERIFICA SE OS LOGIN E SENHA EST�O ARMAZENADOS NO ARQUIVO
int verifLogin(TListaP lp, string u, string s){
    fstream arquivo("login.txt");
    string usuario,senha;
    int cont=0;

    if(arquivo.is_open()){
        while(arquivo.good()){

            getline(arquivo,usuario);
            getline(arquivo,senha);
            if(u == usuario && s == senha && cont == 0){
                cout << "   Logado como Administrador!" << endl;
                cout << "   Bem vindo!" << endl;
                return 1;
            }
            else{
                if(u == usuario || s == senha){
                    cout << "   Bem vindo " << u << endl;
                    return 2;
                }
            }
            cont++;
        }
        return 3;
    }

}

// PROCEDIMENTO DE LOGIN
void login(TListaP lp){
    bool logado = false;
    fstream arquivo("login.txt");
    string usuario,senha, $usuario, $senha;
    int cont, tentativas = 3, verif;
    do{
        cont = 0;
        cout << "||========== LOGIN ==========||" << endl;
        cout << "  Usu�rio: ";
        cin >> usuario;
        cout << "  Senha: ";
        cin >> senha;

        verif = verifLogin(lp,usuario,senha); // 1 - Login como Admin | 2 - Login como funcion�rio | 3 - Login ou senha inv�lidos

        system("pause");
        system("cls");

        switch(verif){
            case 1:
                menuAdmin(lp);
            break;

            case 2:
                TPilhaP p;
                criarPilhaVazia(p);
                Menu_Funcionario(p);
            break;

            default:
                cout << "Login ou senha inv�lida!" << endl;
                tentativas--;
            break;
        }

    }while(tentativas != 0);
}

// REALIZA O CADASTRO DE FUNCION�RIOS
void CadastrarFuncionario(TListaP &lp){
    Tusuario usuario;
    stringstream id, salario;
    fstream arquivo("login.txt",ios::ate|ios::in|ios::out);
    bool diferente = false;

    if(arquivo.is_open()){ // VERIFICA SE O ARQUIVO FOI ABERTO
        cout << "   ||============ CADASTRO DE FUNCION�RIOS ============||" << endl;

        cout << "     Nome: ";
        cin.ignore();
        getline(cin,usuario.nome);
        arquivo << usuario.nome + "\n";

        cout << "     Senha: ";
        cin >> usuario.senha;
        arquivo << usuario.senha + "\n";
        cout << "     CPF: ";
        cin >> usuario.cpf;

        cout << "     Sal�rio: ";
        cin >> usuario.salario;

        while(diferente==false){
            cout << "     ID: ";
            cin >> usuario.id;
            diferente = true;
            if(lp.contItens>0){
                TCelula *aux = lp.primeiro->proximo;

                while(aux != NULL){
                    if(usuario.id != aux->usuario.id){
                        diferente = true;
                    }
                    else{
                        diferente = false;
                        break;
                    }
                    aux = aux->proximo;
                }
                if(diferente){
                    break;
                }
                else{
                    cout << "ID j� existente! Por favor, insira um ID diferente." << endl;
                }
            }
        }

        system("pause");
        inserir(lp,usuario); // Passando os dados coletados para inserir na lista
        arquivo.close();
    }
}

// MOSTRA OS DADOS DO FUNCION�RIO(ID,CPF,NOME E SAL�RIO)
void mostrarFuncionarios(TListaP lp){
    cout << "   ||============== FUNCION�RIOS CADASTRADOS ===============||" << endl;
    mostrar(lp);
    cout << "   ||=======================================================||" << endl;
    system("pause");
}

// PROCURA OS DADOS DO FUNCION�RIO
TCelula *pesquisarFuncionario(TListaP lp){
    if(verifListaVazia(lp)){
        cout << "N�o existe funcion�rios cadastrados!" << endl;
    }
    else{
        int id;
        TCelula *aux = lp.primeiro->proximo;
        bool achou = false;
        mostrarFuncionarios(lp);
        cout << "   Insira o ID do funcion�rio que voc� deseja editar os dados: ";
        cin >> id;

        while(aux != NULL){
            if(id == aux->usuario.id){
                achou = true;
                return aux;
            }
            aux = aux->proximo;
        }
        if(!achou){
            return NULL;
        }
    }
}

// EDITA OS DADOS DOS FUNCION�RIOS
void editarFuncionario(TListaP &lp){
    int opc;
    char escolha;
    TCelula *aux = pesquisarFuncionario(lp); // C�LULA COM OS DADOS DO FUNCION�RIO PESQUISADO
    cout << "     Funcion�rio: " << aux->usuario.nome << endl;
    cout << "     Deseja prosseguir com a edi��o?(S/N): ";
    cin >> escolha;
    if(escolha == 's' || escolha == 'S'){
        fstream arquivo("login.txt");
        string senha, $senha;
        getline(arquivo,$senha); // RECEBENDO O NOME DO USU�RIO
        getline(arquivo,$senha); // RECEBENDO A SENHA
        cout << "     Por favor, insira a senha do ADMINISTRADOR: ";
        cin >> senha;
        system("CLS");
        if(senha == $senha){ // VERIFICANDO A SENHA DO ADMINISTRADOR
            do{
                cout << "   ||========== EDITAR DADOS DOS FUNCION�RIOS ===========||" << endl;
                cout << "   ||1 - EDITAR NOME                                     ||" << endl;
                cout << "   ||2 - EDITAR SENHA                                    ||" << endl;
                cout << "   ||3 - EDITAR CPF                                      ||" << endl;
                cout << "   ||4 - EDITAR SAL�RIO                                  ||" << endl;
                cout << "   ||0 - RETORNAR AO MENU                                ||" << endl;
                cout << "   ||====================================================||" << endl;
                cout << "    |--> Op��o: ";
                cin >> opc;

                switch(opc){

                    case 0:
                        cout << "Retornando ao Menu!" << endl;
                        system("pause");
                    break;

                    case 1:
                        cout << "Insira o nome: ";
                        cin >> aux->usuario.nome;
                    break;

                    case 2:
                        cout << "Insira a senha: ";
                        cin >> aux->usuario.senha;
                    break;

                    case 3:
                        cout << "Insira o CPF: ";
                        cin >> aux->usuario.cpf;
                    break;

                    case 4:
                        cout << "   Insira o S�lario: ";
                        cin >> aux->usuario.salario;
                    break;

                    default:
                        cout << "Op��o inv�lida!" << endl;
                    break;

                }

                salvar_dados(lp);

                if(opc != 0) system("CLS");

            }while(opc==0);
        }
    }

}

// RETIRA O FUNCION�RIO ESCOLHIDO
void retirar_funcionario(TListaP lp){
    if(verifListaVazia(lp)){
        cout << "Nenhum funcion�rio encontrado!" << endl;
    }
    else{
        string usuario,senha,$senha;
        int tentativas = 3;
        fstream arquivo("login.txt",ios::in|ios::out);
        getline(arquivo,usuario);
        getline(arquivo,$senha);
        cout << "Voc� entrou na op��o que remove funcion�rios" << endl;

        do{
            cout << "Tentativas restantes: " << tentativas << endl;
            cout << "Insira a senha do administrador: ";
            cin >> senha;
            tentativas--;
        }while(senha != $senha && tentativas > 0);

        if(senha == $senha){
            int id;
            char escolha;
            TCelula *aux;
            mostrarFuncionarios(lp); // MOSTRANDO FUNCION�RIOS
            cout << "Insira o Id do funcion�rio que deseja retirar: ";
            cin >> id;

            cout << "Deseja realmente retirar o funcion�rio?(S/N)";
            cin >> escolha;

            if(escolha == 's'|| escolha == 'S'){
                retirar(lp,id);
            }
        }
    }
    system("pause");
}

// SALVA OS DADOS DOS FUNCION�RIOS
int salvar_dados(TListaP lp){
    fstream arquivo("dados.txt",ios::trunc|ios::in|ios::out); // ABRE O ARQUIVO LIMPANDO OS DADOS
    fstream arquivo2("login.txt",ios::in|ios::out); // ABRE O ARQUIVO

    if(arquivo.is_open()){
        stringstream salario,id;

        TCelula *aux = lp.primeiro->proximo;


        while(aux != NULL){
            arquivo << aux->usuario.nome + ";";
            arquivo << aux->usuario.senha + ";";
            arquivo << aux->usuario.cpf + ";";

            // LIMPANDO O LIXO ACUMULADO
            salario.str("""");
            id.str("""");

            // CONVERTENDO DOUBLE PARA STRING E INSERINDO NO ARQUIVO
            salario << aux->usuario.salario;
            arquivo << salario.str() + ";";

            // CONVERTENDO INT PARA STRING E INSERINDO NO ARQUIVO
            id << aux->usuario.id;
            arquivo << id.str()+ "\n";

            aux = aux->proximo;
        }
        cout << "Dados salvos!" << endl;
    }
    else{
        cout << "Arquivo com problemas!" << endl;
        return -1;
    }
    arquivo.close();

    // SALVANDO NO ARQUIVO "login.txt"
    if(arquivo2.is_open()){
        string dadosAdmin[2];

        // COLETANDO OS DADOS DE LOGIN DO ADMIN ANTES DE LIMPAR TODO O ARQUIVO
        getline(arquivo2,dadosAdmin[0]);
        getline(arquivo2,dadosAdmin[1]);

        arquivo2.close(); // FECHANDO O ARQUIVO

        arquivo2.open("login.txt",ios::trunc|ios::in|ios::out); // ABRINDO O ARQUIVO J� LIMPANDO O MESMO

        // INSERINDO OS DADOS DO ADMINISTRADOR NO ARQUIVO LIMPO
        arquivo2 << dadosAdmin[0] + "\n";
        arquivo2 << dadosAdmin[1] + "\n";

        // INSERINDO OS DADOS DE LOGIN DOS FUNCION�RIOS
        TCelula *aux = lp.primeiro->proximo;
        while(aux != NULL){
            arquivo2 << aux->usuario.nome + "\n";
            arquivo2 << aux->usuario.senha + "\n";

            aux = aux->proximo;
        }
    }
    else{
        cout << "Problema com o arquivo respons�vel por armazenar os dados de login!" << endl;
        return -1;
    }

    arquivo2.close(); // FECHANDO ARQUIVO



    return 0;
}

// CARREGA OS DADOS DOS FUNCIONARIOS
int carregar_dados(TListaP &lp,string nome){
    fstream arquivo(nome);

    if(arquivo.is_open()){
        string registro, token;
        Tusuario usuario;
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
                        token = token + registro[j]; // Preenche a vari�vel token
                    }
                    else{
                        if(contToken == 0){
                            usuario.nome = token;
                        }
                        if(contToken == 1) usuario.senha = token;
                        if(contToken == 2) usuario.cpf = token;
                        if(contToken == 3) usuario.salario = stod(token);

                        contToken++;

                        token = ""; // Limpa Token
                    }
                    j++;
                }
                usuario.id = stoi(token); // Ultimo Token
                inserir(lp,usuario);
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

// MENU DE GERENCIAMENTO DE FUNCION�RIOS
void gerenciar_funcionarios(TListaP &lp){
    int opc;

    do{
        cout << "   ||========== GERENCIAMENTO DE FUNCION�RIOS ==========||" << endl;
        cout << "   ||1 - CADASTRAR NOVOS FUNCION�RIOS                   ||" << endl;
        cout << "   ||2 - MOSTRAR DADOS DOS FUNCION�RIOS                 ||" << endl;
        cout << "   ||3 - EDITAR DADOS DOS FUNCION�RIOS                  ||" << endl;
        cout << "   ||4 - RETIRAR FUNCION�RIO                            ||" << endl;
        cout << "   ||0 - RETORNAR AO MENU                               ||" << endl;
        cout << "   ||===================================================||" << endl;
        cout << "   |--> Op��o: ";
        cin >> opc;

        system("CLS");

        switch(opc){

            case 0:
                cout << "Retornando ao Menu!" << endl;
            break;

            case 1: // CADASTRAMENTO DE FUNCION�RIOS
                CadastrarFuncionario(lp);
                salvar_dados(lp);
                system("pause");
            break;

            case 2: // MOSTRA OS FUNCION�RIOS CADASTRADOS
                mostrarFuncionarios(lp);
            break;

            case 3: // EDITA OS DADOS DO FUNCION�RIO
                editarFuncionario(lp);
            break;

            case 4: // RETIRA OS DADOS DO FUNCION�RIO
                retirar_funcionario(lp);
                salvar_dados(lp);
                system("CLS");
            break;
        }
        if(opc != 0) system("CLS");

    }while(opc != 0);
}

// MENU PARA EDI��O DE LOGIN E SENHA DO ADMIN
void MenuEditAdmin(TListaP lp, TPilhaP pp){
    char opc;
    cout << "   Deseja continuar com altera��o?(S/N): ";
    cin >> opc;

    if(opc == 's' || opc == 'S'){
        fstream arquivo("login.txt",ios::in|ios::out);
        string senha, $usuario, $senha;
        getline(arquivo,$usuario);
        getline(arquivo,$senha);

        arquivo.close();

        cout << "   Por favor, insira sua senha atual: ";
        cin >> senha;

        if(senha == $senha){
            int escolha;
            do{
                cout << "   ||======= ESCOLHA O QUE DESEJA EDITAR ======||" << endl;
                cout << "   ||1 - EDITAR LOGIN                          ||" << endl;
                cout << "   ||2 - EDITAR SENHA                          ||" << endl;
                cout << "   ||0 - SAIR DA EDI��O                        ||" << endl;
                cout << "   ||==========================================||" << endl;
                cout << "   |--> Op��o: ";
                cin >> escolha;

                arquivo.open("login.txt", ios::in|ios::out);
                switch(escolha){

                    case 1:
                        cout << "   Login atual -> " << $usuario << endl;
                        cout << "   Insira o novo Login: ";
                        cin >> $usuario;
                        arquivo << $usuario;
                    break;

                    case 2:
                        cout << "   Senha atual -> " << $senha << endl;
                        do{
                            cout << "   Insira a nova Senha com no m�nimo 8 caracteres: ";
                            cin >> $senha;
                        }while($senha.length() < 7);
                        arquivo << $usuario +"\n";
                        arquivo << $senha + "\n";
                    break;
                }

            }while(escolha != 0);
        }
        arquivo.close();
    }

}

// MENU DOS FUNCION�RIOS
void OpcoesAdmin(TListaP lp){
    int opc;
    do{
        cout << "   ||========== OP��ES DO ADMINISTRADOR ==========||" << endl;
        cout << "   ||1 - MODIFICAR LOGIN OU SENHA                 ||" << endl;
        cout << "   ||0 - VOLTAR AO MENU                           ||" << endl;
        cout << "   ||=============================================||" << endl;
        cout << "   |--> Op��o: ";
        cin >> opc;

        switch(opc){
            case 1:
                TPilhaP pp;
                criarPilhaVazia(pp);
                MenuEditAdmin(lp,pp);
            break;
        }

    }while(opc != 0);
}

// MENU DO ADMINISTRADOR
void menuAdmin(TListaP lp){
    int opc;
    carregar_dados(lp,"dados.txt");
    TNo *no;
    criarArvoreVazia(no);
    lendoArq(no,5);
    do{
        cout << "   ||==================== MENU DA LOJA =====================||" << endl;
        cout << "   ||1 - OP��ES DE ADMINISTRADOR                            ||" << endl;
        cout << "   ||2 - GERENCIAMENTO DE PRODUTOS                          ||" << endl;
        cout << "   ||3 - GERENCIAMENTO DE FUNCION�RIOS                      ||" << endl;
        cout << "   ||0 - LOGOUT                                             ||" << endl;
        cout << "   ||_______________________________________________________||" << endl;
        cout << "   ||               LOGADO COMO ADMINISTRADO                ||" << endl;
        cout << "   ||=======================================================||" << endl;
        cout << "   |--> Op��o: ";
        cin >> opc;

        system("CLS");

        switch(opc){
            case 0: // FINALIZA O PROGRAMA
                cout << "Programa finalizado!" << endl;
            break;

            case 1: // ACESSA AS OP��ES DO ADMINISTRADOR
                OpcoesAdmin(lp);
            break;

            case 2: // ACESSA O MENU DE PRODUTOS
                system("CLS");
                menuProd(no);
            break;

            case 3: // ACESSA O GERENCIADOR DE FUNCION�RIOS
                gerenciar_funcionarios(lp);
            break;

            default:
                cout << "Op��o inv�lida!" << endl;
            break;
        }
        if(opc != 0) system("CLS");

    }while(opc!=0);
}
