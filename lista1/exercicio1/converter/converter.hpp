#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <iostream>
#include <fstream>
#include <string>

class CsvConverter{
    public:
        std::string filename;
        CsvConverter(void);
        CsvConverter(std::string filename);
        void convertFile(std::string outputName);
    private:
        void reorder(std::string row, std::string &result);
};

#endif // CONVERTER_HPP