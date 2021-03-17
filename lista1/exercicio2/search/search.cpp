#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "search.hpp"

using namespace std;

bool is_desired_field(int cur, int desired){ return cur == desired;}
bool is_next_field(char c){ return c == '|';}

SequentialSearch::SequentialSearch(string file){
    filename = file;
}

void SequentialSearch::search(string term, int field_index, item &result){
    string line;
    ifstream tsv(filename);
    bool found= false;
    item it;
    cout << "Pesquisando por " << term << " em " << fields[field_index] << "..."<< endl;
    while(tsv.read((char *) &it, sizeof(item))) { 
        if(search(it, term, field_index) == true){
            result.cep = it.cep;
            strcpy(result.uf, it.uf);
            strcpy(result.cidade, it.cidade);
            strcpy(result.logradouro, it.logradouro);
            found = true;
            break;
        }
    }
    if(!found)strcpy(result.uf, "nan");
}

bool SequentialSearch::search(item row, string term, int field){
    switch (field)
    {
        case 0: return row.cep == atoi(term.c_str());
        case 1: return strcmp(row.uf, term.c_str()) == 0;
        case 2: return strcmp(row.cidade, term.c_str()) == 0;
        case 3: return strcmp(row.logradouro, term.c_str()) == 0;
        default: return false;
    }
}

