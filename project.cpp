#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "formatter.h"
#include "Rules.h"
#include "io.h"
#include "fcntl.h"
#include <chrono>
int main(int argc, char **argv)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    auto start = std::chrono::steady_clock::now();
    std::string filename = "";
    std::string output = "";
    bool timer = false;
    //Handle all flags
    for(int i = 1; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
        if(argv[i][0] == '-'){
            //Parse flags
            if(argv[i][1] == 'o'){
                printf("argv[%d] = %s\n", i+1, argv[i+1]);
                output = argv[i+1];
                i++;
            }
            if(argv[i][1] == 't'){
                timer = true;
            }
        }else{
            if(filename != ""){
                std::cout << "Multiple files specified." << std::endl;
                std::exit(0);
            }
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
    int k = 95;
    // Create and open a text file
    //Read file;
    //int j = 0;
    auto startin = std::chrono::steady_clock::now();
    file fi = file();
	//std::string *a = new std::string[k];
    while(std::getline(File, linebuffer)){
        fi.addline(linebuffer);
        //a[j] = linebuffer;
        //j++;
    }
    File.close();
    auto endin = std::chrono::steady_clock::now();
    

    Rules r = Rules("config.json");
    Formatter f = Formatter();
    auto startfo = std::chrono::steady_clock::now();
    f.formatFile(fi, r);
    auto endfo = std::chrono::steady_clock::now();
    //a = f.formatFile(a, 14, r);

    std::ofstream op(output);
    auto startou = std::chrono::steady_clock::now();

    for(int i = 0; i < fi.getlinecount(); i++){
        op << fi.getline(i) << ((i+2>=k) ? "" : "\n");
    }

	const wchar_t MID = L'\x251C';
	const wchar_t END = L'\x2514';
    op.close();
    auto endou = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::wcout << "Total:        "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl
        << "reading:      " << MID << std::chrono::duration_cast<std::chrono::milliseconds>(endou - startou).count() << " ms" << std::endl
        << "formatting:   " << MID << std::chrono::duration_cast<std::chrono::milliseconds>(endfo - startfo).count() << " ms" << std::endl
        << "outputting:   " << END << std::chrono::duration_cast<std::chrono::milliseconds>(endin - startin).count()
        << " ms" << std::endl;
    return 0;
}