#include <iostream>
#include <fstream>
#include <string>
#include "search.hpp"

using namespace std;

bool is_desired_field(int cur, int desired){ return cur == desired;}
bool is_next_field(char c){ return c == '|';}

SequentialSearch::SequentialSearch(string file){
    filename = file;
}

IndexedSearch::IndexedSearch(string indexFile, string registerFileName){
    filename = indexFile;
    registerFile = registerFileName;
}

string SequentialSearch::search(string term, int field_index){
    string line;
    ifstream tsv(filename);
    int i = 0;
    
    cout << "Pesquisando por " << term << " em " << fields[field_index] << endl;
    while (getline (tsv, line)) { // O[n*(a + 4(a/4)) = n*2a] iteracoes  *a=tamanho medio de caracteres por linha | n= nro de linhas 
        if(search(line, term, field_index) == 1){
            return line;
        }
    }
    return "";
}

bool SequentialSearch::search(string row, string term, int field){
    int current_field = 0;
    string value = "";
    for(int i = 0; i < row.size(); i++){
        if(is_next_field(row[i])){
            if(is_desired_field(current_field, field)){
                return term == value;
            }
            else{
                current_field++;
                value.clear();
            }
        }
        else if(is_desired_field(current_field, field)){
            value.push_back(row[i]);
        }
    }
    return false;
}

void IndexedSearch::search(int index){

    ifstream indexFile(filename);
    ifstream registerFileStream(registerFile);

    int seekFrom = sizeof(int)*(index);
    int start;
    string line;
    
    indexFile.seekg(seekFrom, indexFile.beg);

    indexFile.read((char *) &start, sizeof(int));

    registerFileStream.seekg(start, registerFileStream.beg);
    
    getline(registerFileStream, line);

    cout << line << endl;

}