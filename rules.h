#pragma once
#include "fstream"
#include "string"
#include "rule.h"

class Rules{
public:
    // Creates rules array from file provided by argument f. Should return null if file not found.
    Rule r[5];
    int i = 0;
    int rules = 0;
    Rules(std::string file){
        r[0] = Rule(0, ".", 0, "\n");
        rules++;
        r[0] = Rule(0, "?", 0, "\n");
        rules++;
        r[0] = Rule(0, "!", 0, "\n");
        rules++;
    }
    // Acesses the next rule and gets the string
    Rule getNextRule(){
        if(i <= rules){
            return r[i];
            i++;
        }
        std::cout << "ERROR: Reached unexpected rule";
        exit(0);
    }

    int getNumOfRules(){
        return rules;
    }
};