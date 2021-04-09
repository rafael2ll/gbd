#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <fstream>
#include <string>

class IndexedSearch{
    public:
        std::string filename;
        std::string registerFile;
        IndexedSearch(void);
        IndexedSearch(std::string filename, std::string registerFile);
        void search(int index);
};

#endif // SEARCH_HPP