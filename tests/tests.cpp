#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../file.h"
#include "../formatter.h"

TEST_CASE( "NewLine after .", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This.Is.A.Test");
    fo.formatFile(f,r);
    for(int i = 0; i < (int)f.getline(0).length(); i++){
        if(f.getline(0).at(i) == '.'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
    }
}
TEST_CASE( "NewLine after !", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This!Is!A!Test");
    fo.formatFile(f,r);
    for(int i = 0; i < (int)f.getline(0).length(); i++){
        if(f.getline(0).at(i) == '!'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
    }
}
TEST_CASE( "NewLine after ?", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This?Is?A?Test");
    fo.formatFile(f,r);
    for(int i = 0; i < (int)f.getline(0).length(); i++){
        if(f.getline(0).at(i) == '?'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
    }
}

TEST_CASE( "Not Newline after %", "[rules]" ) {
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This.Is.A%.Test");
    fo.formatFile(f,r);
    bool stopped = false;
    for(int i = 0; i < (int)f.getline(0).length(); i++){
        if(!stopped && f.getline(0).at(i) == '.'){
            REQUIRE(f.getline(0).at(i+1) == '\n');
        }
        if(stopped && f.getline(0).at(i) == '.'){
            REQUIRE(f.getline(0).at(i+1) != '\n');
        }
        if(f.getline(0).at(i) == '%'){
            stopped = true;
        }
    }
}

/*
TEST_CASE( "Space after %", "[rules]"){
    file f = file();
    Formatter fo = Formatter();
    Rules r = Rules("test");
    f.addline("This?Is?A?Test? %This Is A Comment");
    fo.formatFile(f,r);
    for(int i = 0; i < 34; i++){
        if(f.getline(0).at(i) == '%'){
            REQUIRE(f.getline(0).at(i+1) == ' ');
        }
    }
}

*/