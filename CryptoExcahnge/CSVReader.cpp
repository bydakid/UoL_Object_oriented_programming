#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries; // vector store OrderBookEntry objects

    // open CSV file
    std::ifstream csvFile{csvFilename};
    std::string line;
    if(csvFile.is_open())
    {
        while(std::getline(csvFile, line)) /// read each line
        {
            try{
                OrderBookEntry obe = stringsToOBE(tokenise(line, ',')); // tokenize the line and convert it OrderBookEntry object
                entries.push_back(obe); // Aad the OrderBookEntry object to vector
            }catch(const std::exception& e)
            {
                std::cout << "CSVREADER:: readCSV bad data "<< std::endl; // print an error message
            }
            
        }
    }
     return entries; // return the vector
}

// split the csvLine string into tokens  
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char seperator)
{
    std::vector<std::string> tokens; // vector store tokens
    signed int start, end; // variables store the start and end positions of each token
    std::string token; // string to store the token
        start = csvLine.find_first_not_of(seperator, 0); // find the first non-seperator character
        //continue looping until no more tokens
        do{
            end = csvLine.find_first_of(seperator, start); // first sperator character after start pos
            if (start == csvLine.length() || start == end) break; // if the start position is at the end of the csvLine string, or if the start and end positions are the same, break out of the loop
            if (end >= 0) token = csvLine.substr(start, end - start); // if valid extract the token from the csvLine string
            else token = csvLine.substr(start, csvLine.length() - start); // if not valid extract the remaining part of the csvLine string
            tokens.push_back(token); // add the token to the vector
        start = end + 1; // set the start position to the end pos +1
        }while(end > 0);

        return tokens; // return the vector token
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    // check if number of tokens are correct
    if (tokens.size() !=5) //bad
    {
        std::cout <<"Bad line " << std::endl;
        throw std::exception{};
    }

    // 5 tokens
    try{
        //convert 3 and 4 tokens to double
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout <<"bad float! " << tokens[3]<<std::endl;
        std::cout <<"bad float! " << tokens[4]<<std::endl;
        throw;
    }
    OrderBookEntry obe{ price,
                        amount,
                        tokens[0],
                        tokens[1],
                        OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}