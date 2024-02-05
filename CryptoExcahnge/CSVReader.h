#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

// class so functions for reading data from a CSV file and storing the data
class CSVReader
{
    public:
        CSVReader(); // constructor
        static std::vector<OrderBookEntry> readCSV(std::string csvFile); // reads data from CSV file and stores it in vector 

    private:
        static std::vector<std::string> tokenise(std::string csvLine, char seperator); // tokenizes string by splitting it into pieces separated by a given character separator
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);         // converts a vector of strings into an OrderBookEntry object
};