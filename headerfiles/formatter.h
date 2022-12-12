#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "rules.h"
#include "rule.h"
#include "file.h"
#include "progress.h"
#include "formattingFixes.h"

class Formatter{
    private:
    
    std::string fileToString(file input){
        std::string res = "";
        for(int i = 0; i < input.getlinecount(); i++){
            res += input.getline(i) + ((i<input.getlinecount() - 1) ? "\n" : "");
        }
        
        return res;
    }
    public:

    Formatter(){};

    bool match(file* f, Rule currentRule, formattingFixes* ff){
        for (int currentLine = 0; currentLine < f->getlinecount(); currentLine++) {
            std::string line = f->getline(currentLine);
            std::string triggerUp = currentRule.problem.substr(0, currentRule.problem.find(" "));
            std::string triggerDown = currentRule.problem.substr(currentRule.problem.find(" ")+1);

            for(int linePos = 0; linePos < (int)line.length(); linePos++){
                bool Stop = (currentRule.stoptype == 0 && line.substr(linePos,currentRule.stopclause.length()) == currentRule.stopclause);
                if(currentRule.stoptype == 1 && currentRule.stopclause == line.substr(linePos,currentRule.stopclause.length()))
                    linePos+=(int)currentRule.stopclause.length();
                if(!Stop)Stop = (currentRule.stoptype == 1 && (currentRule.problem != line.substr(linePos,currentRule.problem.length())));

                if(currentRule.type != 1 && currentRule.problem == line.substr(linePos,currentRule.problem.length())){
                    ff->addFix(currentLine, linePos, currentRule);
                } else if(currentRule.type == 1){
                    if(line.substr(linePos,triggerUp.length()) == triggerUp){
                        ff->addFix(currentLine, linePos, currentRule, 1);

                    }
                    if(line.substr(linePos,triggerDown.length()) == triggerDown){
                        ff->addFix(currentLine, linePos, currentRule, -1);
                    }
                } 
                if(Stop) linePos = line.length();
            }
            
        }
        return (ff->getNumRules() != 0 && currentRule.stoptype != 0 && currentRule.fix.length() < currentRule.problem.length()) ? true : false;
    }

    void fix(file* f, formattingFixes* ff){
        int lineDisplacement = 0;
        int charDisplacement = 0;
        int currentLine = -1;
        int rc = 0;

        for(int i = 0; i < ff->getNumRules(); i++){


            if(rc>0 && ff->getLine(i) - 1 != currentLine){

                for(int k = currentLine + 1; k < ff->getLine(i); k++){
                    for(int j = 0; j < rc; j++)
                        f->addtoline(k, 0, "\t");
                }
            }
            if(currentLine != ff->getLine(i)){
                charDisplacement = 0;
                currentLine = ff->getLine(i);
            }
            Rule currentRule = ff->getRule(i);
            if(currentRule.type == 1){
                if(ff->getUpDown(i) < 0){
                    rc += ff->getUpDown(i);
                }
                for(int j = 0; j < rc; j++)
                    f->addtoline(currentLine, 0, "\t");
            }else{
            switch(currentRule.fixtype){
                // Add at problem
                case 0:
                    charDisplacement+=currentRule.problem.length();
                    f->addtoline(currentLine + lineDisplacement, ff->getPos(i) + charDisplacement, currentRule.fix);
                    break;
                // Add at start of line
                case 1:
                    charDisplacement+=currentRule.problem.length();
                    f->addtoline(currentLine + lineDisplacement, 0, currentRule.fix);
                    break;
                // Add at end of line
                case 2:
                    charDisplacement+=currentRule.problem.length();
                    f->addtoline(currentLine + lineDisplacement, f->getline(i).length(), currentRule.fix);
                    break;
                // Replace at problem
                case 3:
                    f->removefromline(currentLine + lineDisplacement, ff->getPos(i) + charDisplacement, currentRule.problem.length());
                    
                    //charDisplacement -= -2;
                    f->addtoline(currentLine + lineDisplacement, ff->getPos(i) + charDisplacement, currentRule.fix);
                    //charDisplacement += currentRule.fix.length() - 2;
                    
                    break;
                default:
                    break;
            }}
                if(currentRule.fix == "\n"){
                    lineDisplacement ++;
                    charDisplacement -= f->getline(ff->getLine(i)).length() * 2;
                }
            if(ff->getUpDown(i) > 0){
                rc += ff->getUpDown(i);
            }
        }
    }

    void format(file* f, Rules rules, Progress prog, bool debug = false){
        // Loop through all Rules
        bool repeated = false;
        for(int rule = 0; rule < rules.getNumOfRules(); rule++){
            formattingFixes* ff = new formattingFixes();
            Rule currentRule = rules.getRule(rule);
            if(!repeated)prog.PrintRule(rule+1);
            repeated = match(f, currentRule, ff);
            if(repeated)
            rule --;
            fix(f, ff);
            delete ff;
        }
    }

    file formatFile(file f, Rules rules, bool debug = false){
        for(int rule = 0; rule < rules.getNumOfRules(); rule++){
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
