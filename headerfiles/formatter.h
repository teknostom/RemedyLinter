#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "rules.h"
#include "rule.h"
#include "file.h"
#include "progress.h"

class Formatter{
    public:
    
std::string fileToString(file input){
    std::string res = "";
    for(int i = 0; i < input.getlinecount(); i++){
        res += input.getline(i) + ((i<input.getlinecount() - 1) ? "\n" : "");
    }
    
    return res;
}
    Formatter(){

    };
    file formatFile(file f, Rules rules, Progress prog, bool debug = false){
        // Loop through all Rules
        for(int rule = 0; rule < rules.getNumOfRules(); rule++){
            //if(debug)
              //  std::cout << "["<<rule+1<<"/" << rules.getNumOfRules() <<"] Rules have been formatted. "<< ((rule+1 < rules.getNumOfRules()) ? "\r" : "\n");
            prog.PrintRule(rule+1);
            // Get current rule
            Rule currentrule = rules.getNextRule();
            // Check if the current rule is of type replace
            if(currentrule.type == 0){
                                // Loop through all lines in text
                for(int currentline = 0; currentline < f.getlinecount(); currentline++){

                    // Get current line
                    std::string line = f.getline(currentline);
                    bool reset = false;
                    // Loop through line
                    for(int linepos = 0; linepos < (int)line.length(); linepos++){
                        // Check if reset was triggered last character
                        if(reset){
                            linepos = 0;
                            reset = false;
                        }
                        // Check if skip clause for ContinueTo is met
                        if(currentrule.stoptype == 1 && currentrule.stopclause == line.substr(linepos,currentrule.stopclause.length()))
                            linepos+=(int)currentrule.stopclause.length();
                        // Check if stop trigger is met
                        bool Stop = (currentrule.stoptype == 0 && line.substr(linepos,currentrule.stopclause.length()) == currentrule.stopclause);
                        if(!Stop) Stop = (currentrule.stoptype == 1 && (currentrule.problem != line.substr(linepos,currentrule.problem.length())));
                        // Check if current position in line matches rule trigger
                        if(currentrule.problem == line.substr(linepos,currentrule.problem.length())){
                            switch(currentrule.fixtype){
                                // Add at problem
                                case 0:
                                    linepos+=currentrule.problem.length();
                                    line = f.addtoline(currentline, linepos, currentrule.fix);
                                    break;
                                // Add at start of line
                                case 1:
                                    linepos+=currentrule.problem.length();
                                    line = f.addtoline(currentline, 0, currentrule.fix);
                                    currentline++;
                                    break;
                                // Add at end of line
                                case 2:
                                    linepos+=currentrule.problem.length();
                                    line = f.addtoline(currentline, line.length(), currentrule.fix);
                                    break;
                                // Replace at problem
                                case 3:
                                    for(int i = 0; i < (int) currentrule.problem.length(); i++)
                                        line = f.removefromline(currentline, linepos, 1);
                                    line = f.addtoline(currentline, linepos, currentrule.fix);
                                    reset = true;
                                    break;
                                default:
                                    break;
                            }
                        }
                        if(Stop){
                            linepos = line.length();
                        }
                    }
                }
            }
            // Check if the current rule is of type running count
            else if(currentrule.type == 1){
                int rc = 0;
                std::string triggerUp = currentrule.problem.substr(0, currentrule.problem.find(" "));
                std::string triggerDown = currentrule.problem.substr(currentrule.problem.find(" ")+1);
                for(int currentline = 0; currentline < f.getlinecount(); currentline++){

                    // Get current line
                    std::string line = f.getline(currentline);

                    for(int linepos = 0; linepos < (int)line.length(); linepos++){
                        if(currentrule.stoptype==0 && currentrule.stopclause == line.substr(linepos,currentrule.stopclause.length())){
                            linepos = line.length();
                        }else
                        if(triggerDown == line.substr(linepos,triggerDown.length())){
                            rc -=1;
                        }
                    }
                    for(int i = 0; i < rc; i++)
                        f.addtoline(currentline, 0, "\t");
                    // Loop through line
                    for(int linepos = 0; linepos < (int)line.length(); linepos++){
                        if(currentrule.stoptype==0 && currentrule.stopclause == line.substr(linepos,currentrule.stopclause.length())){
                            linepos = line.length();
                        }else
                        if(triggerUp == line.substr(linepos,triggerUp.length())){
                            rc +=1;
                        }
                    }
                    
                }
            }
        }
        return f;
    };
};
