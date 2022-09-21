#pragma once
#include "fstream"
#include "string"
#include "rules.h"
#include "rule.h"
#include "file.h"

class Formatter{
    public:
    Formatter(){

    };
    void formatFile(file f, Rules rules){
        for(int i = 0; i < rules.getNumOfRules(); i++){
            Rule temp = rules.getNextRule();
            if(temp.type == 0){
                for(int j = 0; j < f.getlinecount(); j++){
                    std::string line = f.getline(j);
                    for(int k = 0; k < line.length(); k++){
                        if(temp.problem.at(0) == line.at(k)){
                            if(k+1 < line.length() && ' ' == line.at(k+1)){
                                line = f.removefromline(j,k+2);
                            }
                                k+=1;
                            line = f.addtoline(j, k, temp.fix);
                        }
                    }
                }

            }

        }
    };
};
