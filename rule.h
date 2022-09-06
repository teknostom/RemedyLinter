#pragma once
#include "string"

class Rule{
    // inits a rule with type, specification for problem if needed,
    // fix type, and specification for fix if needed.
    Rule(int type, std::string problem, int fixtype, std::string fix);
    // formats the rule as a string that can be handeled by the formatter.
    std::string getRule();
};