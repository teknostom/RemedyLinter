#pragma once
#include "string"

class Rule{
private:
public:
    int type;
    std::string problem;
    int fixtype;
    std::string fix;
    int stoptype;
    std::string stopclause;
    Rule(){}
    // inits a rule with type, specification for problem if needed,
    // fix type, and specification for fix if needed.
    Rule(int type, std::string problem, int fixtype, std::string fix, int stoptype, std::string stopclause){
        this->type = type;
        this->problem = problem;
        this->fixtype = fixtype;
        this->fix = fix;
        this->stoptype = stoptype;
        this->stopclause = stopclause;
    }
};