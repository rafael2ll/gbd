#include <iostream>
#include <fstream>
#include <string.h>
#include "converter.hpp"

using namespace std;

CsvConverter::CsvConverter(void){}

CsvConverter::CsvConverter(string file_name){
    filename = file_name;
}
void CsvConverter::convertFile(string outputName){
    string line;
    ifstream tsv(filename);
    ofstream output(outputName, ofstream::binary);
    int i = 0;
    while (getline (tsv, line)) { // O[n*(a + 4(a/4)) = n*2a] iteracoes  *a=tamanho medio de caracteres por linha | n= nro de linhas 
        item result;
        to_struct(line, result);
        output.write((char *)&result, sizeof(item));
    }
}

void CsvConverter::to_struct(string row, item &result){
    int size = row.size() -1;
    char ** temp = (char **) malloc(4);
    temp[0] = (char *) calloc(1, 20);
    temp[1] = (char *) calloc(1, 3);
    temp[2] = (char *) calloc(1, 39);
    temp[3] = (char *) calloc(1, 67);
    int index = 0;
    int i = 0;
    int field = 0;
    for(i = 0; i< row.size() - 1; i++){ // (n)
        if(row[i] == '\t'){ // Parar a cada tab
            index = i + 1;
            field++;
        }
        else temp[field][i-index] = row[i];
        if(field > 3)break;
    }
    result.cep = atoi(temp[0]);
    strncpy(result.uf, temp[1], 3);
    strncpy(result.cidade, temp[2], 39);
    strncpy(result.logradouro, temp[3], 67);
    // cout << result.cep << " - " << result.uf << " - " << result.cidade << " - " << result.logradouro << endl;
    free(temp);
}
