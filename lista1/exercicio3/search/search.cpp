#include <iostream>
#include <fstream>
#include <string>
#include "search.hpp"

using namespace std;

IndexedSearch::IndexedSearch(string indexFile, string registerFileName){
    filename = indexFile;
    registerFile = registerFileName;
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