#pragma once
#include <iostream>
#include <string>

class Progress{
private:
    const bool printMain, printFull;
    std::string input, output;
    int rules, files;
    void print(int file, int files, int type){
        std::string s;
        switch (type)
        {
        case 0:
            s = "[" + std::to_string(file) + "/" + std::to_string(files) + "] File has been read. {" + input + "}";
            std::wcout << s.c_str() << std::endl;
            break;
        case 1:
            s = "[" + std::to_string(file) + "/" + std::to_string(files) + "] File has been written. {" + input + "}";
            std::wcout << s.c_str() << std::endl;

            break;
        default:
            break;
        }
    }

    void print(int step, int totalSteps){
        std::cout << "[" << step << "/" << totalSteps << "] Rule is beening applied. {" << input << "}" << std::endl;
    }
public:
    Progress(bool printMain, bool printFull) : printMain(printMain), input(""), output(""), printFull(printFull){};
    Progress(bool printMain, bool printFull, std::string input, std::string output) : printMain(printMain), input(input), output(output), printFull(printFull) {};
    Progress(bool printMain, bool printFull, std::string input, std::string output, int rules, int files) : printMain(printMain), input(input), output(output), rules(rules), files(files), printFull(printFull) {};
    
    //Printers
    void PrintIn(int file) {
        if(printMain)
            print(file, files, 0);  
    }

    void PrintOut(int file) {
        if(printMain)
            print(file, files, 1);
    }

    void PrintRule(int rule) {
        if(printFull)
            print(rule, rules);
    }

    //Setters
    void SetInFile(std::string file){input = file;};
    void SetOutFile(std::string file){output = file;};
};