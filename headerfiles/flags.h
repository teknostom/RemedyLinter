#pragma once
#include "string"
#include "io.h"
#include "fcntl.h"
#include <iostream>
#include <chrono>

class Flags{
private:
public:
    std::string filename = "";
    std::string output = "output.tex";
    std::string config = "config.json";
    bool timer = false;
    bool debug = false;
    bool help = false;
    void flagsToRules(int argc, char **argv){
        if(argc <= 1) help = true;
        for(int i = 1; i < argc; i++){
            if(argv[i][0] == '-'){
                //Parse flags
                if(argv[i][1] == 'o'){
                    output = argv[i+1];
                    i++;
                }
                if(argv[i][1] == 't'){
                    timer = true;
                }
                if(argv[i][1] == 'd'){
                    debug = true;
                }
                if(argv[i][1] == 'h'){
                    help = true;
                }
                if(argv[i][1] == 'c'){
                    config = argv[i+1];
                    i++;
                }
            }else{
                if(filename != ""){
                    std::cout << "Multiple files specified." << std::endl;
                    std::exit(0);
                }
                filename = argv[i];
            }
        }
        if(help){
            _setmode(_fileno(stdout), _O_U8TEXT);
            const wchar_t MID = L'\x251C';
            const wchar_t END = L'\x2514';
            const wchar_t line = L'\x2574';
            std::wcout <<    "This is the help command." << std::endl <<
                            MID << line << "-o: Enter a filename after this flag to specify output." << std::endl <<
                            MID << line << "-c: Enter a filename after this flag to specify config." << std::endl <<
                            MID << line << "-t: This flag allows timer to be shown." << std::endl <<
                            MID << line << "-d: This flag allows debug mode to be set." << std::endl <<
                            END << line << "-h: This flag shows the help menu, it cannot be used in execution." << std::endl;
            std::exit(0);
        }

        //Handle filename
        if(filename == ""){
            std::cout << "No file specified" << std::endl;
            std::exit(0);
        }
        if(filename.substr(filename.length() - 4, 4) != ".tex"){
            std::cout << "The file specified is not a tex file." << std::endl;
            std::exit(0);
        }
    }
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point startin;
    void setTimeRead(){
        start = std::chrono::steady_clock::now();
        startin = std::chrono::steady_clock::now();
    }

    std::chrono::steady_clock::time_point endin;
    std::chrono::steady_clock::time_point startfo;
    void setTimeFormatting(){
        endin = std::chrono::steady_clock::now();
        startfo = std::chrono::steady_clock::now();
    }

    std::chrono::steady_clock::time_point endfo;
    std::chrono::steady_clock::time_point startou;
    void setTimeWrite(){
        endfo = std::chrono::steady_clock::now();
        startou = std::chrono::steady_clock::now();
    }

    std::chrono::steady_clock::time_point endou;
    std::chrono::steady_clock::time_point end;

    void setTimeEnd(){
        endou = std::chrono::steady_clock::now();
        end = std::chrono::steady_clock::now();
    }

    void printTimes(){
        if(timer == true){
            const wchar_t MID = L'\x251C';
            const wchar_t END = L'\x2514';
            _setmode(_fileno(stdout), _O_U8TEXT);
            std::wcout << "Total:        "
                << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl
                << "reading:      " << MID << std::chrono::duration_cast<std::chrono::milliseconds>(endin - startin).count() << " ms" << std::endl
                << "formatting:   " << MID << std::chrono::duration_cast<std::chrono::milliseconds>(endfo - startfo).count() << " ms" << std::endl
                << "outputting:   " << END << std::chrono::duration_cast<std::chrono::milliseconds>(endou - startou).count()
                << " ms" << std::endl;
        }
    }
};