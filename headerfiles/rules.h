#pragma once
#include "fstream"
#include <iostream>
#include "string"
#include "rule.h"
#include "json/jsoncpp.cpp"

class Rules{
public:
    // Creates rules array from file provided by argument f. Should return null if file not found.
    int rulespace = 10;
    Rule* r;
    int i = 0;
    int rules = 0;

    //Default
    Rules(){
        r = new Rule[rulespace];
    }

    void addRuleSpace(){
        rulespace*=2;
        Rule* temp = new Rule[rulespace];
        for(int i = 0; i < rulespace/2; i++){
            temp[i] = r[i];
        }
        delete[] r;
        r = temp;

    }

    //Read from files
    Rules(std::string file){
        r = new Rule[rulespace];
        std::ifstream rulesettings(file);
        if(!rulesettings.is_open()){
            std::ofstream generateFile(file);
            generateFile << "{ \n\
    \"Rules\" : [\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \" \",\n\
        \"fixtype\": 3,\n\
        \"fix\": \"\",\n\
        \"stoptype\": 1,\n\
        \"stop\": \"\\t\"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \"\\t\",\n\
        \"fixtype\": 3,\n\
        \"fix\": \"\",\n\
        \"stoptype\": 1,\n\
        \"stop\": \" \"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \". \",\n\
        \"fixtype\": 0,\n\
        \"fix\": \"\\n\",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \"?\",\n\
        \"fixtype\": 0,\n\
        \"fix\": \"\\n\",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \"!\",\n\
        \"fixtype\": 0,\n\
        \"fix\": \"\\n\",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \"%\",\n\
        \"fixtype\": 0,\n\
        \"fix\": \" \",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \"\\\\section\",\n\
        \"fixtype\": 1,\n\
        \"fix\": \"\\n\",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    },\n\
    { \n\
        \"problemtype\": 0,\n\
        \"problem\": \"\\\\chapter\",\n\
        \"fixtype\": 1,\n\
        \"fix\": \"\\n\",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    },\n\
    { \n\
        \"problemtype\": 1,\n\
        \"problem\": \"\\\\begin \\\\end\",\n\
        \"fixtype\": 1,\n\
        \"fix\": \"\\n\",\n\
        \"stoptype\": 0,\n\
        \"stop\": \"%\"\n\
    }\n\
    ]\n\
}";
                        generateFile.close();
                        
            rulesettings.open(file);
        }
        Json::Value json;
        Json::Reader reader;
        reader.parse(rulesettings, json);
        for(int i = 0; i < (int)json["Rules"].size(); i++){
            addRule(json["Rules"][i]["problemtype"].asInt(),json["Rules"][i]["problem"].asString(),json["Rules"][i]["fixtype"].asInt(),json["Rules"][i]["fix"].asString(),json["Rules"][i]["stoptype"].asInt(),json["Rules"][i]["stop"].asString());
        }
        rulesettings.close();
        /*
        std::cout << "JSON: " << json["Rules"][0];
        addRule(0, " ", 3, "", 1, "\t");
        addRule(0, "\t", 3, "", 1, " ");
        addRule(0, ". ", 0, "\n", 0, "%");
        addRule(0, "?", 0, "\n", 0, "%");
        addRule(0, "!", 0, "\n", 0, "%");
        addRule(0, "%", 0, " ", 0, "%");
        addRule(0, "\\section", 1, "\n", 0, "\\section");
        addRule(0, "\\chapter", 1, "\n", 0, "\\chapter");
        addRule(1, "\\begin \\end", 1, "\n", 0, "%");*/
    }
    // Acesses the next rule and gets the string
    Rule getNextRule(){
        if(i <= rules){
            i++;
            return r[i-1];
        }
        std::cout << "ERROR: Reached unexpected rule";
        exit(0);
    }

    void addRule(int ruletype, std::string rule, int fixtype, std::string fix, int stoptype, std::string stoptrigger){
        if(rules+1>=rulespace){
            addRuleSpace();
        }
        r[rules] = Rule(ruletype, rule, fixtype, fix, stoptype, stoptrigger);
        rules++;
    }

    int getNumOfRules(){
        return rules;
    }
};