#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace Converter{
    class CsvConverter{
        public:
            static void convertFile(std::string filename);
        private:
            static void reorder(std::string row, std::string &result);
    };
}