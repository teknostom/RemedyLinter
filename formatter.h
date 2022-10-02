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
        // Loop through all Rules
        for(int i = 0; i < rules.getNumOfRules(); i++){

            // Get current rule
            Rule currentrule = rules.getNextRule();

            // Check if the current rule is of type replace
            if(currentrule.type == 0){

                // Loop through all lines in text
                for(int currentline = 0; currentline < f.getlinecount(); currentline++){

                    // Get current line
                    std::string line = f.getline(currentline);

                    // Loop through line
                    for(int linepos = 0; linepos < (int)line.length(); linepos++){
                        // Check if current position in line matches rule trigger
                        if(currentrule.problem.at(0) == line.at(linepos)){
                            // Check so that there isn't already newline
                            if(linepos+1 < (int)line.length() && ' ' == line.at(linepos+1)){
                                line = f.removefromline(currentline,linepos+2);
                            }
                            linepos+=1;
                            line = f.addtoline(currentline, linepos, currentrule.fix);
                        }
                        // Check if stop trigger is met, and send formatter to next line
                        if(currentrule.stoptype == 0 && line.at(linepos) == currentrule.stopclause.at(0)){
                            linepos = line.length();
                        }
                    }
                }
            }
        }
    };
};
