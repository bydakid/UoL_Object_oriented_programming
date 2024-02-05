#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <map>

// class that implements a command line for interacting with and OrderBook
class MerkelMain
{
    public:
        MerkelMain(); // constructor
        void init(); // initializes the program and go infinite loop
    private:
        void printIntro();
        void printHelp();
        void printProd();
        void printMin();
        void printMax();
        void printAvg();
        void printTime();
        void printStep();
        void printSquare();
        std::string getUserOption(); // user input returns input to a string
        void processUserOption(const std::string& userInput); // processes the user input and calls the function

        std::string currentTime; // stores the time in the program

        OrderBook orderBook{"20200601.csv"}; // OrderBook class, to store and manipulate the data from the CSV
};