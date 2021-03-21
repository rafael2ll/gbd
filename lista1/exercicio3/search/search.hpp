#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <fstream>
#include <string>


class SequentialSearch{
    public:
        std::string filename;
        std::string fields[4] = {"endereco", "cidade", "UF", "CEP"};
        SequentialSearch(void);
        SequentialSearch(std::string filename);
        std::string search(std::string term, int field);
    private:
        bool search(std::string row, std::string term, int field_position);
};

class IndexedSearch{
    public:
        std::string filename;
        std::string registerFile;
        IndexedSearch(void);
        IndexedSearch(std::string filename, std::string registerFile);
        void search(int index);
};

#endif // SEARCH_HPP