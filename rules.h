#pragma once
#include "fstream"
#include "string"
#include "rule.h"

class Rules{
    // Creates rules array from file provided by argument f. Should return null if file not found.
    Rules(std::string file);
    // Acesses the next rule and gets the string
    std::string getNextRule();
};