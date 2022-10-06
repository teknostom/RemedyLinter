#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../headerfiles/file.h"
#include "../headerfiles/formatter.h"

Rules getrules(){
    Rules r = Rules();
    r.addRule(0, " ", 3, "", 1, "\t");
    r.addRule(0, "\t", 3, "", 1, " ");
    r.addRule(0, ". ", 0, "\n", 0, "%");
    r.addRule(0, "?", 0, "\n", 0, "%");
    r.addRule(0, "!", 0, "\n", 0, "%");
    r.addRule(0, "%", 0, " ", 0, "%");
    r.addRule(0, "\\section", 1, "\n", 0, "\\section");
    r.addRule(0, "\\chapter", 1, "\n", 0, "\\chapter");
    r.addRule(1, "\\begin \\end", 1, "\n", 0, "%");
    return r;
}

file formatText(std::string s){
    file f = file();
    Formatter fo = Formatter();
    Rules r = getrules();
    f.addline(s);
    fo.formatFile(f,r);
    return f;
}

file formatText(file input){
    Formatter fo = Formatter();
    Rules r = getrules();
    fo.formatFile(input,r);
    return input;
}

std::string fileToString(file input){
    std::string res = "";
    for(int i = 0; i < input.getlinecount(); i++){
        res += input.getline(i) + ((i<input.getlinecount() - 1) ? "\n" : "");
    }
    
    return res;
}

TEST_CASE( "Space should not exist before text", "[rules]" ){
    SECTION("One space"){
		file result = formatText(" ");
		REQUIRE(result.getline(0) == "");
	}
	SECTION("Space after character"){
		file result = formatText("a ");
		REQUIRE(result.getline(0) == "a ");
	}
	SECTION("Space after number"){
		file result = formatText("1 ");
		REQUIRE(result.getline(0) == "1 ");
	}
	SECTION("Space after tab"){
		file result = formatText("\t ");
		REQUIRE(result.getline(0) == "");
	}
}
TEST_CASE( "tab should not exist before text", "[rules]" ){
	SECTION("One tab"){
		file result = formatText("	");
		REQUIRE(result.getline(0) == "");
	}
	SECTION("Tab after character"){
		file result = formatText("a	");
		REQUIRE(result.getline(0) == "a	");
	}
	SECTION("Tab after number"){
		file result = formatText("1	");
		REQUIRE(result.getline(0) == "1	");
	}
	SECTION("Tab after space"){
		file result = formatText(" \t");
		REQUIRE(result.getline(0) == "");
	}
}

TEST_CASE( "Newlines with .", "[rules]" ){
    SECTION("Simple . with space after"){
        file result = formatText(". ");
        REQUIRE(result.getline(0) == ". \n");
    }   
    SECTION("No NewLine after . with no space after"){  
        file result = formatText(".");
        REQUIRE(result.getline(0) == ".");
    }
    SECTION("No NewLine after . with surrounding text"){
        file result = formatText("a.b");
        REQUIRE(result.getline(0) == "a.b");
    }
    SECTION("No NewLine after . with surrounding numbers"){
        file result = formatText("1.2");
        REQUIRE(result.getline(0) == "1.2");
    }
    SECTION("NewLine after . after long scentence"){
        file result = formatText("This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong. ");
        REQUIRE(result.getline(0) == "This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong. \n");
    }
    SECTION("NewLine after . multiple in one line"){
        file result = formatText(". . . ");
        REQUIRE(result.getline(0) == ". \n. \n. \n");
    }
}

