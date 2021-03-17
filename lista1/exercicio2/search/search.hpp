#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "../model/models.hpp"

class SequentialSearch{
    public:
        std::string filename;
        std::string fields[4] = {"CEP", "UD", "cidade", "logradouro"};
        SequentialSearch(void);
        SequentialSearch(std::string filename);
        void search(std::string term, int field, item &result);
    private:
        bool search(item row, std::string term, int field_position);
};

#endif // SEARCH_HPP