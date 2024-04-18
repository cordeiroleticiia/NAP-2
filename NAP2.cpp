#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool verificar(const string& login, const string& senha){
    ifstream arquivo("login.txt");

    if (arquivo.is_open()) {
        string loginSalvo, senhaSalva;
        while (arquivo >> loginSalvo >> senhaSalva) { // Lê todas as linhas do arquivo
            // Convertendo login para minúsculas para comparar
            transform(loginSalvo.begin(), loginSalvo.end(), loginSalvo.begin(), ::tolower);
            if (login == loginSalvo && senha == senhaSalva) {
                arquivo.close();
                return true;
            }
        }
    }
    arquivo.close(); 
    return false;
}

void cadastro_Usuario(const string& login, const string& senha){
    ofstream arquivo("login.txt", ios::app); // 

    if (arquivo.is_open()) {
        arquivo << login << " " << senha << endl; 
        arquivo.close(); 
        cout << "\nUsuário cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo de credenciais para escrita.\n" << endl;
    }
}

void exibirLogins(){
    ifstream arquivo("login.txt"); 

    if (arquivo.is_open()) {
        string login, senha;
        int quantLogin =0;
        
        while (arquivo >> login >> senha){
            quantLogin++;
        }
        cout << "Logins cadastrados: " << quantLogin << "\n" << endl;
        arquivo.clear();
        arquivo.seekg(0, ios::beg);
        
        while (arquivo >> login >> senha){
            cout << "Login: " << login << endl;
        }
        arquivo.close(); 
    } else {
        cout << "\nErro ao abrir o arquivo de login." << endl;
    }
}

void editarLogin(const string& loginAntigo, const string& novoLogin){
    ifstream arquivoIn("login.txt");
    ofstream arquivoOut("temp.txt");

    if (arquivoIn.is_open() && arquivoOut.is_open()){
        string login, senha;
        while (arquivoIn >> login >> senha) {
            if (login == loginAntigo) {
                arquivoOut << novoLogin << " " << senha << endl;
                cout << "Login atualizado com sucesso!" << endl;
            } else {
                arquivoOut << login << " " << senha << endl;
            }
        }
        arquivoIn.close();
        arquivoOut.close();
        
        remove("login.txt");
        rename("temp.txt", "login.txt");
    } else {
        cout << "Erro ao abrir o arquivo de login." << endl;
    }
}

void excluirLogin(const string& excluirLogin){
    ifstream arquivoIn("login.txt");
    ofstream arquivoOut("temp.txt");

    if (arquivoIn.is_open() && arquivoOut.is_open()) {
        string login, senha;
        bool loginEncontrado = false;
        while (arquivoIn >> login >> senha) {
            if (login == excluirLogin) {
                cout << "Login excluído com sucesso!" << endl;
                loginEncontrado = true;
                continue; // Pula para a próxima iteração do loop, não escrevendo o login e a senha no arquivo temporário
            } else {
                arquivoOut << login << " " << senha << endl;
            }
        }
        if (!loginEncontrado) {
            cout << "Login não encontrado." << endl;
        }
        arquivoIn.close();
        arquivoOut.close();
        
        remove("login.txt");
        rename("temp.txt", "login.txt");
    } else {
        cout << "Erro ao abrir o arquivo de login." << endl;
    }
}

void realizarQuestionario(){
	system("cls");
    char alternativa;
    int pontuacao = 0;
    string questao;
    char resposta;

    ifstream arquivo("BD_questionario.txt");// Abre o arquivo BD_questionario

    cout << "\n===== Questionário de Lógica de Matemática =====\n";

    // Lê as questões e respostas do arquivo
    for (int i = 0; i < 5; ++i){
        getline(arquivo, questao, '#');  // Lê a questão até o espaço
        arquivo >> resposta;
        arquivo.ignore();  // Ignora o caractere de nova linha após a resposta

        cout << "\n" << questao << endl;
        cout << "Resposta (V/F): ";
        cin >> alternativa;

        if (tolower(alternativa) == tolower(resposta)) {// Verifica se a resposta está correta
            cout << "Resposta correta!\n";
            pontuacao++;
        } else {
            cout << "Resposta incorreta. A resposta correta é: " << resposta << endl;
        }
    }
    arquivo.close();  // Fecha o arquivo
    cout << "\n===== Resultado =====\n";
    cout << "Pontuação: " << pontuacao << " de 5 questões\n"<<endl;
    system("pause");
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    
    int opcao, opcao2;
    string login, senha;
	string novoLogin, excluir_Login;
    bool voltar = true, continuar = true;
    
    while (voltar) {
    	system("cls");
        cout << "-- Tela Inicial --\n";
        cout << "\n1 - Fazer login\n2 - Fazer cadastro\n";
        cout << "3 - Editar login\n4 - Excluir login\n";
        cout << "5 - Mostrar logins\n6 - Fechar Sistema\n";
        cout << "\nDigite sua opção: ";
        cin >> opcao;
        system("cls");
        
        switch (opcao){
            case 1:
                cout << "Digite o login: ";
                cin >> login;
                cout << "Digite a senha: ";
                cin >> senha;
                system("pause");
                if (verificar(login, senha)){
                	system("cls");
                    cout << "===== Seja Bem Vindo(a), "<< login <<"! ===== "<< endl;
                    cout << "\nDeseja iniciar o questionário de lógica matemática?";
                    cout << "\n1 - Sim\n2 - Não\n" << endl;
                    cin >> opcao2;
                    if (opcao2 == 1) {
                        realizarQuestionario();
                    } else {
                        cout << "\n===== Entendido! Voltando para a tela inicial... =====\n" << endl;
                    }
                } else {
                    cout << "\nLogin ou senha incorretos! Voltando para a tela inicial...\n" << endl;
                }
                break;
            case 2:
            	//Cadastro do Usuário
            	do{
            		cout << "Digite o login: ";
	                cin >> login;
	                do{ //A senha só permite 4 digitos
	                	system("cls");
	                	cout << "Digite o login: " << login << endl;
		                cout << "Digite a senha(4 digitos): ";
		                cin >> senha;
					}while(senha.size() !=4);
	                
		    		if(verificar(login, senha) == true){ // Verifica no arquivo login.txt se há um login existente;
						cout << "\nLogin já existe!\n"<<endl;
						system("pause");
						system("cls");						
					}else{
				        cadastro_Usuario(login, senha);
				        continuar = false;
					}
				}while(continuar);
                system("pause");
                break;
            case 3:
                cout << "Digite o login antigo: ";
                cin >> login;
                cout << "Digite o novo login: ";
                cin >> novoLogin;
                editarLogin(login, novoLogin);
                system("pause");
                break;
            case 4:
            	exibirLogins(); // Exibe os Logins já cadastrados para selecionalo e exclusão
                cout << "\nDigite o login que deseja excluir: ";
                cin >> excluir_Login;
                excluirLogin(excluir_Login); //Exclui o login digitado;
                system("pause");
                break;
            case 5:
                exibirLogins(); // Exibir logins atualizados
                system("pause");
                break;
            case 6:
                cout << "\nEncerrando o programa." << endl;
                voltar = false;
                break;
            default:
                cout << "\nOpção inválida. Por favor, escolha novamente.\n" << endl;
        }
    }
    return 0;
}
