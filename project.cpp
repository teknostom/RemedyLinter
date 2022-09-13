#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
int main(int argc, char **argv)
{
    std::string filename = "";
    //Handle all flags
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            //Parse flags

        }else{
            filename = argv[argc-1];
        }
    }
    //Handle filename;
    if(filename == ""){
        std::cout << "No file specified" << std::endl;
        std::exit(0);
    }
    if(filename.substr(filename.length() - 4, 4) != ".tex"){
        std::cout << "The file specified is not a tex file." << std::endl;
        std::exit(0);
    }

    //Setup file reading
    std::string linebuffer;
    std::ifstream File(filename);
    //Check if file is good:
    if(!File.is_open()){
        std::cout << "The file was not found." << std::endl;
        std::exit(0);
    }
    //Read file;
    while(getline(File,linebuffer)){
        std::cout << linebuffer << std::endl;
    }
 }