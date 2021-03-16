#include "./converter/converter.hpp"
#include "search/search.hpp"
using namespace std;

string formmater(int size){
    return string(size, ':');
}

void menu_convert(){
    string input;
    string output;
    cout << formmater(10) << " Conversao " << formmater(10) << endl;
    cout << "Nome do arquivo de entrada [cep.txt] :";
    getline(cin, input);
    cout << "Nome do arquivo de saida [cep_pipe.txt]: ";
    getline(cin, output);
    if(input.empty()) input = "../cep.txt";
    if(output.empty()) output = "cep_pipe.txt";

    CsvConverter(input).convertFile(output);
    cout << endl << "Arquivo " << output << " gerado com sucesso" << endl;
}

void menu_search(){
    string input;
    int field;
    string term;
    cout << formmater(10) << " Busca Sequencial " << formmater(10) << endl;
    cout << "Nome do arquivo de busca [cep_pipe.txt] :";
    getline(cin, input);
    if(input.empty())  
        input = "cep_pipe.txt";
    SequentialSearch searcher(input);
    while(true){
        cout << "Campo de busca: " << endl << "(1) Endereco\t(2) Cidade\t(3)UF\t(4)CEP" <<endl;
        cout << "Digite o numero da opcao desejada: ";
        cin >> field;
        field--;
        if(field > 3 || field < 0){
            cout << "Valor fora dos possiveis" << endl;
        }else{
            cin.ignore(1,'\n');
            cout << "Termo a ser buscado: ";
            getline(cin, term);
            string result = searcher.search(term, field);
            if(result.empty())
                cout << endl << "Nenhum resultado encontrado" << endl;
            else cout << endl << "Resultado: " << result << endl;
        }
        cout << endl << "Fazer nova busca [Y/n]: ";
        getline(cin, input);
        if(input == "n") break;
    }
}

void menu(){
    int option;
    while(true){
        cout << formmater(10) << " Menu " << formmater(10) << endl;
        cout << "1. Converter arquivo" << endl;
        cout << "2. Busca sequencial" << endl;
        cout << "3. Sair" << endl;
        cout << "Insira a opcao: ";
        cin >> option;
        cin.ignore(1,'\n');
        switch (option){
        case 1:
            menu_convert();
            break;
        case 2:
            menu_search();
            break;
        case 3:
            exit(0);
        default:
            break;
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    SequentialSearch searcher("cep_pipe.txt");
    cout << searcher.search("RUA L", 0) << endl;
    menu();
    return 0;
}