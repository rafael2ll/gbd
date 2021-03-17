#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "../model/models.hpp"
class CsvConverter{
    public:
        std::string filename;
        CsvConverter(void);
        CsvConverter(std::string filename);
        void convertFile(std::string outputName);
    private:
        void to_struct(std::string row, item &result);
};

#endif // CONVERTER_HPP