#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../file.h"
#include "../formatter.h"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "NewLine after .", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This.Is.A.Test.");
    fo.formatFile(f,r);
    for(int i = 0; i < 14; i++){
        if(f.getline(0).at(i) == '.'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
    }
}
TEST_CASE( "NewLine after !", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This!Is!A!Test!");
    fo.formatFile(f,r);
    for(int i = 0; i < 14; i++){
        if(f.getline(0).at(i) == '.'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
    }
}
TEST_CASE( "NewLine after ?", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This?Is?A?Test?");
    fo.formatFile(f,r);
    for(int i = 0; i < 14; i++){
        if(f.getline(0).at(i) == '.'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
    }
}
TEST_CASE( "Space after %", "[rules]"){
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This?Is?A?Test? %This Is A Comment");
    fo.formatFile(f,r);
    for(int i = 0; i < 14; i++){
        if(f.getline(0).at(i) == '%'){
            REQUIRE(f.getline(0).at(i+1) == ' ');
        }
    }
}