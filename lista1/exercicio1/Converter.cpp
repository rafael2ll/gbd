
#include <iostream>
#include <fstream>
#include <string>
#include "Converter.h"

using namespace std;

namespace Converter{

    void CsvConverter::convertFile(string filename){
        string line;
        ifstream tsv(filename);
        ofstream output("cep_pipe.csv");
        int i = 0;
        while (getline (tsv, line)) {
            string result = line;
            reorder(line, result);
            output << result;
        }
    }

    void CsvConverter::reorder(string row, string &result){
        int size = row.size() -1;
        char * temp = (char *) malloc(row.size());
        int index = 0;
        int i = 0;
        for(i = 0; i< row.size() - 1; i++){
        if(row[i] == '\t'){ // Parar a cada tab
                result[size-i-1] = '|'; // Adicionar pipe no inicio da string
                for(int j = 0; j< i - index; j++){ //copiar string no final da linha
                    result[size - i + j] = temp[j];
                }
            index = i + 1;
        }
        else temp[i-index] = row[i];
        }
        for(int j = 0; j< i - index; j++){ // linha final que termina com \n copia-la para o inicio do arquivo
            result[j] = temp[j];
        }
    }
}