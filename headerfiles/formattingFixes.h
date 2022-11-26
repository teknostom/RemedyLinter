#pragma once
#include "string"
#include "io.h"
#include "fcntl.h"
#include "rule.h"
#include <iostream>
#include <chrono>


class fix{
private:
public:
    int line;
    int pos;
    int updown;
    Rule rule;
    fix(int line, int pos, Rule rule, int updown) : line(line), pos(pos), rule(rule), updown(updown){};
    fix(int line, int pos, Rule rule) : line(line), pos(pos), rule(rule){};
    fix(){};
    void setLine(int l){
        line = l;
    }
    void setPos(int p){
        pos = p;
    }
    void setRule(Rule r){
        rule = r;
    }
};

class formattingFixes{
private:
    int size = 10;
    fix* fixes;
    int i = 0;

    void addSize(){
        size *= 2;
        fix* temp = new fix[size];
        for(int i = 0; i < size/2; i++){
            temp[i] = fixes[i];
        }
        delete[] fixes;
        fixes = temp;
    }
public:
    formattingFixes(){
        fixes = new fix[size];
    }

    void addFix(int line, int pos, Rule rule){
        if(i == size){
            addSize();
        }
        fixes[i] = fix(line, pos, rule);
        i++;
    }
    
    void addFix(int line, int pos, Rule rule, int updown){
        if(i == size){
            addSize();
        }
        fixes[i] = fix(line, pos, rule, updown);
        i++;
    }

    int getUpDown(int i) {
        return fixes[i].updown;
    }

    int getNumRules(){
        return i;
    }

    Rule getRule(int rule){
        return fixes[rule].rule;
    }

    int getLine (int rule) {
        return fixes[rule].line;
    }

    int getPos (int rule) {
        return fixes[rule].pos;
    }
};