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
    std::string Name;
    Rule(){}
    // inits a rule with type, specification for problem if needed,
    // fix type, and specification for fix if needed.
    Rule(int type, std::string problem, int fixtype, std::string fix, int stoptype, std::string stopclause, std::string Name = ""){
        //type is defined as 0 for replacement/ addition and 1 for running count.
        this->type = type;
        //problem describes the problem, what to replace or something.
        this->problem = problem;
        //fixtype is defined as 0 for add at problem, 1 for add at begining of line, 2 is add at end of line, 3 is for replace at problem.
        this->fixtype = fixtype;
        //fix is what to replace
        this->fix = fix;
        //stoptype is 0 for stop at the defined clause, 1 for go until character
        this->stoptype = stoptype;
        //stopclause is what character to stop at if stoptype is 0 and what character to skip if stoptype is 1
        this->stopclause = stopclause;

        this->Name = Name;
    }
};