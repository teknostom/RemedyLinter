#pragma once
#include "fstream"
#include "string"
#include "rules.h"

class Formatter{
    Formatter();
    void formatFile(std::string file, Rules rules);
};
