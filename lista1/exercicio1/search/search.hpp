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

#endif // SEARCH_HPP