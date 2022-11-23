// Tom Evaldsson PAGPT21 PA1414 LP1 2022

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "headerfiles/formatter.h"
#include "headerfiles/Rules.h"
#include "headerfiles/progress.h"
#include "headerfiles/flags.h"
int main(int argc, char **argv)
{
    //Handle all flags
    Flags flags; 
    flags.flagsToRules(argc, argv);
    Rules r = Rules(flags.config);
    Formatter f = Formatter();
    file workingFile = file();
    Progress p = Progress(flags.debug, flags.debug, flags.filename, flags.output, r.getNumOfRules(), 1);
    
    
    //Read file;
    flags.setTimeRead();
    workingFile.ReadFile(flags.filename);

    //format file
    flags.setTimeFormatting();
    p.PrintIn(1);
    workingFile = f.formatFile(workingFile, r, p, flags.debug);

    //Write file
    flags.setTimeWrite();
    workingFile.WriteFile(flags.output);

    //End
    flags.setTimeEnd();
    flags.printTimes();

    _setmode(_fileno(stdout), _O_U8TEXT);

    p.PrintOut(1);
    std::wcout << "test" << std::endl;
    workingFile.del();
    return 0;
}