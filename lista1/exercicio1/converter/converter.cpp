#include <iostream>
#include <fstream>
#include <string>
#include "converter.hpp"

using namespace std;

CsvConverter::CsvConverter(void){}

CsvConverter::CsvConverter(string file_name){
    filename = file_name;
}
void CsvConverter::convertFile(string outputName){
    string line;
    ifstream tsv(filename);
    ofstream output(outputName);
    int i = 0;
    while (getline (tsv, line)) { // O[n*(a + 4(a/4)) = n*2a] iteracoes  *a=tamanho medio de caracteres por linha | n= nro de linhas 
        string result = line;
        reorder(line, result);
        output << result << endl; // Copia cada linha invertida para o novo arquivo
    }
}

void CsvConverter::reorder(string row, string &result){
    int size = row.size() -1;
    char * temp = (char *) malloc(row.size());
    int index = 0;
    int i = 0;
    for(i = 0; i< row.size() - 1; i++){ // (n)
    if(row[i] == '\t'){ // Parar a cada tab 
            result[size-i-1] = '|'; // Adicionar pipe no inicio da string
            for(int j = 0; j< i - index; j++){ //copiar string no final da linha // n/4
                result[size - i + j] = temp[j];
            }
        index = i + 1;
    }
    else temp[i-index] = row[i];
    }
    for(int j = 0; j< i - index; j++){ // linha final que termina com \n copia-la para o inicio do arquivo // n/4
        result[j] = temp[j];
    }
}
