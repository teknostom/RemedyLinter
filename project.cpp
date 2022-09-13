#include <stdio.h>
#include <iostream>
#include <fstream>
int main(int argc, char **argv)
{
    
    //Handle all flags
    for(int i = 1; i < argc - 1; i++){
        if(argv[i][0] == '-'){
            //Parse flags

            //Skips the flag option
            i++;
        }
    }
    //Handle filename;
    std::string filename = argv[argc-1];
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