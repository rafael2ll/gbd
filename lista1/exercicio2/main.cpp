#include "./converter/converter.hpp"
#include "search/search.hpp"
#include <string.h>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

/**
    Nomes e Matrículas:

    Rafael Valentim     11711BCC010
    Matheus José        11711BCC008
    Leonardo Essia      11712BCC009

**/

string formmater(int size){
    return string(size, ':');
}

void menu_convert(){
    string input;
    string output;
    cout << formmater(10) << " Conversao " << formmater(10) << endl;
    cout << "Nome do arquivo de entrada [cep.txt] :";
    getline(cin, input);
    cout << "Nome do arquivo de saida [cep_binary.txt]: ";
    getline(cin, output);
    if(input.empty()) input = "../cep.txt";
    if(output.empty()) output = "cep_binary.txt";

    CsvConverter(input).convertFile(output);
    cout << endl << "Arquivo " << output << " gerado com sucesso" << endl;
}

void menu_search(){
    string input;
    int field;
    string term;
    item found;
    cout << formmater(10) << " Busca Sequencial " << formmater(10) << endl;
    cout << "Nome do arquivo de busca [cep_binary.txt] :";
    getline(cin, input);
    if(input.empty())  
        input = "cep_binary.txt";
    SequentialSearch searcher(input);
    while(true){
        cout << "Campo de busca: " << endl << "(1) CEP\t(2) UF\t(3) Cidade\t(4) Logradouro" <<endl;
        cout << "Digite o numero da opcao desejada: ";
        cin >> field;
        field--;
        if(field > 3 || field < 0){
            cout << "Valor fora dos possiveis" << endl;
        }else{
            cin.ignore(1,'\n');
            cout << "Termo a ser buscado: ";
            getline(cin, term);
            auto time_init = high_resolution_clock::now();
            searcher.search(term, field, found);
            auto time_end = high_resolution_clock::now();
            if(strcmp(found.uf,"nan") == 0)
                cout << endl << "Nenhum resultado encontrado" << endl;
            else{
                 cout << endl << "Resultado: " << endl;
                 cout <<'\t' << "CEP: " << found.cep << endl;
                 cout <<'\t' << "UF: " << found.uf << endl;
                 cout <<'\t' << "Cidade: " << found.cidade << endl;
                 cout <<'\t' << "Logradouro: " << found.logradouro << endl;
            }
            duration<double, std::milli> ms_double = time_end - time_init;
            cout << endl << "Duracao: " << ms_double.count() << "ms" << endl;
        }
        cout << endl << "Fazer nova busca [Y/n]: ";
        getline(cin, input);
        if(input == "n") break;
    }
}
void menu_pos_search(){
    string input;
    int index;
    item found;
    cout << formmater(10) << " Busca por Posicao " << formmater(10) << endl;
    cout << "Nome do arquivo de busca [cep_binary.txt] :";
    getline(cin, input);
    if(input.empty())  
        input = "cep_binary.txt";

    IndexedSearch searcher(input);
    while(true){
        cout << "Digite o indice do item: ";
        cin >> index;
        cin.ignore(1,'\n');
        index--;
        if(index < 0){
            cout << "Insira um valor positivo maior que 0" << endl;
        }else{
            auto time_init = high_resolution_clock::now();
            searcher.search(index, found);
            auto time_end = high_resolution_clock::now();
            if(strcmp(found.uf,"nan") == 0)
                cout << endl << "Nenhum resultado encontrado" << endl;
            else{
                 cout << endl << "Resultado: " << endl;
                 cout <<'\t' <<"CEP: " << found.cep << endl;
                 cout <<'\t' <<"UF: " << found.uf << endl;
                 cout <<'\t' <<"Cidade: " << found.cidade << endl;
                 cout <<'\t' <<"Logradouro: " << found.logradouro << endl;
            }
            duration<double, std::milli> ms_double = time_end - time_init;
            cout << endl << "Duracao: " << ms_double.count() << "ms" << endl;
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
        cout << "3. Busca por posicao" << endl;
        cout << "4. Sair" << endl;
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
            menu_pos_search();
            break;
        case 4:
            exit(0);
        default:
            break;
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    menu();
    return 0;
}