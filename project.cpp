#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(int argc, char **argv)
{
    std::string filename = "";
    std::string output = "";
    bool debug = false;
    //Handle all flags
    for(int i = 1; i < argc; i++){
        //printf("argv[%d] = %s\n", i, argv[i]);
        if(argv[i][0] == '-'){
            //Parse flags
            if(argv[i][1] == 'o'){
            //printf("argv[%d] = %s\n", i+1, argv[i+1]);
                output = argv[i+1];
                i++;
            }
            if(argv[i][1] == 'd'){
                debug = true;
            }
        }else{
            if(filename != ""){
                std::cout << "Multiple files specified." << std::endl;
                std::exit(0);
            }
            filename = argv[i];
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
    int k = 95;
    //Read file;
    int j = 0;
	std::string *a = new std::string[k];
    
    while(std::getline(File, linebuffer)){
        a[j] = linebuffer;

        j++;
    }
    File.close();
    if(debug == true) std::cout << "[1/1] File has been read. {" << filename << "}" << std::endl;
    std::ofstream op(output);

    for(int i = 0; i < k; i++){
        op << a[i] << ((i+2>=k) ? "" : "\n");
    }

    op.close();
    if(debug == true) std::cout << "[1/1] File has been written. {" << output << "}" << std::endl;
    return 0;
}