TEST_CASE( "NewLine after !", "[rules]" ) {
    SECTION("Simple ! with space after"){
        file result = formatText("! ");
        REQUIRE(result.getline(0) == "!\n ");
    }   
    SECTION("NewLine after ! with no space after"){  
        file result = formatText("!");
        REQUIRE(result.getline(0) == "!\n");
    }
    SECTION("NewLine after ! with surrounding text"){
        file result = formatText("a!b");
        REQUIRE(result.getline(0) == "a!\nb");
    }
    SECTION("NewLine after ! with surrounding numbers"){
        file result = formatText("1!2");
        REQUIRE(result.getline(0) == "1!\n2");
    }
    SECTION("NewLine after ! after long scentence"){
        file result = formatText("This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong! ");
        REQUIRE(result.getline(0) == "This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong!\n ");
    }
    SECTION("NewLine after ! multiple in one line"){
        file result = formatText("! ! ! ");
        REQUIRE(result.getline(0) == "!\n !\n !\n ");
    }
}


TEST_CASE( "NewLine after ?", "[rules]" ) {
    SECTION("Simple ? with space after"){
        file result = formatText("? ");
        REQUIRE(result.getline(0) == "?\n ");
    }   
    SECTION("NewLine after ? with no space after"){  
        file result = formatText("?");
        REQUIRE(result.getline(0) == "?\n");
    }
    SECTION("NewLine after ? with surrounding text"){
        file result = formatText("a?b");
        REQUIRE(result.getline(0) == "a?\nb");
    }
    SECTION("NewLine after ? with surrounding numbers"){
        file result = formatText("1?2");
        REQUIRE(result.getline(0) == "1?\n2");
    }
    SECTION("NewLine after ? after long scentence"){
        file result = formatText("This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong? ");
        REQUIRE(result.getline(0) == "This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong?\n ");
    }
    SECTION("NewLine after ? multiple in one line"){
        file result = formatText("? ? ? ");
        REQUIRE(result.getline(0) == "?\n ?\n ?\n ");
    }
}

TEST_CASE( "Space after %", "[rules]" ){
    SECTION("Space after simple %"){
        file result = formatText("%");
        REQUIRE(result.getline(0) == "% ");
    }
    SECTION("Space after % with surrounding text"){
        file result = formatText("a%b");
        REQUIRE(result.getline(0) == "a% b");
    }
    SECTION("Space after % with surrounding numbers"){
        file result = formatText("1%2");
        REQUIRE(result.getline(0) == "1% 2");
    }
    SECTION("Space after % after long scentence"){
        file result = formatText("This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong%");
        REQUIRE(result.getline(0) == "This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong% ");
    }
    SECTION("Space after % before long scentence"){
        file result = formatText("%This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong");
        REQUIRE(result.getline(0) == "% This is a simulated long scentence that is just for testing purposes, if you intend to derive meaning from this, you are doing it wrong");
    }
    SECTION("No space after % in line after another %"){
        file result = formatText("%%");
        REQUIRE(result.getline(0) == "% %");
    }
    SECTION("No space after % in line after multiple %"){
        file result = formatText("%%%%%%");
        REQUIRE(result.getline(0) == "% %%%%%");
    }
}

TEST_CASE( "newline line before section", "[rules]" ) {
    SECTION("newline before one section"){
        file result = formatText("\\section");
        REQUIRE(result.getline(0) == "\n\\section");
    }
    SECTION("only one newline before two section on same line"){
        file result = formatText("\\section\\section");
        REQUIRE(result.getline(0) == "\n\\section\\section");
    }
    SECTION("multiple newlines before two sections on seperate lines"){
        file input;
        input.addline("\\section");
        input.addline("\\section");
        file result = formatText(input);
        REQUIRE(fileToString(result) == "\n\\section\n\n\\section");
    }
}

TEST_CASE( "newline line before chapter", "[rules]" ) {
    SECTION("newline before one chapter"){
        file result = formatText("\\chapter");
        REQUIRE(result.getline(0) == "\n\\chapter");
    }
    SECTION("only one newline before two chapters on same line"){
        file result = formatText("\\chapter\\chapter");
        REQUIRE(result.getline(0) == "\n\\chapter\\chapter");
    }
    SECTION("multiple newlines before two chapters on seperate lines"){
        file input;
        input.addline("\\chapter");
        input.addline("\\chapter");
        file result = formatText(input);
        REQUIRE(fileToString(result) == "\n\\chapter\n\n\\chapter");
    }
}