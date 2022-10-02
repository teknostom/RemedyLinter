#pragma once
#include "iostream"
#include "string"
class file{
private:
    std::string* f;
    int l = 0;
    int maxLines = 100;
    int r = 0;
public:
    file(){
        f = new std::string[maxLines];
    }

    void expandStorage(){
        maxLines *=2;
        std::string* temp = new std::string[maxLines];
        for(int i = 0; i < maxLines/2; i++){
            temp[i] = f[i];
        }
        delete[] f;
        f = temp;
    }

    void addline(std::string line){
        if(l>=maxLines){
            expandStorage();
        }
        f[l] = line;
        l++;
    };

    int getlinecount(){
        return l;
    }

    std::string getline(int i){
        r = 0;
        if(i < l && l >= 0){
            return f[i];
        }
        std::cout << "ERROR: line out of range";
        exit(0);
    }

    std::string addtoline(int i, int c, std::string addition){
        if(c +r < (int)f[i].length()){
            f[i] = f[i].substr(0,c+r) + addition + "" + f[i].substr(c+r);
            r++;
        }
        return getline(i);
    }

    std::string removefromline(int i, int c){
        if(c+r < (int)f[i].length()){
            f[i] = f[i].substr(0,c-1) + "" + f[i].substr(c);
            r--;
        }
        return getline(i);
    }
};
